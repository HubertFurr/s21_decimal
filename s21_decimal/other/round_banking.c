#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"

/**
 * @brief производит округление числа по правилам банковского округления.
 * Число передается отдельно в виде целой части integral и дробной части fractional
 *
 * Вспомогательная функция для внутренних расчетов, переполнение не контролируется и осуществляется
 * за пределами функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param integral целая часть числа
 * @param fractional дробная часть числа
 * @return s21_decimal округленный результат
 */
s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
    s21_decimal zerofive = s21_decimal_get_zerofive();
    s21_decimal result;

    if (s21_is_equal(fractional, zerofive)) {
        // Если дробная часть ровно 0.5
        if (s21_decimal_even(integral)) {
            // Если целая часть четная, то оставляем её
            result = integral;
        } else {
            // Если целая часть нечетная, то увеличиваем её на 1
            result = s21_int128_binary_addition(integral, s21_decimal_get_one());
        }
    } else if (s21_is_greater(fractional, zerofive)) {
        // Если дробная часть > 0.5, то увеличиваем целую часть на 1
        result = s21_int128_binary_addition(integral, s21_decimal_get_one());
    } else {
        // Если дробная часть < 0.5, то оставляем целую часть без изменений
        result = integral;
    }

    return result;
}
