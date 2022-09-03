#ifndef SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_
#define SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_

#include "./../types.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_handle(s21_int256 value_2l, s21_int256 res, s21_int256 remainder, s21_decimal *result);
int s21_div_calc_fractional(s21_int256 *res, s21_int256 value_2l, s21_int256 *remainder);

void s21_decimal_leveling(s21_decimal value_1, s21_decimal value_2, s21_int256 *value_1l,
                          s21_int256 *value_2l);
s21_decimal s21_abs(s21_decimal value_1);

int s21_int256_get_shift_to_decimal(s21_int256 value);
int s21_max(int value_1, int value_2);

/**
 * @brief коды ошибок арифметических операторов
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
typedef enum s21_arithmetic_result {
    S21_ARITHMETIC_OK = 0,
    S21_ARITHMETIC_BIG = 1,
    S21_ARITHMETIC_SMALL = 2,
    S21_ARITHMETIC_ZERO_DIV = 3,
    S21_ARITHMETIC_ERROR = 4
} s21_arithmetic_result;

#endif  //  SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_
