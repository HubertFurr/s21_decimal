#include "./../helpers/helpers.h"
#include "./other.h"

/**
 * @brief Возвращает результат умножения value на -1.
 *
 * @param value
 * @param result указатель, куда будет записан результат
 * @return int код ошибки:
 *      0 - OK
 *      1 - ошибка вычисления
 */
int s21_negate(s21_decimal value, s21_decimal *result) {
    s21_other_result code = S21_OTHER_OK;

    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_OTHER_ERROR;
    } else {
        // В остальных случаях меняем знак
        *result = value;
        s21_decimal_set_sign(result, !s21_decimal_get_sign(*result));

        if (!s21_is_correct_decimal(value)) {
            // Если value не является корректными decimal, то выставляем код ошибки
            // Но знак реально при этом мы меняем и у некорректного decimal
            code = S21_OTHER_ERROR;
        }
    }

    return code;
}
