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
	while(1)
		sleep(1);
}


int main()
{
	pthread_t tid;
	int arg = 1024;
	pthread_create(&tid,NULL,tb,(void*)&arg);
	printf("主进程创建完毕...\n");
	
	while(1)
		sleep(1);
	//线程的生命周期随进程持续
	return 0;
}
