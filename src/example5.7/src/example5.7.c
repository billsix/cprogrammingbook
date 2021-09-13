#include <inttypes.h>
#include <stdio.h>

/*
* Compare
  two strings for equality.
* Return 'false' if they are.
*/
int32_t str_eq(const char *s1, const char *s2) {
  while (*s1 == *s2) {
    /*
     * At end of string return 0.
     */
    if (*s1 == 0)
      return 0;
    s1++;
    s2++;
  }
  /* Difference detected! */
  return 1;
}

int main(int argc, char *argv[]) {

  char *str1 = "str1";
  char *str2 = "str2";
  char *str3 = "str1";

  printf("str1 compared to str2 is %d\n", str_eq(str1, str2));
  printf("str1 compared to str3 is %d\n", str_eq(str1, str3));
  printf("str2 compared to str3 is %d\n", str_eq(str2, str3));
}
