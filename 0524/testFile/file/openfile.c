#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int fd = 0, i = 0;
	char name[100]="";
	for(i;1;i++)
	{
		sprintf(name,"file%d",i);
		fd = open(name,O_CREAT,0666);
		if(-1 == fd)
		{
			printf("i = %d\n",i);
			perror("open error");
			return 1;
		}
	}
	return 0;
}
