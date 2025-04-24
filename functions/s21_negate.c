#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    return error = 1;
  }
  if (get_sign(value)) {
    set_bit_0(&value.bits[3], 31);
  } else {
    set_bit(&value.bits[3], 31);
  }

  *result = value;

  return error;
}
