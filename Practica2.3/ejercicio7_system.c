#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv){


	if (argc != 2) {
   	   printf("Usage: %s \"<command and options>\"\n",argv[0]);
   	   return -1;
      	}
	pid_t pid = fork();

	if(pid==-1)
	{ 
		perror("Error al hacer fork");
		exit(1);
	}
	else if(pid==0)
	{
		//hijo
		system(argv[1]);
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

