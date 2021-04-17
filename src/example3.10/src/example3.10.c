#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /* comma used - this loop has two counters */
  for (int32_t i = 0, j = 0; i <= 10; i++, j = i * i) {
    printf("i %d j %d\n", i, j);
  }

  /*
   * In this futile example, all but the last
   * constant value is discarded.
   * Note use of parentheses to force a comma
   * expression in a function call.
   */
  printf("Overall: %d\n", ("abc", 1.2e6, 4 * 3 + 2));
  exit(EXIT_SUCCESS);
}
