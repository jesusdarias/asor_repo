#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <time.h>




int main(int argc, char **argv)
{

	if(argc!=3)
	{
		printf("Usage: %s <address> <port>\n", argv[0]);
		return -1;
	}
	
	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;	
	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
	
	if(rc!=0)
	{
		perror("Error getaddrinfo()");
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,0);


	if(sd==-1)
	{
		perror("Error socket()");
		return -1;
	}
	
	rc = bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

	if(rc==-1)
	{
		perror("Error bind()");
		return -1;
	}
	
	freeaddrinfo(res);

	while(1){		
		char buf[80];
		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof(struct sockaddr_storage);
		int bytes = recvfrom(sd, buf, 80, 0, (struct sockaddr *) &addr, &addrlen);
		if(bytes==-1)
		{
			perror("Error recvfrom()");
			return -1;
		}
		buf[bytes] = '\0';
		
		
		char host[NI_MAXHOST], serv[NI_MAXSERV];
		rc = getnameinfo((struct sockaddr *)&addr,
			addrlen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST);
		if(rc==-1)
		{
			perror("Error getnameinfo()");
			return -1;
		}

		printf("%d bytes de %s:%s\n", bytes,host,serv);
		
		if(strcmp(buf,"t\n")==0)
		{
			
			
			struct tm *lt;
			time_t t;
			time(&t);
			lt = localtime(&t);

			if(lt==NULL)
			{
				perror("Error localtime()");
				return -1;
			}

	
		   	char cadena[100];

			strftime(cadena,100,"%H:%M:%S\n", lt);
		   	sendto(sd, cadena, strlen(cadena)+1, 0,
                     (struct sockaddr *) &addr, addrlen);

		}
		else if(strcmp(buf,"d\n")==0)
		{
		
			struct tm *lt;
			time_t t;
			time(&t);
			lt = localtime(&t);

			if(lt==NULL)
			{
				perror("Error localtime()");
				return -1;
			}

	
		   	char cadena[100];

			strftime(cadena,100,"%d/%m/%y\n", lt);
		   	sendto(sd, cadena, strlen(cadena)+1, 0,
                     (struct sockaddr *) &addr, addrlen);
		}	
		else if(strcmp(buf,"q\n")==0)
		{
			printf("Saliendo...\n");
				close(sd);
				return 0;
		}
		else
		{
			buf[bytes-1]='\0';
			printf("Comando %s no soportado.\n",buf);
		}
	
	}

	return 0;
}
