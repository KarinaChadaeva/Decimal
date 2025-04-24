#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <limits.h>

#include "../s21_decimal.h"

// arithmetics
Suite *test_add(void);
Suite *test_sub(void);
Suite *test_mul(void);
Suite *s21_div_suite(void);

// comparisons
Suite *test_comparisons(void);

// converters
Suite *test_from_decimal_to_int(void);
Suite *test_from_int_to_decimal(void);
Suite *test_from_decimal_to_float(void);
Suite *test_from_float_to_decimal(void);

// others
Suite *test_floor(void);
Suite *test_round(void);
Suite *test_truncate(void);
Suite *test_negate(void);

#endif
