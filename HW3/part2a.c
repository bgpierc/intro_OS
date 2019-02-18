#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	printf("Process: 0 PID: %d PPID: %d \n",getpid(),getppid());
	fflush(stdout);
	int child1,child2,child3,child4,child5,child6,j;
	child1 = fork();
	if (!child1){ 
		printf("Process: 1 PID: %d PPID: %d \n",getpid(),getppid());
		child3 = fork();
		if(!child3){
			printf("Process: 3 PID: %d PPID: %d \n",getpid(),getppid());
		}
		else{
			child4 = fork();
			if (!child4){
				printf("Process: 4 PID: %d PPID: %d \n",getpid(),getppid());
			}
		}
	}
	else{
		child2 = fork();
		if (!child2){
			printf("Process: 2 PID: %d PPID: %d \n",getpid(),getppid());
			child5 = fork();
			if (!child5){
				printf("Process: 5 PID: %d PPID: %d \n",getpid(),getppid());
			}
			else{
				child6 = fork();
				if (!child6){
					printf("Process: 6 PID: %d PPID: %d \n",getpid(),getppid());
				}
			}
		}
	}
	fflush(stdout);
	for (j = 0; j < 7; j++){
	int deadProcess = wait(NULL);
	if (deadProcess >0)
		printf("Process PID: %d is done!\n",deadProcess);
	}
	return 0;
}	