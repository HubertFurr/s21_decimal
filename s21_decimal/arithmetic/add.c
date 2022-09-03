#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"

/**
 * @brief Суммирует value_1 и value_2 и записывает результат в result
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое слагаемое
 * @param value_2 второе слагаемое
 * @param result сумма
 * @return int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_ARITHMETIC_ERROR;
    } else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        // Проверяем, что value_1 и value_2 являются корректными decimal
        code = S21_ARITHMETIC_ERROR;
        *result = s21_decimal_get_inf();
    } else {
        // В остальных случаях считаем сумму
        *result = s21_decimal_get_zero();
        s21_decimal res = s21_decimal_get_zero();

        int sign1 = s21_decimal_get_sign(value_1);
        int sign2 = s21_decimal_get_sign(value_2);

        if (sign1 == S21_POSITIVE && sign2 == S21_POSITIVE) {
            // Если оба слагаемых положительные
            // вызываем суммирование
            // v1 = 2; v2 = 1;
            // v1 + v2 = 2 + 1 = v2 + v1
            // v1 = 1; v2 = 2;
            // v1 + v2 = 1 + 2 = v2 + v1
            code = s21_add_handle(value_1, value_2, &res);
        } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
            // Если первое - положительное, второе - отрицательное
            // вызываем вычитание (используя abs)
            // v1 = 2; v2 = -1;
            // v1 + v2 = 2 + -1 = 2 - 1 = v1 - abs(v2)
            // v1 = 2; v2 = -3;
            // v1 + v2 = 2 + -3 = 2 - 3 = v1 - abs(v2)
            code = s21_sub(value_1, s21_abs(value_2), &res);
        } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
            // Если первое - отрицательное, второе - положительное
            // вызываем вычитание (используя abs), у результата меняем знак
            // v1 = -2; v2 = 1;
            // v1 + v2 = -2 + 1 = -(2 - 1) = -(abs(v1) - v2)
            // v1 = -1; v2 = 2;
            // v1 + v2 = -1 + 2 = -(1 - 2) = -(abs(v1) - v2)
            code = s21_sub(s21_abs(value_1), value_2, &res);
            s21_negate(res, &res);
        } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
            // Если оба слагаемых отрицательные
            // вызываем суммирование (используя abs), у результата меняем знак
            // v1 = -2; v2 = -1;
            // v1 + v2 = -2 + -1 = - (2 + 1) = -(abs(v1) + abs(v2))
            // v1 = -1; v2 = -2;
            // v1 + v2 = -1 + -2 = - (1 + 2) = -(abs(v1) + abs(v2))
            code = s21_add_handle(s21_abs(value_1), s21_abs(value_2), &res);
            s21_negate(res, &res);
        }

        if (s21_decimal_get_sign(res) == S21_NEGATIVE && code == S21_ARITHMETIC_BIG) {
            code = S21_ARITHMETIC_SMALL;
        }

        *result = res;
    }

    return code;
}

/**
 * @brief Вспомогательная функция, которая осуществляет суммирование двух положительных чисел
 * decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое слагаемое
 * @param value_2 второе слагаемое
 * @param result сумма
 * @return int код ошибки, для передачи в родительскую функцию (и последующей обработки)
 */
int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    s21_int256 value_1l;
    s21_int256 value_2l;
    int power1 = s21_decimal_get_power(value_1);
    int power2 = s21_decimal_get_power(value_2);
    int max_power = s21_max(power1, power2);

    // Выравниваем степени слагаемых (знак и степень при этом будут обнулены)
    s21_decimal_leveling(value_1, value_2, &value_1l, &value_2l);
    // Складываем выравненные слагаемые как два огромных целых числа
    s21_int256 res = s21_int256_binary_addition(value_1l, value_2l);
    // Рассчитываем, на сколько необходимо поделить результат, чтобы вписать его в 96бит числа decimal
    int shift = s21_int256_get_shift_to_decimal(res);
    // Рассчитываем степень будущего результата
    int res_power = max_power - shift;

    if (res_power < 0) {
        // Анализируем степень результата на корректность
        code = S21_ARITHMETIC_BIG;
        *result = s21_decimal_get_inf();
    } else {
        // Если результат надо делить более, чем на 10^28, то уменьшаем его, чтобы далее делить на 10^28
        while (shift > 28) {
            res =
                s21_int256_binary_division(res, s21_create_int256_from_decimal(s21_decimal_get_ten()), NULL);
            --shift;
        }

        s21_int256 remainder = s21_create_int256_from_decimal(s21_decimal_get_zero());
        s21_int256 powerten = s21_create_int256_from_decimal(s21_int128_get_ten_pow(shift));

        // Уменьшаем результат, чтобы он поместился в 96бит числа decimal
        // remainder - остаток от деления при этом
        res = s21_int256_binary_division(res, powerten, &remainder);
        // Устанавливаем для остатка степень, чтобы выполнить банковское округление чисел decimal
        s21_decimal_set_power(&remainder.decimals[0], shift);
        // Выполняем банковское округления результата, исходя из остатка от деления remainder
        res.decimals[0] = s21_round_banking(res.decimals[0], remainder.decimals[0]);
        // Устанавливаем степень результата
        s21_decimal_set_power(&res.decimals[0], res_power);

        // Анализируем результат на корректность (переполнение)
        if (!s21_int128_binary_equal_zero(res.decimals[1]) || !s21_is_correct_decimal(res.decimals[0])) {
            code = S21_ARITHMETIC_BIG;
            *result = s21_decimal_get_inf();
        } else {
            *result = res.decimals[0];
        }
    }

    return code;
}
