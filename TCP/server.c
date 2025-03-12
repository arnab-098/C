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

sem_t mutex;

typedef struct ThreadData {
  int fd;
  char inputData[BUFFER_SIZE];
} threadData;

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

void *bitStuffing(void *args) {
  threadData *data = (threadData *)args;
  char inputData[BUFFER_SIZE], result[BUFFER_SIZE];
  int i, j, k, size, count, fd;
  i = 0;
  j = 0;
  size = strlen(data->inputData);

  fd = data->fd;
  strcpy(inputData, data->inputData);

  while (i < size) {
    if (inputData[i] == '0') {
      count = 1;
      result[j] = inputData[i];
      for (k=i+1; inputData[k] == '0' && k < size && count < 5; k++) {
        result[++j] = inputData[k];
        count++;
        if (count == 5) {
          result[++j] = '1';
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

  write(fd, result, BUFFER_SIZE);

  sem_wait(&mutex);
  printf("%s -> %s\n", inputData, result);
  sem_post(&mutex);

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
  s_addr.sin_port = htons(4444);
  s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (bind(sfd, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
    handleError("bind");
  }

  if (listen(sfd, LISTEN_BACKLOG) == -1) {
    handleError("listen");
  }

  printf("Server is waiting for connection...\n");

  pthread_t threads[LISTEN_BACKLOG];

  count = 0;

  while (1) {
    c_addr_size = sizeof(cfd);
    cfd = accept(sfd, (struct sockaddr *) &c_addr, &c_addr_size);
    if (cfd == -1) {
      handleError("accept");
    }

    threadData data;
    data.fd = cfd;
    read(cfd, data.inputData, BUFFER_SIZE);

    if (pthread_create(&threads[count++], NULL, &bitStuffing, (void *)&data) != 0) {
      handleError("pthread_create");
    }

    if (count >= LISTEN_BACKLOG) {
      count = 0;
      while (count < LISTEN_BACKLOG) {
        if (pthread_join(threads[count], NULL) != 0) {
          handleError("pthread_join");
        }
        count++;
      }
      count = 0;
    }
  }

  if (close(sfd) == -1) {
    handleError("close");
  }

  sem_destroy(&mutex);

  return EXIT_SUCCESS;
}
