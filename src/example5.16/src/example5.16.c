#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void func(int);

int main(int argc, char *argv[]) {
  void (*fp)(int) = func;

  (*fp)(1);
  fp(2);

  exit(EXIT_SUCCESS);
}

void func(int32_t arg) { printf("%d\n", arg); }
