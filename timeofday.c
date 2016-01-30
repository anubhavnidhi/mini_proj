#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int i, iterations = 10000;

  struct timeval tim;  
  gettimeofday(&tim, NULL);  
  double t1=tim.tv_sec+(tim.tv_usec/1000000.0);  

  for (i = 0; i < iterations; i++)
    {
    }
  
  gettimeofday(&tim, NULL);  
  double t2=tim.tv_sec+(tim.tv_usec/1000000.0);  
  
  printf("%.6lf seconds elapsed\n", t2-t1); 
  
  return 0;
}
