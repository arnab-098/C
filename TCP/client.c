#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 32;

void signalHandler(int sigNum) {
  if (sigNum == SIGINT) {
    printf("\nShutting down client...\n");
    exit(EXIT_SUCCESS);
  }
}

void handleError(const char *error) {
  fprintf(stderr, "%s failed with error: %d\n", error, errno);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  signal(SIGINT, signalHandler);

  struct sockaddr_in addr;
  int fd;
  char buffer[BUFFER_SIZE];

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    handleError("socket");
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(4444);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(fd, (struct sockaddr *) &addr, sizeof(addr))) {
    handleError("connect");
  }

  printf("Input data: ");
  fgets(buffer, BUFFER_SIZE, stdin);
  buffer[strlen(buffer)-1] = '\0';

  write(fd, buffer, BUFFER_SIZE);
  read(fd, buffer, BUFFER_SIZE);
  printf("Stuffed Data: %s\n", buffer);

  if (close(fd) == -1) {
    handleError("close");
  }

  return EXIT_SUCCESS;
}
