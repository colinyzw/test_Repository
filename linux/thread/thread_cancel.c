#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void * tb(void * targ)
{
	//普通线程工作

	while(1)
	{
		pthread_testcancel();
	}

}


int main()
{
	pthread_t tid;
	void* reval;

	pthread_create(&tid,NULL,tb,NULL);
	sleep(5);
	
	pthread_cancel(tid);
	printf("join.....\n");
	pthread_join(tid,&reval);
	printf("join thread success return value %ld\n",(long int)reval);
	while(1)
		sleep(1);
	//线程的生命周期随进程持续
	return 0;
}
