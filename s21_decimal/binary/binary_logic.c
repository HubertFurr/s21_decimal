#include "./binary.h"
#include "./../helpers/helpers.h"

/**
 * @brief Побитовое «И» для двоичных положительных целых чисел размера 128бит.
 * Эквивалентно decimal1 & decimal2
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal1 
 * @param decimal2 
 * @return s21_decimal результат применения decimal1 & decimal2 
 */
s21_decimal s21_int128_binary_and(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = s21_decimal_get_zero();
    result.bits[0] = decimal1.bits[0] & decimal2.bits[0];
    result.bits[1] = decimal1.bits[1] & decimal2.bits[1];
    result.bits[2] = decimal1.bits[2] & decimal2.bits[2];
    result.bits[3] = decimal1.bits[3] & decimal2.bits[3];

    return result;
}

/**
 * @brief Исключающее «или» для двоичных положительных целых чисел размера 128бит.
 * Эквивалентно decimal1 ^ decimal2
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal1 
 * @param decimal2 
 * @return s21_decimal результат применения decimal1 ^ decimal2
 */
s21_decimal s21_int128_binary_xor(s21_decimal decimal1, s21_decimal decimal2) {
    s21_decimal result = s21_decimal_get_zero();
    result.bits[0] = decimal1.bits[0] ^ decimal2.bits[0];
    result.bits[1] = decimal1.bits[1] ^ decimal2.bits[1];
    result.bits[2] = decimal1.bits[2] ^ decimal2.bits[2];
    result.bits[3] = decimal1.bits[3] ^ decimal2.bits[3];

    return result;
}

/**
 * @brief Дополнение (побитовая инверсия) для двоичных положительных целых чисел размера 128бит.
 * Эквивалентно ~decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal
 * @return s21_decimal результат применения ~decimal
 */
s21_decimal s21_int128_binary_not(s21_decimal decimal) {
    s21_decimal result = s21_decimal_get_zero();
    result.bits[0] = ~decimal.bits[0];
    result.bits[1] = ~decimal.bits[1];
    result.bits[2] = ~decimal.bits[2];
    result.bits[3] = ~decimal.bits[3];

    return result;
}
