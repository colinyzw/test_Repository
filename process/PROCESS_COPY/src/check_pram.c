#include <process_copy.h>

int check_pram(int arg_num,const char * src_file,int pro_num)
{
	if(arg_num < 3)
	{
		printf("param error : missing required param...\n");
		exit(-1);
	}
	if((access(src_file,F_OK))!=0)
	{
		printf("param error : file does not exist...\n");
		exit(-1);
	}
	if(pro_num <= 0 || pro_num > 100)
	{
		printf("param error : the number of process can not be less than 0 and greater than 100...\n");
		exit(-1);
	}
	printf("param check successful...\n");
	return 0;
}
