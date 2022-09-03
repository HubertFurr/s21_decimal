#ifndef SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_
#define SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_

#include <stdlib.h>

#include "./../types.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/**
 * @brief коды ошибок функций-преобразователей
 * 0 - OK
 * 1 - ошибка конвертации
 */
typedef enum s21_conversion_result {
    S21_CONVERSION_OK = 0,
    S21_CONVERSION_ERROR = 1
} s21_conversion_result;

#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
    0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

// Вспомогательные функции

s21_decimal s21_decimal_get_from_char(char c);
int s21_get_float_exp_from_string(char *str);
s21_decimal s21_float_string_to_decimal(char *str);

// void s21_get_float_mantissa_bits_string(float number, char *str);
// void s21_get_uint32_bits_string(uint32_t number, char *str);
// void s21_get_bits_string(size_t const size, void const *const ptr, char *str);

#endif  //  SRC_S21_DECIMAL_CONVERSION_CONVERSION_H_
