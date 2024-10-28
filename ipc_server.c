#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

const char* FIFO1 = "./fifo1";
const char* FIFO2 = "./fifo2";

const int SIZE = 100;

int main(int argc, char *argv[]) {
  unlink(FIFO1);
  unlink(FIFO2);

  mkfifo(FIFO1, 0666);
  mkfifo(FIFO2, 0666);

  int fd1 = open(FIFO1, O_RDONLY);
  int fd2 = open(FIFO2, O_WRONLY);

  char buffer[SIZE];
  int index, number;

  read(fd1, buffer, sizeof(buffer));
  read(fd1, &index, sizeof(index));
  read(fd1, &number, sizeof(number));

  printf("Data received\n");

  char result[number];
  strncpy(result, buffer+index, number);
  result[strlen(result)] = '\0';

  write(fd2, result, strlen(result)+1);

  printf("Data sent\n");

  close(fd1);
  close(fd2);

  return 0;
}
