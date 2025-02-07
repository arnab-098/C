#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "buffer.h"


const key_t KEY = 1234;

char *readInput(char *inputText) {
  char *string = (char *)malloc(sizeof(char) * BUF_SIZE);
	printf("%s", inputText);
  fgets(string, BUF_SIZE, stdin);
  string[strlen(string)-1] = '\0';
  return string;
}

int sendMessage(int msgid, int type, char *text) {
  buffer buf;

  if (set_buf(&buf, (long)type, text) == -1) {
		fprintf(stderr, "buffer overflow detected\n");
    exit(1);
  }
	if (msgsnd(msgid, (void *)&buf, BUF_SIZE, 0) == -1) {
		fprintf(stderr, "msgsnd failed with error: %d\n", errno);
    exit(1);
	}

  return 0;
} 

int sendData(int msgid, int N) {
  char *name, *roll;

  char numOfStudents[BUF_SIZE];
  sprintf(numOfStudents, "%d", N);

  sendMessage(msgid, 1, numOfStudents);
  sendMessage(msgid, 2, numOfStudents);

  printf("\nEnter student details:\n");

  for (int i=0; i < N; i++) {
    printf("\n");
    name = readInput("Enter name: ");
    roll = readInput("Enter roll: ");

    sendMessage(msgid, 1, name);
    sendMessage(msgid, 2, roll);
	}

  return 0;
}

int receiveData(int msgid, int N) {
  return 0;
}

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

  sendData(msgid, N);
  receiveData(msgid, N);

  if (msgctl(msgid, IPC_RMID, 0) == -1) {
    fprintf(stderr, "msgctl failed with error: %d\n", errno);
    return -1;
  }

	return 0;
}
