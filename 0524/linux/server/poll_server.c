/****************************************************“
  > File Name: tcp_server.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月26日 星期二 13时47分18秒
  > Modified Time:2022年05月02日 星期一 14时52分26秒
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
#include <sys/select.h>
#include <poll.h>


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

int poll_starting(int sockfd)
{
	int readycode;//就绪量
	struct pollfd listen_array[1024];
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t addrlen;

	listen_array[0].fd = sockfd;
	listen_array[0].events = POLLIN;

	for(int i=1;i<1024;i++){
		listen_array[i].fd = -1;
		listen_array[i].events = POLLIN;
	}

	printf("Poll server Running...\n");

	while(SHUTDOWN){
		readycode = poll(listen_array,1024,-1);//阻塞监听sock读事件，就绪时返回
		while(readycode){//循环处理就绪事件
			if(listen_array[0].revents == POLLIN){//serverfd就绪
				addrlen = sizeof(client_addr);
				if((client_fd = accept(sockfd,(struct sockaddr*)&client_addr,&addrlen))>0){
					//连接成功，打印输出客户端信息
					for(int i =0;i<1024;i++)
						if(listen_array[i].fd==-1){
							listen_array[i].fd=client_fd;
							break;
						}
					listen_array[0].revents = 0;
				}else{
					perror("accept call failed");
                    exit(0);
				}
			}else{//clientfd就绪
				for(int i=1;i<1024;i++)
					if(listen_array[i].fd!=-1)
						if(listen_array[i].revents == POLLIN){
							if((server_recv_response(listen_array[i].fd))==-1){
								close(listen_array[i].fd);//删除监听
								listen_array[i].fd = -1;///删除数据
							}
							listen_array[i].revents = 0;//事件处理完毕，就绪集合对应位清0
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
	poll_starting(sfd);
	close(sfd);

	return 0;
}
