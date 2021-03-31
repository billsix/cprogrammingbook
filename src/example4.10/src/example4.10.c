#include <stdio.h>
#include <stdlib.h>

int callable();

int main() {
  int callable_val = callable();
  printf("%d\n", callable_val);
  exit(EXIT_SUCCESS);
}
