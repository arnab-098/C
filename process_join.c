#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv){
  int pid = fork();

  if (pid == -1) {
    perror("Failed to fork\n");
    return 1;
  }

  if (pid == 0) {
    printf("Child 1: %d\n", getpid());
    sleep(1);
  } else {
    int pid2 = fork();
    if (pid2 == 0) {
      printf("Child 2: %d\n", getpid());
      sleep(1);
    } else {
      printf("Parent: %d\n", getpid());

      int status, corpse;
      while ((corpse = wait(&status)) > 0) {
        printf("PID %5d exited with status 0x%.4X\n", corpse, status);
      }

      printf("Main program terminating\n");
    }
  }

  return 0;
}
