#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>
#include <sys/time.h>
#define PORT 8000
double shubert(double x1, double x2);
double evaul_shubert(double x1,double x2,double end1, double end2);
double buff[20];
int main(){
  struct timeval start_time, stop_time, elapsed_time;  // timers
  gettimeofday(&start_time,NULL); // Unix timer
  int  sd, client_sock , c , read_size;
	struct sockaddr_in server , client;
  server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8000 );
	char client_message[2000];
	sd = socket(AF_INET , SOCK_STREAM , 0);
	if (sd == -1){
		printf("Socket failed");
	}
	puts("Socket created");
	if( bind(sd,(struct sockaddr *)&server , sizeof(server)) < 0){
		perror("Bind wrong");
		return -1;
	}
	listen(sd , 5);
	puts("waiting for client...");
	c = sizeof(struct sockaddr_in);
	client_sock = accept(sd, (struct sockaddr *)&client, (socklen_t*)&c);
  char *message = "Start";
  write(client_sock,message,strlen(message)+1);
  double min = evaul_shubert(-2,-2,0,0);
  double result[1];
  recv(client_sock,result, 2000 , 0);
  printf("Server Result: %0.2f \nClient Result: %0.2f\n",min,result[0]);
  double global_min;
  if(min <= result[0]){global_min = min;}
  else{global_min = result[0];}
  printf("Global min: %0.2f\n",global_min);
  gettimeofday(&stop_time,NULL);
  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
  printf("Total time was %0.2f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
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
