/****************************************************“
  > File Name: thread_pool_error.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年05月05日 星期四 16时35分33秒
  > Modified Time:2022年05月05日 星期四 16时41分31秒
 ****************************************************/

#include <thread_pool.h>

void thread_pool_error(const char* str,int errcode)
{
    if(errcode == 0)
    {
        perror(str);
        exit(errcode);
    }else{
        printf("%s,%s\n",str,strerror(errcode));
        pthread_exit(NULL);
    }
}
