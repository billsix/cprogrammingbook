void r_func() {
  static int depth = 0;
  depth++;
  if (depth > 200) {
    printf("excessive recursion\n");
    exit(1);
  } else {
    /* do usual thing,
     * not shown here.
     * This last action
     * occasionally results in another
     * call on r_func()
     */
    x_func();
  }
  depth--;
}
