#include <stdio.h>
#include <time.h>


int main()
{
	
	struct tm *lt;
	time_t t;
	time(&t);
	lt = localtime(&t);

	if(lt==NULL)
	{
		perror("Error");
		return -1;
	}

	printf("Año: %d\n", lt->tm_year +1900);


	return 0;
}
