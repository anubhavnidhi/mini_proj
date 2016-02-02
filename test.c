#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rdtsc.h"


int main(int argc, char **argv)
{
  int i, iterations = 10000;

  struct timeval start,stop;  
  
  double diff = 0;
  int sum = 0;
    
  gettimeofday(&start, NULL);  
  
  //double t1=tim.tv_sec+(tim.tv_usec/1000000.0);  
    
  for (i = 0; i<10; i++)
    {
        sum += i;
        //gettimeofday(&stop, NULL);
        //diff = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_usec - start.tv_usec;
        //printf("%lf",diff);//double t2=tim.tv_sec+(tim.tv_usec/1000000.0);

    }
  gettimeofday(&stop, NULL);
  diff = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_usec - start.tv_usec;
  printf("%lf",diff);//double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
//  printf("\nStopped at %d",i);
  /*  
  gettimeofday(&tim, NULL);  
  double t2=tim.tv_sec+(tim.tv_usec/1000000.0);  
  
  printf("%.6lf seconds elapsed\n", t2-t1); 
  */
  return 0;
}
