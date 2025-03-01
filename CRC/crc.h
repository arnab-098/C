#ifndef CRC

#define CRC

void XOR(char *a, char *b);
void leftShift(char *str);
char *crc(char *data, char *divisor);

void XOR(char *a, char *b) {
  for (int i=0; i<strlen(a); i++) {
    a[i] = ((a[i] == b[i]) ? '0' : '1');
  }
}

void leftShift(char *str) {
  for (int i=0; i<strlen(str)-1; i++) {
    str[i] = str[i+1];
  }
}

char *crc(char *data, char *divisor) {
  int size = strlen(divisor);
  char *check_value = (char *)malloc(sizeof(char) * size);
  strncpy(check_value, data, size);
  int idx = size;
  while (idx <= strlen(data)) {
    if (check_value[0] == '1') {
      XOR(check_value, divisor);
    }
    leftShift(check_value);
    check_value[size-1] = data[idx++];
  }
  return check_value;
}

#endif //CRC
