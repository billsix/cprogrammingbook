#include <stdio.h>
#include <stdlib.h>

int main() {
  for (int i = 0; i <= 10; i++) {
    switch (i) {
    case 1:
    case 2:
      printf("1 or 2\n");
      break;
    case 7:
      printf("7\n");
      break;
    default:
      printf("default\n");
    }
  }
  exit(EXIT_SUCCESS);
}
