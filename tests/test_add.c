#include "tests.h"

START_TEST(add_0) {
  s21_decimal val1 = {{100, 0, 0, 0x00000000}};
  s21_decimal val2 = {{200, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 300);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{100, 200, 300, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 99);
  ck_assert_int_eq(res.bits[1], 201);
  ck_assert_int_eq(res.bits[2], 300);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{100, 200, 300, 0x00020000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00040000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 9999);
  ck_assert_int_eq(res.bits[1], 20001);
  ck_assert_int_eq(res.bits[2], 30000);
  ck_assert_int_eq(res.bits[3], 262144);
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{100, 200, 300, 0x00050000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x80060000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1001);
  ck_assert_int_eq(res.bits[1], 1999);
  ck_assert_int_eq(res.bits[2], 3000);
  ck_assert_int_eq(res.bits[3], 393216);
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x000D0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x000C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 3264175145);
  ck_assert_int_eq(res.bits[1], 2405181685);
  ck_assert_int_eq(res.bits[2], 472446402);
  ck_assert_int_eq(res.bits[3], 720896);
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x00050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1305451419);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 458752);
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{0, 0, 1, 0x00110000}};
  s21_decimal val2 = {{123456789, 0, 9876543, 0x80050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1911069901);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 987654300);
  ck_assert_int_eq(res.bits[3], 2147942400);
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{1, 2, 3, 0x801C0000}};
  s21_decimal val2 = {{11111111, 22222222, 33333333, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1111116634);
  ck_assert_int_eq(res.bits[1], 2222222200);
  ck_assert_int_eq(res.bits[2], 3333333300);
  ck_assert_int_eq(res.bits[3], 2148270080);
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{5, 0, 0, 0x00010000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1982497920);
  ck_assert_int_eq(res.bits[1], 1028290528);
  ck_assert_int_eq(res.bits[2], 1234567892);
  ck_assert_int_eq(res.bits[3], 983040);
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{60, 0, 0, 0x80000000}};
  s21_decimal val2 = {{40, 0, 0, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 100);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{123, 456, 789, 0x800D0000}};
  s21_decimal val2 = {{111, 222, 333, 0x00100000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 122889);
  ck_assert_int_eq(res.bits[1], 455778);
  ck_assert_int_eq(res.bits[2], 788667);
  ck_assert_int_eq(res.bits[3], 2148532224);
}
END_TEST

Suite *test_add(void) {
  Suite *s = suite_create("\033[45m-=S21_ADD=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, add_0);
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);
  tcase_add_test(tc, add_13);
  tcase_add_test(tc, add_14);

  suite_add_tcase(s, tc);
  return s;
}