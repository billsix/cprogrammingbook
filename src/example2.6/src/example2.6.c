#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned int x = 0;
  while (x >= 0) {
    printf("%u\n", x);
    x = x + 1;
  }

  exit(EXIT_SUCCESS);
}
