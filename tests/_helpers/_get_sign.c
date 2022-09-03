#include "../../s21_decimal.h"
#include "./_debug.h"

int test_decimal_get_sign(s21_decimal value) {
    test_decimal_bytes decimal_bytes;
    decimal_bytes.d = value;
    return decimal_bytes.parts.sign;
}

int test_decimal_get_power(s21_decimal value) {
    test_decimal_bytes decimal_bytes;
    decimal_bytes.d = value;
    return decimal_bytes.parts.power;
}

int test_is_correct_decimal(s21_decimal decimal) {
    int code = 1;
    test_decimal_bytes decimal_bytes;
    decimal_bytes.d = decimal;

    if (decimal_bytes.parts.empty1 != 0 || decimal_bytes.parts.empty2 != 0) {
        code = 0;
    } else {
        int power = test_decimal_get_power(decimal);
        if (power < 0 || power > 28) {
            code = 0;
        }
    }

    return code;
}
