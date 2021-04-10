#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void called_func(int, float);

int main() {
  called_func(1, 2 * 3.5);
  exit(EXIT_SUCCESS);
}

void called_func(int32_t iarg, float farg) { float tmp = iarg * farg; }
