#include "add.h"

static int add_internal(int a, int b) { return a + b; }

int add(int a, int b) { return add_internal(a, b); }
