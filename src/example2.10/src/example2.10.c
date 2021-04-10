#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int32_t a, b;
  a = b = 5;
  printf("%d\n", ++a + 5);
  printf("%d\n", a);
  printf("%d\n", b++ + 5);
  printf("%d\n", b);
  exit(EXIT_SUCCESS);
}
