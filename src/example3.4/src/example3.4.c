#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  int i = 0;
  while (i <= 10) {
    printf("%d\n", i);
    i++;
  }

  /* the same done using ``for'' */
  for (int j = 0; j <= 10; j++) {
    printf("%d\n", j);
  }
  exit(EXIT_SUCCESS);
}
