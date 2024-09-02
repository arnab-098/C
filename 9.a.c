#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *fn1 (void *args) {

  printf("b");
  sleep(1);

  printf("bb");
  sleep(1);

  printf("bb");
  sleep(1);

  printf("b\n");
  sleep(1);

}

void *fn2 (void *args) {

  for (int i=0; i<3; i++) {
    printf("aa");
    sleep(1);
  }

}

int main (int argc, char *argv[]) {

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
