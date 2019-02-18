// Chris Fietkiewicz. For problem 5.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For wait()

int main() {
	pid_t pid;

		/* fork a child process */
		pid = fork();

		if (pid == 0) { /* child process */
printf("Child\n");
//return 0;
}
wait(NULL);
printf("Parent\n");
}
