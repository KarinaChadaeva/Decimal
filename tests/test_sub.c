#include "tests.h"

START_TEST(sub_0) {
  s21_decimal val1 = {{1000, 0, 0, 0x00000000}};
  s21_decimal val2 = {{500, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 500);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{100, 200, 300, 0x00020000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00040000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 10001);
  ck_assert_int_eq(res.bits[1], 19999);
  ck_assert_int_eq(res.bits[2], 30000);
  ck_assert_int_eq(res.bits[3], 262144);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{100, 200, 300, 0x00050000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x80060000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 999);
  ck_assert_int_eq(res.bits[1], 2001);
  ck_assert_int_eq(res.bits[2], 3000);
  ck_assert_int_eq(res.bits[3], 393216);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{0, 0, 1, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0XFFFFFFFF);
  ck_assert_int_eq(res.bits[1], 0XFFFFFFFF);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x000D0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x000C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1717986918);
  ck_assert_int_eq(res.bits[1], 1717986918);
  ck_assert_int_eq(res.bits[2], 3865470566);
  ck_assert_int_eq(res.bits[3], 2148270080);
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x00050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1911069901);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 2147942400);
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x80050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1305451419);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 458752);
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{1, 2, 3, 0x801C0000}};
  s21_decimal val2 = {{11111111, 22222222, 33333333, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1111105566);
  ck_assert_int_eq(res.bits[1], 2222222200);
  ck_assert_int_eq(res.bits[2], 3333333300);
  ck_assert_int_eq(res.bits[3], 786432);
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{123, 321, 0, 0x00020000}};
  s21_decimal val2 = {{0, 0, 1, 0x00030000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 4294966066);
  ck_assert_int_eq(res.bits[1], 4294964085);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 2147680256);
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1470944564);
  ck_assert_int_eq(res.bits[1], 1791840269);
  ck_assert_int_eq(res.bits[2], 1234567892);
  ck_assert_int_eq(res.bits[3], 983040);
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{123, 456, 789, 0x000D0000}};
  s21_decimal val2 = {{111, 222, 333, 0x80100000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 123111);
  ck_assert_int_eq(res.bits[1], 456222);
  ck_assert_int_eq(res.bits[2], 789333);
  ck_assert_int_eq(res.bits[3], 1048576);
}
END_TEST

Suite *test_sub(void) {
  Suite *s = suite_create("\033[45m-=S21_SUB=-\033[0m");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, sub_0);
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);
  tcase_add_test(tc, sub_8);
  tcase_add_test(tc, sub_9);
  tcase_add_test(tc, sub_10);
  tcase_add_test(tc, sub_11);
  tcase_add_test(tc, sub_12);
  tcase_add_test(tc, sub_13);

  suite_add_tcase(s, tc);
  return s;
}