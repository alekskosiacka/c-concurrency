
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t mysem;

//declare a thread function
void * funkythread (void*arg);

int main (int argc, char ** argv)
{
  //create semaphore that is shared between threads and has only 1
  //so basically a mutex
  //create a handle called thread that will be used to
  //refer to a thread
  sem_init(&mysem , 0 , 1);
  pthread_t thread[4];
  //create a thread
  for (int i = 0; i<4; i++)
  pthread_create( &thread[i], NULL , funkythread , i);
  
  for (int i = 0; i<4; i++)
  pthread_join(thread[i], NULL);
  // creates a new thread called funkythread
  // waits for it to complete/terminate

  return 0;
}
//define function aka give it value
void * funkythread ( void *arg)
{
  //sem_t = a semaphore
  //sem_init = create semaphore
  //sem_wait = take semaphore
  //sem_post = release semaphore
  for(int i = 0; i<20; i++){
  int num = (int)arg;
  //pthread_mutex_lock(&mutex);
  sem_wait(&mysem);
  printf("Roses\n");
  printf("Tulips %d \n" , num);
  printf("Orchids %d\n", i);
  sem_post(&mysem);
  // pthread_mutex_unlock(&mutex);
  }
  return NULL;
}


