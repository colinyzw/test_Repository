/****************************************************“
  > File Name: pthread_cond.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月19日 星期二 19时49分07秒
    > Modified Time:2022年04月19日 星期二 20时55分39秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int day;
pthread_mutex_t lock;
pthread_cond_t cond;
//保安A
void* ta(void* arg)
{
	while(1){
		pthread_mutex_lock(&lock);
		if(day==1){
			pthread_cond_wait(&cond,&lock);
			printf("thread a tid [0x%x] 白天工作 print day:%d\n",(unsigned int)pthread_self(),day);
			day-=1;
		}
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
}
//保安B
void* tb(void* arg)
{
	while(1){
		pthread_mutex_lock(&lock);
		if(day==0){
			pthread_cond_wait(&cond,&lock);
			printf("thread b tid [0x%x] 夜晚工作 print day:%d\n",(unsigned int)pthread_self(),day);
			day+=1;
		}
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
}

int main(void)
{
	pthread_t tida;
	pthread_t tidb;
	int errno;
	pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond,NULL);
	if((errno=pthread_create(&tida,NULL,ta,NULL))>0)
		printf("create thread a failed...%s\n",strerror(errno));
	if((errno=pthread_create(&tidb,NULL,tb,NULL))>0)
		printf("create thread b failed...%s\n",strerror(errno));

	pthread_join(tida,NULL);
	pthread_join(tidb,NULL);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	return 0;
}
