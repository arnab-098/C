#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUFFER_SIZE 64

const int LISTEN_BACKLOG = 5;
const char *TERMINATION_PROMPT = "QUIT";
const char *IP = "127.0.0.1";
const int PORT = 4444;

sem_t mutex;

void signalHandler(int sigNum) {
  if (sigNum == SIGINT) {
    printf("\nShutting down server...\n");
    exit(EXIT_SUCCESS);
  }
}

void handleError(const char *error) {
  fprintf(stderr, "%s failed with error: %d\n", error, errno);
  exit(EXIT_FAILURE);
}

void bitStuffing(char *inputData, char *result) {
  int i, j, k, size, count;

  i = 0;
  j = 0;
  size = strlen(inputData);

  while (i < size) {
    if (inputData[i] == '1') {
      count = 0;
      result[j] = inputData[i];
      for (k=i+1; inputData[k] == '0' && k < size && count < 5; k++) {
        result[++j] = inputData[k];
        count++;
        if (count == 5) {
          result[++j] = '0';
        }
        i = k;
      }
    } else {
      result[j] = inputData[i];
    }
    i++;
    j++;
  }
  result[j] = '\0';
}

void *respond(void *args) {
  int fd = *(int *)args;

  char *inputData, *result;

  inputData = (char *)malloc(sizeof(char) * BUFFER_SIZE);
  result = (char *)malloc(sizeof(char) * BUFFER_SIZE);

  while (1) {
    read(fd, inputData, sizeof(inputData));

    if (strcmp(inputData, TERMINATION_PROMPT) == 0) {
      break;
    }

    bitStuffing(inputData, result);

    write(fd, result, strlen(result));

    sem_wait(&mutex);
    printf("%s -> %s\n", inputData, result);
    sem_post(&mutex);

    sleep(1);
  }

  free(inputData);
  free(result);

  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  signal(SIGINT, signalHandler);

  sem_init(&mutex, 0, 1);

  struct sockaddr_in s_addr, c_addr;
  int sfd, cfd, c_addr_size, count;

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    handleError("socket");
  }

  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  s_addr.sin_addr.s_addr = inet_addr(IP);

  if (bind(sfd, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
    handleError("bind");
  }

  if (listen(sfd, LISTEN_BACKLOG) == -1) {
    handleError("listen");
  }

  printf("Server is waiting for connection...\n");

  while (1) {
    c_addr_size = sizeof(cfd);
    cfd = accept(sfd, (struct sockaddr *) &c_addr, &c_addr_size);
    if (cfd == -1) {
      handleError("accept");
    }

  	pthread_t thread;

    if (pthread_create(&thread, NULL, &respond, (void *)&cfd) != 0) {
      handleError("pthread_create");
    }
  }

  if (close(sfd) == -1) {
    handleError("close");
  }

  sem_destroy(&mutex);

  return EXIT_SUCCESS;
}
