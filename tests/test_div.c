#include "tests.h"

START_TEST(div_0) {
  s21_decimal number1 = {{864192, 0, 0, 0x00030000}};
  s21_decimal number2 = {{7, 0, 0, 0x00000000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_div(number1, number2, &res));
  ck_assert_int_eq(res.bits[0], 123456);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 196608);
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{15, 15, 15, 0x000F0000}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{46, 0, 0, 0x00020000}};
  s21_decimal val2 = {{2, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 23);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 131072);
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, 2147745792}};
  s21_decimal val2 = {{5, 0, 0, 393216}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 4);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(div_4) {
  s21_decimal val1 = {{123456789, 900009, 0, 0x00100000}};
  s21_decimal val2 = {{1, 1, 0, 0x80070000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 90000900);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(div_5) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_6) {
  s21_decimal val1 = {{1, 0, 0, 0x001C0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 123);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_8) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x000A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 655360);
}
END_TEST

START_TEST(div_9) {
  s21_decimal val1 = {{80000, 80000, 80000, 0x00050000}};
  s21_decimal val2 = {{80000, 2, 80000, 0x000A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 100);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_10_) {
  s21_decimal val1 = {{1234567890, 0, 0, 0x00050000}};
  s21_decimal val2 = {{0, 0, 0, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s = suite_create("\033[45m-=S21_DIV=-\033[0m");
  TCase *tc = tcase_create("div_tc");

  tcase_add_test(tc, div_0);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);
  tcase_add_test(tc, div_10_);

  suite_add_tcase(s, tc);
  return s;
}
