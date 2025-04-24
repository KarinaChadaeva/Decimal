#include "../s21_decimal.h"

// gcc -o mul_test s21_mul_test.c ../arithmetic.c
// -I/opt/homebrew/Cellar/check/0.15.2/include
// -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck

// int main () {
//     s21_decimal res = {0};
//     int error = 0;

//     s21_decimal num1 = {{123, 321, 0, 0x00020000}};
//     s21_decimal num2 = {{0, 0, 1, 0x00030000}};

//     printf("scale 1: %d\nscale 2: %d\n", get_scale(num1), get_scale(num2));

//     printf("num1\n");
//     for (int i = 3; i >= 0; i--) {
//         print_bits(num1.bits[i]);
//         printf(" ");
//     }
//     printf("\n");

//     printf("num2\n");
//     for (int i = 3; i >= 0; i--) {
//         print_bits(num2.bits[i]);
//         printf(" ");
//     }
//     printf("\n");

//     error = s21_sub(num1, num2, &res);

//     printf("scale res %d\n", get_scale(res));
//     printf("res\n");
//     for (int i = 3; i >= 0; i--) {
//         print_bits(res.bits[i]);
//         printf(" ");
//     }
//     printf("\n");

//     printf("error_code %d\n", error);

//     return 0;
// }

void big_to_decimal(s21_decimal *small, big_decimal *big, int *error_code,
                    int sign, int *scale) {
  bank_rounding(big, scale);
  if (big->bits[3] || big->bits[4] || big->bits[5] || big->bits[6] ||
      big->bits[7])
    *error_code = sign ? 2 : 1;
  else if (*scale > 28)
    *scale = 0;
  if (*error_code == 0) {
    set_scale(small, *scale);
    for (int i = 0; i < 3; i++) {
      small->bits[i] = big->bits[i];
    }
    if (sign) set_bit(&small->bits[3], 31);
  }
}

void bank_rounding(big_decimal *value, int *scale) {
  big_decimal value_copy;
  int scale_copy = *scale;
  big_copy(&value_copy, *value);
  divide_by_ten(&value_copy, 1, &scale_copy);

  while (((value->bits[3] || value->bits[4] || value->bits[5] ||
           value->bits[6] || value->bits[7]) &&
          *scale) ||
         (*scale > 28 && !big_is_zero(*value))) {
    int round = 0;
    int last_num = divide_by_ten(value, 1, scale),
        penultimate_num = divide_by_ten(&value_copy, 1, &scale_copy);
    if (last_num > 5)
      round = 1;
    else if (last_num == 5)
      if (penultimate_num % 2 == 1) round = 1;

    if (round) inc(value);
  }
}

int divide_by_ten(big_decimal *value, int times, int *scale) {
  int carry = 0;
  if (times > 0) {
    *scale -= times;
    if (*scale < 0) *scale = 0;
    while (times--) {
      carry = 0;
      for (int i = 7; i >= 0; i--) {
        unsigned long dividend = ((unsigned long)carry << 32) | value->bits[i];
        value->bits[i] = (unsigned int)(dividend / 10);
        carry = (int)(dividend % 10);
      }
    }
  }
  return carry;
}

void inc(big_decimal *dec) {
  int i = 0;
  while (++dec->bits[i] == 0) i++;
}

void big_copy(big_decimal *big_to, big_decimal big_from) {
  for (int i = 0; i < 8; i++) big_to->bits[i] = big_from.bits[i];
}

int big_is_zero(big_decimal n) {
  return n.bits[0] == 0 && n.bits[1] == 0 && n.bits[2] == 0 && n.bits[3] == 0 &&
         n.bits[4] == 0 && n.bits[5] == 0 && n.bits[6] == 0 && n.bits[7] == 0;
}

void normalisation(big_decimal *value_1, big_decimal *value_2, int *scale1,
                   int *scale2) {
  big_decimal ten = {0};
  zero_big(&ten);
  set_bit(&ten.bits[0], 1);
  set_bit(&ten.bits[0], 3);

  if (*scale1 > *scale2) {
    int diff = *scale1 - *scale2;
    for (int i = 0; i < diff; i++) {
      mul_big_decimal(*value_2, ten, value_2);
    }
    *scale2 += diff;
  } else if (*scale1 < *scale2) {
    int diff = *scale2 - *scale1;
    for (int i = 0; i < diff; i++) {
      mul_big_decimal(*value_1, ten, value_1);
    }
    *scale1 += diff;
  }
}

int check_max_big(big_decimal *value) {
  int res = 0;

  s21_decimal max_decimal = {0};
  big_decimal max_big = {0};
  for (int i = 0; i < 3; i++) {
    for (int f = 0; f < 32; f++) {
      set_bit(&max_decimal.bits[i], f);
    }
  }
  decimal_to_big(&max_decimal, &max_big);
  if (is_greater_big(*value, max_big)) {
    res = 1;
    *value = max_big;
  }
  return res;
}

void set_bit_big(big_decimal *value, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    value->bits[index / 32] = value->bits[index / 32] & ~mask;
  else
    value->bits[index / 32] = value->bits[index / 32] | mask;
}

int get_bit_big(big_decimal value, int index) {
  int mask = 1u << (index % 32);
  return (value.bits[index / 32] & mask) != 0;
}

s21_decimal abs_decimal(s21_decimal value) {
  s21_decimal res = {0};
  set_bit(&value.bits[3], 31);
  s21_negate(value, &res);
  return res;
}

// int s21_negate (s21_decimal value, s21_decimal *result) {
//     int error = 0;
//     if (result == NULL)
//         return error = 1;
//     if (get_sign(&value))
//         set_bit_0(&value.bits[3], 31);
//     else
//         set_bit(&value.bits[3], 31);
//     *result = value;
//     return error;
// }

void decimal_to_big(s21_decimal *small, big_decimal *big) {
  for (int i = 0; i < 3; i++) {
    big->bits[i] = small->bits[i];
  }
  big->bits[3] = big->bits[4] = big->bits[5] = big->bits[6] = big->bits[7] = 0;
}

// void set_bit (unsigned int *number, int bit_number) {
//     *number |= (1 << bit_number);
// }

int get_scale(s21_decimal value) {
  int mask = 127 << 16;
  int scale = (mask & value.bits[3]) >> 16;
  return scale;
}

void set_scale(s21_decimal *value, int scale) {
  value->bits[3] = 0;
  scale <<= 16;
  value->bits[3] = scale | value->bits[3];
}

// void print_bits (unsigned int number) {
//     unsigned int size = sizeof(unsigned int);
//     unsigned int maxPow = 1<<(size*8-1);
//     unsigned int i=0;
//     for(; i < size * 8; ++i) {
//         printf("%u",number&maxPow ? 1 : 0);
//         number = number<<1;
//     }
// }

void zero_decimal(s21_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] = 0;
}

// int get_sign (s21_decimal *num) {
//     int sign = -1;

//     if((check_bit(num->bits[3], 31)) == 0) {
//         sign = 0;
//     } else {
//         sign = 1;
//     }
//     return sign;
// }

// int check_bit (unsigned int number, int bit_number) {
//     return number & (1 << bit_number);
// }

// void set_bit_0 (unsigned int *number, int bit_number){
//     *number &= ~(1 << bit_number);
// }

void zero_big(big_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] =
      value->bits[4] = value->bits[5] = value->bits[6] = value->bits[7] = 0;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  zero_decimal(result);
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  decimal_to_big(&value_1, &val_1);
  decimal_to_big(&value_2, &val_2);
  if (scale1 != scale2) normalisation(&val_1, &val_2, &scale1, &scale2);
  if ((sign1 && sign2) || (!sign1 && !sign2)) {
    add_big_decimal(val_1, val_2, &res);
    big_to_decimal(result, &res, &error_code, sign1, &scale1);
    if (sign1) set_bit(&result->bits[3], 31);
  } else if ((!sign1 && sign2) || (sign1 && !sign2)) {
    value_1 = abs_decimal(value_1);
    value_2 = abs_decimal(value_2);
    if (is_equal_big(val_1, val_2)) {
      zero_decimal(result);
    } else if (is_greater_big(val_1, val_2)) {
      sub_big_decimal(val_1, val_2, &res);
      big_to_decimal(result, &res, &error_code, sign1, &scale1);
      set_scale(result, scale1);
      if (sign1) set_bit(&result->bits[3], 31);
    } else {
      sub_big_decimal(val_2, val_1, &res);
      big_to_decimal(result, &res, &error_code, sign2, &scale2);
      set_scale(result, scale2);
      if (sign2) set_bit(&result->bits[3], 31);
    }
  }

  return error_code;
}

void add_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result) {
  unsigned sum = 0, overflow1 = 0;
  zero_big(result);
  for (int i = 0; i < 256; i++) {
    sum = get_bit_big(value_1, i) + get_bit_big(value_2, i) + overflow1;
    overflow1 = sum / 2;
    set_bit_big(result, i, sum % 2);
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0, sign_res = 0;
  big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  zero_decimal(result);
  int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  decimal_to_big(&value_1, &val_1);
  decimal_to_big(&value_2, &val_2);
  mul_big_decimal(val_1, val_2, &res);
  if (sign1 || sign2) sign_res = 1;
  scale1 += scale2;
  big_to_decimal(result, &res, &error_code, sign_res, &scale1);
  set_scale(result, scale1);

  if (sign_res) set_bit(&result->bits[3], 31);
  return error_code;
}

void mul_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result) {
  zero_big(result);
  for (int i = 0; i < 6; ++i) {
    unsigned long partial_sum = 0;
    for (int j = 0; j <= i; ++j) {
      partial_sum += (unsigned long)value_1.bits[j] * value_2.bits[i - j];
    }
    unsigned long tmp = partial_sum + (unsigned long)result->bits[i];
    result->bits[i] = (unsigned int)tmp;
    result->bits[i + 1] += (unsigned int)(tmp >> 32);
  }
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0;
  big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  zero_decimal(result);
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  decimal_to_big(&value_1, &val_1);
  decimal_to_big(&value_2, &val_2);
  if (scale1 != scale2) normalisation(&val_1, &val_2, &scale1, &scale2);
  if ((sign1 && !sign2) || (!sign1 && sign2)) {
    add_big_decimal(val_1, val_2, &res);
    big_to_decimal(result, &res, &error_code, sign1, &scale1);
    set_scale(result, scale1);
    if (sign1) set_bit(&result->bits[3], 31);
  } else {
    value_1 = abs_decimal(value_1);
    value_2 = abs_decimal(value_2);
    if (is_equal_big(val_1, val_2)) {
      zero_decimal(result);
    } else if (is_greater_big(val_1, val_2)) {
      sub_big_decimal(val_1, val_2, &res);
      big_to_decimal(result, &res, &error_code, sign1, &scale1);
      set_scale(result, scale1);
      if (sign1) set_bit(&result->bits[3], 31);
    } else {
      sub_big_decimal(val_2, val_1, &res);
      big_to_decimal(result, &res, &error_code, sign2, &scale2);
      set_scale(result, scale2);
      if (!sign2) set_bit(&result->bits[3], 31);
    }
  }
  return error_code;
}

void sub_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result) {
  zero_big(result);
  int tmp = 0, res = 0;
  for (int i = 0; i < 256; i++) {
    res = get_bit_big(value_1, i) - get_bit_big(value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    set_bit_big(result, i, res % 2);
  }
}

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int error_code = 0, sign_res = 0, scale_res = 0;
//     big_decimal val_1 = {0}, val_2 = {0}, res = {0};
//     zero_decimal(result);
//     int sign1 = get_sign(&value_1), sign2 = get_sign(&value_2);
//     int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
//     decimal_to_big(&value_1, &val_1);
//     decimal_to_big(&value_2, &val_2);
//     if (sign1 || sign2)
//         sign_res = 1;
//     if (big_is_zero(val_2))
//         error_code = 3;
//     else {
//         div_big_decimal(val_1, val_2, &res, &scale1, &scale2, &scale_res);
//         decimal_to_big(result, &res);
//         set_scale(result, scale_res);
//         if (sign_res)
//             set_bit(&result->bits[3], 31);
//     }
//     return error_code;
// }

// void div_big_decimal (big_decimal value_1, big_decimal value_2, big_decimal
// *result, int *scale1, int *scale2, int *scale_res) {
//     big_decimal remainder = {0}, quotient = {0}, ten = {0}, tmp = {0};
//     int scale1_copy = *scale1, scale2_copy = *scale2, quotient_scale = 0,
//     check = 0; set_bit(&ten.bits[0], 1); set_bit(&ten.bits[0], 3); while
//     (scale1_copy) {
//         mul_big_decimal(value_1, ten, &value_1);
//         scale1_copy--;
//     }
//     while (scale2_copy) {
//         mul_big_decimal(value_2, ten, &value_2);
//         scale2_copy--;
//     }

//     do {
//         zero_big(&remainder);
//         zero_big(&quotient);

//         for (int i = 256; i >= 0; i--) {
//             big_shift_left(&remainder, 1);
//             set_bit_big(&remainder, 0, get_bit_big(value_1, i));
//             if (is_greater_big(remainder, value_2) || is_equal_big(remainder,
//             value_2)) {
//                 big_decimal tmp = {0};
//                 sub_big_decimal(remainder, value_2, &tmp);
//                 big_copy(&remainder, tmp);
//                 set_bit_big(&quotient, i, 1);
//             }
//         }
//         add_big_decimal(*result, quotient, &tmp);
//         big_copy(result, tmp);
//         if (result->bits[3] == 0 && !big_is_zero(remainder)) {
//             big_copy(&value_1, remainder);
//             mul_big_decimal(value_1, ten, &value_1);
//             mul_big_decimal(*result, ten, result);
//             quotient_scale++;
//         } else
//             check = 1;
//     } while (!check);

//     if (*scale2 > *scale1) {
//         for (int i = 0; i < (*scale2 - *scale1); i++)
//             mul_big_decimal(*result, ten, result);
//     } else if (*scale2 < *scale1) {
//         for (int i = 0; i < (*scale1 - *scale2); i++)
//             mul_big_decimal(*result, ten, result);
//     }
// }

void big_shift_left(big_decimal *value, int shift) {
  for (int i = 7; i > 0; i--) {
    value->bits[i] =
        (value->bits[i] << shift) | (value->bits[i - 1] >> (32 - shift));
  }
  value->bits[0] = value->bits[0] << shift;
}

int is_greater_big(big_decimal value1, big_decimal value2) {
  int res = 0;
  for (int i = 7; i >= 0; i--) {
    if (value1.bits[i] > value2.bits[i]) {
      res = 1;
      i -= 8;
    } else if (value1.bits[i] < value2.bits[i]) {
      res = 0;
      i -= 8;
    }
  }
  return res;
}

int is_equal_big(big_decimal value_1, big_decimal value_2) {
  int res = 0;
  if (value_1.bits[0] == value_2.bits[0] &&
      value_1.bits[1] == value_2.bits[1] &&
      value_1.bits[2] == value_2.bits[2] &&
      value_1.bits[3] == value_2.bits[3] &&
      value_1.bits[4] == value_2.bits[4] &&
      value_1.bits[5] == value_2.bits[5] &&
      value_1.bits[6] == value_2.bits[6] && value_1.bits[7] == value_2.bits[7])
    res = 1;

  return res;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = 0, sign_res = 0, scale_res = 0;
  big_decimal val_1 = {0}, val_2 = {0}, res = {0};
  zero_decimal(result);
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  if (sign1 || sign2) sign_res = 1;
  decimal_to_big(&value_1, &val_1);
  decimal_to_big(&value_2, &val_2);

  if (big_is_zero(val_2))
    error_code = 3;
  else {
    div_big_decimal(val_1, val_2, &res, &scale1, &scale2, &scale_res);
    error_code = 0;
    big_to_decimal(result, &res, &error_code, sign_res, &scale_res);
    set_scale(result, scale_res);
    if (sign_res) set_bit(&result->bits[3], 31);
  }
  return error_code;
}

void div_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result, int *scale1, int *scale2,
                     int *scale_res) {
  big_decimal remainder = {0}, quotient = {0}, ten = {0};
  int scale1_copy = *scale1, scale2_copy = *scale2, check = 0,
      quotient_scale = 0;
  *scale_res = 0;
  set_bit(&ten.bits[0], 1);
  set_bit(&ten.bits[0], 3);
  if (*scale1 > *scale2) {
    for (int i = 0; i < scale1_copy - scale2_copy; i++) {
      mul_big_decimal(value_1, ten, &value_1);
      mul_big_decimal(value_2, ten, &value_2);
    }
  } else if (*scale1 < *scale2) {
    for (int i = 0; i < scale2_copy - scale1_copy; i++) {
      mul_big_decimal(value_1, ten, &value_1);
      mul_big_decimal(value_2, ten, &value_2);
    }
  } else if (*scale1 == *scale2) {
    for (int i = 0; i < scale2_copy; i++) {
      mul_big_decimal(value_1, ten, &value_1);
      mul_big_decimal(value_2, ten, &value_2);
    }
  }

  do {
    zero_big(&remainder);
    zero_big(&quotient);

    for (int i = 256; i >= 0; i--) {
      big_shift_left(&remainder, 1);
      set_bit_big(&remainder, 0, get_bit_big(value_1, i));
      if (is_greater_big(remainder, value_2) ||
          is_equal_big(remainder, value_2)) {
        sub_big_decimal(remainder, value_2, &remainder);
        set_bit_big(&quotient, i, 1);
      }
    }
    normalisation(result, &quotient, scale_res, &quotient_scale);
    add_big_decimal(*result, quotient, result);
    if (!big_is_zero(remainder) && !(*scale_res)) {
      big_copy(&value_1, remainder);
      mul_big_decimal(value_1, ten, &value_1);
      mul_big_decimal(*result, ten, result);
      quotient_scale++;
      scale_res++;
    } else
      check = 1;
  } while (!check);

  if (*scale1 > *scale2)
    *scale_res += *scale1 - *scale2;
  else if (*scale1 < *scale2)
    *scale_res += *scale2 - *scale1;
  else
    *scale_res = *scale1;
}
