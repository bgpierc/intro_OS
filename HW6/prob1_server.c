#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>


int main(){
  const int SIZE = 4096;
	const char *name1 = "Message";
  const char *name2 = "Semaphore";
  void *mess;
  void *sem;


  int shm_fd_message = shm_open(name1, O_CREAT | O_RDWR, 0666);
  int shm_fd_semaphore = shm_open(name2, O_CREAT | O_RDWR, 0666);
  if (shm_fd_message ==-1 || shm_fd_semaphore ==-1){
    puts("Shared Memory Failed\n");
    return -1;
  }

  ftruncate(shm_fd_message,SIZE);
  ftruncate(shm_fd_semaphore,SIZE);

  mess = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_message, 0);
  sem = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore, 0);
  if (mess == MAP_FAILED || sem == MAP_FAILED){
    printf("One or both of the maps failed\n");
    return -1;
  }

  memcpy(mess,"Hello",strlen("Hello")+1);

  sem_t mutex;
  if(sem_init(&mutex, 1, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
	}
  memcpy(sem,&mutex,sizeof(mutex));

  int response;

  do{
    int val;
    // sem_getvalue(sem,&val);
    // printf("Semaphore Value: %d\n",val);

    // sem_getvalue(sem,&val);
    // printf("Semaphore Value: %d\n",val);
    printf("Message: %s\n0: Quit\n1: Change message\n2: Check message\n",mess);
    scanf(" %d",&response);
    if(response == 1){
      puts("Enter new message: ");
      sem_wait(sem);
      scanf("%s",mess); //security thru prayer
      sem_post(sem);
    }
    else if (response == 2){
      printf("The current message is: %s\n",mess);
    }
    // sem_getvalue(sem,&val);
    // printf("Semaphore Value: %d\n",val);

  }while (response);

sem_destroy(sem);

}
