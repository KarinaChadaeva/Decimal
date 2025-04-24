#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  big_decimal value1_big, value2_big;
  int scale1 = get_scale(value1), scale2 = get_scale(value2);

  to_big(value1, &value1_big);
  to_big(value2, &value2_big);

  s21_normalize_big(&value1_big, &value2_big, &scale1, &scale2);

  int res = 0;
  if (check_dec_is_null(value1) && check_dec_is_null(value2)) {
    res = 0;
  } else if (get_sign(value1) < get_sign(value2)) {
    res = 1;
  } else if (get_sign(value1) > get_sign(value2)) {
    res = 0;
  } else if (s21_is_equal(value1, value2)) {
    res = 0;
  } else {
    for (int i = 191; i >= 0; i--) {
      if (check_bit(value1_big.bits[i / 32], i % 32) >
          check_bit(value2_big.bits[i / 32], i % 32)) {
        res = 1;
        break;
      } else if (check_bit(value1_big.bits[i / 32], i % 32) <
                 check_bit(value2_big.bits[i / 32], i % 32)) {
        res = 0;
        break;
      }
    }
    if (get_sign(value1) == 1 && get_sign(value2) == 1) res = res ? 0 : 1;
  }
  return res;
}

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int is_equal = 1;

  if (value1.bits[0] != value2.bits[0]) {
    is_equal = 0;
  } else {
    int i = 1;
    while (i < 4 && value1.bits[i] == value2.bits[i]) {
      i++;
    }
    if (i < 4) {
      is_equal = 0;
    }
  }
  return is_equal;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  return !s21_is_greater(value1, value2) && s21_is_not_equal(value1, value2);
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_equal(value1, value2);
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_greater(value1, value2);
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_less(value1, value2);
}
