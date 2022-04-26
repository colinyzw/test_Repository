#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void sig_int()
{
	printf("***********\n");
}

int main(void)
{
	char buffer[0x1000];
	bzero(buffer,sizeof(buffer));

	int len;

	struct sigaction newact,oldact;
	newact.sa_handler = sig_int;
	newact.sa_flags = 0;
	sigemptyset(&newact.sa_mask);

	sigaction(SIGINT,&newact,&oldact);
	
	printf("read...\n");
	if((len = read(STDIN_FILENO,buffer,sizeof(buffer))) == -1)
	{
		if(errno == EINTR)
		{
			printf("read again...\n");
			len = read(STDIN_FILENO,buffer,sizeof(buffer));
		}
	}


	return 0;
}
