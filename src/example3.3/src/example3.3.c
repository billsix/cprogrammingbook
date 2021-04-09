#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  /* initialise */
  int i = 0;
  /* check */
  while (i <= 10) {
    printf("%d\n", i);
    /* update */
    i++;
  }
  exit(EXIT_SUCCESS);
}
