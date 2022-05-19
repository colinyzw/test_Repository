#include <thread_pool.h>


int server_net_init(void)
{
    int server_fd;
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(_SERVERPORT);
    inet_pton(AF_INET,_SERVERIP,&serveraddr.sin_addr.s_addr);

    printf("server_net_init runing..\n");
    if((server_fd = socket(AF_INET,SOCK_STREAM,0))==-1)
        thread_pool_error("server_net_init -> create socket error",0);

    if((bind(server_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))==-1)
    thread_pool_error("server_net_init -> bind error",0);

    listen(server_fd,_BACKLOG);
    printf("server_net_init over...\n");

    return server_fd;
}
