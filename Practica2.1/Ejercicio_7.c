#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Número Máximo de Enlaces: %li\n", pathconf("/",_PC_LINK_MAX));
	printf("Tamaño Máximo de Ruta: %li\n", pathconf("/",_PC_PATH_MAX));
	printf("Tamaño Máximo de Nombre: %li\n", pathconf("/",_PC_NAME_MAX));

	return 0;
}
