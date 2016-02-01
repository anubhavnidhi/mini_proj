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

    int i, iterations = 10000;
    double diff;
    clock_gettime(CLOCK_MONOTONIC, &start);
	for (i = 0; i < iterations; i++)
    {
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
	remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
	diff = (double)remainderDelay / 1000000000.0;
	printf("Latency Average = %lf seconds\n", diff);
	
    return 0;
}