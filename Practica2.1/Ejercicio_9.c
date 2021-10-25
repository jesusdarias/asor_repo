#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

	printf("User ID: %d\n",getuid());
        printf("Effective User ID: %d\n",geteuid());
	printf("Group ID: %d\n",getgid());
        printf("Effective Group ID: %d\n",getegid());

	//podemos asegurar que el bit setuid está activado
	//cuando el usuario o grupo efectivo difiere del 
	//del usuario o grupo del fichero.

	return 0;
}
