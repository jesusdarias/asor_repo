#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>
#include <string.h>

int main()
{
	struct utsname buf;

	if(uname(&buf)==-1)
	{
		printf("Syscall uname failed with error code %d: %s", errno, strerror(errno));
		return -1;
	}

	printf("Sistema Operativo: %s\n", buf.sysname);
	printf("Nombre del Nodo: %s\n", buf.nodename);
	printf("Release del Sistema Operativo: %s\n", buf.release);
	printf("Versión del Sistema Operativo: %s\n", buf.version);
	printf("Identificador Hardware: %s\n", buf.machine);

	
	return 0;
}
