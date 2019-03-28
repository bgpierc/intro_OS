#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>


#define STEPS 1500
#define STEP_SIZE 0.001

double shubert(double x1, double x2);
int main(int argc, char *argv[]){
  if (argc <1){
    printf("Need thread number arg");
    return -1;
  }
  int MAX_THREADS = atoi(argv[1]);
  int tid = 0;
  double min;
  double x1,x2;
  double y;
  int i;
  double local[MAX_THREADS];

  omp_set_num_threads(MAX_THREADS);

  struct timeval start_time, stop_time, elapsed_time;  // timers
  gettimeofday(&start_time,NULL); // Unix timer

  #pragma omp parallel for private(tid)
    for (i = 0; i <= STEPS; i++) {
      tid = omp_get_thread_num();
      x1 = (STEP_SIZE * i) - 2;
      for (x2 = -2; x2 <= 2; x2 += 0.001) { // x2 parameter of Shubert function
        y = shubert(x1, x2); // Evaluate Shubert function defined below
        if (y < local[tid]) // Check for global minimum
          local[tid] = y;
      }
    }
    int j;
    min = local[0];
    for (j = 0; j < 4; j++){
      if (local[j] < min){
        min = local[j];
      }

    }
  printf("Threads: %d ",MAX_THREADS);
  printf("Minimum: %0.2f ",min);
  gettimeofday(&stop_time,NULL);
  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
  printf("Total time was %0.2f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
}

double shubert(double x1, double x2) {
	double sum1 = 0;
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((i + 1) * x1 + i);
		sum2 += i * cos((i + 1) * x2 + i);
	}
	return sum1 * sum2;
}
