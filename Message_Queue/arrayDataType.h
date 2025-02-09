#ifndef ARRAY

#define ARRAY

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int STRING_SIZE = 33;

typedef struct Array {
  size_t length, capacity;
  int dataType;
  union {
    long int *numbers;
    char **strings;
  }data;
} array; 

void createArray(array *a, int type, int size);
void setArrayNumber(array *a, size_t idx, long int num);
void setArrayString(array *a, size_t idx, char *str);
char *getArrayString(array *a, size_t idx);
long int getArrayNumber(array *a, size_t idx);
void *getArrayElement(array *a, size_t idx);
void insertArray(array *a, void *data);
void replaceAtPosArray(array *a, void *data, size_t pos);
int getArraySize(array *a);
void displayStringArray(array *a);
void displayNumberArray(array *a);
void displayArray(array *a);
void destroyArray(array *a);

void createArray(array *a, int type, int size) {
  a->capacity = size;
  a->length = 0;
  a->dataType = type;
  if (type == 1) {
    a->data.strings = (char **)malloc(sizeof(char *) * a->capacity);
  } else {
    a->data.numbers = (long int *)malloc(sizeof(long int) * a->capacity);
  }
}

void setArrayNumber(array *a, size_t idx, long int num) {
  a->data.numbers[idx] = num;
}

void setArrayString(array *a, size_t idx, char *str) {
  if (strlen(str) >= STRING_SIZE) {
    return;
  }
  a->data.strings[idx] = (char *)malloc(sizeof(char) * STRING_SIZE);
  strcpy(a->data.strings[idx], str);
}

char *getArrayString(array *a, size_t idx) {
  return a->data.strings[idx];
}

long int getArrayNumber(array *a, size_t idx) {
  return a->data.numbers[idx];
}

void *getArrayElement(array *a, size_t idx) {
  if (idx >= a->length) {
    return NULL;
  }
  if (a->dataType == 1) {
    char *result = (char *)malloc(sizeof(char) * STRING_SIZE);
    strcpy(result, getArrayString(a, idx));
    return (void *)result;
  } else {
    long int *result = (long int *)malloc(sizeof(long int));
    *result = getArrayNumber(a, idx);
    return (void *)result;
  }
}

void insertArray(array *a, void *data) {
  if (a->length == a->capacity) {
    return;
  }
  if (a->dataType == 1) {
    setArrayString(a, a->length++, (char *)data);
  } else {
    setArrayNumber(a, a->length++, *((long int *)data));
  }
}

void replaceAtPosArray(array *a, void *data, size_t pos) {
  if (pos >= a->length) {
    return;
  }
  if (a->dataType == 1) {
    setArrayString(a, pos, (char *)data);
  } else {
    setArrayNumber(a, pos, *(long int *)data);
  }
}

int getArraySize(array *a) {
  return a->length;
}

void displayStringArray(array *a) {
  for (int i=0; i<a->length; i++) {
    printf("%s\t", a->data.strings[i]);
  }
  printf("\n");
}

void displayNumberArray(array *a) {
  for (int i=0; i<a->length; i++) {
    printf("%ld\t", a->data.numbers[i]);
  }
  printf("\n");
}

void displayArray(array *a) {
  if (a->dataType == 1) {
    displayStringArray(a);
  } else {
    displayNumberArray(a);
  }
}

void destroyArray(array *a) {
  if (a->dataType == 1) {
    free(a->data.strings);
  } else {
    free(a->data.numbers);
  }
  a->dataType = 0;
  a->length = 0;
  a->capacity = 0;
}

#endif // !ARRAY
