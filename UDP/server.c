#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
char *hammingCode(const char *inputData);
char calculateParity(const char *data, int position);


int main(int argc, char **argv) {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_size, client_size;
    char *input, *result;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1) {
        handle_error("socket");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP, &server_addr.sin_addr) != 1) {
        perror("inet_pton");
        return EXIT_FAILURE;
    }

    server_size = sizeof(server_addr);
    client_size = sizeof(client_addr);

    if (bind(server_fd, (struct sockaddr *)&server_addr, server_size) == -1) {
        handle_error("bind");
    }

    puts("Server listening for connections...");

    input = (char *)malloc(sizeof(char) * INPUT_BUFFER_SIZE);
    result = (char *)malloc(sizeof(char) * OUTPUT_BUFFER_SIZE);

    while (1) {
        bzero(input, INPUT_BUFFER_SIZE);
        if (recvfrom(server_fd, input, INPUT_BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_size) == -1) {
            handle_error("recvfrom");
        }

        if (!strcmp(input, TERMINATION_PROMPT)) {
            break;
        }

        printf("[+]Data recv: %s\n", input);

        bzero(result, OUTPUT_BUFFER_SIZE);
        result = hammingCode(input);

        if (sendto(server_fd, result, strlen(result)+1, 0, (struct sockaddr *)&client_addr, client_size) == -1) {
            handle_error("sendto");
        }
        printf("[+]Data sent: %s\n", result);
    }

    free(input);
    free(result);

    if (close(server_fd) == -1) {
        handle_error("close");
    }

    puts("Terminating server...");

    return EXIT_SUCCESS;
}

void handle_error(const char *msg) {
    fprintf(stderr, "%s failed with error: %d", msg, errno);
    exit(EXIT_FAILURE);
}

char *hammingCode(const char *inputData) {
    char * result = (char *)malloc(sizeof(char) * OUTPUT_BUFFER_SIZE);

    int inputDataSize = strlen(inputData), errorBitsNum = 1;

    while (pow(2, errorBitsNum) < (inputDataSize + errorBitsNum + 1)) {
        errorBitsNum++;
    }

    int i=strlen(inputData)-1, j=0, count = 0, size = inputDataSize + errorBitsNum;

    while (j < size && i >= 0) {
        if (pow(2, count)-1 == j) {
            result[size - j - 1] = '0';
            j++;
            count++;
            continue;
        }
        result[size - j - 1] = inputData[i--];
        j++;
    }

    for (int i=0; i<errorBitsNum; i++) {
        int pos = pow(2, i);
        result[size-pos] = calculateParity(result, pos);
    }

    return result;
}

char calculateParity(const char *data, int position) {
    int parity = 0, size = strlen(data), idx = size - position;

    while (idx >= 0) {
        for (int i=0; i<position; i++) {
            parity ^= (data[idx--] - '0');
        }
        idx -= (position);
    }

    return parity + '0';
}
