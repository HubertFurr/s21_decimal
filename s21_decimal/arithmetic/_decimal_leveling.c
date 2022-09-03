#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

/**
 * @brief Выравнивание порядков степеней чисел value_1 и value_2.
 * Степень и знак чисел зануляются при выравнивании. Выравненные числа - это только целая часть чисел
 *
 * Например:
 * 123 (степень 0) и 7.898 (степень 3)
 * 123      -> 123.000 (степень 3)
 * 7.898    ->   7.898 (степень 3)
 *
 * Результат: 123000 и 7898
 *
 * 6148914689804861440.1 (степень 1) и 0.0000000000000000000000000001 (степень 28)
 * 6148914689804861440.1            -> 6148914689804861440.1000000000000000000000000000 (степень 28)
 * 0.0000000000000000000000000001   ->                   0.0000000000000000000000000001 (степень 28)
 *
 * Результат:  61489146898048614401000000000000000000000000000 и 1
 *
 * Т.к при выравнивании огромного числа и маленького числа с большим количество знаков после запятой
 * числа знаков decimal может не хватить, то результат записывается в число типа int256
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое число типа decimal
 * @param value_2 второе число типа decimal
 * @param value_1l выравненное число value_1
 * @param value_2l выравненное число value_2
 */
void s21_decimal_leveling(s21_decimal value_1, s21_decimal value_2, s21_int256 *value_1l,
                          s21_int256 *value_2l) {
    int power1 = s21_decimal_get_power(value_1);
    int power2 = s21_decimal_get_power(value_2);
    s21_decimal tmp1 = value_1;
    s21_decimal tmp2 = value_2;

    s21_decimal_null_service_bits(&tmp1);
    s21_decimal_null_service_bits(&tmp2);

    if (power1 > power2) {
        *value_1l = s21_create_int256_from_decimal(tmp1);
        *value_2l = s21_int128_binary_multiplication(tmp2, s21_int128_get_ten_pow(power1 - power2));
    } else if (power1 < power2) {
        *value_1l = s21_int128_binary_multiplication(tmp1, s21_int128_get_ten_pow(power2 - power1));
        *value_2l = s21_create_int256_from_decimal(tmp2);
    } else {
        *value_1l = s21_create_int256_from_decimal(tmp1);
        *value_2l = s21_create_int256_from_decimal(tmp2);
    }
}
