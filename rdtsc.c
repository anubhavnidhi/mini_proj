#include <stdio.h>
#include "rdtsc.h"

static long sec_to_nsec = 1000000000;

int main(int argc, char* argv[])
{
  int i,iterations=10000;
  unsigned long long a,b,diff;
  unsigned long long frequency = 2128047;
  double time_in_seconds;

  a = rdtsc();
  for (i = 0; i < iterations; i++)
    {
    }
  b = rdtsc();

  diff = (b-a);

  //printf("CLOCK %llu\n", diff);

  time_in_seconds = ((double) diff / frequency)*0.001;// * sec_to_nsec;
  printf("Second: %lf\n", time_in_seconds);

  return 0;
}