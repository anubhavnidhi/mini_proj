/*
 * Author: Tithy Sahu
 * Contact: tsahu@wisc.edu
 * Date created: 1/29/2016
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <limits.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mainmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t  fill = PTHREAD_COND_INITIALIZER;

int maxBuf;
int threads;
char* file;
int *buffer;
int full = 0;
int use = 0;
int count = 0;

/*
 * Put item into shared buffer
 */
void put(int value) {	
	buffer[full] = value;
	full = (full + 1) % maxBuf;
	count++;
}
/*
 * Get item from shared buffer
 */
int get() {
	use = 0;
	int tmp = buffer[use];
	buffer[use] = INT_MAX; //???
	//use = (use + 1) % maxBuf; //???
	count--;
	return tmp;
}
/*
 * Producer
 */
void producer(void *arg) {
	//int i;
	//for (i = 0; i < maxBuf; i++) {
		printf("Server role: producers: count %d maxBuf %d\n", count, maxBuf);
		pthread_mutex_lock(&mutex); 
		while (count == maxBuf) 
			pthread_cond_wait(&empty, &mutex); 
		pthread_mutex_unlock(&mutex);
		put(* (int *) arg); 
		pthread_mutex_lock(&mutex);
		printf("Producer: Queued request count[%d]: %d \n", count, buffer[full-1]);
		pthread_cond_signal(&fill); 
		pthread_mutex_unlock(&mutex);
	//}
}

/*
 * Consumer
 */
void *consumer(void *arg) {
	while(1){
		printf("Client request = consumer \n");
		pthread_mutex_lock(&mutex); 
		while (count == 0) 
			pthread_cond_wait(&fill, &mutex);
		int rqst = get(); 
		printf("Consumer: Client Request served: %d \n", rqst);
		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex); 
	}
}

/*
 * Get program arguments
 */
void getargs(int *threads, int *maxBuf, char *file, int argc, char *argv[])
{
    if (argc != 4) {
	fprintf(stderr, "Usage: %s <threads> <buffers> <file>\n", argv[0]);
	exit(1);
    }
    *threads = atoi(argv[2]);
    *maxBuf = atoi(argv[3]);
    file = argv[4];
}

/*
 * Driver program
 */
int main(int argc, char *argv[]){

	//Initializations
	int i,fd;
	getargs(&threads, &maxBuf, file, argc, argv);
	printf("threads: %d, max buffer: %d filename: %s\n", threads, maxBuf, file);
    
	//Create child
	int pid = fork();
	if(pid < 0){
		printf("Error creating child \n");
		return -1;
	}

	//Shared memory using mmap
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    	if (fd == -1) {
		perror("Error opening file for writing");
		return -1;
   	}
	int result = write(fd, "", 1);
	if (result != 1) {
		close(fd);
		perror("Error writing to file");
		return -1;
	}
    	// mmap the file
	buffer = mmap(0, maxBuf, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (buffer == MAP_FAILED) {
		close(fd);
		perror("Error mmapping the file");
		return -1;
	}

	//Create some threads...
	pthread_t rqst[threads];
	for(i = 0; i < maxBuf; i++){
		buffer[i] = INT_MAX;
	}
	for(i = 0; i < threads; i++){
		pthread_create(&rqst[i], NULL, consumer, NULL);
	}

	//Parent = Producer
	while (1) {
		pthread_mutex_lock(&mainmutex);
	    	producer((void *) 1); //???
	    	pthread_mutex_unlock(&mainmutex);
	}

	close(fd);
	return 0;
}
