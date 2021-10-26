#include <stdio.h>
#include <time.h>

int main()
{
	time_t t;

	if( time(&t)==-1)
	{
		perror("Error");
		return -1;
	}

	printf("Hora en segundos desde el Epoch: %lu\n", t);

	return 0;
}
