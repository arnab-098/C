#ifndef ARRAY

#include <stdlib.h>

const int ARRAY_MIN_CAP = 32;

typedef struct Array {
  size_t size, capacity;
  void **buf;
}array; 

void create(array *a);
void set(array *a, size_t idx, const void *data);
void *get(array *a, size_t idx);
void insert(array *a, const void *data);

#endif // !ARRAY

void create(array *a) {
  array a;
  a->capacity = ARRAY_MIN_CAP;
  a->size = 0;
  a->buf = malloc(sizeof(*a->buf) * capacity);
  return a;
}

void set(array *a, size_t idx, const void *data) {
  a->buf[idx] = data;
}

void *get(array *a, size_t idx) {
  return a->buf[idx];
}

void insert(array *a, const void *data) {
  if (a->size == a->capacity) {
    a->capacity =* 2;
    a->buf = realloc(a->buf, sizeof(*a->buf) * a->capacity);
  }
  set(a, a->size++, data);
}
