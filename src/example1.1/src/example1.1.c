#include <inttypes.h>
#include <stdio.h>

/*
 * Tell the compiler that we intend
 * to use a function called show_message.
 * It has no arguments and returns no value
 * This is the "declaration".
 *
 */

void show_message();
/*
 * Another function, but this includes the body of
 * the function. This is a "definition".
 */
int main() {
  int32_t count = 0;
  while (count < 10) {
    show_message();
    count = count + 1;
  }

  return 0;
}

/*
 * The body of the simple function.
 * This is now a "definition".
 */
void show_message() { printf("hello\n"); }
