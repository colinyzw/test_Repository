#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void daemon_create();

void daemon_jobs();

void daemon_jobs()
{
	int fd;
	fd=open("time.log",O_RDWR|O_CREAT,0664);
	char time_buf[1024];
	bzero(time_buf,sizeof(time_buf));
	time_t t;

	while(1)
	{
		t = time(NULL);
		ctime_r(&t,time_buf);
		write(fd,time_buf,strlen(time_buf));
		bzero(time_buf,sizeof(time_buf));
		sleep(3);
	}
}

void daemon_create()
{
	pid_t pid;
	pid = fork();
	if(pid > 0){
		exit(0);
	}else if(pid == 0){
		setsid();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);

		chdir("./");
		umask(0002);
		daemon_jobs();
	}else{
		perror("fork call failed");
		exit(-1);
	}

}

int main()
{
	daemon_create();
	return 0;
}
