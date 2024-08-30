#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t s;

void *fn1 (void *args) {

  sem_wait(&s);
  printf("b");
  sem_post(&s);
  sleep(1);

  sem_wait(&s);
  printf("bb");
  sem_post(&s);
  sleep(1);

  sem_wait(&s);
  printf("bb");
  sem_post(&s);
  sleep(1);

  sem_wait(&s);
  printf("b\n");
  sem_post(&s);
  sleep(1);

}

void *fn2 (void *args) {

  for (int i=0; i<3; i++) {
    sem_wait(&s);
    printf("aa");
    sem_post(&s);
    sleep(1);
  }

}

int main (int argc, char *argv[]) {

  if (sem_init(&s, 0, 1) != 0) {
    perror("FAILED TO CREATE SEMAPHORE\n");
    exit(EXIT_FAILURE);
  }

  pthread_t th1, th2;

  if (pthread_create(&th1, NULL, fn1, NULL) != 0) {
    perror("FAILED TO CREATE THREAD\n");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&th2, NULL, fn2, NULL) != 0) {
    perror("FAILED TO CREATE THREAD\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  return EXIT_SUCCESS;

}
