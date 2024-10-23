#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// IMPORTANT: cmocka needs the imports above
#include <cmocka.h>
#include <stdio.h>

// We can include a C file directly to test static funcs
#include "add.c"

static void test_add_internal(void **state) {
  // given
  int a = 1, b = 0;
  int expected_result = 1;
  int result;

  // when
  result = add_internal(a, b);

  // then
  assert_int_equal(expected_result, result);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_add_internal),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
