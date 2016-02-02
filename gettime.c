#include <stdio.h>
#include <sys/types.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Timer variables
uint64_t remainderDelay;//in nano seconds
struct timespec start, stop;
    


int main(int argc, char *argv[])
{

    int i, iterations = atoi(argv[1]);
    double diff = 0;
    int sum = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
	for (i = 0; i<iterations; i++)
    {
        sum += i;
        //clock_gettime(CLOCK_MONOTONIC, &stop);
        //diff = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
    
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
    diff = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
    
    printf("clock_gettime %lf\n",diff/1000000000.0);
    /*
    clock_gettime(CLOCK_MONOTONIC, &stop);
	remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
	diff = (double)remainderDelay / 1000000000.0;
	printf("Latency Average = %lf seconds\n", diff);
	*/
    return 0;
}