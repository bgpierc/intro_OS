// Chris Fietkiewicz (cxf47)
// Sleeps for 30 seconds

#include <stdio.h>
#include <unistd.h> //to remove sleep warning
int main() {
	printf("Sleeping\n");
	fflush(stdout); // Force output
	sleep(30);
	return 0;
}
