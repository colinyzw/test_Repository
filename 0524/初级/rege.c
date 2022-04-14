#include <stdio.h>
#include <regex.h>
#include <sys/types.h>

void regexMatch(char* pRegexStr,char* pText)
{
	regex_t oregex;
	int errcode = 0;
	char errmag[1024] = "";
	size_t errlength = 0;

	errcode = regcomp(&oregex,pRegexStr,/*REG_EXTENDED|REG_NOSUB*/0);
	if(0 == errcode)
	{
		int nmatch = 2;
		regmatch_t pmatch[2];
		char buf[1024] = "" ;

		errcode = regexec( &oregex, pText, nmatch, pmatch, 0);
		if (0 == errcode)
		{
			printf(" %s match %s\n" ，pRegexStr, pText);
			for(inti=0;i<2;i++)
			{
				int begin = pmatch[i].rm_so;
				int end = pmatch[i].rm_eo;
				printf("begin=%d, end=%d\n", begin, end);
				if(-1=begin||-1==end)
				{
					continue ;
				}
				snprintf(buf, end - begin + 1, "%s", pText + begin);
				printf("match string: %s\n", buf);
			}
			regfree(&oregex);
			return;
		}
	}
	errlength = regerror(errcode, &oregex, errmsg, sizeof(errmsg));
	printf("%s match error: %s\n", pRegexStr ，errmsg);
	regfree(&oregex);
}
	
	
int main(int argc,char* argv[])
{
	if(3!=argc)
	{
		printf("%s regex text\n",argv[0]);
		return 1;
	}
	regexMatch(argv[1],argv[2]);
	return 0;
}
