#include <stdio.h>
#include <sched.h>

int main(int argc, char **argv){

	
	int scheduler = sched_getscheduler(0);
	
	if(scheduler==-1)
	{
		perror("Error al obtener el scheduler");
		return -1;
	}

	if(scheduler==SCHED_OTHER)
		printf("Política estándar: SCHED_OTHER\n");
	else if(scheduler==SCHED_FIFO)
		printf("Política FIFO\n");
	else if(scheduler==SCHED_RR)
		printf("Política Round Robin\n");
	else
		printf("Otra política\n");

	struct sched_param s_param;
	
	int rc = sched_getparam(0, &s_param);

	if(rc==-1)
	{
		perror("Error al obtener parámetros");
		return -1;
	}

	printf("Current priority: %d\n", s_param.sched_priority);
	printf("Max priority: %d\nMin priority: %d\n", sched_get_priority_max(scheduler), 		sched_get_priority_min(scheduler));
	
	return 0;

	
}
