#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 33;
const char *TERMINATION_PROMPT = "QUIT";
const char *IP = "127.0.0.1";
const int PORT = 4444;

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
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr(IP);

  if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
    handleError("connect");
  }

	while (1) {
		printf("Input data: ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strlen(buffer)-1] = '\0';

    if (strcmp(buffer, TERMINATION_PROMPT) == 0) {
      break;
    }

		write(fd, buffer, strlen(buffer));
    printf("Data sent to server: %s\n", buffer);
		read(fd, buffer, sizeof(buffer));
		printf("Data receviced from server: %s\n", buffer);
	}

  printf("Terminating Client...\n");

  return EXIT_SUCCESS;
}
