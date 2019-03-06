#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>
#include <sys/time.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

double shubert(double x1, double x2);
double evaul_shubert(double x1,double x2,double end1, double end2);

int main(){
  double write_data[BUFFER_SIZE];
	double read_data[BUFFER_SIZE];
	pid_t pid;
	int fd[2];
  struct timeval start_time, stop_time, elapsed_time;  // timers
  gettimeofday(&start_time,NULL); // Unix timer
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	if (!pid) { //child
    double min = evaul_shubert(-2,-2,0,0);
    write_data[0] = min;
		write(fd[WRITE_END], write_data, sizeof(write_data));
	}
	else { //parent
    double global_min;
    double min = evaul_shubert(0,0,2,2);
    wait(NULL);
    double child_min;
		read(fd[READ_END], read_data, sizeof(read_data)); //read
    child_min = read_data[0];
    printf("Parent Min: %0.2f \nChild Min: %0.2f\n",min,child_min);
    if(min <= child_min){global_min = min;}
    else{global_min = child_min;}
    printf("The minimum is: %0.2f\n",global_min);
    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    printf("Total time was %0.2f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
	}
	return 0;
}

double evaul_shubert(double start1,double start2,double end1, double end2){
  double x1,x2;
  double y;
  double min =0;
  for (x1 = start1; x1 <= end1; x1 += 0.001) { // x1 parameter of Shubert function
    for (x2 = start2; x2 <= end2; x2 += 0.001) { // x2 parameter of Shubert function
      y = shubert(x1, x2); // Evaluate Shubert function defined below
      //printf("%.2f ", y); // Print value for demonstration purposes
      if (y < min) // Check for global minimum
        min = y;
    }
  }
  return min;
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
