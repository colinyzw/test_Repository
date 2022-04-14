#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int fd = 0;
	char buf[100];
	int nLen = 0;
	//open
	/*fd = open("/dev/tty",O_RDONLY|O_NONBLOCK);
	if(-1 == fd)
	{
		perror("open file error");
		return 1;
	}*/
	int flags = fcntl(STDIN_FILENO,F_GETFL);
	flags |= O_NONBLOCK;
	if(-1 == fcntl(STDIN_FILENO,F_SETFL,flags))
	{
		perror("set stdin error:");
		return 1;
	}
	//read
	while(1)
	{
		nLen = read(fd,buf,sizeof(buf));
		if(nLen < 0)
		{
			if(EAGAIN == errno)
			{
				sleep(1);
				continue;
			}
			perror("read file error");
			return 1;
		}
		break;
	}
	//write
	write(STDOUT_FILENO,buf,nLen);
	close(fd);
	return 0;
}
