#include <process_copy.h>

void zombie_wait(void)
{
	pid_t wpid;
	while((wpid = waitpid(-1,NULL,WNOHANG))!=-1)
	{
		if(wpid > 0)
			printf("parent process %d wait the zombie process successful...\n",getpid());
		else
			continue;
	}
}
