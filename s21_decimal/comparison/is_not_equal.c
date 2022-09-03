#include "./comparison.h"

/**
 * @brief Проверяет, что число value_1 не равно value_2
 * Проверка входных данных на корректность не осуществляется и должна производится за пределами функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое сравниваемое число
 * @param value_2 второе сравниваемое число
 * @return int результат сравнения:
 *          1 - true
 *          0 - false
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    return !s21_is_equal(value_1, value_2);
}
