#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



int main() {
   
   if(setuid(0)==-1)
   {
	printf("Setuid Error Code %d: %s\n",errno,strerror(errno));
	return 1;
   }
	
   return 0;
}

