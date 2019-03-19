/* Chris Fietkiewicz. Demonstrates monitor rules with condition variables.
Based on algorithms from Operating System Concepts by Silberschatz et al.
Does the following steps:
1. Creates 2 threads for "add" function.
   Each thread computes a sum (1-50 or 51-100) and signals a cond. var.
2. Creates 3rd thread for "total" function which waits on "add" threads.
*/
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

// Struct for condition variable
struct condition {
	sem_t sem; // Semaphore to be initialized to 0
	sem_t mutex; // Semaphore to protect changes to count
	int count; // Count of threads waiting
};

/* Global variables are shared by the thread(s) */
int sum; // Global sum
sem_t mutex; // For monitor operations
struct condition add_done; // For communication
// Count of "add" threads that are done
int done_count = 0; 

/* Global vars. for using cond. vars. in monitor */
sem_t next; // Semaphore for monitor entry queue
int next_count = 0; // Counter for monitor entry queue

// Thread functions
void *add(void *start); // Add start to start+49
void *total(); // Computes total for all subranges

// Monitor operations
void monitor_add_to_sum(int i); // Adds i to sum
// Increments count_done and signals total
void monitor_add_done(); 
void monitor_print_sum(); // Prints sum

// Monitor helper functions
void monitor_enter();
void monitor_exit();

// For condition variables
void cwait(struct condition *c); // Semaphore implementation of conditional wait
void cpost(struct condition *c); // Semaphore implementation of conditional signal

int main(int argc, char *argv[]) {
	pthread_t tid_add1, tid_add2, tid_total; // thread identifiers
	sum = 0; // Global sum
	add_done.count = 0;
	sem_init(&mutex, 0, 1);
	sem_init(&(add_done.sem), 0, 0);
	sem_init(&next, 0, 0);
	int start1 = 1;
	pthread_create(&tid_add1, NULL, add, &start1); // Launch add
	int start2 = 51;
	pthread_create(&tid_add2, NULL, add, &start2); // Launch add
	pthread_create(&tid_total, NULL, total, NULL); // Launch total
	// Join and print result
	pthread_join(tid_add1, NULL);
	pthread_join(tid_add2, NULL);
	pthread_join(tid_total, NULL);
	sem_destroy(&mutex);
	sem_destroy(&(add_done.sem));
}

// Semaphore implementation of conditional wait
void cwait(struct condition *c) {
	sem_wait(&mutex);
	c->count++;
	if (next_count > 0)
		sem_post(&next);
	else
		sem_post(&mutex);
	sem_wait(&(c->sem));
	c->count--;
}

// Semaphore implementation of conditional signal
void cpost(struct condition *c) {
	if (c->count > 0) {
		next_count++;
		sem_post(&(c->sem));
		sem_wait(&next);
		next_count--;
	}
}

// Adds subrange of values
void *add(void *start_void) {
	int *start = start_void; // Cast from void to int
	int i;
	for (i = *start; i <= *start + 49; i++)
		monitor_add_to_sum(i);
	monitor_add_done();
	pthread_exit(0);
}

// Print total for all subranges
void *total() {
	monitor_print_sum();
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
	if (done_count < 1)
		cwait(&add_done); // Wait for condition signal
	if (done_count < 2)
		cwait(&add_done); // Wait for condition signal
	printf("sum = %d\n", sum);
	monitor_exit();
}

// Updates done_count and signals total
void monitor_add_done() {
	monitor_enter();
	done_count++;
	cpost(&add_done);
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
