#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// IMPORTANT: cmocka needs the imports above
#include <cmocka.h>
#include <stdio.h>

int __wrap_add_internal(int a, int b) {
  printf("Hello from __wrap_add_internal");
  check_expected(a);
  check_expected(b);
  return mock_type(int);
}

#include "add.c"

static void test_add_internal_mock(void **state) {
  // given
  int a = 1, b = 0;
  int expected_result = 42;
  int result;

  expect_value(__wrap_add_internal, a, 1);
  expect_value(__wrap_add_internal, b, 0);
  will_return(__wrap_add_internal, 42);

  // when
  result = add(a, b);

  // then
  assert_int_equal(expected_result, result);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_add_internal_mock),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
