#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  for (int32_t i = 0; i < 10000; i++) {
    if (getchar() == 's')
      break;
    printf("%d\n", i);
  }
  exit(EXIT_SUCCESS);
}
