#include "tests.h"

START_TEST(negate_0) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_negate(number, &res));
  ck_assert_int_eq(res.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(res.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(res.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(res.bits[3], 0x00010000);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal number = {{0, 0, 0, 0}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_negate(number, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal number = {{123, 456, 789, 0x000F0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_negate(number, &res));
  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq(res.bits[1], 456);
  ck_assert_int_eq(res.bits[2], 789);
  ck_assert_int_eq(res.bits[3], 0x800F0000);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_negate(number, &res));
  ck_assert_int_eq(res.bits[0], 387420489);
  ck_assert_int_eq(res.bits[1], 999999999);
  ck_assert_int_eq(res.bits[2], 123456789);
  ck_assert_int_eq(res.bits[3], 2148401152);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_negate(number, &res));
  ck_assert_int_eq(res.bits[0], 987654321);
  ck_assert_int_eq(res.bits[1], 666666666);
  ck_assert_int_eq(res.bits[2], 888888888);
  ck_assert_int_eq(res.bits[3], 1638400);
}
END_TEST

Suite *test_negate(void) {
  Suite *s = suite_create("\033[45m-=S21_NEGATE=-\033[0m");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, negate_0);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);

  suite_add_tcase(s, tc);
  return s;
}