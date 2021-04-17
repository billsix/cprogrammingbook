#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

void func();
jmp_buf place;

int main(int argc, char *argv[]) {
  int retval;

  /*
   * First call returns 0,
   * a later longjmp will return non-zero.
   */
  if (setjmp(place) != 0) {
    printf("Returned using longjmp\n");
    exit(EXIT_SUCCESS);
  }

  /*
   * This call will never return - it
   * 'jumps' back above.
   */
  func();
  printf("What! func returned!\n");
}

void func() {
  /*
   * Return to main.
   * Looks like a second return from setjmp,
   * returning 4!
   */
  longjmp(place, 4);
  printf("What! longjmp returned!\n");
}
