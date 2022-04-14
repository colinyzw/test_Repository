#include<stdio.h>
#include"common.h"

int main()
{
	int c = add(2,3);
	printf("2 + 3 = %d\n",c);
	#ifdef DEF_DEBUG
		printf("debug verrsion\n");
	#else
		printf("no log\n");
	#endif //DEF_DEBUG
	return 0;
}
