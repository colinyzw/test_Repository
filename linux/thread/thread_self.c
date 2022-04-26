#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


void * tb(void * arg)
{
	printf("普通线程十进制tid:0x%x\n",(unsigned int)pthread_self());
	while(1)
		sleep(1);
}
int main()
{
	pthread_t tid;
	printf("主线程十进制tid:0x%x\n",(unsigned int)pthread_self());

	pthread_create(&tid,NULL,tb,NULL);

	while(1)
		sleep(1);

}
