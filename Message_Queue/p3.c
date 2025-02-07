#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "buffer.h"


const key_t KEY = 1234;
const int MSG_TO_RECEIVE = 2;


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

	for (int i; i<N; i++) {
		if (msgrcv(msgid, (void *)&buf, BUF_SIZE, MSG_TO_RECEIVE, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			return -1;
		}

    printf("%s\n", getText(&buf));
	}

	return 0;
}
