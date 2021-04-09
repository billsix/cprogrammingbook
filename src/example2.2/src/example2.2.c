#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define BOILING 212 /* degrees Fahrenheit */

int main() {
  int i = 0;
  printf("Fahrenheit to Centigrade\n");
  while (i <= BOILING) {
    long double l_d_var = 5 * (i - 32);
    l_d_var = l_d_var / 9;
    const double d_var = l_d_var;
    const float f_var = l_d_var;
    printf("%d %f %f %Lf\n", i, f_var, d_var, l_d_var);
    i = i + 1;
  }
  exit(EXIT_SUCCESS);
}
