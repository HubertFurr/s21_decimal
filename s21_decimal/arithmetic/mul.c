#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"
/**
 * @brief Умножает value_1 на value_2 и записывает результат в result
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первый множитель
 * @param value_2 второй множитель
 * @param result произведение
 * @return int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;

    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_ARITHMETIC_ERROR;
    } else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        // Проверяем, что value_1 и value_2 являются корректными decimal
        code = S21_ARITHMETIC_ERROR;
        *result = s21_decimal_get_inf();
    } else {
        // В остальных случаях считаем произведение
        *result = s21_decimal_get_zero();
        s21_decimal res = s21_decimal_get_zero();

        int sign1 = s21_decimal_get_sign(value_1);
        int sign2 = s21_decimal_get_sign(value_2);

        if (sign1 == S21_POSITIVE && sign2 == S21_POSITIVE) {
            // Если оба множителя положительные
            // вызываем перемножение
            // v1 = 2; v2 = 1;
            // v1 * v2 = 2 * 1 = v2 * v1
            // v1 = 1; v2 = 2;
            // v1 * v2 = 1 * 2 = v2 * v1
            code = s21_mul_handle(value_1, value_2, &res);
        } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
            // Если первый - положительный, второй - отрицательный
            // вызываем перемножение (используя abs), у результата меняем знак
            // v1 = 2; v2 = -1;
            // v1 * v2 = 2 * -1 = - (2 * 1) = -(v1 * abs(v2))
            // v1 = 2; v2 = -3;
            // v1 * v2 = 2 * -3 = - (2 * 3) = -(v1 * abs(v2))
            code = s21_mul_handle(value_1, s21_abs(value_2), &res);
            s21_negate(res, &res);
        } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
            // Если первый - отрицательный, второй - положительный
            // вызываем перемножение (используя abs), у результата меняем знак
            // v1 = -2; v2 = 1;
            // v1 * v2 = -2 * 1 = -(2 * 1) = -(abs(v1) * v2)
            // v1 = -1; v2 = 2;
            // v1 * v2 = -1 * 2 = -(1 * 2) = -(abs(v1) * v2)
            code = s21_mul_handle(s21_abs(value_1), value_2, &res);
            s21_negate(res, &res);
        } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
            // Если оба множителя отрицательные
            // вызываем перемножение (используя abs)
            // v1 = -2; v2 = -1;
            // v1 * v2 = -2 * -1 = - -(2 * 1) = 2 * 1 = abs(v1) * abs(v2)
            // v1 = -1; v2 = -2;
            // v1 * v2 = -1 * -2 = - -(1 * 2) = 1 * 2 = abs(v1) * abs(v2)
            code = s21_mul_handle(s21_abs(value_1), s21_abs(value_2), &res);
        }

        if (code == S21_ARITHMETIC_BIG) {
            if (s21_decimal_get_sign(res) == S21_NEGATIVE) {
                code = S21_ARITHMETIC_SMALL;
            }
        }

        // Обрабатываем ситуацию, что результат получился слишком маленький (0 < |x| < 1e-28)
        if (code == S21_ARITHMETIC_OK && s21_is_not_equal(value_1, s21_decimal_get_zero()) &&
            s21_is_not_equal(value_2, s21_decimal_get_zero()) && s21_is_equal(res, s21_decimal_get_zero())) {
            code = S21_ARITHMETIC_SMALL;
        }

        *result = res;
    }

    return code;
}

/**
 * @brief Вспомогательная функция, которая осуществляет умножение двух положительных чисел
 * decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первый множитель
 * @param value_2 второй множитель
 * @param result произведение
 * @return int код ошибки, для передачи в родительскую функцию (и последующей обработки)
 */
int s21_mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;
    int power1 = s21_decimal_get_power(value_1);
    int power2 = s21_decimal_get_power(value_2);

    // зануляем степени чисел (степени получим в конце, анализируя входные данные)
    s21_decimal_null_service_bits(&value_1);
    s21_decimal_null_service_bits(&value_2);

    // Перемножаем множители без степеней как два огромных целых числа
    s21_int256 res = s21_int128_binary_multiplication(value_1, value_2);

    // Рассчитываем, на сколько необходимо поделить результат, чтобы вписать его в 96бит числа decimal
    int shift = s21_int256_get_shift_to_decimal(res);
    // Рассчитываем степень будущего результата
    int res_power = power1 + power2 - shift;

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

        // Если слишком много цифр после запятой получается в результате, то корректируем результат
        if (res_power > 28) {
            s21_int256 tmp = res;
            int tmp_power = res_power;
            while (tmp_power > 28) {
                tmp = s21_int256_binary_division(tmp, s21_create_int256_from_decimal(s21_decimal_get_ten()),
                                                 NULL);
                --tmp_power;
            }
            shift = res_power - tmp_power + shift;
            res_power = tmp_power;
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
