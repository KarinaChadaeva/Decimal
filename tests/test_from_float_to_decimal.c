#include "tests.h"

START_TEST(from_float_to_decimal_0) {
  float number = 123456.7890f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 1234568);
  ck_assert_float_eq(res.bits[1], 0);
  ck_assert_float_eq(res.bits[2], 0);
  ck_assert_float_eq(res.bits[3], 65536);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  float number = -1111111111111111.2222222222222222222f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 2960524800);
  ck_assert_float_eq(res.bits[1], 258700);
  ck_assert_float_eq(res.bits[2], 0);
  ck_assert_float_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  float number = 0.0f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 0);
  ck_assert_float_eq(res.bits[1], 0);
  ck_assert_float_eq(res.bits[2], 0);
  ck_assert_float_eq(res.bits[3], 0);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  float number = 0.000000000000015f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 15);
  ck_assert_float_eq(res.bits[1], 0);
  ck_assert_float_eq(res.bits[2], 0);
  ck_assert_float_eq(res.bits[3], 983040);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  float number = 1231541515571249051523857325.0f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 2243952640);
  ck_assert_float_eq(res.bits[1], 2557039510);
  ck_assert_float_eq(res.bits[2], 66762025);
  ck_assert_float_eq(res.bits[3], 0);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  float number = 79228162514264337593543950335.0f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 536870912);
  ck_assert_float_eq(res.bits[1], 3012735514);
  ck_assert_float_eq(res.bits[2], 4294967159);
  ck_assert_float_eq(res.bits[3], 0);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  float number = 1e-28f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 1);
  ck_assert_float_eq(res.bits[1], 0);
  ck_assert_float_eq(res.bits[2], 0);
  ck_assert_float_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(from_float_to_decimal_7) {
  float number = 15454545e-27f;
  s21_decimal res;

  ck_assert_float_eq(0, s21_from_float_to_decimal(number, &res));
  ck_assert_float_eq(res.bits[0], 1545454);
  ck_assert_float_eq(res.bits[1], 0);
  ck_assert_float_eq(res.bits[2], 0);
  ck_assert_float_eq(res.bits[3], 1703936);
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  float number = 1e-29f;
  s21_decimal res;

  ck_assert_float_eq(1, s21_from_float_to_decimal(number, &res));
}
END_TEST

START_TEST(from_float_to_decimal_9) {
  float number = 792281625142643375935439503360.0f;
  s21_decimal res;

  ck_assert_float_eq(1, s21_from_float_to_decimal(number, &res));
}
END_TEST

Suite *test_from_float_to_decimal(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_FLOAT_TO_DECIMAL=-\033[0m");
  TCase *tc = tcase_create("from_float_to_decimal_tc");

  tcase_add_test(tc, from_float_to_decimal_0);
  tcase_add_test(tc, from_float_to_decimal_1);
  tcase_add_test(tc, from_float_to_decimal_2);
  tcase_add_test(tc, from_float_to_decimal_3);
  tcase_add_test(tc, from_float_to_decimal_4);
  tcase_add_test(tc, from_float_to_decimal_5);
  tcase_add_test(tc, from_float_to_decimal_6);
  tcase_add_test(tc, from_float_to_decimal_7);
  tcase_add_test(tc, from_float_to_decimal_8);
  tcase_add_test(tc, from_float_to_decimal_9);

  suite_add_tcase(s, tc);
  return s;
}