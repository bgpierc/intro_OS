#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const char *name = "OS";
	const int SIZE = 4096;
	int shm_fd;
	void *ptr;
	int i;
	shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}
		for (int i = 0; i < 3; i++){
			puts(ptr); //question
			char *response[80];
			scanf("%s",response);
			memcpy(ptr,response,strlen(response)+1);
			sleep(10);
			puts(ptr);//result
			sleep(10);
	}
	printf("That's all folks! Thanks for playing!");


	return 0;
}
