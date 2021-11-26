#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char **argv){


	if (argc < 2) {
   	   printf("Usage: %s <command> <options>\n",argv[0]);
   	   return -1;
      	}

	int fdin=open("/dev/null",O_CREAT|O_RDWR|O_TRUNC,0777);
	int fdout=open("/tmp/daemon.out",O_CREAT|O_RDWR|O_TRUNC,0777);
   	int fderr=open("/tmp/daemon.err",O_CREAT|O_RDWR|O_TRUNC,0777);
	pid_t pid = fork();

	if(pid==-1)
	{ 
		perror("Error al hacer fork");
		exit(1);
	}
	else if(pid==0)
	{
		//hijo
		setsid();
		dup2(fdin,0);
   		dup2(fdout,1);
		dup2(fderr,2);
 
		execvp(argv[1], argv+1);
	}
	else
	{
		//padre
		int status;
		wait(&status);
		
		if(status==-1)
		{
			perror("El proceso hijo no terminó correctamente.");
			exit(1);
		}

		printf("El comando terminó de ejecutarse\n");

	}

	return 0;

}

