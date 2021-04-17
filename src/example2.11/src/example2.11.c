#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  const int32_t i = 5;
  const int32_t j = 2;
  float f = 3.0;

  f = f + j / i;
  printf("value of f is %f\n", f);
  exit(EXIT_SUCCESS);
}
