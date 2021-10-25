#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Longitud Máxima de Argumentos: %li\n", sysconf(_SC_ARG_MAX));
	printf("Número Máximo de Hijos: %li\n", sysconf(_SC_CHILD_MAX));
	printf("Número Máximo de Ficheros Abiertos: %li\n", sysconf(_SC_OPEN_MAX));
	return 0;
}
