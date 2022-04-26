#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sig_int(int n)
{
	printf("捕捉函数执行，捕捉的信号编号为：%d\n",n);
}

int main(void)
{
	//信号行为的修改是针对一个信号的
	struct sigaction newact,oldact;

	//void (*sa_handler)(int)
	newact.sa_handler = sig_int;//自定义捕捉行为
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);//初始化临时屏蔽字
	
	struct sigaction act9,oact9;
	act9.sa_handler = sig_int;//自定义捕捉行为
	act9.sa_flags = 0;
	sigemptyset(&act9.sa_mask);//初始化临时屏蔽字

	sigaction(SIGKILL,&act9,&oact9);
	sigaction(SIGINT,&newact,&oldact);
	while(1)
		sleep(1);
	return 0;
}
