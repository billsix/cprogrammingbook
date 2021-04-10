#include <inttypes.h>
#include <stdio.h>
#include <stdlib.hi>
#include <string.h>

#define MAXSTRING 50 /* max no. of strings */
#define MAXLEN 80    /* max length. of strings */

void print_arr(const char **p_array);
void sort_arr(const char **p_array);
char *next_string();

int main() {

  char **p_array = (char **)malloc(sizeof(char * [MAXSTRING + 1]));
  if (p_array == 0) {
    printf("No memory\n");
    exit(EXIT_FAILURE);
  }

  int32_t nstrings = 0; /* count of strings read */
  while (nstrings < MAXSTRING && (p_array[nstrings] = next_string()) != 0) {

    nstrings++;
  }
  /* terminate p_array */
  p_array[nstrings] = 0;

  sort_arr(p_array);
  print_arr(p_array);
  exit(EXIT_SUCCESS);
}

void print_arr(const char **p_array) {
  while (*p_array)
    printf("%s\n", *p_array++);
}

void sort_arr(const char **p_array) {

  for (const char **lo_p = p_array; *lo_p != 0 && *(lo_p + 1) != 0; lo_p++) {
    for (const char **hi_p = lo_p + 1; *hi_p != 0; hi_p++) {

      if (strcmp(*hi_p, *lo_p) >= 0)
        continue;
      /* swap strings */
      const char *tmp = *hi_p;
      *hi_p = *lo_p;
      *lo_p = tmp;
    }
  }
}

char *next_string() {

  char *destination = (char *)malloc(MAXLEN);
  if (destination != 0) {
    char *cp = destination;
    int32_t c;
    while ((c = getchar()) != '\n' && c != EOF) {
      if (cp - destination < MAXLEN - 1)
        *cp++ = c;
    }
    *cp = 0;
    if (c == EOF && cp == destination)
      return 0;
  }
  return destination;
}
