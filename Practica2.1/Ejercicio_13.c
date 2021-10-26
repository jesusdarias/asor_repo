#include <stdio.h>
#include <sys/time.h>


int main()
{

	
	struct timeval tv_antes;
	struct timeval tv_despues;
	

	if(gettimeofday(&tv_antes, NULL)==-1)
	{
		perror("Error");
		return -1;
	}

	int i;
	
	for(i=0; i < 1000000;i++)
	

	if(gettimeofday(&tv_despues, NULL)==-1)
	{
		perror("Error");
		return -1;
	}
	
	suseconds_t total = tv_despues.tv_usec - tv_antes.tv_usec;

	printf("Microsegundos que tarda el bucle: %lu\n", total);
	
	

	return 0;
}
