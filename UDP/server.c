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
  int server_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t server_size, client_size;
  char *buffer;

  server_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_fd == -1) {
    handle_error("socket");
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(IP);

  server_size = sizeof(server_addr);
  client_size = sizeof(client_addr);

  if (bind(server_fd, (struct sockaddr *)&server_addr, server_size) == -1) {
    handle_error("bind");
  }

  printf("Server listening for connections...\n");

  buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);

  if (recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_size) == -1) {
    handle_error("recvfrom");
  }
  printf("[+]Data recv: %s\n", buffer);

  bzero(buffer, BUFFER_SIZE);

  strcpy(buffer, "Hello from server");
  if (sendto(server_fd, buffer, strlen(buffer)+1, 0, (struct sockaddr *)&client_addr, client_size) == -1) {
    handle_error("sendto");
  }
  printf("[+]Data sent: %s\n", buffer);

  free(buffer);

  if (close(server_fd) == -1) {
    handle_error("close");
  }

  printf("Terminating server...\n");

  return EXIT_SUCCESS;
}

void handle_error(const char *msg) {
  fprintf(stderr, "%s failed with error: %d", msg, errno);
  exit(EXIT_FAILURE);
}
