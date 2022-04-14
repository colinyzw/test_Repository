#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	char msg[] = "this is a test\n";
	int save_fd;
	int fd = open("test",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	save_fd = dup(STDOUT_FILENO);
	dup2(fd,STDOUT_FILENO);

	close(fd);
	write(STDOUT_FILENO,msg,strlen(msg));

	close(save_fd);
	close(STDOUT_FILENO);

	return 0;
}
