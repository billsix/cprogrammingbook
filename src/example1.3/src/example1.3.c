#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char ch = getchar();
  while (ch != 'a') {
    if (ch != '\n')
      printf("ch was %c, value %d\n", ch, ch);
    ch = getchar();
  }
  exit(EXIT_SUCCESS);
}
