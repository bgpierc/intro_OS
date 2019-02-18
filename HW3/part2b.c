#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    int child1,child2,i,j;
    printf("Root PID: %d\n",getpid());
    fflush(stdout);
    for(i=1;i<3;i++){
        child1=fork();
        if(child1)
            child2=fork();        
        if(child1 && child2)        
            break;            
		printf("Process PID: %d PPID: %d \n",getpid(),getppid());  
	}
	fflush(stdout);
    for (j = 0; j < 7; j++){
		int deadProcess = wait(NULL);
		if (deadProcess >0)
			printf("Process PID: %d is done!\n",deadProcess);
	}
    return 0;
}

