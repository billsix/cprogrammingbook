#include <inttypes.h>

struct list_ele {
  int32_t data;
  struct list_ele *pointer;
} ar[3];

int main(int argc, char *argv[]) {

  ar[0].data = 5;
  ar[0].pointer = &ar[1];
  ar[1].data = 99;
  ar[1].pointer = &ar[2];
  ar[2].data = -7;
  ar[2].pointer = 0; /* mark end of list */
  return 0;
}
