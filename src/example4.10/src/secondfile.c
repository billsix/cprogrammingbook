/* example library module */
/* only 'callable' is visible outside */
static int buf[100];
static int length;
static void fillup();

int callable() {
  if (length == 0) {
    fillup();
  }
  return buf[length--];
}

static void fillup() {
  while (length < 100) {
    buf[length++] = 0;
  }
}
