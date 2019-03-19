/* Chris Fietkiewicz. Demonstrates monitor rules WITHOUT condition variables.
   Creates 2 threads for "add" function and prints global sum.
*/
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

/* Global variables are shared by threads */
int sum; // Global sum
sem_t mutex; // For monitor operations
/* Global vars. for using cond. vars. in monitor (not used) */
sem_t next; // Semaphore for monitor entry queue
int next_count = 0; // Counter for monitor entry queue

// Thread function
void *add(void *start); // Add start to start+49

// Monitor operations
void monitor_add_to_sum(int i); // Adds i to sum
void monitor_print_sum(); // Prints sum

// Monitor helper functions
void monitor_enter();
void monitor_exit();

int main(int argc, char *argv[]) {
	pthread_t tid_add1, tid_add2; // thread identifiers
	sum = 0; // Global sum
	sem_init(&mutex, 0, 1); // For monitor operations
	sem_init(&next, 0, 0); // For completeness
	int start1 = 1;
	pthread_create(&tid_add1, NULL, add, &start1); // Launch add
	int start2 = 51;
	pthread_create(&tid_add2, NULL, add, &start2); // Launch add
	// Join and print result
	pthread_join(tid_add1, NULL);
	pthread_join(tid_add2, NULL);
	monitor_print_sum();
	// Cleanup
	sem_destroy(&mutex);
}

// Adds subrange of values
void *add(void *start_void) {
	// Cast from void to int
	int *start = start_void; 
	int i;
	for (i = *start; i <= *start + 49; i++)
		monitor_add_to_sum(i);
	pthread_exit(0);
}

////////////////////////
// Monitor operations //
////////////////////////


// Adds i to shared sum
void monitor_add_to_sum(int i) {
	monitor_enter();
	sum += i;
	monitor_exit();
}

// Prints value of shared sum
void monitor_print_sum() {
	monitor_enter();
	printf("sum = %d\n", sum);
	monitor_exit();
}

//////////////////////////////
// Monitor helper functions //
//////////////////////////////

// Prepare to "enter the monitor"
void monitor_enter() {
	sem_wait(&mutex);
}

// Prepare to "exit the monitor"
void monitor_exit() {
	if (next_count > 0)
		sem_post(&next);
	else
		sem_post(&mutex);
}
