#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

const char *SOCKET_PATH = "socket_server";
const int BUFFER_SIZE = 64;
const int LISTEN_BACKLOG = 5;

void handleError(char *error) {
	fprintf(stderr, "%s failed with error: %d\n", error, errno);
	exit(EXIT_FAILURE);
}

void addRedundantBits(char *data, char *divisor) {
	int n = strlen(divisor) - 1;
	if (sizeof(data) <= strlen(data) + n) {
		data = realloc(data, 2 * sizeof(data));
	}
	int len = strlen(data);
	int i;
	for (i=len; i<len+n; i++) {
		data[i] = '0';
	}
	data[i] = '\0';
}

int main(){
	int server_sockfd, client_sockfd;
	struct sockaddr_un server_addr, client_addr;
	
	unlink(SOCKET_PATH);

	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_sockfd == -1) {
		handleError("socket");
	}

	server_addr.sun_family= AF_UNIX;
	strcpy(server_addr.sun_path, SOCKET_PATH);

	int server_len=sizeof(server_addr);

	if (bind(server_sockfd, (struct sockaddr*)&server_addr, server_len) == -1) {
		handleError("bind");
	}

	if (listen(server_sockfd, LISTEN_BACKLOG) == -1) {
		handleError("listen");
	}

	printf("Server is on and running!\n");

	int client_len = sizeof(client_addr);

	client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);
	if (client_sockfd == -1) {
		handleError("accept");
	}

	char *data = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	char *divisor = (char *)malloc(sizeof(char) * BUFFER_SIZE);

	while(1){
		printf("Server is waiting...\n");

		read(client_sockfd, data, BUFFER_SIZE);
		read(client_sockfd, divisor, BUFFER_SIZE);

		printf("Data read from client %s and %s\n", data, divisor);

		//addRedundantBits(data, divisor);

		write(client_sockfd, data, strlen(divisor)+1);

		printf("Result sent to client: %s\n", data);
	}

	close(server_sockfd);

	return 0;
}
