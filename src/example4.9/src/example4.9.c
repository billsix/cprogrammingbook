#include <inttypes.h>

int i; /* definition */
int main() {
  void f_in_other_place(); /* declaration */
  i = 0;
  f_in_other_place();
  printf("i = %d\n", i);
  f_in_other_place();
  printf("i = %d\n", i);
  f_in_other_place();
  printf("i = %d\n", i);
}
