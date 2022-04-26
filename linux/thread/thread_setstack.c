#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>



void* tb(void* arg)
{
	while(1)
		sleep(1);
}


int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int stacksize=0x100000;
	void* stackaddr=NULL;
	int thread_number=0;
	int err;

	while(1){
		if((stackaddr = (void*)malloc(stacksize))==NULL){
			perror("malloc call failed");
			exit(0);
		}
		pthread_attr_setstack(&attr,stackaddr,stacksize);

		if((err = pthread_create(&tid,&attr,tb,NULL))>0){
			printf("pthred_create error:%s\n",strerror(err));
			exit(0);
		}
		printf("thread number:%d\n",++thread_number);
	}

	return 0;
}
