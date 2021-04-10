#include <inttypes.h>

extern int32_t i;         /* declaration */
void f_in_other_place() { /* definition */
  i++;
}
