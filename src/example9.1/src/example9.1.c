#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  size_t distance;
  struct x {
    int a, b, c;
  } s_tr;

  distance = offsetof(struct x, c);
  printf("Offset of x.c is %lu bytes\n", (unsigned long)distance);

  exit(EXIT_SUCCESS);
}
