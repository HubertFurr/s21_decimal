#include "./../arithmetic/arithmetic.h"
#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./comparison.h"

/**
 * @brief Проверяет, что число value_1 меньше value_2
 * Проверка входных данных на корректность не осуществляется и должна производится за пределами функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое сравниваемое число
 * @param value_2 второе сравниваемое число
 * @return int результат сравнения:
 *          1 - true
 *          0 - false
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;

    int sign1 = s21_decimal_get_sign(value_1);
    int sign2 = s21_decimal_get_sign(value_2);

    if (s21_is_equal(value_1, s21_decimal_get_zero()) && s21_is_equal(value_2, s21_decimal_get_zero())) {
        // Если оба 0, то всегда false
        code = S21_COMPARISON_FALSE;
    } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
        // Отрицательное число (value_1) всегда меньше положительного (value_2)
        code = S21_COMPARISON_TRUE;
    } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
        // Положительное число (value_1) всегда не меньше отрицательного (value_2)
        code = S21_COMPARISON_FALSE;
    } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
        // Отрицательные числа делаем положительными и сравниваем наоборот
        // Т.к. 2 < 3, но -2 > -3
        code = s21_is_less_handle(s21_abs(value_2), s21_abs(value_1));
    } else {
        // В остальных случаях просто сравниваем
        code = s21_is_less_handle(value_1, value_2);
    }

    return code;
}

/**
 * @brief вспомогательная функция, которая сравнивает 2 положительных числа (что число value_1 меньше value_2)
 * Проверка входных данных на корректность не осуществляется и должна производится за пределами функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое сравниваемое число
 * @param value_2 второе сравниваемое число
 * @return int результат сравнения:
 *          1 - true
 *          0 - false
 */
int s21_is_less_handle(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_FALSE;
    s21_decimal tmp1 = value_1;
    s21_decimal tmp2 = value_2;
    s21_int256 tmp1l;
    s21_int256 tmp2l;

    // Выравниваем степени слагаемых (знак и степень при этом будут обнулены)
    s21_decimal_leveling(tmp1, tmp2, &tmp1l, &tmp2l);

    // Сравниваем выравненные числа
    int compare = s21_int256_binary_compare(tmp1l, tmp2l);

    if (compare == -1) {
        code = S21_COMPARISON_TRUE;
    } else {
        code = S21_COMPARISON_FALSE;
    }

    return code;
}
