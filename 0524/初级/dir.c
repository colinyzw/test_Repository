#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_PATH (1024)

void dirwalk(char* dir)
{
	char name[MAX_PATH] = "";
	struct dirent* dp;
	DIR* dfd = opendir(dir);
	if(NULL == dfd)
	{
		printf("dirwalk:open fail %s\n",dir);
		return;
	}
	while(NULL != (dp = readdir(dfd)))
	{
		if(0 == strcmp(".",dp->d_name) || 0 == strcmp("..",dp->d_name))
		{
			continue;
		}
		if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) 
		{
			printf("dirwalk:name:%s/%s too long\n",dir,dp->d_name);
		}
		else
		{
			sprintf(name,"%s/%s",dir,dp->d_name);
			fsize(name);
		}
	}
	closedir(dfd);
}

int fsize(char* path)
{
	struct stat buf;
	if(-1 == stat(path,&buf))
	{
		printf("fsize:open fail%s\n",path);
		return;
	}
	if(S_IFDIR == (S_IFMT & buf.st_mode))
	{
		dirwalk(path);
	}
	printf("%d %s\n",buf.st_size,path);
}

int main(int argc,char* argv[])
{
	if(1 == argc)
	{
		fsize(".");
	}
	else if(2 == argc)
	{
		fsize(argv[1]);
	}
	else
	{
		printf("too many.\n");
	}
	return 0;
}
