#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char input_c;

  /* The Classic Bit */
  while ((input_c = getchar()) != EOF) {
    printf("%c was read\n", input_c);
  }
  exit(EXIT_SUCCESS);
}
