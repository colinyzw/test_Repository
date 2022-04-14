#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd = open("abc",O_RDONLY);

	if(-1 == fd)
	{
		printf("open error:%d\n",errno);
		perror("open file failed");
		printf("open file error:%s\n",strerror(errno));
	}

	return 0;

}

