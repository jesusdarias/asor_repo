#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char**argv)
{

	if(argc!=2)
	{
		printf("Usage: %s <filename>", argv[0]);
		return -1;
	}

	int fd = open(argv[1],O_RDWR);

	if(fd == -1)
	{
		perror("No se pudo abrir el fichero");
		return -1;
	}

	int rc = dup2(fd,1);

	if(rc==-1)
	{
		perror("No se pudo duplicar el descriptor");
		return -1;
	}

	printf("Probando a mostrar cadenas por stdout...\n");
	printf("Cadena 1\n");
	printf("Cadena 2\n");
	printf("Cadena 3\n");

	return 0;
}
