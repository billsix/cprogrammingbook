#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  void pmax(int32_t first, int32_t second); /*declaration*/
  for (int32_t i = -10; i <= 10; i++) {
    for (int32_t j = -10; j <= 10; j++) {
      pmax(i, j);
    }
  }
  exit(EXIT_SUCCESS);
}

void pmax(int32_t a1, int32_t a2) { /*definition*/
  int32_t biggest;

  if (a1 > a2) {
    biggest = a1;
  } else {
    biggest = a2;
  }

  printf("largest of %d and %d is %d\n", a1, a2, biggest);
}
