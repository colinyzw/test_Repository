#include <thread_pool.h>


void* manager(void* arg)
{
    thread_pool_t* p = NULL;
    p = (thread_pool_t*)arg;
    pthread_detach(pthread_self());

    int alive;
    int busy;
    int cur;

    while(p->thread_shutdown)
    {
        pthread_mutex_lock(&p->lock);
        alive = p->thread_alive;
        busy = p->thread_busy;
        cur = p->cur;
        pthread_mutex_unlock(&p->lock);

        printf(">>>>manager 0x%x starting <<<<<<\n\tthread_max %d\n\tthread_min %d\n\tthread_alive %d\n\tthread_busy %d\n\tque_cur %d\n\tthread_idel %d\n\tBusy/alive %.2f%%\n\tAlive/ALL %.2f%%\n\n",(unsigned int)pthread_self(),p->thread_max,p->thread_min,alive,busy,cur,alive-busy,(double)busy/alive*100,(double)alive/p->thread_max*100);
        //扩容条件
        int flag;//tids下标
        int add;//创建数量
        int err;
        if((cur > alive - busy || busy / alive * 100 >= 70) && (alive + _DFLNUM)<= p->thread_max)
        {
            for(flag=0,add=0;flag < p->thread_max && add < _DFLNUM;flag++)
            {
                if(p->tids[flag] == 0 || !if_thread_alive(p->tids[flag]))
                {
                    if((err = pthread_create(&p->tids[flag],NULL,customer,(void*)p))>0)
                        thread_pool_error("manager -> thread create error",err);
                    pthread_mutex_lock(&p->lock);
                    ++(p->thread_alive);
                    pthread_mutex_unlock(&p->lock);
                    add++;
                }
            }

        }

        //缩减条件
        if(busy*2 <= alive-busy && alive-_DFLNUM >= p->thread_min)
        {
            //挂起在not_empty的线程，都是闲线程，管理者可以唤醒这些线程
            pthread_mutex_lock(&p->lock);
            p->thread_exitcode = _DFLNUM;
            pthread_mutex_unlock(&p->lock);

            for(int i=0;i<10;i++)
                pthread_cond_signal(&p->not_empty);

        }
        sleep(_TIMEOUT);
    }
    pthread_exit(NULL);
}
