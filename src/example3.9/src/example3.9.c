#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  for (int32_t i = 0; i <= 10; i++) {
    printf((i & 1) ? "odd\n" : "even\n");
  }
  exit(EXIT_SUCCESS);
}
