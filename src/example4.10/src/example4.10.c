#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int32_t callable();

int main(int argc, char *argv[]) {
  int32_t callable_val = callable();
  printf("%d\n", callable_val);
  exit(EXIT_SUCCESS);
}
