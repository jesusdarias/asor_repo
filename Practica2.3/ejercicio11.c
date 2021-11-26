#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include<stdio.h>

int main(int argc,char **argv) {

	char *secs_str = getenv("SLEEP_SECS"); //debe existir la variable de entorno (definir en la terminal)
	
	int rc;
	sigset_t set;

	
    	rc = sigprocmask(SIG_BLOCK, &set,NULL);
	if(rc==-1)
	{
		perror("Error");
		return -1;
	}
    	rc = sigemptyset(&set);
	if(rc==-1)
	{
		perror("Error");
		return -1;
	}
    	rc = sigaddset(&set, SIGINT);
	if(rc==-1)
	{
		perror("Error");
		return -1;
	}
    	rc = sigaddset(&set, SIGTSTP);
	if(rc==-1)
	{
		perror("Error");
		return -1;
	}

	sleep(atoi(secs_str)); //SLEEP
	
	sigset_t pend_set;
	rc = sigpending(&pend_set);
	
	int flag_int = sigismember(&pend_set,SIGINT);
	if(flag_int==-1)
	{
		perror("Error");
		return -1;
	}

	if(flag_int==1)
		printf("Se ha recibido la señal SIGINT.\n");

	int flag_stop = sigismember(&pend_set,SIGTSTP);
	if(flag_stop==-1)
	{
		perror("Error");
		return -1;
	}

	if(flag_stop==1)
		printf("Se ha recibido la señal SIGTSTP.\n");
	
	sigprocmask(SIG_UNBLOCK, &set, NULL); //aunque no se hayan recibido, no pasa nada.

	printf("Cadena de prueba\n");

	return 0;
		
	
}
