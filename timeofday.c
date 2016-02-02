#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int i, iterations = atoi(argv[1]);

  struct timeval start,stop;  
  
  double diff = 0;
  int sum = 0;
    
  gettimeofday(&start, NULL);  
  
  //double t1=tim.tv_sec+(tim.tv_usec/1000000.0);  
    
  for (i = 0; i<iterations; i++)
    {
        sum += i;
        
    }
   gettimeofday(&stop, NULL);
    diff = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_usec - start.tv_usec;
    printf("timeofday %lf\n",diff/1000000.0);//double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
  //printf("\nStopped at %d",i);
  /*  
  gettimeofday(&tim, NULL);  
  double t2=tim.tv_sec+(tim.tv_usec/1000000.0);  
  
  printf("%.6lf seconds elapsed\n", t2-t1); 
  */
  return 0;
}
