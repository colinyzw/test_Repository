#include <process_copy.h>


void str_err(const char * errstr, int exitcode)
{
	perror(errstr);
	exit(exitcode);
}
