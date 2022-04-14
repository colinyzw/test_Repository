#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void print_pset(sigset_t pset)
{
	int signo;
	for(signo=1;signo<32;signo++)
	{
		if((sigismember(&pset,signo))==1)
			putchar('1');
		else
			putchar('0');
	}
	putchar('\n');
}

int main(void)
{
	sigset_t newset,oldset,pset;
	sigemptyset(&newset);
	sigaddset(&newset,SIGINT);
	sigaddset(&newset,SIGQUIT);
	sigaddset(&newset,SIGKILL);
	sigprocmask(SIG_SETMASK,&newset,&oldset);
    
	//sleep(10);
	//sigprocmask(SIG_SETMASK,&oldset,NULL);

	while(1){
		sigpending(&pset);
		print_pset(pset);
		sleep(1);
	}
	return 0;
}
