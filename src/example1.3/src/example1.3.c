#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int32_t ch = getchar();
  while (ch != 'a') {
    if (ch != '\n')
      printf("ch was %c, value %d\n", ch, ch);
    ch = getchar();
  }
  exit(EXIT_SUCCESS);
}
