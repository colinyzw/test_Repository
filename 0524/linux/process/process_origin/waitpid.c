#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void * job(void * arg)
{
	printf("call job exec...\n");
	sleep(1);
	return NULL;
}

int main()
{
	pid_t pid;
	pid = fork();

	if(pid > 0){
		printf("grandfather parent process pid %d %d\n",getppid(),getpid());
		pid_t zpid;
		while((zpid = waitpid(-1,NULL,WNOHANG))!=-1)
		{
			if(zpid > 0)
			{
				printf("parent wait zombie success,zpid = %d\n",zpid);	
			}
			else if(zpid == 0)
			{
				job(NULL);
			}
		}
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("child process pid %d running..\n",getpid());
		sleep(8);
		exit(0);
	}else{
		perror("call fork error");
		exit(-1);
	}
	return 0;
}
