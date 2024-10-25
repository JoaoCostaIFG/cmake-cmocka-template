#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
// IMPORTANT: cmocka needs the imports above
#include <cmocka.h>
#include <stdio.h>

#include "utils.h"

#include "add.c"

static int add_internal_mock(int a, int b)
{
	printf("Hello from add_internal_mock\n");
	check_expected(a);
	check_expected(b);
	return mock_type(int);
}

/*
 * This example is important/interesting.
 * We are testing a file that has a static function, add_internal, used by a
 * non-static function, add.
 * We will mock the static add_internal function too return the product of
 * a and b, instead of the sum.
 */
static void test_add_mock_add_internal(void **state)
{
	// given
	int a = 2, b = 4;
	int expected_result = a * b;
	int result;

	expect_value(add_internal_mock, a, a);
	expect_value(add_internal_mock, b, b);
	will_return(add_internal_mock, expected_result);

	hotpatch((void *)&add_internal, (void *)&add_internal_mock);

	// when
	result = add(a, b);

	// then
	assert_int_equal(expected_result, result);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_add_mock_add_internal),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
