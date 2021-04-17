#include <inttypes.h>

int32_t i; /* definition */
int main(int argc, char *argv[]) {
  void f_in_other_place(); /* declaration */
  i = 0;
  f_in_other_place();
  printf("i = %d\n", i);
  f_in_other_place();
  printf("i = %d\n", i);
  f_in_other_place();
  printf("i = %d\n", i);
}
