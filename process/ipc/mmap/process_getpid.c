#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	pid = fork();

	if(pid > 0)
	{
		printf("parent pid %d\n",getpid());
		while(1)
			sleep(1);
	}
	else if(pid == 0)
	{
		printf("child pid %d parent pid %d\n",getpid(),getppid());
		while(1)
			sleep(1);
	}
	else
	{
		perror("fork call failed");
		exit(0);
	}	
	return 0;	
}
