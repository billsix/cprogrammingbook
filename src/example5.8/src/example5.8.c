#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  char *cp = "a string";

  while (*cp != 0) {
    putchar(*cp);
    cp++;
  }
  putchar('\n');

  for (int i = 0; i < 8; i++)
    putchar("a string"[i]);
  putchar('\n');
  exit(EXIT_SUCCESS);
}
