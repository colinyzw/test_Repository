#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int main(int argc,char ** argv)
{
	if(argc < 3)
	{
		printf("parameters error..\n");
		exit(0);
	}

	kill(atoi(argv[2]),atoi(argv[1]));

	return 0;
}
