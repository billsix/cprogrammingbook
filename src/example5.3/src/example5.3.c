#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#define ARSZ 20

int main() {
  int32_t ar[ARSZ];
  for (int32_t i = 0; i < ARSZ; i++) {
    ar[i] = i;
    i[ar]++;
    printf("ar[%d] now = %d\n", i, ar[i]);
  }

  printf("15[ar] = %d\n", 15 [ar]);
  exit(EXIT_SUCCESS);
}
