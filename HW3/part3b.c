#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(){
	int number;
	printf("Number of processes to generate from parent %d: ",getpid());
	scanf("%d",&number);
	int i,j,pid;
	for (i=1; i <= number; i++){
		pid = fork();
		if (!pid){
			printf("Forked process %d PID: %d PPID: %d \n",i,getpid(),getppid());
			return 0;
		}
	}
	for (j=1;j<=number;j++){
		int deadProcess = wait(NULL);
		printf("Process PID: %d is done!\n",deadProcess);
	}
	printf("Parent process %d is done\n",getpid());
}