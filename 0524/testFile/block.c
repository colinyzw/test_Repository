#include <stdio.h>
#include <unistd.h>

int main()
{
	char buf[10];
	int nLen = 0;

	nLen = read(STDIN_FILENO,buf,sizeof(buf));
	write(STDOUT_FILENO,buf,nLen);

	return 0;
}
