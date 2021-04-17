#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char c = 'a';
  while (c <= 'z') {
    printf("value %d char %c\n", c, c);
    c = c + 1;
  }

  exit(EXIT_SUCCESS);
}
