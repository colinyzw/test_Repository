#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int convert(int o)
{
	int d = 0;
	int count = 1;
	while(o != 0)
	{
		d += o%10*count;
		count = count * 8;
		o = o/10;
	}
	printf("%d\n",d);
	return d;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("./chmod mode file\n");
		return 1;
	}

	int mode = atoi(argv[1]);
	//check file exist
	if(access(argv[2],F_OK) < 0)
	{
		perror("access error");
		return 1;
	}
	else
	{
		//change mode
		if(chmod(argv[2],convert(mode)) < 0)
		{
			perror("chmod error");
			return 1;
		}
		printf("chmod success\n");
	}
		
	return 0;
} 
