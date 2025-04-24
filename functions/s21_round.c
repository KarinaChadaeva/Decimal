#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int exp = stepen(value), error = 0, round = check_last_num(value, exp),
      sign = get_sign(value);
  if (exp == -1) {
    return error = 1;
  } else if (exp == 0) {
    *result = value;
    return error;
  }
  s21_truncate(value, result);
  if (round == 5 && !check_bit(result->bits[0], 0)) {
  } else {
    if (round >= 5 && sign == 0) {
      s21_decimal one = {0};
      one.bits[0] = 1;
      s21_add(*result, one, result);
    } else if (round >= 5 && sign == 1) {
      s21_decimal one = {0};
      one.bits[0] = 1;
      s21_sub(*result, one, result);
    }
  }

  return error;
}

int check_last_num(s21_decimal buf, int exp) {
  unsigned long long u_num;
  // printf("\nITS DAUN ME\n");
  int tmp_int = 0, more_or_5 = 0;
  for (int i = 0; i < exp; i++) {
    u_num = buf.bits[2];

    for (int j = 2; j >= 0; j--) {
      if (j == 0) {
        buf.bits[j] = u_num / 10;
        more_or_5 = u_num % 10;
      } else {
        tmp_int = u_num % 10;
        buf.bits[j] = u_num / 10;
        u_num = tmp_int * (overflow) + buf.bits[j - 1];
      }
    }
  }
  return more_or_5;
}
