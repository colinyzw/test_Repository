#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void * tb(void * arg)
{
	while(1)
		sleep(1);
}

int main()
{
	int flag = 0;
	int err;
	pthread_t tid;
	while(1)
	{
		if((err = pthread_create(&tid,NULL,tb,NULL)) > 0){
			printf("pthread_create error:%s\n",strerror(err));
			exit(0);
		}
		printf("create thread no %d\n",++flag);
	}
	return 0;
}
