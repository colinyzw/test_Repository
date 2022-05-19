#include <thread_pool.h>


int main(void)
{
    int sockfd;
    thread_pool_t* pool = NULL;
    sockfd = server_net_init();
    server_epoll_create(sockfd);
    pthread_mutex_init(&accept_lock,NULL);

    pool = thread_pool_create(10,100,20);

    server_epoll_listen(pool,sockfd);

    close(sockfd);
    pthread_mutex_destroy(&accept_lock);
    thread_pool_destroy(pool);
    return 0;
}
