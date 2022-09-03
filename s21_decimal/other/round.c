#include "./../helpers/helpers.h"
#include "./../arithmetic/arithmetic.h"
#include "./other.h"

/**
 * @brief Округляет value до ближайшего целого числа.
 * 
 * Если число равноудаленно от обоих целых - используется округление до ближайшего чётного
 *
 * @param value округляемое число
 * @param result указатель, куда будет записан результат
 * @return int код ошибки:
 *      0 - OK
 *      1 - ошибка вычисления
 */
int s21_round(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_OTHER_ERROR;
    } else if (!s21_is_correct_decimal(value)) {
        // Проверяем, что value является корректными decimal
        code = S21_OTHER_ERROR;
        *result = s21_decimal_get_inf();
    } else {
        // В остальных случаях округляем
        *result = s21_decimal_get_zero();
        int sign = s21_decimal_get_sign(value);
        s21_decimal fractional;
        s21_decimal value_unsigned_truncated;
        // Убираем знак
        s21_decimal value_unsigned = s21_abs(value);
        // Убираем дробную часть числа
        s21_truncate(value_unsigned, &value_unsigned_truncated);

        // Считаем убранную дробную часть числа
        s21_sub(value_unsigned, value_unsigned_truncated, &fractional);

        // Производим округление, исходя из дробной части числа
        value_unsigned_truncated = s21_round_banking(value_unsigned_truncated, fractional);

        *result = value_unsigned_truncated;
        // Возвращаем знак
        s21_decimal_set_sign(result, sign);
    }

    return code;
}
