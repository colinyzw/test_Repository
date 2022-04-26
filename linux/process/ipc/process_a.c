#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define msg "test message...."

int main()
{
	int fd;
	fd = open("fifo",O_WRONLY);

	write(fd,msg,strlen(msg));

	printf("process a pid %d send message success...\n",getpid());

	close(fd);


	return 0;
}
