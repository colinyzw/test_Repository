#include <stdio.h>
#include <unistd.h>

int main()
{
	if(access("xx",F_OK) < 0)
	{
		perror("access error");
		return 1;
	}
	printf("a2 exist.\n");
	return 0;
}
