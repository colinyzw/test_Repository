#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/epoll.h>

#define _SERVERIP "192.168.110.129"
#define _SERVERPORT 8080
#define _BUFFERSIZE 1500
#define _IPSIZE 16
#define _EPOLLSIZE 200000
#define _TIMEOUT 2
#define _DFLNUM 10 //扩容缩减
#define _BACKLOG 128 //监听

int epfd;
pthread_mutex_t accept_lock;

typedef struct
{
    void* (*task_addr)(void*);
    void* arg;
}task_t;

typedef struct
{
    int thread_max;
    int thread_min;
    int thread_alive;
    int thread_busy;
    int thread_shutdown;
    int thread_exitcode;

    pthread_t* tids;//消费者线程
    pthread_t mtid;//管理者线程

    task_t* task_list;
    int front;
    int rear;
    int max;
    int cur;

    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;

}thread_pool_t;

thread_pool_t* thread_pool_create(int,int,int);
int thread_pool_destroy(thread_pool_t*);
int thread_pool_add_task(thread_pool_t*,task_t);
void* customer(void*);
void* manager(void*);
void* bussiness_accept(void*);
void* bussiness_response(void*);
void thread_pool_error(const char*,int);
int if_thread_alive(pthread_t);
int server_net_init(void);
int server_epoll_create(int);
int server_epoll_listen(thread_pool_t*,int);
