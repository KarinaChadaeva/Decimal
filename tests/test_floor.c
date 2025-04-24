#include "tests.h"

START_TEST(floor_0) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 2576980378);
  ck_assert_int_eq(res.bits[1], 2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(floor_1) {
  s21_decimal number = {{1234567890, 0, 0, 0x00020000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 12345678);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal number = {{123, 123, 123, 0x000F0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 2268949);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 4294967295);
  ck_assert_int_eq(res.bits[1], 4294967295);
  ck_assert_int_eq(res.bits[2], 4294967295);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal number = {{1234567890, 987654321, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 1640);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(floor_5) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 8);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(floor_6) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 1841348007);
  ck_assert_int_eq(res.bits[1], 5302);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], 1640);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

Suite *test_floor(void) {
  Suite *s = suite_create("\033[45m-=S21_FLOOR=-\033[0m");
  TCase *tc = tcase_create("floor_tc");

  tcase_add_test(tc, floor_0);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);

  suite_add_tcase(s, tc);
  return s;
}