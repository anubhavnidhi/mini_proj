#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define PORTNUM     9000
//#define STRINGSIZE      1024

int main(int argc, char *argv[])
{   int ser_sock,num=0;
    struct sockaddr_in self;
    if (argc < 3)
    {
        printf("Error : run code as ./socket <size> <num-iterations>\n");
        return -1;
    }
    int STRINGSIZE = atoi(argv[1]);
    int numPackets=atoi(argv[2]);
    char buf[STRINGSIZE];
    
    /*---Create streaming socket---*/
    if ( (ser_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("Socket");
        exit(errno);
    }
    int yes=1;
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

    /*---Forever... ---*/
    while (1)
    {   int clientfd;
        struct sockaddr_in client_addr;
        int addrlen=sizeof(client_addr);

        /*---accept a connection (creating a data pipe)---*/
        printf("\nWaiting to accept\n");
        clientfd = accept(ser_sock, (struct sockaddr*)&client_addr, &addrlen);
        //printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        /*---Echo back anything sent---*/
        num = 0;
        while(num<numPackets){
            send(clientfd, buf, recv(clientfd, buf, STRINGSIZE, 0), 0);
            num++;
        }
        printf("\nNumber %d",num);
        /*---Close data connection---*/
        close(clientfd);
    }

    /*---Clean up (should never get here!)---*/
    close(ser_sock);
    return 0;
}
