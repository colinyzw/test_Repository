#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

int main()
{
    int mfd = open("mmap_file",O_RDWR);	
	int fsize = lseek(mfd,0,SEEK_END);
	int *ptr = NULL;
	if((ptr = mmap(NULL,fsize,PROT_READ|PROT_WRITE,MAP_SHARED,mfd,0)) == MAP_FAILED)
	{
		perror("mmap call failed");
		exit(0);
	}

	close(mfd);

	ptr[0] = 0x34333231;
	munmap(ptr,fsize);

	return 0;
}
