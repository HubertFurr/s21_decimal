#include "./../types.h"

/**
 * @brief проверяет, установлен ли в числе number бит index
 *
 * Например, 123 - 00000000 00000000 00000000 01111011
 * для index = 0 return 1
 * для index = 1 return 1
 * для index = 2 return 0
 * для index = 31 return 0
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param number
 * @param index
 * @return int результат провреки:
 *          0 - бит не установлен.
 *          1 - бит установлен.
 */
int s21_is_set_bit(int number, int index) {
    return !!(number & (1U << index));
}

/**
 * @brief устанавливает бит index в числе number значением 1
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param number
 * @param index
 * @return новый int с установленным битом
 */
int s21_set_bit(int number, int index) {
    return number | (1U << index);
}

/**
 * @brief устанавливает бит index в числе number значением 0
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param number
 * @param index
 * @return новый int с установленным битом
 */
int s21_reset_bit(int number, int index) {
    return number & ~(1U << index);
}

/**
 * @brief Проверяет, установлен ли бит (имеет значение 1) номер index в числе decimal
 * Валидация данных не осуществляется и должна осуществляться до вызова функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal проверяемое число типа decimal
 * @param index номер проверяемого бита
 * @return int результат провреки:
 *          0 - бит не установлен.
 *          1 - бит установлен.
 */
int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
    return s21_is_set_bit(decimal.bits[index / MAX_BLOCK_BITS], index % MAX_BLOCK_BITS);
}

/**
 * @brief Устанавливает значение 1 для бита номер index в числе decimal
 * Валидация данных не осуществляется и должна осуществляться до вызова функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal число типа decimal, бит которого мы хотим установить
 * @param index номер устанавливаеиого бита
 * @return s21_decimal измененный decimal (у которого бит index установлен)
 */
s21_decimal s21_decimal_set_bit(s21_decimal decimal, int index) {
    decimal.bits[index / MAX_BLOCK_BITS] =
        s21_set_bit(decimal.bits[index / MAX_BLOCK_BITS], index % MAX_BLOCK_BITS);
    return decimal;
}

/**
 * @brief Находит ближайший к старшему биту установленный бит (который имеет значение 1) числа decimal
 * Например:
 * 10000000 00000000 00000000 00000000 ... 00000000 10000001 00011000 00000000 - вернет 127
 * 00100000 00000000 00000000 00000000 ... 00000000 00000000 00000000 10000000 - вернет 125
 * 00000000 00000000 00000000 00000000 ... 00000000 00000000 00000000 10000000 - вернет 7
 * 00000000 00000000 00000000 00000000 ... 00000000 00000000 00000000 00000001 - вернет 0
 *
 * Если все биты равны 0, то вернет -1
 * @param decimal проверяемый decimal
 * @return int индекс найденного бита, либо -1, если все биты равны 0
 */
int s21_decimal_get_not_zero_bit(s21_decimal decimal) {
    int result = -1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        if (s21_decimal_is_set_bit(decimal, i)) {
            result = i;
            break;
        }
    }

    return result;
}
