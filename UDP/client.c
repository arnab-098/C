#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


const int PORT = 4444;
const char *IP = "127.0.0.1";
const int BUFFER_SIZE = 32;


void handle_error(const char *msg);


int main(int argc, char **argv) {
  int sock_fd;
  struct sockaddr_in sock_addr;
  socklen_t sock_size;
  char * buffer;

  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fd == -1) {
    handle_error("socket");
  }

  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(PORT);
  sock_addr.sin_addr.s_addr = inet_addr(IP);

  sock_size = sizeof(sock_addr);

  buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);

  strcpy(buffer, "Hello World!");
  if (sendto(sock_fd, buffer, strlen(buffer)+1, 0, (struct sockaddr *)&sock_addr, sock_size) == -1) {
    handle_error("sendto");
  }
  printf("[+]Data sent: %s\n", buffer);

  bzero(buffer, BUFFER_SIZE);

  if (recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sock_addr, &sock_size) == -1) {
    handle_error("recvfrom");
  }
  printf("[+}Data recv: %s\n", buffer);

  free(buffer);

  if (close(sock_fd) == -1) {
    handle_error("close");
  }

  printf("Terminating client...\n");

  return EXIT_SUCCESS;
}

void handle_error(const char *msg) {
  fprintf(stderr, "%s failed with error: %d", errno);
  exit(EXIT_FAILURE);
}
