#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	int fd;
	char buffer[1024] = "";
	int len;
	fd = open("fifo",O_RDONLY);

	len = read(fd,buffer,sizeof(buffer));

	printf("process b pid %d srecv message success= %s...\n",getpid(),buffer);

	close(fd);
	
	printf("delete fifo...\n");
	unlink("fifo");

	return 0;
}
