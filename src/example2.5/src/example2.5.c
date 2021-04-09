#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
  char c = 'a';
  while (c <= 'z') {
    printf("value %d char %c\n", c, c);
    c = c + 1;
  }

  exit(EXIT_SUCCESS);
}
