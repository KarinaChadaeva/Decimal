#include "tests.h"

START_TEST(truncate_0) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 7);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal number = {{123456, 0, 0, 0x00030000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x00000000);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal number = {{123, 456, 789, 0x000F0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 14554481);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal number = {{123456789, 574656435, 1000000, 0x80150000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 18446);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal number = {{0, 0, 0, 0x80150000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(truncate_5) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 2576980377);
  ck_assert_int_eq(res.bits[1], 2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(truncate_6) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 1841348007);
  ck_assert_int_eq(res.bits[1], 5302);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_truncate(number, &res));
  ck_assert_int_eq(res.bits[0], 1639);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(truncate_8) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 4194304}};
  s21_decimal res;

  ck_assert_int_eq(1, s21_truncate(number, &res));
}
END_TEST

Suite *test_truncate(void) {
  Suite *s = suite_create("\033[45m-=S21_TRUNCATE=-\033[0m");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, truncate_0);
  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_5);
  tcase_add_test(tc, truncate_6);
  tcase_add_test(tc, truncate_7);
  tcase_add_test(tc, truncate_8);

  suite_add_tcase(s, tc);
  return s;
}