#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "messageBuffer.h"
#include "arrayDataType.h"


const key_t KEY = 1234;
const int NAME_DATA_TYPE = 1;
const int ROLL_DATA_TYPE = 2;


void readInput(char *string, char *inputText);
int sendMessage(int msgid, int type, char *text);
int receiveMessage(int msgid, int type, array *arr);
int sendData(int msgid, int N);
int receiveData(int msgid, int N, array *names, array *rolls);


int main(int argc, char **argv) {
	int msgid = msgget(KEY, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		return -1;
	}

	int N;
  printf("Enter the number of students: ");
  scanf("%d", &N);

  int c;
  do {
    c = getchar();
  }while(c != EOF && c != '\n');

  array names, rolls;
  createArray(&names, NAME_DATA_TYPE, N);
  createArray(&rolls, ROLL_DATA_TYPE, N);

  sendData(msgid, N);
  receiveData(msgid, N, &names, &rolls);

  printf("\nSorted names:\t");
  displayArray(&names);
  printf("Sorted rolls:\t");
  displayArray(&rolls);

  if (msgctl(msgid, IPC_RMID, 0) == -1) {
    fprintf(stderr, "msgctl failed with error: %d\n", errno);
    return -1;
  }

	return 0;
}

void readInput(char *string, char *inputText) {
	printf("%s", inputText);
  fgets(string, BUFFER_SIZE, stdin);
  string[strlen(string)-1] = '\0';
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

  if (type == 1) {
		if (msgrcv(msgid, (void *)&buf, BUFFER_SIZE, NAME_DATA_TYPE, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			return -1;
		}
    char *data = getText(&buf);
    insertArray(arr, (void *)data);
  } else {
    if (msgrcv(msgid, (void *)&buf, BUFFER_SIZE, ROLL_DATA_TYPE, 0) == -1) {
      fprintf(stderr, "msgrcv failed with error: %d\n", errno);
      return -1;
    }
    long int data = strtol(getText(&buf), NULL, 10);
    insertArray(arr, (void *)&data);
  }

  return 0;
}

int sendData(int msgid, int N) {
  char *name, *roll;
  name = (char *)malloc(sizeof(char) * BUFFER_SIZE);
  roll = (char *)malloc(sizeof(char) * BUFFER_SIZE);

  char numOfStudents[BUFFER_SIZE];
  sprintf(numOfStudents, "%d", N);

  sendMessage(msgid, NAME_DATA_TYPE, numOfStudents);
  sendMessage(msgid, ROLL_DATA_TYPE, numOfStudents);

  printf("\nEnter student details:\n");

  for (int i=0; i < N; i++) {
    printf("\n");
    readInput(name, "Enter name: ");
    readInput(roll, "Enter roll: ");

    sendMessage(msgid, NAME_DATA_TYPE, name);
    sendMessage(msgid, ROLL_DATA_TYPE, roll);
	}

  return 0;
}

int receiveData(int msgid, int N, array *names, array *rolls) {
  for (int i=0; i<N; i++) {
    receiveMessage(msgid, NAME_DATA_TYPE, names);
    receiveMessage(msgid, ROLL_DATA_TYPE, rolls);
  }

  return 0;
}
