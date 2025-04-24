#ifndef DECIMAL_H
#define DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UINT 4294967295
#define MAX_INT 2147483647
#define MAX_MIN_INT 2147483648
#define overflow 4294967296
#define MIN_INT -2147483648
#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL -1 * MAX_DECIMAL
#define MAX_POW 28
#define FLOAT_ACCURACY 7

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
  int scale;
} big_decimal;

int check_bit(unsigned int number, int bit_number);
int get_sign(s21_decimal num);
void set_bit(unsigned int *number, int bit_number);
void set_bit_0(unsigned int *number, int bit_number);
void set_bit_mantissa(s21_decimal *num, int bit_number);
void print_bits(unsigned int number);
int s21_negate(s21_decimal value, s21_decimal *result);
int stepen(s21_decimal num);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
s21_decimal create_decimal(int bit0, int bit1, int bit2, int bit3);
void check_and_change_bit_3(s21_decimal *value);
void clear_decimal(s21_decimal *value);
int check_exp(s21_decimal value);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int chet(s21_decimal value);
void truncate_buff(s21_decimal *buf, int exp);
int check_last_num(s21_decimal buf, int exp);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
void scale_write(s21_decimal *num, int scale);
void aligment_scale(s21_decimal *first, s21_decimal *second);
void div_10(s21_decimal *first, s21_decimal *second);
int check_dec_is_null(s21_decimal src);
// int s21_is_less(s21_decimal, s21_decimal);
// int s21_is_greater(s21_decimal, s21_decimal);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void big_to_decimal(s21_decimal *small, big_decimal *big, int *error_code,
                    int sign, int *scale);
void bank_rounding(big_decimal *value, int *scale);
int divide_by_ten(big_decimal *value, int times, int *scale);
void inc(big_decimal *dec);
void big_copy(big_decimal *big_to, big_decimal big_from);
int big_is_zero(big_decimal n);
void normalisation(big_decimal *value_1, big_decimal *value_2, int *scale1,
                   int *scale2);
int check_max_big(big_decimal *value);
void set_bit_big(big_decimal *value, int index, int bit);
int get_bit_big(big_decimal value, int index);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
s21_decimal abs_decimal(s21_decimal value);
int is_equal_big(big_decimal value_1, big_decimal value_2);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int is_greater_big(big_decimal value1, big_decimal value2);
void big_shift_left(big_decimal *value, int shift);
void sub_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void mul_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void add_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result);
void zero_big(big_decimal *value);
void zero_decimal(s21_decimal *value);
void decimal_to_big(s21_decimal *small, big_decimal *big);
void to_big(s21_decimal from, big_decimal *to);
void s21_normalize_big(big_decimal *value_1, big_decimal *value_2, int *scale1,
                       int *scale2);
void mul_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result);
void zero_big(big_decimal *value);
int get_pow(s21_decimal src);
int get_scale(s21_decimal value);
int check_dec_is_null(s21_decimal src);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
void div_big_decimal(big_decimal value_1, big_decimal value_2,
                     big_decimal *result, int *scale1, int *scale2,
                     int *scale_res);

#endif
