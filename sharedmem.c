/*
 * Author: Tithy Sahu
 * Contact: tsahu@wisc.edu
 * Date created: 1/29/2016
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <limits.h>

#define MAXBUF 1024*1024
int datasz;
int itr;
struct timespec start, stop;

struct shmem {
  sem_t mutex;
  sem_t full;
  sem_t empty;
  sem_t child;
  char buffer[MAXBUF];
} shmem;

/*
 * Get program arguments
 */
void getargs(int *datasz, int *itr, int argc, char *argv[])
{
    if (argc != 3) {
	fprintf(stderr, "Usage: %s <data_size> <iterations> \n", argv[0]);
	exit(1);
    }
    *datasz = atoi(argv[1]);
    *itr = atoi(argv[2]);
}

/*
 * Driver program
 */
int main(int argc, char *argv[]){

	//Initializations
	int i,fd;
	struct shmem *ptr;
	uint64_t rtt, minrtt = UINT32_MAX;
	getargs(&datasz, &itr, argc, argv);
        //printf("%d %d \n", datasz, itr);
	
	//Shared memory using mmap
	fd = open("buf.txt", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0660);
    	if (fd == -1) {
		fprintf(stderr,"Error opening file for writing");
		return -1;
   	}
	write(fd, &shmem, sizeof(struct shmem));
	
    	// mmap the file
	ptr = (struct shmem *) mmap(NULL, sizeof(struct shmem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED) {
		close(fd);
		fprintf(stderr,"Error mmapping the file");
		return -1;
	}
	//initialize semaphores
	if(sem_init(&ptr->mutex, 1, 1) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	if(sem_init(&ptr->empty, 1, 1) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	if(sem_init(&ptr->full, 1, 0) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	if(sem_init(&ptr->child, 1, 0) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	setbuf(stdout, NULL);
	
	char *temp = (char*)malloc(datasz * sizeof(char));
	for(i = 0; i < datasz; i++)
		*((char*)temp+i) = 't';

        for(i = 0; i < itr; i++){	
	int pid = fork();
	if (pid == 0){
		//Child process
		char *tmp = (char *)malloc(datasz * sizeof(char));
		char *ctemp = (char*)malloc(datasz * sizeof(char));
		for(i = 0; i < datasz; i++)
			*((char*)ctemp+i) = 's';

		//read parent's data
		sem_wait(&ptr->full);
		sem_wait(&ptr->mutex);
		memcpy((void*)tmp, (void*)ptr->buffer, datasz);
		//printf("Child: Data read \n"); //%s of data size %d\n", tmp, datasz);
		sem_post(&ptr->mutex);
		sem_post(&ptr->empty);
		
		//write child data
		sem_wait(&ptr->mutex);
		memcpy((void*)ptr->buffer, (void*)ctemp, datasz);
		//printf("Child: Data written %s \n", ctemp);		
	      	sem_post(&ptr->mutex);		
	      	sem_post(&ptr->child);	
		//printf("Child complete...\n");		
	}
	else{
		//Parent process
		clock_gettime(CLOCK_MONOTONIC, &start);	
		//write parent data
		sem_wait(&ptr->empty);
		sem_wait(&ptr->mutex);
		memcpy((void*)ptr->buffer, (void*)temp, datasz);
		//printf("Parent: Data written \n"); //%s of data size %d\n", temp, datasz);
	      	sem_post(&ptr->mutex);
	      	sem_post(&ptr->full);
		
		//read child's data
		char *ptmp = (char *)malloc(datasz * sizeof(char));
		sem_wait(&ptr->child);
		sem_wait(&ptr->mutex);
		memcpy((void*)ptmp, (void*)ptr->buffer, datasz);
		//printf("Parent: Data read %s \n", ptmp);	
		sem_post(&ptr->mutex);
		//printf("Parent complete...\n");

		clock_gettime(CLOCK_MONOTONIC, &stop);
		rtt = 1e9L * (stop.tv_sec - start.tv_sec) + stop.tv_nsec - start.tv_nsec;
		//printf("%dB = %llu us\n", datasz, (long long unsigned int) ((rtt*1.0)/2000.0) );
		if(minrtt > rtt)
			minrtt = rtt;
		
	  }
       }
	if(minrtt != UINT32_MAX)
		printf("%d %lf\n", datasz, (double) (minrtt/2000.0) );
	close(fd);
	//printf("Complete...\n");
	exit(0);
}
