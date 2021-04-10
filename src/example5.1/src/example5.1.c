#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  int32_t x;

  int32_t *p = &x; /* initialise pointer */
  *p = 0;      /* set x to zero */
  printf("x is %d\n", x);
  printf("*p is %d\n", *p);

  *p += 1; /* increment what p points to */
  printf("x is %d\n", x);

  (*p)++; /* increment what p points to */
  printf("x is %d\n", x);

  exit(EXIT_SUCCESS);
}
