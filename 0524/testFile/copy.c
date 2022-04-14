#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEF_BUFFER_SIZE (4096)

int main(int argc,char* argv[])
{
	int fd_src = 0,fd_dest = 0,nLen = 0;
	char buf[DEF_BUFFER_SIZE] = "";
	if(argc < 3)
	{
		printf("please input src and dest filename\n");
		return 1;
	}
	umask(0000);
	fd_src = open(argv[1],O_RDONLY);
	fd_dest = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0664);
	if(-1 == fd_src || -1 == fd_dest)
	{
		printf("copy file failed\n");
		return 1;
	}
	printf("fd_src = %d,fd_dest = %d\n",fd_src,fd_dest);
	while(nLen = read(fd_src,buf,DEF_BUFFER_SIZE))
	{
		if(nLen > 0)
		{
			write(fd_dest,buf,nLen);
		}
	}
	close(fd_src);
	close(fd_dest);
	return 0;
}
