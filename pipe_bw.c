#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "rdtsc.h"
#include <netdb.h> 
#include <float.h>

//#define STRINGSIZE 64

uint64_t remainderDelay;//in nano seconds
struct timespec start, stop;
uint64_t rAverage; 

long sort(long* number, int n)
{

    int temp=0,j,i;
    for(i=1;i<n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(number[j] >number[j+1])
            {
                temp=number[j];
                number[j]=number[j+1];
                number[j+1]=temp;
            }
        }
    }
    //for(i=0;i<n;i++)
    //    printf("%llu\n",number[i]);
    
    return number[0]; 

}

int main(int argc, char *argv[])
{
    //unsigned long long begin,end,diff;
    //unsigned long long frequency = 2128047;
  
    pid_t pid;
    int a,b,j;
    /* Hope this is big enough. */
    if (argc < 3)
    {
        printf("Error : run code as ./client <size> <num-iterations>\n");
        return -1;
    }
    unsigned long STRINGSIZE = atoi(argv[1]);
    int numPackets=1000;
    int iterations=atoi(argv[2]);
    printf("iter: %d\n",iterations);
    char buf[STRINGSIZE];
    char s[1]="a";
    unsigned long bw[iterations];
    double min = DBL_MAX;
    int readpipe[2];
    int writepipe[2];
    int iter=0;
    a=pipe(readpipe);
    b=pipe(writepipe);
    if (a == -1) { perror("pipe"); exit(EXIT_FAILURE); }
    if (b == -1) { perror("pipe"); exit(EXIT_FAILURE); }

    fflush(stdin);
    pid=fork();
    if(pid==-1)
    {
        printf("pid:main");
        exit(1);
    }
    while(iter<iterations)
    {
    
        if(pid==0)
        { 
                //printf("\nCHILD PROCESS");
                close(readpipe[0]);
                close(writepipe[1]);
                memset( buf, 'a', sizeof(char)*STRINGSIZE );
                buf[STRINGSIZE-1]='\0';
            
                int num = 0;
                clock_gettime(CLOCK_MONOTONIC, &start);
                    
                while(num<numPackets)
                {
                    if(write(readpipe[1],buf,strlen(buf)+1) < 0)
                    {
                        printf("Child can't write\n");
                    }
                    //printf("CHILD %d\n",num);           
                    num++;
                }
                if(read(writepipe[0],s,sizeof(s)) < 0)
                    {
                        printf("Parent can't read\n");
                    }
                  //  printf("CHILD READ\n");
                clock_gettime(CLOCK_MONOTONIC, &stop);
                remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
                //printf("%llu delay %d\n",remainderDelay,numPackets);
                double micro = (remainderDelay/2000.0);
                double bw = STRINGSIZE*numPackets/micro;
                //printf("\nBW : %lf",bw);
                if (bw<min)
                    min = bw;
               
                //exit(0); 
        }
        else
        { 
                //printf("\nPAR PROCESS");
                close(readpipe[1]);
                close(writepipe[0]);
                int num = 0;
                while(num<numPackets)
                {
                    if(read(readpipe[0],buf,sizeof(buf)) < 0)
                    {
                        printf("Parent can't read\n");
                    } 
                    //printf("PAR %d: %s\n",num,buf); 
                    num++;
                }
                if(write(writepipe[1],s,strlen(s)+1) < 0)
                {
                    printf("Parent can't write\n");
                }
                //exit(0);
         
        }
        iter++;
    }
    
    if(min != DBL_MAX)
   	 printf("\n%d %lf\n",STRINGSIZE,min);
    
    close(readpipe[1]);
    close(writepipe[0]);
    close(readpipe[0]);
    close(writepipe[1]);
    return 0;
}
