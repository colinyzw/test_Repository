#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i=0;
	pid_t pid;
	for(i;i<2;i++)
	{
		pid=fork();
		if(pid == 0)
			break;
	}
	if(pid > 0){
		printf("parent ppid %d pid %d gid %d sid %d\n",getppid(),getpid(),getpgrp(),getsid(getpid()));
		while(1)
			sleep(1);
	}else if(pid == 0){
		if(i ==0 )
		{
			setpgid(getpid(),getpgid());
			printf("child ppid %d pid %d gid %d sid %d\n",getppid(),getpid(),getpgrp(),getsid(getpid()));
		}

			printf("child ppid %d pid %d gid %d sid %d\n",getppid(),getpid(),getpgrp(),getsid(getpid()));
			while(1)
				sleep(1);
	}else{
		perror("fork call failed");
		exit(0);
	}
	return 0;
}
