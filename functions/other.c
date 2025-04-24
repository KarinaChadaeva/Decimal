#include "../s21_decimal.h"

int check_bit(unsigned int number, int bit_number) {
  return number & (1 << bit_number);
}

int get_sign(s21_decimal num) {
  int sign = -1;

  if ((check_bit(num.bits[3], 31)) == 0) {
    sign = 0;
  } else {
    sign = 1;
  }
  return sign;
}

void set_bit(unsigned int *number, int bit_number) {
  *number |= (1 << bit_number);
}

void set_bit_0(unsigned int *number, int bit_number) {
  *number &= ~(1 << bit_number);
}

// void print_bits(unsigned int number) {
//     unsigned int size = sizeof(unsigned int);
//     unsigned int maxPow = 1<<(size*8-1);
//     int i=0;
//     for(;i<size*8;++i){
//     // print last bit and shift left.
//     printf("%u ",number&maxPow ? 1 : 0);
//     number = number<<1;
//         }
// }

// void set_bit_mantissa(s21_decimal *num, int bit_number) {
// if(bit_number > 0 && bit_number < 32) {
//     set_bit(&num->bits[0], bit_number);
// } else if (bit_number > 31 && bit_number < 64) {
//     set_bit(&num->bits[1], bit_number);
// } else if (bit_number > 63 && bit_number < 98) {
//     set_bit(&num->bits[2], bit_number);
// }

// }

int stepen(s21_decimal num) {
  int check = 24;
  for (int i = 24; i < 32; i++) {
    set_bit_0(&num.bits[3], check);
    check++;
  }
  num.bits[3] = num.bits[3] >> 16;
  if (num.bits[3] < 29) {
    return num.bits[3];
  } else {
    return -1;
  }
}

// s21_decimal create_decimal(int data1, int data2, int data3, int data4) {
//     s21_decimal decimal = {0};

//     decimal.bits[0] = data1;
//     decimal.bits[1] = data2;
//     decimal.bits[2] = data3;
//     decimal.bits[3] = data4;

//     return decimal;

// }

// void check_and_change_bit_3(s21_decimal *value){
//     int mask = 2130771967; // 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1
//     1 1 1 1 1 1 1 1 Mask for unused bits
// if((mask &= value->bits[3]) == 0) {
//     printf("DA");
// } else {
//     value->bits[3] &= ~(mask);
// }

// }

void clear_decimal(s21_decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
}

// int check_exp(s21_decimal value) {
//     int error = 0;
//     if(stepen(value) > 28) {
//         error = 1;
//     }
//     return error;
// }

// int s21_sravnenie(s21_decimal value1, s21_decimal value2) {

// int return_value = -1;

// if(get_sign(&value1) != get_sign(&value2)) {
//     return return_value = 0;
// }

// }
// int chet(s21_decimal value) {
// int chet_check = -1; //if 0 - chet if 1 - nechet
// if ((value.bits[0] & 1) == 1) {
//     chet_check = 1;
// } else {
//     chet_check = 0;
// }

// return chet_check;
// }

int check_dec_is_null(s21_decimal src) {
  int err = 0;
  if (!src.bits[0] && !src.bits[1] && !src.bits[2]) err = 1;
  return err;
}

// void aligment_scale(s21_decimal *first, s21_decimal *second) {
// if(stepen(*first) > stepen(*second)) {
//     while(stepen(*first) - stepen(*second)) {
//         unsigned int overflow_0 = 0, overflow_1 = 0, overflow_2 = 0;
//         unsigned long long int bits_0 = 0, bits_1 = 0, bits_2 = 0;
//         bits_0 = (unsigned long long int)second->bits[0] * 10;
//         if(MAX_UINT <= bits_0) overflow_0 = bits_0 / MAX_UINT;
//         bits_1 = (unsigned long long int)second->bits[1] * 10 + overflow_0;
//         if(MAX_UINT <= bits_1) overflow_1 = bits_1 / MAX_UINT;
//         bits_2 = (unsigned long long int)second->bits[2] * 10 + overflow_1;
//         if(MAX_UINT <= bits_2) overflow_2 = 1;
//         if(overflow_2) {
//             div_10(first, second);
//             break;
//         }
//         second->bits[0] = bits_0 % MAX_UINT;
//         // if(bits_1 > 0) set_bit_0(&second->bits[0], 0);
//         second->bits[1] = bits_1 % MAX_UINT;
//         second->bits[2] = bits_2 % MAX_UINT;
//         second->bits[3] += 1U << 16;
//         printf("%d", stepen(*second));
//     }
// } else if(stepen(*first) < stepen(*second)) {
//     aligment_scale(second, first);
// }

// }

void aligment_scale(s21_decimal *first, s21_decimal *second) {
  int carry;
  if (stepen(*first) > stepen(*second)) {
    while (stepen(*first) - stepen(*second)) {
      carry = 0;
      for (int j = 0; j < 3; j++) {
        unsigned long long sum =
            (unsigned long long)second->bits[j] * 10 + carry;
        second->bits[j] = (int)(sum & 0xFFFFFFFF);
        carry = (int)(sum >> 32);
      }
      second->bits[3] += 1U << 16;
    }
  } else if (stepen(*first) < stepen(*second)) {
    aligment_scale(second, first);
  }
}

void scale_write(s21_decimal *num, int scale) {
  int sign = -1;
  if (check_bit(num->bits[3], 31) == 0) {
    sign = 0;
  } else {
    sign = 1;
  }
  num->bits[3] = scale << 16;
  if (check_bit(num->bits[3], 31) != sign) {
    s21_negate(*num, num);
  }
}

void truncate_buff(s21_decimal *buf, int exp) {
  unsigned long long u_num;
  int tmp_int = 0;
  for (int i = 0; i < exp; i++) {
    u_num = buf->bits[2];
    for (int j = 2; j >= 0; j--) {
      if (j == 0) {
        buf->bits[j] = u_num / 10;
      } else {
        tmp_int = u_num % 10;
        buf->bits[j] = u_num / 10;
        u_num = tmp_int * (overflow) + buf->bits[j - 1];
      }
    }
  }
  buf->bits[3] &= (2147483648);  // 10000000000000000000000000000000 mask to
                                 // sett all bits exept 31 to 0
}

// int check_dec_is_null(s21_decimal src) {
//   return !src.bits[0] && !src.bits[1] && !src.bits[2];
// }

int get_pow(s21_decimal src) {
  int dst = 0;
  for (int i = 16; i <= 23; i++) {
    dst += check_bit(src.bits[3], i) * ((int)pow(2, i - 16));
  }
  return dst;
}

void s21_normalize_big(big_decimal *value_1, big_decimal *value_2, int *scale1,
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

void to_big(s21_decimal from, big_decimal *to) {
  for (int i = 0; i < 3; i++) {
    to->bits[i] = from.bits[i];
  }
  to->bits[3] = 0;
  to->bits[4] = 0;
  to->bits[5] = 0;
  to->scale = get_pow(from);
}
