#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void str_err(const char * errstr,int exitcode);

void zombie_wait(void);

int check_parm(int arg_num,const char * src_file,int pro_num);

int block_cur(const char * src_file,int pro_num);

int process_create(const char * src_file,const char * des_file,int pro_num,int blocksize);
