#ifndef SORT

#define SORT

#include "arrayDataType.h"

int compareString(char *str1, char *str2);
int compareLong(long int num1, long int num2);
int compare(void *leftArrData, void *rightArrData, int type);
void merge(array *a, int left, int mid, int right);
void mergeSort(array *a, int left, int right);
void sort(array *a);

int compareString(char *str1, char *str2) {
  return strcmp(str1, str2);
}

int compareLong(long int num1, long int num2) {
  if (num1 > num2) {
    return 1;
  } else if (num1 < num2) {
    return -1;
  } else {
    return 0;
  }
}

int compare(void *leftArrData, void *rightArrData, int type) {
  if (type == 1) {
    return compareString((char *)leftArrData, (char *)rightArrData);
  } else {
    return compareLong(*(long int*)leftArrData, *(long int*)rightArrData);
  }
}

void merge(array *a, int left, int mid, int right) {
  int i, j, k;
  size_t n1 = mid - left + 1;
  size_t  n2 = right - mid;

  array leftArr, rightArr;
  createArray(&leftArr, a->dataType, n1);
  createArray(&rightArr, a->dataType, n2);

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
    if (compare(leftArrData, rightArrData, a->dataType) < 0) {
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

void mergeSort(array *a, int left, int right) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);

    merge(a, left, mid, right);
  }
}

void sort(array *a) {
  mergeSort(a, 0, getArraySize(a)-1);
}

#endif // !SORT
