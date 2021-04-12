#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int32_t comma_count = 0;
  int32_t stop_count = 0;
  char this_char = getchar();
  while (this_char != EOF) {
    if (this_char == '.')
      stop_count = stop_count + 1;
    if (this_char == ',')
      comma_count = comma_count + 1;
    this_char = getchar();
  }
  printf("%d commas, %d stops\n", comma_count, stop_count);
  exit(EXIT_SUCCESS);
}
