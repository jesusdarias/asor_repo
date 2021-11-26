#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char **argv)
{
	printf("PID:%d\n",getpid());
	printf("PPID:%d\n",getppid());
	printf("PGID:%d\n",getgid());
	printf("SID:%d\n",getsid(getpid()));

  	char path[4096];
  	char *path_ptr = getcwd(path, 4096);
	
	struct rlimit l;
	int rc = getrlimit(RLIMIT_NOFILE, &l);
	if(rc==-1) 
	{
		perror("No se pudo obtener el límite de ficheros");
		return -1;
	}
	printf("Número máximo de ficheros que puede abrir: %lu\n",(long unsigned)l.rlim_cur);

	if(path_ptr==NULL) 
	{
		perror("No se pudo obtener el directorio de trabajo actual");
		return -1;
	}
		
	else printf("Directorio de trabajo actual:%s\n",path);
	
	return 0;
}

