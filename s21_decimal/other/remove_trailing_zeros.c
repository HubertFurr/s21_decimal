#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./other.h"

/**
 * @brief Отбрасывает конечные нули числа value
 *
 * Проверка входных данных на корректность не осуществляется и должна производится за пределами функции
 *
 * Примеры работы функции:
 * 123.510 -> 123.51
 * 0.00000 -> 0
 * 500.001 -> 500.001
 * 500.10 -> 500.1
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value
 * @return s21_decimal число без конечных нулей
 */
s21_decimal s21_remove_trailing_zeros(s21_decimal value) {
    s21_decimal result = value;
    int power = s21_decimal_get_power(value);
    int sign = s21_decimal_get_sign(value);

    if (power > 0 && s21_is_correct_decimal(value)) {
        s21_decimal remainder = s21_decimal_get_zero();
        s21_decimal tmp = value;
        s21_decimal_null_service_bits(&tmp);

        // Делим число на 10, уменьшая степень decimal, до тех пор, пока остаток от деления равен нулю
        while (power > 0) {
            tmp = s21_int128_binary_division(tmp, s21_int128_get_ten_pow(1), &remainder);
            if (s21_int128_binary_equal_zero(remainder)) {
                --power;
                result = tmp;
            } else {
                break;
            }
        }
        s21_decimal_set_power(&result, power);
        s21_decimal_set_sign(&result, sign);
    }

    return result;
}
