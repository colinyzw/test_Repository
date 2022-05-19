/****************************************************“
  > File Name: set_flock_a.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月19日 星期二 18时29分53秒
    > Modified Time:2022年04月19日 星期二 18时51分16秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	int fd = open("thread_join.c",O_RDWR);
	struct flock nlock,olock;
	nlock.l_type = F_WRLCK;//设置写锁关键字 
	nlock.l_whence = SEEK_SET;
	nlock.l_start = 0;
	nlock.l_len = 0;//对整个文件上锁

	//查看文件锁状态
	fcntl(fd,F_GETLK,&olock);
	
		printf("pid %d seting write lock....\n",getpid());
		fcntl(fd,F_SETLKW,&nlock);//阻塞上锁
		printf("pid %d set lock successful....\n",getpid());
		sleep(10);
		nlock.l_type = F_UNLCK;//设置解锁关键字
		fcntl(fd,F_SETLK,&nlock);//解锁
		printf("pid %d set unlock....\n",getpid());
	
	return 0;
}

