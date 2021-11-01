#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	umask(0757);
	
	int rc = open("./fichero7", O_CREAT, 0645);

	if(rc == -1)
	{
		perror("Error al crear el fichero");
		return -1;
	}


	return 0;
}

