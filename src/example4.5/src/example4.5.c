#include <stdio.h>
#include <stdlib.h>

int a; /* visible from here onwards */

void func(void) {
  float a; /* a different 'a' */
  { char a; /* yet another 'a' */ }
  /* the float 'a' reappears */
}
/* the int 'a' reappears */

int main() {
  func();
  exit(EXIT_SUCCESS);
}
