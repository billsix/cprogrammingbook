#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  for (int i = 0; i < 10000; i++) {
    if (getchar() == 's')
      break;
    printf("%d\n", i);
  }
  exit(EXIT_SUCCESS);
}
