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

const char *SOCKET_PATH = "socket_server";
const int BUFFER_SIZE = 64;

void handleError(char *error) {
	fprintf(stderr, "%s failed with error: %d\n", error, errno);
	exit(EXIT_FAILURE);
}

void readInput(char *data, char *prompt) {
	printf("%s", prompt);
	fgets(data, BUFFER_SIZE, stdin);
	data[strlen(data)-1] = '\0';
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
		readInput(data, "Enter the data: ");
		readInput(divisor, "Enter the divisor: ");
		
		write(sockfd, data, strlen(data)+1);
		write(sockfd, divisor, strlen(divisor)+1);
		
		printf("%s and %s is sent to server\n", data, divisor);

		read(sockfd, result, BUFFER_SIZE);

		printf("Message got from server: %s\n", result);

	}

	close(sockfd);

	return 0;
}
