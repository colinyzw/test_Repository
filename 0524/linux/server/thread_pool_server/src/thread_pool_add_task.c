#include <thread_pool.h>


int thread_pool_add_task(thread_pool_t* pool,task_t task)
{
    if(pool->thread_shutdown)
    {
        pthread_mutex_lock(&pool->lock);
        while(pool->cur == pool->max)
            pthread_cond_wait(&pool->not_full,&pool->lock);

        if(pool->thread_shutdown == 0){
            pthread_mutex_unlock(&pool->lock);
            --pool->thread_alive;
            pthread_exit(NULL);
        }
        pool->task_list[pool->front].task_addr = task.task_addr;
        pool->task_list[pool->front].arg = task.arg;
        ++(pool->cur);
        pool->front = (pool->front + 1)%pool->max;
        pthread_mutex_unlock(&pool->lock);
        pthread_cond_signal(&pool->not_empty);
    }else{
        pthread_exit(NULL);
    }
    return 0;
}
