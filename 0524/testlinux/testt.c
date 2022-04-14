#include <stdio.h>
#include <unistd.h>

int main()
{
	int i=0;
	for(i = 0;i<2;i++)
	{
		pid_t fpid = fork();
		if(fpid == 0)
		{
			printf("%d child %4d %4d %4d\n",i,getppid(),getpid(),fpid);
		}
		else
		{
			printf("%d parent %4d %4d %4d\n",i,getppid(),getpid(),fpid);
		}
	}
	return 0;
}
