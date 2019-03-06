// Chris Fietkiewicz
// Uses http://man7.org/linux/man-pages/man3/sem_getvalue.3.html
#include <stdio.h>
#include <semaphore.h>  

int main(int argc, char *argv[]) {
	// Initialize semaphore to 1
	sem_t mutex;
	if(sem_init(&mutex, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}

	int value;
	sem_getvalue(&mutex, &value);
	printf("start: %d\n", value);
	sem_wait(&mutex); // Wait
	sem_getvalue(&mutex, &value);
	printf("wait: %d\n", value);
	sem_post(&mutex); // Post
	sem_getvalue(&mutex, &value);
	printf("post: %d\n", value);
	sem_post(&mutex); // Post
	sem_getvalue(&mutex, &value);
	printf("post: %d\n", value);
} 
