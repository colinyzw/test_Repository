/****************************************************“
  > File Name: tcp_server.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月26日 星期二 13时47分18秒
  > Modified Time:2022年05月02日 星期一 13时28分35秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>//大小端转换
#include <sys/socket.h>//socket套接字
#include <ctype.h>//转换大小写

//完成基本连接及简单的数据交互，（请求响应），业务处理
//服务端可以帮助客户端完成简单的数据处理，大小写转换

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

int server_accepting(int sfd)
{
	struct sockaddr_in client_addr;
	int client_fd;
	socklen_t addrlen;
	addrlen = sizeof(client_addr);
	char cip[IP_SIZE];
	bzero(cip,IP_SIZE);
	//阻塞模型，等待连接，建立 连接，存储客户端网络信息及存储客户端socket
	if((client_fd = accept(sfd,(struct sockaddr*)&client_addr,&addrlen))>0){
		printf("tcp server accept success :client ip[%s] client port[%d]\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,IP_SIZE),client_addr.sin_port);
	}else{
		perror("Accept call failed");
		return -1;
	}
    return client_fd;
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

//阻塞读取数据请求
int server_recv_response(int sockfd)
{
	printf("111\n");
	char recv_buffer[BUFFER_SIZE];
	bzero(recv_buffer,BUFFER_SIZE);
	ssize_t recvlen;
	printf("222\n");
	while((recvlen = recv(sockfd,recv_buffer,sizeof(recv_buffer),0))>0)
	{

		printf("test...\n");
		//处理请求
		bussiness(recv_buffer,recvlen);
		//反馈响应
		send(sockfd,recv_buffer,recvlen,0);
		bzero(recv_buffer,sizeof(recv_buffer));
	}
	printf("333\n");
	return 0;
}


int main(void)
{
	int sfd;
	int cfd;
	sfd = server_net_init();//网络初始化成功
	cfd = server_accepting(sfd);//等待连接
	printf("test1...\n");
	server_recv_response(cfd);//读取请求，处理请求，响应结果
	printf("test2...\n");

	close(cfd);
	close(sfd);
	return 0;
}
