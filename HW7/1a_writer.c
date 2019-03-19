#include <unistd.h> // For shared memory
#include <stdio.h> // For printf
#include <stdlib.h> // For exit
#include <fcntl.h> // For shared memory
#include <sys/shm.h> // For shared memory
#include <sys/mman.h> // For shared memory
#include <semaphore.h> // For semaphores
#include <string.h> // For string operations


int main(){
  const int SIZE = 128;
  //shared memory
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
  void *write_lock = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore_write_lock, 0);
  sem_t *read_lock = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore_read_lock, 0);
  int *num_readers = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_num_readers, 0);

  char *prompt = "0. Quit 1. Write Message";
  for(;;){
    printf("%s",prompt);
    char selection[5];
    bzero(selection, sizeof(selection));
    gets(selection);
    if (selection[0] == '0'){
      return 0;
    }
    else if (selection[0] == '1'){
      if ((int)*num_readers != 0){
          int tmp;
          sem_getvalue(read_lock,&tmp);
          printf("Waiting for %d readers...\n",tmp);
          int val =1;
          while(val>1){
            sem_getvalue(read_lock,&val);
            if (val != tmp){
              printf("Waiting for %d readers...\n",val);
              tmp = val;
            }
          }
          printf("New Message: ");
          char buf[80];
          gets(buf);
          gets(buf);
          sprintf(mess,buf);

      }
      else{
        char tmp[80];
        printf("%s","Enter Message: ");
        gets(tmp);
        gets(tmp);
        sprintf(mess,tmp);
      }
    }
    else
      printf("%s","Invalid Input");
  }
}
