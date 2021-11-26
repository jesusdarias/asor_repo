#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>




int main(int argc, char **argv){

	pid_t pid = fork();

	if(pid==-1)
	{ 
		perror("Error al hacer fork");
		exit(1);
	}
	else if(pid==0)
	{
		//hijo
		
		chdir("/tmp");
		setsid();
		printf("Proceso HIJO\n");
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
			exit(1);
		}
		printf("Número máximo de ficheros que puede abrir: %lu\n",(long 			unsigned)l.rlim_cur);

		if(path_ptr==NULL) 
		{
			perror("No se pudo obtener el directorio de trabajo actual");
			exit(1);
		}
		else 
			printf("Directorio de trabajo actual:%s\n\n",path);
		
		
	}
	else
	{
		//padre
		printf("Proceso PADRE\n");
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
			exit(1);
		}
		printf("Número máximo de ficheros que puede abrir: %lu\n",(long unsigned)l.rlim_cur);

		if(path_ptr==NULL) 
		{
			perror("No se pudo obtener el directorio de trabajo actual");
			exit(1);
		}
		else 
			printf("Directorio de trabajo actual:%s\n\n",path);

	}

	return 0;

}

