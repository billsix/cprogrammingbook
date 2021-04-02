int small_val() {
  static unsigned count = 0;
  count++;
  return count % 16;
}
