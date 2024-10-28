#include <stdio.h>
#include <pthread.h>

typedef struct ArrayData {
  int *values;
  int start, end, order;
} arrayData;

void *threadFunction(void *args);
int findMin(int nums[], int start, int end);
int findMax(int nums[], int start, int end);
void swap(int nums[], int idx1, int idx2);
void create(arrayData *d, int arr[], int start, int end, int order);
void printArray(arrayData d);

int main(int argc, char *argv[]) {
  int n;
  printf("Enter the number of values: ");
  scanf("%d", &n);
  int arr[n];
  for (int i=0; i<n; i++) {
    printf("Enter arr[%d]: ", i);
    scanf("%d", &arr[i]);
  }
  
  arrayData d1, d2;
  create(&d1, arr, 0, n/2, 0);
  create(&d2, arr, n/2, n, 1);

  printf("\nInialially:\n");
  printArray(d1);
  printArray(d2);

  pthread_t th1, th2;
  pthread_create(&th1, NULL, threadFunction, (void *)&d1);
  pthread_create(&th2, NULL, threadFunction, (void *)&d2);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("\nFinally:\n");
  printArray(d1);
  printArray(d2);
  
  return 0;
}

void create(arrayData *d, int arr[], int start, int end, int order) {
  d->values = arr;
  d->start = start;
  d->end = end;
  d->order = order;
}

int findMin(int nums[], int start, int end) {
  int minValue = nums[start], index = start;
  for (int i=start; i<end; i++) {
    if (nums[i] < minValue) {
      minValue = nums[i];
      index = i;
    }
  }
  return index;
}

int findMax(int nums[], int start, int end) {
  int maxValue = nums[start], index = start;
  for (int i=start; i<end; i++) {
    if (nums[i] > maxValue) {
      maxValue = nums[i];
      index = i;
    }
  }
  return index;
}

void swap(int nums[], int idx1, int idx2) {
  int temp = nums[idx1];
  nums[idx1] = nums[idx2];
  nums[idx2] = temp;
}

void *threadFunction(void *args) {
  arrayData *d = (arrayData *)args;
  int i, j;
  for (int i=d->start; i<d->end-1; i++) {
    if (d->order == 0) {
      j = findMin(d->values, i, d->end);
    } else {
      j = findMax(d->values, i, d->end);
    }
    if (i != j) {
      swap(d->values, i, j);
    }
  }
  pthread_exit(NULL);
}

void printArray(arrayData d) {
  for (int i=d.start; i<d.end; i++) {
    printf("%d\t", d.values[i]);
  }
  printf("\n");
}
