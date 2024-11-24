#ifndef MYHEADER

#include <stdbool.h>

typedef struct {
  bool flag;
} buffer;

void buf_init(buffer *b);
bool getFlag(buffer *b);
void changeFlag(buffer *b);

#endif // !MYHEADER

void buf_init(buffer *b) {
  b->flag = true;
}

bool getFlag(buffer *b) {
  return b->flag;
}

void changeFlag(buffer *b) {
  b->flag = !(b->flag);
  return;
}
