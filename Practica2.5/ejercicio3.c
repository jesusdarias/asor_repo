#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


int main(int argc, char ** argv)
{
	if(argc!=4)
	{
		printf("Usage: %s <direccion host> <puerto> <comando>\n",argv[0]);
		return -1;
	}

	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;
	int rc = getaddrinfo(argv[1],argv[2],&hints,&res);

	if(rc==-1)
	{
		perror("Error getaddrinfo()");
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,
                            0);
	if(sd==-1)
	{
		perror("Error socket()");
		return -1;	
	}

	rc = connect(sd, res->ai_addr, res->ai_addrlen);

	if(rc==-1)
	{
		perror("Error connect()");
		return -1;
	}

	
	char command[2];
	command[0] = argv[3][0];
	command[1]= '\n';
	rc = sendto(sd, command, 2, 0,
                      res->ai_addr, res->ai_addrlen);
	if(rc==-1)
	{
		perror("Error sendto()");
		return -1;
	}
	
	char buf[100];
	struct sockaddr_storage addr;
	socklen_t addr_len = sizeof(addr);
	int bytes = recvfrom(sd,buf,100,0,(struct sockaddr *)&addr, &addr_len);
	buf[bytes]='\0';
	printf("%s",buf);

	freeaddrinfo(res);
	return 0;

}
