#include <stdlib.h>
#include<stdio.h>
#include <signal.h>

volatile int INT = 0,TSTP=0;

void handler(int signal){
    if(signal==SIGINT) 
	INT++;
    if(signal==SIGTSTP) 
	TSTP++;
}

int main(int argc,char **argv) {
    struct sigaction sa;

    sa.sa_handler=handler;
    sa.sa_flags = SA_RESTART;

    sigaction(SIGINT,&sa,NULL);
    sigaction(SIGTSTP,&sa,NULL);

    sigset_t set;
    sigemptyset(&set);
    while(INT + TSTP < 10)
	sigsuspend(&set);

    printf("INT :%d\n",INT);
    printf("TSTP :%d\n",TSTP);
    return 0;
}
