#define NDEBUG
#include <assert.h>

void func() {
  int c;
  assert((c = getchar()) != EOF);
  putchar(c);
}
