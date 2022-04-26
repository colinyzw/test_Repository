#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* tb()
{
	pthread_detach(pthread_self());
	while(1)
		sleep(1);
}

int main(void)
{
	pthread_t tid;
	int err;
	pthread_create(&tid,NULL,tb,NULL);

	printf("join...\n");
	sleep(0);

	if((err = pthread_join(tid,NULL)) > 0)
	{
		printf("call pthread_join failed:%s\n",strerror(err));
		exit(0);
	}
	return 0;
}
