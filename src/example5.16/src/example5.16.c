#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void func(int);

int main() {
  void (*fp)(int) = func;

  (*fp)(1);
  fp(2);

  exit(EXIT_SUCCESS);
}

void func(int32_t arg) { printf("%d\n", arg); }
