// Chris Fietkiewicz. Solution to Problem #2 (client program).
// Usage: client ipaddress port
// Example: client 127.0.0.1 8000

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <semaphore.h>
#include <fcntl.h> // for open



// Helper function to conveniently print to stderr AND exit (terminate)
void error(const char *msg) {
    perror(msg);
    exit(0);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    int portno = atoi(argv[2]); //must be 8000 or 8001
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    struct hostent *server;
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

  char buffer[256];
  bzero(buffer, sizeof(buffer));
	int n; // number of bytes that were written/read
  char *client_prompt = "Quit:0 Send message:1 ";
  for(;;){
    printf("%s",client_prompt);
    char selection[5];
    bzero(selection, sizeof(selection));
    gets(selection);
    if (selection[0] == '0'){
      close(sockfd);
      return 0;
    }
    else if (selection[0] == '1'){
      printf("Enter Message: ");
      gets(buffer);
      n = write(sockfd,buffer,sizeof(buffer));

    }
    else{
      printf("Undefined input\n");
    }
  }
	return 0;
}
