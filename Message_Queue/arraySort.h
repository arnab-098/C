#ifndef SORT

#include "arrayDataType.h"

int compareString(char *str1, char *str2);
int compareLong(long *num1, long *num2);
int compare(void *data1, void *data2);
void merge(array *a, int left, int mid, int right);
void mergeSort(array *a, int left, int right);
void sort(array *a);

#endif // !SORT

int compareString(char *str1, char *str2) {
  return strcmp(str1, str2);
}

int compareLong(long *num1, long *num2) {
  if (*num1 > *num2) {
    return 1;
  } else if (*num1 < *num2) {
    return -1;
  } else {
    return 0;
  }
}

int compare(void *data1, void *data2) {
  if (strtol((char *)data1, NULL, 10) == ERANGE) {
    return compareString(data1, data2);
  } else {
    return compareLong(data1, data2);
  }
}

void merge(array *a, int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  array leftArr, rightArr;
  createArray(&leftArr);
  createArray(&rightArr);

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
    if (compare(getArray(&leftArr, i), getArray(&rightArr, j))) {
      insertArray(a, getArray(&leftArr, i));
      i++;
    }
    else {
      insertArray(a, getArray(&rightArr, j));
      j++;
    }
    k++;
  }

  while (i < n1) {
    insertArray(a, getArray(&leftArr, i));
    i++;
    k++;
  }

  while (j < n2) {
    insertArray(a, getArray(&rightArr, j));
    j++;
    k++;
  }
}

void mergeSort(array *a, int left, int right) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);

    merge(a, left, mid, right);
  }
}

void sort(array *a) {
  mergeSort(a, 0, a->size-1);
}
