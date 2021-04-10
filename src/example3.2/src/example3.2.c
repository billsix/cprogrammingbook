#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  int32_t input_c;

  /* The Classic Bit */
  while ((input_c = getchar()) != EOF) {
    printf("%c was read\n", input_c);
  }
  exit(EXIT_SUCCESS);
}
