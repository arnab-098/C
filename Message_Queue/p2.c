#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "messageBuffer.h"
#include "arrayDataType.h"
#include "arraySort.h"


const key_t KEY = 1234;
const long MSG_TO_RECEIVE = 1;
const int SORT_TYPE = 1;


int main(int argc, char **argv) {
	int msgid = msgget(KEY, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		return -1;
	}

	buffer buf;

	if (msgrcv(msgid, (void *)&buf, BUFFER_SIZE, MSG_TO_RECEIVE, 0) == -1) {
		fprintf(stderr, "msgrcv failed with error: %d\n", errno);
		return -1;
	}

  int N = atoi(getText(&buf));

  array arr;
  createArray(&arr);

	for (int i=0; i<N; i++) {
		if (msgrcv(msgid, (void *)&buf, BUFFER_SIZE, MSG_TO_RECEIVE, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			return -1;
		}
    char *data = getText(&buf);
    insertArray(&arr, (void *)data);
	}

  printf("Before sort:\t");
  for (int i=0; i<getArraySize(&arr); i++) {
    printf("%s\t", getArrayElement(&arr, i));
  }

  sort(&arr, SORT_TYPE);

  printf("\nAfter sort:\t");
  for (int i=0; i<getArraySize(&arr); i++) {
    printf("%s\t", getArrayElement(&arr, i));
  }

  printf("\nMemory addresses:\n");
  for (int i=0; i<getArraySize(&arr); i++) {
    printf("%p\n", getArrayElement(&arr, i));
  }

  destroyArray(&arr);

	return 0;
}
