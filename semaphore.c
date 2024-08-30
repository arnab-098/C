#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

int shared = 1;

sem_t s;

void *fn1 (void *args) {
  int x;
  sem_wait(&s);
  x = shared;
  printf("Read value in thread 1: %d\n", shared);
  x++;
  printf("Local value in thread 1: %d\n", x);
  sleep(1);
  shared = x;
  printf("Shared value updated by thread 1: %d\n", shared);
  sem_post(&s);
}

void *fn2 (void *args) {
  int y;
  sem_wait(&s);
  y = shared;
  printf("Read value in thread 2: %d\n", shared);
  y++;
  printf("Local value in thread 2: %d\n", y);
  sleep(1);
  shared = y;
  printf("Shared value updated by thread 2: %d\n", shared);
  sem_post(&s);
}

int main (int argc, char *argv[]) {
  sem_init(&s, 0, 1);

  pthread_t th1, th2;

  pthread_create(&th1, NULL, fn1, NULL);
  pthread_create(&th2, NULL, fn2, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("Final value: %d\n", shared);

  return EXIT_SUCCESS;
}
