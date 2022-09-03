#include <limits.h>

#include "../../s21_decimal.h"
/**
 * @brief конвертирует int src в decimal dst
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый int
 * @param dst указатель на decimal, в который будет записан результат конвертации
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;

    if (!dst) {
        // Если указатель на decimal является NULL
        code = S21_CONVERSION_ERROR;
    } else {
        *dst = s21_decimal_get_zero();
        int sign;

        if (src < 0) {
            sign = S21_NEGATIVE;
            if (src != INT_MIN) {
                // У INT_MIN не надо менять знак, ибо:
                // negation of -2147483648 cannot be represented in type 'int';
                // А при этом битовое представление -2147483648 нас устраивает без дополнительных операций
                src = -src;
            }
        } else {
            sign = S21_POSITIVE;
        }

        dst->bits[0] = src;
        // Определяем знак результата, исходя из знака числа src (типа int)
        s21_decimal_set_sign(dst, sign);
    }

    return code;
}
