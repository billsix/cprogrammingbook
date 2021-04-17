/*
 *
 * Dumb program that generates prime numbers.
 */
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int32_t this_number = 3;

  while (this_number < 10000) {
    int32_t divisor = this_number / 2;
    bool not_prime = false;
    while (divisor > 1) {
      if (this_number % divisor == 0) {
        not_prime = true;
        divisor = 0;
      } else
        divisor = divisor - 1;
    }

    if (not_prime == false)
      printf("%d is a prime number\n", this_number);
    this_number = this_number + 1;
  }
  exit(EXIT_SUCCESS);
}
