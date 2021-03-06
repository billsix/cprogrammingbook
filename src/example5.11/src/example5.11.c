#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 50 /* max no. of strings */
#define MAXLEN 80    /* max length. of strings */

void print_arr(const char *p_array[]);
void sort_arr(const char *p_array[]);
char *next_string();

int main(int argc, char *argv[]) {
  const char *p_array[MAXSTRING + 1];
  size_t nstrings = 0;

  while (nstrings < MAXSTRING && (p_array[nstrings] = next_string()) != 0) {

    nstrings++;
  }
  /* terminate p_array */
  p_array[nstrings] = 0;

  sort_arr(p_array);
  print_arr(p_array);
  exit(EXIT_SUCCESS);
}

void print_arr(const char *p_array[]) {
  for (size_t index = 0; p_array[index] != 0; index++)
    printf("%s\n", p_array[index]);
}

void sort_arr(const char *p_array[]) {

  for (size_t low_index = 0;
       p_array[low_index] != 0 && p_array[low_index + 1] != 0; low_index++) {

    for (size_t hi_index = low_index + 1; p_array[hi_index] != 0; hi_index++) {

      int32_t comp_val = strcmp(p_array[hi_index], p_array[low_index]);
      if (comp_val >= 0)
        continue;
      /* swap strings */
      const char *tmp = p_array[hi_index];
      p_array[hi_index] = p_array[low_index];
      p_array[low_index] = tmp;
    }
  }
}

char *next_string() {
  char *destination = (char *)malloc(MAXLEN);
  if (destination != 0) {
    char *cp = destination;

    char c;
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
