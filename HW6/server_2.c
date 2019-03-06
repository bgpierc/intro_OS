#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


int main(int argc , char *argv[]){
  const char *questions[] = {"What is the number of this course? ","Who is the instructor? ","What is 2+2"};
  const char *anwsers[] = {"338","Chris","4"};
	int  sd, client_sock , c , read_size;
	struct sockaddr_in server , client;
  server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8000);
	char client_message[2000];
	sd = socket(AF_INET , SOCK_STREAM , 0);
	if (sd == -1){
		printf("Socket failed");
    return -1;
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
    int i;
    for (i = 0; i < 3; i++){
		write(client_sock , questions[i], strlen(questions[i])+1);
    recv(client_sock , client_message , 2000 , 0);
    printf("%s",client_message);
    char *response;
    if(strcmp(client_message, anwsers[i]) == 0){
      response = "Correct!";
    }
    else{
      response = "Wrong";
    }
    write(client_sock,response,strlen(response)+1);
    //sleep(3);
  }

	return 0;
}
