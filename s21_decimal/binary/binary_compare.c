#include "./binary.h"

/**
 * @brief Функция определяет, являются ли все биты decimal нулями
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal
 * @return int 1 - все биты нули, 0 - не все биты нули
 */
int s21_int128_binary_equal_zero(s21_decimal decimal) {
    return decimal.bits[0] == 0 && decimal.bits[1] == 0 && decimal.bits[2] == 0 && decimal.bits[3] == 0;
}

/**
 * @brief Сравнивает побитово 2 числа типа decimal как int128
 * Степень и знак в данном сравнении не выполняют свои функции.
 * Фактически числа сравниваются как uint128
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param d1 первое сравниваемое число
 * @param d2 второе сравниваемое число
 * @return int результат сравнения:
 *          -1 - Значение d1 меньше d2.
 *           0 - Значения d1 и d2 равны.
 *           1 - Значение d1 больше значения d2.
 */
int s21_int128_binary_compare(s21_decimal d1, s21_decimal d2) {
    int result = 0;

    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int b1 = s21_decimal_is_set_bit(d1, i);
        int b2 = s21_decimal_is_set_bit(d2, i);

        if (b1 == 0 && b2 != 0) {
            result = -1;
        }

        if (b1 != 0 && b2 == 0) {
            result = 1;
        }

        if (result != 0) {
            break;
        }
    }

    return result;
}

/**
 * @brief Сравнивает побитово 2 числа int256
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param d1 первое сравниваемое число
 * @param d2 второе сравниваемое число
 * @return int результат сравнения:
 *          -1 - Значение d1 меньше d2.
 *           0 - Значения d1 и d2 равны.
 *           1 - Значение d1 больше значения d2.
 */
int s21_int256_binary_compare(s21_int256 d1, s21_int256 d2) {
    int compare = s21_int128_binary_compare(d1.decimals[1], d2.decimals[1]);

    if (compare == 0) {
        compare = s21_int128_binary_compare(d1.decimals[0], d2.decimals[0]);
    }

    return compare;
}
