#ifndef SORT

#define SORT

#include "arrayDataType.h"

int compareString(char *str1, char *str2);
int compareLong(long *num1, long *num2);
int compare(void *data1, void *data2, int type);
void merge(array *a, int left, int mid, int right, int type);
void mergeSort(array *a, int left, int right, int type);
void sort(array *a, const int type);

int compareString(char *str1, char *str2) {
  return strcmp(str1, str2);
}

int compareLong(long int *num1, long int *num2) {
  if (*num1 > *num2) {
    printf("%ld is greater than %ld\n", *num1, *num2);
    return 1;
  } else if (*num1 < *num2) {
    printf("%ld is less than %ld\n", *num1, *num2);
    return -1;
  } else {
    printf("%ld is equal to %ld\n", *num1, *num2);
    return 0;
  }
}

int compare(void *data1, void *data2, int type) {
  if (type == 1) {
    return compareString(data1, data2);
  } else {
    return compareLong(data1, data2);
  }
}

void merge(array *a, int left, int mid, int right, int type) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  array leftArr, rightArr;
  createArray(&leftArr, sizeof(getArray(a, left)));
  createArray(&rightArr, sizeof(getArray(a, right)));

  for (i = 0; i < n1; i++) {
    insertArray(&leftArr, getArray(a, left+i));
  }
  for (j = 0; j < n2; j++) {
    insertArray(&rightArr, getArray(a, mid+1+j));
  }

  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (compare(getArray(&leftArr, i), getArray(&rightArr, j), type)) {
      replaceAtPosArray(a, getArray(&leftArr, i), k);
      i++;
    }
    else {
      replaceAtPosArray(a, getArray(&rightArr, j), k);
      j++;
    }
    k++;
  }

  while (i < n1) {
    replaceAtPosArray(a, getArray(&leftArr, i), k);
    i++;
    k++;
  }

  while (j < n2) {
    replaceAtPosArray(a, getArray(&rightArr, j), k);
    j++;
    k++;
  }
}

void mergeSort(array *a, int left, int right, int type) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    mergeSort(a, left, mid, type);
    mergeSort(a, mid + 1, right, type);

    merge(a, left, mid, right, type);
  }
}

void sort(array *a, const int type) {
  mergeSort(a, 0, a->size-1, type);
}

#endif // !SORT
