#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_producer =  PTHREAD_COND_INITIALIZER;

struct {
  char data[1024];
  int  filled;
  int  closed;
}buff = {.filled = 0, .closed = 0};

void *consumer(void *arg)
{
  int munching = 1;
  while(munching){
    pthread_mutex_lock(&mutex);
    if (buff.filled != 1)
      pthread_cond_wait(&cond_consumer, &mutex);
    printf("%s", buff.data);
    buff.filled = 0;
    if (buff.closed == 1)
      munching =0;

    pthread_cond_signal(&cond_producer);
    pthread_mutex_unlock(&mutex);
  }
  return 0;
}

void *producer (void *arg)
{
  const char *data = " Hello, Stonehenge! Who takes the Pandorica takes the"
    "Universe! But, bad news everyone, 'cause guess who! Ha! Except, you lot,"
    "you're all whizzing about, it's really very distracting. Could you all just"
    "stay still a minute because I am talking!";
  size_t len = strlen(data);
  size_t pos = 0;
  int cooking = 1;
  while (cooking == 1){
    pthread_mutex_lock(&mutex);
    if (buff.filled == 1)
      pthread_cond_wait(&cond_producer, &mutex);
    const int buf_space = sizeof(buff.data) -1;
    const int wlen = (len - pos) < buf_space ? len - pos : buf_space;
    memcpy(&buff.data[0], data  + pos, wlen);
    buff.data[wlen] = 0;
    buff.filled = 1;
    pos += wlen;
    if (pos >= len){
      cooking = 0;
      buff.closed = 1;
    }
    
    pthread_cond_signal(&cond_consumer);
    pthread_mutex_unlock(&mutex);
  }
  return 0;
}  

int main(int argc, char ** argv)
{
  pthread_t prod_thread, con_thread;
  pthread_create (&prod_thread, NULL, producer, NULL);
  pthread_create (&con_thread, NULL, consumer, NULL);

  pthread_join(prod_thread, NULL);
  pthread_join(con_thread, NULL);


return 0;
}
