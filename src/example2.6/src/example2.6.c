#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  unsigned int x = 0;
  while (x >= 0) {
    printf("%u\n", x);
    x = x + 1;
  }

  exit(EXIT_SUCCESS);
}
