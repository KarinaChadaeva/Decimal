#include "tests.h"

START_TEST(from_int_to_decimal_0) {
  int number = 1234567890;
  s21_decimal res;

  ck_assert_int_eq(0, s21_from_int_to_decimal(number, &res));
  ck_assert_int_eq(res.bits[0], 1234567890);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  int number = -1234567890;
  s21_decimal res;

  ck_assert_int_eq(0, s21_from_int_to_decimal(number, &res));
  ck_assert_int_eq(res.bits[0], 1234567890);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0X80000000);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  int number = 2147483647;
  s21_decimal res;

  ck_assert_int_eq(0, s21_from_int_to_decimal(number, &res));
  ck_assert_int_eq(res.bits[0], 2147483647);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  int number = -2147483648;
  s21_decimal res;

  ck_assert_int_eq(0, s21_from_int_to_decimal(number, &res));
  ck_assert_int_eq(res.bits[0], 2147483648);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0X80000000);
}
END_TEST

Suite *test_from_int_to_decimal(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_INT_TO_DECIMAL=-\033[0m");
  TCase *tc = tcase_create("from_int_to_decimal_tc");

  tcase_add_test(tc, from_int_to_decimal_0);
  tcase_add_test(tc, from_int_to_decimal_1);
  tcase_add_test(tc, from_int_to_decimal_2);
  tcase_add_test(tc, from_int_to_decimal_3);

  suite_add_tcase(s, tc);
  return s;
}