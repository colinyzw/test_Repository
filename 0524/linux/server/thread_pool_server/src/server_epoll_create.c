#include <thread_pool.h>


int server_epoll_create(int server_fd)
{
    printf("server_epoll_create runing...\n");
    if((epfd = epoll_create(_EPOLLSIZE))==-1)
        thread_pool_error("server_epoll_create -> epoll create error",0);

    struct epoll_event node;
    node.data.fd = server_fd;
    node.events = EPOLLIN;
    node.events|=EPOLLET;

    if((epoll_ctl(epfd,EPOLL_CTL_ADD,server_fd,&node))==-1)
        thread_pool_error("server_epoll_create -> epoll ctl add server_fd error",0);
    printf("server_epoll_create over..\n");
    return 0;
}
