#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;

  /* initialise */
  i = 0;
  /* check */
  while (i <= 10) {
    printf("%d\n", i);
    /* update */
    i++;
  }
  exit(EXIT_SUCCESS);
}
