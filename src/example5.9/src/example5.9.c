#include <inttypes.h>

#define ARLEN 10

int32_t ar[ARLEN], *ip;

ip = ar;
while (ip < &ar[ARLEN])
  *(ip++) = 0;
