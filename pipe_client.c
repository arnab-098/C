#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

const int SIZE = 100;

const char *FIFO1 = "./fifo1";
const char *FIFO2 = "./fifo2";

int main (int argc, char *argv[]) {
  int fd1, fd2;

  if ((fd1 = open(FIFO1, O_WRONLY)) == -1) {
    fprintf(stderr, "Failed to open pipe: %d\n", errno);
    return 1;
  }
  if ((fd2 = open(FIFO2, O_RDONLY)) == -1) {
    fprintf(stderr, "Failed to open pipe: %d\n", errno);
    return 1;
  }

  char buf1[SIZE], buf2[SIZE], result[SIZE];

  printf("Enter string 1: ");
  fgets(buf1, sizeof(buf1), stdin);
  printf("Enter string 2: ");
  fgets(buf2, sizeof(buf2), stdin);

  if (write(fd1, buf1, strlen(buf1)+1) == -1) {
    fprintf(stderr, "Failed to write to pipe: %d\n", errno);
    return 1;
  }
  if (write(fd1, buf2, strlen(buf2)+1) == -1) {
    fprintf(stderr, "Failed to write to pipe: %d\n", errno);
    return 1;
  }

  if (read(fd2, result, sizeof(result)) == -1) {
    fprintf(stderr, "Failed to read from pipe: %d\n", errno);
    return 1;
  }

  printf("%s\n", result);

  close(fd1);
  close(fd2);

  return 0;
}
