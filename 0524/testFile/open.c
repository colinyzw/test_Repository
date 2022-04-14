#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	int fd = 0;
	if(argc < 2)
	{
		printf("please input filename\n");
		return 1;
	}
	umask(0000);
	fd = open(argv[1],O_CREAT,0666);
	if(-1 == fd)
	{
		printf("create file failed\n");
		return 1;
	}
	printf("fd = %d\n",fd);
	close(fd);
	return 0;
}
