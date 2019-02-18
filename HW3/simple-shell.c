//bgp12
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void parseArguments(char text[], char *args[]);

int main(void){
    size_t MAX_LINE = 80;
    int should_run = 1;
	int i, upper;

    while (should_run){   
        char text[MAX_LINE]; // For user input text
        char *args[MAX_LINE/2 + 1]; // Choose max # of command line arguments
        printf("sh>");
        fgets(text, MAX_LINE, stdin); // Get user input
        parseArguments(text,args);
        if (!strcmp(args[0], "exit")){
            return 0;
        }
        int pid = fork();
        if (!pid){ //child
            execvp(args[0], args); // Execute the command
        }
        else
            wait(NULL); //wait for child
    }

    
}

void parseArguments(char text[], char *args[]){ //helper function based on code in execvp_demo.c
    text[strlen(text) - 1] = '\0'; // Remove the \n from fgets
    args[0] = strtok(text, " "); // Get text before 1st space
    int i = 0; // Iterator for "arguments" after 1st space
    while (args[i] != NULL) // Loop until a null 
        args[++i] = strtok(NULL, " ");

}


