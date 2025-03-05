#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

void calculateParity(int m[ROWS][COLS]) {
  // Calculate row parity
  for (int i = 0; i < ROWS-1; i++) {
    m[i][COLS-1] = 0;
    for (int j = 0; j < COLS-1; j++) {
      m[i][COLS-1] ^= m[i][j]; // XOR for parity calculation
    }
  }

  // Calculate column parity
  for (int j = 0; j < COLS; j++) {
    m[ROWS-1][j] = 0;
    for (int i = 0; i < ROWS-1; i++) {
      m[ROWS-1][j] ^= m[i][j]; // XOR for parity calculation
    }
  }
}

void populateMatrix(char *data, int m[ROWS][COLS]) {
  int idx = 0;
  for (int i=0; i<ROWS-1; i++) {
    for (int j=0; j<COLS-1; j++) {
      m[i][j] = data[idx++] - '0';
    }
  }
}

void printMatrix(int data[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%d ", data[i][j]);
    }
    printf("\n");
  }
}

int main() {
  char *data = "1011010111100011";

  int m[ROWS][COLS];

  populateMatrix(data, m);

  // Calculate parity bits
  calculateParity(m);

  printMatrix(m);

  return 0;
}

