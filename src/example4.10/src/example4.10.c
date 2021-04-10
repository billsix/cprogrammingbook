#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int32_t callable();

int main() {
  int32_t callable_val = callable();
  printf("%d\n", callable_val);
  exit(EXIT_SUCCESS);
}
