#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;
sem_t full;
sem_t empty;
sem_t track_S;

int bounded_buffer[5];
int S; //to track theoretical value of mutex semaphore

void *producer_thread();
void *consumer_thread();
void wait_mutex(int thread);
void post_mutex(int thread);

int main(){
  if(sem_init(&mutex, 0, 1) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
	}
  if(sem_init(&full, 0, 0) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
	}
  if(sem_init(&empty,0, 5) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
	}
  if(sem_init(&track_S,0,1) <0){ // 1 = multiprocess
    fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
  }
  printf("Initialized semaphores\n");
  pthread_t parent,child;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&parent,&attr,producer_thread,NULL);
  pthread_create(&child,&attr,consumer_thread,NULL);

  pthread_join(parent,NULL);
  pthread_join(child,NULL);

  sem_destroy(&empty);
  sem_destroy(&mutex);
  sem_destroy(&full);
  return 0;
}

void *producer_thread(){
  int produced_nums[] = {1,2,3,4,5,6,7,8,9,10};
  int i;
  for (i = 0; i < 10;i++){
    sem_wait(&empty);
    wait_mutex(0);
    bounded_buffer[i%5] = produced_nums[i];
    post_mutex(0);
    sem_post(&full);
  }
  pthread_exit(0);
}
void *consumer_thread(){
  sleep(0.5);
  int i;
  for (i =0;i < 10;i++){
    sem_wait(&full);
    wait_mutex(1);
    printf("Child consumed data = %d\n",bounded_buffer[i%5]);
    bounded_buffer[i%5]=0;
    post_mutex(1);
    sem_post(&empty);
  }
  pthread_exit(0);
}
void wait_mutex(int thread){
    sem_wait(&track_S);
    if (thread == 0){
      printf("Parent wait ");
    }
    else if (thread ==1){
      printf("Child wait ");
    }
    S--;
    printf("S=%d\n",S);
    fflush(stdout);
    sem_post(&track_S);
    sem_wait(&mutex);
}
void post_mutex(int thread){
    sem_wait(&track_S);
    if (thread == 0){
      printf("Parent post ");
    }
    else if (thread == 1){
      printf("Child post ");
    }
    S++;
    printf("S=%d\n",S);
    fflush(stdout);
    sem_post(&track_S);
    sem_post(&mutex);
}
