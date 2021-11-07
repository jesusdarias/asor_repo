#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

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
		perror("No se pudo duplicar el descriptor para stdout");
		return -1;
	}

	rc = dup2(fd,2);

	if(rc==-1)
	{
		perror("No se pudo duplicar el descriptor para stderr");
		return -1;
	}


	fprintf(stdout,"Probando a mostrar cadenas por STDOUT...\n");
	fprintf(stdout, "Cadena 1\n");
	fprintf(stdout,"Cadena 2\n");
	fprintf(stdout, "Cadena 3\n");
	fprintf(stderr, "Probando a mostrar cadenas por STDERR...\n");
	fprintf(stderr, "Error 1\n");
	fprintf(stderr, "Error 2\n");
	fprintf(stderr, "Error 3\n");

	return 0;
}
