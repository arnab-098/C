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
const int MSG_TO_SEND = 1;
const int DATA_TYPE = 1;


int sendMessage(int msgid, int type, char *text);
int receiveMessage(int msgid, int type, array *arr);
int sendData(int msgid, int N, array *arr);
int receiveData(int msgid, int N, array *arr);


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
  createArray(&arr, DATA_TYPE, N);

  receiveData(msgid, N, &arr);

  printf("Received student names:\t");
  displayArray(&arr);

  printf("Sorting student name...\n");

  sort(&arr);

  printf("Sending sorted student names...\n");

  sendData(msgid, N, &arr);

  printf("Data sent. Ending program\n");

  destroyArray(&arr);

	return 0;
}

int sendMessage(int msgid, int type, char *text) {
  buffer buf;

  if (setBuffer(&buf, (long)type, text) == -1) {
		fprintf(stderr, "buffer overflow detected\n");
    exit(1);
  }
	if (msgsnd(msgid, (void *)&buf, BUFFER_SIZE, 0) == -1) {
		fprintf(stderr, "msgsnd failed with error: %d\n", errno);
    exit(1);
	}

  return 0;
} 

int receiveMessage(int msgid, int type, array *arr) {
  buffer buf;

  if (msgrcv(msgid, (void *)&buf, BUFFER_SIZE, MSG_TO_RECEIVE, 0) == -1) {
    fprintf(stderr, "msgrcv failed with error: %d\n", errno);
    return -1;
  }

  char *data = getText(&buf);
  insertArray(arr, (void *)data);

  return 0;
}

int sendData(int msgid, int N, array *arr) {
  char name[STRING_SIZE];

  for (int i=0; i < N; i++) {
    strcpy(name, (char *)getArrayElement(arr, i));
    sendMessage(msgid, MSG_TO_SEND, name);
	}

  return 0;
}

int receiveData(int msgid, int N, array *arr) {
	for (int i=0; i<N; i++) {
    receiveMessage(msgid, MSG_TO_RECEIVE, arr);
	}

  return 0;
}
