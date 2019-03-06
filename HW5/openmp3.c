// Chris Fietkiewicz. OpenMP example that does parallel summation.
#include <stdio.h>
#include <omp.h> 
#define MAX_THREADS 8

int main () { 
	int nthreads, tid; 
	int i;
	int sum[MAX_THREADS] = {0, 0, 0, 0, 0, 0, 0, 0}; // All sums
	#pragma omp parallel for private(tid) 
	for (i = 1; i <= 10; i++) {
		/* Obtain and print thread id */ 
		tid = omp_get_thread_num(); 
		printf("Thread #%d, i = %d\n", tid, i); 
		sum[tid] = sum[tid] + i;
		/* Only master thread does this */ 
		if (i == 1) { 
			nthreads = omp_get_num_threads(); 
			printf("Number of threads = %d\n", nthreads); 
		} 
	} /* All threads join master thread and terminate */ 
	if (nthreads > MAX_THREADS)
		printf("ERROR: nthreads exceeds MAX_THREADS\n");
	else {
		int total_sum = 0;
		for (i = 0; i < nthreads; i++) {
			printf("Sum #%d = %d\n", i, sum[i]);
			total_sum = total_sum + sum[i];
		}
		printf("Total sum = %d\n", total_sum);
	}
	return 0;
} 
