#include "./comparison.h"

/**
 * @brief Проверяет, что число value_1 больше value_2
 * Проверка входных данных на корректность не осуществляется и должна производится за пределами функции
 *
 * 2 > 3 == 3 < 2 - поэтому для проверки вызываем функцию меньше с числами наоборот
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое сравниваемое число
 * @param value_2 второе сравниваемое число
 * @return int результат сравнения:
 *          1 - true
 *          0 - false
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    return s21_is_less(value_2, value_1);
}
