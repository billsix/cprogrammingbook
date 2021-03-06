#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

FILE *temp_file;
void leave(int sig);

int main(int argc, char *argv[]) {
  signal(SIGINT, leave);
  temp_file = fopen("tmp", "w");
  for (;;) {
    /*
     * Do things....
     */
    printf("Ready...\n");
    getchar();
  }
  /* can't get here ... */
  exit(EXIT_SUCCESS);
}

/*
 * on receipt of SIGINT, close tmp file
 * but beware - calling library functions from a
 * signal handler is not guaranteed to work in all
 * implementations.....
 * this is not a strictly conforming program
 */

void leave(int sig) {
  fprintf(temp_file, "\nInterrupted..\n");
  fclose(temp_file);
  exit(sig);
}
