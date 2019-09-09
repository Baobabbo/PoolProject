//------------------------------------------------
//  UTILS.C - implementation of additional functions
//------------------------------------------------
#include "utils.h"

void sleeping(void) {
  struct timespec t;
  t.tv_sec = 0;
  t.tv_nsec = 1000;
  nanosleep(&t, NULL);
}

void reset(char *tmp) {
  for (int i = 0; i < 255; i++) {
    tmp[i] = 0;
  }
}

// Reverse the string
void reverse(char str[], int length) {
  int start = 0;
  int end = length - 1;
  char aux;
  while (start < end) {
    aux = str[start];
    str[start] = str[end];
    str[end] = aux;
    start++;
    end--;
  }
}

// int to ascii
char *itoa(int num, char *str, int base) {
  int i = 0;
  int isNegative = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  if (num < 0 && base == 10) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (isNegative)
    str[i++] = '-';

  str[i] = '\0';

  reverse(str, i);
  return str;
}
