#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{

	int p_h[2];
	int h_p[2];
	char buffer[256];
	int num=0;
	
	int rc = pipe(p_h);	
	if(rc==-1)
	{
		perror("Error al hacer pipe p_h");
		return -1;
	}

	rc = pipe(h_p);
	if(rc==-1)
	{
		perror("Error al hacer pipe h_p");
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
			close(p_h[1]);
			close(h_p[0]);
			int fin = 0;
			while(!fin)
			{
				int read_bytes = read(p_h[0],buffer,256);
				buffer[read_bytes]='\0';
				printf("Mensaje: %s\n",buffer);
				num++;	
				sleep(1);			
				if(num==10)
				{	
					write(h_p[1],"q",1);
					fin = 1;
				}				
				else
					write(h_p[1],"l",1);
			}
			
			close(p_h[0]);
			close(h_p[1]);
			exit(0);
			break;	
		default:
		//PADRE
			close(p_h[0]);
			close(h_p[1]);
			int fin2 = 0;
			while(!fin2)
			{
				printf("Escribe mensaje: ");
				scanf("%s", buffer);

				write(p_h[1],buffer,strlen(buffer)+1);
				char respuesta[1];		
				read(h_p[0],respuesta,1);
				if(respuesta[0]=='q')
				{
					fin2 =1;
				}

			}
			

			exit(0);
			break;
	}


	return 0;



}
