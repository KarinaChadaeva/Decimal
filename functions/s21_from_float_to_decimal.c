#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  if (!dst || src != src || fabs(src) > MAX_DECIMAL ||
      (fabs(src) > 0 && fabs(src) < 1e-28)) {
    err = 1;
  } else {
    char tmp_float[100];
    sprintf(tmp_float, "%E", fabs(src));
    int scale = (tmp_float[10] - '0') * 10 + (tmp_float[11] - '0');
    if (tmp_float[9] == '+') scale = -scale;
    unsigned int val = 0;
    int pw = 0, zeros = 1, mul = -1;
    for (int i = 7; i >= 0; i--) {
      if (tmp_float[i] == '.') {
        continue;
      } else if (zeros && tmp_float[i] == '0') {
        continue;
      } else {
        zeros = 0;
        mul++;
        val += (tmp_float[i] - '0') * pow(10, pw++);
      }
    }
    scale += mul;
    s21_decimal tmp_decimal = {0};
    s21_decimal null_decimal = {0};
    s21_from_int_to_decimal(val, &tmp_decimal);

    if (src < 0) set_bit(&tmp_decimal.bits[3], 31);
    if (scale > 28 || scale < -28) {
      err = 1;

    } else if (scale < 0) {
      scale_write(&null_decimal, abs(scale));
      aligment_scale(&null_decimal, &tmp_decimal);
      scale_write(&tmp_decimal, 0);

    } else {
      scale_write(&tmp_decimal, abs(scale));
    }
    *dst = tmp_decimal;
  }
  return err;
}
