#include <thread_pool.h>


int server_epoll_listen(thread_pool_t* p,int sockfd)
{
    printf("server_epoll_listen runing ...\n");
    int readycode;
    int flag;
    struct epoll_event ready_array[_EPOLLSIZE];
    struct epoll_event node;

    task_t task;
    while(p->thread_shutdown)
    {
        flag = 0;
        if((readycode=epoll_wait(epfd,ready_array,_EPOLLSIZE,-1))==-1)
            thread_pool_error("server_epoll_listen -> epoll_wait call failed",0);
        while(readycode)
        {
            if(ready_array[flag].data.fd == sockfd)
            {
                task.task_addr = bussiness_accept;
                task.arg = (void*)&(ready_array[flag].data.fd);
                //add task
                thread_pool_add_task(p,task);
            }else{
                task.task_addr = bussiness_response;
                task.arg = (void*)&(ready_array[flag].data.fd);
                //add task
                thread_pool_add_task(p,task);
            }
            --readycode;
            ++flag;
        }
    }
    close(epfd);
    printf("server_epoll_listen voer..\n");
    return 0;
}
