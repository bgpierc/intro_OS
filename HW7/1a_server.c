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
	  char *initial_message = "Initial Message";
    char *message = (char*) create_shm("Message",80);
    sprintf(message,initial_message);
    printf("Initial Message: %s\n",message);

    int *readers = (int*) create_shm("read_count",80);


    sem_t mutex;
    if(sem_init(&mutex, 1, 1) < 0) { // 0 = multithreaded
  		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
  		return -1;
  	}
    void *sem_write_lock = create_shm("write_lock",80);
    memcpy(sem_write_lock,&mutex,sizeof(mutex));

    sem_t read_lock;
    if(sem_init(&read_lock, 1, 0) < 0) { // 0 = multithreaded
  		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
  		return -1;
  	}
    void *sem_read_lock = create_shm("read_lock",80);
    memcpy(sem_read_lock,&read_lock,sizeof(read_lock));
    for (;;){

    }

}
