#ifndef SORT

#define SORT

#include "arrayDataType.h"

int compareString(char *str1, char *str2);
int compareLong(long *num1, long *num2);
int compare(void *leftArrData, void *rightArrData, int type);
void merge(array *a, int left, int mid, int right, int type);
void mergeSort(array *a, int left, int right, int type);
void sort(array *a, const int type);

int compareString(char *str1, char *str2) {
  return strcmp(str1, str2);
}

int compareLong(long int *num1, long int *num2) {
  if (*num1 > *num2) {
    return 1;
  } else if (*num1 < *num2) {
    return -1;
  } else {
    return 0;
  }
}

int compare(void *leftArrData, void *rightArrData, int type) {
  if (type == 1) {
    return compareString(leftArrData, rightArrData);
  } else {
    return compareLong(leftArrData, rightArrData);
  }
}

void merge(array *a, int left, int mid, int right, int type) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  array leftArr, rightArr;
  createArray(&leftArr);
  createArray(&rightArr);

  for (i = 0; i < n1; i++) {
    insertArray(&leftArr, getArrayElement(a, left+i));
  }
  for (j = 0; j < n2; j++) {
    insertArray(&rightArr, getArrayElement(a, mid+1+j));
  }

  void *leftArrData, *rightArrData;

  i = 0;
  j = 0;
  k = left;

  while (i < n1 && j < n2) {
    leftArrData = getArrayElement(&leftArr, i);
    rightArrData = getArrayElement(&rightArr, j);
    if (compare(leftArrData, rightArrData, type) < 0) {
      replaceAtPosArray(a, leftArrData, k);
      i++;
    } else {
      replaceAtPosArray(a, rightArrData, k);
      j++;
    }
    k++;
  }

  while (i < n1) {
    leftArrData = getArrayElement(&leftArr, i);
    replaceAtPosArray(a, leftArrData, k);
    i++;
    k++;
  }

  while (j < n2) {
    rightArrData = getArrayElement(&rightArr, j);
    replaceAtPosArray(a, rightArrData, k);
    j++;
    k++;
  }

  destroyArray(&leftArr);
  destroyArray(&rightArr);
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
  mergeSort(a, 0, getArraySize(a)-1, type);
}

#endif // !SORT
