int small_val(void) {
  static unsigned count = 0;
  count++;
  return (count % 16);
}
