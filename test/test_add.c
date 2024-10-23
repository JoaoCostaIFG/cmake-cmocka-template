#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// IMPORTANT: cmocka needs the imports above
#include <cmocka.h>

#include "add.h"

static void test_add(void **state) {
  // given
  int a = 2, b = 4;
  int expected_result = 6;

  // when
  int result = add(a, b);

  // then
  assert_int_equal(expected_result, result);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_add),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
