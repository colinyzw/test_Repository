#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define CODE 5000

int number;
pthread_mutex_t lock;

void* ta(void* arg)
{
	int tmp;
	pthread_detach(pthread_self());
	for(int i=0;i<CODE;i++)
	{
		pthread_mutex_lock(&lock);
		tmp = number;
		printf("ta thread 0x%x ++ number = %d\n",(unsigned int)pthread_self(),++tmp);
		number = tmp;
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}

void* tb(void* arg)
{
	int tmp;
	pthread_detach(pthread_self());
	for(int i=0;i<CODE;i++)
	{
		pthread_mutex_lock(&lock);
		tmp = number;
		printf("tb thread 0x%x ++ number = %d\n",(unsigned int)pthread_self(),++tmp);
		number = tmp;
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}


int main(void)
{
	pthread_t tid;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&tid,NULL,ta,NULL);
	pthread_create(&tid,NULL,tb,NULL);

	while(1)
		sleep(1);
	
	pthread_mutex_destroy(&lock);

	return 0;
}

