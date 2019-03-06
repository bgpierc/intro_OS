// Chris Fietkiewicz. OpenMP example that demonstrates "for" loop clause
#include <stdio.h>
#include <omp.h> 

int main () { 
  int nthreads, tid; 
  /* Fork a team of threads with each thread having a private tid variable */ 
  int i;
  #pragma omp parallel for private(tid) 
  for (i = 1; i <= 10; i++) {
    /* Obtain and print thread id */ 
    tid = omp_get_thread_num(); 
    printf("Thread #%d, i = %d\n", tid, i); 
    /* Only master thread does this */ 
    if (i == 1) 
    { 
      nthreads = omp_get_num_threads(); 
      printf("Number of threads = %d\n", nthreads); 
    } 
  } /* All threads join master thread and terminate */ 
  return 0;
} 
