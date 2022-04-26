/****************************************************“
  > File Name: thread_read.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月14日 星期四 18时43分49秒
    > Modified Time:2022年04月14日 星期四 19时00分02秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int number;
pthread_rwlock_t lock;

void* thread_read(void* arg)
{
	while(1){
		pthread_rwlock_rdlock(&lock);
		printf("read thread tid [0x%x] print number:%d\n",(unsigned int)pthread_self(),number);
		pthread_rwlock_unlock(&lock);
		usleep(50000);
	}
}
void* thread_write(void* arg)
{
	while(1){
		pthread_rwlock_wrlock(&lock);
		printf("write thread tid [0x%x] print number:%d\n",(unsigned int)pthread_self(),++number);
		pthread_rwlock_unlock(&lock);
		usleep(50000);
	}

}
int main(void)
{
	pthread_t tids[8];
	int i = 0;
	int err;

	pthread_rwlock_init(&lock,NULL);

	for(i;i<3;i++)
		if((err=pthread_create(&tids[i],NULL,thread_write,NULL))>0)
			printf("pthread_create call failed:%s\n",strerror(err));
	for(i;i<8;i++)
		if((err=pthread_create(&tids[i],NULL,thread_read,NULL))>0)
			printf("pthread_create call failed:%s\n",strerror(err));
	while(i--)//循環回收
		pthread_join(tids[i],NULL);

	pthread_rwlock_destroy(&lock);

	return 0;
}
