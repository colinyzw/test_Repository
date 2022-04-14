#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void parent_sig(int n,siginfo_t* info,void * arg)
{
	union sigval val;
	printf("parent pid %d numer=%d\n",getpid(),info->si_int);
	val.sival_int = ++(info->si_int);
	sigqueue(getpid()+1,SIGUSR1,val);
	usleep(50000);//delay
}
void child_sig(int n,siginfo_t* info,void * arg)
{
	union sigval val;
	printf("child pid %d numer=%d\n",getpid(),info->si_int);
	val.sival_int = ++(info->si_int);
	sigqueue(getppid(),SIGUSR2,val);
	usleep(50000);//delay

}


int main()
{
	////父进程捕捉设定
	struct sigaction act,oact;
	act.sa_sigaction = parent_sig;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR2,&act,&oact);

	////屏蔽SIGUSR1，继承
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set,SIGUSR1);
	sigprocmask(SIG_SETMASK,&set,&oset);

	pid_t pid;
	pid = fork();

	if(pid > 0){
		//父进程第一次向子进程发送信号
		union sigval val;
		val.sival_int = 1;
		sigqueue(pid,SIGUSR1,val);
		while(1)
			sleep(1);//等待信号
	}else if(pid == 0){
		//子进程完成捕捉设定
		struct sigaction act,oact;
		act.sa_sigaction = child_sig;
		act.sa_flags = SA_SIGINFO;
		sigemptyset(&act.sa_mask);
		sigaction(SIGUSR1,&act,&oact);
		//解除屏蔽SIGUSR1
		sigprocmask(SIG_SETMASK,&act.sa_mask,NULL);

		while(1)
			sleep(1);//等待信号
	}else{
		perror("fork call failed...");
		exit(-1);
	}

	return 0;
}
