#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>





int main(int argc, char **argv)
{

	if(argc!=2)
	{
		printf("Usage: ./ejercicio_9 <filename>\n");
		return -1;
	}

	struct stat buf;

	int rc = stat(argv[1], &buf);

	if(rc==-1)
	{
		perror("Error al ejecutar stat");
		return -1;
	}

	printf("Major Number: %d\n", major(buf.st_dev));
	printf("Minor Number: %d\n", minor(buf.st_dev));
	printf("I-Nodo: %ld\n", (long)buf.st_ino);
	printf("Tipo de Fichero: ");
	
	switch (buf.st_mode & S_IFMT) {
           case S_IFBLK:  printf("Dispositivo de caracteres\n");            break;
           case S_IFCHR:  printf("Dispositivo de bloque\n");        	    break;
           case S_IFDIR:  printf("Directorio\n");                	    break;
           case S_IFIFO:  printf("FIFO/pipe\n");               		    break;
           case S_IFLNK:  printf("Enlace simbólico\n");                     break;
           case S_IFREG:  printf("Fichero regular\n");            	    break;
           case S_IFSOCK: printf("Socket\n");                  		    break;
           default:       printf("Desconocido?\n");                	    break;
           }

	printf("Hora de último acceso: %s", ctime(&buf.st_atime));

	//la diferencia entre st_mtime y st_ctime es que el primero contiene la fecha de
	// la última modificación del contenido del fichero, pero sin cambiar información del
	// i-nodo. st_ctime contiene la fecha de modiciación del i-nodo, ya sea por un cambio de
	// permisos, propietario, etc.



	return 0;
}
