#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


typedef struct
{
	char Gname[50];
	int Gprice;
}info_t;

int main()
{
	int fd = open("mmap_file",O_RDWR|O_CREAT,0664);
	
	ftruncate(fd,sizeof(info_t));

	info_t * ptr = NULL;
	if((ptr = mmap(NULL,sizeof(info_t),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0))==MAP_FAILED)
	{
		perror("mmap call failed");
		exit(-1);
	}
	close(fd);

	ptr->Gprice = 198;
	int flag = 0;
	while(1)
	{
		sprintf(ptr->Gname,"Pubg %d",++flag);
		sleep(1);
	}
	munmap(ptr,sizeof(info_t));

	return 0;
}
