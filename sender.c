#include <stdio.h>
#include "udp.h"
#include <time.h>



char recvBuff[UDP_PKT_SIZE];
char string_val[STRINGSIZE]="This is a test string";
int i;


//Timer variables
uint64_t remainderDelay;//in nano seconds
struct timespec start, stop;

uint64_t rAverage; 

void sendString(){

	
	struct sockaddr_in addr;//structure to store address of incoming socket(from server in this case)

	//Always running on local so for now get local hostname
	char *hostname[1024];
	gethostname((char*)hostname,1024);
	
	//open a socket on an OS selected unused port
	int sd=UDP_Open(0);
	assert(sd > -1);

	int rc=UDP_FillSockAddr(&addr, (char*)hostname, PORTNUM);
	assert(rc==0);

	char * buffer1 = malloc(sizeof(string_val));
	strcpy(buffer1, string_val);
	char *buffer;
	buffer=buffer1;

	/*** Send Msg and Wait for ACK ***/
	clock_gettime(CLOCK_MONOTONIC, &start);
	do{
		//Send message to server	
		rc = UDP_Write(sd, &addr, buffer, sizeof(string_val));
		assert(rc >= 0);

		//Timeout
		rc=UDP_Read(sd, &addr, recvBuff, sizeof(string_val), TIMEOUT);
		//printf("\nRead %s\n",recvBuff);
		if(rc == -1)
			printf("Missed Packet, retrying\n");
	}while(rc == -1);

	clock_gettime(CLOCK_MONOTONIC, &stop);
	remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
	rAverage+=remainderDelay;
}



void measureBW(char buffer[], int numPackets){


	int j=0;

	struct sockaddr_in addr;//structure to store address of incoming socket(from server in this case)
	
	//Always running on local so for now get local hostname
	char *hostname[1024];
	gethostname((char*)hostname,1024);
	
	//open a socket on an OS selected unused port
	int sd=UDP_Open(0);
	assert(sd > -1);

	int rc=UDP_FillSockAddr(&addr, (char*)hostname, PORTNUM);
	assert(rc==0);


	clock_gettime(CLOCK_MONOTONIC, &start);

	for(j=1; j<=numPackets; j++){

		do{
			//Send message to server	
			rc = UDP_Write(sd, &addr, buffer, UDP_PKT_SIZE);
			assert(rc >= 0);

			//Timeout
			rc=UDP_Read(sd, &addr, recvBuff, UDP_PKT_SIZE, TIMEOUT);
			//printf("\nRead %s\n",recvBuff);
			if(rc == -1)
				printf("Missed Packet %d, retrying\n", j);
		}while(rc == -1);
	
	}
	
	clock_gettime(CLOCK_MONOTONIC, &stop);
	remainderDelay = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;

	rAverage+=remainderDelay;

}


void sendStringA(){
	printf("\n\nSending String\n");
	rAverage=0;
	for(i=1; i<=2; i++)
		sendString();
	
	printf("rAverage = %llu nanoseconds\n", (long long unsigned int) rAverage/(i));
}

void measureBWA(){
	
	char buffer[UDP_PKT_SIZE];
	memset( buffer, 'a', UDP_PKT_SIZE);

	rAverage=0;
	int numPackets=2;
	
	printf("\n\nSending %d UDP_PKT_SIZE pkts for measuring BW\n", numPackets);

	measureBW(buffer, numPackets);
	//The 2*numPackets is because the time is for packets coming back from server as well
	printf("bAverage = %Lf bytes/nanoseconds\n", (long double)(2*numPackets*UDP_PKT_SIZE*1.0)/(rAverage*1.0));
}


int main(int argc, char* argv[]){

	memset( string_val, 'a', sizeof(char)*STRINGSIZE );
	string_val[STRINGSIZE-1]='\0';
	sendStringA();
	measureBWA();
	return 0;

}