#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  unsigned int stop_val = 0;
  int i = -10;

  while (i <= stop_val) {
    printf("%d\n", i);
    i = i + 1;
  }
  exit(EXIT_SUCCESS);
}
