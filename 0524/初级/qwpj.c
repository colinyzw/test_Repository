#include<stdio.h>

int qwpj(int high)
{
	int day = 0;
	int m = 0;
	while(1)
	{
		day++;
		m += 5;
		if(m >= high){
			return day;
		}
		m -= 4;
	}
	
}
int  main()
{

	int day = qwpj(10);
	printf("%d days out\n",day);


	return 0;
}
