#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// IMPORTANT: cmocka needs the imports above
#include <cmocka.h>

#include <stdio.h>

#include "add3.h"

int __wrap_add(int a, int b);

int __wrap_add(int a, int b) {
  printf("------\nHELLO FROM __wrap_add\n------\n");
  check_expected(a);
  check_expected(b);
  return (int)mock();
}

static void test_add3_mock(void **state) {
  // given
  int a = 1, b = 2, c = 4;
  int expected_result = 7;
  int result;

  expect_value(__wrap_add, a, 1);
  expect_value(__wrap_add, b, 2);
  will_return(__wrap_add, 3);

  // when
  result = add3(a, b, c);

  // then
  assert_int_equal(expected_result, result);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_add3_mock),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
