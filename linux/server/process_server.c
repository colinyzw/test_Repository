/****************************************************“
  > File Name: tcp_server.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月26日 星期二 13时47分18秒
    > Modified Time:2022年04月26日 星期二 22时35分08秒
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

void sig_wait(int n)//捕捉函数
{
	pid_t zpid;
	int status;
	while((zpid = waitpid(-1,&status,WNOHANG))>0)
	{
		if(WIFEXITED(status))
			printf("thread 0x%x wait success,zpid %d exitcode or reval %d\n",(unsigned int)pthread_self(),zpid,WEXITSTATUS(status));
		if(WIFSIGNALED(status))
			printf("thread 0x%x wait success,zpid %d signal No  %d\n",(unsigned int)pthread_self(),zpid,WTERMSIG(status));
	}

}

void* thread_wait(void* arg)
{
	//被创建后屏蔽了SIGCHLD信号
	pthread_detach(pthread_self());
	struct sigaction act,oact;
	act.sa_handler = sig_wait;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	sigaction(SIGCHLD,&act,&oact);

	sigprocmask(SIG_SETMASK,&act.sa_mask,NULL);
	printf("wait thread 0x%x waiting...\n",(unsigned int)pthread_self());

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
		printf("client exit .child %d exiting...\n",getpid());
	}
	return 0;
}

int server_accepting(int sfd)
{
	struct sockaddr_in client_addr;
	int client_fd;
	socklen_t addrlen;
	addrlen = sizeof(client_addr);
	char cip[IP_SIZE];
	bzero(cip,IP_SIZE);
	pid_t pid;
	//阻塞模型，等待连接，建立连接，存储客户端网络信息及存储客户端socket
	if((client_fd = accept(sfd,(struct sockaddr*)&client_addr,&addrlen))>0){
		pid = fork();
		if(pid>0){
			printf("tcp server accept success :client ip[%s] client port[%d]\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cip,IP_SIZE),client_addr.sin_port);
		}else if(pid == 0){
			server_recv_response(client_fd);//读取请求，处理请求，响应结果
		}else{
			perror("fork call failed");
			exit(0);
		}
	}else{
		perror("Accept call failed");
		return -1;
	}
}


int main(void)
{
	int sfd;
	int cfd;
	
	//主线程设置屏蔽，--》继承给普通线程
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	sigprocmask(SIG_SETMASK,&set,&oset);

	//回收线程创建
	pthread_t tid;
	pthread_create(&tid,NULL,thread_wait,NULL);

	sfd = server_net_init();//网络初始化成功
	while(SHUTDOWN)
		cfd = server_accepting(sfd);//等待连接

	close(cfd);
	close(sfd);
	return 0;
}
