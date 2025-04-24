#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int exp = stepen(value), error = 0, sign = get_sign(value);
  if (exp == -1) {
    return error = 1;
  }
  if (exp != 0 && sign == 0) {
    s21_truncate(value, result);
  } else if (exp != 0 && sign == 1) {
    s21_truncate(value, result);
    s21_decimal one = {0};
    one.bits[0] = 1;
    s21_sub(*result, one, result);
  } else {
    *result = value;
  }

  return error;
}
