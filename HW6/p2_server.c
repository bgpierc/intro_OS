// Chris Fietkiewicz. Solution to Problem #2 (server program).
// Usage: server port
// Example: server 8000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>


#include <fcntl.h> // for open
#include <unistd.h> // for close

// Helper function to conveniently print to stderr AND exit (terminate)
void error(const char *msg) {
    perror(msg);
    exit(1);

}

char buffer[256]; //global buffer
sem_t mutex;

void *thread_1(){

  // Setup phase
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
     error("ERROR opening socket");
  struct sockaddr_in serv_addr; // Server address struct
  bzero((char *) &serv_addr, sizeof(serv_addr));
  int portno = 8000;//screw it //atoi(port); // Port number is commandline argument
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
           sizeof(serv_addr)) < 0)
       error("ERROR on binding");
  printf("Listening for clients\n");
  listen(sockfd, 5);

  // Service phase
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr); // Address struct length
  int newsockfd = accept(sockfd,
                  (struct sockaddr *) &cli_addr,
                  &clilen);
  if (newsockfd < 0)
       error("ERROR on accept");



  char *prompt = "Client 1 : Quit:0 Check Message:1 ";
  char *client_prompt = "Quit:0 Send message:1";
  // Play the game
  int n; // number of bytes that were written/read
  int i;

  sprintf(buffer,"Hello");

  for(;;){
    sem_wait(&mutex);

    printf("%s",prompt);
    //get input
    char selection[5];
    bzero(selection, sizeof(selection));
    gets(selection);
    //printf("%s",selection);

    if (selection[0] == '0'){
      printf("Quitting...");
      exit(0);
      close(newsockfd);
      close(sockfd);
      pthread_exit(0);
    }
    else if (selection[0] == '1'){
      printf("Message: %s\n",buffer);
    }
    else{
      printf("Undefined input\n");
    }
    //n = write(newsockfd, client_prompt, strlen(client_prompt));
    if (n < 0)
     error("ERROR writing to socket");

    //bzero(buffer, sizeof(buffer));

    // n = write(newsockfd,buffer, strlen(buffer));
    // if (n < 0)
    //  error("ERROR reading from socket");
   fflush(stdout);


   n = read(newsockfd, buffer, sizeof(buffer));
   sem_post(&mutex);
   sleep(1);
   }
    close(newsockfd);
    close(sockfd);

    return 0;
}
void *thread_2(){

  // Setup phase
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
     error("ERROR opening socket");
  struct sockaddr_in serv_addr; // Server address struct
  bzero((char *) &serv_addr, sizeof(serv_addr));
  int portno = 8001;//screw it //atoi(port); // Port number is commandline argument
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
           sizeof(serv_addr)) < 0)
       error("ERROR on binding");
  printf("Listening for clients\n");
  listen(sockfd, 5);

  // Service phase
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr); // Address struct length
  int newsockfd = accept(sockfd,
                  (struct sockaddr *) &cli_addr,
                  &clilen);
  if (newsockfd < 0)
       error("ERROR on accept");



  char *prompt = "Client 2: Quit:0 Check Message:1 ";
  //char *client_prompt = "Quit:0 Send message:1 ";
  // Play the game
  int n; // number of bytes that were written/read

  sprintf(buffer,"Hello");

  for(;;){
    sem_wait(&mutex); //seperate io, otherwise the prompt doesn't match the response
    printf("%s",prompt);
    //get input
    char selection[5];
    bzero(selection, sizeof(selection));
    gets(selection);
    //printf("%s",selection);

    if (selection[0] == '0'){
      printf("Quitting...");
      close(newsockfd);
      close(sockfd);
      exit(0);
      pthread_exit(0);
      return 0;
    }
    else if (selection[0] == '1'){
      printf("Message: %s\n",buffer);
    }
    else{
      printf("Undefined input\n");

    }
    //n = write(newsockfd, client_prompt, strlen(client_prompt));
    if (n < 0)
     error("ERROR writing to socket");

    //bzero(buffer, sizeof(buffer));

    // n = write(newsockfd,buffer, strlen(buffer));
    // if (n < 0)
    //  error("ERROR reading from socket");

    n = read(newsockfd, buffer, sizeof(buffer));
    sem_post(&mutex);
    sleep(1);

    fflush(stdout);
   }


    close(newsockfd);
    close(sockfd);

    return 0;
}

int main() {

  if(sem_init(&mutex, 0, 1) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
	}



  pthread_t t1,t2;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&t1,&attr,thread_1,NULL);
  pthread_create(&t2,&attr,thread_2,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);



}
