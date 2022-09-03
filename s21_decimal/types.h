#ifndef SRC_S21_DECIMAL_TYPES_H_
#define SRC_S21_DECIMAL_TYPES_H_

#include <stdint.h>

typedef struct s21_decimal {
    int bits[4];
} s21_decimal;

typedef struct s21_int256 {
    s21_decimal decimals[2];
} s21_int256;

// Общее количество бит в decimal
#define MAX_BITS 128
// Общее количество бит в одном элементе массива
#define MAX_BLOCK_BITS 32
// Общее количество бит основания decimal (целого числа, которое хранит значение decimal)
#define MAX_BLOCK_NUMBER 96

/**
 * @brief объединение для получения доступа к данным bits[3] decimal
 * 16 бит: Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
 * 8 бит: Биты с 16 по 23 должны содержать показатель степени от 0 до 28.
 * 7 бит: Биты с 24 по 30 не используются и должны быть равны нулю.
 * 1 бит: Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.
 * Итого 32 бита
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 */
typedef union decimal_bit3 {
    int i;
    struct {
        uint32_t empty2 : 16;
        uint32_t power : 8;
        uint32_t empty1 : 7;
        uint32_t sign : 1;
    } parts;
} decimal_bit3;

/**
 * @brief enum для улучшения читаемости кода при проверках на знак
 * 0 - положительный decimal
 * 1 - отрицательный decimal
 */
typedef enum s21_decimal_sign {
    S21_POSITIVE = 0,
    S21_NEGATIVE = 1
} s21_decimal_sign;

/**
 * ! ! ! ! ! ! ! !
 * Закомментированный ниже union нужен для старой версии s21_from_float_to_decimal()
 * (см. описание функции s21_from_float_to_decimal)
 */

/**
 * @brief каст для побитовой работы с float
 * (23 бита) Биты 0 - 23: Мантисса
 *   (8 бит) Биты 24 - 30: Порядок
 *   (1 бит) Бит 31: Знак
 * via: https://w.wiki/5RpW (Число одинарной точности)
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 */
// typedef union float_cast {
//     float f;
//     struct {
//         uint32_t mantisa : 23;
//         uint32_t exponent : 8;
//         uint32_t sign : 1;
//     } parts;
//     uint32_t bytes;
//     int int32_bytes;
// } float_cast;

#endif  //  SRC_S21_DECIMAL_TYPES_H_
