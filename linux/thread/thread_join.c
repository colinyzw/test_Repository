#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void * tb(void * targ)
{
	//普通线程工作
	int arg = *(int*)targ;
	printf("普通线程,接受参数为%d\n",arg);

	sleep(3);
	return (void*)7;

}


int main()
{
	pthread_t tid;
	int arg = 1024;
	void* reval;

	pthread_create(&tid,NULL,tb,(void*)&arg);
	printf("主进程创建完毕...\n");
	
	printf("join.....\n");
	pthread_join(tid,&reval);
	printf("join thread success return value %ld\n",(long int)reval);
	while(1)
		sleep(1);
	//线程的生命周期随进程持续
	return 0;
}
