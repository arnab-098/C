#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "crc.h"

const char *SOCKET_PATH = "socket_server";
const int BUFFER_SIZE = 64;
const char *TERMINATION_PROMPT = "end";

void handleError(char *error) {
	fprintf(stderr, "%s failed with error: %d\n", error, errno);
	exit(EXIT_FAILURE);
}

void readInput(char *data, char *prompt) {
	printf("%s", prompt);
	fgets(data, BUFFER_SIZE, stdin);
	data[strlen(data)-1] = '\0';
}

void checkError(char *data, char *divisor) {
  char *remainder = crc(data, divisor);
  for (int i=0; i<strlen(remainder); i++) {
    if (remainder[i] == '1') {
      printf("Error detected\n");
      return;
    }
  }
  printf("No error detected\n");
}

int main(){
	int sockfd;
	struct sockaddr_un addr;

	sockfd= socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd == -1) {
		handleError("socket");
	}

	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,SOCKET_PATH);

	int addrlen= sizeof(addr);
	
	if(connect(sockfd, (struct sockaddr*)&addr, addrlen) == -1){
		handleError("connect");
	}

	printf("Client connected!\n");

	char data[BUFFER_SIZE], divisor[BUFFER_SIZE], result[BUFFER_SIZE];

	while(1){
		readInput(data, "\nEnter the data: ");
		write(sockfd, data, strlen(data)+1);

    if (strcmp(data, TERMINATION_PROMPT) == 0) {
      break;
    }

		readInput(divisor, "Enter the divisor: ");
		write(sockfd, divisor, strlen(divisor)+1);
		
		read(sockfd, result, BUFFER_SIZE);

		printf("Message got from server: %s\n", result);
    checkError(result, divisor);

	}

  printf("\nClient closing connection...\n");

	close(sockfd);

	return 0;
}
