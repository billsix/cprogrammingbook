/*
 * Recursive descent parser for simple C expressions.
 * Very little error checking.
 */

#include <stdio.h>
#include <stdlib.h>

int expr();
int mul_exp();
int unary_exp();
int primary();

int main() {
  for (;;) {
    printf("expression: ");
    int val = expr();
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

int expr() {
  int val = mul_exp();
  for (;;) {
    const int ch_in = getchar();
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

int mul_exp() {
  int val = unary_exp();
  for (;;) {
    const int ch_in = getchar();
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

int unary_exp() {
  int val;

  const int ch_in = getchar();
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

int primary() {
  int val;

  const int ch_in = getchar();
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
