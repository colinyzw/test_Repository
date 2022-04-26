#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void sig_alarm(int n)
{
	//空捕捉
}

unsigned int mysleep(unsigned int seconds)
{
	unsigned int reval;
	//信号捕捉设定，让SIGALRM失效
	struct sigaction act,oact;
	act.sa_handler = sig_alarm;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM,&act,&oact);
	//屏蔽SIGALRM信号
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	sigprocmask(SIG_SETMASK,&set,&oset);


	reval = alarm(seconds);//CPU定时，到时后内核向该进程发送SIGALRM信号
	//pause();//调用pause挂起当前进程，pause察觉到系统信号则唤醒
	//调用pause挂起当前进程，pause察觉到系统信号则唤醒

	sleep(3);
	sigsuspend(&act.sa_mask);//解除屏蔽字，一定要保证内部对应SIGALRM信号位永远为0
	return reval;


}

int main()
{
	while(1)
	{
		mysleep(2);
		printf("sleep two seconds...\n");
	}
	return 0;
}
