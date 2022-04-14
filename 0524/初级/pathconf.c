#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("%ld\n",fpathconf(STDIN_FILENO,_PC_NAME_MAX));
	printf("%ld\n",pathconf("a2",_PC_NAME_MAX));
	return 0;
}
