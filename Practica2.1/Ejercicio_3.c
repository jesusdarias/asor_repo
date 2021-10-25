#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>

int main()
{
	int i;
	for(i=1; i <= 133;i++)
	{
		printf("Error Code %d: %s\n", i,strerror(i));
	}

	return 0;
}
