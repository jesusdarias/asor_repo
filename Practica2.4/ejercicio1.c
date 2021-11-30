#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

int main(int argc, char** argv)
{

	int fd[2];
	int rc = pipe(fd);
	
	if(rc==-1)
	{
		perror("Error al hacer pipe");
		return -1;
	}

	pid_t pid = fork();
	
	switch(pid)
	{
		case -1:
			perror("Error al hacer fork");
			exit(1);
			break;
		case 0:
		//HIJO
			close(0);
			dup2(fd[0],0);
			close(fd[0]);
			close(fd[1]);
			execlp(argv[3],argv[3],argv[4],NULL);
			break;	
		default:
		//PADRE
			close(1);
			int rc = dup2(fd[1],1);
			if(rc==-1)
			{
				perror("Error al hacer dup2");
				exit(1);
			}
			close(fd[0]);
			close(fd[1]);
			execlp(argv[1],argv[1],argv[2],NULL);
			break;
	}


	return 0;



}
