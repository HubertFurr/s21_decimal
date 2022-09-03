#include <math.h>
#include <stdio.h>

#include "./../helpers/helpers.h"
#include "./conversion.h"

/**
 * @brief конвертирует float src в decimal dst
 * 
 * Значение Decimal, возвращаемое данной функцией, содержит не более семи значащих цифр.
 * Если src содержит более семи значащих цифр, он округляется с помощью округления до ближайшего.
 * Т.е:
 * 1234567500.12F -> 1234568000
 * 1234568500.12F -> 1234568000
 * 10.980365F -> 10.98036
 * 10.980355F -> 10.98036
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый float
 * @param dst указатель на decimal, в который запишется результат функции
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;
    if (!dst) {
        // Если указатель на decimal является NULL
        code = S21_CONVERSION_ERROR;
    } else if (src == 0.0) {
        // Отдельно обрабатываем 0.0, чтобы не выполнять лишних вычислений
        code = S21_CONVERSION_OK;
        *dst = s21_decimal_get_zero();
        if (signbit(src) != 0) {
            // Добавляем знак для -0.0
            s21_decimal_set_sign(dst, S21_NEGATIVE);
        }
    } else if (isinf(src) || isnan(src)) {
        // Отдельно обрабатываем +inf, -inf, +nan, и -nan
        code = S21_CONVERSION_ERROR;
        *dst = s21_decimal_get_inf();
        if (signbit(src) != 0) {
            // Добавляем знак для -nan и -inf
            s21_decimal_set_sign(dst, S21_NEGATIVE);
        }
    } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
        // MAX_FLOAT_TO_CONVERT - максимальное число, которое можно сконвертировать в decimal
        code = S21_CONVERSION_ERROR;
        *dst = s21_decimal_get_inf();
        if (signbit(src) != 0) {
            // Добавляем знак для для отрицательного числа
            s21_decimal_set_sign(dst, S21_NEGATIVE);
        }
    } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
        // MIN_FLOAT_TO_CONVERT - минимальное число, которое можно сконвертировать в decimal
        code = S21_CONVERSION_ERROR;
        *dst = s21_decimal_get_zero();
    } else {
        *dst = s21_decimal_get_zero();
        s21_decimal result;
        char flt[64];

        // Приводим float в научную запись - одна цифра до запятой и 6 цифр после запятой
        // В итоге мы получаем 7 значащих цифр, которые нам и нужно перевести по заданию из
        // float в decimal
        sprintf(flt, "%.6E", fabsf(src));
        // Получаем степень float из научной записи.
        int exp = s21_get_float_exp_from_string(flt);
        // Анализируем полученную степень.
        if (exp <= -23) {
            // Если степень слишком маленькая, то не все значащие цифры поместятся в decimal
            // Поэтому корректируем точность и заново приводим float в научную запись уже с новой точностью
            int float_precision = exp + 28;
            sprintf(flt, "%.*E", float_precision, fabsf(src));
        }

        // Переводим строку с научной нотацией в decimal
        result = s21_float_string_to_decimal(flt);

        // Определяем знак результата, исходя из знака числа src (типа float)
        if (signbit(src) != 0) {
            s21_decimal_set_sign(&result, S21_NEGATIVE);
        }

        *dst = result;
    }

    return code;
}

/**
 * ! ! ! ! ! ! ! !
 * Закомментированная ниже версия - конвертация всех цифр float в decimal на основе
 * описания формата из IEEE-754
 *
 * т.е. 0.03f превратится в decimal в 0.0299999993294477462768554688
 *
 */

/**
 * @brief конвертирует float src в decimal dst
 *
 * Т.к. минимальное число в decimal 1e-28, то алгоритм конвертации денормализованных float нам не нужен.
 * Нормализованные float конвертируем в decimal, исходя из алгоритма хранения чисел одинарной точности в
 * памяти: https://w.wiki/5RpW (Число одинарной точности)
 *
 * Float занимает в памяти 8 байт и хранит три параметра:
 * - Знак
 * - Порядок
 * - Мантисса
 * (Более подробное описание структуры есть в union float_cast или по ссылке в вики выше)
 *
 * Проще всего рассмотреть конвертацию на примере:
 *
 * Возьмем число 0.15625
 * Представление в памяти 00111110 00100000 00000000 00000000
 * Знак: 0 - число положительное
 * Порядок: 01111100
 * Мантисса: 0100000 00000000 00000000
 *
 * Порядок 01111100 - это 124. Но формат хранит степень со смещением 127, чтобы получить степень вычисляем её
 * как 124 - 127 = -3
 *
 * В нормализованном виде (а мы только такой вид и рассматриваем, как я писал выше) целая часть мантиссы
 * всегда равна 1 и не хранится в памяти. Поэтому реальная мантисса будет 1.01000000000000000000000
 *
 * Значение float рассчитывается по следующей формуле:
 * float = мантисса * 2^степень
 *
 * Для расчета необходимо мантиссу из двоичного вида перевести в десятичный:
 * Целая часть мантиссы (у нас всегда 1) = 1 * 2^0
 * Дробная часть мантиссы считается как: первый бит * 2^-1 + второй бит * 2^-2 + третий бит * 2^-3 + и т.д.
 * В нашей дробной части (01000000000000000000000) только второй бит равен 1 (остальное все 0,
 * поэтому суммируемые буду 0), получаем дробную мантиссу:
 * 0 * 2^-1 + 1 * 2^-2 + 0 * 2^-3 + ... = 1 * 2^-2
 *
 * С учетом целой части мантисса = 1 * 2^0 + 1 * 2^-2 = 1.25
 *
 * Итого наш float = мантисса * 2^степень = 1.25 * 2^-3 = 0.15625
 *
 * Т.к. в результате вычисления мы хотим получить число в формате decimal, то вычисление производим,
 * используя математику decimal (числа decimal и функции арифметики decimal)
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param src конвертируемый float
 * @param dst указатель на decimal, в который запишется результат функции
 * @return int код ошибки:
 * 0 - OK
 * 1 - ошибка конвертации
 */
/*
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_conversion_result code = S21_CONVERSION_OK;
    if (!dst) {
        // Если указатель на decimal является NULL
        code = S21_CONVERSION_ERROR;
    } else if (src == 0.0) {
        // Отдельно обрабатываем 0.0, чтобы не выполнять лишних вычислений
        code = S21_CONVERSION_OK;
        *dst = s21_decimal_get_zero();
        if (signbit(src) != 0) {
            // Отдельно обрабатываем -0.0
            s21_decimal_set_sign(dst, S21_NEGATIVE);
        }
    } else if (isinf(src) || isnan(src)) {
        // Отдельно обрабатываем +inf, -inf, +nan, и -nan
        code = S21_CONVERSION_ERROR;
        *dst = s21_decimal_get_inf();
        if (signbit(src) != 0) {
            s21_decimal_set_sign(dst, S21_NEGATIVE);
        }
    } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
        // MAX_FLOAT_TO_CONVERT - максимальное число, которое можно сконвертировать в decimal
        code = S21_CONVERSION_ERROR;
        *dst = s21_decimal_get_inf();
        if (signbit(src) != 0) {
            s21_decimal_set_sign(dst, S21_NEGATIVE);
        }
    } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
        // MIN_FLOAT_TO_CONVERT - минимальное число, которое можно сконвертировать в decimal
        code = S21_CONVERSION_ERROR;
        *dst = s21_decimal_get_zero();
    } else {
        // В остальных случаях производим конвертацию по алгоритму, описанному в brief
        *dst = s21_decimal_get_zero();
        s21_decimal result = s21_decimal_get_zero();
        float_cast cast;
        cast.f = src;

        char float_bits_str[24];
        // Получаем битовое представление мантиссы числа src (типа float)
        s21_get_float_mantissa_bits_string(src, float_bits_str);
        // Получаем значение степени  числа src (типа float)
        int float_exponent = cast.parts.exponent - 127;

        // Начинаем считать мантиссу float src
        // Сначала прибавляем целую часть мантиссы, которая всегда 1
        result = s21_decimal_get_one();

        // Далее считаем дробную часть мантиссы
        // Тут и далее не контролируем ошибки выход за пределы s21_decimal_get_two_pow(), т.к. мы не выйдем
        // никогда за границы decimal (мы отсекли большие и маленькие float в самом начале функции)
        for (int i = 0; i < (int)strlen(float_bits_str); i++) {
            if (float_bits_str[i] == '1') {
                s21_decimal tmp = s21_decimal_get_two_pow(-i - 1);
                s21_add(result, tmp, &result);
            }
        }

        // Определяем знак результата, исходя из знака числа src (типа float)
        if (cast.parts.sign == 1) {
            s21_decimal_set_sign(&result, S21_NEGATIVE);
        }

        // Считаем результат умножения мантиссы на степень
        // Отдельно для отрицательных и положительных степеней
        if (float_exponent < 0) {
            s21_div(result, s21_decimal_get_two_pow(-float_exponent), &result);
        } else {
            s21_mul(result, s21_decimal_get_two_pow(float_exponent), &result);
        }

        *dst = result;
    }

    return code;
}*/
