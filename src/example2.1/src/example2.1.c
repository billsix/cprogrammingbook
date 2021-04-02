#include <stdio.h>
#include <stdlib.h>

int f(void) {
  const float f_var = 1;
  double d_var = 1;
  long double l_d_var = 1;
  d_var = d_var + f_var;
  l_d_var = d_var + f_var;
  return l_d_var;
}

int main() {
  printf("f() evaluates to %f, \n", f());
  exit(EXIT_SUCCESS);
}
