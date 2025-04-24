#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0, exp = stepen(src);
  int sign = get_sign(src);
  if (exp == -1) {
    return err = 1;
  } else if (exp > 0) {
    s21_truncate(src, &src);
  }

  if (src.bits[0] > MAX_INT && sign == 0) {
    return err = 1;
  } else if (src.bits[0] > MAX_MIN_INT && sign == 1) {
    return err = 1;
  }

  if (src.bits[2] == 0) {
    if (src.bits[1] == 0) {
      *dst = src.bits[0];
      if (get_sign(src) == 1) {
        *dst *= -1;
      }
    } else {
      err = 1;
    }
  } else {
    err = 1;
  }

  return err;
}
