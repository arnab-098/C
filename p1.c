#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char *argv[]) {

  char *fifo = "./fifo";
  mkfifo(fifo, 0666);

  char s1[100], s2[100], result[10];

  int fd1 = open(fifo, O_WRONLY);

  if (fd1 == -1) {
    perror("ERROR OPENING FIFO\n");
    exit(EXIT_FAILURE);
  }

  printf("Enter string 1: ");
  scanf("%s", s1);

  printf("Enter string 2: ");
  scanf("%s", s2);

  write(fd, s1, strlen(s)+1);
  write(fd, s2, strlen(s)+1);

  close(fd1);

  int fd2 = open(fifo, O_RDONLY);

  if (fd2 == -1) {
    perror("ERROR OPENING FIFO\n");
    exit(EXIT_FAILURE);
  }

  read(fd2, result, sizeof(result));

  printf("Result: %s\n", result);

  close(fd2);

  return EXIT_SUCCESS;

}
