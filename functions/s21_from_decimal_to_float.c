#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  if (!dst) {
    err = 1;
  } else {
    s21_decimal tmp = src;
    int sign = get_sign(src);
    if (sign) s21_negate(tmp, &tmp);
    s21_decimal min = {{0x1, 0x0, 0x0, 0x001C0000}};
    s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

    if (check_dec_is_null(src)) {
      if (sign)
        *dst = -0.0;
      else
        *dst = 0.0;
    } else if (s21_is_less(tmp, min)) {
      err = 1;
      *dst = 0.0;
    } else if (tmp.bits[0] > max.bits[0] && tmp.bits[1] > max.bits[1] &&
               tmp.bits[2] > max.bits[2]) {
      err = 1;
    } else {
      *dst = 0.0;
      double tmp_double = 0.0;
      int scale = stepen(src);
      for (int i = 0; i < 96; i++) {
        if (check_bit(src.bits[i / 32], i % 32)) {
          tmp_double += pow(2.0, i);
        }
      }
      tmp_double /= pow(10.0, scale);
      if (sign) tmp_double *= -1;
      *dst = (float)tmp_double;
    }
  }
  return err;
}
