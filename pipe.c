#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "rdtsc.h"
#include <netdb.h> 

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
    int numPackets=atoi(argv[2]);
    char buf[STRINGSIZE],iter=0;
    unsigned long latency[numPackets];
    int readpipe[2];
    int writepipe[2];
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

    if(pid==0)
    { 
            //CHILD PROCESS
            close(readpipe[0]);
            close(writepipe[1]);
            memset( buf, 'a', sizeof(char)*STRINGSIZE );
            buf[STRINGSIZE-1]='\0';
            int num = 0;
            while(num<numPackets)
            {
                clock_gettime(CLOCK_MONOTONIC, &start);
                //begin = rdtsc();
                if(write(readpipe[1],buf,strlen(buf)+1) < 0)
                {
                    printf("Child can't write\n");
                }        
                if(read(writepipe[0],buf,sizeof(buf)) < 0)
                {
                    printf("Parent can't read\n");
                }
                //printf("CHILD BUFFER: %s\n",buf);
                //end = rdtsc();

                  //diff = (end-begin);
                clock_gettime(CLOCK_MONOTONIC, &stop);
                remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
                //printf("%d %llu\n",iter,(long long unsigned int)remainderDelay);
                rAverage+=remainderDelay;
                latency[iter] = remainderDelay/2.0;
                //  latency[iter] = ((double) diff / frequency)*1000000.0/2.0;
                iter++;
                num++;
            }
            //printf("Number %d\n",num);
            //printf("Child: Received string: %s\n", buf);
            //printf("Latency Average = %llu nanoseconds\n", (long long unsigned int) ((rAverage*1.0)/2.0)/(numPackets));
            //printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(2*numPackets*STRINGSIZE*1.0)/(rAverage*1.0));
            /*printf("\nSet of latencies");
            for(j=0;j<iter;j++)
                printf("\n%d %llu",j,latency[j]);*/
            long median = sort(latency,iter);
            double micro = median/(float)1000.0;
            //printf("\nMed %llu, %lf\n",median,micro);
            printf("\n%d %lf",STRINGSIZE,micro);
            exit(0); 
    }
    else
    { 
            //PARENT PROCESS
            close(readpipe[1]);
            close(writepipe[0]);
            int num = 0;
            while(num<numPackets)
            {
                if(read(readpipe[0],buf,sizeof(buf)) < 0)
                {
                    printf("Parent can't read\n");
                }

                //printf("%d PARENT BUFFER: %s\n",num,buf);

                if(write(writepipe[1],buf,strlen(buf)+1) < 0)
                {
                    printf("Parent can't write\n");
                }
                num++;
            }
            //printf("Number %d\n",num);
    }
    close(readpipe[1]);
    close(writepipe[0]);
    close(readpipe[0]);
    close(writepipe[1]);
    return 0;
}