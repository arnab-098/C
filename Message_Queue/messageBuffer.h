#ifndef BUFFER

#include <string.h>

#define BUF_SIZE 100

typedef struct Buffer {
	long mtype;
	char mtext[BUF_SIZE];
} buffer;

int set_buf(buffer *b, long type, char *text);

#endif //!BUFFER

int set_buf(buffer *b, long type, char *text) {
	if (strlen(text) >= BUF_SIZE) {
		return -1;
	}
	b->mtype = type;
	strcpy(b->mtext, text);
	return 0;
}

char *getText(buffer *b) {
  return b->mtext;
}
