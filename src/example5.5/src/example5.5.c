#include <stdio.h>
#include <inttypes.h>
#define ARSZ 10

int main() {
  float fa[ARSZ], *fp1, *fp2;

  fp1 = fp2 = fa; /* address of first element */
  while (fp2 != &fa[ARSZ]) {
    printf("Difference: %ld\n", (long)(fp2 - fp1));
    fp2++;
  }
  return 0;
}
