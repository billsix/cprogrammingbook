#include <stdio.h>
#include <stdlib.h>
#define DELTA 0.0001

int main() {
  double sq_root(double); /* prototype */

  for (int i = 1; i < 100; i++) {
    printf("root of %d is %f\n", i, sq_root(i));
  }
  exit(EXIT_SUCCESS);
}

double sq_root(double x) { /* definition */
  double last_appx = x;
  double diff = DELTA + 1;

  double curr_appx;
  while (diff > DELTA) {
    curr_appx = 0.5 * (last_appx + x / last_appx);
    diff = curr_appx - last_appx;
    if (diff < 0)
      diff = -diff;
    last_appx = curr_appx;
  }
  return curr_appx;
}
