#ifndef ARRAY

#define ARRAY

#include <stdlib.h>

#define ARRAY_MIN_CAP 32

typedef struct Array {
  size_t size, capacity;
  void **buf;
} array; 

void createArray(array *a);
void setArray(array *a, size_t idx, void *data);
void *getArrayElement(array *a, size_t idx);
void insertArray(array *a, void *data);
void replaceAtPosArray(array *a, void *data, size_t pos);
int getArraySize(array *a);
void destroyArray(array *a);

void createArray(array *a) {
  a->capacity = ARRAY_MIN_CAP;
  a->size = 0;
  a->buf = malloc(sizeof(*a->buf) * a->capacity);
}

void setArray(array *a, size_t idx, void *data) {
  a->buf[idx] = data;
}

void *getArrayElement(array *a, size_t idx) {
  if (idx >= a->size) {
    return NULL;
  }
  return a->buf[idx];
}

void insertArray(array *a, void *data) {
  if (a->size == a->capacity) {
    a->capacity *= 2;
    a->buf = realloc(a->buf, sizeof(*a->buf) * a->capacity);
  }
  setArray(a, a->size, data);
  (a->size)++;
}

void replaceAtPosArray(array *a, void *data, size_t pos) {
  if (pos >= a->size) {
    return;
  }
  setArray(a, pos, data);
}

int getArraySize(array *a) {
  return a->size;
}

void destroyArray(array *a) {
  free(a->buf);
  a->size = 0;
  a->capacity = 0;
}

#endif // !ARRAY
