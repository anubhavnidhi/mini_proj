 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "udp.h"

#define BUFFSIZE 2048

int sd;//socket descriptor
struct sockaddr_in addr;//structure to store address of incoming socket
char buffer[BUFFSIZE];//2kb buffer size for incoming messages


int main(int argc, char *argv[])
{

	sd=UDP_Open(PORTNUM);
	assert(sd != -1);
	
	//Server listening in loop
	while(1)
	{
		
		
		//read incoming message from port
		/*** Read Incoming Message ***/
		int rc=UDP_Read(sd, &addr, buffer, BUFFSIZE, -1);
		//printf("\nRead %s\n",buffer);
		if(rc>0)
		{
			//char * msg = strdup(buffer);
			//printf("Server recieved:%s\n",msg);
			//sprintf(buffer, "Server got your message: %s\n",msg);

			/*** Message drop probability ***/
			rc = UDP_Write(sd, &addr, buffer, BUFFSIZE);//Send back the response to the client
			if(rc < 0)
				printf("Server UDP_write failed\n");
		}

	}

	return 0;
}