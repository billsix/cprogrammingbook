#include <inttypes.h>


/* example library module */
/* only 'callable' is visible outside */
static int32_t buf[100];
static int32_t length;
static void fillup();

int32_t callable() {
  if (length == 0) {
    fillup();
  }
  return buf[length--];
}

static void fillup() {
  while (length < 100) {
    buf[length++] = 0;
  }
}
