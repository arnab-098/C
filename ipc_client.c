#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const char* FIFO1 = "./fifo1";
const char* FIFO2 = "./fifo2";

const int SIZE = 100;

int main(int argc, char *argv[]) {
  char buf1[100], buf2[100], buf3[100];
  printf("Enter string: ");
  fgets(buf1, sizeof(buf1), stdin);
  buf1[strlen(buf1)-1] = '\0';

  int index, number;

  printf("Enter index: ");
  scanf("%d", &index);
  printf("Enter number of characters: ");
  scanf("%d", &number);

  int fd1 = open(FIFO1, O_WRONLY);
  int fd2 = open(FIFO2, O_RDONLY);

  write(fd1, buf1, strlen(buf1)+1);
  write(fd1, &index, sizeof(index));
  write(fd1, &number, sizeof(number));

  char result[SIZE];
  read(fd2, result, sizeof(result));
  printf("%s\n", result);

  close(fd1);
  close(fd2);

  return 0;
}
