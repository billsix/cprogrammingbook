#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char c = CHAR_MIN;
  printf("%d\n", c);
  do {
    c = c + 1;
    printf("%d\n", c);
  } while (c != CHAR_MAX);

  exit(EXIT_SUCCESS);
}
