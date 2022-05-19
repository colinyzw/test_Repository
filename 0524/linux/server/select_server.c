/****************************************************“
  > File Name: tcp_server.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月26日 星期二 13时47分18秒
  > Modified Time:2022年05月02日 星期一 14时44分06秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>//大小端转换
#include <sys/socket.h>//socket套接字
#include <ctype.h>//转换大小写
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netdb.h>
//#include <sys/select.h>


//建立连接后创建子进程
int SHUTDOWN=1;

#define _SERVER_PORT 8080
#define _SERVER_IP "192.168.110.129"
#define BACK_LOG 128
#define IP_SIZE 16
#define BUFFER_SIZE 1500


int server_net_init(void)
{
	int server_fd;
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(_SERVER_PORT);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//设置本机任意ip
	inet_pton(AF_INET,_SERVER_IP,&server_addr.sin_addr.s_addr);//转换并设置自定义ip
	server_fd = socket(AF_INET,SOCK_STREAM,0);
	bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(server_fd,BACK_LOG);
	printf("Tcp Server Start Net init success...\n");
	return server_fd;
}

void bussiness(char* response,ssize_t recvlen)
{
	int flag = 0;
	while(recvlen > flag)
	{
		response[flag] = toupper(response[flag]);
		flag++;
	}
}

int server_recv_response(int sockfd)
{
    char recv_buffer[BUFFER_SIZE];
    bzero(recv_buffer,BUFFER_SIZE);
    ssize_t recvlen;
    if((recvlen = recv(sockfd,recv_buffer,sizeof(recv_buffer),0))>0)
    {
	    //处理请求
		bussiness(recv_buffer,recvlen);
		//反馈响应
		send(sockfd,recv_buffer,recvlen,0);
		bzero(recv_buffer,sizeof(recv_buffer));
	}
	if(recvlen == 0)
	{
		printf("client exit.child %d exiting...\n",getpid());
		return -1;
	}
	return 0;
}

int select_starting(int sockfd)
{
	int readycode;
	fd_set nset,oset;
	int clientfd_array[1021];
	int maxfd;
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t addrlen;

	maxfd=sockfd;
	FD_ZERO(&nset);
	FD_SET(sockfd,&nset);

	for(int i=0;i<1021;i++)
		clientfd_array[i]=-1;
	printf("select server runing..\n");
	while(1){
		oset = nset;
		readycode = select(maxfd+1,&oset,NULL,NULL,NULL);//阻塞监听sock读事件，就绪时返回
		while(readycode){//循环处理就绪事件
			if((FD_ISSET(sockfd,&oset)))
            {//serverfd就绪
				addrlen = sizeof(client_addr);
				if((client_fd = accept(sockfd,(struct sockaddr*)&client_addr,&addrlen))>0){
					//连接成功，打印输出客户端信息
                    printf("连接客户端加一\n");
					if(client_fd > maxfd)
						maxfd = client_fd;
					FD_SET(client_fd,&nset);
					for(int i =0;i<1021;i++)
						if(clientfd_array[i]==-1){
							clientfd_array[i]=client_fd;
							break;
						}
					FD_CLR(sockfd,&oset);//事件处理完毕，就绪集合对应位清0
				}else{
					perror("accept call failed");
                    exit(0);
				}
			}else{//clientfd就绪
				for(int i=0;i<1021;i++)
					if(clientfd_array[i]!=-1)
						if((FD_ISSET(clientfd_array[i],&oset))){
							if((server_recv_response(clientfd_array[i]))==-1){
                                printf("客户端退出\n");
								FD_CLR(clientfd_array[i],&nset);//删除监听
								clientfd_array[i] = -1;///删除数据
							}
							FD_CLR(clientfd_array[i],&oset);//事件处理完毕，就绪集合对应位清0
							break;
						}

			}
			--readycode;
		}

	}
}


int main(void)
{
	int sfd;

	sfd = server_net_init();
	int cfd;
	select_starting(sfd);
	close(sfd);

	return 0;
}
