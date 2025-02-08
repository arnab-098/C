#ifndef ARRAY

#define ARRAY

#include <stdlib.h>

#define ARRAY_MIN_CAP 32

typedef struct Array {
  size_t size, capacity;
  void **buf;
} array; 

void createArray(array *a, size_t dataSize);
void setArray(array *a, size_t idx, void *data);
void *getArray(array *a, size_t idx);
void insertArray(array *a, void *data);
void replaceAtPosArray(array *a, void *data, int pos);
int getArraySize(array *a);

void createArray(array *a, size_t dataSize) {
  a->capacity = ARRAY_MIN_CAP;
  a->size = 0;
  a->buf = malloc(dataSize * a->capacity);
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

void replaceAtPosArray(array *a, void *data, int pos) {
  if (pos >= a->size) {
    return;
  }
  setArray(a, pos, data);
}

int getArraySize(array *a) {
  return a->size;
}

#endif // !ARRAY
