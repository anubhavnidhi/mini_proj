#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include <netdb.h> 

//#define STRINGSIZE 64

uint64_t remainderDelay;//in nano seconds
struct timespec start, stop;
uint64_t rAverage; 

int main(int argc, char *argv[])
{
    pid_t pid;
    int a,b;
    /* Hope this is big enough. */
    if (argc < 3)
    {
        printf("Error : run code as ./client <size> <num-iterations>\n");
        return -1;
    }
    int STRINGSIZE = atoi(argv[1]);
    char buf[STRINGSIZE];
    int numPackets=atoi(argv[2]);
    int readpipe[2];
    int writepipe[2];
    char temp[1] = "a";

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
                if(write(readpipe[1],buf,strlen(buf)+1) < 0)
                {
                    printf("Child can't write\n");
                }        
                if(read(writepipe[0],temp,sizeof(temp)) < 0)
                {
                    printf("Parent can't read\n");
                }
                //printf("CHILD BUFFER: %s\n",temp);
                clock_gettime(CLOCK_MONOTONIC, &stop);
                remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
                rAverage+=remainderDelay;
                num++;
            }
            //printf("Number %d\n",num);
            //printf("Child: Received string: %s\n", buf);
            //printf("Latency Average = %llu nanoseconds\n", (long long unsigned int) ((rAverage*1.0)/2.0)/(numPackets));
            printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(numPackets*STRINGSIZE*1.0)/(rAverage/2.0)); 
            //printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(2*numPackets*STRINGSIZE*1.0)/(rAverage*1.0));

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

                //printf("PARENT BUFFER: %s\n",buf);

                if(write(writepipe[1],temp,sizeof(temp)) < 0)
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