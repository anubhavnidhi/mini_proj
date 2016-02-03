#include <stdio.h>
#include "rdtsc.h"

static long sec_to_nsec = 1000000000;

int main(int argc, char* argv[])
{
  int i,iterations = atoi(argv[1]);
  unsigned long long begin,end,diff;
  unsigned long long frequency = 2128047;
  double time_in_seconds;
  double sum = 0;
  begin = rdtsc();
  for (i = 0; i < iterations; i++)
    {
      sum += i;
    }
  
  //sleep(1);
  end = rdtsc();

  diff = (end-begin);

  //printf("CLOCK %llu\n", diff);
  //time_in_seconds = ((double) diff / frequency);
  time_in_seconds = ((double) diff / frequency)*1000000.0;// * sec_to_nsec;// * sec_to_nsec;
  printf("rdtsc %lf\n", time_in_seconds);

  return 0;
}