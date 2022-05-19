#include <thread_pool.h>

thread_pool_t* thread_pool_create(int tmin,int tmax,int qmax)//qmax业务队列最大数
{
    printf("thread_pool_create runing...\n");
    thread_pool_t* pool = NULL;
    if((pool = (thread_pool_t*)malloc(sizeof(thread_pool_t)))==NULL)
        thread_pool_error("thrad_poll_create -> malloc poll error",0);

    pool->thread_max = tmax;
    pool->thread_min = tmin;
    pool->thread_alive = 0;
    pool->thread_busy = 0;
    pool->thread_shutdown = 1;
    pool->thread_exitcode = 0;
    printf("pool init over...\n");

    //申请消费者线程数组
    if((pool->tids = (pthread_t*)malloc(sizeof(pthread_t) * tmax))==NULL)
        thread_pool_error("thrad_poll_create -> malloc tids error",0);
    bzero(pool->tids,sizeof(pthread_t) * tmax);

    //申请任务队列
    if((pool->task_list = (task_t*)malloc(sizeof(task_t)*qmax))==NULL)
        thread_pool_error("thrad_poll_create -> malloc task_list error",0);

    pool->front = 0;
    pool->rear = 0;
    pool->max = qmax;
    pool->cur = 0;

    printf("pool init2 \n");
    if(pthread_mutex_init(&pool->lock,NULL)!=0 || pthread_cond_init(&pool->not_full,NULL)!=0 || pthread_cond_init(&pool->not_empty,NULL)!=0){
        printf("thread_pool_create-> init lock or cond error!\n");
        exit(0);
    }

    printf("poll init3\n");
    int err;//错误处理
    for(int i=0;i<tmin;i++)
    {
        if((err = pthread_create(&pool->tids[i],NULL,customer,(void*)pool))>0)
            thread_pool_error("thread_pllo_create-> customer thread error",err);
        printf("test1\n");
        ++pool->thread_alive;
        printf("thread_alive:%d\n",pool->thread_alive);
        printf("test2\n");
    }
    printf("pool init4\n");
    if((err = pthread_create(&pool->mtid,NULL,manager,(void*)pool))>0)
        thread_pool_error("thread_pllo_create-> manager thread error",err);
    printf("thread_pool_create over...\n");
    return pool;
}
