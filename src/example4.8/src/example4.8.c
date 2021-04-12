/*
 * Recursive descent parser for simple C expressions.
 * Very little error checking.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int32_t expr();
int32_t mul_exp();
int32_t unary_exp();
int32_t primary();

int main() {
  for (;;) {
    printf("expression: ");
    int32_t val = expr();
    if (getchar() != '\n') {
      printf("error\n");
      while (getchar() != '\n')
        ; /* NULL */
    } else {
      printf("result is %d\n", val);
    }
  }
  exit(EXIT_SUCCESS);
}

int32_t expr() {
  int32_t val = mul_exp();
  for (;;) {
    const char ch_in = getchar();
    switch (ch_in) {
    default:
      ungetc(ch_in, stdin);
      return val;
    case '+':
      val = val + mul_exp();
      break;
    case '-':
      val = val - mul_exp();
      break;
    }
  }
}

int32_t mul_exp() {
  int32_t val = unary_exp();
  for (;;) {
    const char ch_in = getchar();
    switch (ch_in) {
    default:
      ungetc(ch_in, stdin);
      return val;
    case '*':
      val = val * unary_exp();
      break;
    case '/':
      val = val / unary_exp();
      break;
    case '%':
      val = val % unary_exp();
      break;
    }
  }
}

int32_t unary_exp() {
  int32_t val;

  const char ch_in = getchar();
  switch (ch_in) {
  default:
    ungetc(ch_in, stdin);
    val = primary();
    break;
  case '+':
    val = unary_exp();
    break;
  case '-':
    val = -unary_exp();
    break;
  }
  return val;
}

int32_t primary() {
  int32_t val;

  const char ch_in = getchar();
  if (ch_in >= '0' && ch_in <= '9') {
    val = ch_in - '0';
    goto out;
  }
  if (ch_in == '(') {
    val = expr();
    getchar(); /* skip closing ')' */
    goto out;
  }
  printf("error: primary read %d\n", ch_in);
  exit(EXIT_FAILURE);
out:
  return val;
}
