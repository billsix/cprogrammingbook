#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int main() {
  unsigned int stop_val = 0;
  int i = -10;

  while (i <= stop_val) {
    printf("%d\n", i);
    i = i + 1;
  }
  exit(EXIT_SUCCESS);
}
