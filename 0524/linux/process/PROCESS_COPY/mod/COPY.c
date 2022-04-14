#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc,char ** argv)
{
	int sfd;
	int dfd;
	int pos = atoi(argv[3]);
	int blocksize = atoi(argv[4]);
	int read_len;
	char buffer[blocksize];
	bzero(buffer,sizeof(buffer));
	sfd = open(argv[1],O_RDONLY);
	dfd = open(argv[2],O_RDWR|O_CREAT,0664);
	lseek(sfd,pos,SEEK_SET);
	lseek(dfd,pos,SEEK_SET);
	read_len = read(sfd,buffer,sizeof(buffer));
	write(dfd,buffer,read_len);
	printf("child process %d copy_pos [%d] copy_blocksize [%d]\n",getpid(),pos,blocksize);
	close(sfd);
	close(dfd);
	return 0;
}
