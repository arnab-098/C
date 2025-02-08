#ifndef ARRAY

#include <stdlib.h>

#define ARRAY_MIN_CAP 32

typedef struct Array {
  size_t size, capacity;
  void **buf;
} array; 

void createArray(array *a);
void setArray(array *a, size_t idx, const void *data);
void *getArray(array *a, size_t idx);
void insertArray(array *a, const void *data);

#endif // !ARRAY

void createArray(array *a) {
  a->capacity = ARRAY_MIN_CAP;
  a->size = 0;
  a->buf = malloc(sizeof(*a->buf) * a->capacity);
}

void setArray(array *a, size_t idx, void *data) {
  a->buf[idx] = data;
}

void *getArray(array *a, size_t idx) {
  return a->buf[idx];
}

void insertArray(array *a, void *data) {
  if (a->size == a->capacity) {
    a->capacity *= 2;
    a->buf = realloc(a->buf, sizeof(*a->buf) * a->capacity);
  }
  setArray(a, a->size++, data);
}
