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

	
   	char cadena[100];

	strftime(cadena,100,"%A, %d de %B de %Y, %R\n", lt);
   	printf(cadena);


	return 0;
}
