#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv)
{

	int tub1 = open("tuberia", O_RDONLY|O_NONBLOCK);

	if(tub1==-1)
	{
		perror("No se ha podido abrir la tubería 1");
		return -1;
	}
	
	int tub2 = open("tuberia2", O_RDONLY|O_NONBLOCK);
	if(tub2==-1)
	{
		perror("No se ha podido abrir la tubería 2");
		return -1;
	}

	fd_set rfds;

    	FD_ZERO(&rfds);
	struct timeval timeout;
    	

	int mayor=tub2;
	char buffer[256];
	int bytes;
	int cambios;

	while(1) {

	FD_SET(tub1, &rfds);
	FD_SET(tub2, &rfds);
	timeout.tv_sec = 1;
    	timeout.tv_usec = 0;
	if(tub1 > tub2)
		mayor = tub1;
    	cambios = select(mayor+1, &rfds, NULL, NULL, &timeout);
	if(cambios==-1)
	{
		perror("Error al hacer select");
		return -1;
	}
	else if(cambios)
	{
		if(FD_ISSET(tub1, &rfds))
		{	
			bytes = read(tub1,buffer,256);
			if(bytes==0)
			{
				//cerrar tuberia y volver a abrir
				close(tub1);
				tub1 = open("tuberia", O_RDONLY|O_NONBLOCK);

				if(tub1==-1)
				{
					perror("No se ha podido abrir la tubería 1");
					return -1;
				}
			}
			else
			{	buffer[bytes]='\0';
				printf("Tubería 1:%s", buffer);
			}
			
		}
		else if(FD_ISSET(tub2, &rfds))
		{
			bytes = read(tub2,buffer,256);
			if(bytes==0)
			{
				//cerrar tuberia y volver a abrir
				close(tub2);
				tub2 = open("tuberia2", O_RDONLY|O_NONBLOCK);

				if(tub2==-1)
				{
					perror("No se ha podido abrir la tubería 2");
					return -1;
				}
				
			}
			else
			{
				buffer[bytes]='\0';
				printf("Tubería 2:%s", buffer);
			}
		}
	}

	}
	

	return 0;
}
