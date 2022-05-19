#include <thread_pool.h>

void* customer(void* arg)
{
    thread_pool_t* p = NULL;
    p = (thread_pool_t*)arg;
    task_t tmp;
    while(p->thread_shutdown)
    {
        pthread_mutex_lock(&p->lock);
        while(p->cur == 0)
        {
            pthread_cond_wait(&p->not_empty,&p->lock);
            if(p->thread_exitcode > 0)
            {
                //消费者自行缩减退出
                --(p->thread_alive);
                --(p->thread_exitcode);
                pthread_mutex_unlock(&p->lock);
                pthread_exit(NULL);
            }
        }
        if(!p->thread_shutdown)
        {
            --(p->thread_alive);
            pthread_mutex_unlock(&p->lock);
            pthread_exit(NULL);
        }

        tmp.task_addr = p->task_list[p->rear].task_addr;
        tmp.arg = p->task_list[p->rear].arg;
        --(p->cur);
        p->rear = (p->rear + 1) % p->max;
        ++(p->thread_busy);
        pthread_mutex_unlock(&p->lock);
        pthread_cond_signal(&p->not_full);

        (tmp.task_addr)(tmp.arg);

        pthread_mutex_lock(&p->lock);
        --(p->thread_busy);
        pthread_mutex_unlock(&p->lock);
    }
    pthread_exit(NULL);
}
