#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  const size_t sz = sizeof(sz);
  printf("size of sizeof is %lu\n", (unsigned long)sz);
  exit(EXIT_SUCCESS);
}
