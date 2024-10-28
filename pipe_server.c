#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const int SIZE = 100;

const char *FIFO1 = "./fifo1";
const char *FIFO2 = "./fifo2";

void compare(char buf1[], char buf2[], char result[]);

int main (int argc, char *argv[]) {
  unlink(FIFO1);
  unlink(FIFO2);

  if (mkfifo(FIFO1, 0666) == -1) {
    fprintf(stderr, "Failed to make pipe: %d\n", errno);
    return 1;
  }
  if (mkfifo(FIFO2, 0666) == -1) {
    fprintf(stderr, "Failed to make pipe: %d\n", errno);
    return 1;
  }

  int fd1, fd2;

  if ((fd1 = open(FIFO1, O_RDONLY)) == -1) {
    fprintf(stderr, "Failed to open pipe: %d\n", errno);
    return 1;
  }
  if ((fd2 = open(FIFO2, O_WRONLY)) == -1) {
    fprintf(stderr, "Failed to open pipe: %d\n", errno);
    return 1;
  }

  char buf1[SIZE], buf2[SIZE], result[SIZE];

  if (read(fd1, buf1, sizeof(buf1)) == -1) {
    fprintf(stderr, "Failed to read from pipe: %d\n", errno);
    return 1;
  }
  if (read(fd1, buf2, sizeof(buf2)) == -1) {
    fprintf(stderr, "Failed to read from pipe: %d\n", errno);
    return 1;
  }

  printf("String 1: %s\nString 2: %s\n", buf1, buf2);

  compare(buf1, buf2, result);

  printf("Compared\n");

  if (write(fd2, result, strlen(result)+1) == -1) {
    fprintf(stderr, "Failed to write to pipe: %d\n", errno);
    return 1;
  }

  close(fd1);
  close(fd2);

  return 0;
}

void compare(char buf1[], char buf2[], char result[]) {
  if (strcmp(buf1, buf2) == 0) {
    strcpy(result, "The strings are same");
  } else {
    strcpy(result, "The strings are not same");
  }
}

