#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void handleSystemError(const char *error);
void handleCustomError(const char *error);
int validate(const char *data);
char *bitStuffing(const char *data);
char *bitUnstuffing(const char *data);

int main(int argc, char **argv) {
    if (argc != 2) {
        handleCustomError("Invalid syntax!\nSyntax: ./a.out <input>");
    }
    printf("Result: %s\n", bitStuffing(argv[1]));
    return EXIT_SUCCESS;
}

void handleSystemError(const char *error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void handleCustomError(const char *error) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
}

int validate(const char *data) {
    int size = strlen(data);
    for (int i=0; i<size; i++) {
        if (data[i] != '0' && data[i] != '1') {
            return 0;
        }
    }
    return 1;
}

char *bitStuffing(const char *data) {
    if (!validate(data)) {
        handleCustomError("Invalid data input");
    }

    int size = strlen(data);
    char *result = (char *)malloc(sizeof(char) * (2 * size + 1));
    if (result == NULL) {
        handleSystemError("malloc");
    }

    int i=0, j=0, count=0;

    while (data[i] != '\0') {
        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }
        result[j++] = data[i++];
        if (count == 5) {
            count = 0;
            result[j++] = '0';
        }
    }

    printf("Unstuffed data: %s\n", bitUnstuffing(result));

    return result;
}

char *bitUnstuffing(const char *data) {
    if (!validate(data)) {
        handleCustomError("Invalid data input");
    }
    
    size_t size = strlen(data);
    char *result = (char *)malloc(sizeof(char) * size);
    if (result == NULL) {
        handleSystemError("malloc");
    }

    int i=0, j=0, count=0;

    while (data[i] != '\0') {
        if (data[i] == '1') {
            count++;
        } else {
            count = 0;
        }
        result[j++] = data[i++];
        if (count == 5) {
            i++;
        }
    }
    
    return result;
}
