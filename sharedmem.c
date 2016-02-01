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
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <limits.h>

#define MAXBUF 4*1024
char *file;

struct shmem {
  sem_t mutex;
  sem_t full;
  sem_t empty;
  char buffer[MAXBUF];
} shmem;


/*
 * Producer
 */
void producer() {
	
}

/*
 * Consumer
 */
void consumer() {
	
}

/*
 * Get program arguments
 */
void getargs(char **file, int argc, char *argv[])
{
    if (argc != 2) {
	fprintf(stderr, "Usage: %s <file>\n", argv[0]);
	exit(1);
    }
    *file = argv[1];
}

/*
 * Driver program
 */
int main(int argc, char *argv[]){

	//Initializations
	int i,fd;
	struct shmem *ptr;
	getargs(&file, argc, argv);
	printf("filename: %s\n", file);
        
	//Shared memory using mmap
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0660);
    	if (fd == -1) {
		fprintf(stderr,"Error opening file for writing");
		return -1;
   	}
	int result = write(fd, &shmem, 1);
	if (result != 1) {
		close(fd);
		fprintf(stderr,"Error writing to file");
		return -1;
	}
    	// mmap the file
	ptr = (struct shmem *) mmap(0, sizeof(struct shmem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED) {
		close(fd);
		fprintf(stderr,"Error mmapping the file");
		return -1;
	}
	//initialize semaphores
	if(sem_init(&ptr->mutex, 1, 1) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	if(sem_init(&ptr->empty, 0, MAXBUF) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	if(sem_init(&ptr->full, 0, 0) != 0 )
		fprintf(stderr,"sem_init error"), exit(-2);
	setbuf(stdout, NULL);
	
	char *temp = (char*)malloc(MAXBUF);
	for(i = 0; i < MAXBUF; i++)
		*((char*)temp+i) = 'A';
	
	if (fork() == 0)
		producer();
	
	//Measure Latency
	//clock_gettime(CLOCK_MONOTONIC, &start);
	consumer();
	//clock_gettime(CLOCK_MONOTONIC, &end);

	printf("Complete...\n");
	munmap(0, MAXBUF);
	close(fd);
	return 0;
}
