#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void date(int32_t *, int32_t *); /* declare the function */

int main() {
  int32_t month, day;
  date(&day, &month);
  printf("day is %d, month is %d\n", day, month);
  exit(EXIT_SUCCESS);
}

void date(int32_t *day_p, int32_t *month_p) {
  int32_t day_ret, month_ret;
  /*
   * At this point, calculate the day and month
   * values in day_ret and month_ret respectively.
   */
  *day_p = day_ret;
  *month_p = month_ret;
}
