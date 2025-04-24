#include "tests.h"

START_TEST(from_decimal_to_int_0) {
  s21_decimal number = {{123456, 0, 0, 0x00030000}};
  int res;

  ck_assert_int_eq(0, s21_from_decimal_to_int(number, &res));
  ck_assert_int_eq(res, 123);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal number = {{0XFFFFFFFF, 0, 0, 0x80050000}};
  int res;

  ck_assert_int_eq(0, s21_from_decimal_to_int(number, &res));
  ck_assert_int_eq(res, -42949);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal number = {{0X7FFFFFFF, 0, 0, 0x00000000}};
  int res;

  ck_assert_int_eq(0, s21_from_decimal_to_int(number, &res));
  ck_assert_int_eq(res, 2147483647);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal number = {{0XFFFFFFFF, 1, 0, 0x00000000}};
  int res;

  ck_assert_int_eq(1, s21_from_decimal_to_int(number, &res));
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal number = {{0XFFFFFFFF, 0, 0, 0x80000000}};
  int res;

  ck_assert_int_eq(1, s21_from_decimal_to_int(number, &res));
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  int res;

  ck_assert_int_eq(1, s21_from_decimal_to_int(number, &res));
}
END_TEST

START_TEST(from_decimal_to_int_6) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  int res;

  ck_assert_int_eq(0, s21_from_decimal_to_int(number, &res));
  ck_assert_int_eq(res, -1639);
}
END_TEST

Suite *test_from_decimal_to_int(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_INT=-\033[0m");
  TCase *tc = tcase_create("from_decimal_to_int_tc");

  tcase_add_test(tc, from_decimal_to_int_0);
  tcase_add_test(tc, from_decimal_to_int_1);
  tcase_add_test(tc, from_decimal_to_int_2);
  tcase_add_test(tc, from_decimal_to_int_3);
  tcase_add_test(tc, from_decimal_to_int_4);
  tcase_add_test(tc, from_decimal_to_int_5);
  tcase_add_test(tc, from_decimal_to_int_6);

  suite_add_tcase(s, tc);
  return s;
}