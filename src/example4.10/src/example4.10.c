#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int32_t callable();

int main() {
  int32_t callable_val = callable();
  printf("%d\n", callable_val);
  exit(EXIT_SUCCESS);
}
