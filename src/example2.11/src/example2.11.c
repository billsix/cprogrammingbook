#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  const int i = 5;
  const int j = 2;
  float f = 3.0;

  f = f + j / i;
  printf("value of f is %f\n", f);
  exit(EXIT_SUCCESS);
}
