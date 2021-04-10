#include <inttypes.h>

struct s_1; /* incomplete type */

struct s_2 {
  int32_t something;
  struct s_1 *sp;
};

struct s_1 { /* now the full declaration */
  float something;
  struct s_2 *sp;
};
