#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"

/**
 * @brief Вычитает из value_1 значение value_2 и записывает результат в result
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 уменьшаемое
 * @param value_2 вычитаемое
 * @param result разность
 * @return int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_ARITHMETIC_ERROR;
    } else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        // Проверяем, что value_1 и value_2 являются корректными decimal
        code = S21_ARITHMETIC_ERROR;
        *result = s21_decimal_get_inf();
    } else {
        // В остальных случаях считаем разность
        *result = s21_decimal_get_zero();
        s21_decimal res = s21_decimal_get_zero();
        int sign1 = s21_decimal_get_sign(value_1);
        int sign2 = s21_decimal_get_sign(value_2);

        if (sign1 == S21_POSITIVE && sign2 == S21_POSITIVE) {
            // Если уменьшаемое и вычитаемое положительные
            if (s21_is_greater_or_equal(value_1, value_2)) {
                // Если уменьшаемое больше или равно вычитаемому
                // Вычитаем из уменьшаемого вычитаемое
                // v1 = 2; v2 = 1;
                // v1 - v2 = 2 - 1 = v1 - v2
                code = s21_sub_handle(value_1, value_2, &res);
            } else {
                // Если уменьшаемое меньше вычитаемомого
                // Вычитаем из вычитаемого уменьшаемое, у результата меняем знак
                // v1 = 1; v2 = 2;
                // v1 - v2 = 1 - 2 = - (2 - 1) = -(v2 - v1)
                code = s21_sub_handle(value_2, value_1, &res);
                s21_negate(res, &res);
            }
        } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
            // Если уменьшаемое положительное, а вычитаемое отрицательное
            // вызываем суммирование (используя abs)
            // v1 = 2; v2 = -1;
            // v1 - v2 = 2 - -1 = 2 + 1 = v1 + abs(v2)
            // v1 = 1; v2 = -2;
            // v1 - v2 = 1 - -2 = 1 + 2 = v1 + abs(v2)
            code = s21_add(value_1, s21_abs(value_2), &res);
        } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
            // Если уменьшаемое отрицательное, а вычитаемое положительное
            // вызываем суммирование (используя abs), у результата меняем знак
            // v1 = -2; v2 = 1;
            // v1 - v2 = -2 - 1 = - (2 + 1) = - (abs(v1) + v2)
            // v1 = -1; v2 = 2;
            // v1 - v2 = -1 - 2 = - (1 + 2) = - (abs(v1) + v2)
            code = s21_add(s21_abs(value_1), value_2, &res);
            s21_negate(res, &res);
        } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
            // Если уменьшаемое и вычитаемое отрицательные
            if (s21_is_greater_or_equal(value_1, value_2)) {
                // Если уменьшаемое больше или равно вычитаемому
                // Вычитаем из вычитаемого уменьшаемое (используя abs)
                // v1 = -1; v2 = -2;
                // v1 - v2 = -1 - -2 = -1 + 2 = 2 - 1 = abs(v2) - abs(v1)
                code = s21_sub_handle(s21_abs(value_2), s21_abs(value_1), &res);
            } else {
                // Если уменьшаемое меньше вычитаемомого
                // Вычитаем из уменьшаемого вычитаемое (используя abs), у результата меняем знак
                // v1 = -2; v2 = -1;
                // v1 - v2 = -2 - -1 = -2 + 1 = 1 - 2 = - (2 - 1) = - (abs(v1) - abs(v2))
                code = s21_sub_handle(s21_abs(value_1), s21_abs(value_2), &res);
                s21_negate(res, &res);
            }
        }

        if (s21_decimal_get_sign(res) == S21_NEGATIVE && code == S21_ARITHMETIC_BIG) {
            code = S21_ARITHMETIC_SMALL;
        }

        *result = res;
    }

    return code;
}

/**
 * @brief Вспомогательная функция, которая осуществляет вычитание двух положительных чисел decimal,
 * при этом value_1 всегда больше value_2
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 уменьшаемое
 * @param value_2 вычитаемое
 * @param result разность
 * @return int код ошибки, для передачи в родительскую функцию (и последующей обработки)
 */
int s21_sub_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    s21_int256 value_1l;
    s21_int256 value_2l;
    int power1 = s21_decimal_get_power(value_1);
    int power2 = s21_decimal_get_power(value_2);
    int max_power = s21_max(power1, power2);

    // Выравниваем степени уменьшаемого и вычитаемого (знак и степень при этом будут обнулены)
    s21_decimal_leveling(value_1, value_2, &value_1l, &value_2l);
    // Вычитаем выравненные уменьшаемое и вычитаемое как два огромных целых числа
    s21_int256 res = s21_int256_binary_subtraction(value_1l, value_2l);
    // Рассчитываем, на сколько необходимо поделить результат, чтобы вписать его в 96бит числа decimal
    int shift = s21_int256_get_shift_to_decimal(res);
    // Рассчитываем степень будущего результата
    int res_power = max_power - shift;

    if (res_power < 0) {
        // Анализируем степень результата на корректность
        code = S21_ARITHMETIC_BIG;
        *result = s21_decimal_get_inf();
    } else {
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

        *result = res.decimals[0];
    }

    return code;
}
