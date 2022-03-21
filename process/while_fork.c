#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	int i;
	for(i=0;i<7;i++)
	{
		pid=fork();
		if(pid == 0)
			break;
	}
	if(pid > 0)
	{
		printf("parent pid %d\n",getpid());
		while(1)
			sleep(1);
	}
	else if(pid == 0)
	{
		if(i == 0)
		{
			printf("woshilaoda\n");
		}
		else if(i == 1)
		{
			printf("woshilaoer\n");
		}
		else if(i == 2)
		{
			printf("woshilaosan\n");
		}
		else if(i == 3)
		{
			printf("woshilaosi\n");
		}
		else
		{
			printf("sleep\n");
		}
		while(1)
			sleep(1);
	}
	else
	{
		perror("fork call failed");
		exit(-1);
	}
	return 0;
}
