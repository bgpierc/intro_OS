#include <stdio.h>
#include <unistd.h> //to remove sleep warning
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int pid = fork();
	if (pid){ //parent
		printf("I'm the parent! Waiting for child...\n");
		int childID = wait(NULL);
		printf("The PID of my child was %d \n",childID);
	}
	else{
		printf("I'm the child! My parent's PID is %d \n",getppid());
		sleep(2);
	}


}	