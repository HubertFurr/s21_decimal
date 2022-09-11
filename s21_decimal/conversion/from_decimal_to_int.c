#include <math.h>
#include <stdio.h>

#include "../../s21_decimal.h"
#include "../binary/binary.h"
#include "../comparison/comparison.h"
#include "../helpers/helpers.h"

/**
 * @brief конвертирует decimal src в int dst
 * Если в числе src есть дробная часть, то её отбрасываем, например:
 * 0.9 преобразуется в 0
 * 123.555 преобразуется в 123
 *
 * Касательно перевода числа - алгоритм перевода двоичного числа в десятичное довольно очевиден
 * и легко гуглится :)
 * Разберем на примере числа 101001011:
 *
 * 101001011 = 1*2^8 + 0*2^7 + 1*2^6 + 0*2^5 + 0*2^4 + 1*2^3 + 0*2^2 + 1*2^1 + 1*2^0 =
 * = 256 + 0 + 64 + 0 + 0 + 8 + 0 + 2 + 1 = 331
 *
 * Т.е. младший бит - это нулевая степень двойки, 1й бит - первая степень, 2й бит - вторая степень и т.д.
 * И эта степень умножается на 1 или 0 (смотря какое значение имеет бит двоичного числа)
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый decimal
 * @param dst указатель на int, в который будет записан результат конвертации
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;

    if (!dst) {
        // Если указатель на int является NULL
        code = S21_CONVERSION_ERROR;
    } else if (!s21_is_correct_decimal(src)) {
        // Проверяем, что src является корректным decimal
        code = S21_CONVERSION_ERROR;
        *dst = 0;
    } else {
        *dst = 0;
        s21_decimal truncated_decimal = s21_decimal_get_zero();
        // Отбрасываем дробную часть decimal
        s21_truncate(src, &truncated_decimal);

        if (s21_is_less(truncated_decimal, s21_decimal_get_int_min()) == S21_COMPARISON_TRUE) {
            // Если decimal меньше -2147483648, то сконвертировать нельзя
            code = S21_CONVERSION_ERROR;
        } else if (s21_is_greater(truncated_decimal, s21_decimal_get_int_max()) == S21_COMPARISON_TRUE) {
            // Если decimal больше 2147483647, то сконвертировать нельзя
            code = S21_CONVERSION_ERROR;
        } else {
            // В остальных случаях производим конвертацию
            /**
             * самый простой способ:
             * *dst = truncated_decimal.bits[0];
             * а потом определить знак путем анализа исходного decimal
             * но это работает только для целочисленных типов размера 32бит и менее
             * ниже универсальный способ, который подойдет и для long, например
             * (чисто для разнообразия)
             */
            for (int i = 0; i < MAX_BLOCK_NUMBER; i++) {
                // Пример расчета есть в брифе
                if (s21_decimal_is_set_bit(truncated_decimal, i) != 0) {
                    *dst += pow(2, i);
                }
            }

            // Определяем знак результата, исходя из знака числа src (типа decimal)
            if (s21_decimal_get_sign(src) == S21_NEGATIVE && *dst != -2147483648) {
                // У INT_MIN не надо менять знак, ибо:
                // negation of -2147483648 cannot be represented in type 'int';
                // А при этом для INT_MIN при расчете мы получили переполнение int и правильное значение
                *dst = -*dst;
            }
        }
    }

    return code;
}
