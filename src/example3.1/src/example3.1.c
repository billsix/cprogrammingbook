#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int32_t i = -10;
  while (i <= 5) {
    printf("value of i is %d, ", i);
    printf("i == 0 = %d, ", i == 0);
    printf("i > -5 = %d\n", i > -5);
    i++;
  }
  exit(EXIT_SUCCESS);
}
