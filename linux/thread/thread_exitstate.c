#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* tb(void* arg)
{
	while(1)
		sleep(1);
}

//只要使用pthread前缀的线程函数必须编译时 -lpthread
int main()
{
	int detachstate;
	pthread_attr_t attr;
	pthread_attr_init(&attr);//初始化线程属性

	pthread_attr_getdetachstate(&attr,&detachstate);//传出属性中的退出状态

	if(detachstate == PTHREAD_CREATE_JOINABLE)
		printf("线程属性中的退出状态为:JOINABLE..\n");
	else
		printf("线程属性中的退出状态为:DETACHED..\n");

	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	pthread_attr_getdetachstate(&attr,&detachstate);//传出属性中的退出状态

	if(detachstate == PTHREAD_CREATE_JOINABLE)
		printf("线程属性中的退出状态为:JOINABLE..\n");
	else
		printf("线程属性中的退出状态为:DETACHED..\n");
	
	pthread_t tid;
	pthread_create(&tid,&attr,tb,NULL);

	//
	int err;
	if((err = pthread_join(tid,NULL))>0){
		printf("join error:%s\n",strerror(err));
		exit(0);
	}

	return 0;
}
