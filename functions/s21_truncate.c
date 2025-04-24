#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int exp = stepen(value);
  if (exp == -1) {
    return error = 1;
  }
  if (result == NULL) {
    return error = 1;
  }

  if (exp != 0) {
    s21_decimal buf = {0};
    buf = value;
    truncate_buff(&buf, exp);
    *result = buf;
  } else {
    *result = value;
  }

  return error;
}
