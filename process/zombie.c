#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main()
{
	pid_t pid;
	pid = fork();

	if(pid > 0){
		printf("parent process pid %d \n",getpid());
		pid_t zpid;
		zpid = wait(NULL);
		printf("parent wait zombie success,zpid = %d\n",zpid);
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
