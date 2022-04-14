#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i=0;
	pid_t pid;
	for(i;i<5;i++)
	{
		pid = fork();
		if(pid == 0)
			break;
	}
	if(pid > 0){
		printf("parent ppid %d pid [%d] group pid [%d]\n",getppid(),getpid(),getpgrp());
		while(1)
			sleep(1);
	}else if(pid == 0){
		if(i == 0)
		{
			printf("child pid %d create group..\n",getpid());
			setpgid(getpid(),getpid());
		}
		printf("child pid [%d] group pid [%d]\n",getpid(),getpgrp());
		while(1)
			sleep(1);
	}else{
		perror("fork call failed");
		exit(0);
	}
	
	return 0;
}

