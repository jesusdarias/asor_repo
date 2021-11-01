#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




int main(int argc, char **argv)
{

	if(argc!=2)
	{
		printf("Usage: ./ejercicio_15 <filename>\n");
		return -1;
	}

	int fd = open(argv[1], O_RDWR);
	
	if(fd == -1)
	{
		perror("Error al abrir el fichero");
		return -1;
	}
	
	int lock = lockf(fd, F_TEST,0);
	
	if(lock == -1)
	{
		perror("El fichero está bloqueado");
	}
	else
	{
		
		printf("El fichero está desbloqueado.\n");
		printf("Fijando cerrojo...\n");
		lock = lockf(fd, F_LOCK,0);
		if(lock == -1)
		{
			perror("El fichero está bloqueado");
			return 0;
		}
		
		
		struct tm *lt;
		time_t t;
		time(&t);
		lt = localtime(&t);

		if(lt==NULL)
		{
			perror("Error");
			return -1;
		}

		char cadena[50];

		strftime(cadena,50,"%H:%M:%S\n", lt);
   		printf(cadena);

		sleep(30);	

		lock = lockf(fd, F_ULOCK,0);
		if(lock == -1)
		{
			perror("Error al desbloquear el fichero");
			return 0;
		}
		
	}

	return 0;
}
