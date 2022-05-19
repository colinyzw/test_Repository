#include <thread_pool.h>


int thread_pool_destroy(thread_pool_t* p)
{
    printf("thread_pool_destroy runing...\n");
    free(p->task_list);
    free(p->tids);
    pthread_mutex_destroy(&p->lock);
    pthread_cond_destroy(&p->not_full);
    pthread_cond_destroy(&p->not_empty);
    free(p);
    printf("thread_pool_destroy over...\n");
    return 0;
}
