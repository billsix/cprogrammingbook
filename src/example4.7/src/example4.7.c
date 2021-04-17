#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  void changer(int);

  int32_t i = 5;
  printf("before i=%d\n", i);
  changer(i);
  printf("after i=%d\n", i);
  exit(EXIT_SUCCESS);
}

void changer(int32_t x) {
  while (x) {
    printf("changer: x=%d\n", x);
    x--;
  }
}
