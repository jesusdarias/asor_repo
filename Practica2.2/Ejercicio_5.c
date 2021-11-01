#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

	int rc = open("./fichero5", O_CREAT, 0645);

	if(rc == -1)
	{
		perror("Error al crear el fichero");
		return -1;
	}


	return 0;
}

