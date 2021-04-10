#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int32_t i = 0;
  while (i <= 10) {
    printf("%d\n", i);
    i++;
  }

  /* the same done using ``for'' */
  for (int32_t j = 0; j <= 10; j++) {
    printf("%d\n", j);
  }
  exit(EXIT_SUCCESS);
}
