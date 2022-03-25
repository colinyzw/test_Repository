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
		printf("父进程完成工作区任务...\n");
	}
	else if(pid ==0 )
	{//child start
		printf("子进程完成工作区任务...\n");
		while(1)
			sleep(1);
	//child end
	}
	else
	{
		perror("fork call failed");
	}
	printf("父进程完成其他任务...\n");
	while(1)
		sleep(1);

	while(1)
		sleep(1);

	return 0;	
	//parent end
}
