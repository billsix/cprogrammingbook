#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  const size_t sz = sizeof(sz);
  printf("size of sizeof is %lu\n", (unsigned long)sz);
  exit(EXIT_SUCCESS);
}
