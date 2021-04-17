#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define ARSZ 10

int main(int argc, char *argv[]) {
  float fa[ARSZ], *fp1, *fp2;

  fp1 = fp2 = fa; /* address of first element */
  while (fp2 != &fa[ARSZ]) {
    printf("Difference: %d\n", (int)(fp2 - fp1));
    fp2++;
  }
  exit(EXIT_SUCCESS);
}
