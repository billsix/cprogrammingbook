#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define ARSIZE 10

struct wp_char {
  char wp_cval;
  short wp_font;
  short wp_psize;
} ar[ARSIZE];

/*
 * type of the input function -
 * could equally have been declared above;
 * it returns a structure and takes no arguments.
 */
struct wp_char infun();

int main(int argc, char *argv[]) {
  size_t icount = 0;
  for (; icount < ARSIZE; icount++) {
    ar[icount] = infun();
    if (ar[icount].wp_cval == '\n') {
      /*
       * Leave the loop.
       * not incrementing icount means that the
       * '\n' is ignored in the sort
       */
      break;
    }
  }

  /* now a simple exchange sort */

  for (size_t lo_indx = 0; lo_indx <= icount - 2; lo_indx++)
    for (size_t hi_indx = lo_indx + 1; hi_indx <= icount - 1; hi_indx++) {
      if (ar[lo_indx].wp_cval > ar[hi_indx].wp_cval) {
        /*
         * Swap the two structures.
         */
        struct wp_char wp_tmp = ar[lo_indx];
        ar[lo_indx] = ar[hi_indx];
        ar[hi_indx] = wp_tmp;
      }
    }

  /* now print32_t */
  for (size_t lo_indx = 0; lo_indx < icount; lo_indx++) {
    printf("%c %d %d\n", ar[lo_indx].wp_cval, ar[lo_indx].wp_font,
           ar[lo_indx].wp_psize);
  }
  exit(EXIT_SUCCESS);
}

struct wp_char infun() {
  struct wp_char wp_char;

  wp_char.wp_cval = getchar();
  wp_char.wp_font = 2;
  wp_char.wp_psize = 10;

  return wp_char;
}
