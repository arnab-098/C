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
const int INPUT_BUFFER_SIZE = 32;
const int OUTPUT_BUFFER_SIZE = INPUT_BUFFER_SIZE * 2;
const char *TERMINATION_PROMPT = "END";


void handle_error(const char *msg);


int main(int argc, char **argv) {
    int sock_fd;
    struct sockaddr_in sock_addr;
    socklen_t sock_size;
    char * input, *output;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1) {
        handle_error("socket");
    }

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP, &sock_addr.sin_addr) != 1) {
        perror("inet_pton");
        return EXIT_FAILURE;
    }

    sock_size = sizeof(sock_addr);

    input = (char *)malloc(sizeof(char) * INPUT_BUFFER_SIZE);
    output = (char *)malloc(sizeof(char) * OUTPUT_BUFFER_SIZE);

    while(1) {
        bzero(input, INPUT_BUFFER_SIZE);
        printf("Enter data: ");
        fgets(input, INPUT_BUFFER_SIZE, stdin);
        input[strlen(input)-1] = '\0';

        if (sendto(sock_fd, input, strlen(input)+1, 0, (struct sockaddr *)&sock_addr, sock_size) == -1) {
            handle_error("sendto");
        }

        if (!strcmp(input, TERMINATION_PROMPT)) {
            break;
        }

        printf("[+]Data sent: %s\n", input);

        bzero(output, OUTPUT_BUFFER_SIZE);
        if (recvfrom(sock_fd, output, OUTPUT_BUFFER_SIZE, 0, (struct sockaddr *)&sock_addr, &sock_size) == -1) {
            handle_error("recvfrom");
        }
        printf("[+}Data recv: %s\n", output);
    }

    free(input);
    free(output);

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
