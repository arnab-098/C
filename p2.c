#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {

  char *fifo = "./fifo";
  mkfifo(fifo, 0666);

  int fd1 = open(fifo, O_RDONLY);

  if (fd1 == -1) {
    perror("FAILED TO OPEN FIFO\n");
    exit(EXIT_FAILURE);
  }

  char s1[100], s2[100], result[10];

  read(fd1, s1, sizeof(s1));
  read(fd1, s2, sizeof(s2));

  close(fd1);

  if (strcmp(s1, s2) == 0) {
    strcpy(result, "SAME");
  } else {
    strcpy(result, "NOT SAME");
  }

  printf("Compared\n");

  int fd2 = open(fifo, O_WRONLY);

  if (fd2 == -1) {
    perror("FAILED TO OPEN FIFO\n");
    exit(EXIT_FAILURE);
  }

  write(fd2, result, strlen(result));

  close(fd2);

  return EXIT_SUCCESS;

}
