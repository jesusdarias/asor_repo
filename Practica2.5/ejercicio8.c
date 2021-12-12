#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 4

int process(int clisd,struct sockaddr_storage *addr,socklen_t addrlen);
int main(int argc, char**argv)
{

	if(argc!=3)
	{
		printf("Usage: %s <direccion> <puerto>\n",argv[0]);
		return -1;
	}

	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;

	int rc = getaddrinfo(argv[1],argv[2],&hints,&res);

	if(rc==-1)
	{
		perror("Error getaddrinfo()");
		return -1;
	}

	int sd = socket(res->ai_family,res->ai_socktype,0);
	if(sd==-1)
	{
		perror("Error socket()");
		return -1;
	}

	rc = bind(sd,res->ai_addr,res->ai_addrlen);
	if(rc==-1)
	{
		perror("Error bind()");
		return -1;
	}

	freeaddrinfo(res);

	rc = listen(sd,5);
	if(rc==-1)
	{
		perror("Error listen()");
		return -1;
	}

	int i;

	for(i=0; i<N; i++)
	{

		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof(addr);

		int clisd = accept(sd,(struct sockaddr *)&addr,&addrlen);
		if(clisd==-1)
		{
			perror("Error accept()");
			return -1;
		}

		pid_t pid = fork();

		if(pid==-1)
		{
			perror("Error fork()");
			return -1;
		}
		else if(pid==0)
		{
			//HIJO
			rc = process(clisd, &addr,addrlen);
			return rc;
		}
		else
		{
			close(clisd);
		}



	}
	while(wait(NULL)>0); 
	return 0;
}

int process(int clisd,struct sockaddr_storage *addr,socklen_t addrlen)
{
		
		char host[NI_MAXHOST],serv[NI_MAXSERV];
		int rc = getnameinfo((struct sockaddr *)addr, addrlen, host, NI_MAXHOST
		, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
		if(rc==-1)
		{
			perror("Error getnameinfo()");
			return -1;
		}
		printf("SERV PID: %d -> Conexión desde %s:%s\n", getpid(),host,serv);
		char buf[80];
		
		int bytes = recv(clisd,buf,sizeof(buf),0);
		if(bytes==-1)
		{
			perror("Error recv()");
			return -1;
		}
		
		while(bytes > 0)
		{
			buf[bytes]='\0';			
			int sent = send(clisd,buf,bytes,0);
			if(sent==-1)
			{
				perror("Error send()");
				return -1;
			}

			bytes = recv(clisd,buf,sizeof(buf),0);
			if(bytes==-1)
			{
				perror("Error recv()");
				return -1;
			}
		}

		printf("Conexión terminada. SERV PID: %d\n", getpid());
		close(clisd);


	return 0;
}
