#include "tests.h"

START_TEST(mul_0) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{4, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 492);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{15, 15, 15, 0x000F0000}};
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 150);
  ck_assert_int_eq(res.bits[1], 150);
  ck_assert_int_eq(res.bits[2], 150);
  ck_assert_int_eq(res.bits[3], 983040);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{0XFFFFFFFF, 0, 0, 0x00040000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00070000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 4294967294);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 720896);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{127, 0, 0, 0x00000000}};
  s21_decimal val2 = {{229, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 29083);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147483648);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{1, 0, 0, 0x001C0000}};
  s21_decimal val2 = {{1, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{123456789, 900009, 1337, 0x00100000}};
  s21_decimal val2 = {{1, 1, 1111111, 0x80070000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 3773028595);
  ck_assert_int_eq(res.bits[1], 2256743337);
  ck_assert_int_eq(res.bits[2], 2740366469);
  ck_assert_int_eq(res.bits[3], 2147745792);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0, 0}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{0XFFFFFFFF, 100, 0, 0}};
  s21_decimal val2 = {{0XFFFFFFFF, 100, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 4294967094);
  ck_assert_int_eq(res.bits[2], 10200);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{1, 0, 0, 0x001C0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 4294967295);
  ck_assert_int_eq(res.bits[1], 4294967295);
  ck_assert_int_eq(res.bits[2], 4294967295);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{1241434324, 223, 64654654, 0x00060000}};
  s21_decimal val2 = {{7676767, 7465478, 12, 0x80070000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1797304573);
  ck_assert_int_eq(res.bits[1], 1947946003);
  ck_assert_int_eq(res.bits[2], 2024334038);
  ck_assert_int_eq(res.bits[3], 2148270080);
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("\033[45m-=S21_MUL=-\033[0m");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, mul_0);
  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);

  suite_add_tcase(s, tc);
  return s;
}