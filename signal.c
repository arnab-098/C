#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void handler (int sig) {

  char *message = "Signal sent\n";
  write(STDOUT_FILENO, message, strlen(message));
  return;
}


int main (int argc, char *argv[]) {

  signal(SIGCONT, handler);

  int pid = fork();

  if (pid == -1) {
    perror("FORK FAILED\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    while (1) {
      pause();
      printf("Child received signal\n");
      int n;
      printf("Enter the year: ");
      scanf("%d", &n);
      if (n % 4 == 0 && n % 100 != 0 || n % 400 == 0) {
        printf("Leap year\n");
      }
      else {
        printf("Not leap year\n");
      }
    }
  }
  else {
    while (1) {
      sleep(5);
      printf("Parent sending signal\n");
      kill(pid, SIGCONT);
    }
  }

  return EXIT_SUCCESS;

}
