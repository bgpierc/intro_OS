
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "Studying ";
	const char *message1= "Operating Systems ";
	const char *message2= "Is Fun!";

	const char *questions[] = {"What is the number of this course? ","Who is the instructor? ","What is 2+2 "};
	const char *anwsers[] = {"338","Chris","4"};
	int shm_fd;
	void *ptr;

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
	printf("Map failed\n");
	return -1;
}

	for (int i = 0; i < 3; i++){
		memcpy(ptr,questions[i],strlen(questions[i])+1);
		puts("Waiting for response...");
		sleep(10);
		char *response = (char *)ptr;
		printf("The user's anwser was: %s",response);
		printf("The correct response is: %s",anwsers[i]);
		if (strcmp(response,anwsers[i]) == 0){
				char * correct = "That's right!";
				memcpy(ptr,correct,strlen(correct)+1);
				sleep(10);
		}
		else{
				char response[80];
				strcpy(response, "Wrong, the correct anwser was: ");
				strcat(response,anwsers[i]);
				memcpy(ptr,response,strlen(response)+1);
				sleep(10);
		}

	}


	return 0;
}
