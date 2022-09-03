#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"

/**
 * @brief Делит value_1 на value_2 и записывает результат в result
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 делимое
 * @param value_2 делитель
 * @param result частное
 * @return int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;

    if (!result) {
        // Если указатель на decimal является NULL
        code = S21_ARITHMETIC_ERROR;
    } else if (!s21_is_correct_decimal(value_1) || !s21_is_correct_decimal(value_2)) {
        // Проверяем, что value_1 и value_2 являются корректными decimal
        code = S21_ARITHMETIC_ERROR;
        *result = s21_decimal_get_inf();
    } else if (s21_is_equal(value_2, s21_decimal_get_zero())) {
        // Проверяем случай, когда value_2 является нулем
        code = S21_ARITHMETIC_ZERO_DIV;
        *result = s21_decimal_get_inf();
    } else {
        // В остальных случаях считаем частное
        *result = s21_decimal_get_zero();
        int sign1 = s21_decimal_get_sign(value_1);
        int sign2 = s21_decimal_get_sign(value_2);
        s21_int256 value_1l;
        s21_int256 value_2l;
        // Выравниваем степени делимого и делителя (знак и степень при этом будут обнулены)
        s21_decimal_leveling(value_1, value_2, &value_1l, &value_2l);

        s21_int256 remainder = s21_create_int256_from_decimal(s21_decimal_get_zero());
        s21_int256 res;

        // Делим выравненное делимое на выравненный делитель, остаток от деления будет записан в remainder
        res = s21_int256_binary_division(value_1l, value_2l, &remainder);

        if (res.decimals[0].bits[3] != 0 || !s21_int128_binary_equal_zero(res.decimals[1])) {
            // Если целый результат деления уже не помещается в decimal (переполнение),
            // то возвращаем соответствующие ошибки
            if (sign1 != sign2) {
                code = S21_ARITHMETIC_SMALL;
            } else {
                code = S21_ARITHMETIC_BIG;
            }
            *result = s21_decimal_get_inf();
        } else {
            // В остальных случаях продолжаем вычисления и вызываем вспомогательную функцию для расчетов
            code = s21_div_handle(value_2l, res, remainder, result);
            // Если знаки делимого и делителя отличаются, то необходимо сделать результат отрицательным
            if (sign1 != sign2) {
                s21_decimal_set_sign(result, S21_NEGATIVE);
            }
            // Корректируем код ответа от вспомогательной функции в случае ошибки и отрицательного результата
            if (s21_decimal_get_sign(*result) == S21_NEGATIVE && code == S21_ARITHMETIC_BIG) {
                code = S21_ARITHMETIC_SMALL;
            }
            // Обрабатываем ситуацию, что результат получился слишком маленький (0 < |x| < 1e-28)
            if (code == S21_ARITHMETIC_OK && s21_is_not_equal(value_1, s21_decimal_get_zero()) &&
                s21_is_equal(*result, s21_decimal_get_zero())) {
                code = S21_ARITHMETIC_SMALL;
            }
        }
    }

    return code;
}

/**
 * @brief Вспомогательная функция для деления
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_2l - делитель
 * @param res - предварительно рассчитанная целая часть от целочисленного деления
 * @param remainder - предварительно рассчитанный остаток от целочисленного деления
 * @param result - результат деления (вида 12.5454334)
 * @return int код ошибки, для передачи в родительскую функцию (и последующей обработки)
 */
int s21_div_handle(s21_int256 value_2l, s21_int256 res, s21_int256 remainder, s21_decimal *result) {
    s21_arithmetic_result code = S21_ARITHMETIC_OK;

    // рассчитываем дробную часть нашего результата и получаем в res результат, включая дробную часть
    // после расчетов в remainder останется остаток от деления (который не поместился в дробную часть)
    // power1 - значение степени результата
    int power1 = s21_div_calc_fractional(&res, value_2l, &remainder);

    s21_int256 tmp_res = s21_create_int256_from_decimal(s21_decimal_get_zero());
    // Переводи остаток, полученный в расчете выше, в decimal, чтобы использовать его для округления
    // power2 - значение степени данного decimal
    int power2 = s21_div_calc_fractional(&tmp_res, value_2l, &remainder);

    // Устанавливаем полученную степень для нашего остатка
    s21_decimal_set_power(&tmp_res.decimals[0], power2);

    if (s21_is_equal(tmp_res.decimals[0], s21_decimal_get_zerofive())) {
        if (!s21_int128_binary_equal_zero(remainder.decimals[0]) ||
            !s21_int128_binary_equal_zero(remainder.decimals[1])) {
            // Если остаток от деления в виде decimal получился ровно 0.5, но после вычисления остаток от
            // деления не равен 0, то корректируем остаток, т.к. фактически он больше 0.5:
            // 0.5 + 0.0000000000000000000000000001 = 0.5000000000000000000000000001
            s21_add(tmp_res.decimals[0], s21_decimal_get_min(), &tmp_res.decimals[0]);
        }
    }
    // Выполняем банковское округления результата, исходя из остатка от деления
    res.decimals[0] = s21_round_banking(res.decimals[0], tmp_res.decimals[0]);
    // Устанавливаем степень результата
    s21_decimal_set_power(&res.decimals[0], power1);
    // Анализируем результат на корректность (переполнение)
    if (!s21_int128_binary_equal_zero(res.decimals[1]) || !s21_is_correct_decimal(res.decimals[0])) {
        code = S21_ARITHMETIC_BIG;
        *result = s21_decimal_get_inf();
    } else {
        *result = res.decimals[0];
    }

    return code;
}

/**
 * @brief вспомогательная функция для расчета дробной части числа.
 * 
 * Например, если изначально мы делим 62/16, то получаем 3 и 14 в остатке.
 * На входе функции в res записана целая часть числа, полученная при предварительном целочисленном делении.
 * Т.е. 3 из примера выше.
 * value_2l на входе содержит 16, а remainder содержит 14
 * 
 * Что делает функция:
 * Остаток умножает на 10 и опять делит на value_2l, чтобы получить первую цифру дробной части.
 * новый остаток опять умножается на 10 и снова делит на value_2l
 * и т.д., т.е.:
 * 
 * 1: 14 * 10 = 140 / 16 = 8 и 12 в остатке, целую часть умножаем на 10 и прибавляем 8 - 38
 * 2: 12 * 10 = 120 / 16 = 7 и 8 в остатке, 38 умножаем на 10 прибавляем 7 - 387
 * 3: 8 * 10  = 80  / 16 = 5 и 0 в остатке, 387 умножаем на 10 прибавляем 5 - 3875
 * 
 * Итого в res записываем 3875, в remainder записываем 0, а в return возвращаем 3, т.к.
 * именно степень 3 превратит 3875 в decimal 3.875 (который и является результатом 62/16)
 * 
 * Если бы знаков decimal не хватило бы, чтобы записать дробь, то в remainder был бы записан 
 * остаток от последнего деления, например:
 * 59 / 15 = 3 и 14 в остатке.
 * 
 * 1: 140 / 15 = 9 (остаток 5) - 39
 * 2: 50 / 15 = 3 (остаток 5) - 393
 * 3: 50 / 15 = 3 (остаток 5) - 3933
 * 4: 50 / 15 = 3 (остаток 5) - 39333
 * 5: 50 / 15 = 3 (остаток 5) - 393333
 * .......
 * 28: 50 / 15 = 3 (остаток 5) - 39333333333333333333333333333
 * 
 * В res записываем 39333333333333333333333333333
 * В remainder 5
 * В return 28
 * 
 * @param res предварительно рассчитанная целая часть от целочисленного деления
 * @param value_2l делитель
 * @param remainder предварительно рассчитанный остаток от целочисленного деления
 * @return int
 */
int s21_div_calc_fractional(s21_int256 *res, s21_int256 value_2l, s21_int256 *remainder) {
    int power = 0;
    s21_int256 number = *res;

    s21_int256 tmp;
    s21_int256 tmp_remainder = *remainder;

    // Производим расчеты пока остаток не будет полностью равен нулю или пока степень не станет
    // максимально допустимой (28)
    while ((!s21_int128_binary_equal_zero((*remainder).decimals[0]) ||
            !s21_int128_binary_equal_zero((*remainder).decimals[1])) &&
           power < 28) {
        // Сохраняем значения полученных числа и остатка перед дальнейшей итерацией расчетов
        // Чтобы вернуть эти значения в случае переполнения
        s21_int256 number_stored = number;
        s21_int256 remainder_stored = tmp_remainder;

        // Производим расчеты (вжик вжик, см бриф)
        number = s21_int256_binary_multiplication(number, s21_decimal_get_ten());
        tmp_remainder = s21_int256_binary_multiplication(tmp_remainder, s21_decimal_get_ten());
        tmp = s21_int256_binary_division(tmp_remainder, value_2l, &tmp_remainder);
        number = s21_int256_binary_addition(number, tmp);

        // Возвращаем предварительно сохраненные число и остаток, если произошло переполнение при расчете
        if (!s21_is_correct_decimal(number.decimals[0])) {
            number = number_stored;
            tmp_remainder = remainder_stored;
            break;
        }

        ++power;
    }

    *res = number;
    *remainder = tmp_remainder;

    return power;
}
