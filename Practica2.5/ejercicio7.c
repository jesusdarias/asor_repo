#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char** argv)
{

	if(argc!=3)
	{
		printf("Usage: %s <dir. host> <puerto>\n",argv[0]);
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

	rc = connect(sd,res->ai_addr,res->ai_addrlen);
	
	if(rc==-1)
	{
		perror("Error connect()");
		return -1;
	}

	freeaddrinfo(res);
	char buf[80];
	memset(buf,0,sizeof(buf));

	while(1)
	{	
		
		int bytes = read(0,buf,sizeof(buf));
		if(bytes==-1)
		{
			perror("Error read()");
			return -1;
		}
		buf[bytes]= '\0';
		
		if(strcmp(buf,"Q\n")==0)
			break;		//sale del bucle

		rc = send(sd,buf,bytes,0);
		if(rc==-1)
		{
			perror("Error send()");
			return -1;
		}

		bytes = recv(sd,buf,sizeof(buf),0);
		if(bytes==-1)
		{
			perror("Error recv()");
			return -1;
		}
		buf[bytes]='\0';
		printf("%s",buf);
		

	}
	
	close(sd);
	
	
	return 0;
}
