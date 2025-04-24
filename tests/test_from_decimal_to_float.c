#include "tests.h"

START_TEST(convert_1) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);

  ck_assert_float_eq(res, 79228162514264337593543950336.0f);
  ck_assert_int_eq(0, error_code);
}
END_TEST

START_TEST(convert_2) {
  s21_decimal number = {{1234567890, 0, 0, 0x00040000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);

  ck_assert_float_eq(res, 123456.7890f);
  ck_assert_int_eq(0, error_code);
}
END_TEST

START_TEST(convert_3) {
  s21_decimal number = {{123, 0, 0, 0x80000000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);

  ck_assert_float_eq(res, -123.0f);
  ck_assert_int_eq(0, error_code);
}
END_TEST

START_TEST(convert_4) {
  s21_decimal number = {{15, 15, 15, 0x000F0000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);
  ck_assert_float_eq(res, 276701.156250f);
  ck_assert_int_eq(0, error_code);
}
END_TEST

START_TEST(convert_5) {
  s21_decimal number = {{387420489, 999999999, 123456789, 0x000E0000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);

  ck_assert_float_eq(res, 2.2773758E+13f);
  ck_assert_int_eq(0, error_code);
}
END_TEST

START_TEST(convert_6) {
  s21_decimal number = {{987654321, 666666666, 888888888, 0x80190000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);
  ck_assert_float_eq(res, -1639.7106f);
  ck_assert_int_eq(0, error_code);
}
END_TEST

START_TEST(convert_7) {
  s21_decimal number = {{123, 0, 0, 0xFFFFFFFF}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);

  ck_assert_int_eq(1, error_code);
}
START_TEST(convert_8) {
  s21_decimal number = {{0, 0, 0, 0x00000000}};
  float res;

  int error_code = s21_from_decimal_to_float(number, &res);

  ck_assert_float_eq(res, 0.0);
  ck_assert_int_eq(0, error_code);
}

Suite *test_from_decimal_to_float(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_FLOAT=-\033[0m");
  TCase *tc = tcase_create("from_decimal_to_float_tc");

  tcase_add_test(tc, convert_1);
  tcase_add_test(tc, convert_2);
  tcase_add_test(tc, convert_3);
  tcase_add_test(tc, convert_4);
  tcase_add_test(tc, convert_5);
  tcase_add_test(tc, convert_6);
  tcase_add_test(tc, convert_7);
  tcase_add_test(tc, convert_8);
  suite_add_tcase(s, tc);
  return s;
}