#include "add3.h"
#include "add.h"

int add3(int a, int b, int c) {
  int a_plus_b = add(a, b);
  return a_plus_b + c;
}
