#include <thread_pool.h>

void* bussiness_accept(void* arg)
{
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    int serverfd = *(int*)arg;
    int clientfd;

    struct epoll_event node;

    addrlen = sizeof(clientaddr);

    pthread_mutex_lock(&accept_lock);
    if((clientfd = accept(serverfd,(struct sockaddr*)&clientaddr,&addrlen))==-1)
    {
        pthread_mutex_unlock(&accept_lock);
        thread_pool_error("bussiness_accept <F3>-> accept call failed",0);

    }
    pthread_mutex_unlock(&accept_lock);

    node.data.fd = clientfd;
    node.events = EPOLLIN|EPOLLET;

    epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&node);

    return NULL;
}
