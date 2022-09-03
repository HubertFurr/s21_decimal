#include "./binary.h"
#include "./../helpers/helpers.h"

/**
 * @brief Битовый сдвиг влево для чисел типа decimal как для int128.
 * Эквивалентно decimal << shift
 * Как и оригинальный сдвиг не осуществляет валидацию входных данных и сдвиги за пределы размеров
 * (валидация должна осуществляться перед вызовом функции)
 * 
 * Фактически функция shift раз вызывает вспомогательную функцию s21_int128_binary_shift_left_one()
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal 
 * @param shift 
 * @return s21_decimal результат применения decimal << shift
 */
s21_decimal s21_int128_binary_shift_left(s21_decimal decimal, int shift) {
    s21_decimal result = decimal;
    while (shift > 0) {
        result = s21_int128_binary_shift_left_one(result);
        --shift;
    }

    return result;
}

/**
 * @brief Битовый сдвиг вправо для чисел типа decimal как для int128.
 * Эквивалентно decimal >> shift
 * Как и оригинальный сдвиг не осуществляет валидацию входных данных и сдвиги за пределы размеров
 * (валидация должна осуществляться перед вызовом функции)
 * 
 * Фактически функция shift раз вызывает вспомогательную функцию s21_int128_binary_shift_right_one()
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal 
 * @param shift 
 * @return s21_decimal результат применения decimal >> shift
 */
s21_decimal s21_int128_binary_shift_right(s21_decimal decimal, int shift) {
    s21_decimal result = decimal;
    while (shift > 0) {
        result = s21_int128_binary_shift_right_one(result);
        --shift;
    }

    return result;
}

/**
 * @brief Битовый сдвиг влево для чисел типа int256.
 * Эквивалентно int256 << shift
 * 
 * Работает аналогично функции для сдвига влево числа типа decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal 
 * @param shift 
 * @return int256 результат применения decimal << shift
 */
s21_int256 s21_int256_binary_shift_left(s21_int256 decimal, int shift) {
    s21_int256 result = decimal;
    while (shift > 0) {
        int b0 = s21_decimal_is_set_bit(result.decimals[0], MAX_BITS - 1);
        result.decimals[0] = s21_int128_binary_shift_left_one(result.decimals[0]);
        result.decimals[1] = s21_int128_binary_shift_left_one(result.decimals[1]);
        if (b0) {
            result.decimals[1] = s21_decimal_set_bit(result.decimals[1], 0);
        }
        --shift;
    }

    return result;
}

/**
 * @brief Битовый сдвиг вправо для чисел типа int256.
 * Эквивалентно int256 >> shift
 * 
 * Работает аналогично функции для сдвига вправо числа типа decimal
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal 
 * @param shift 
 * @return int256 результат применения decimal >> shift
 */
s21_int256 s21_int256_binary_shift_right(s21_int256 decimal, int shift) {
    s21_int256 result = decimal;
    while (shift > 0) {
        int b1 = s21_decimal_is_set_bit(result.decimals[1], 0);
        result.decimals[0] = s21_int128_binary_shift_right_one(result.decimals[0]);
        result.decimals[1] = s21_int128_binary_shift_right_one(result.decimals[1]);
        if (b1) {
            result.decimals[0] = s21_decimal_set_bit(result.decimals[0], MAX_BITS - 1);
        }
        --shift;
    }

    return result;
}

/**
 * @brief Битовый сдвиг влево на один для чисел типа decimal как для int128.
 * Эквивалентно decimal << 1
 * 
 * Функция выполняет отдельно сдвиг для каждого элемента массива decimal:
 * bits[0] = bits[0] << 1
 * bits[1] = bits[1] << 1
 * bits[2] = bits[2] << 1
 * bits[3] = bits[3] << 1
 * 
 * и переносит старший бит элементов массива в соседний элемент:
 * из bits[0] в bits[1]
 * из bits[1] в bits[2]
 * из bits[2] в bits[3]
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal 
 * @return s21_decimal результат применения decimal << 1
 */
s21_decimal s21_int128_binary_shift_left_one(s21_decimal decimal) {
    s21_decimal result = s21_decimal_get_zero();

    int b0 = s21_is_set_bit(decimal.bits[0], MAX_BLOCK_BITS - 1);
    unsigned int result0 = decimal.bits[0];
    result0 = result0 << 1;
    result.bits[0] = result0;

    int b1 = s21_is_set_bit(decimal.bits[1], MAX_BLOCK_BITS - 1);
    unsigned int result1 = decimal.bits[1];
    result1 = result1 << 1;
    result.bits[1] = result1;

    int b2 = s21_is_set_bit(decimal.bits[2], MAX_BLOCK_BITS - 1);
    unsigned int result2 = decimal.bits[2];
    result2 = result2 << 1;
    result.bits[2] = result2;

    unsigned int result3 = decimal.bits[3];
    result3 = result3 << 1;
    result.bits[3] = result3;

    if (b0) {
        result.bits[1] = s21_set_bit(result.bits[1], 0);
    }

    if (b1) {
        result.bits[2] = s21_set_bit(result.bits[2], 0);
    }

    if (b2) {
        result.bits[3] = s21_set_bit(result.bits[3], 0);
    }

    return result;
}

/**
 * @brief Битовый сдвиг вправо на один для чисел типа decimal как для int128.
 * Эквивалентно decimal >> 1
 * 
 * Функция выполняет отдельно сдвиг для каждого элемента массива decimal:
 * bits[0] = bits[0] >> 1
 * bits[1] = bits[1] >> 1
 * bits[2] = bits[2] >> 1
 * bits[3] = bits[3] >> 1
 * 
 * и переносит младший бит элементов массива в соседний элемент:
 * из bits[3] в bits[2]
 * из bits[2] в bits[1]
 * из bits[1] в bits[0]
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal 
 * @return s21_decimal результат применения decimal >> 1
 */
s21_decimal s21_int128_binary_shift_right_one(s21_decimal decimal) {
    s21_decimal result = s21_decimal_get_zero();

    int b3 = s21_is_set_bit(decimal.bits[3], 0);
    unsigned int result3 = decimal.bits[3];
    result3 = result3 >> 1;
    result.bits[3] = result3;

    int b2 = s21_is_set_bit(decimal.bits[2], 0);
    unsigned int result2 = decimal.bits[2];
    result2 = result2 >> 1;
    result.bits[2] = result2;

    int b1 = s21_is_set_bit(decimal.bits[1], 0);
    unsigned int result1 = decimal.bits[1];
    result1 = result1 >> 1;
    result.bits[1] = result1;

    unsigned int result0 = decimal.bits[0];
    result0 = result0 >> 1;
    result.bits[0] = result0;

    if (b3) {
        result.bits[2] = s21_set_bit(result.bits[2], MAX_BLOCK_BITS - 1);
    }

    if (b2) {
        result.bits[1] = s21_set_bit(result.bits[1], MAX_BLOCK_BITS - 1);
    }

    if (b1) {
        result.bits[0] = s21_set_bit(result.bits[0], MAX_BLOCK_BITS - 1);
    }

    return result;
}
