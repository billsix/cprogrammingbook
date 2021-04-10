#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define DOUBLE(x) ((x) + (x))

int main() {
  int32_t a[20], *ip;

  ip = a;
  a[0] = 1;
  a[1] = 2;
  printf("%d\n", DOUBLE(*ip++));
  exit(EXIT_SUCCESS);
}
