#include <thread_pool.h>

void* bussiness_response(void* arg)
{
    char buffer[_BUFFERSIZE];
    ssize_t recvlen;
    int flag = 0;
    int clientfd = *(int*)arg;

    while((recvlen = recv(clientfd,buffer,sizeof(buffer),MSG_DONTWAIT))>0)//非阻塞读取IO
    {
        while(recvlen > flag)
        {
            buffer[flag] = toupper(buffer[flag]);
            flag++;
        }
        send(clientfd,buffer,recvlen,MSG_NOSIGNAL);
    }
    if(recvlen == 0)
    {
        epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,NULL);
        close(clientfd);
    }
    return NULL;
}
