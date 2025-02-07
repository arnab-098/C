#ifndef SORT

#include "array.h"

#define type(x) _Generic((x),
    char *: "char", long: "long")

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

#endif // !SORT

int compareString(char *str1, char *str2) {
  return strcmp(str1, str2);
}

int compareLong(long num1, long num2) {
  if (num1 > num2) {
    return 1;
  } else if (num1 < num2) {
    return -1;
  } else {
    return 0;
  }
}

int compare(void *data1, void *data2) {
  if (type(data1) == "long") {
    return compareLong(data1, data2);
  } else {
    return compareString(data1, data2);
  }
}

void merge(array a, int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  array leftArr, rightArr;
  create(&leftArr);
  create(&rightArr);

  for (i = 0; i < n1; i++) {
    insert(&leftArr, get(&a, left+i));
  }
  for (j = 0; j < n2; j++) {
    insert(&rightArr, get(&a, mid+1+j));
  }

  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (compre(get(&leftArr, i), get(&rightArr, j))) {
      insert(&a, get(&leftArr, i));
      i++;
    }
    else {
      insert(&a, get(&rightArr, j));
      j++;
    }
    k++;
  }

  while (i < n1) {
    insert(&a, get(&leftArr, i));
    i++;
    k++;
  }

  while (j < n2) {
    insert(&a, get(&rightArr, j));
    j++;
    k++;
  }
}

void mergeSort(array a, int left, int right) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(a, mid + 1, right);

    merge(a, left, mid, right);
  }
}

