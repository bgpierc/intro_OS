// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
// Demonstrates process and thread IDs

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // For getpid()

void *child(); /* the thread */

int main(int argc, char *argv[]) {
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	printf("Parent thread has PID %d.\n", getpid());
	pthread_create(&tid, &attr, child, NULL);
	printf("Parent created %ld.\n", tid);
	pthread_join(tid,NULL);
	fflush(stdout);
}

// Do busy work in child thread
void *child() {
	long long tid = (long long) pthread_self();
	printf("Child thread ID is %lld, child process ID is %d, and my parent ID is %d.\n", tid, getpid(), getppid());
	fflush(stdout);
	int i, j, N = 10000000;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
		}
	}
	pthread_exit(0);
}
