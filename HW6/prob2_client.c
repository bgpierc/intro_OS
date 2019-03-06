#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
  int sock;
	struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8000);
	char message[1000],server_reply[2000];
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (connect(sock,(struct sockaddr *)&server , sizeof(server)) < 0){
		perror("connect failed");
		return -1;
	}
  send(sock,"Hi server",strlen("Hi server")+1,0);
	for(int i =0; i < 3; i++){
    // if(recv(sock , server_reply , 2000 , 0) < 0){
		// 	puts("recieve failed");
		// 	break;
		// }
    // printf("%s\nA:",server_reply);
		scanf("%s" , message);
		if(send(sock , message , strlen(message)+1 , 0) < 0){
			puts("Send failed");
			return -1;
		}
    // recv(sock,server_reply,2000,0);
    // printf(server_reply);
	}
	close(sock);
	return 0;
}
