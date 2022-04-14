#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd = 0,nLen = 0;
	if(argc < 2)
	{
		printf("please input file\n");
		return 1;
	}
	//open file
	fd = open(argv[1],O_RDONLY);
	if(-1 == fd)
	{
		printf("open file error\n");
		return 1;
	}

	//read file
	char buf[1024] = "";
	lseek(fd,5,SEEK_SET);
	nLen = read(fd,buf,sizeof(buf));
	write(STDOUT_FILENO,buf,nLen);
	printf("read file size:%d\n",nLen);

	//file size
	nLen = lseek(fd,0,SEEK_END);
	printf("file size:%d\n",nLen);

	close(fd);
	return 0;
}
