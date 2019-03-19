/* Chris Fietkiewicz. Optional example of creating different types of
   shared memory with a single function.
*/
#include <unistd.h> // For shared memory
#include <stdio.h> // For printf
#include <stdlib.h> // For exit
#include <fcntl.h> // For shared memory
#include <sys/shm.h> // For shared memory
#include <sys/mman.h> // For shared memory
#include <semaphore.h> // For semaphores
#include <string.h> // For string operations

// Create shared memory
void *create_shm(const char* name, int SIZE) {
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	void *memory = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (memory == MAP_FAILED) {
		printf("Map failed\n");
		exit(0);
	}
	return memory;
}

int main() {
	// Set up shared memory for string
	char *name_string = "ChrisF string";
	char *string = (char*) create_shm(name_string, 50);
	sprintf(string, "Hello");
	printf("string: %s\n", string);
	
	// Set up shared memory for semaphore
	const char *name_semaphore = "ChrisF semaphore";
	sem_t *semaphore = (sem_t*) create_shm(name_semaphore, 1);
	if(sem_init(semaphore, 1, 1)) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		exit(0);
	}
	int value;
	sem_getvalue(semaphore, &value);
	printf("semaphore = %d\n", value);

	// Set up shared memory for integer
	const char *name_integer = "ChrisF integer";
	int *integer = (int*) create_shm(name_integer, 1);
	*integer = 123;
	printf("integer = %d\n", *integer);

	// Remove shared memory segments
	if (shm_unlink(name_string) == -1 || shm_unlink(name_semaphore) == -1 || shm_unlink(name_integer) == -1) {
		printf("Error removing shared memory\n");
		exit(-1);
	}
	return 0;
}