#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {

  int pid1 = fork();

  if (pid1 == -1) {
    perror("FORK FAILED\n");
    exit(EXIT_FAILURE);
  }

  if (pid1 == 0) {
    printf("Child process 1\n");
    printf("PID: %d\tPPID: %d\n", getpid(), getppid());
    sleep(4);
    printf("\nChild 1 terminating");
  }
  else {
    int pid2 = fork();

    if (pid2 == -1) {
      perror("FORK FAILED\n");
      exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
      printf("%d: Child process 2\n", getpid());
      printf("PID: %d\tPPID: %d\n", getpid(), getppid());
      sleep(1);
      printf("\nChild 2 terminating");
    }
    else {
      int pid3 = fork();

      if (pid3 == -1) {
        perror("FORK FAILED\n");
        exit(EXIT_FAILURE);
      }

      if (pid3 == 0) {
        printf("%d: Child process 3\n", getpid());
        printf("PID: %d\tPPID: %d\n", getpid(), getppid());
        sleep(10);
        printf("\nChild 3 terminating");
      }
      else {
        printf("Parent process\n");
        printf("PID: %d\tPPID: %d\n", getpid(), getppid());
        sleep(5);
        printf("\nParent terminating");
      }
    }
  }

  printf("\n");

  return EXIT_SUCCESS;

}
