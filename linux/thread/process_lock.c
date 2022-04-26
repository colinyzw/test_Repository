/****************************************************“
  > File Name: process_lock.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月14日 星期四 19时58分18秒
    > Modified Time:2022年04月14日 星期四 20时26分19秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DFL_CODE 5000

//進程共享資源
typedef struct 
{
	int number;
	pthread_mutex_t lock;
}shared_t;


int main(void)
{
	//1.創建映射文件
	int mfd = open("mmap_file",O_RDWR|O_CREAT,0664);
	//2.拓展映射文件
	ftruncate(mfd,sizeof(shared_t));
	//3.內存共享映射
	shared_t* date;
	if((date=mmap(NULL,sizeof(shared_t),PROT_READ|PROT_WRITE,MAP_SHARED,mfd,0))==MAP_FAILED){
		perror("mmap call failed");
		exit(0);
	}
	//4.初始化共享數據,number和互斥鎖及屬性
	date->number = 0;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&date->lock,&attr);

	//5.進程創建
	pid_t pid;
	pid = fork();
	if(pid > 0){
		for(int i=0;i<DFL_CODE;i++){
			pthread_mutex_lock(&date->lock);
			printf("parent process pid %d ++number %d\n",getpid(),++(date->number));
			pthread_mutex_unlock(&date->lock);
		}
		wait(NULL);
	}else if(pid == 0){
		for(int i=0;i<DFL_CODE;i++){
			pthread_mutex_lock(&date->lock);
			printf("child process pid %d ++number %d\n",getpid(),++(date->number));
			pthread_mutex_unlock(&date->lock);
		}
		exit(0);
	}else{
		perror("fork call failed");
		exit(0);
	}
	//銷毀釋放資源
	pthread_mutexattr_destroy(&attr);
	pthread_mutex_destroy(&date->lock);
	munmap(date,sizeof(shared_t));
	return 0;
}

