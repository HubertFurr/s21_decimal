#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./other.h"

/**
 * @brief Возвращает целые цифры числа value.
 * Любые дробные цифры отбрасываются, включая конечные нули.
 *
 * 123.999 -> 123
 * 123.000 -> 123
 * 123 -> 123
 *
 * Для получения целой части выполняем деление 96-разрядного целого числа (bits[0], bits[1], bits[2])
 * на 10 ^ n (где n - показатель степени decimal)
 * Используется именно бинарное деление целых чисел, а не деление decimal:
 * в бинарном виде: 123999 / 1000 = 123
 * в делении decimal: 123999 / 1000 = 123.999
 * Очевидно, что нам нужен 1й вариант
 *
 * Затем корректно выставляем знак, анализируя знак исходного числа
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value обрабатываемый decimal
 * @param result указатель на decimal, куда запишется результат выполнения функции
 * @return int код ошибки:
 *      0 - OK
 *      1 - ошибка вычисления
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_OTHER_ERROR;
    } else if (!s21_is_correct_decimal(value)) {
        // Проверяем, что value является корректными decimal
        code = S21_OTHER_ERROR;
        *result = s21_decimal_get_inf();
    } else {
        // В остальных случаях производим расчет
        *result = s21_decimal_get_zero();
        int power = s21_decimal_get_power(value);
        s21_decimal tmp = value;
        s21_decimal_null_service_bits(&tmp);

        tmp = s21_int128_binary_division(tmp, s21_int128_get_ten_pow(power), NULL);

        *result = tmp;
        if (s21_decimal_get_sign(value) == S21_NEGATIVE) {
            s21_decimal_set_sign(result, S21_NEGATIVE);
        }
    }

    return code;
}
