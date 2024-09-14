#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "queue.h"

#define N 10


sem_t semFull, semEmpty, mutex;


queue q;


void handler(int sig) {
  char *message = "\nENDING EXCECUTION\n";
  write(1, message, strlen(message));
  exit(EXIT_SUCCESS);
}


void *producer(void *args) {
  
  while (1) {
    sem_wait(&semEmpty);
    sem_wait(&mutex);
    enQueue(&q, rand() % 100);
    sem_post(&mutex);
    sem_post(&semFull);
  }

}


void *consumer(void *args) {

  while (1) {
    sem_wait(&semFull);
    sem_wait(&mutex);
    int x = deQueue(&q);
    printf("Got %d\n", deQueue(&q));
    sem_post(&mutex);
    sem_post(&semEmpty);
    sleep(1);
  }

}


int main (int argc, char *argv[]) {

  signal(SIGINT, handler);

  q = create();

  sem_init(&mutex, 0, 1);
  sem_init(&semFull, 0, 0);
  sem_init(&semEmpty, 0, SIZE);

  pthread_t th[N];

  int i;
  for (i=0; i<N; i++) {
    if (i%2 == 0) {
      if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
        perror("FAILED TO CREATE THREAD\n");
      }
    } else {
      if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
        perror("FAILED TO CREATE THREAD\n");
      }
    }
  }
  
  for (i=0; i<N; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      perror("FAILED TO JOIN THREAD\n");
    }
  }

  sem_destroy(&mutex);
  sem_destroy(&semFull);
  sem_destroy(&semEmpty);

  return EXIT_SUCCESS;

}

