#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{

	if(argc!=2)
	{
		printf("Usage: ./ejercicio_11 <filename>\n");
		return -1;
	}

	struct stat buf;

	int rc = stat(argv[1], &buf);

	if(rc==-1)
	{
		perror("Error al ejecutar stat");
		return -1;
	}

	if((buf.st_mode & S_IFMT) == S_IFREG)
	{
		char * ruta = strdup(argv[1]);

		rc = link(argv[1], strcat(ruta,".hard"));

		if(rc==-1)
		{
			perror("Error al crear el enlace rígido");
			return -1;
		}
		
		ruta = strdup(argv[1]);
		rc = symlink(argv[1], strcat(ruta,".sym"));

		if(rc==-1)
		{
			perror("Error al crear el enlace simbólico");
			return -1;
		}

	}
	else
	{
		printf("No es un fichero regular.");
	}


	return 0;
}
