#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	struct stat buf;
	if(argc < 2)
	{
		printf("please input filename.\n");
		return 1;
	}

	if(lstat(argv[1],&buf) < 0)
	{
		perror("stat error");
		return 1;
	}

	printf("file[%s]size:%ld\n",argv[1],buf.st_size);

	return 0;
}
