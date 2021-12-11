#include <stdio.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/types.h>


int main(int argc, char **argv)
{

	if(argc!=2)
	{
		printf("Usage: %s <hostname or address>\n", argv[0]);
		return -1;
	}

	struct addrinfo *res, *rp;
	
	int rc = getaddrinfo(argv[1], NULL, NULL, &res);

	if(rc!=0)
	{
		perror("Error getaddrinfo()");
		return -1;
	}

	for (rp = res; rp != NULL; rp = rp->ai_next) 
	{
		char host[NI_MAXHOST];
		rc = getnameinfo(rp->ai_addr,rp->ai_addrlen,host,NI_MAXHOST
				,NULL,0,NI_NUMERICHOST);

		if(rc!=0)
		{
			perror("Error getnameinfo()");
			return -1;
		}
		
		printf("%s\t%d\t%d\n", host,rp->ai_family, rp->ai_socktype);         
		      
	}

	freeaddrinfo(res);
	

	return 0;
}
