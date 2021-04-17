#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct s {
  int32_t a;
  char b;
  char *cp;
} ex_s = {1, 'a', "hello"};

int main(int argc, char *argv[]) {
  struct s first = ex_s;
  struct s second = {2, 'b', "byebye"};

  exit(EXIT_SUCCESS);
}
