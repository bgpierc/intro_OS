#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int number,deadProcess;
	int rootID = getpid();
	printf("Number of processes to generate from root process %d: \n",rootID);
	scanf("%d",&number);
	int i,j,pid;
	for (i=0; i <= number; i++){
		pid = fork();
		if (pid){
			printf("Process %d PID: %d PPID: %d \n",i,getpid(),getppid());
			deadProcess = wait(NULL);
			printf("Process PID: %d is done!\n",deadProcess);
			return 0;
		}
	}
	return 0;
}