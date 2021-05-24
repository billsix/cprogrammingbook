#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define ARSZ 20

int main(int argc, char *argv[]) {
  int32_t ar[ARSZ];
  for (size_t i = 0; i < ARSZ; i++) {
    ar[i] = i;
    i[ar]++;
    printf("ar[%d] now = %d\n", i, ar[i]);
  }

  printf("15[ar] = %d\n", 15 [ar]);
  exit(EXIT_SUCCESS);
}
