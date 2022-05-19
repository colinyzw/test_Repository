/****************************************************“
  > File Name: tcp_server.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月26日 星期二 13时47分18秒
    > Modified Time:2022年04月26日 星期二 23时13分54秒
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


//建立连接后创建子进程
int SHUTDOWN=1;

#define _SERVER_PORT 8080
#define _SERVER_IP "192.168.110.129"
#define BACK_LOG 128
#define IP_SIZE 16
#define BUFFER_SIZE 1500

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
    while((recvlen = recv(sockfd,recv_buffer,sizeof(recv_buffer),0))>0)
    {   
	    //处理请求
		bussiness(recv_buffer,recvlen);
		//反馈响应
		send(sockfd,recv_buffer,recvlen,0);
		bzero(recv_buffer,sizeof(recv_buffer));
	}
	if(recvlen == 0)
	{
		printf("client exit .thread 0x%x exiting...\n",(unsigned int)pthread_self());

	}
	return 0;
}

//处理线程
void* thread_job(void* arg)
{
	int client_fd = *(int*)arg;
	pthread_detach(pthread_self());
	printf("wait thread 0x%x waiting...\n",(unsigned int)pthread_self());
	server_recv_response(client_fd);//读取请求，处理请求，响应结果

	while(1)
		sleep(1);//睡眠等待信号

}

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


int server_accepting(int sfd)
{
	pthread_t tid;
	struct sockaddr_in client_addr;
	int client_fd;
	socklen_t addrlen;
	addrlen = sizeof(client_addr);
	char cip[IP_SIZE];
	bzero(cip,IP_SIZE);
	//阻塞模型，等待连接，建立连接，存储客户端网络信息及存储客户端socket
	if((client_fd = accept(sfd,(struct sockaddr*)&client_addr,&addrlen))>0){
			printf("tcp server main thread 0x%x accept success :client ip[%s] client port[%d]\n",(unsigned int)pthread_self(),inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,IP_SIZE),client_addr.sin_port);
			pthread_create(&tid,NULL,thread_job,(void*)&client_fd);
	}else{
		perror("Accept call failed");
		return -1;
	}
}


int main(void)
{
	int sfd;
	int cfd;
	

	sfd = server_net_init();//网络初始化成功
	while(SHUTDOWN)
		cfd = server_accepting(sfd);//等待连接

	close(cfd);
	close(sfd);
	return 0;
}
