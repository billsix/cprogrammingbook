#include <inttypes.h>

struct list_ele *sortfun(struct list_ele *list) {

  struct list_ele dummy;

  /*
   * Algorithm is this:
   * Repeatedly scan list.
   * If two list items are out of order,
   * link them in the other way round.
   * Stop if a full pass is made and no
   * exchanges are required.
   * The whole business is confused by
   * working one element behind the
   * first one of interest.
   * This is because of the simple mechanics of
   * linking and unlinking elements.
   */

  dummy.pointer = list;
  do {
    int32_t exchange = 0;
    struct list_ele *thisp;
    thisp = &dummy;

    struct list_ele *nextp;

    while ((nextp = thisp->pointer) && nextp->pointer) {
      if (nextp->data < nextp->pointer->data) {
        /* exchange */
        exchange = 1;
        thisp->pointer = nextp->pointer;
        nextp->pointer = thisp->pointer->pointer;
        thisp->pointer->pointer = nextp;
      }
      thisp = thisp->pointer;
    }
  } while (exchange);

  return dummy.pointer;
}
