#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/tcp.h>
#include "rdtsc.h"
#define PORTNUM 9000
//#define STRINGSIZE 64

//Timer variables
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
  
    int sockfd, portno, n,j;
    pid_t pid;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3)
    {
        printf("Error : run code as ./socket <size> <num-iterations>\n");
        return -1;
    }
    unsigned long STRINGSIZE = atoi(argv[1]);
    int numPackets=atoi(argv[2]);
    unsigned long latency[numPackets];
    int iter = 0;
    char buffer[STRINGSIZE];
    int ser_sock;
    struct sockaddr_in self;
    char buf[STRINGSIZE];
    
    portno = PORTNUM;
    pid=fork();
    if(pid==-1)
    {
        printf("pid:main");
        exit(1);
    }

    if(pid==0)
    { 
        //CHILD
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
            perror("ERROR opening socket");
        server = gethostbyname("localhost");
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
             (char *)&serv_addr.sin_addr.s_addr,
             server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
            perror("ERROR connecting");


        memset( buffer, 'a', sizeof(char)*STRINGSIZE );
        buffer[STRINGSIZE-1]='\0';
        for(j=1; j<=numPackets; j++){
            clock_gettime(CLOCK_MONOTONIC, &start);
            //begin = rdtsc();

            n = send(sockfd,buffer,sizeof(buffer),0);
            if (n < 0) 
                 perror("ERROR writing to socket");
            //bzero(buffer,STRINGSIZE);
            n = recv(sockfd,buffer,sizeof(buffer),0);
            //printf("CHILD BUFFER: %s\n",buffer);
            if (n < 0) 
                 perror("ERROR reading from socket");
            //end = rdtsc();

            //diff = (end-begin);
            //printf("Read done\n");
            clock_gettime(CLOCK_MONOTONIC, &stop);
            remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
            rAverage+=remainderDelay;
            latency[iter] = remainderDelay/2.0;
            //latency[iter] = ((double) diff / frequency)*1000000.0/2.0;
            //printf("%d %llu\n",iter,(long long unsigned int)remainderDelay);
            iter++;
            if (n < 0) 
                 perror("ERROR reading from socket");
            //printf("Data: %s\n",buffer);
        }
        //printf("Latency Average = %llu nanoseconds\n", (long long unsigned int) ((rAverage*1.0)/2.0)/(numPackets));
        //printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(2*numPackets*STRINGSIZE*1.0)/(rAverage*1.0)); 
        /*printf("\nSet of latencies");
        for(j=0;j<iter;j++)
            printf("\n%d %llu",j,latency[j]);*/
        unsigned long median = sort(latency,iter);
        double micro = median/(float)1000.0;
        //printf("\nMed %llu, %lf\n",median,micro);
        printf("\n%d %lf",STRINGSIZE,micro);
        close(sockfd);
        exit(0);
    }
    else
    {
       /*---Create streaming socket---*/
        if ( (ser_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        {
            perror("Socket");
            exit(errno);
        }
        int yes=1;
        /*IPPROTO_TCP,TCP_NODELAY instead of SO_REUSEADDR*/
        if (setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        /*---Initialize address/port structure---*/
        bzero(&self, sizeof(self));
        self.sin_family = AF_INET;
        self.sin_port = htons(PORTNUM);
        self.sin_addr.s_addr = inet_addr("127.0.0.1");

        /*---Assign a port number to the socket---*/
        if ( bind(ser_sock, (struct sockaddr*)&self, sizeof(self)) != 0 )
        {
            perror("socket--bind");
            exit(errno);
        }

        /*---Make it a "listening socket"---*/
        if ( listen(ser_sock, 20) != 0 )
        {
            perror("socket--listen");
            exit(errno);
        }

        int clientfd;
        struct sockaddr_in client_addr;
        int addrlen=sizeof(client_addr);

        /*---accept a connection (creating a data pipe)---*/
        //printf("\nWaiting to accept\n");
        clientfd = accept(ser_sock, (struct sockaddr*)&client_addr, &addrlen);
        //printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        /*---Echo back anything sent---*/
        int num = 0;
        while(num<numPackets){
            recv(clientfd, buf, sizeof(buf), 0);
            //printf("%d PARENT BUFFER: %s\n",num,buf);
            send(clientfd, buf, sizeof(buf), 0);
            //printf("%s\n",buf);
            num++;
        }
        //printf("\nNumber %d",num);
        /*---Close data connection---*/
        close(clientfd);
    
        /*---Clean up (should never get here!)---*/
        close(ser_sock);
     
    }

    return 0;
}