#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  /* initialise */
  int32_t i = 0;
  /* check */
  while (i <= 10) {
    printf("%d\n", i);
    /* update */
    i++;
  }
  exit(EXIT_SUCCESS);
}
