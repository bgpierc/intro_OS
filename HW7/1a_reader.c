#include <unistd.h> // For shared memory
#include <stdio.h> // For printf
#include <stdlib.h> // For exit
#include <fcntl.h> // For shared memory
#include <sys/shm.h> // For shared memory
#include <sys/mman.h> // For shared memory
#include <semaphore.h> // For semaphores
#include <string.h> // For string operations

int main(){
  const int SIZE = 128; //overkill
  int shm_fd_message = shm_open("Message", O_RDWR, 0666);
  int shm_fd_semaphore_write_lock = shm_open("write_lock",O_RDWR,0666);
  int shm_fd_semaphore_read_lock = shm_open("read_lock",O_RDWR,0666);
  int shm_fd_num_readers = shm_open("read_count", O_RDWR,0666);

  if (shm_fd_message ==-1 || shm_fd_semaphore_write_lock ==-1 || shm_fd_semaphore_read_lock ==-1){
    puts("Shared Memory Failed\n");
    return -1;
  }
//ftruncate
  ftruncate(shm_fd_message,SIZE);
  ftruncate(shm_fd_semaphore_write_lock,SIZE);
  ftruncate(shm_fd_semaphore_read_lock,SIZE);
  ftruncate(shm_fd_num_readers,SIZE);
//mmap
  void *mess = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_message, 0);
  sem_t *write_lock = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore_write_lock, 0);
  sem_t *read_lock = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore_read_lock, 0);
  int *num_readers = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_num_readers, 0);


  char *prompt = "0. Quit 1. Read Message";
  for(;;){
    printf("%s\n",prompt);
    char selection[5];
    bzero(selection, sizeof(selection));
    gets(selection);
    if (selection[0] == '0'){
      return 0;
    }
    else if (selection[0] == '1'){
      int tmp;
      sem_wait(read_lock);//sem_getvalue(read_lock,&tmp);
      *num_readers++;
      if (num_readers == 1){
        wait()
      }
      //sem_post(read_lock);
      printf("There are %d readers\n",tmp);

      printf("The message is %s\n",mess);
      printf("This message will be valid for 2 seconds\n");
      fflush(stdout);
      sleep(10);
      //sem_trywait(read_lock); //we don't want to block, just keep track of who's in the critical section
    }
    else
      printf("%s","Invalid Input");
  }
}
