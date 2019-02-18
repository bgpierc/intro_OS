// Chris Fietkiewicz (cxf47)
// Stays busy with nested for loops
#include <stdio.h>
#include <unistd.h> //to remove sleep warning

int main() {
	int i, j, k, N = 2;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				sleep(1);
			}
		}
	}
}
