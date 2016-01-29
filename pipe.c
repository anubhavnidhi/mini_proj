#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include <netdb.h> 

#define STRINGSIZE 64

uint64_t remainderDelay;//in nano seconds
struct timespec start, stop;
uint64_t rAverage; 

int main()
{
    pid_t pid;
    int a,b;
    /* Hope this is big enough. */
    char buf[STRINGSIZE];
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
            clock_gettime(CLOCK_MONOTONIC, &start);
            if(write(readpipe[1],buf,strlen(buf)+1) < 0)
            {
                printf("Child can't write\n");
            }        

            if(read(writepipe[0],buf,sizeof(buf)) < 0)
            {
                printf("Parent can't read\n");
            }
            clock_gettime(CLOCK_MONOTONIC, &stop);
            remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
            rAverage+=remainderDelay;

            //printf("Child: Received string: %s\n", buf);
            printf("Latency Average = %llu nanoseconds\n", (long long unsigned int) ((rAverage*1.0)/2.0));
            printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(2*STRINGSIZE*1.0)/(rAverage*1.0));

            exit(0);
    }
    else
    { 
            //PARENT PROCESS
            close(readpipe[1]);
            close(writepipe[0]);
            if(read(readpipe[0],buf,sizeof(buf)) < 0)
            {
                printf("Parent can't read\n");
            }

            //printf("\nParent: Received string: %s\n",buf);

            if(write(writepipe[1],buf,strlen(buf)+1) < 0)
            {
                printf("Parent can't write\n");
            }

    }
    close(readpipe[1]);
    close(writepipe[0]);
    close(readpipe[0]);
    close(writepipe[1]);
    return 0;
}