#include "module.h"

#include <stdio.h>

static int add_helper(int a, int b) { return a + b; }

int add(int a, int b) {
  printf("------\nHELLO FROM add\n------\n");
  return add_helper(a, b);
}

int add3(int a, int b, int c) {
  int a_plus_b = add(a, b);
  // return add(a_plus_b, c);
  return a_plus_b + c;
}
