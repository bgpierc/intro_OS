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


#define MAX_THREADS 4
double shubert(double x1, double x2);
int main(){
  int tid;
  int i;
  double min;
  struct timeval start_time, stop_time, elapsed_time;  // timers
  gettimeofday(&start_time,NULL); // Unix timer
  omp_set_num_threads(4);
  double x1,x2;
  double y;
  #pragma omp parallel
  {
    for (x1 = -2; x1 <= 2; x1 += 0.001) { // x1 parameter of Shubert function
      for (x2 = -2; x2 <= 2; x2 += 0.001) { // x2 parameter of Shubert function
        y = shubert(x1, x2); // Evaluate Shubert function defined below
        //printf("%.2f ", y); // Print value for demonstration purposes
        #pragma omp critical
        {
        if (y < min) // Check for global minimum
          min = y;
        }
      }
    }
  }

  printf("Minimum: %0.2f\n",min);
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
