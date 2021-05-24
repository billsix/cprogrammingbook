#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *cp = "a string";

  while (*cp != 0) {
    putchar(*cp);
    cp++;
  }
  putchar('\n');

  for (size_t i = 0; i < 8; i++)
    putchar("a string"[i]);
  putchar('\n');
  exit(EXIT_SUCCESS);
}
