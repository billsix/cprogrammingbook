#include <inttypes.h>

struct x; /* incomplete type */

/* valid uses of the tag */
struct x *p, func();

void f1() {
  struct x {
    int32_t i;
  }; /* redeclaration! */
}

/* full declaration now */
struct x {
  float f;
} s_x;

void f2() {
  /* valid statements */
  p = &s_x;
  *p = func();
  s_x = func();
}

struct x func() {
  struct x tmp;
  tmp.f = 0;
  return tmp;
}
