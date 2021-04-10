#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  for (int32_t i = -10; i < 10; i++) {
    if (i == 0)
      continue;
    printf("%f\n", 15.0 / i);
    /*
     * Lots of other statements .....
     */
  }
  exit(EXIT_SUCCESS);
}
