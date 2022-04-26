#include <process_copy.h>

int main(int argc ,char ** argv)
{
	int pro_num;
	int blocksize;
	if(argv[3]==0)
		pro_num = 5;
	else
		pro_num = atoi(argv[3]);
	
	check_pram(argc,argv[1],pro_num);
	blocksize = block_cur(argv[1],pro_num);

	process_create(argv[1],argv[2],pro_num,blocksize);

	return 0;
}
