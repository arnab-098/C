#ifndef BUFFER

#define BUFFER

#include <string.h>

#define BUFFER_SIZE 100

typedef struct Buffer {
	long mtype;
	char mtext[BUFFER_SIZE];
} buffer;

int setBuffer(buffer *b, long type, char *text);
char *getText(buffer *b);

int setBuffer(buffer *b, long type, char *text) {
	if (strlen(text) >= BUFFER_SIZE) {
		return -1;
	}
	b->mtype = type;
	strcpy(b->mtext, text);
	return 0;
}

char *getText(buffer *b) {
  return b->mtext;
}

#endif //!BUFFER
