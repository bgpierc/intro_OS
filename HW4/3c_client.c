#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

double shubert(double x1, double x2);
double evaul_shubert(double x1,double x2,double end1, double end2);
int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8000 );
	char message[1000] , server_reply[2000];
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (connect(sock,(struct sockaddr *)&server , sizeof(server)) < 0){
		perror("connect failed. Error");
		return -1;
	}

  if(recv(sock , server_reply , 2000 , 0) < 0){
		puts("Recieve failed");
    return -1;
  }
  else{
    double buf[1];
    buf[0] = evaul_shubert(0,0,2,2);
    send(sock ,buf, sizeof(buf), 0);
  }
	close(sock);
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
