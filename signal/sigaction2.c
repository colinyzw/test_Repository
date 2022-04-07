#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sig_int(int n)
{
	int flag = 3;
	while(flag){
		printf("   flag %d \n",flag);
		sleep(1);
		--flag;
	}
}

int main(void)
{
	//信号行为的修改是针对一个信号的
	struct sigaction newact,oldact;

	//void (*sa_handler)(int)
	newact.sa_handler = sig_int;//自定义捕捉行为
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);//初始化临时屏蔽字
	
	sigaction(SIGINT,&newact,&oldact);
	while(1)
		sleep(1);
	return 0;
}
