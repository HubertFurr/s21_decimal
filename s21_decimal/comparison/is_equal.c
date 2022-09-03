#include "../../s21_decimal.h"

/**
 * @brief Проверяет, что число value_1 равно value_2
 * Проверка входных данных на корректность не осуществляется и должна производится за пределами функции
 *
 * Перед выполнением сравнения у чисел отбрасываются конечные нули (функцией s21_remove_trailing_zeros()):
 *
 * 123.510 -> 123.51
 * 0.00000 -> 0
 * 500.001 -> 500.001
 * 500.10 -> 500.1
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое сравниваемое число
 * @param value_2 второе сравниваемое число
 * @return int результат сравнения:
 *          1 - true
 *          0 - false
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    s21_comparison_result code = S21_COMPARISON_TRUE;

    s21_decimal tmp1 = s21_remove_trailing_zeros(value_1);
    s21_decimal tmp2 = s21_remove_trailing_zeros(value_2);

    if (tmp1.bits[0] == 0 && tmp1.bits[1] == 0
        && tmp1.bits[2] == 0 && tmp2.bits[0] == 0
        && tmp2.bits[1] == 0 && tmp2.bits[2] == 0) {
        // Считаем -0 == 0, поэтому знаковый бит не проверяем, степени уже будут равны
        // после отбрасывания конечных нулей
        code = S21_COMPARISON_TRUE;
    } else {
        code = tmp1.bits[0] == tmp2.bits[0]
            && tmp1.bits[1] == tmp2.bits[1]
            && tmp1.bits[2] == tmp2.bits[2]
            && tmp1.bits[3] == tmp2.bits[3];
    }

    return code;
}
