#include <string.h>

#include "./../binary/binary.h"
#include "./helpers.h"

/**
 * @brief Возвращает заполненный decimal по данным аргументов
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param data1 int для bits[0]
 * @param data2 int для bits[1]
 * @param data3 int для bits[2]
 * @param data4 int для bits[3]
 * @return s21_decimal заполненный decimal
 */
s21_decimal s21_create_decimal_from_array(int data1, int data2, int data3, int data4) {
    s21_decimal decimal;

    decimal.bits[0] = data1;
    decimal.bits[1] = data2;
    decimal.bits[2] = data3;
    decimal.bits[3] = data4;

    return decimal;
}

/**
 * @brief Возвращает заполненный decimal по данным аргументов
 *
 * @param sign знак для заполнения в bits[3]
 * @param power степень для заполнения в bits[3]
 * @param data1 int для bits[0]
 * @param data2 int для bits[1]
 * @param data3 int для bits[2]
 * @return s21_decimal заполненный decimal
 */
s21_decimal s21_create_decimal_from_data(int sign, int power, int data1, int data2, int data3) {
    s21_decimal decimal;
    s21_clear_decimal(&decimal);

    decimal.bits[0] = data1;
    decimal.bits[1] = data2;
    decimal.bits[2] = data3;

    s21_decimal_set_power(&decimal, power);
    s21_decimal_set_sign(&decimal, sign);

    return decimal;
}

/**
 * @brief Возвращает заполненный decimal по данным аргументов
 *
 * Пробелы в строке игнорируются, можно передать как "11111111 11111111 11111111 11111111",
 * так и "11111111111111111111111111111111"
 * Если в строке окажутся символы, отличные от " 01" или количество бит в строке будет больше 32, то
 * функция вернет некорректный decimal (все биты которого 1, кроме знака)
 *
 * @param str1 строка для bits[0]
 * @param str2 строка для bits[1]
 * @param str3 строка для bits[2]
 * @param str4 строка для bits[3]
 * @return s21_decimal
 */
s21_decimal s21_create_decimal_from_strings(char *str1, char *str2, char *str3, char *str4) {
    s21_decimal decimal = s21_decimal_get_zero();
    int error = 0;

    error = s21_decimal_set_bits_from_string(&decimal.bits[0], str1);

    if (error == 0) {
        error = s21_decimal_set_bits_from_string(&decimal.bits[1], str2);
    }

    if (error == 0) {
        error = s21_decimal_set_bits_from_string(&decimal.bits[2], str3);
    }

    if (error == 0) {
        error = s21_decimal_set_bits_from_string(&decimal.bits[3], str4);
    }

    if (error == 1) {
        decimal = s21_decimal_get_inf();
    }

    return decimal;
}

/**
 * @brief устанавливает биты числа bits в соответствии со строкой str
 *
 * @param bits
 * @param str
 * @return int код ошибки:
 *          0 - OK
 *          1 - Некорректная строка str
 */
int s21_decimal_set_bits_from_string(int *bits, char *str) {
    int index = 0;
    int error = 0;

    for (int i = (int)strlen(str) - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            continue;
        } else if (str[i] == '1') {
            *bits = s21_set_bit(*bits, index);
        } else if (str[i] == '0') {
            *bits = s21_reset_bit(*bits, index);
        } else {
            error = 1;
            break;
        }
        ++index;
    }

    return error;
}

/**
 * @brief зануляет все биты числа *decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param decimal зануляемый decimal
 */
void s21_clear_decimal(s21_decimal *decimal) {
    decimal->bits[0] = 0;
    decimal->bits[1] = 0;
    decimal->bits[2] = 0;
    decimal->bits[3] = 0;
}

/**
 * @brief зануляет все биты, не являющиеся самим числом decimal (bits[3])
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value указатель на decimal, биты которого требуется занулить
 */
void s21_decimal_null_service_bits(s21_decimal *value) {
    value->bits[3] = 0;
}

/**
 * @brief формирует и возвращает число (0) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (0)
 */
s21_decimal s21_decimal_get_zero(void) {
    s21_decimal result;
    s21_clear_decimal(&result);

    return result;
}

/**
 * @brief формирует и возвращает число (1) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (1)
 */
s21_decimal s21_decimal_get_one(void) {
    s21_decimal result;
    s21_clear_decimal(&result);
    result.bits[0] = 1;

    return result;
}

/**
 * ! ! ! ! ! ! ! !
 * Закомментированная ниже функции нужны для старой версии s21_from_float_to_decimal()
 * (см. описание функции s21_from_float_to_decimal)
 * 
 * @brief возвращает 2 в степени pow в виде числа decimal
 * Допустимый диапазон для pow - [-95, 95]. Валидация данных не осуществляется и должна производится
 * перед вызовом функции
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param pow требуемая степень числа 2 (в диапазоне [-95, 95])
 * @return s21_decimal 2^pow
 */
// s21_decimal s21_decimal_get_two_pow(int pow) {
//     s21_decimal result;
//     s21_clear_decimal(&result);

//     if (pow < 0) {
//         pow = -pow;
//         result = all_two_pows_neg[pow];
//     } else {
//         result = all_two_pows_pos[pow];
//     }

//     return result;
// }

/**
 * @brief формирует и возвращает число (10) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (10)
 */
s21_decimal s21_decimal_get_ten(void) {
    s21_decimal result;
    s21_clear_decimal(&result);
    result.bits[0] = 10;

    return result;
}

/**
 * @brief возвращает 10 в степени pow в виде числа int128
 * Допустимый диапазон для pow - [0, 38]. Валидация данных не осуществляется и должна производится
 * перед вызовом функции
 * 
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param pow требуемая степень числа 10 (в диапазоне [0, 38])
 * @return s21_decimal 10^pow
 */
s21_decimal s21_int128_get_ten_pow(int pow) {
    return all_ten_pows[pow];
}

/**
 * @brief формирует и возвращает число (0.5) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (0.5)
 */
s21_decimal s21_decimal_get_zerofive(void) {
    s21_decimal result = {{0x5, 0x0, 0x0, 0x10000}};

    return result;
}

/**
 * @brief формирует и возвращает число (0.0000000000000000000000000001) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (0.0000000000000000000000000001)
 */
s21_decimal s21_decimal_get_min(void) {
    s21_decimal result = {{0x1, 0x0, 0x0, 0x1C0000}};

    return result;
}

/**
 * @brief формирует и возвращает число (79228162514264337593543950335) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (79228162514264337593543950335)
 */
s21_decimal s21_decimal_get_max(void) {
    s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    return result;
}

/**
 * @brief формирует и возвращает число (2147483647) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (2147483647)
 */
s21_decimal s21_decimal_get_int_max(void) {
    // MAX_INT = 2147483647
    s21_decimal result = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

    return result;
}

/**
 * @brief формирует и возвращает число (-2147483648) в виде decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @return s21_decimal число (-2147483648)
 */
s21_decimal s21_decimal_get_int_min(void) {
    // MIN_INT = -2147483648
    s21_decimal result = {{0x80000000, 0x0, 0x0, 0x80000000}};

    return result;
}

s21_int256 s21_create_int256_from_decimal(s21_decimal value_1) {
    s21_int256 result;
    result.decimals[0] = value_1;
    result.decimals[1] = s21_decimal_get_zero();
    return result;
}

s21_decimal s21_decimal_get_inf(void) {
    s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

    return result;
}
