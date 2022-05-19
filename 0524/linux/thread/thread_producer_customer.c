/****************************************************“
  > File Name: thread_producer_customer.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月20日 星期三 19时21分05秒
    > Modified Time:2022年04月21日 星期四 10时32分58秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


typedef struct
{
	void* (*task_addr)(void*);//业务地址//类似于线程函数
	void* arg;//业务参数
}task_t;//业务

typedef struct
{
	task_t* task_list;
	int front;
	int rear;
	int cur;//当前任务数
	int maxsize;
}container_t;//环形队列作为容器


pthread_mutex_t lock;
pthread_cond_t not_full;//生产者非满
pthread_cond_t not_empty;//消费者非空

//生产者任务
int producer_add_task(container_t* ct,task_t job)//生产者调用，调用一次添加一个任务
{
	pthread_mutex_lock(&lock);
	if(ct->cur == ct->maxsize)
		pthread_cond_wait(&not_full,&lock);
	ct->task_list[ct->front].task_addr = job.task_addr;
	ct->task_list[ct->front].arg = job.arg;
	ct->cur++;
	ct->front = (ct->front + 1)% ct->maxsize;
	pthread_mutex_unlock(&lock);
	pthread_cond_signal(&not_empty);
	return 0;
}

//消费者任务
void* customer_job(void* arg)//消费者任务，从容器中获取任务并执行
{
	container_t* ct = (container_t*)arg;
	task_t task;
	pthread_detach(pthread_self());
	while(1){
		pthread_mutex_lock(&lock);
		while(ct->cur == 0)//while可以多检测一次//signal如果工作于多核处理器可能调用一次唤醒多个线程
			pthread_cond_wait(&not_empty,&lock);
		task.task_addr = ct->task_list[ct->rear].task_addr;
		task.arg = ct->task_list[ct->rear].arg;
		(ct->cur)--;
		ct->rear = (ct->rear + 1) % ct->maxsize;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&not_full);
		//执行任务不要放在锁里
		(task.task_addr)(task.arg);
	}
	pthread_exit(NULL);
}

//容器创建初始化
container_t* container_create(int maxsize)
{
	container_t* ct = NULL;
	ct = (container_t*)malloc(sizeof(container_t));
	ct->task_list = (task_t*)malloc(sizeof(task_t)*maxsize);
	ct->front = 0;
	ct->rear = 0;
	ct->cur = 0;
	ct->maxsize = maxsize;
	if(pthread_mutex_init(&lock,NULL) || pthread_cond_init(&not_full,NULL) || pthread_cond_init(&not_empty,NULL))
	{
		printf("inint lock or cond error\n");
		exit(0);
	}
	return ct;
}

//自定义任务
void* business(void* arg)
{
	printf("Customer tid [0x%x] start Bussiness....\n",(unsigned int)pthread_self());
	sleep(1);//任务处理时长1s
	return (void*)0;
}

int main(void)
{
	pthread_t ctids[5];
	container_t* ct = NULL;
	ct = container_create(100);
	task_t bs;
	bs.task_addr = business;
	bs.arg = NULL;
	for(int i=0;i<5;i++){
		pthread_create(&ctids[i],NULL,customer_job,(void*)ct);
	}
	//主线程作为生产者，普通线程为消费者，一对多模式
	while(1){//测试任务添加
		for(int i=0;i<5;i++)
			producer_add_task(ct,bs);
		sleep(5);
	}
	return 0;
}




