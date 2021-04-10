#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int32_t a; /* visible from here onwards */

void func() {
  float a; /* a different 'a' */
  { char a; /* yet another 'a' */ }
  /* the float 'a' reappears */
}
/* the int32_t 'a' reappears */

int main() {
  func();
  exit(EXIT_SUCCESS);
}
