// Chris Fietkiewicz
// Uses http://man7.org/linux/man-pages/man3/sem_getvalue.3.html
// One thread is blocked while another thread shows the negative semaphore value.
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>  

sem_t mutex; // Global semaphore
void *child(); // For child thread

int main(int argc, char *argv[]) {
	// Initialize semaphore to 1
	if(sem_init(&mutex, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}

	printf("Start...\n");
	pthread_t tid; /* the thread identifier */
	pthread_create(&tid, NULL, child, NULL); // Launch child
	sleep(1);
	printf("Decrement...\n");
	sem_wait(&mutex);
	sleep(2);
	printf("Decrement...\n");
	sem_wait(&mutex);
	pthread_join(tid, NULL);
} 

// For child thread
void *child() {
	int value;
	sem_getvalue(&mutex, &value);
	printf("mutex = %d\n", value);
	sleep(2);
	sem_getvalue(&mutex, &value);
	printf("mutex = %d\n", value);
	sleep(2);
	sem_getvalue(&mutex, &value);
	printf("mutex = %d\n", value);
	sleep(2);
	printf("Increment...\n");
	sem_post(&mutex);
	sem_getvalue(&mutex, &value);
	printf("mutex = %d\n", value);
}
