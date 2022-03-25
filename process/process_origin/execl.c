#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0){
		printf("parent process pid %d %d running...\n",getppid(),getpid());
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("child process pid %d Execl firebox\n",getpid());
		char* parm[]={"firefox","https://www.baidu.com",NULL};
		//execl("/usr/bin/firefox","firefox","https://www.baidu.com",NULL);
		//execlp("firefox","firefox","https://www.baidu.com",NULL);
		execv("/usr/bin/firefox",parm);
	}else{
		perror("fork failed");
		exit(-1);
	}

	return 0;	
}
