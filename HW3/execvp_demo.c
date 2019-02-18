/* Chris Fietkiewicz (cxf47@case.edu)

Demonstrates: 
1. How to parse a string separated by spaces using fgets() and strtok().
2. How to use execvp() by separating a command and arguments.

After parsing the string, it checks whether the first part of the string
is equivalent to "ls" using strcmp(). For "ls", it prints a special message.
The first part of the string (before the 1st space), is used as a Linux
command with execvp(), no matter what it is.
*/

#include <unistd.h> // Required for execvp
#include <stdio.h> // Required for I/O
#include <string.h> // Required for string operations

#define MAX_LINE 80 // 80 chars per line, per command

int main() {
	char text[MAX_LINE]; // For user input text
	char *args[MAX_LINE/2 + 1];	// Choose max # of command line arguments
	printf("Enter text: ");
    fgets(text, MAX_LINE, stdin); // Get user input
    text[strlen(text) - 1] = '\0'; // Remove the \n from fgets
	args[0] = strtok(text, " "); // Get text before 1st space
	int i = 0; // Iterator for "arguments" after 1st space
	while (args[i] != NULL) // Loop until a null 
		args[++i] = strtok(NULL, " ");
	if (!strcmp(args[0], "ls")) // Returns difference in lexicographical order (0 means equal)	
		printf("Ah, I see that you used the 'ls' command. Excellent!\n");
	printf("Text before the 1st space: '%s'. Now calling execvp()...\n", args[0]);
	execvp(args[0], args); // Execute the command
}
