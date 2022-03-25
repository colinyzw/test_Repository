#include <process_copy.h>

int block_cur(const char * src_file,int pro_num)
{
	int filesize;
	int fd;
	if((fd = open(src_file,0,O_RDONLY))==-1)
		str_err("block_cur >> open call failed",-1);
	
	if((filesize = lseek(fd,0,SEEK_END))==-1)
		str_err("block_cur >> lseek call failed",-1);
	close(fd);
	if(filesize % pro_num == 0)
		return filesize / pro_num;
	else
		return filesize / pro_num + 1;
}
