#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

/**
 * @brief рассчитывает сколько раз необходимо разделить 256-битный int на 10, чтобы результат поместился в
 * 96битный int (в decimal)
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value 256-битный int, для которого производится расчет
 * @return int искомая степень десятки
 */
int s21_int256_get_shift_to_decimal(s21_int256 value) {
    int cnt = 0;

    // Если value содержит только нули, то расчет не производим, резльтат - 0
    if (!(s21_int128_binary_equal_zero(value.decimals[0]) &&
          s21_int128_binary_equal_zero(value.decimals[1]))) {
        // Максимальное 96битное число
        s21_int256 max = s21_create_int256_from_decimal(s21_decimal_get_max());
        // Находим число, во сколько раз value больше максимального 96битного числа
        s21_int256 quotient = s21_int256_binary_division(value, max, NULL);

        // Перебираем все степени 10, чтобы найти ближайшую большую степень, чем quotient
        // Делаем так, потому что это гораздо быстрее, чем делить на 10 в цикле
        while (1) {
            int compare = s21_int128_binary_compare(quotient.decimals[0], s21_int128_get_ten_pow(cnt));
            if (compare == -1 || compare == 0) {
                break;
            }
            ++cnt;
        }

        // Проверяем, что value впишется в 96 бит, если поделить на 10 в найденной степени
        s21_int256 tmp = s21_int256_binary_division(
            value, s21_create_int256_from_decimal(s21_int128_get_ten_pow(cnt)), NULL);
        // Если не помещается, то берем следующую степень
        if (!s21_int128_binary_equal_zero(tmp.decimals[1]) || tmp.decimals[0].bits[3] != 0) {
            ++cnt;
        }
    }

    return cnt;
}

/**
 * @brief находит максимальное число среди двух чисел
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первое число
 * @param value_2 второе число
 * @return int максимальное число среди двух чисел
 */
int s21_max(int value_1, int value_2) {
    int result = value_2;
    if (value_1 > value_2) {
        result = value_1;
    }

    return result;
}
