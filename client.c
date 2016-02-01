#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PORTNUM 9000
//#define STRINGSIZE 64

//Timer variables
uint64_t remainderDelay;//in nano seconds
struct timespec start, stop;

uint64_t rAverage; 


int main(int argc, char *argv[])
{
    int sockfd, portno, n,j;

    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3)
    {
        printf("Error : run code as ./client <size> <num-iterations>\n");
        return -1;
    }
    int STRINGSIZE = atoi(argv[1]);
    char buffer[STRINGSIZE];
    int numPackets=atoi(argv[2]);

    portno = PORTNUM;
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
	    n = write(sockfd,buffer,strlen(buffer));
	    if (n < 0) 
	         perror("ERROR writing to socket");
	    bzero(buffer,STRINGSIZE);
	    n = read(sockfd,buffer,sizeof(buffer));
        if (n < 0) 
             perror("ERROR reading from socket");
        printf("Read done\n");
	    clock_gettime(CLOCK_MONOTONIC, &stop);
		remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
		rAverage+=remainderDelay;
	    
	    if (n < 0) 
	         perror("ERROR reading from socket");
	    //printf("Data: %s\n",buffer);
	}
	printf("Latency Average = %llu nanoseconds\n", (long long unsigned int) ((rAverage*1.0)/2.0)/(numPackets));
	printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(2*numPackets*STRINGSIZE*1.0)/(rAverage*1.0)); 
    close(sockfd);
    return 0;
}