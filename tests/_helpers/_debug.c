#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../../s21_decimal.h"
#include "./../test.h"
#include "./_debug.h"

void s21_print_decimal_bits(s21_decimal decimal) {
    s21_print_bit(decimal.bits[3], 1);
    s21_print_bit(decimal.bits[2], 0);
    s21_print_bit(decimal.bits[1], 0);
    s21_print_bit(decimal.bits[0], 0);
    putchar('\n');
}

void s21_print_bit(int number, int color) {
    s21_print_bits(sizeof(number), &number, color);
}

void s21_print_bits(size_t const size, void const *const ptr, int color) {
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    int cnt = 31;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            if (color == 1) {
                if (cnt == 31) {
                    printf("%s", GREEN);
                }
                if (cnt == 30 || cnt == 15) {
                    printf("%s", YELLOW);
                }
            }

            byte = (b[i] >> j) & 1;
            if (byte == 1) {
                if (color == 1 && cnt == 31) {
                    printf("%u", byte);
                } else {
                    printf("%s%u%s", RED, byte, RESET);
                }
            } else {
                printf("%u", byte);
            }
            if (color == 1) {
                if (cnt == 0 || cnt == 24 || cnt == 31) {
                    printf("%s", RESET);
                }
            }

            cnt--;
        }
        putchar(' ');
    }
    putchar('|');
    putchar(' ');
}

void s21_print_decimal_string(s21_decimal decimal) {
    char res[1024];
    memset(res, '\0', 1024);

    s21_decimal_to_string(decimal, res);

    if (res[0] == '(') {
        printf("%s%s%s\n", RED, res, RESET);
    } else {
        printf("%s\n", res);
    }
}

void s21_decimal_to_string(s21_decimal decimal, char *res) {
    res[0] = '\0';
    // Не используем s21_is_correct_decimal(), т.к. в тестируемой библиотеке её может не быть
    if (test_is_correct_decimal(decimal) == 0) {
        strcat(res, "(Incorrect Decimal)");
    } else {
        s21_format_decimal_to_str(decimal, res);
    }
}

void s21_format_decimal_to_str(s21_decimal decimal, char *res) {
    char *str;
    // Не используем s21_decimal_get_power(), т.к. в тестируемой библиотеке её может не быть
    int power = test_decimal_get_power(decimal);
    // Не используем s21_decimal_get_sign(), т.к. в тестируемой библиотеке её может не быть
    int sign = test_decimal_get_sign(decimal);

    decimal.bits[3] = 0;
    str = s21_bin128_to_string(decimal);

    char *ptr = res;
    if (sign == 1 && (decimal.bits[0] != 0 || decimal.bits[1] != 0 || decimal.bits[2] != 0)) {
        *(ptr++) = '-';
    }

    if (strlen(str) <= (size_t)power) {
        *(ptr++) = '0';
        *(ptr++) = '.';

        for (size_t i = 0; i < power - strlen(str); i++) {
            *(ptr++) = '0';
        }

        for (size_t i = 0; i < strlen(str); i++) {
            *(ptr++) = str[i];
        }
    } else {
        size_t i;
        for (i = 0; i < strlen(str) - power; i++) {
            *(ptr++) = str[i];
        }

        for (int j = 0; j < power; j++) {
            if (j == 0) {
                *(ptr++) = '.';
            }
            *(ptr++) = str[i + j];
        }
    }
    *(ptr++) = '\0';
}

char *s21_bin128_to_string(s21_decimal decimal) {
    static char s[44];
    uint32_t n[4];
    char *p = s;

    memset(s, '0', sizeof(s) - 1);
    s[sizeof(s) - 1] = '\0';

    n[0] = decimal.bits[0];
    n[1] = decimal.bits[1];
    n[2] = decimal.bits[2];
    n[3] = decimal.bits[3];

    for (int i = 0; i < 128; i++) {
        int carry = (n[3] >= 0x80000000);

        n[3] = ((n[3] << 1) & 0xFFFFFFFF) + (n[2] >= 0x80000000);
        n[2] = ((n[2] << 1) & 0xFFFFFFFF) + (n[1] >= 0x80000000);
        n[1] = ((n[1] << 1) & 0xFFFFFFFF) + (n[0] >= 0x80000000);
        n[0] = ((n[0] << 1) & 0xFFFFFFFF);

        for (int j = sizeof(s) - 2; j >= 0; j--) {
            s[j] += s[j] - '0' + carry;
            carry = (s[j] > '9');
            if (carry) {
                s[j] -= 10;
            }
        }
    }

    while ((p[0] == '0') && (p < &s[sizeof(s) - 2])) {
        p++;
    }

    return p;
}
