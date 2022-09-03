#include "./../helpers/helpers.h"
#include "./arithmetic.h"

/**
 * @brief Функция возвращает модуль числа value
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 decimal, модуль которого считаем
 * @return модуль числа value
 */
s21_decimal s21_abs(s21_decimal value_1) {
    s21_decimal result = value_1;
    s21_decimal_set_sign(&result, S21_POSITIVE);
    return result;
}
