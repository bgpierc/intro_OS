// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
// Keeps parent thread blocked on wait for while child loops.
// Allows user to monitor statuses using "top"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // For getpid()
#include <semaphore.h>  

sem_t sem; // Global semaphore
void *child(); /* the thread */

int main(int argc, char *argv[]) {
	// Initialize semaphore to 0 so wait will block immediately
	if(sem_init(&sem, 0, 0) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, child, NULL);
	printf("Parent waiting...\n");
	sem_wait(&sem);
	sem_destroy(&sem); // Clean up semaphore
}

// Do busy work in child thread
void *child() {
	int i, j, N = 100000;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
		}
	}
	printf("Child signaling...\n");
	sem_post(&sem);
	pthread_exit(0);
}
