#include <stdio.h>

#include "add3.h"

int main(int argc, char **argv) {
  int a = 1, b = 2, c = 4;
  printf("%d + %d + %d = %d\n", a, b, c, add3(a, b, c));

  return 0;
}
