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

double shubert(double x1, double x2);
void *evaul_shubert();
void *evaul_shubert_2();
double min1,min2;

int main(){
  pthread_t tid1,tid2; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */

  /* get the default attributes */
	pthread_attr_init(&attr);

  //timing
  struct timeval start_time, stop_time, elapsed_time;  // timers
  gettimeofday(&start_time,NULL); // Unix timer

  /* create the thread */
  double args1[] = {-2,-2,0,0,1};
  double args2[] = {0,0,2,2,2};
	pthread_create(&tid1,&attr,evaul_shubert,args1);
  pthread_create(&tid2,&attr,evaul_shubert,args2);

	/* now wait for the thread to exit */
	pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  gettimeofday(&stop_time,NULL);
  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
  printf("Min1 = %0.2f Min2 = %0.2f \n",min1,min2);
  double global_min;
  if(min1 <= min2){global_min = min1;}
  else{global_min = min2;}
  printf("The minimum is: %0.2f\n",global_min);
  printf("Total time was %0.2f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

}




void *evaul_shubert(double param[]){
  double start1 = param[0];
  double start2 = param[1];
  double end1 = param[2];
  double end2 = param[3];
  int thread_num = (int)param[4];
  //printf("%d",thread_num);
  double x1,x2;
  double y;
  double min =0;
  for (x1 = start1; x1 <= end1; x1 += 0.0005) { // x1 parameter of Shubert function
    for (x2 = start2; x2 <= end2; x2 += 0.0005) { // x2 parameter of Shubert function
      y = shubert(x1, x2); // Evaluate Shubert function defined below
      //printf("%.2f ", y); // Print value for demonstration purposes
      if (y < min) // Check for global minimum
        min = y;
    }
  }
  //printf("%.2f",min);
  if (thread_num == 1){ //wanted to pass pointer to var but I dont feel like messing with it
    min1 = min;
  }
  else if(thread_num == 2){
    min2 = min;
  }
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
