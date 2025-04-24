#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err = 0;
  clear_decimal(dst);
  if (src < 0) {
    set_bit(&dst->bits[3], 31);
  } else if (src > 0) {
    set_bit_0(&dst->bits[3], 31);
  }

  dst->bits[0] = abs(src);

  if (src == 0) {
    clear_decimal(dst);
  }

  return err;
}
