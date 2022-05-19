/****************************************************“
  > File Name: tcp_client.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月26日 星期二 16时34分40秒
    > Modified Time:2022年05月02日 星期一 10时48分39秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(void)
{
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	inet_pton(AF_INET,"192.168.110.129",&server_addr.sin_addr.s_addr);

	int cfd = socket(AF_INET,SOCK_STREAM,0);

	int reval;
	ssize_t recvlen;
	char buffer[1500]; 
	bzero(buffer,sizeof(buffer));

	if((reval = connect(cfd,(struct sockaddr*)&server_addr,sizeof(server_addr)))==0)
	{
		printf("client connect success...\n");

		//连接成功，读取标准输入，循环向客户端发送请求数据
		while((fgets(buffer,sizeof(buffer),stdin))!=NULL){
			send(cfd,buffer,strlen(buffer),0);
			recvlen = recv(cfd,buffer,sizeof(buffer),0);
			write(STDOUT_FILENO,buffer,recvlen);
			bzero(buffer,sizeof(buffer));
		}
	}else if(reval == -1){
		perror("connect call failed");
		exit(-1);
	}
	return 0;


}
