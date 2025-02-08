#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "messageBuffer.h"
#include "arrayDataType.h"
#include "arraySort.h"


const key_t KEY = 1234;
const int MSG_TO_RECEIVE = 1;


int main(int argc, char **argv) {
	int msgid = msgget(KEY, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		return -1;
	}

	buffer buf;

	if (msgrcv(msgid, (void *)&buf, BUF_SIZE, MSG_TO_RECEIVE, 0) == -1) {
		fprintf(stderr, "msgrcv failed with error: %d\n", errno);
		return -1;
	}

  int N = atoi(getText(&buf));

  array arr;
  createArray(&arr);

	for (int i; i<N; i++) {
		if (msgrcv(msgid, (void *)&buf, BUF_SIZE, MSG_TO_RECEIVE, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			return -1;
		}

    insertArray(&arr, getText(&buf));
	}

  sort(&arr);

  for (int i=0; i<arr.size; i++) {
    printf("%s", getArray(&arr, i));
  }

	return 0;
}
