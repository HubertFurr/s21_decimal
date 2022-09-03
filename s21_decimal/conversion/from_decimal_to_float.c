#include <math.h>

#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./conversion.h"

/**
 * @brief конвертирует decimal src в float dst
 *
 * 078ee41e268ebc6fdbced3ebb41c40559be01974 - non-full-working version with alternative algorithm
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый decimal
 * @param dst указатель на float, в который будет записан результат конвертации
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;
    if (!dst) {
        // Если указатель на float является NULL
        code = S21_CONVERSION_ERROR;
    } else if (!s21_is_correct_decimal(src)) {
        // Проверяем, что src является корректным decimal
        code = S21_CONVERSION_ERROR;
        *dst = 0.0;
    } else if (s21_is_equal(src, s21_decimal_get_zero())) {
        // Отдельно обрабатываем 0 и -0
        int sign = s21_decimal_get_sign(src);
        if (sign == S21_NEGATIVE) {
            *dst = -0.0;
        } else {
            *dst = 0.0;
        }
        code = S21_CONVERSION_OK;
    } else {
        // В остальных случаях осуществляем конвертацию
        *dst = 0.0;
        // float и long double не подойдут ^_^
        double tmp = 0.0;
        // Запоминаем знак и степень decimal
        int sign = s21_decimal_get_sign(src);
        int power = s21_decimal_get_power(src);

        // Каждый бит decimal переводим в double, для этого каждый бит представляем как 2 в степени
        // позиции бита и прибавляет к результату
        for (int i = 0; i < MAX_BLOCK_NUMBER; i++) {
            if (s21_decimal_is_set_bit(src, i) != 0) {
                tmp += pow(2.0, i);
            }
        }

        // Затем учитываем степень и корректируем итоговый результат
        double powerten = pow(10, power);
        tmp /= powerten;

        if (sign == S21_NEGATIVE) {
            tmp *= -1.0;
        }

        *dst = (float)tmp;
    }

    return code;
}
