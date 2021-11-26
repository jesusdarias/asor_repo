#include <stdlib.h>
#include<stdio.h>
#include <signal.h>
#include <unistd.h>
volatile int INT = 0,TSTP=0;

void continuar(int signal){
  return;
}
int main(int argc,char **argv) {

    if (argc != 2) {
   	   printf("Usage: %s <seconds>\n", argv[0]);
   	   return -1;
      }
    struct sigaction sa;
    struct sigaction sa1;

    sa.sa_handler=continuar;
    sa.sa_flags = SA_RESTART;
    sa1.sa_handler=SIG_DFL;
    sa1.sa_flags = SA_RESTART;

    sigaction(SIGALRM,&sa,NULL);
    sigaction(SIGUSR1,&sa1,NULL);

    sigset_t set;
    sigfillset(&set);
    sigdelset(&set,SIGALRM);
    sigdelset(&set,SIGUSR1);

    alarm(atoi(argv[1]));
    sigsuspend(&set);

    printf("Se ha borrado el fichero.\n");
    unlink(argv[0]);
    
    return 0;
}
