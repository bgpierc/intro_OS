#include <stdio.h>
#include <unistd.h> //to remove sleep warning


int main(){
	int a = 0; // Regular integer
	const int b = 0; // Constant integer
	// Print the pointer values (addresses) in hexadecimal
	printf("%p, %p\n", &a, &b);
	sleep(30);
}
