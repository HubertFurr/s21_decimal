#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

/**
 * @brief Функция рассчитывает остаток от деления value_1 на value_2
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 делимое
 * @param value_2 делитель
 * @param result остаток от деления
 * @return int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;

    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_ARITHMETIC_ERROR;
    } else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        // Проверяем, что value_1 и value_2 являются корректными decimal
        code = S21_ARITHMETIC_ERROR;
        *result = s21_decimal_get_inf();
    } else if (s21_is_equal(value_2, s21_decimal_get_zero())) {
        // Проверяем деление на ноль
        code = S21_ARITHMETIC_ZERO_DIV;
        *result = s21_decimal_get_inf();
    } else if (s21_is_less(s21_abs(value_1), s21_abs(value_2))) {
        // Если делимое меньше делителя, то сразу записываем делимое в результат
        code = S21_ARITHMETIC_OK;
        *result = value_1;
    } else {
        // В остальных случаях считаем остаток от деления
        *result = s21_decimal_get_zero();

        int sign1 = s21_decimal_get_sign(value_1);
        int power1 = s21_decimal_get_power(value_1);
        int power2 = s21_decimal_get_power(value_2);
        int max_power = s21_max(power1, power2);
        s21_int256 value_1l;
        s21_int256 value_2l;
        s21_int256 remainder = s21_create_int256_from_decimal(s21_decimal_get_zero());

        // Выравниваем степени делителя и делимого (знак и степень при этом будут обнулены)
        s21_decimal_leveling(value_1, value_2, &value_1l, &value_2l);
        // Считаем остаток от деления двух целых чисел, полученных после выравнивания степеней
        s21_int256_binary_division(value_1l, value_2l, &remainder);
        // Выставляем степень результата, анализируя входные данные
        s21_decimal_set_power(&remainder.decimals[0], max_power);

        *result = remainder.decimals[0];
        // Выставляем знак результата, анализируя входные данные
        s21_decimal_set_sign(result, sign1);
    }

    return code;
}
