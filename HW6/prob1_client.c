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


  int shm_fd_message = shm_open(name1, O_RDWR, 0666);
  int shm_fd_semaphore = shm_open(name2,O_RDWR, 0666);
  if (shm_fd_message ==-1 || shm_fd_semaphore ==-1){
    puts("Shared Memory Failed\n");
    return -1;
  }

  mess = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_message, 0);
  sem = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore, 0);
  if (mess == MAP_FAILED || sem == MAP_FAILED){
    printf("One or both of the maps failed\n");
    return -1;
  }
  if (sem_open(sem,1,1) < 0){
      printf("Failed to open semaphore\n");
      return -1;
  }

  // int val;
  // sem_getvalue(sem,&val);
  // printf("%d",val);
  int response;
  do{

    // sem_getvalue(sem,&val);
    // printf("%d",val);
    printf("Message: %s\n0: Quit\n1: Change message\n2: Check message\n",mess);
    response = getchar() -'0'; //temporary hack
    if(response == 1){
      sem_wait(sem);
      puts("Enter new message: ");
      scanf("%s",mess); //yes lets allow the user to write arbitrary data directly to memory
      sem_post(sem);
    }
    else if (response == 2){
      printf("Message: %s\n",mess);
    }
    else if (response == 0){
      continue;
    }

  }while (response);



}
