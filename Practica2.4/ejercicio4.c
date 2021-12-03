#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Usage: %s <argumento>\n", argv[0]);
		return -1;
	}
	//debe haber un fichero especial tipo pipe llamado tubería.
	int fd = open("tuberia",O_WRONLY);

	if(fd==-1)
	{
		perror("No se ha podido abrir la tubería");
		return -1;
	}

	ssize_t rc =write(fd, argv[1], strlen(argv[1])+1);
	if(rc==-1)
	{
		perror("Error al escribir en la tubería");
		return -1;
	}
	close(fd);

	return 0;

}
