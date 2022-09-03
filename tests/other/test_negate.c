#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные (ручные)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_negate_fail1) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    int code = s21_negate(decimal, NULL);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(test_negate_fail2) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail4) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail5) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail6) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail7) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail8) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_fail9) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;

    int code = s21_negate(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_negate_ok1) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok2) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // -7922816251426433759354395033.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 7922816251426433759354395033.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok5) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // -792281625142643375935439503.35
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok6) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // 792281625142643375935439503.35
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok7) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // -79228162514264337593543950.335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok8) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // 79228162514264337593543950.335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok9) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // -7922816251426433759354395.0335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok10) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // 7922816251426433759354395.0335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok11) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // -792281625142643375935439.50335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok12) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // 792281625142643375935439.50335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok13) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // -79228162514264337593543.950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok14) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // 79228162514264337593543.950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok15) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // -7922816251426433759354.3950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok16) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // 7922816251426433759354.3950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok17) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // -792281625142643375935.43950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok18) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // 792281625142643375935.43950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok19) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // -79228162514264337593.543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok20) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // 79228162514264337593.543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok21) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // -7922816251426433759.3543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok22) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // 7922816251426433759.3543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok23) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // -792281625142643375.93543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok24) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // 792281625142643375.93543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok25) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // -79228162514264337.593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok26) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // 79228162514264337.593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok27) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // -7922816251426433.7593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok28) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // 7922816251426433.7593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok29) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // -792281625142643.37593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok30) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // 792281625142643.37593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok31) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // -79228162514264.337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok32) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // 79228162514264.337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok33) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // -7922816251426.4337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok34) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // 7922816251426.4337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok35) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // -792281625142.64337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok36) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // 792281625142.64337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok37) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // -79228162514.264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok38) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // 79228162514.264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok39) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // -7922816251.4264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok40) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // 7922816251.4264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok41) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // -792281625.14264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok42) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // 792281625.14264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok43) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // -79228162.514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok44) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // 79228162.514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok45) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // -7922816.2514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok46) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // 7922816.2514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok47) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // -792281.62514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok48) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // 792281.62514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok49) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // -79228.162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok50) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // 79228.162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok51) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // -7922.8162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok52) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // 7922.8162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok53) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // -792.28162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok54) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // 792.28162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok55) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // -79.228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok56) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // 79.228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok57) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // -7.9228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok58) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // 7.9228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok59) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok60) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // 79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok61) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // -7922816251426433759354395033.4
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok62) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 7922816251426433759354395033.4
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok63) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // -792281625142643375935439503.34
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok64) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // 792281625142643375935439503.34
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok65) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // -79228162514264337593543950.334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok66) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // 79228162514264337593543950.334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok67) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // -7922816251426433759354395.0334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok68) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // 7922816251426433759354395.0334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok69) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // -792281625142643375935439.50334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok70) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // 792281625142643375935439.50334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok71) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // -79228162514264337593543.950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok72) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // 79228162514264337593543.950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok73) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // -7922816251426433759354.3950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok74) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // 7922816251426433759354.3950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok75) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // -792281625142643375935.43950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok76) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // 792281625142643375935.43950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok77) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // -79228162514264337593.543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok78) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // 79228162514264337593.543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok79) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // -7922816251426433759.3543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok80) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // 7922816251426433759.3543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok81) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // -792281625142643375.93543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok82) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // 792281625142643375.93543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok83) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // -79228162514264337.593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok84) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // 79228162514264337.593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok85) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // -7922816251426433.7593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok86) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // 7922816251426433.7593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok87) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // -792281625142643.37593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok88) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // 792281625142643.37593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok89) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // -79228162514264.337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok90) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // 79228162514264.337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok91) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // -7922816251426.4337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok92) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // 7922816251426.4337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok93) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // -792281625142.64337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok94) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // 792281625142.64337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok95) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // -79228162514.264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok96) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // 79228162514.264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok97) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // -7922816251.4264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok98) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // 7922816251.4264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok99) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // -792281625.14264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok100) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // 792281625.14264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok101) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // -79228162.514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok102) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // 79228162.514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok103) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // -7922816.2514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok104) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // 7922816.2514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok105) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // -792281.62514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok106) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // 792281.62514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok107) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // -79228.162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok108) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // 79228.162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok109) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // -7922.8162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok110) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // 7922.8162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok111) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // -792.28162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok112) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // 792.28162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok113) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // -79.228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok114) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // 79.228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok115) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // -7.9228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok116) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // 7.9228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok117) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // -52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok118) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // 52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok119) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // -5281877500950955839569596689.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok120) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // 5281877500950955839569596689.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok121) {
    // 5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // -5281877500950955.8395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok122) {
    // -5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // 5281877500950955.8395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok123) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // -5.2818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok124) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // 5.2818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok125) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // -52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok126) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // 52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok127) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // -5281877500950955839283265536.0
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok128) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // 5281877500950955839283265536.0
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok129) {
    // 5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // -5281877500950955.8392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok130) {
    // -5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // 5281877500950955.8392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok131) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // -5.2818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok132) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // 5.2818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok133) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    // -52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok134) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    // 52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok135) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    // -5281877499721172901608624401.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok136) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    // 5281877499721172901608624401.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok137) {
    // 5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0xD0000}};
    // -5281877499721172.9016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok138) {
    // -5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // 5281877499721172.9016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok139) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // -5.2818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok140) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // 5.2818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok141) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    // -52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok142) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    // 52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok143) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    // -5281877499721172901322293248.0
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok144) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    // 5281877499721172901322293248.0
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok145) {
    // 5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0xD0000}};
    // -5281877499721172.9013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok146) {
    // -5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // 5281877499721172.9013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok147) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // -5.2818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok148) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // 5.2818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok149) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    // -12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok150) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    // 12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok151) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    // -1229782938247303441.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok152) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    // 1229782938247303441.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok153) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    // -122978293.82473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok154) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // 122978293.82473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok155) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    // -1.2297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok156) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    // 1.2297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok157) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    // -12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok158) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    // 12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok159) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    // -1229782937960972288.0
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok160) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    // 1229782937960972288.0
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok161) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    // -122978293.79609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok162) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // 122978293.79609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok163) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    // -1.2297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok164) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    // 1.2297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok165) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    // -2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok166) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    // 2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok167) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    // -286331153.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok168) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    // 286331153.0
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok169) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    // -286331.1530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok170) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    // 286331.1530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok171) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    // -2.863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok172) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    // 2.863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok173) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok174) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok175) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    // -2640938750475477919784798344.5
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok176) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    // 2640938750475477919784798344.5
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok177) {
    // 2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0xD0000}};
    // -2640938750475477.9197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok178) {
    // -2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x800D0000}};
    // 2640938750475477.9197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok179) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    // -2.6409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok180) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    // 2.6409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok181) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    // -26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok182) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    // 26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok183) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    // -2640938750475477919641632768.0
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok184) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    // 2640938750475477919641632768.0
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok185) {
    // 2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0xD0000}};
    // -2640938750475477.9196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok186) {
    // -2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x800D0000}};
    // 2640938750475477.9196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok187) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    // -2.6409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok188) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    // 2.6409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok189) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // -26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok190) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // 26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok191) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    // -2640938749860586450804312200.5
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok192) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    // 2640938749860586450804312200.5
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok193) {
    // 2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0xD0000}};
    // -2640938749860586.4508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok194) {
    // -2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x800D0000}};
    // 2640938749860586.4508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok195) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    // -2.6409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok196) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    // 2.6409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok197) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    // -26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok198) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    // 26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok199) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    // -2640938749860586450661146624.0
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok200) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    // 2640938749860586450661146624.0
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok201) {
    // 2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0xD0000}};
    // -2640938749860586.4506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok202) {
    // -2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x800D0000}};
    // 2640938749860586.4506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok203) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    // -2.6409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok204) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    // 2.6409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok205) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // -6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok206) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // 6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok207) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    // -614891469123651720.5
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok208) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    // 614891469123651720.5
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok209) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    // -6148914.691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok210) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    // 6148914.691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok211) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    // -6.148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok212) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    // 6.148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok213) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    // -6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok214) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // 6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok215) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    // -614891468980486144.0
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok216) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    // 614891468980486144.0
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok217) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    // -6148914.689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok218) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    // 6148914.689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok219) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    // -6.148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok220) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    // 6.148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok221) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    // -1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok222) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // 1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok223) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    // -143165576.5
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok224) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    // 143165576.5
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok225) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    // -143165.5765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok226) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    // 143165.5765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok227) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    // -1.431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok228) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    // 1.431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok229) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    // -18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok230) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    // 18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok231) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    // -1844674407800451891.3
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok232) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    // 1844674407800451891.3
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok233) {
    // 184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000}};
    // -184467440780.04518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok234) {
    // -184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80080000}};
    // 184467440780.04518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok235) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    // -1.8446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok236) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    // 1.8446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok237) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    // -18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok238) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    // 18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok239) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    // -1844674407800451891.2
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok240) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    // 1844674407800451891.2
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok241) {
    // 18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x90000}};
    // -18446744078.004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok242) {
    // -18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80090000}};
    // 18446744078.004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok243) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    // -1.8446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok244) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    // 1.8446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok245) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    // -18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok246) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    // 18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok247) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    // -1844674407370955161.7
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok248) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    // 1844674407370955161.7
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok249) {
    // 1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xA0000}};
    // -1844674407.3709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok250) {
    // -1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800A0000}};
    // 1844674407.3709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok251) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    // -1.8446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok252) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    // 1.8446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok253) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    // -18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok254) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    // 18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok255) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    // -1844674407370955161.6
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok256) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    // 1844674407370955161.6
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok257) {
    // 184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xB0000}};
    // -184467440.73709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok258) {
    // -184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800B0000}};
    // 184467440.73709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok259) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    // -1.8446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok260) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    // 1.8446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok261) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    // -4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok262) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    // 4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok263) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    // -429496729.7
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok264) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    // 429496729.7
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok265) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    // -42949672.97
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok266) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    // 42949672.97
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok267) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    // -429496.7297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok268) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    // 429496.7297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok269) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    // -4.294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok270) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    // 4.294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok271) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    // -42.94967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok272) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    // 42.94967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok273) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    // -4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok274) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    // 4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok275) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    // -429496729.6
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok276) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    // 429496729.6
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok277) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    // -42949672.96
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok278) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    // 42949672.96
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok279) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    // -4294967.296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok280) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    // 4294967.296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok281) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    // -4.294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok282) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    // 4.294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok283) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    // -42.94967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok284) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    // 42.94967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok285) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok286) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok287) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    // -0.1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok288) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    // 0.1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok289) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    // -0.0000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok290) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    // 0.0000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok291) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    // -0.00000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok292) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    // 0.00000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok293) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    // -0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok294) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    // 0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok295) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok296) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok297) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    // -39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok298) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    // 39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok299) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    // -3961408126635554083577423462.4
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok300) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    // 3961408126635554083577423462.4
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok301) {
    // 39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
    // -39614081266355.540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok302) {
    // -39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
    // 39614081266355.540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok303) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    // -3.9614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok304) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    // 3.9614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok305) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    // -39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok306) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    // 39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok307) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    // -3961408126635554083362675097.6
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok308) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    // 3961408126635554083362675097.6
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok309) {
    // 3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0xD0000}};
    // -3961408126635554.0833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok310) {
    // -3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x800D0000}};
    // 3961408126635554.0833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok311) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    // -3.9614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok312) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    // 3.9614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok313) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    // -39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok314) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    // 39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok315) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    // -3961408125713216879891945881.6
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok316) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    // 3961408125713216879891945881.6
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok317) {
    // 39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0xC0000}};
    // -39614081257132168.798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok318) {
    // -39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x800C0000}};
    // 39614081257132168.798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok319) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    // -3.9614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok320) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    // 3.9614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok321) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    // -39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok322) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    // 39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok323) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    // -3961408125713216879677197516.8
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok324) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    // 3961408125713216879677197516.8
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok325) {
    // 396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0xB0000}};
    // -396140812571321687.96771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok326) {
    // -396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x800B0000}};
    // 396140812571321687.96771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok327) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    // -3.9614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok328) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    // 3.9614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok329) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    // -9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok330) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    // 9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok331) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    // -922337203900225945.6
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok332) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    // 922337203900225945.6
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok333) {
    // 922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x70000}};
    // -922337203900.2259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok334) {
    // -922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80070000}};
    // 922337203900.2259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok335) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    // -9.223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok336) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    // 9.223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok337) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    // -9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok338) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    // 9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok339) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    // -922337203685477580.8
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok340) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    // 922337203685477580.8
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok341) {
    // 92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000}};
    // -92233720368.54775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok342) {
    // -92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80080000}};
    // 92233720368.54775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok343) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    // -9.223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok344) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    // 9.223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok345) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    // -2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok346) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    // 2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok347) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    // -214748364.8
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok348) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    // 214748364.8
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok349) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    // -21474836.48
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok350) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    // 21474836.48
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok351) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    // -214748.3648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok352) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    // 214748.3648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok353) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    // -21.47483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok354) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    // 21.47483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok355) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    // -2.147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok356) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    // 2.147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok357) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    // -156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok358) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    // 156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok359) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    // -15606476756221269530542694.4
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok360) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    // 15606476756221269530542694.4
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok361) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    // -1560647.67562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok362) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    // 1560647.67562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok363) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    // -1.56064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok364) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    // 1.56064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok365) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    // -156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok366) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    // 156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok367) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    // -15606476756221269529696665.6
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok368) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    // 15606476756221269529696665.6
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok369) {
    // 15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x40000}};
    // -15606476756221269529696.6656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok370) {
    // -15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80040000}};
    // 15606476756221269529696.6656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok371) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    // -1.56064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok372) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    // 1.56064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok373) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    // -156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok374) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    // 156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok375) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    // -15606476752587603503068569.6
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok376) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    // 15606476752587603503068569.6
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok377) {
    // 1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0xB0000}};
    // -1560647675258760.35030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok378) {
    // -1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x800B0000}};
    // 1560647675258760.35030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok379) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    // -1.56064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok380) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    // 1.56064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok381) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    // -156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok382) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    // 156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok383) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    // -15606476752587603502222540.8
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok384) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    // 15606476752587603502222540.8
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok385) {
    // 15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x130000}};
    // -15606476.7525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok386) {
    // -15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80130000}};
    // 15606476.7525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok387) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    // -1.56064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok388) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    // 1.56064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok389) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    // -36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok390) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    // 36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok391) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    // -3633666028320153.6
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok392) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    // 3633666028320153.6
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok393) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    // -363366602.83201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok394) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    // 363366602.83201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok395) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    // -3.6336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok396) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    // 3.6336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok397) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    // -36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok398) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    // 36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok399) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    // -3633666027474124.8
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok400) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    // 3633666027474124.8
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok401) {
    // 363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x20000}};
    // -363366602747412.48
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok402) {
    // -363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80020000}};
    // 363366602747412.48
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok403) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    // -363366602.74741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok404) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    // 363366602.74741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok405) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    // -36.336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok406) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    // 36.336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok407) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    // -3.6336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok408) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    // 3.6336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok409) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    // -8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok410) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    // 8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok411) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    // -846028.8
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok412) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    // 846028.8
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok413) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    // -84602.88
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok414) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    // 84602.88
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok415) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    // -8460.288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok416) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    // 8460.288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok417) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    // -84.60288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok418) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    // 84.60288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok419) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    // -8.460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok420) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    // 8.460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok421) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok422) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok423) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // -7922816251426433759354395033.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok424) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 7922816251426433759354395033.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok425) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // -792281625142.64337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok426) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // 792281625142.64337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok427) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // -7.9228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok428) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // 7.9228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok429) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // -79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok430) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // 79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok431) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // -7922816251426433758924898304.0
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok432) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // 7922816251426433758924898304.0
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok433) {
    // 79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // -79228162514264.337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok434) {
    // -79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // 79228162514264.337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok435) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // -7.9228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok436) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // 7.9228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok437) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    // -79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok438) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    // 79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok439) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    // -7922816249581759352412936601.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok440) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    // 7922816249581759352412936601.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok441) {
    // 792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x110000}};
    // -792281624958.17593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok442) {
    // -792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80110000}};
    // 792281624958.17593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok443) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // -7.9228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok444) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // 7.9228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok445) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    // -79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok446) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    // 79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok447) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    // -7922816249581759351983439872.0
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok448) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    // 7922816249581759351983439872.0
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok449) {
    // 79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x120000}};
    // -79228162495.817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok450) {
    // -79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80120000}};
    // 79228162495.817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok451) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // -7.9228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok452) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // 7.9228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok453) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    // -18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok454) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    // 18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok455) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    // -1844674407370955161.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok456) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    // 1844674407370955161.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok457) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    // -18446744073709551.615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok458) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    // 18446744073709551.615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok459) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    // -184467440.73709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok460) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    // 184467440.73709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok461) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    // -184.46744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok462) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    // 184.46744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok463) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    // -1.8446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok464) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    // 1.8446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok465) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    // -18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok466) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    // 18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok467) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    // -1844674406941458432.0
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok468) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    // 1844674406941458432.0
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok469) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    // -18446744069414584.320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok470) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    // 18446744069414584.320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok471) {
    // 18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x90000}};
    // -18446744069.414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok472) {
    // -18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80090000}};
    // 18446744069.414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok473) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    // -184.46744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok474) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    // 184.46744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok475) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    // -1.8446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok476) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    // 1.8446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok477) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    // -4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok478) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    // 4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok479) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    // -429496729.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok480) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    // 429496729.5
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok481) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    // -42949672.95
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok482) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    // 42949672.95
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok483) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    // -42949.67295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok484) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    // 42949.67295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok485) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    // -42.94967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok486) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    // 42.94967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok487) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    // -4.294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok488) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    // 4.294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok489) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    // -1.0
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok490) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    // 1.0
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok491) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    // -1.00
    s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok492) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    // 1.00
    s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok493) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    // -1.000
    s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok494) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    // 1.000
    s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok495) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    // -1.0000000000
    s21_decimal decimal_check = {{0x540BE400, 0x2, 0x0, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok496) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    // 1.0000000000
    s21_decimal decimal_check = {{0x540BE400, 0x2, 0x0, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok497) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    // -1.0000000000000000
    s21_decimal decimal_check = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok498) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    // 1.0000000000000000
    s21_decimal decimal_check = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok499) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    // -1.00000000000000000000000
    s21_decimal decimal_check = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok500) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    // 1.00000000000000000000000
    s21_decimal decimal_check = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok501) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    // -1.000000000000000000000000000
    s21_decimal decimal_check = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok502) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    // 1.000000000000000000000000000
    s21_decimal decimal_check = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok503) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -1.0000000000000000000000000000
    s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok504) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // 1.0000000000000000000000000000
    s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok505) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    // -1.1
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok506) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    // 1.1
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok507) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    // -12.12
    s21_decimal decimal_check = {{0x4BC, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok508) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    // 12.12
    s21_decimal decimal_check = {{0x4BC, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok509) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    // -123.123
    s21_decimal decimal_check = {{0x1E0F3, 0x0, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok510) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    // 123.123
    s21_decimal decimal_check = {{0x1E0F3, 0x0, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok511) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    // -1234.1234
    s21_decimal decimal_check = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok512) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    // 1234.1234
    s21_decimal decimal_check = {{0xBC4FF2, 0x0, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok513) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    // -12345.12345
    s21_decimal decimal_check = {{0x499529D9, 0x0, 0x0, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok514) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    // 12345.12345
    s21_decimal decimal_check = {{0x499529D9, 0x0, 0x0, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok515) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    // -123456.123456
    s21_decimal decimal_check = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok516) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    // 123456.123456
    s21_decimal decimal_check = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok517) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    // -1234567.1234567
    s21_decimal decimal_check = {{0x73593407, 0xB3A, 0x0, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok518) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    // 1234567.1234567
    s21_decimal decimal_check = {{0x73593407, 0xB3A, 0x0, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok519) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    // -1234567890.1234567890
    s21_decimal decimal_check = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok520) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    // 1234567890.1234567890
    s21_decimal decimal_check = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok521) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    // -12345678901234.12345678901234
    s21_decimal decimal_check = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok522) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    // 12345678901234.12345678901234
    s21_decimal decimal_check = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok523) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok524) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok525) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    // -9.9
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok526) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    // 9.9
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok527) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    // -99.99
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok528) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    // 99.99
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok529) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    // -999.999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok530) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    // 999.999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok531) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    // -9999.9999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok532) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    // 9999.9999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok533) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    // -99999.99999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok534) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    // 99999.99999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok535) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    // -999999.999999
    s21_decimal decimal_check = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok536) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    // 999999.999999
    s21_decimal decimal_check = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok537) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    // -9999999.9999999
    s21_decimal decimal_check = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok538) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    // 9999999.9999999
    s21_decimal decimal_check = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok539) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    // -99999999.99999999
    s21_decimal decimal_check = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok540) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    // 99999999.99999999
    s21_decimal decimal_check = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok541) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    // -999999999.999999999
    s21_decimal decimal_check = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok542) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    // 999999999.999999999
    s21_decimal decimal_check = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok543) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    // -9999999999.9999999999
    s21_decimal decimal_check = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok544) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    // 9999999999.9999999999
    s21_decimal decimal_check = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok545) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok546) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok547) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    // -0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok548) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    // 0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok549) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // -0.99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok550) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // 0.99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok551) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    // -0.999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok552) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    // 0.999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok553) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    // -0.9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok554) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    // 0.9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok555) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    // -0.99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok556) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    // 0.99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok557) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    // -0.999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok558) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    // 0.999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok559) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    // -0.9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok560) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    // 0.9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok561) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    // -0.99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok562) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    // 0.99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok563) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // -0.999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok564) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // 0.999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok565) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    // -0.9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok566) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    // 0.9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok567) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    // -0.99999999999999999999
    s21_decimal decimal_check = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok568) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    // 0.99999999999999999999
    s21_decimal decimal_check = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok569) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok570) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok571) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    // -0.0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok572) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    // 0.0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok573) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    // -0.00
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok574) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    // 0.00
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok575) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    // -0.00000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok576) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    // 0.00000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok577) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    // -0.000000000000000000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok578) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    // 0.000000000000000000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok579) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    // -0.0000000000000000000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok580) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    // 0.0000000000000000000000000000
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok581) {
    // 0.5
    s21_decimal decimal = {{0x5, 0x0, 0x0, 0x10000}};
    // -0.5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok582) {
    // -0.5
    s21_decimal decimal = {{0x5, 0x0, 0x0, 0x80010000}};
    // 0.5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok583) {
    // 0.49
    s21_decimal decimal = {{0x31, 0x0, 0x0, 0x20000}};
    // -0.49
    s21_decimal decimal_check = {{0x31, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok584) {
    // -0.49
    s21_decimal decimal = {{0x31, 0x0, 0x0, 0x80020000}};
    // 0.49
    s21_decimal decimal_check = {{0x31, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok585) {
    // 0.51
    s21_decimal decimal = {{0x33, 0x0, 0x0, 0x20000}};
    // -0.51
    s21_decimal decimal_check = {{0x33, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok586) {
    // -0.51
    s21_decimal decimal = {{0x33, 0x0, 0x0, 0x80020000}};
    // 0.51
    s21_decimal decimal_check = {{0x33, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok587) {
    // 0.49999999
    s21_decimal decimal = {{0x2FAF07F, 0x0, 0x0, 0x80000}};
    // -0.49999999
    s21_decimal decimal_check = {{0x2FAF07F, 0x0, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok588) {
    // -0.49999999
    s21_decimal decimal = {{0x2FAF07F, 0x0, 0x0, 0x80080000}};
    // 0.49999999
    s21_decimal decimal_check = {{0x2FAF07F, 0x0, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok589) {
    // 0.4999999999999999999999999999
    s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // -0.4999999999999999999999999999
    s21_decimal decimal_check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok590) {
    // -0.4999999999999999999999999999
    s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // 0.4999999999999999999999999999
    s21_decimal decimal_check = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok591) {
    // 0.5000000000000000000000000001
    s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // -0.5000000000000000000000000001
    s21_decimal decimal_check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok592) {
    // -0.5000000000000000000000000001
    s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // 0.5000000000000000000000000001
    s21_decimal decimal_check = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok593) {
    // 0.5000000000000000000000000000
    s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // -0.5000000000000000000000000000
    s21_decimal decimal_check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok594) {
    // -0.5000000000000000000000000000
    s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // 0.5000000000000000000000000000
    s21_decimal decimal_check = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok595) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // -0.99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok596) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // 0.99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok597) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // -0.999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok598) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // 0.999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok599) {
    // 0.9999999999999999999999999999
    s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -0.9999999999999999999999999999
    s21_decimal decimal_check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok600) {
    // -0.9999999999999999999999999999
    s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // 0.9999999999999999999999999999
    s21_decimal decimal_check = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok601) {
    // 1.0000000000000000000000000001
    s21_decimal decimal = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // -1.0000000000000000000000000001
    s21_decimal decimal_check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok602) {
    // -1.0000000000000000000000000001
    s21_decimal decimal = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // 1.0000000000000000000000000001
    s21_decimal decimal_check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok603) {
    // 1.5
    s21_decimal decimal = {{0xF, 0x0, 0x0, 0x10000}};
    // -1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok604) {
    // -1.5
    s21_decimal decimal = {{0xF, 0x0, 0x0, 0x80010000}};
    // 1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok605) {
    // 1.49
    s21_decimal decimal = {{0x95, 0x0, 0x0, 0x20000}};
    // -1.49
    s21_decimal decimal_check = {{0x95, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok606) {
    // -1.49
    s21_decimal decimal = {{0x95, 0x0, 0x0, 0x80020000}};
    // 1.49
    s21_decimal decimal_check = {{0x95, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok607) {
    // 1.51
    s21_decimal decimal = {{0x97, 0x0, 0x0, 0x20000}};
    // -1.51
    s21_decimal decimal_check = {{0x97, 0x0, 0x0, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok608) {
    // -1.51
    s21_decimal decimal = {{0x97, 0x0, 0x0, 0x80020000}};
    // 1.51
    s21_decimal decimal_check = {{0x97, 0x0, 0x0, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok609) {
    // 1.49999999
    s21_decimal decimal = {{0x8F0D17F, 0x0, 0x0, 0x80000}};
    // -1.49999999
    s21_decimal decimal_check = {{0x8F0D17F, 0x0, 0x0, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok610) {
    // -1.49999999
    s21_decimal decimal = {{0x8F0D17F, 0x0, 0x0, 0x80080000}};
    // 1.49999999
    s21_decimal decimal_check = {{0x8F0D17F, 0x0, 0x0, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok611) {
    // 1.4999999999999999999999999999
    s21_decimal decimal = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x1C0000}};
    // -1.4999999999999999999999999999
    s21_decimal decimal_check = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok612) {
    // -1.4999999999999999999999999999
    s21_decimal decimal = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x801C0000}};
    // 1.4999999999999999999999999999
    s21_decimal decimal_check = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok613) {
    // 1.5000000000000000000000000001
    s21_decimal decimal = {{0x98000001, 0x5D378391, 0x3077B58D, 0x1C0000}};
    // -1.5000000000000000000000000001
    s21_decimal decimal_check = {{0x98000001, 0x5D378391, 0x3077B58D, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok614) {
    // -1.5000000000000000000000000001
    s21_decimal decimal = {{0x98000001, 0x5D378391, 0x3077B58D, 0x801C0000}};
    // 1.5000000000000000000000000001
    s21_decimal decimal_check = {{0x98000001, 0x5D378391, 0x3077B58D, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok615) {
    // 1.5000000000000000000000000000
    s21_decimal decimal = {{0x98000000, 0x5D378391, 0x3077B58D, 0x1C0000}};
    // -1.5000000000000000000000000000
    s21_decimal decimal_check = {{0x98000000, 0x5D378391, 0x3077B58D, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok616) {
    // -1.5000000000000000000000000000
    s21_decimal decimal = {{0x98000000, 0x5D378391, 0x3077B58D, 0x801C0000}};
    // 1.5000000000000000000000000000
    s21_decimal decimal_check = {{0x98000000, 0x5D378391, 0x3077B58D, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok617) {
    // 1.999999
    s21_decimal decimal = {{0x1E847F, 0x0, 0x0, 0x60000}};
    // -1.999999
    s21_decimal decimal_check = {{0x1E847F, 0x0, 0x0, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok618) {
    // -1.999999
    s21_decimal decimal = {{0x1E847F, 0x0, 0x0, 0x80060000}};
    // 1.999999
    s21_decimal decimal_check = {{0x1E847F, 0x0, 0x0, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok619) {
    // 1.9999999999999999999999999999
    s21_decimal decimal = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
    // -1.9999999999999999999999999999
    s21_decimal decimal_check = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok620) {
    // -1.9999999999999999999999999999
    s21_decimal decimal = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
    // 1.9999999999999999999999999999
    s21_decimal decimal_check = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok621) {
    // -31995312930785154696052954.189
    s21_decimal decimal = {{0x873F544D, 0x720EF6CF, 0x6761E70D, 0x80030000}};
    // 31995312930785154696052954.189
    s21_decimal decimal_check = {{0x873F544D, 0x720EF6CF, 0x6761E70D, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok622) {
    // 31995312930785154696052954.189
    s21_decimal decimal = {{0x873F544D, 0x720EF6CF, 0x6761E70D, 0x30000}};
    // -31995312930785154696052954.189
    s21_decimal decimal_check = {{0x873F544D, 0x720EF6CF, 0x6761E70D, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok623) {
    // 505895479.13980033234385760539
    s21_decimal decimal = {{0x2C27F11B, 0xAB7A362C, 0xA376B177, 0x140000}};
    // -505895479.13980033234385760539
    s21_decimal decimal_check = {{0x2C27F11B, 0xAB7A362C, 0xA376B177, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok624) {
    // -505895479.13980033234385760539
    s21_decimal decimal = {{0x2C27F11B, 0xAB7A362C, 0xA376B177, 0x80140000}};
    // 505895479.13980033234385760539
    s21_decimal decimal_check = {{0x2C27F11B, 0xAB7A362C, 0xA376B177, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok625) {
    // 2142258001479126924635870.868
    s21_decimal decimal = {{0x63E31694, 0xF61EB7CD, 0x6EC08C6, 0x30000}};
    // -2142258001479126924635870.868
    s21_decimal decimal_check = {{0x63E31694, 0xF61EB7CD, 0x6EC08C6, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok626) {
    // -2142258001479126924635870.868
    s21_decimal decimal = {{0x63E31694, 0xF61EB7CD, 0x6EC08C6, 0x80030000}};
    // 2142258001479126924635870.868
    s21_decimal decimal_check = {{0x63E31694, 0xF61EB7CD, 0x6EC08C6, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok627) {
    // 54106681724336.874301252305096
    s21_decimal decimal = {{0x9C8A00C8, 0x934CB014, 0xAED3FF85, 0xF0000}};
    // -54106681724336.874301252305096
    s21_decimal decimal_check = {{0x9C8A00C8, 0x934CB014, 0xAED3FF85, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok628) {
    // -54106681724336.874301252305096
    s21_decimal decimal = {{0x9C8A00C8, 0x934CB014, 0xAED3FF85, 0x800F0000}};
    // 54106681724336.874301252305096
    s21_decimal decimal_check = {{0x9C8A00C8, 0x934CB014, 0xAED3FF85, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok629) {
    // -7125.4264674374072027825163875
    s21_decimal decimal = {{0x6335CE63, 0xF0D0163D, 0xE63C2573, 0x80190000}};
    // 7125.4264674374072027825163875
    s21_decimal decimal_check = {{0x6335CE63, 0xF0D0163D, 0xE63C2573, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok630) {
    // 7125.4264674374072027825163875
    s21_decimal decimal = {{0x6335CE63, 0xF0D0163D, 0xE63C2573, 0x190000}};
    // -7125.4264674374072027825163875
    s21_decimal decimal_check = {{0x6335CE63, 0xF0D0163D, 0xE63C2573, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok631) {
    // -351491064926027919.22225067848
    s21_decimal decimal = {{0x8D233748, 0x29D6FE5, 0x7192A8D1, 0x800B0000}};
    // 351491064926027919.22225067848
    s21_decimal decimal_check = {{0x8D233748, 0x29D6FE5, 0x7192A8D1, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok632) {
    // 351491064926027919.22225067848
    s21_decimal decimal = {{0x8D233748, 0x29D6FE5, 0x7192A8D1, 0xB0000}};
    // -351491064926027919.22225067848
    s21_decimal decimal_check = {{0x8D233748, 0x29D6FE5, 0x7192A8D1, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok633) {
    // -4044647961809480.1797480051324
    s21_decimal decimal = {{0xE9A5F27C, 0x9103102B, 0x82B08B35, 0x800D0000}};
    // 4044647961809480.1797480051324
    s21_decimal decimal_check = {{0xE9A5F27C, 0x9103102B, 0x82B08B35, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok634) {
    // 4044647961809480.1797480051324
    s21_decimal decimal = {{0xE9A5F27C, 0x9103102B, 0x82B08B35, 0xD0000}};
    // -4044647961809480.1797480051324
    s21_decimal decimal_check = {{0xE9A5F27C, 0x9103102B, 0x82B08B35, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok635) {
    // 787567884367013096891806886.45
    s21_decimal decimal = {{0xD3F79105, 0xD79DCCA, 0xFE7A16A8, 0x20000}};
    // -787567884367013096891806886.45
    s21_decimal decimal_check = {{0xD3F79105, 0xD79DCCA, 0xFE7A16A8, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok636) {
    // -787567884367013096891806886.45
    s21_decimal decimal = {{0xD3F79105, 0xD79DCCA, 0xFE7A16A8, 0x80020000}};
    // 787567884367013096891806886.45
    s21_decimal decimal_check = {{0xD3F79105, 0xD79DCCA, 0xFE7A16A8, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok637) {
    // -1588.6156880717336145015869256
    s21_decimal decimal = {{0x3B780F48, 0x203F2D8C, 0x3354B892, 0x80190000}};
    // 1588.6156880717336145015869256
    s21_decimal decimal_check = {{0x3B780F48, 0x203F2D8C, 0x3354B892, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok638) {
    // 1588.6156880717336145015869256
    s21_decimal decimal = {{0x3B780F48, 0x203F2D8C, 0x3354B892, 0x190000}};
    // -1588.6156880717336145015869256
    s21_decimal decimal_check = {{0x3B780F48, 0x203F2D8C, 0x3354B892, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok639) {
    // -1.1288079906187025161270790909
    s21_decimal decimal = {{0xE0E30AFD, 0xDFB7B835, 0x247947E5, 0x801C0000}};
    // 1.1288079906187025161270790909
    s21_decimal decimal_check = {{0xE0E30AFD, 0xDFB7B835, 0x247947E5, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok640) {
    // 1.1288079906187025161270790909
    s21_decimal decimal = {{0xE0E30AFD, 0xDFB7B835, 0x247947E5, 0x1C0000}};
    // -1.1288079906187025161270790909
    s21_decimal decimal_check = {{0xE0E30AFD, 0xDFB7B835, 0x247947E5, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok641) {
    // 47874765834.98019023871100102
    s21_decimal decimal = {{0x9A7544C6, 0xA0AA802F, 0xF781B99, 0x110000}};
    // -47874765834.98019023871100102
    s21_decimal decimal_check = {{0x9A7544C6, 0xA0AA802F, 0xF781B99, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok642) {
    // -47874765834.98019023871100102
    s21_decimal decimal = {{0x9A7544C6, 0xA0AA802F, 0xF781B99, 0x80110000}};
    // 47874765834.98019023871100102
    s21_decimal decimal_check = {{0x9A7544C6, 0xA0AA802F, 0xF781B99, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok643) {
    // 7325105732697471168627274464.8
    s21_decimal decimal = {{0x8AD7CC8, 0x89CEB74E, 0xECAFDABE, 0x10000}};
    // -7325105732697471168627274464.8
    s21_decimal decimal_check = {{0x8AD7CC8, 0x89CEB74E, 0xECAFDABE, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok644) {
    // -7325105732697471168627274464.8
    s21_decimal decimal = {{0x8AD7CC8, 0x89CEB74E, 0xECAFDABE, 0x80010000}};
    // 7325105732697471168627274464.8
    s21_decimal decimal_check = {{0x8AD7CC8, 0x89CEB74E, 0xECAFDABE, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok645) {
    // -72130.403841036757567571211222
    s21_decimal decimal = {{0x7D47B3D6, 0x55DF7B4B, 0xE910DF23, 0x80180000}};
    // 72130.403841036757567571211222
    s21_decimal decimal_check = {{0x7D47B3D6, 0x55DF7B4B, 0xE910DF23, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok646) {
    // 72130.403841036757567571211222
    s21_decimal decimal = {{0x7D47B3D6, 0x55DF7B4B, 0xE910DF23, 0x180000}};
    // -72130.403841036757567571211222
    s21_decimal decimal_check = {{0x7D47B3D6, 0x55DF7B4B, 0xE910DF23, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok647) {
    // 234.01142182632722763593730624
    s21_decimal decimal = {{0xD426CA40, 0xA712AF2C, 0x4B9CF89B, 0x1A0000}};
    // -234.01142182632722763593730624
    s21_decimal decimal_check = {{0xD426CA40, 0xA712AF2C, 0x4B9CF89B, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok648) {
    // -234.01142182632722763593730624
    s21_decimal decimal = {{0xD426CA40, 0xA712AF2C, 0x4B9CF89B, 0x801A0000}};
    // 234.01142182632722763593730624
    s21_decimal decimal_check = {{0xD426CA40, 0xA712AF2C, 0x4B9CF89B, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok649) {
    // 40832336935500667248295.547327
    s21_decimal decimal = {{0xBD9011BF, 0xA81025E1, 0x83EFB7AC, 0x60000}};
    // -40832336935500667248295.547327
    s21_decimal decimal_check = {{0xBD9011BF, 0xA81025E1, 0x83EFB7AC, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok650) {
    // -40832336935500667248295.547327
    s21_decimal decimal = {{0xBD9011BF, 0xA81025E1, 0x83EFB7AC, 0x80060000}};
    // 40832336935500667248295.547327
    s21_decimal decimal_check = {{0xBD9011BF, 0xA81025E1, 0x83EFB7AC, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok651) {
    // -7838108432432579020287.7275832
    s21_decimal decimal = {{0xD5DD6EB8, 0x4F67C0FA, 0xFD435037, 0x80070000}};
    // 7838108432432579020287.7275832
    s21_decimal decimal_check = {{0xD5DD6EB8, 0x4F67C0FA, 0xFD435037, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok652) {
    // 7838108432432579020287.7275832
    s21_decimal decimal = {{0xD5DD6EB8, 0x4F67C0FA, 0xFD435037, 0x70000}};
    // -7838108432432579020287.7275832
    s21_decimal decimal_check = {{0xD5DD6EB8, 0x4F67C0FA, 0xFD435037, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok653) {
    // 69015888252402261058162782.46
    s21_decimal decimal = {{0xB4B864E6, 0xE577A195, 0x164CDC47, 0x20000}};
    // -69015888252402261058162782.46
    s21_decimal decimal_check = {{0xB4B864E6, 0xE577A195, 0x164CDC47, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok654) {
    // -69015888252402261058162782.46
    s21_decimal decimal = {{0xB4B864E6, 0xE577A195, 0x164CDC47, 0x80020000}};
    // 69015888252402261058162782.46
    s21_decimal decimal_check = {{0xB4B864E6, 0xE577A195, 0x164CDC47, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok655) {
    // -55850655241531059265092696.899
    s21_decimal decimal = {{0x1D0BBB43, 0x615E4A12, 0xB4769447, 0x80030000}};
    // 55850655241531059265092696.899
    s21_decimal decimal_check = {{0x1D0BBB43, 0x615E4A12, 0xB4769447, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok656) {
    // 55850655241531059265092696.899
    s21_decimal decimal = {{0x1D0BBB43, 0x615E4A12, 0xB4769447, 0x30000}};
    // -55850655241531059265092696.899
    s21_decimal decimal_check = {{0x1D0BBB43, 0x615E4A12, 0xB4769447, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok657) {
    // 441549233113186273534.49107993
    s21_decimal decimal = {{0x896A9219, 0xCCCBF8, 0x8EAC18B5, 0x80000}};
    // -441549233113186273534.49107993
    s21_decimal decimal_check = {{0x896A9219, 0xCCCBF8, 0x8EAC18B5, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok658) {
    // -441549233113186273534.49107993
    s21_decimal decimal = {{0x896A9219, 0xCCCBF8, 0x8EAC18B5, 0x80080000}};
    // 441549233113186273534.49107993
    s21_decimal decimal_check = {{0x896A9219, 0xCCCBF8, 0x8EAC18B5, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok659) {
    // -151016553161.11241097827129358
    s21_decimal decimal = {{0xC039180E, 0x17BEB589, 0x30CBCBE7, 0x80110000}};
    // 151016553161.11241097827129358
    s21_decimal decimal_check = {{0xC039180E, 0x17BEB589, 0x30CBCBE7, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok660) {
    // 151016553161.11241097827129358
    s21_decimal decimal = {{0xC039180E, 0x17BEB589, 0x30CBCBE7, 0x110000}};
    // -151016553161.11241097827129358
    s21_decimal decimal_check = {{0xC039180E, 0x17BEB589, 0x30CBCBE7, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok661) {
    // -2504745147808573373831964087.9
    s21_decimal decimal = {{0x7166F92F, 0x636702FE, 0x50EEC429, 0x80010000}};
    // 2504745147808573373831964087.9
    s21_decimal decimal_check = {{0x7166F92F, 0x636702FE, 0x50EEC429, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok662) {
    // 2504745147808573373831964087.9
    s21_decimal decimal = {{0x7166F92F, 0x636702FE, 0x50EEC429, 0x10000}};
    // -2504745147808573373831964087.9
    s21_decimal decimal_check = {{0x7166F92F, 0x636702FE, 0x50EEC429, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok663) {
    // -61729133434784021526374.826345
    s21_decimal decimal = {{0xD17CC169, 0xC8328AFD, 0xC7752474, 0x80060000}};
    // 61729133434784021526374.826345
    s21_decimal decimal_check = {{0xD17CC169, 0xC8328AFD, 0xC7752474, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok664) {
    // 61729133434784021526374.826345
    s21_decimal decimal = {{0xD17CC169, 0xC8328AFD, 0xC7752474, 0x60000}};
    // -61729133434784021526374.826345
    s21_decimal decimal_check = {{0xD17CC169, 0xC8328AFD, 0xC7752474, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok665) {
    // 311077020664558443854.4955571
    s21_decimal decimal = {{0x91B5F8B3, 0xCEB2D42A, 0xA0D2B36, 0x70000}};
    // -311077020664558443854.4955571
    s21_decimal decimal_check = {{0x91B5F8B3, 0xCEB2D42A, 0xA0D2B36, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok666) {
    // -311077020664558443854.4955571
    s21_decimal decimal = {{0x91B5F8B3, 0xCEB2D42A, 0xA0D2B36, 0x80070000}};
    // 311077020664558443854.4955571
    s21_decimal decimal_check = {{0x91B5F8B3, 0xCEB2D42A, 0xA0D2B36, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok667) {
    // 3.7671877098664416926980883530
    s21_decimal decimal = {{0x8DBC44A, 0x995466F5, 0x79B97245, 0x1C0000}};
    // -3.7671877098664416926980883530
    s21_decimal decimal_check = {{0x8DBC44A, 0x995466F5, 0x79B97245, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok668) {
    // -3.7671877098664416926980883530
    s21_decimal decimal = {{0x8DBC44A, 0x995466F5, 0x79B97245, 0x801C0000}};
    // 3.7671877098664416926980883530
    s21_decimal decimal_check = {{0x8DBC44A, 0x995466F5, 0x79B97245, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok669) {
    // -967513672211158867637770335.3
    s21_decimal decimal = {{0x607AF3B9, 0xA90EE1CF, 0x1F4315E4, 0x80010000}};
    // 967513672211158867637770335.3
    s21_decimal decimal_check = {{0x607AF3B9, 0xA90EE1CF, 0x1F4315E4, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok670) {
    // 967513672211158867637770335.3
    s21_decimal decimal = {{0x607AF3B9, 0xA90EE1CF, 0x1F4315E4, 0x10000}};
    // -967513672211158867637770335.3
    s21_decimal decimal_check = {{0x607AF3B9, 0xA90EE1CF, 0x1F4315E4, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok671) {
    // 38498.641608826781155397574344
    s21_decimal decimal = {{0x30959EC8, 0x80650782, 0x7C655477, 0x180000}};
    // -38498.641608826781155397574344
    s21_decimal decimal_check = {{0x30959EC8, 0x80650782, 0x7C655477, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok672) {
    // -38498.641608826781155397574344
    s21_decimal decimal = {{0x30959EC8, 0x80650782, 0x7C655477, 0x80180000}};
    // 38498.641608826781155397574344
    s21_decimal decimal_check = {{0x30959EC8, 0x80650782, 0x7C655477, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok673) {
    // -71236.00489546778547498822342
    s21_decimal decimal = {{0x5E7CAAC6, 0x5592C8F4, 0x17048114, 0x80170000}};
    // 71236.00489546778547498822342
    s21_decimal decimal_check = {{0x5E7CAAC6, 0x5592C8F4, 0x17048114, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok674) {
    // 71236.00489546778547498822342
    s21_decimal decimal = {{0x5E7CAAC6, 0x5592C8F4, 0x17048114, 0x170000}};
    // -71236.00489546778547498822342
    s21_decimal decimal_check = {{0x5E7CAAC6, 0x5592C8F4, 0x17048114, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok675) {
    // 193625519496582.73322276379192
    s21_decimal decimal = {{0xE57A5A38, 0x6F244181, 0x3E9053DC, 0xE0000}};
    // -193625519496582.73322276379192
    s21_decimal decimal_check = {{0xE57A5A38, 0x6F244181, 0x3E9053DC, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok676) {
    // -193625519496582.73322276379192
    s21_decimal decimal = {{0xE57A5A38, 0x6F244181, 0x3E9053DC, 0x800E0000}};
    // 193625519496582.73322276379192
    s21_decimal decimal_check = {{0xE57A5A38, 0x6F244181, 0x3E9053DC, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok677) {
    // 408199057216532927237.43497659
    s21_decimal decimal = {{0x24581DBB, 0x34187C7E, 0x83E56F43, 0x80000}};
    // -408199057216532927237.43497659
    s21_decimal decimal_check = {{0x24581DBB, 0x34187C7E, 0x83E56F43, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok678) {
    // -408199057216532927237.43497659
    s21_decimal decimal = {{0x24581DBB, 0x34187C7E, 0x83E56F43, 0x80080000}};
    // 408199057216532927237.43497659
    s21_decimal decimal_check = {{0x24581DBB, 0x34187C7E, 0x83E56F43, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok679) {
    // -789428554950431891535385.56050
    s21_decimal decimal = {{0xBB8CC092, 0x7F2B3A7E, 0xFF13FFE3, 0x80050000}};
    // 789428554950431891535385.56050
    s21_decimal decimal_check = {{0xBB8CC092, 0x7F2B3A7E, 0xFF13FFE3, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok680) {
    // 789428554950431891535385.56050
    s21_decimal decimal = {{0xBB8CC092, 0x7F2B3A7E, 0xFF13FFE3, 0x50000}};
    // -789428554950431891535385.56050
    s21_decimal decimal_check = {{0xBB8CC092, 0x7F2B3A7E, 0xFF13FFE3, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok681) {
    // -16320961587.434330846592909538
    s21_decimal decimal = {{0xDB1640E2, 0x81E77C2B, 0x34BC620C, 0x80120000}};
    // 16320961587.434330846592909538
    s21_decimal decimal_check = {{0xDB1640E2, 0x81E77C2B, 0x34BC620C, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok682) {
    // 16320961587.434330846592909538
    s21_decimal decimal = {{0xDB1640E2, 0x81E77C2B, 0x34BC620C, 0x120000}};
    // -16320961587.434330846592909538
    s21_decimal decimal_check = {{0xDB1640E2, 0x81E77C2B, 0x34BC620C, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok683) {
    // -7575836313015457255204617487.8
    s21_decimal decimal = {{0x2464E29E, 0x7BA3AF2B, 0xF4C9D966, 0x80010000}};
    // 7575836313015457255204617487.8
    s21_decimal decimal_check = {{0x2464E29E, 0x7BA3AF2B, 0xF4C9D966, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok684) {
    // 7575836313015457255204617487.8
    s21_decimal decimal = {{0x2464E29E, 0x7BA3AF2B, 0xF4C9D966, 0x10000}};
    // -7575836313015457255204617487.8
    s21_decimal decimal_check = {{0x2464E29E, 0x7BA3AF2B, 0xF4C9D966, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok685) {
    // -7122663615.9332396743512235380
    s21_decimal decimal = {{0x44271D74, 0x239E94EA, 0xE6254AE3, 0x80130000}};
    // 7122663615.9332396743512235380
    s21_decimal decimal_check = {{0x44271D74, 0x239E94EA, 0xE6254AE3, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok686) {
    // 7122663615.9332396743512235380
    s21_decimal decimal = {{0x44271D74, 0x239E94EA, 0xE6254AE3, 0x130000}};
    // -7122663615.9332396743512235380
    s21_decimal decimal_check = {{0x44271D74, 0x239E94EA, 0xE6254AE3, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok687) {
    // 47478.313259881987700553638758
    s21_decimal decimal = {{0xC58F6366, 0x1D95F0B4, 0x996923E7, 0x180000}};
    // -47478.313259881987700553638758
    s21_decimal decimal_check = {{0xC58F6366, 0x1D95F0B4, 0x996923E7, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok688) {
    // -47478.313259881987700553638758
    s21_decimal decimal = {{0xC58F6366, 0x1D95F0B4, 0x996923E7, 0x80180000}};
    // 47478.313259881987700553638758
    s21_decimal decimal_check = {{0xC58F6366, 0x1D95F0B4, 0x996923E7, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok689) {
    // -4758688310.6049169487039918664
    s21_decimal decimal = {{0xA4157248, 0x45055A66, 0x99C2F276, 0x80130000}};
    // 4758688310.6049169487039918664
    s21_decimal decimal_check = {{0xA4157248, 0x45055A66, 0x99C2F276, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok690) {
    // 4758688310.6049169487039918664
    s21_decimal decimal = {{0xA4157248, 0x45055A66, 0x99C2F276, 0x130000}};
    // -4758688310.6049169487039918664
    s21_decimal decimal_check = {{0xA4157248, 0x45055A66, 0x99C2F276, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok691) {
    // -7759553663118364923509.460394
    s21_decimal decimal = {{0x6E41CDAA, 0xF41B262C, 0x19128D66, 0x80060000}};
    // 7759553663118364923509.460394
    s21_decimal decimal_check = {{0x6E41CDAA, 0xF41B262C, 0x19128D66, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok692) {
    // 7759553663118364923509.460394
    s21_decimal decimal = {{0x6E41CDAA, 0xF41B262C, 0x19128D66, 0x60000}};
    // -7759553663118364923509.460394
    s21_decimal decimal_check = {{0x6E41CDAA, 0xF41B262C, 0x19128D66, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok693) {
    // -490.94850073769253372538799119
    s21_decimal decimal = {{0x4D36440F, 0x643BCEFF, 0x9EA24EE3, 0x801A0000}};
    // 490.94850073769253372538799119
    s21_decimal decimal_check = {{0x4D36440F, 0x643BCEFF, 0x9EA24EE3, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok694) {
    // 490.94850073769253372538799119
    s21_decimal decimal = {{0x4D36440F, 0x643BCEFF, 0x9EA24EE3, 0x1A0000}};
    // -490.94850073769253372538799119
    s21_decimal decimal_check = {{0x4D36440F, 0x643BCEFF, 0x9EA24EE3, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok695) {
    // 7940577688413.027735940807540
    s21_decimal decimal = {{0xC282BB74, 0x743068B, 0x19A84ABB, 0xF0000}};
    // -7940577688413.027735940807540
    s21_decimal decimal_check = {{0xC282BB74, 0x743068B, 0x19A84ABB, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok696) {
    // -7940577688413.027735940807540
    s21_decimal decimal = {{0xC282BB74, 0x743068B, 0x19A84ABB, 0x800F0000}};
    // 7940577688413.027735940807540
    s21_decimal decimal_check = {{0xC282BB74, 0x743068B, 0x19A84ABB, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok697) {
    // -5517432521.5405139583164130733
    s21_decimal decimal = {{0x670EA5AD, 0x32BD3BFC, 0xB24721D3, 0x80130000}};
    // 5517432521.5405139583164130733
    s21_decimal decimal_check = {{0x670EA5AD, 0x32BD3BFC, 0xB24721D3, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok698) {
    // 5517432521.5405139583164130733
    s21_decimal decimal = {{0x670EA5AD, 0x32BD3BFC, 0xB24721D3, 0x130000}};
    // -5517432521.5405139583164130733
    s21_decimal decimal_check = {{0x670EA5AD, 0x32BD3BFC, 0xB24721D3, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok699) {
    // -3022805040914609972.2991986999
    s21_decimal decimal = {{0x8BC6937, 0x2E0C6D5F, 0x61AC0EA8, 0x800A0000}};
    // 3022805040914609972.2991986999
    s21_decimal decimal_check = {{0x8BC6937, 0x2E0C6D5F, 0x61AC0EA8, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok700) {
    // 3022805040914609972.2991986999
    s21_decimal decimal = {{0x8BC6937, 0x2E0C6D5F, 0x61AC0EA8, 0xA0000}};
    // -3022805040914609972.2991986999
    s21_decimal decimal_check = {{0x8BC6937, 0x2E0C6D5F, 0x61AC0EA8, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok701) {
    // -722193033090.31456454691566415
    s21_decimal decimal = {{0x1DDCB34F, 0x26EE55F0, 0xE95A6855, 0x80110000}};
    // 722193033090.31456454691566415
    s21_decimal decimal_check = {{0x1DDCB34F, 0x26EE55F0, 0xE95A6855, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok702) {
    // 722193033090.31456454691566415
    s21_decimal decimal = {{0x1DDCB34F, 0x26EE55F0, 0xE95A6855, 0x110000}};
    // -722193033090.31456454691566415
    s21_decimal decimal_check = {{0x1DDCB34F, 0x26EE55F0, 0xE95A6855, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok703) {
    // -23029433933514704.253009181280
    s21_decimal decimal = {{0x3612BA60, 0x17661D9D, 0x4A698053, 0x800C0000}};
    // 23029433933514704.253009181280
    s21_decimal decimal_check = {{0x3612BA60, 0x17661D9D, 0x4A698053, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok704) {
    // 23029433933514704.253009181280
    s21_decimal decimal = {{0x3612BA60, 0x17661D9D, 0x4A698053, 0xC0000}};
    // -23029433933514704.253009181280
    s21_decimal decimal_check = {{0x3612BA60, 0x17661D9D, 0x4A698053, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok705) {
    // 174961.83454409460423697046616
    s21_decimal decimal = {{0x57C31C58, 0x92E37D96, 0x388880F5, 0x170000}};
    // -174961.83454409460423697046616
    s21_decimal decimal_check = {{0x57C31C58, 0x92E37D96, 0x388880F5, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok706) {
    // -174961.83454409460423697046616
    s21_decimal decimal = {{0x57C31C58, 0x92E37D96, 0x388880F5, 0x80170000}};
    // 174961.83454409460423697046616
    s21_decimal decimal_check = {{0x57C31C58, 0x92E37D96, 0x388880F5, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok707) {
    // 7688233523633863979468351.3801
    s21_decimal decimal = {{0x927C0BC9, 0x732A076F, 0xF86B93C0, 0x40000}};
    // -7688233523633863979468351.3801
    s21_decimal decimal_check = {{0x927C0BC9, 0x732A076F, 0xF86B93C0, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok708) {
    // -7688233523633863979468351.3801
    s21_decimal decimal = {{0x927C0BC9, 0x732A076F, 0xF86B93C0, 0x80040000}};
    // 7688233523633863979468351.3801
    s21_decimal decimal_check = {{0x927C0BC9, 0x732A076F, 0xF86B93C0, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok709) {
    // 3815631762232.2757778379682438
    s21_decimal decimal = {{0x35E8B286, 0x22AAADB, 0x7B4A2A8B, 0x100000}};
    // -3815631762232.2757778379682438
    s21_decimal decimal_check = {{0x35E8B286, 0x22AAADB, 0x7B4A2A8B, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok710) {
    // -3815631762232.2757778379682438
    s21_decimal decimal = {{0x35E8B286, 0x22AAADB, 0x7B4A2A8B, 0x80100000}};
    // 3815631762232.2757778379682438
    s21_decimal decimal_check = {{0x35E8B286, 0x22AAADB, 0x7B4A2A8B, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok711) {
    // -46958264034637590.844321113097
    s21_decimal decimal = {{0xAA152409, 0x2006919A, 0x97BAF732, 0x800C0000}};
    // 46958264034637590.844321113097
    s21_decimal decimal_check = {{0xAA152409, 0x2006919A, 0x97BAF732, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok712) {
    // 46958264034637590.844321113097
    s21_decimal decimal = {{0xAA152409, 0x2006919A, 0x97BAF732, 0xC0000}};
    // -46958264034637590.844321113097
    s21_decimal decimal_check = {{0xAA152409, 0x2006919A, 0x97BAF732, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok713) {
    // -13079482184230054725878943216
    s21_decimal decimal = {{0xD70A0DF0, 0xF4D591A7, 0x2A431815, 0x80000000}};
    // 13079482184230054725878943216
    s21_decimal decimal_check = {{0xD70A0DF0, 0xF4D591A7, 0x2A431815, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok714) {
    // 13079482184230054725878943216
    s21_decimal decimal = {{0xD70A0DF0, 0xF4D591A7, 0x2A431815, 0x0}};
    // -13079482184230054725878943216
    s21_decimal decimal_check = {{0xD70A0DF0, 0xF4D591A7, 0x2A431815, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok715) {
    // -304613793051866203875.93720482
    s21_decimal decimal = {{0x186292A2, 0xFABB014A, 0x626D0FF8, 0x80080000}};
    // 304613793051866203875.93720482
    s21_decimal decimal_check = {{0x186292A2, 0xFABB014A, 0x626D0FF8, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok716) {
    // 304613793051866203875.93720482
    s21_decimal decimal = {{0x186292A2, 0xFABB014A, 0x626D0FF8, 0x80000}};
    // -304613793051866203875.93720482
    s21_decimal decimal_check = {{0x186292A2, 0xFABB014A, 0x626D0FF8, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok717) {
    // 71864352877721119585710.444415
    s21_decimal decimal = {{0x906D0F7F, 0xB6E9F6DB, 0xE834CCA7, 0x60000}};
    // -71864352877721119585710.444415
    s21_decimal decimal_check = {{0x906D0F7F, 0xB6E9F6DB, 0xE834CCA7, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok718) {
    // -71864352877721119585710.444415
    s21_decimal decimal = {{0x906D0F7F, 0xB6E9F6DB, 0xE834CCA7, 0x80060000}};
    // 71864352877721119585710.444415
    s21_decimal decimal_check = {{0x906D0F7F, 0xB6E9F6DB, 0xE834CCA7, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok719) {
    // 3.1768777596019896776498905496
    s21_decimal decimal = {{0xC7D48198, 0x5736C818, 0x66A68454, 0x1C0000}};
    // -3.1768777596019896776498905496
    s21_decimal decimal_check = {{0xC7D48198, 0x5736C818, 0x66A68454, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok720) {
    // -3.1768777596019896776498905496
    s21_decimal decimal = {{0xC7D48198, 0x5736C818, 0x66A68454, 0x801C0000}};
    // 3.1768777596019896776498905496
    s21_decimal decimal_check = {{0xC7D48198, 0x5736C818, 0x66A68454, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok721) {
    // 715.39030503466615660582670958
    s21_decimal decimal = {{0xE6E6126E, 0x77E021DC, 0xE727B2F6, 0x1A0000}};
    // -715.39030503466615660582670958
    s21_decimal decimal_check = {{0xE6E6126E, 0x77E021DC, 0xE727B2F6, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok722) {
    // -715.39030503466615660582670958
    s21_decimal decimal = {{0xE6E6126E, 0x77E021DC, 0xE727B2F6, 0x801A0000}};
    // 715.39030503466615660582670958
    s21_decimal decimal_check = {{0xE6E6126E, 0x77E021DC, 0xE727B2F6, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok723) {
    // -67.152452596397860376114252119
    s21_decimal decimal = {{0x8BCE4957, 0xA320E48E, 0xD8FB34F5, 0x801B0000}};
    // 67.152452596397860376114252119
    s21_decimal decimal_check = {{0x8BCE4957, 0xA320E48E, 0xD8FB34F5, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok724) {
    // 67.152452596397860376114252119
    s21_decimal decimal = {{0x8BCE4957, 0xA320E48E, 0xD8FB34F5, 0x1B0000}};
    // -67.152452596397860376114252119
    s21_decimal decimal_check = {{0x8BCE4957, 0xA320E48E, 0xD8FB34F5, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok725) {
    // 702300879.95327828693099047933
    s21_decimal decimal = {{0xF7656BFD, 0xEB4C071D, 0xE2ECF79A, 0x140000}};
    // -702300879.95327828693099047933
    s21_decimal decimal_check = {{0xF7656BFD, 0xEB4C071D, 0xE2ECF79A, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok726) {
    // -702300879.95327828693099047933
    s21_decimal decimal = {{0xF7656BFD, 0xEB4C071D, 0xE2ECF79A, 0x80140000}};
    // 702300879.95327828693099047933
    s21_decimal decimal_check = {{0xF7656BFD, 0xEB4C071D, 0xE2ECF79A, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok727) {
    // 553728783.22350676089188517524
    s21_decimal decimal = {{0x6FD60694, 0xB182FB09, 0xB2EB5F14, 0x140000}};
    // -553728783.22350676089188517524
    s21_decimal decimal_check = {{0x6FD60694, 0xB182FB09, 0xB2EB5F14, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok728) {
    // -553728783.22350676089188517524
    s21_decimal decimal = {{0x6FD60694, 0xB182FB09, 0xB2EB5F14, 0x80140000}};
    // 553728783.22350676089188517524
    s21_decimal decimal_check = {{0x6FD60694, 0xB182FB09, 0xB2EB5F14, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok729) {
    // -2629806028.5296848613679768191
    s21_decimal decimal = {{0x4C47227F, 0xAC76516C, 0x54F93EE0, 0x80130000}};
    // 2629806028.5296848613679768191
    s21_decimal decimal_check = {{0x4C47227F, 0xAC76516C, 0x54F93EE0, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok730) {
    // 2629806028.5296848613679768191
    s21_decimal decimal = {{0x4C47227F, 0xAC76516C, 0x54F93EE0, 0x130000}};
    // -2629806028.5296848613679768191
    s21_decimal decimal_check = {{0x4C47227F, 0xAC76516C, 0x54F93EE0, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok731) {
    // -37301566276730339101787998538
    s21_decimal decimal = {{0xAA36C94A, 0xB79758E9, 0x788721E7, 0x80000000}};
    // 37301566276730339101787998538
    s21_decimal decimal_check = {{0xAA36C94A, 0xB79758E9, 0x788721E7, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok732) {
    // 37301566276730339101787998538
    s21_decimal decimal = {{0xAA36C94A, 0xB79758E9, 0x788721E7, 0x0}};
    // -37301566276730339101787998538
    s21_decimal decimal_check = {{0xAA36C94A, 0xB79758E9, 0x788721E7, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok733) {
    // -19886670070506083349797941.599
    s21_decimal decimal = {{0xED8A315F, 0xB27F7C0C, 0x4041DE30, 0x80030000}};
    // 19886670070506083349797941.599
    s21_decimal decimal_check = {{0xED8A315F, 0xB27F7C0C, 0x4041DE30, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok734) {
    // 19886670070506083349797941.599
    s21_decimal decimal = {{0xED8A315F, 0xB27F7C0C, 0x4041DE30, 0x30000}};
    // -19886670070506083349797941.599
    s21_decimal decimal_check = {{0xED8A315F, 0xB27F7C0C, 0x4041DE30, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok735) {
    // -3754213648112.7256866352070280
    s21_decimal decimal = {{0x4808FE88, 0xA1181C06, 0x794E20A0, 0x80100000}};
    // 3754213648112.7256866352070280
    s21_decimal decimal_check = {{0x4808FE88, 0xA1181C06, 0x794E20A0, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok736) {
    // 3754213648112.7256866352070280
    s21_decimal decimal = {{0x4808FE88, 0xA1181C06, 0x794E20A0, 0x100000}};
    // -3754213648112.7256866352070280
    s21_decimal decimal_check = {{0x4808FE88, 0xA1181C06, 0x794E20A0, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok737) {
    // -20864287343724.448209815726664
    s21_decimal decimal = {{0x5897EA48, 0x457A041A, 0x436A88B3, 0x800F0000}};
    // 20864287343724.448209815726664
    s21_decimal decimal_check = {{0x5897EA48, 0x457A041A, 0x436A88B3, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok738) {
    // 20864287343724.448209815726664
    s21_decimal decimal = {{0x5897EA48, 0x457A041A, 0x436A88B3, 0xF0000}};
    // -20864287343724.448209815726664
    s21_decimal decimal_check = {{0x5897EA48, 0x457A041A, 0x436A88B3, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok739) {
    // -18333.761850490314285328278117
    s21_decimal decimal = {{0xF5F2A265, 0x681BB955, 0x3B3D5515, 0x80180000}};
    // 18333.761850490314285328278117
    s21_decimal decimal_check = {{0xF5F2A265, 0x681BB955, 0x3B3D5515, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok740) {
    // 18333.761850490314285328278117
    s21_decimal decimal = {{0xF5F2A265, 0x681BB955, 0x3B3D5515, 0x180000}};
    // -18333.761850490314285328278117
    s21_decimal decimal_check = {{0xF5F2A265, 0x681BB955, 0x3B3D5515, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok741) {
    // 17.26662158134174659568869492
    s21_decimal decimal = {{0xD8EE2074, 0x265E79D6, 0x59442EF, 0x1A0000}};
    // -17.26662158134174659568869492
    s21_decimal decimal_check = {{0xD8EE2074, 0x265E79D6, 0x59442EF, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok742) {
    // -17.26662158134174659568869492
    s21_decimal decimal = {{0xD8EE2074, 0x265E79D6, 0x59442EF, 0x801A0000}};
    // 17.26662158134174659568869492
    s21_decimal decimal_check = {{0xD8EE2074, 0x265E79D6, 0x59442EF, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok743) {
    // -4467.5276786603099348176850290
    s21_decimal decimal = {{0xC4E1CD72, 0x6BDB519C, 0x905A85D7, 0x80190000}};
    // 4467.5276786603099348176850290
    s21_decimal decimal_check = {{0xC4E1CD72, 0x6BDB519C, 0x905A85D7, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok744) {
    // 4467.5276786603099348176850290
    s21_decimal decimal = {{0xC4E1CD72, 0x6BDB519C, 0x905A85D7, 0x190000}};
    // -4467.5276786603099348176850290
    s21_decimal decimal_check = {{0xC4E1CD72, 0x6BDB519C, 0x905A85D7, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok745) {
    // -362724438094.46369572362017671
    s21_decimal decimal = {{0xC1125B87, 0xFA5EAAF2, 0x7533DCBE, 0x80110000}};
    // 362724438094.46369572362017671
    s21_decimal decimal_check = {{0xC1125B87, 0xFA5EAAF2, 0x7533DCBE, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok746) {
    // 362724438094.46369572362017671
    s21_decimal decimal = {{0xC1125B87, 0xFA5EAAF2, 0x7533DCBE, 0x110000}};
    // -362724438094.46369572362017671
    s21_decimal decimal_check = {{0xC1125B87, 0xFA5EAAF2, 0x7533DCBE, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok747) {
    // -7605.7021001795924025561664762
    s21_decimal decimal = {{0xCF514CFA, 0x25695B9B, 0xF5C0E4AA, 0x80190000}};
    // 7605.7021001795924025561664762
    s21_decimal decimal_check = {{0xCF514CFA, 0x25695B9B, 0xF5C0E4AA, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok748) {
    // 7605.7021001795924025561664762
    s21_decimal decimal = {{0xCF514CFA, 0x25695B9B, 0xF5C0E4AA, 0x190000}};
    // -7605.7021001795924025561664762
    s21_decimal decimal_check = {{0xCF514CFA, 0x25695B9B, 0xF5C0E4AA, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok749) {
    // -6320.8176491370321279168857014
    s21_decimal decimal = {{0xCC6CC3B6, 0x8A1F97E8, 0xCC3C9401, 0x80190000}};
    // 6320.8176491370321279168857014
    s21_decimal decimal_check = {{0xCC6CC3B6, 0x8A1F97E8, 0xCC3C9401, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok750) {
    // 6320.8176491370321279168857014
    s21_decimal decimal = {{0xCC6CC3B6, 0x8A1F97E8, 0xCC3C9401, 0x190000}};
    // -6320.8176491370321279168857014
    s21_decimal decimal_check = {{0xCC6CC3B6, 0x8A1F97E8, 0xCC3C9401, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok751) {
    // 117642423742406.17917792307743
    s21_decimal decimal = {{0x1FF2CA1F, 0xFD692006, 0x26032738, 0xE0000}};
    // -117642423742406.17917792307743
    s21_decimal decimal_check = {{0x1FF2CA1F, 0xFD692006, 0x26032738, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok752) {
    // -117642423742406.17917792307743
    s21_decimal decimal = {{0x1FF2CA1F, 0xFD692006, 0x26032738, 0x800E0000}};
    // 117642423742406.17917792307743
    s21_decimal decimal_check = {{0x1FF2CA1F, 0xFD692006, 0x26032738, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok753) {
    // 1241972744872041109370763116.6
    s21_decimal decimal = {{0x2F11AA3E, 0x143B0D2C, 0x28215B96, 0x10000}};
    // -1241972744872041109370763116.6
    s21_decimal decimal_check = {{0x2F11AA3E, 0x143B0D2C, 0x28215B96, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok754) {
    // -1241972744872041109370763116.6
    s21_decimal decimal = {{0x2F11AA3E, 0x143B0D2C, 0x28215B96, 0x80010000}};
    // 1241972744872041109370763116.6
    s21_decimal decimal_check = {{0x2F11AA3E, 0x143B0D2C, 0x28215B96, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok755) {
    // 30342.861383397098561691465239
    s21_decimal decimal = {{0x2B2C3617, 0x90B65CE7, 0x620B06D3, 0x180000}};
    // -30342.861383397098561691465239
    s21_decimal decimal_check = {{0x2B2C3617, 0x90B65CE7, 0x620B06D3, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok756) {
    // -30342.861383397098561691465239
    s21_decimal decimal = {{0x2B2C3617, 0x90B65CE7, 0x620B06D3, 0x80180000}};
    // 30342.861383397098561691465239
    s21_decimal decimal_check = {{0x2B2C3617, 0x90B65CE7, 0x620B06D3, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok757) {
    // 70086944438.030060636448014360
    s21_decimal decimal = {{0x2E4CC018, 0x2110157E, 0xE2768FC7, 0x120000}};
    // -70086944438.030060636448014360
    s21_decimal decimal_check = {{0x2E4CC018, 0x2110157E, 0xE2768FC7, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok758) {
    // -70086944438.030060636448014360
    s21_decimal decimal = {{0x2E4CC018, 0x2110157E, 0xE2768FC7, 0x80120000}};
    // 70086944438.030060636448014360
    s21_decimal decimal_check = {{0x2E4CC018, 0x2110157E, 0xE2768FC7, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok759) {
    // 566482390624046530267.5970491
    s21_decimal decimal = {{0x6F16D9BB, 0x4B709662, 0x124DD51F, 0x70000}};
    // -566482390624046530267.5970491
    s21_decimal decimal_check = {{0x6F16D9BB, 0x4B709662, 0x124DD51F, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok760) {
    // -566482390624046530267.5970491
    s21_decimal decimal = {{0x6F16D9BB, 0x4B709662, 0x124DD51F, 0x80070000}};
    // 566482390624046530267.5970491
    s21_decimal decimal_check = {{0x6F16D9BB, 0x4B709662, 0x124DD51F, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok761) {
    // -41054218444853761729128.610293
    s21_decimal decimal = {{0xEF38B9F5, 0x6157C9BB, 0x84A740E9, 0x80060000}};
    // 41054218444853761729128.610293
    s21_decimal decimal_check = {{0xEF38B9F5, 0x6157C9BB, 0x84A740E9, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok762) {
    // 41054218444853761729128.610293
    s21_decimal decimal = {{0xEF38B9F5, 0x6157C9BB, 0x84A740E9, 0x60000}};
    // -41054218444853761729128.610293
    s21_decimal decimal_check = {{0xEF38B9F5, 0x6157C9BB, 0x84A740E9, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok763) {
    // -425640348068531825729774558.82
    s21_decimal decimal = {{0xF8F8030A, 0x5DEFF074, 0x898824F6, 0x80020000}};
    // 425640348068531825729774558.82
    s21_decimal decimal_check = {{0xF8F8030A, 0x5DEFF074, 0x898824F6, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok764) {
    // 425640348068531825729774558.82
    s21_decimal decimal = {{0xF8F8030A, 0x5DEFF074, 0x898824F6, 0x20000}};
    // -425640348068531825729774558.82
    s21_decimal decimal_check = {{0xF8F8030A, 0x5DEFF074, 0x898824F6, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok765) {
    // 6930.5025380379969951990866737
    s21_decimal decimal = {{0xCCCE331, 0x141BCF2F, 0xDFEFC5FA, 0x190000}};
    // -6930.5025380379969951990866737
    s21_decimal decimal_check = {{0xCCCE331, 0x141BCF2F, 0xDFEFC5FA, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok766) {
    // -6930.5025380379969951990866737
    s21_decimal decimal = {{0xCCCE331, 0x141BCF2F, 0xDFEFC5FA, 0x80190000}};
    // 6930.5025380379969951990866737
    s21_decimal decimal_check = {{0xCCCE331, 0x141BCF2F, 0xDFEFC5FA, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok767) {
    // -4893478018705063611335618.7925
    s21_decimal decimal = {{0x58F2E915, 0x71EE87C9, 0x9E1DE6C5, 0x80040000}};
    // 4893478018705063611335618.7925
    s21_decimal decimal_check = {{0x58F2E915, 0x71EE87C9, 0x9E1DE6C5, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok768) {
    // 4893478018705063611335618.7925
    s21_decimal decimal = {{0x58F2E915, 0x71EE87C9, 0x9E1DE6C5, 0x40000}};
    // -4893478018705063611335618.7925
    s21_decimal decimal_check = {{0x58F2E915, 0x71EE87C9, 0x9E1DE6C5, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok769) {
    // -3719188876231.7200053704267359
    s21_decimal decimal = {{0xCD6F165F, 0xBF46F2F9, 0x782C68C9, 0x80100000}};
    // 3719188876231.7200053704267359
    s21_decimal decimal_check = {{0xCD6F165F, 0xBF46F2F9, 0x782C68C9, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok770) {
    // 3719188876231.7200053704267359
    s21_decimal decimal = {{0xCD6F165F, 0xBF46F2F9, 0x782C68C9, 0x100000}};
    // -3719188876231.7200053704267359
    s21_decimal decimal_check = {{0xCD6F165F, 0xBF46F2F9, 0x782C68C9, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok771) {
    // -19155910711381619.204342790599
    s21_decimal decimal = {{0xF0CDB9C7, 0x75FE835D, 0x3DE565E0, 0x800C0000}};
    // 19155910711381619.204342790599
    s21_decimal decimal_check = {{0xF0CDB9C7, 0x75FE835D, 0x3DE565E0, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok772) {
    // 19155910711381619.204342790599
    s21_decimal decimal = {{0xF0CDB9C7, 0x75FE835D, 0x3DE565E0, 0xC0000}};
    // -19155910711381619.204342790599
    s21_decimal decimal_check = {{0xF0CDB9C7, 0x75FE835D, 0x3DE565E0, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok773) {
    // -368.97585215469170781927729120
    s21_decimal decimal = {{0x356767E0, 0x81087394, 0x7738F796, 0x801A0000}};
    // 368.97585215469170781927729120
    s21_decimal decimal_check = {{0x356767E0, 0x81087394, 0x7738F796, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok774) {
    // 368.97585215469170781927729120
    s21_decimal decimal = {{0x356767E0, 0x81087394, 0x7738F796, 0x1A0000}};
    // -368.97585215469170781927729120
    s21_decimal decimal_check = {{0x356767E0, 0x81087394, 0x7738F796, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok775) {
    // -18065466336409663317.087784854
    s21_decimal decimal = {{0xF0068F96, 0x71E89536, 0x3A5F674C, 0x80090000}};
    // 18065466336409663317.087784854
    s21_decimal decimal_check = {{0xF0068F96, 0x71E89536, 0x3A5F674C, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok776) {
    // 18065466336409663317.087784854
    s21_decimal decimal = {{0xF0068F96, 0x71E89536, 0x3A5F674C, 0x90000}};
    // -18065466336409663317.087784854
    s21_decimal decimal_check = {{0xF0068F96, 0x71E89536, 0x3A5F674C, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok777) {
    // -260712165342967081086876.07434
    s21_decimal decimal = {{0x24E5868A, 0x4A8DB43E, 0x543D9AD8, 0x80050000}};
    // 260712165342967081086876.07434
    s21_decimal decimal_check = {{0x24E5868A, 0x4A8DB43E, 0x543D9AD8, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok778) {
    // 260712165342967081086876.07434
    s21_decimal decimal = {{0x24E5868A, 0x4A8DB43E, 0x543D9AD8, 0x50000}};
    // -260712165342967081086876.07434
    s21_decimal decimal_check = {{0x24E5868A, 0x4A8DB43E, 0x543D9AD8, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok779) {
    // -617384269597993645.39618009822
    s21_decimal decimal = {{0x35D5A2DE, 0xC858D3A2, 0xC77CD46F, 0x800B0000}};
    // 617384269597993645.39618009822
    s21_decimal decimal_check = {{0x35D5A2DE, 0xC858D3A2, 0xC77CD46F, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok780) {
    // 617384269597993645.39618009822
    s21_decimal decimal = {{0x35D5A2DE, 0xC858D3A2, 0xC77CD46F, 0xB0000}};
    // -617384269597993645.39618009822
    s21_decimal decimal_check = {{0x35D5A2DE, 0xC858D3A2, 0xC77CD46F, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok781) {
    // -420012885002270.45303708462071
    s21_decimal decimal = {{0x47C6ABF7, 0xF4F2CCE9, 0x87B6A6CB, 0x800E0000}};
    // 420012885002270.45303708462071
    s21_decimal decimal_check = {{0x47C6ABF7, 0xF4F2CCE9, 0x87B6A6CB, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok782) {
    // 420012885002270.45303708462071
    s21_decimal decimal = {{0x47C6ABF7, 0xF4F2CCE9, 0x87B6A6CB, 0xE0000}};
    // -420012885002270.45303708462071
    s21_decimal decimal_check = {{0x47C6ABF7, 0xF4F2CCE9, 0x87B6A6CB, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok783) {
    // 1663517.787555391667512695470
    s21_decimal decimal = {{0x7DDA5AAE, 0xF637FC56, 0x5600797, 0x150000}};
    // -1663517.787555391667512695470
    s21_decimal decimal_check = {{0x7DDA5AAE, 0xF637FC56, 0x5600797, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok784) {
    // -1663517.787555391667512695470
    s21_decimal decimal = {{0x7DDA5AAE, 0xF637FC56, 0x5600797, 0x80150000}};
    // 1663517.787555391667512695470
    s21_decimal decimal_check = {{0x7DDA5AAE, 0xF637FC56, 0x5600797, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok785) {
    // -15030275251325730.575364780666
    s21_decimal decimal = {{0x4005F27A, 0x6F18F59, 0x3090C096, 0x800C0000}};
    // 15030275251325730.575364780666
    s21_decimal decimal_check = {{0x4005F27A, 0x6F18F59, 0x3090C096, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok786) {
    // 15030275251325730.575364780666
    s21_decimal decimal = {{0x4005F27A, 0x6F18F59, 0x3090C096, 0xC0000}};
    // -15030275251325730.575364780666
    s21_decimal decimal_check = {{0x4005F27A, 0x6F18F59, 0x3090C096, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok787) {
    // -776912281724424348.86526562650
    s21_decimal decimal = {{0x8057F15A, 0x61A714D9, 0xFB08AD7E, 0x800B0000}};
    // 776912281724424348.86526562650
    s21_decimal decimal_check = {{0x8057F15A, 0x61A714D9, 0xFB08AD7E, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok788) {
    // 776912281724424348.86526562650
    s21_decimal decimal = {{0x8057F15A, 0x61A714D9, 0xFB08AD7E, 0xB0000}};
    // -776912281724424348.86526562650
    s21_decimal decimal_check = {{0x8057F15A, 0x61A714D9, 0xFB08AD7E, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok789) {
    // 4531350170047949434475552.1436
    s21_decimal decimal = {{0xF086279C, 0x544B4249, 0x926A7339, 0x40000}};
    // -4531350170047949434475552.1436
    s21_decimal decimal_check = {{0xF086279C, 0x544B4249, 0x926A7339, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok790) {
    // -4531350170047949434475552.1436
    s21_decimal decimal = {{0xF086279C, 0x544B4249, 0x926A7339, 0x80040000}};
    // 4531350170047949434475552.1436
    s21_decimal decimal_check = {{0xF086279C, 0x544B4249, 0x926A7339, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok791) {
    // 53637047493703043440217603.231
    s21_decimal decimal = {{0x93CABC9F, 0xEB46ED7B, 0xAD4F869A, 0x30000}};
    // -53637047493703043440217603.231
    s21_decimal decimal_check = {{0x93CABC9F, 0xEB46ED7B, 0xAD4F869A, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok792) {
    // -53637047493703043440217603.231
    s21_decimal decimal = {{0x93CABC9F, 0xEB46ED7B, 0xAD4F869A, 0x80030000}};
    // 53637047493703043440217603.231
    s21_decimal decimal_check = {{0x93CABC9F, 0xEB46ED7B, 0xAD4F869A, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok793) {
    // 54804288291732332667.238099876
    s21_decimal decimal = {{0x96D02BA4, 0x5EF398A6, 0xB1150B75, 0x90000}};
    // -54804288291732332667.238099876
    s21_decimal decimal_check = {{0x96D02BA4, 0x5EF398A6, 0xB1150B75, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok794) {
    // -54804288291732332667.238099876
    s21_decimal decimal = {{0x96D02BA4, 0x5EF398A6, 0xB1150B75, 0x80090000}};
    // 54804288291732332667.238099876
    s21_decimal decimal_check = {{0x96D02BA4, 0x5EF398A6, 0xB1150B75, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok795) {
    // -985382.7201083808279374901426
    s21_decimal decimal = {{0xDAC4B0B2, 0xEF82E661, 0x1FD6E512, 0x80160000}};
    // 985382.7201083808279374901426
    s21_decimal decimal_check = {{0xDAC4B0B2, 0xEF82E661, 0x1FD6E512, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok796) {
    // 985382.7201083808279374901426
    s21_decimal decimal = {{0xDAC4B0B2, 0xEF82E661, 0x1FD6E512, 0x160000}};
    // -985382.7201083808279374901426
    s21_decimal decimal_check = {{0xDAC4B0B2, 0xEF82E661, 0x1FD6E512, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok797) {
    // 653105353.88405014972875006539
    s21_decimal decimal = {{0xA4DDE24B, 0xB70AAEFE, 0xD3079BD1, 0x140000}};
    // -653105353.88405014972875006539
    s21_decimal decimal_check = {{0xA4DDE24B, 0xB70AAEFE, 0xD3079BD1, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok798) {
    // -653105353.88405014972875006539
    s21_decimal decimal = {{0xA4DDE24B, 0xB70AAEFE, 0xD3079BD1, 0x80140000}};
    // 653105353.88405014972875006539
    s21_decimal decimal_check = {{0xA4DDE24B, 0xB70AAEFE, 0xD3079BD1, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok799) {
    // -13821854.118480016981366644819
    s21_decimal decimal = {{0xAB5BA053, 0x26D4FEF7, 0x2CA92B75, 0x80150000}};
    // 13821854.118480016981366644819
    s21_decimal decimal_check = {{0xAB5BA053, 0x26D4FEF7, 0x2CA92B75, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok800) {
    // 13821854.118480016981366644819
    s21_decimal decimal = {{0xAB5BA053, 0x26D4FEF7, 0x2CA92B75, 0x150000}};
    // -13821854.118480016981366644819
    s21_decimal decimal_check = {{0xAB5BA053, 0x26D4FEF7, 0x2CA92B75, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok801) {
    // -6.2016442506941176394830065597
    s21_decimal decimal = {{0x48BC2FBD, 0xCADABF47, 0xC862CC84, 0x801C0000}};
    // 6.2016442506941176394830065597
    s21_decimal decimal_check = {{0x48BC2FBD, 0xCADABF47, 0xC862CC84, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok802) {
    // 6.2016442506941176394830065597
    s21_decimal decimal = {{0x48BC2FBD, 0xCADABF47, 0xC862CC84, 0x1C0000}};
    // -6.2016442506941176394830065597
    s21_decimal decimal_check = {{0x48BC2FBD, 0xCADABF47, 0xC862CC84, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok803) {
    // 33051746141.289111961459202145
    s21_decimal decimal = {{0xFE6B9861, 0x8A8F808A, 0x6ACBC37C, 0x120000}};
    // -33051746141.289111961459202145
    s21_decimal decimal_check = {{0xFE6B9861, 0x8A8F808A, 0x6ACBC37C, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok804) {
    // -33051746141.289111961459202145
    s21_decimal decimal = {{0xFE6B9861, 0x8A8F808A, 0x6ACBC37C, 0x80120000}};
    // 33051746141.289111961459202145
    s21_decimal decimal_check = {{0xFE6B9861, 0x8A8F808A, 0x6ACBC37C, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok805) {
    // 12452390690806.252268332567169
    s21_decimal decimal = {{0xC98CA81, 0xFB036440, 0x283C604B, 0xF0000}};
    // -12452390690806.252268332567169
    s21_decimal decimal_check = {{0xC98CA81, 0xFB036440, 0x283C604B, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok806) {
    // -12452390690806.252268332567169
    s21_decimal decimal = {{0xC98CA81, 0xFB036440, 0x283C604B, 0x800F0000}};
    // 12452390690806.252268332567169
    s21_decimal decimal_check = {{0xC98CA81, 0xFB036440, 0x283C604B, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok807) {
    // -5183694786358.3434117358953514
    s21_decimal decimal = {{0xE302242A, 0x6F8D44F8, 0xA77E84AE, 0x80100000}};
    // 5183694786358.3434117358953514
    s21_decimal decimal_check = {{0xE302242A, 0x6F8D44F8, 0xA77E84AE, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok808) {
    // 5183694786358.3434117358953514
    s21_decimal decimal = {{0xE302242A, 0x6F8D44F8, 0xA77E84AE, 0x100000}};
    // -5183694786358.3434117358953514
    s21_decimal decimal_check = {{0xE302242A, 0x6F8D44F8, 0xA77E84AE, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok809) {
    // -67593171327538078754885011.985
    s21_decimal decimal = {{0x4B70A11, 0xECD258D0, 0xDA67C2C7, 0x80030000}};
    // 67593171327538078754885011.985
    s21_decimal decimal_check = {{0x4B70A11, 0xECD258D0, 0xDA67C2C7, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok810) {
    // 67593171327538078754885011.985
    s21_decimal decimal = {{0x4B70A11, 0xECD258D0, 0xDA67C2C7, 0x30000}};
    // -67593171327538078754885011.985
    s21_decimal decimal_check = {{0x4B70A11, 0xECD258D0, 0xDA67C2C7, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok811) {
    // -28396.530002071102622289802402
    s21_decimal decimal = {{0xF236B4A2, 0xF6FAD2C1, 0x5BC10F1F, 0x80180000}};
    // 28396.530002071102622289802402
    s21_decimal decimal_check = {{0xF236B4A2, 0xF6FAD2C1, 0x5BC10F1F, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok812) {
    // 28396.530002071102622289802402
    s21_decimal decimal = {{0xF236B4A2, 0xF6FAD2C1, 0x5BC10F1F, 0x180000}};
    // -28396.530002071102622289802402
    s21_decimal decimal_check = {{0xF236B4A2, 0xF6FAD2C1, 0x5BC10F1F, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok813) {
    // -36240630302206929873954303.496
    s21_decimal decimal = {{0xA42E6E08, 0x4B7A7DD8, 0x75198BF9, 0x80030000}};
    // 36240630302206929873954303.496
    s21_decimal decimal_check = {{0xA42E6E08, 0x4B7A7DD8, 0x75198BF9, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok814) {
    // 36240630302206929873954303.496
    s21_decimal decimal = {{0xA42E6E08, 0x4B7A7DD8, 0x75198BF9, 0x30000}};
    // -36240630302206929873954303.496
    s21_decimal decimal_check = {{0xA42E6E08, 0x4B7A7DD8, 0x75198BF9, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok815) {
    // 17338554760124.472732998122697
    s21_decimal decimal = {{0x3BB33CC9, 0xEF2DC0A1, 0x38061DC8, 0xF0000}};
    // -17338554760124.472732998122697
    s21_decimal decimal_check = {{0x3BB33CC9, 0xEF2DC0A1, 0x38061DC8, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok816) {
    // -17338554760124.472732998122697
    s21_decimal decimal = {{0x3BB33CC9, 0xEF2DC0A1, 0x38061DC8, 0x800F0000}};
    // 17338554760124.472732998122697
    s21_decimal decimal_check = {{0x3BB33CC9, 0xEF2DC0A1, 0x38061DC8, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok817) {
    // 474611017874439.51154039741077
    s21_decimal decimal = {{0xE4B5DA95, 0x533B07AE, 0x995AE73B, 0xE0000}};
    // -474611017874439.51154039741077
    s21_decimal decimal_check = {{0xE4B5DA95, 0x533B07AE, 0x995AE73B, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok818) {
    // -474611017874439.51154039741077
    s21_decimal decimal = {{0xE4B5DA95, 0x533B07AE, 0x995AE73B, 0x800E0000}};
    // 474611017874439.51154039741077
    s21_decimal decimal_check = {{0xE4B5DA95, 0x533B07AE, 0x995AE73B, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok819) {
    // 700238694105.9061505347544248
    s21_decimal decimal = {{0xDFF7E4B8, 0xB43A865D, 0x16A03D1C, 0x100000}};
    // -700238694105.9061505347544248
    s21_decimal decimal_check = {{0xDFF7E4B8, 0xB43A865D, 0x16A03D1C, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok820) {
    // -700238694105.9061505347544248
    s21_decimal decimal = {{0xDFF7E4B8, 0xB43A865D, 0x16A03D1C, 0x80100000}};
    // 700238694105.9061505347544248
    s21_decimal decimal_check = {{0xDFF7E4B8, 0xB43A865D, 0x16A03D1C, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok821) {
    // -3836156.7255702200272159480044
    s21_decimal decimal = {{0xA13B98EC, 0xEDD699C3, 0x7BF3F1D7, 0x80160000}};
    // 3836156.7255702200272159480044
    s21_decimal decimal_check = {{0xA13B98EC, 0xEDD699C3, 0x7BF3F1D7, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok822) {
    // 3836156.7255702200272159480044
    s21_decimal decimal = {{0xA13B98EC, 0xEDD699C3, 0x7BF3F1D7, 0x160000}};
    // -3836156.7255702200272159480044
    s21_decimal decimal_check = {{0xA13B98EC, 0xEDD699C3, 0x7BF3F1D7, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok823) {
    // -384482521655.10607733442365911
    s21_decimal decimal = {{0x745A49D7, 0x4E4C847D, 0x7C3BA616, 0x80110000}};
    // 384482521655.10607733442365911
    s21_decimal decimal_check = {{0x745A49D7, 0x4E4C847D, 0x7C3BA616, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok824) {
    // 384482521655.10607733442365911
    s21_decimal decimal = {{0x745A49D7, 0x4E4C847D, 0x7C3BA616, 0x110000}};
    // -384482521655.10607733442365911
    s21_decimal decimal_check = {{0x745A49D7, 0x4E4C847D, 0x7C3BA616, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok825) {
    // 3.5062977582964094538356878865
    s21_decimal decimal = {{0xCC9FEE11, 0x7687DD55, 0x714B6A4F, 0x1C0000}};
    // -3.5062977582964094538356878865
    s21_decimal decimal_check = {{0xCC9FEE11, 0x7687DD55, 0x714B6A4F, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok826) {
    // -3.5062977582964094538356878865
    s21_decimal decimal = {{0xCC9FEE11, 0x7687DD55, 0x714B6A4F, 0x801C0000}};
    // 3.5062977582964094538356878865
    s21_decimal decimal_check = {{0xCC9FEE11, 0x7687DD55, 0x714B6A4F, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok827) {
    // -5667473716660209.6226447982577
    s21_decimal decimal = {{0x980FFF1, 0xDC2696D, 0xB7203E6A, 0x800D0000}};
    // 5667473716660209.6226447982577
    s21_decimal decimal_check = {{0x980FFF1, 0xDC2696D, 0xB7203E6A, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok828) {
    // 5667473716660209.6226447982577
    s21_decimal decimal = {{0x980FFF1, 0xDC2696D, 0xB7203E6A, 0xD0000}};
    // -5667473716660209.6226447982577
    s21_decimal decimal_check = {{0x980FFF1, 0xDC2696D, 0xB7203E6A, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok829) {
    // -59128683278599741332498772969
    s21_decimal decimal = {{0x2C2D73E9, 0x57DFC06B, 0xBF0E19B7, 0x80000000}};
    // 59128683278599741332498772969
    s21_decimal decimal_check = {{0x2C2D73E9, 0x57DFC06B, 0xBF0E19B7, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok830) {
    // 59128683278599741332498772969
    s21_decimal decimal = {{0x2C2D73E9, 0x57DFC06B, 0xBF0E19B7, 0x0}};
    // -59128683278599741332498772969
    s21_decimal decimal_check = {{0x2C2D73E9, 0x57DFC06B, 0xBF0E19B7, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok831) {
    // 525563594897103.398285981778
    s21_decimal decimal = {{0xD289B852, 0x917E811F, 0x1B2BC6B, 0xC0000}};
    // -525563594897103.398285981778
    s21_decimal decimal_check = {{0xD289B852, 0x917E811F, 0x1B2BC6B, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok832) {
    // -525563594897103.398285981778
    s21_decimal decimal = {{0xD289B852, 0x917E811F, 0x1B2BC6B, 0x800C0000}};
    // 525563594897103.398285981778
    s21_decimal decimal_check = {{0xD289B852, 0x917E811F, 0x1B2BC6B, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok833) {
    // -31872.184105126612003502230073
    s21_decimal decimal = {{0x70110A39, 0x6E8B37A6, 0x66FC0D82, 0x80180000}};
    // 31872.184105126612003502230073
    s21_decimal decimal_check = {{0x70110A39, 0x6E8B37A6, 0x66FC0D82, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok834) {
    // 31872.184105126612003502230073
    s21_decimal decimal = {{0x70110A39, 0x6E8B37A6, 0x66FC0D82, 0x180000}};
    // -31872.184105126612003502230073
    s21_decimal decimal_check = {{0x70110A39, 0x6E8B37A6, 0x66FC0D82, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok835) {
    // -76345333810188353151.269478782
    s21_decimal decimal = {{0x8346217E, 0xCE8E8756, 0xF6AF6146, 0x80090000}};
    // 76345333810188353151.269478782
    s21_decimal decimal_check = {{0x8346217E, 0xCE8E8756, 0xF6AF6146, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok836) {
    // 76345333810188353151.269478782
    s21_decimal decimal = {{0x8346217E, 0xCE8E8756, 0xF6AF6146, 0x90000}};
    // -76345333810188353151.269478782
    s21_decimal decimal_check = {{0x8346217E, 0xCE8E8756, 0xF6AF6146, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok837) {
    // -7174574575679119963595196811.7
    s21_decimal decimal = {{0x9345DF75, 0xCE2717AD, 0xE7D2B09E, 0x80010000}};
    // 7174574575679119963595196811.7
    s21_decimal decimal_check = {{0x9345DF75, 0xCE2717AD, 0xE7D2B09E, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok838) {
    // 7174574575679119963595196811.7
    s21_decimal decimal = {{0x9345DF75, 0xCE2717AD, 0xE7D2B09E, 0x10000}};
    // -7174574575679119963595196811.7
    s21_decimal decimal_check = {{0x9345DF75, 0xCE2717AD, 0xE7D2B09E, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok839) {
    // 3166453.3424596529510029632683
    s21_decimal decimal = {{0x381AA4AB, 0x7BFFC2AD, 0x665049C4, 0x160000}};
    // -3166453.3424596529510029632683
    s21_decimal decimal_check = {{0x381AA4AB, 0x7BFFC2AD, 0x665049C4, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok840) {
    // -3166453.3424596529510029632683
    s21_decimal decimal = {{0x381AA4AB, 0x7BFFC2AD, 0x665049C4, 0x80160000}};
    // 3166453.3424596529510029632683
    s21_decimal decimal_check = {{0x381AA4AB, 0x7BFFC2AD, 0x665049C4, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok841) {
    // 36776561417115488875871116.163
    s21_decimal decimal = {{0x7C529B83, 0x3FC8EEA6, 0x76D4DBCD, 0x30000}};
    // -36776561417115488875871116.163
    s21_decimal decimal_check = {{0x7C529B83, 0x3FC8EEA6, 0x76D4DBCD, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok842) {
    // -36776561417115488875871116.163
    s21_decimal decimal = {{0x7C529B83, 0x3FC8EEA6, 0x76D4DBCD, 0x80030000}};
    // 36776561417115488875871116.163
    s21_decimal decimal_check = {{0x7C529B83, 0x3FC8EEA6, 0x76D4DBCD, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok843) {
    // 131043791001822.38035340302867
    s21_decimal decimal = {{0x3AF61A13, 0x797CD646, 0x2A57B036, 0xE0000}};
    // -131043791001822.38035340302867
    s21_decimal decimal_check = {{0x3AF61A13, 0x797CD646, 0x2A57B036, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok844) {
    // -131043791001822.38035340302867
    s21_decimal decimal = {{0x3AF61A13, 0x797CD646, 0x2A57B036, 0x800E0000}};
    // 131043791001822.38035340302867
    s21_decimal decimal_check = {{0x3AF61A13, 0x797CD646, 0x2A57B036, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok845) {
    // 120433990421.36034443271245061
    s21_decimal decimal = {{0x592E8D05, 0x47998A3F, 0x26EA10F2, 0x110000}};
    // -120433990421.36034443271245061
    s21_decimal decimal_check = {{0x592E8D05, 0x47998A3F, 0x26EA10F2, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok846) {
    // -120433990421.36034443271245061
    s21_decimal decimal = {{0x592E8D05, 0x47998A3F, 0x26EA10F2, 0x80110000}};
    // 120433990421.36034443271245061
    s21_decimal decimal_check = {{0x592E8D05, 0x47998A3F, 0x26EA10F2, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok847) {
    // 55666775789775262973830.377575
    s21_decimal decimal = {{0xC2403067, 0x53AF2293, 0xB3DE7A4A, 0x60000}};
    // -55666775789775262973830.377575
    s21_decimal decimal_check = {{0xC2403067, 0x53AF2293, 0xB3DE7A4A, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok848) {
    // -55666775789775262973830.377575
    s21_decimal decimal = {{0xC2403067, 0x53AF2293, 0xB3DE7A4A, 0x80060000}};
    // 55666775789775262973830.377575
    s21_decimal decimal_check = {{0xC2403067, 0x53AF2293, 0xB3DE7A4A, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok849) {
    // -6741911.8834465173255493230873
    s21_decimal decimal = {{0xA937A119, 0x5E88E7F7, 0xD9D7C9BB, 0x80160000}};
    // 6741911.8834465173255493230873
    s21_decimal decimal_check = {{0xA937A119, 0x5E88E7F7, 0xD9D7C9BB, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok850) {
    // 6741911.8834465173255493230873
    s21_decimal decimal = {{0xA937A119, 0x5E88E7F7, 0xD9D7C9BB, 0x160000}};
    // -6741911.8834465173255493230873
    s21_decimal decimal_check = {{0xA937A119, 0x5E88E7F7, 0xD9D7C9BB, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok851) {
    // 136778.02510971570586942454460
    s21_decimal decimal = {{0x94643ABC, 0xDC74899A, 0x2C320357, 0x170000}};
    // -136778.02510971570586942454460
    s21_decimal decimal_check = {{0x94643ABC, 0xDC74899A, 0x2C320357, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok852) {
    // -136778.02510971570586942454460
    s21_decimal decimal = {{0x94643ABC, 0xDC74899A, 0x2C320357, 0x80170000}};
    // 136778.02510971570586942454460
    s21_decimal decimal_check = {{0x94643ABC, 0xDC74899A, 0x2C320357, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok853) {
    // -46242543.886097454727015710672
    s21_decimal decimal = {{0x3CEC3FD0, 0x20CEE69B, 0x956AEF8F, 0x80150000}};
    // 46242543.886097454727015710672
    s21_decimal decimal_check = {{0x3CEC3FD0, 0x20CEE69B, 0x956AEF8F, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok854) {
    // 46242543.886097454727015710672
    s21_decimal decimal = {{0x3CEC3FD0, 0x20CEE69B, 0x956AEF8F, 0x150000}};
    // -46242543.886097454727015710672
    s21_decimal decimal_check = {{0x3CEC3FD0, 0x20CEE69B, 0x956AEF8F, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok855) {
    // -40.791876436962394540129614993
    s21_decimal decimal = {{0xD3037C91, 0xA2C0238B, 0x83CE3FD4, 0x801B0000}};
    // 40.791876436962394540129614993
    s21_decimal decimal_check = {{0xD3037C91, 0xA2C0238B, 0x83CE3FD4, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok856) {
    // 40.791876436962394540129614993
    s21_decimal decimal = {{0xD3037C91, 0xA2C0238B, 0x83CE3FD4, 0x1B0000}};
    // -40.791876436962394540129614993
    s21_decimal decimal_check = {{0xD3037C91, 0xA2C0238B, 0x83CE3FD4, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok857) {
    // -49756999731927641.043111197288
    s21_decimal decimal = {{0xBEA33A68, 0x492C302B, 0xA0C60688, 0x800C0000}};
    // 49756999731927641.043111197288
    s21_decimal decimal_check = {{0xBEA33A68, 0x492C302B, 0xA0C60688, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok858) {
    // 49756999731927641.043111197288
    s21_decimal decimal = {{0xBEA33A68, 0x492C302B, 0xA0C60688, 0xC0000}};
    // -49756999731927641.043111197288
    s21_decimal decimal_check = {{0xBEA33A68, 0x492C302B, 0xA0C60688, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok859) {
    // -28661776774289094351.326636307
    s21_decimal decimal = {{0xE7BD6913, 0x4C875CF8, 0x5C9C7750, 0x80090000}};
    // 28661776774289094351.326636307
    s21_decimal decimal_check = {{0xE7BD6913, 0x4C875CF8, 0x5C9C7750, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok860) {
    // 28661776774289094351.326636307
    s21_decimal decimal = {{0xE7BD6913, 0x4C875CF8, 0x5C9C7750, 0x90000}};
    // -28661776774289094351.326636307
    s21_decimal decimal_check = {{0xE7BD6913, 0x4C875CF8, 0x5C9C7750, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok861) {
    // 54701583.980450434134055537457
    s21_decimal decimal = {{0xF1474B31, 0x80089C5A, 0xB0C016F9, 0x150000}};
    // -54701583.980450434134055537457
    s21_decimal decimal_check = {{0xF1474B31, 0x80089C5A, 0xB0C016F9, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok862) {
    // -54701583.980450434134055537457
    s21_decimal decimal = {{0xF1474B31, 0x80089C5A, 0xB0C016F9, 0x80150000}};
    // 54701583.980450434134055537457
    s21_decimal decimal_check = {{0xF1474B31, 0x80089C5A, 0xB0C016F9, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok863) {
    // -2.596597038203724290724477478
    s21_decimal decimal = {{0x64B83A26, 0x7E973CF9, 0x863DACF, 0x801B0000}};
    // 2.596597038203724290724477478
    s21_decimal decimal_check = {{0x64B83A26, 0x7E973CF9, 0x863DACF, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok864) {
    // 2.596597038203724290724477478
    s21_decimal decimal = {{0x64B83A26, 0x7E973CF9, 0x863DACF, 0x1B0000}};
    // -2.596597038203724290724477478
    s21_decimal decimal_check = {{0x64B83A26, 0x7E973CF9, 0x863DACF, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok865) {
    // -660.17027224771166967426736420
    s21_decimal decimal = {{0xD75C6124, 0xE81598D1, 0xD5500148, 0x801A0000}};
    // 660.17027224771166967426736420
    s21_decimal decimal_check = {{0xD75C6124, 0xE81598D1, 0xD5500148, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok866) {
    // 660.17027224771166967426736420
    s21_decimal decimal = {{0xD75C6124, 0xE81598D1, 0xD5500148, 0x1A0000}};
    // -660.17027224771166967426736420
    s21_decimal decimal_check = {{0xD75C6124, 0xE81598D1, 0xD5500148, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok867) {
    // 2341110502190.8440369730403507
    s21_decimal decimal = {{0x5F3BBCB3, 0x40813793, 0x4BA53652, 0x100000}};
    // -2341110502190.8440369730403507
    s21_decimal decimal_check = {{0x5F3BBCB3, 0x40813793, 0x4BA53652, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok868) {
    // -2341110502190.8440369730403507
    s21_decimal decimal = {{0x5F3BBCB3, 0x40813793, 0x4BA53652, 0x80100000}};
    // 2341110502190.8440369730403507
    s21_decimal decimal_check = {{0x5F3BBCB3, 0x40813793, 0x4BA53652, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok869) {
    // -7501947213564737488.9026498320
    s21_decimal decimal = {{0xC0AAAF10, 0x68C37512, 0xF266A725, 0x800A0000}};
    // 7501947213564737488.9026498320
    s21_decimal decimal_check = {{0xC0AAAF10, 0x68C37512, 0xF266A725, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok870) {
    // 7501947213564737488.9026498320
    s21_decimal decimal = {{0xC0AAAF10, 0x68C37512, 0xF266A725, 0xA0000}};
    // -7501947213564737488.9026498320
    s21_decimal decimal_check = {{0xC0AAAF10, 0x68C37512, 0xF266A725, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok871) {
    // 439752.62741468675807786674808
    s21_decimal decimal = {{0x8125AA78, 0xFEFDC7F2, 0x8E177C19, 0x170000}};
    // -439752.62741468675807786674808
    s21_decimal decimal_check = {{0x8125AA78, 0xFEFDC7F2, 0x8E177C19, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok872) {
    // -439752.62741468675807786674808
    s21_decimal decimal = {{0x8125AA78, 0xFEFDC7F2, 0x8E177C19, 0x80170000}};
    // 439752.62741468675807786674808
    s21_decimal decimal_check = {{0x8125AA78, 0xFEFDC7F2, 0x8E177C19, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok873) {
    // 20924623640319768.320796462636
    s21_decimal decimal = {{0x70DF0E2C, 0x76BC5FB6, 0x439C7168, 0xC0000}};
    // -20924623640319768.320796462636
    s21_decimal decimal_check = {{0x70DF0E2C, 0x76BC5FB6, 0x439C7168, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok874) {
    // -20924623640319768.320796462636
    s21_decimal decimal = {{0x70DF0E2C, 0x76BC5FB6, 0x439C7168, 0x800C0000}};
    // 20924623640319768.320796462636
    s21_decimal decimal_check = {{0x70DF0E2C, 0x76BC5FB6, 0x439C7168, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok875) {
    // 452322156567094060225457.60205
    s21_decimal decimal = {{0x6FFCDFCD, 0x111DB09E, 0x9227363C, 0x50000}};
    // -452322156567094060225457.60205
    s21_decimal decimal_check = {{0x6FFCDFCD, 0x111DB09E, 0x9227363C, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok876) {
    // -452322156567094060225457.60205
    s21_decimal decimal = {{0x6FFCDFCD, 0x111DB09E, 0x9227363C, 0x80050000}};
    // 452322156567094060225457.60205
    s21_decimal decimal_check = {{0x6FFCDFCD, 0x111DB09E, 0x9227363C, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok877) {
    // -49110564328090650233530233.960
    s21_decimal decimal = {{0xBF003468, 0xD34395C8, 0x9EAF4E82, 0x80030000}};
    // 49110564328090650233530233.960
    s21_decimal decimal_check = {{0xBF003468, 0xD34395C8, 0x9EAF4E82, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok878) {
    // 49110564328090650233530233.960
    s21_decimal decimal = {{0xBF003468, 0xD34395C8, 0x9EAF4E82, 0x30000}};
    // -49110564328090650233530233.960
    s21_decimal decimal_check = {{0xBF003468, 0xD34395C8, 0x9EAF4E82, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok879) {
    // 6035.808177536380740546606690
    s21_decimal decimal = {{0xE8C83662, 0xF0856C18, 0x1380B418, 0x180000}};
    // -6035.808177536380740546606690
    s21_decimal decimal_check = {{0xE8C83662, 0xF0856C18, 0x1380B418, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok880) {
    // -6035.808177536380740546606690
    s21_decimal decimal = {{0xE8C83662, 0xF0856C18, 0x1380B418, 0x80180000}};
    // 6035.808177536380740546606690
    s21_decimal decimal_check = {{0xE8C83662, 0xF0856C18, 0x1380B418, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok881) {
    // -687504715629519.36141141397389
    s21_decimal decimal = {{0xD57ECF8D, 0x65D432AD, 0xDE250EA3, 0x800E0000}};
    // 687504715629519.36141141397389
    s21_decimal decimal_check = {{0xD57ECF8D, 0x65D432AD, 0xDE250EA3, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok882) {
    // 687504715629519.36141141397389
    s21_decimal decimal = {{0xD57ECF8D, 0x65D432AD, 0xDE250EA3, 0xE0000}};
    // -687504715629519.36141141397389
    s21_decimal decimal_check = {{0xD57ECF8D, 0x65D432AD, 0xDE250EA3, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok883) {
    // -62856265929.001220492484666884
    s21_decimal decimal = {{0x7A83E604, 0xBA3C8320, 0xCB197C0B, 0x80120000}};
    // 62856265929.001220492484666884
    s21_decimal decimal_check = {{0x7A83E604, 0xBA3C8320, 0xCB197C0B, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok884) {
    // 62856265929.001220492484666884
    s21_decimal decimal = {{0x7A83E604, 0xBA3C8320, 0xCB197C0B, 0x120000}};
    // -62856265929.001220492484666884
    s21_decimal decimal_check = {{0x7A83E604, 0xBA3C8320, 0xCB197C0B, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok885) {
    // -23595370816703298452722466.203
    s21_decimal decimal = {{0xCA9ABD9B, 0xE7F49E, 0x4C3DA21F, 0x80030000}};
    // 23595370816703298452722466.203
    s21_decimal decimal_check = {{0xCA9ABD9B, 0xE7F49E, 0x4C3DA21F, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok886) {
    // 23595370816703298452722466.203
    s21_decimal decimal = {{0xCA9ABD9B, 0xE7F49E, 0x4C3DA21F, 0x30000}};
    // -23595370816703298452722466.203
    s21_decimal decimal_check = {{0xCA9ABD9B, 0xE7F49E, 0x4C3DA21F, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok887) {
    // -741483364683691948158959.27187
    s21_decimal decimal = {{0xF7347993, 0x427543D8, 0xEF9610FE, 0x80050000}};
    // 741483364683691948158959.27187
    s21_decimal decimal_check = {{0xF7347993, 0x427543D8, 0xEF9610FE, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok888) {
    // 741483364683691948158959.27187
    s21_decimal decimal = {{0xF7347993, 0x427543D8, 0xEF9610FE, 0x50000}};
    // -741483364683691948158959.27187
    s21_decimal decimal_check = {{0xF7347993, 0x427543D8, 0xEF9610FE, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok889) {
    // -163894856.43687686791913333762
    s21_decimal decimal = {{0xBF04E402, 0xA51AD7E, 0x34F51095, 0x80140000}};
    // 163894856.43687686791913333762
    s21_decimal decimal_check = {{0xBF04E402, 0xA51AD7E, 0x34F51095, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok890) {
    // 163894856.43687686791913333762
    s21_decimal decimal = {{0xBF04E402, 0xA51AD7E, 0x34F51095, 0x140000}};
    // -163894856.43687686791913333762
    s21_decimal decimal_check = {{0xBF04E402, 0xA51AD7E, 0x34F51095, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok891) {
    // -1787444327.5435647242066628435
    s21_decimal decimal = {{0xE80E8F53, 0x8F4FDA93, 0x39C16497, 0x80130000}};
    // 1787444327.5435647242066628435
    s21_decimal decimal_check = {{0xE80E8F53, 0x8F4FDA93, 0x39C16497, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok892) {
    // 1787444327.5435647242066628435
    s21_decimal decimal = {{0xE80E8F53, 0x8F4FDA93, 0x39C16497, 0x130000}};
    // -1787444327.5435647242066628435
    s21_decimal decimal_check = {{0xE80E8F53, 0x8F4FDA93, 0x39C16497, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok893) {
    // 4107574719881790.7400933254742
    s21_decimal decimal = {{0x3022656, 0x789FBD26, 0x84B90FCD, 0xD0000}};
    // -4107574719881790.7400933254742
    s21_decimal decimal_check = {{0x3022656, 0x789FBD26, 0x84B90FCD, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok894) {
    // -4107574719881790.7400933254742
    s21_decimal decimal = {{0x3022656, 0x789FBD26, 0x84B90FCD, 0x800D0000}};
    // 4107574719881790.7400933254742
    s21_decimal decimal_check = {{0x3022656, 0x789FBD26, 0x84B90FCD, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok895) {
    // -15238977639375862405389.462737
    s21_decimal decimal = {{0x7EE5ACD1, 0x274997F0, 0x313D6309, 0x80060000}};
    // 15238977639375862405389.462737
    s21_decimal decimal_check = {{0x7EE5ACD1, 0x274997F0, 0x313D6309, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok896) {
    // 15238977639375862405389.462737
    s21_decimal decimal = {{0x7EE5ACD1, 0x274997F0, 0x313D6309, 0x60000}};
    // -15238977639375862405389.462737
    s21_decimal decimal_check = {{0x7EE5ACD1, 0x274997F0, 0x313D6309, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok897) {
    // -54101751124144.809222335792316
    s21_decimal decimal = {{0x125684BC, 0x3411A44F, 0xAECFEB6D, 0x800F0000}};
    // 54101751124144.809222335792316
    s21_decimal decimal_check = {{0x125684BC, 0x3411A44F, 0xAECFEB6D, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok898) {
    // 54101751124144.809222335792316
    s21_decimal decimal = {{0x125684BC, 0x3411A44F, 0xAECFEB6D, 0xF0000}};
    // -54101751124144.809222335792316
    s21_decimal decimal_check = {{0x125684BC, 0x3411A44F, 0xAECFEB6D, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok899) {
    // -51396.324122604622092683738384
    s21_decimal decimal = {{0xCDEC7D10, 0x93299859, 0xA6120AF9, 0x80180000}};
    // 51396.324122604622092683738384
    s21_decimal decimal_check = {{0xCDEC7D10, 0x93299859, 0xA6120AF9, 0x180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok900) {
    // 51396.324122604622092683738384
    s21_decimal decimal = {{0xCDEC7D10, 0x93299859, 0xA6120AF9, 0x180000}};
    // -51396.324122604622092683738384
    s21_decimal decimal_check = {{0xCDEC7D10, 0x93299859, 0xA6120AF9, 0x80180000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok901) {
    // 1257378312148719.8795186218860
    s21_decimal decimal = {{0x58B6A76C, 0xD57A6E93, 0x28A0CA24, 0xD0000}};
    // -1257378312148719.8795186218860
    s21_decimal decimal_check = {{0x58B6A76C, 0xD57A6E93, 0x28A0CA24, 0x800D0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok902) {
    // -1257378312148719.8795186218860
    s21_decimal decimal = {{0x58B6A76C, 0xD57A6E93, 0x28A0CA24, 0x800D0000}};
    // 1257378312148719.8795186218860
    s21_decimal decimal_check = {{0x58B6A76C, 0xD57A6E93, 0x28A0CA24, 0xD0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok903) {
    // -69212599648938134433703383.617
    s21_decimal decimal = {{0x81F3D241, 0x232D423B, 0xDFA35211, 0x80030000}};
    // 69212599648938134433703383.617
    s21_decimal decimal_check = {{0x81F3D241, 0x232D423B, 0xDFA35211, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok904) {
    // 69212599648938134433703383.617
    s21_decimal decimal = {{0x81F3D241, 0x232D423B, 0xDFA35211, 0x30000}};
    // -69212599648938134433703383.617
    s21_decimal decimal_check = {{0x81F3D241, 0x232D423B, 0xDFA35211, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok905) {
    // -691677929774865779208215.12331
    s21_decimal decimal = {{0xA0C1488B, 0x9C65CB43, 0xDF7E41E2, 0x80050000}};
    // 691677929774865779208215.12331
    s21_decimal decimal_check = {{0xA0C1488B, 0x9C65CB43, 0xDF7E41E2, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok906) {
    // 691677929774865779208215.12331
    s21_decimal decimal = {{0xA0C1488B, 0x9C65CB43, 0xDF7E41E2, 0x50000}};
    // -691677929774865779208215.12331
    s21_decimal decimal_check = {{0xA0C1488B, 0x9C65CB43, 0xDF7E41E2, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok907) {
    // -199399989702.75268695565803332
    s21_decimal decimal = {{0x78A41F44, 0x2584D9A8, 0x406DFB06, 0x80110000}};
    // 199399989702.75268695565803332
    s21_decimal decimal_check = {{0x78A41F44, 0x2584D9A8, 0x406DFB06, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok908) {
    // 199399989702.75268695565803332
    s21_decimal decimal = {{0x78A41F44, 0x2584D9A8, 0x406DFB06, 0x110000}};
    // -199399989702.75268695565803332
    s21_decimal decimal_check = {{0x78A41F44, 0x2584D9A8, 0x406DFB06, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok909) {
    // 2540106587315049901576149858.3
    s21_decimal decimal = {{0xE92691D7, 0x27E65E1D, 0x521344EC, 0x10000}};
    // -2540106587315049901576149858.3
    s21_decimal decimal_check = {{0xE92691D7, 0x27E65E1D, 0x521344EC, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok910) {
    // -2540106587315049901576149858.3
    s21_decimal decimal = {{0xE92691D7, 0x27E65E1D, 0x521344EC, 0x80010000}};
    // 2540106587315049901576149858.3
    s21_decimal decimal_check = {{0xE92691D7, 0x27E65E1D, 0x521344EC, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok911) {
    // -32616655.807941432780321666836
    s21_decimal decimal = {{0xE2973714, 0x4F215521, 0x6963DD86, 0x80150000}};
    // 32616655.807941432780321666836
    s21_decimal decimal_check = {{0xE2973714, 0x4F215521, 0x6963DD86, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok912) {
    // 32616655.807941432780321666836
    s21_decimal decimal = {{0xE2973714, 0x4F215521, 0x6963DD86, 0x150000}};
    // -32616655.807941432780321666836
    s21_decimal decimal_check = {{0xE2973714, 0x4F215521, 0x6963DD86, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok913) {
    // 66475160517775602158.908888406
    s21_decimal decimal = {{0x9CBE5556, 0x7C185F27, 0xD6CAF6C8, 0x90000}};
    // -66475160517775602158.908888406
    s21_decimal decimal_check = {{0x9CBE5556, 0x7C185F27, 0xD6CAF6C8, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok914) {
    // -66475160517775602158.908888406
    s21_decimal decimal = {{0x9CBE5556, 0x7C185F27, 0xD6CAF6C8, 0x80090000}};
    // 66475160517775602158.908888406
    s21_decimal decimal_check = {{0x9CBE5556, 0x7C185F27, 0xD6CAF6C8, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok915) {
    // 54010639049993.555855560743980
    s21_decimal decimal = {{0x50B91C2C, 0xC4449934, 0xAE848DB1, 0xF0000}};
    // -54010639049993.555855560743980
    s21_decimal decimal_check = {{0x50B91C2C, 0xC4449934, 0xAE848DB1, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok916) {
    // -54010639049993.555855560743980
    s21_decimal decimal = {{0x50B91C2C, 0xC4449934, 0xAE848DB1, 0x800F0000}};
    // 54010639049993.555855560743980
    s21_decimal decimal_check = {{0x50B91C2C, 0xC4449934, 0xAE848DB1, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok917) {
    // -477.3719976970560233446532679
    s21_decimal decimal = {{0x11536647, 0x7E528589, 0xF6CBA86, 0x80190000}};
    // 477.3719976970560233446532679
    s21_decimal decimal_check = {{0x11536647, 0x7E528589, 0xF6CBA86, 0x190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok918) {
    // 477.3719976970560233446532679
    s21_decimal decimal = {{0x11536647, 0x7E528589, 0xF6CBA86, 0x190000}};
    // -477.3719976970560233446532679
    s21_decimal decimal_check = {{0x11536647, 0x7E528589, 0xF6CBA86, 0x80190000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok919) {
    // -539886.89898024052874868347952
    s21_decimal decimal = {{0x13C2D430, 0xDAAC7969, 0xAE7265C7, 0x80170000}};
    // 539886.89898024052874868347952
    s21_decimal decimal_check = {{0x13C2D430, 0xDAAC7969, 0xAE7265C7, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok920) {
    // 539886.89898024052874868347952
    s21_decimal decimal = {{0x13C2D430, 0xDAAC7969, 0xAE7265C7, 0x170000}};
    // -539886.89898024052874868347952
    s21_decimal decimal_check = {{0x13C2D430, 0xDAAC7969, 0xAE7265C7, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok921) {
    // -264203459915.79400930690346710
    s21_decimal decimal = {{0x56102ED6, 0x182E1F3D, 0x555E65E2, 0x80110000}};
    // 264203459915.79400930690346710
    s21_decimal decimal_check = {{0x56102ED6, 0x182E1F3D, 0x555E65E2, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok922) {
    // 264203459915.79400930690346710
    s21_decimal decimal = {{0x56102ED6, 0x182E1F3D, 0x555E65E2, 0x110000}};
    // -264203459915.79400930690346710
    s21_decimal decimal_check = {{0x56102ED6, 0x182E1F3D, 0x555E65E2, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok923) {
    // -599345149599.72301263909886415
    s21_decimal decimal = {{0x4DF19CF, 0x52C6DA25, 0xC1A8AB36, 0x80110000}};
    // 599345149599.72301263909886415
    s21_decimal decimal_check = {{0x4DF19CF, 0x52C6DA25, 0xC1A8AB36, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok924) {
    // 599345149599.72301263909886415
    s21_decimal decimal = {{0x4DF19CF, 0x52C6DA25, 0xC1A8AB36, 0x110000}};
    // -599345149599.72301263909886415
    s21_decimal decimal_check = {{0x4DF19CF, 0x52C6DA25, 0xC1A8AB36, 0x80110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok925) {
    // -5333107052.7528560145838075146
    s21_decimal decimal = {{0xA0B76D0A, 0x58A0F672, 0xAC526D76, 0x80130000}};
    // 5333107052.7528560145838075146
    s21_decimal decimal_check = {{0xA0B76D0A, 0x58A0F672, 0xAC526D76, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok926) {
    // 5333107052.7528560145838075146
    s21_decimal decimal = {{0xA0B76D0A, 0x58A0F672, 0xAC526D76, 0x130000}};
    // -5333107052.7528560145838075146
    s21_decimal decimal_check = {{0xA0B76D0A, 0x58A0F672, 0xAC526D76, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok927) {
    // 242013135176385326.70163654447
    s21_decimal decimal = {{0xFE2A172F, 0xA42DE21B, 0x4E32DB7A, 0xB0000}};
    // -242013135176385326.70163654447
    s21_decimal decimal_check = {{0xFE2A172F, 0xA42DE21B, 0x4E32DB7A, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok928) {
    // -242013135176385326.70163654447
    s21_decimal decimal = {{0xFE2A172F, 0xA42DE21B, 0x4E32DB7A, 0x800B0000}};
    // 242013135176385326.70163654447
    s21_decimal decimal_check = {{0xFE2A172F, 0xA42DE21B, 0x4E32DB7A, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok929) {
    // 2367332.4036581459797138363598
    s21_decimal decimal = {{0x392A54CE, 0x854FA479, 0x4C7E1D5B, 0x160000}};
    // -2367332.4036581459797138363598
    s21_decimal decimal_check = {{0x392A54CE, 0x854FA479, 0x4C7E1D5B, 0x80160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok930) {
    // -2367332.4036581459797138363598
    s21_decimal decimal = {{0x392A54CE, 0x854FA479, 0x4C7E1D5B, 0x80160000}};
    // 2367332.4036581459797138363598
    s21_decimal decimal_check = {{0x392A54CE, 0x854FA479, 0x4C7E1D5B, 0x160000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok931) {
    // 464147.22989913137210363088692
    s21_decimal decimal = {{0x9760F34, 0xC807CCC, 0x95F95BE7, 0x170000}};
    // -464147.22989913137210363088692
    s21_decimal decimal_check = {{0x9760F34, 0xC807CCC, 0x95F95BE7, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok932) {
    // -464147.22989913137210363088692
    s21_decimal decimal = {{0x9760F34, 0xC807CCC, 0x95F95BE7, 0x80170000}};
    // 464147.22989913137210363088692
    s21_decimal decimal_check = {{0x9760F34, 0xC807CCC, 0x95F95BE7, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok933) {
    // -1711193943676.7872965424775507
    s21_decimal decimal = {{0xAAF50153, 0xA3A2F639, 0x374AAA1F, 0x80100000}};
    // 1711193943676.7872965424775507
    s21_decimal decimal_check = {{0xAAF50153, 0xA3A2F639, 0x374AAA1F, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok934) {
    // 1711193943676.7872965424775507
    s21_decimal decimal = {{0xAAF50153, 0xA3A2F639, 0x374AAA1F, 0x100000}};
    // -1711193943676.7872965424775507
    s21_decimal decimal_check = {{0xAAF50153, 0xA3A2F639, 0x374AAA1F, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok935) {
    // 53409928.548733207315651224291
    s21_decimal decimal = {{0xD32BE2E3, 0x3DD9DA46, 0xAC93A84C, 0x150000}};
    // -53409928.548733207315651224291
    s21_decimal decimal_check = {{0xD32BE2E3, 0x3DD9DA46, 0xAC93A84C, 0x80150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok936) {
    // -53409928.548733207315651224291
    s21_decimal decimal = {{0xD32BE2E3, 0x3DD9DA46, 0xAC93A84C, 0x80150000}};
    // 53409928.548733207315651224291
    s21_decimal decimal_check = {{0xD32BE2E3, 0x3DD9DA46, 0xAC93A84C, 0x150000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok937) {
    // -68032.37326130614338486516759
    s21_decimal decimal = {{0x3687BC17, 0x723E60D0, 0x15FB818A, 0x80170000}};
    // 68032.37326130614338486516759
    s21_decimal decimal_check = {{0x3687BC17, 0x723E60D0, 0x15FB818A, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok938) {
    // 68032.37326130614338486516759
    s21_decimal decimal = {{0x3687BC17, 0x723E60D0, 0x15FB818A, 0x170000}};
    // -68032.37326130614338486516759
    s21_decimal decimal_check = {{0x3687BC17, 0x723E60D0, 0x15FB818A, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok939) {
    // 2661541642111.868968501687040
    s21_decimal decimal = {{0xB6D6B300, 0x86E3FBF7, 0x899935D, 0xF0000}};
    // -2661541642111.868968501687040
    s21_decimal decimal_check = {{0xB6D6B300, 0x86E3FBF7, 0x899935D, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok940) {
    // -2661541642111.868968501687040
    s21_decimal decimal = {{0xB6D6B300, 0x86E3FBF7, 0x899935D, 0x800F0000}};
    // 2661541642111.868968501687040
    s21_decimal decimal_check = {{0xB6D6B300, 0x86E3FBF7, 0x899935D, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok941) {
    // 4.8457296849524270770518456242
    s21_decimal decimal = {{0x678377B2, 0xD9F94BB4, 0x9C92EFBD, 0x1C0000}};
    // -4.8457296849524270770518456242
    s21_decimal decimal_check = {{0x678377B2, 0xD9F94BB4, 0x9C92EFBD, 0x801C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok942) {
    // -4.8457296849524270770518456242
    s21_decimal decimal = {{0x678377B2, 0xD9F94BB4, 0x9C92EFBD, 0x801C0000}};
    // 4.8457296849524270770518456242
    s21_decimal decimal_check = {{0x678377B2, 0xD9F94BB4, 0x9C92EFBD, 0x1C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok943) {
    // 519460123.66219060511605387135
    s21_decimal decimal = {{0xD505EF7F, 0xF87E6EBE, 0xA7D8BBFC, 0x140000}};
    // -519460123.66219060511605387135
    s21_decimal decimal_check = {{0xD505EF7F, 0xF87E6EBE, 0xA7D8BBFC, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok944) {
    // -519460123.66219060511605387135
    s21_decimal decimal = {{0xD505EF7F, 0xF87E6EBE, 0xA7D8BBFC, 0x80140000}};
    // 519460123.66219060511605387135
    s21_decimal decimal_check = {{0xD505EF7F, 0xF87E6EBE, 0xA7D8BBFC, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok945) {
    // -2586294417297089493552197.9856
    s21_decimal decimal = {{0xED336DD0, 0xF5D7683C, 0x53915374, 0x80040000}};
    // 2586294417297089493552197.9856
    s21_decimal decimal_check = {{0xED336DD0, 0xF5D7683C, 0x53915374, 0x40000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok946) {
    // 2586294417297089493552197.9856
    s21_decimal decimal = {{0xED336DD0, 0xF5D7683C, 0x53915374, 0x40000}};
    // -2586294417297089493552197.9856
    s21_decimal decimal_check = {{0xED336DD0, 0xF5D7683C, 0x53915374, 0x80040000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok947) {
    // -199694731113080613944.34400207
    s21_decimal decimal = {{0x4B421FCF, 0x8896F2AE, 0x40865C6A, 0x80080000}};
    // 199694731113080613944.34400207
    s21_decimal decimal_check = {{0x4B421FCF, 0x8896F2AE, 0x40865C6A, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok948) {
    // 199694731113080613944.34400207
    s21_decimal decimal = {{0x4B421FCF, 0x8896F2AE, 0x40865C6A, 0x80000}};
    // -199694731113080613944.34400207
    s21_decimal decimal_check = {{0x4B421FCF, 0x8896F2AE, 0x40865C6A, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok949) {
    // 50042765294467513495253976855
    s21_decimal decimal = {{0x3F488717, 0x78E1B68A, 0xA1B267BE, 0x0}};
    // -50042765294467513495253976855
    s21_decimal decimal_check = {{0x3F488717, 0x78E1B68A, 0xA1B267BE, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok950) {
    // -50042765294467513495253976855
    s21_decimal decimal = {{0x3F488717, 0x78E1B68A, 0xA1B267BE, 0x80000000}};
    // 50042765294467513495253976855
    s21_decimal decimal_check = {{0x3F488717, 0x78E1B68A, 0xA1B267BE, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok951) {
    // -457425026200420287392042157.51
    s21_decimal decimal = {{0xC88FF3C7, 0xC757117B, 0x93CD4FB3, 0x80020000}};
    // 457425026200420287392042157.51
    s21_decimal decimal_check = {{0xC88FF3C7, 0xC757117B, 0x93CD4FB3, 0x20000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok952) {
    // 457425026200420287392042157.51
    s21_decimal decimal = {{0xC88FF3C7, 0xC757117B, 0x93CD4FB3, 0x20000}};
    // -457425026200420287392042157.51
    s21_decimal decimal_check = {{0xC88FF3C7, 0xC757117B, 0x93CD4FB3, 0x80020000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok953) {
    // -72310586827734683605914423.783
    s21_decimal decimal = {{0x692111E7, 0x9DD85508, 0xE9A5EA5E, 0x80030000}};
    // 72310586827734683605914423.783
    s21_decimal decimal_check = {{0x692111E7, 0x9DD85508, 0xE9A5EA5E, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok954) {
    // 72310586827734683605914423.783
    s21_decimal decimal = {{0x692111E7, 0x9DD85508, 0xE9A5EA5E, 0x30000}};
    // -72310586827734683605914423.783
    s21_decimal decimal_check = {{0x692111E7, 0x9DD85508, 0xE9A5EA5E, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok955) {
    // -63413178181918057777804.485714
    s21_decimal decimal = {{0x4B462452, 0x73C9C3A3, 0xCCE626CD, 0x80060000}};
    // 63413178181918057777804.485714
    s21_decimal decimal_check = {{0x4B462452, 0x73C9C3A3, 0xCCE626CD, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok956) {
    // 63413178181918057777804.485714
    s21_decimal decimal = {{0x4B462452, 0x73C9C3A3, 0xCCE626CD, 0x60000}};
    // -63413178181918057777804.485714
    s21_decimal decimal_check = {{0x4B462452, 0x73C9C3A3, 0xCCE626CD, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok957) {
    // -125335521963077580.93288723677
    s21_decimal decimal = {{0x39C9D4DD, 0x286A22A, 0x287F82EA, 0x800B0000}};
    // 125335521963077580.93288723677
    s21_decimal decimal_check = {{0x39C9D4DD, 0x286A22A, 0x287F82EA, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok958) {
    // 125335521963077580.93288723677
    s21_decimal decimal = {{0x39C9D4DD, 0x286A22A, 0x287F82EA, 0xB0000}};
    // -125335521963077580.93288723677
    s21_decimal decimal_check = {{0x39C9D4DD, 0x286A22A, 0x287F82EA, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok959) {
    // -302.11393210220011229657780432
    s21_decimal decimal = {{0x2D0150D0, 0x9DE1362D, 0x619E475B, 0x801A0000}};
    // 302.11393210220011229657780432
    s21_decimal decimal_check = {{0x2D0150D0, 0x9DE1362D, 0x619E475B, 0x1A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok960) {
    // 302.11393210220011229657780432
    s21_decimal decimal = {{0x2D0150D0, 0x9DE1362D, 0x619E475B, 0x1A0000}};
    // -302.11393210220011229657780432
    s21_decimal decimal_check = {{0x2D0150D0, 0x9DE1362D, 0x619E475B, 0x801A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok961) {
    // -46816499694591064.294714899966
    s21_decimal decimal = {{0xC8DDFDFE, 0xDA2525F3, 0x9745B36D, 0x800C0000}};
    // 46816499694591064.294714899966
    s21_decimal decimal_check = {{0xC8DDFDFE, 0xDA2525F3, 0x9745B36D, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok962) {
    // 46816499694591064.294714899966
    s21_decimal decimal = {{0xC8DDFDFE, 0xDA2525F3, 0x9745B36D, 0xC0000}};
    // -46816499694591064.294714899966
    s21_decimal decimal_check = {{0xC8DDFDFE, 0xDA2525F3, 0x9745B36D, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok963) {
    // -1899403862578.8668315357170323
    s21_decimal decimal = {{0xA75C4A93, 0x1E207895, 0x3D5F8021, 0x80100000}};
    // 1899403862578.8668315357170323
    s21_decimal decimal_check = {{0xA75C4A93, 0x1E207895, 0x3D5F8021, 0x100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok964) {
    // 1899403862578.8668315357170323
    s21_decimal decimal = {{0xA75C4A93, 0x1E207895, 0x3D5F8021, 0x100000}};
    // -1899403862578.8668315357170323
    s21_decimal decimal_check = {{0xA75C4A93, 0x1E207895, 0x3D5F8021, 0x80100000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok965) {
    // -16345822771297715.35137753127
    s21_decimal decimal = {{0xEECBC827, 0xCC6BCF7F, 0x5481842, 0x800B0000}};
    // 16345822771297715.35137753127
    s21_decimal decimal_check = {{0xEECBC827, 0xCC6BCF7F, 0x5481842, 0xB0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok966) {
    // 16345822771297715.35137753127
    s21_decimal decimal = {{0xEECBC827, 0xCC6BCF7F, 0x5481842, 0xB0000}};
    // -16345822771297715.35137753127
    s21_decimal decimal_check = {{0xEECBC827, 0xCC6BCF7F, 0x5481842, 0x800B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok967) {
    // -72.901924197290007046614505467
    s21_decimal decimal = {{0x924557FB, 0xA75D6FC7, 0xEB8F0EED, 0x801B0000}};
    // 72.901924197290007046614505467
    s21_decimal decimal_check = {{0x924557FB, 0xA75D6FC7, 0xEB8F0EED, 0x1B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok968) {
    // 72.901924197290007046614505467
    s21_decimal decimal = {{0x924557FB, 0xA75D6FC7, 0xEB8F0EED, 0x1B0000}};
    // -72.901924197290007046614505467
    s21_decimal decimal_check = {{0x924557FB, 0xA75D6FC7, 0xEB8F0EED, 0x801B0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok969) {
    // -282236638347022354.0187283394
    s21_decimal decimal = {{0x33FBFC2, 0x39B55CFA, 0x91E9B54, 0x800A0000}};
    // 282236638347022354.0187283394
    s21_decimal decimal_check = {{0x33FBFC2, 0x39B55CFA, 0x91E9B54, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok970) {
    // 282236638347022354.0187283394
    s21_decimal decimal = {{0x33FBFC2, 0x39B55CFA, 0x91E9B54, 0xA0000}};
    // -282236638347022354.0187283394
    s21_decimal decimal_check = {{0x33FBFC2, 0x39B55CFA, 0x91E9B54, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok971) {
    // 48288007672417452531842304033
    s21_decimal decimal = {{0xCBEC4821, 0x2BED059E, 0x9C06E75D, 0x0}};
    // -48288007672417452531842304033
    s21_decimal decimal_check = {{0xCBEC4821, 0x2BED059E, 0x9C06E75D, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok972) {
    // -48288007672417452531842304033
    s21_decimal decimal = {{0xCBEC4821, 0x2BED059E, 0x9C06E75D, 0x80000000}};
    // 48288007672417452531842304033
    s21_decimal decimal_check = {{0xCBEC4821, 0x2BED059E, 0x9C06E75D, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok973) {
    // 64006437557224887691199710.512
    s21_decimal decimal = {{0xE6050530, 0xA14AFA9D, 0xCED0E25C, 0x30000}};
    // -64006437557224887691199710.512
    s21_decimal decimal_check = {{0xE6050530, 0xA14AFA9D, 0xCED0E25C, 0x80030000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok974) {
    // -64006437557224887691199710.512
    s21_decimal decimal = {{0xE6050530, 0xA14AFA9D, 0xCED0E25C, 0x80030000}};
    // 64006437557224887691199710.512
    s21_decimal decimal_check = {{0xE6050530, 0xA14AFA9D, 0xCED0E25C, 0x30000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok975) {
    // 46642666123238344382848119685
    s21_decimal decimal = {{0x1D2B3385, 0x110998EA, 0x96B5E8BD, 0x0}};
    // -46642666123238344382848119685
    s21_decimal decimal_check = {{0x1D2B3385, 0x110998EA, 0x96B5E8BD, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok976) {
    // -46642666123238344382848119685
    s21_decimal decimal = {{0x1D2B3385, 0x110998EA, 0x96B5E8BD, 0x80000000}};
    // 46642666123238344382848119685
    s21_decimal decimal_check = {{0x1D2B3385, 0x110998EA, 0x96B5E8BD, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok977) {
    // -78057463950659013.5127323377
    s21_decimal decimal = {{0xC45732F1, 0xFF3BD529, 0x285AD1B, 0x800A0000}};
    // 78057463950659013.5127323377
    s21_decimal decimal_check = {{0xC45732F1, 0xFF3BD529, 0x285AD1B, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok978) {
    // 78057463950659013.5127323377
    s21_decimal decimal = {{0xC45732F1, 0xFF3BD529, 0x285AD1B, 0xA0000}};
    // -78057463950659013.5127323377
    s21_decimal decimal_check = {{0xC45732F1, 0xFF3BD529, 0x285AD1B, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok979) {
    // -166067859.03204182917936128463
    s21_decimal decimal = {{0xED2521CF, 0xB678D50C, 0x35A8CFB3, 0x80140000}};
    // 166067859.03204182917936128463
    s21_decimal decimal_check = {{0xED2521CF, 0xB678D50C, 0x35A8CFB3, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok980) {
    // 166067859.03204182917936128463
    s21_decimal decimal = {{0xED2521CF, 0xB678D50C, 0x35A8CFB3, 0x140000}};
    // -166067859.03204182917936128463
    s21_decimal decimal_check = {{0xED2521CF, 0xB678D50C, 0x35A8CFB3, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok981) {
    // -2252784754217328866832980136
    s21_decimal decimal = {{0xD8C98A8, 0x3BB520F5, 0x74775BA, 0x80000000}};
    // 2252784754217328866832980136
    s21_decimal decimal_check = {{0xD8C98A8, 0x3BB520F5, 0x74775BA, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok982) {
    // 2252784754217328866832980136
    s21_decimal decimal = {{0xD8C98A8, 0x3BB520F5, 0x74775BA, 0x0}};
    // -2252784754217328866832980136
    s21_decimal decimal_check = {{0xD8C98A8, 0x3BB520F5, 0x74775BA, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok983) {
    // -427579323754187997327165.64258
    s21_decimal decimal = {{0x2B956F22, 0x9EF12A57, 0x8A28885E, 0x80050000}};
    // 427579323754187997327165.64258
    s21_decimal decimal_check = {{0x2B956F22, 0x9EF12A57, 0x8A28885E, 0x50000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok984) {
    // 427579323754187997327165.64258
    s21_decimal decimal = {{0x2B956F22, 0x9EF12A57, 0x8A28885E, 0x50000}};
    // -427579323754187997327165.64258
    s21_decimal decimal_check = {{0x2B956F22, 0x9EF12A57, 0x8A28885E, 0x80050000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok985) {
    // -465443016545191895908.96236286
    s21_decimal decimal = {{0xD40B56FE, 0x88531CB2, 0x96648B40, 0x80080000}};
    // 465443016545191895908.96236286
    s21_decimal decimal_check = {{0xD40B56FE, 0x88531CB2, 0x96648B40, 0x80000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok986) {
    // 465443016545191895908.96236286
    s21_decimal decimal = {{0xD40B56FE, 0x88531CB2, 0x96648B40, 0x80000}};
    // -465443016545191895908.96236286
    s21_decimal decimal_check = {{0xD40B56FE, 0x88531CB2, 0x96648B40, 0x80080000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok987) {
    // 2992553232.8473012093242990234
    s21_decimal decimal = {{0x41D65E9A, 0x2A70ACE4, 0x60B1D1F6, 0x130000}};
    // -2992553232.8473012093242990234
    s21_decimal decimal_check = {{0x41D65E9A, 0x2A70ACE4, 0x60B1D1F6, 0x80130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok988) {
    // -2992553232.8473012093242990234
    s21_decimal decimal = {{0x41D65E9A, 0x2A70ACE4, 0x60B1D1F6, 0x80130000}};
    // 2992553232.8473012093242990234
    s21_decimal decimal_check = {{0x41D65E9A, 0x2A70ACE4, 0x60B1D1F6, 0x130000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok989) {
    // -3016389385188214739.2787710551
    s21_decimal decimal = {{0xFB320257, 0x3DDC0940, 0x6176FCFA, 0x800A0000}};
    // 3016389385188214739.2787710551
    s21_decimal decimal_check = {{0xFB320257, 0x3DDC0940, 0x6176FCFA, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok990) {
    // 3016389385188214739.2787710551
    s21_decimal decimal = {{0xFB320257, 0x3DDC0940, 0x6176FCFA, 0xA0000}};
    // -3016389385188214739.2787710551
    s21_decimal decimal_check = {{0xFB320257, 0x3DDC0940, 0x6176FCFA, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok991) {
    // 33815043.65286234113249073658
    s21_decimal decimal = {{0x1C6359FA, 0xF4A4027C, 0xAED1D66, 0x140000}};
    // -33815043.65286234113249073658
    s21_decimal decimal_check = {{0x1C6359FA, 0xF4A4027C, 0xAED1D66, 0x80140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok992) {
    // -33815043.65286234113249073658
    s21_decimal decimal = {{0x1C6359FA, 0xF4A4027C, 0xAED1D66, 0x80140000}};
    // 33815043.65286234113249073658
    s21_decimal decimal_check = {{0x1C6359FA, 0xF4A4027C, 0xAED1D66, 0x140000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok993) {
    // -655398781067771.83794689059460
    s21_decimal decimal = {{0xE2C9AA84, 0x63E0C758, 0xD3C55107, 0x800E0000}};
    // 655398781067771.83794689059460
    s21_decimal decimal_check = {{0xE2C9AA84, 0x63E0C758, 0xD3C55107, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok994) {
    // 655398781067771.83794689059460
    s21_decimal decimal = {{0xE2C9AA84, 0x63E0C758, 0xD3C55107, 0xE0000}};
    // -655398781067771.83794689059460
    s21_decimal decimal_check = {{0xE2C9AA84, 0x63E0C758, 0xD3C55107, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok995) {
    // 1893515916082631238.3416469102
    s21_decimal decimal = {{0x51EB866E, 0xED244119, 0x3D2ECBEA, 0xA0000}};
    // -1893515916082631238.3416469102
    s21_decimal decimal_check = {{0x51EB866E, 0xED244119, 0x3D2ECBEA, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok996) {
    // -1893515916082631238.3416469102
    s21_decimal decimal = {{0x51EB866E, 0xED244119, 0x3D2ECBEA, 0x800A0000}};
    // 1893515916082631238.3416469102
    s21_decimal decimal_check = {{0x51EB866E, 0xED244119, 0x3D2ECBEA, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok997) {
    // -50688490238048905980647854344
    s21_decimal decimal = {{0xB1205108, 0xCE1E0202, 0xA3C88951, 0x80000000}};
    // 50688490238048905980647854344
    s21_decimal decimal_check = {{0xB1205108, 0xCE1E0202, 0xA3C88951, 0x0}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok998) {
    // 50688490238048905980647854344
    s21_decimal decimal = {{0xB1205108, 0xCE1E0202, 0xA3C88951, 0x0}};
    // -50688490238048905980647854344
    s21_decimal decimal_check = {{0xB1205108, 0xCE1E0202, 0xA3C88951, 0x80000000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok999) {
    // -5694011593981989243301.7721765
    s21_decimal decimal = {{0xD1B953A5, 0x2D2C928A, 0xB7FBC28E, 0x80070000}};
    // 5694011593981989243301.7721765
    s21_decimal decimal_check = {{0xD1B953A5, 0x2D2C928A, 0xB7FBC28E, 0x70000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1000) {
    // 5694011593981989243301.7721765
    s21_decimal decimal = {{0xD1B953A5, 0x2D2C928A, 0xB7FBC28E, 0x70000}};
    // -5694011593981989243301.7721765
    s21_decimal decimal_check = {{0xD1B953A5, 0x2D2C928A, 0xB7FBC28E, 0x80070000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1001) {
    // 7391817384113353885252676556.8
    s21_decimal decimal = {{0xD4363600, 0x3C647D46, 0xEED7AE29, 0x10000}};
    // -7391817384113353885252676556.8
    s21_decimal decimal_check = {{0xD4363600, 0x3C647D46, 0xEED7AE29, 0x80010000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1002) {
    // -7391817384113353885252676556.8
    s21_decimal decimal = {{0xD4363600, 0x3C647D46, 0xEED7AE29, 0x80010000}};
    // 7391817384113353885252676556.8
    s21_decimal decimal_check = {{0xD4363600, 0x3C647D46, 0xEED7AE29, 0x10000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1003) {
    // 67381264773976866357.851509099
    s21_decimal decimal = {{0x37B8D16B, 0xA369F4E6, 0xD9B879D2, 0x90000}};
    // -67381264773976866357.851509099
    s21_decimal decimal_check = {{0x37B8D16B, 0xA369F4E6, 0xD9B879D2, 0x80090000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1004) {
    // -67381264773976866357.851509099
    s21_decimal decimal = {{0x37B8D16B, 0xA369F4E6, 0xD9B879D2, 0x80090000}};
    // 67381264773976866357.851509099
    s21_decimal decimal_check = {{0x37B8D16B, 0xA369F4E6, 0xD9B879D2, 0x90000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1005) {
    // 3880207503319540203.1112505076
    s21_decimal decimal = {{0x4B9DC6F4, 0x6594B4BA, 0x7D6052FE, 0xA0000}};
    // -3880207503319540203.1112505076
    s21_decimal decimal_check = {{0x4B9DC6F4, 0x6594B4BA, 0x7D6052FE, 0x800A0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1006) {
    // -3880207503319540203.1112505076
    s21_decimal decimal = {{0x4B9DC6F4, 0x6594B4BA, 0x7D6052FE, 0x800A0000}};
    // 3880207503319540203.1112505076
    s21_decimal decimal_check = {{0x4B9DC6F4, 0x6594B4BA, 0x7D6052FE, 0xA0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1007) {
    // -52231370183613270.792051465171
    s21_decimal decimal = {{0x12159BD3, 0x3F977FBD, 0xA8C4C6DB, 0x800C0000}};
    // 52231370183613270.792051465171
    s21_decimal decimal_check = {{0x12159BD3, 0x3F977FBD, 0xA8C4C6DB, 0xC0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1008) {
    // 52231370183613270.792051465171
    s21_decimal decimal = {{0x12159BD3, 0x3F977FBD, 0xA8C4C6DB, 0xC0000}};
    // -52231370183613270.792051465171
    s21_decimal decimal_check = {{0x12159BD3, 0x3F977FBD, 0xA8C4C6DB, 0x800C0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1009) {
    // 762012.47518574196197311629136
    s21_decimal decimal = {{0xFDDBC750, 0x4985467C, 0xF63831D1, 0x170000}};
    // -762012.47518574196197311629136
    s21_decimal decimal_check = {{0xFDDBC750, 0x4985467C, 0xF63831D1, 0x80170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1010) {
    // -762012.47518574196197311629136
    s21_decimal decimal = {{0xFDDBC750, 0x4985467C, 0xF63831D1, 0x80170000}};
    // 762012.47518574196197311629136
    s21_decimal decimal_check = {{0xFDDBC750, 0x4985467C, 0xF63831D1, 0x170000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1011) {
    // 528160336985692.03305796312337
    s21_decimal decimal = {{0x783F9D11, 0xE71F058C, 0xAAA8662B, 0xE0000}};
    // -528160336985692.03305796312337
    s21_decimal decimal_check = {{0x783F9D11, 0xE71F058C, 0xAAA8662B, 0x800E0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1012) {
    // -528160336985692.03305796312337
    s21_decimal decimal = {{0x783F9D11, 0xE71F058C, 0xAAA8662B, 0x800E0000}};
    // 528160336985692.03305796312337
    s21_decimal decimal_check = {{0x783F9D11, 0xE71F058C, 0xAAA8662B, 0xE0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1013) {
    // 53331962353.888666415154074761
    s21_decimal decimal = {{0x8381489, 0x599DA089, 0xAC532A50, 0x120000}};
    // -53331962353.888666415154074761
    s21_decimal decimal_check = {{0x8381489, 0x599DA089, 0xAC532A50, 0x80120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1014) {
    // -53331962353.888666415154074761
    s21_decimal decimal = {{0x8381489, 0x599DA089, 0xAC532A50, 0x80120000}};
    // 53331962353.888666415154074761
    s21_decimal decimal_check = {{0x8381489, 0x599DA089, 0xAC532A50, 0x120000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1015) {
    // 21469522554935341566486.374228
    s21_decimal decimal = {{0x23BBE754, 0xD07AAACA, 0x455F2C3D, 0x60000}};
    // -21469522554935341566486.374228
    s21_decimal decimal_check = {{0x23BBE754, 0xD07AAACA, 0x455F2C3D, 0x80060000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1016) {
    // -21469522554935341566486.374228
    s21_decimal decimal = {{0x23BBE754, 0xD07AAACA, 0x455F2C3D, 0x80060000}};
    // 21469522554935341566486.374228
    s21_decimal decimal_check = {{0x23BBE754, 0xD07AAACA, 0x455F2C3D, 0x60000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1017) {
    // -48282841899130.570326498609779
    s21_decimal decimal = {{0x32F40A73, 0xA632221, 0x9C02A178, 0x800F0000}};
    // 48282841899130.570326498609779
    s21_decimal decimal_check = {{0x32F40A73, 0xA632221, 0x9C02A178, 0xF0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1018) {
    // 48282841899130.570326498609779
    s21_decimal decimal = {{0x32F40A73, 0xA632221, 0x9C02A178, 0xF0000}};
    // -48282841899130.570326498609779
    s21_decimal decimal_check = {{0x32F40A73, 0xA632221, 0x9C02A178, 0x800F0000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1019) {
    // -743355137752.71190832768620564
    s21_decimal decimal = {{0xC2E01814, 0x66150693, 0xF030E554, 0x80110000}};
    // 743355137752.71190832768620564
    s21_decimal decimal_check = {{0xC2E01814, 0x66150693, 0xF030E554, 0x110000}};

    test_negate(decimal, decimal_check);
}

START_TEST(test_negate_ok1020) {
    // 743355137752.71190832768620564
    s21_decimal decimal = {{0xC2E01814, 0x66150693, 0xF030E554, 0x110000}};
    // -743355137752.71190832768620564
    s21_decimal decimal_check = {{0xC2E01814, 0x66150693, 0xF030E554, 0x80110000}};

    test_negate(decimal, decimal_check);
}


Suite *negate_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("negate_suite1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_negate_ok1);
    tcase_add_test(tc_core, test_negate_ok2);
    tcase_add_test(tc_core, test_negate_ok3);
    tcase_add_test(tc_core, test_negate_ok4);
    tcase_add_test(tc_core, test_negate_ok5);
    tcase_add_test(tc_core, test_negate_ok6);
    tcase_add_test(tc_core, test_negate_ok7);
    tcase_add_test(tc_core, test_negate_ok8);
    tcase_add_test(tc_core, test_negate_ok9);
    tcase_add_test(tc_core, test_negate_ok10);
    tcase_add_test(tc_core, test_negate_ok11);
    tcase_add_test(tc_core, test_negate_ok12);
    tcase_add_test(tc_core, test_negate_ok13);
    tcase_add_test(tc_core, test_negate_ok14);
    tcase_add_test(tc_core, test_negate_ok15);
    tcase_add_test(tc_core, test_negate_ok16);
    tcase_add_test(tc_core, test_negate_ok17);
    tcase_add_test(tc_core, test_negate_ok18);
    tcase_add_test(tc_core, test_negate_ok19);
    tcase_add_test(tc_core, test_negate_ok20);
    tcase_add_test(tc_core, test_negate_ok21);
    tcase_add_test(tc_core, test_negate_ok22);
    tcase_add_test(tc_core, test_negate_ok23);
    tcase_add_test(tc_core, test_negate_ok24);
    tcase_add_test(tc_core, test_negate_ok25);
    tcase_add_test(tc_core, test_negate_ok26);
    tcase_add_test(tc_core, test_negate_ok27);
    tcase_add_test(tc_core, test_negate_ok28);
    tcase_add_test(tc_core, test_negate_ok29);
    tcase_add_test(tc_core, test_negate_ok30);
    tcase_add_test(tc_core, test_negate_ok31);
    tcase_add_test(tc_core, test_negate_ok32);
    tcase_add_test(tc_core, test_negate_ok33);
    tcase_add_test(tc_core, test_negate_ok34);
    tcase_add_test(tc_core, test_negate_ok35);
    tcase_add_test(tc_core, test_negate_ok36);
    tcase_add_test(tc_core, test_negate_ok37);
    tcase_add_test(tc_core, test_negate_ok38);
    tcase_add_test(tc_core, test_negate_ok39);
    tcase_add_test(tc_core, test_negate_ok40);
    tcase_add_test(tc_core, test_negate_ok41);
    tcase_add_test(tc_core, test_negate_ok42);
    tcase_add_test(tc_core, test_negate_ok43);
    tcase_add_test(tc_core, test_negate_ok44);
    tcase_add_test(tc_core, test_negate_ok45);
    tcase_add_test(tc_core, test_negate_ok46);
    tcase_add_test(tc_core, test_negate_ok47);
    tcase_add_test(tc_core, test_negate_ok48);
    tcase_add_test(tc_core, test_negate_ok49);
    tcase_add_test(tc_core, test_negate_ok50);
    tcase_add_test(tc_core, test_negate_ok51);
    tcase_add_test(tc_core, test_negate_ok52);
    tcase_add_test(tc_core, test_negate_ok53);
    tcase_add_test(tc_core, test_negate_ok54);
    tcase_add_test(tc_core, test_negate_ok55);
    tcase_add_test(tc_core, test_negate_ok56);
    tcase_add_test(tc_core, test_negate_ok57);
    tcase_add_test(tc_core, test_negate_ok58);
    tcase_add_test(tc_core, test_negate_ok59);
    tcase_add_test(tc_core, test_negate_ok60);
    tcase_add_test(tc_core, test_negate_ok61);
    tcase_add_test(tc_core, test_negate_ok62);
    tcase_add_test(tc_core, test_negate_ok63);
    tcase_add_test(tc_core, test_negate_ok64);
    tcase_add_test(tc_core, test_negate_ok65);
    tcase_add_test(tc_core, test_negate_ok66);
    tcase_add_test(tc_core, test_negate_ok67);
    tcase_add_test(tc_core, test_negate_ok68);
    tcase_add_test(tc_core, test_negate_ok69);
    tcase_add_test(tc_core, test_negate_ok70);
    tcase_add_test(tc_core, test_negate_ok71);
    tcase_add_test(tc_core, test_negate_ok72);
    tcase_add_test(tc_core, test_negate_ok73);
    tcase_add_test(tc_core, test_negate_ok74);
    tcase_add_test(tc_core, test_negate_ok75);
    tcase_add_test(tc_core, test_negate_ok76);
    tcase_add_test(tc_core, test_negate_ok77);
    tcase_add_test(tc_core, test_negate_ok78);
    tcase_add_test(tc_core, test_negate_ok79);
    tcase_add_test(tc_core, test_negate_ok80);
    tcase_add_test(tc_core, test_negate_ok81);
    tcase_add_test(tc_core, test_negate_ok82);
    tcase_add_test(tc_core, test_negate_ok83);
    tcase_add_test(tc_core, test_negate_ok84);
    tcase_add_test(tc_core, test_negate_ok85);
    tcase_add_test(tc_core, test_negate_ok86);
    tcase_add_test(tc_core, test_negate_ok87);
    tcase_add_test(tc_core, test_negate_ok88);
    tcase_add_test(tc_core, test_negate_ok89);
    tcase_add_test(tc_core, test_negate_ok90);
    tcase_add_test(tc_core, test_negate_ok91);
    tcase_add_test(tc_core, test_negate_ok92);
    tcase_add_test(tc_core, test_negate_ok93);
    tcase_add_test(tc_core, test_negate_ok94);
    tcase_add_test(tc_core, test_negate_ok95);
    tcase_add_test(tc_core, test_negate_ok96);
    tcase_add_test(tc_core, test_negate_ok97);
    tcase_add_test(tc_core, test_negate_ok98);
    tcase_add_test(tc_core, test_negate_ok99);
    tcase_add_test(tc_core, test_negate_ok100);
    tcase_add_test(tc_core, test_negate_ok101);
    tcase_add_test(tc_core, test_negate_ok102);
    tcase_add_test(tc_core, test_negate_ok103);
    tcase_add_test(tc_core, test_negate_ok104);
    tcase_add_test(tc_core, test_negate_ok105);
    tcase_add_test(tc_core, test_negate_ok106);
    tcase_add_test(tc_core, test_negate_ok107);
    tcase_add_test(tc_core, test_negate_ok108);
    tcase_add_test(tc_core, test_negate_ok109);
    tcase_add_test(tc_core, test_negate_ok110);
    tcase_add_test(tc_core, test_negate_ok111);
    tcase_add_test(tc_core, test_negate_ok112);
    tcase_add_test(tc_core, test_negate_ok113);
    tcase_add_test(tc_core, test_negate_ok114);
    tcase_add_test(tc_core, test_negate_ok115);
    tcase_add_test(tc_core, test_negate_ok116);
    tcase_add_test(tc_core, test_negate_ok117);
    tcase_add_test(tc_core, test_negate_ok118);
    tcase_add_test(tc_core, test_negate_ok119);
    tcase_add_test(tc_core, test_negate_ok120);
    tcase_add_test(tc_core, test_negate_ok121);
    tcase_add_test(tc_core, test_negate_ok122);
    tcase_add_test(tc_core, test_negate_ok123);
    tcase_add_test(tc_core, test_negate_ok124);
    tcase_add_test(tc_core, test_negate_ok125);
    tcase_add_test(tc_core, test_negate_ok126);
    tcase_add_test(tc_core, test_negate_ok127);
    tcase_add_test(tc_core, test_negate_ok128);
    tcase_add_test(tc_core, test_negate_ok129);
    tcase_add_test(tc_core, test_negate_ok130);
    tcase_add_test(tc_core, test_negate_ok131);
    tcase_add_test(tc_core, test_negate_ok132);
    tcase_add_test(tc_core, test_negate_ok133);
    tcase_add_test(tc_core, test_negate_ok134);
    tcase_add_test(tc_core, test_negate_ok135);
    tcase_add_test(tc_core, test_negate_ok136);
    tcase_add_test(tc_core, test_negate_ok137);
    tcase_add_test(tc_core, test_negate_ok138);
    tcase_add_test(tc_core, test_negate_ok139);
    tcase_add_test(tc_core, test_negate_ok140);
    tcase_add_test(tc_core, test_negate_ok141);
    tcase_add_test(tc_core, test_negate_ok142);
    tcase_add_test(tc_core, test_negate_ok143);
    tcase_add_test(tc_core, test_negate_ok144);
    tcase_add_test(tc_core, test_negate_ok145);
    tcase_add_test(tc_core, test_negate_ok146);
    tcase_add_test(tc_core, test_negate_ok147);
    tcase_add_test(tc_core, test_negate_ok148);
    tcase_add_test(tc_core, test_negate_ok149);
    tcase_add_test(tc_core, test_negate_ok150);
    tcase_add_test(tc_core, test_negate_ok151);
    tcase_add_test(tc_core, test_negate_ok152);
    tcase_add_test(tc_core, test_negate_ok153);
    tcase_add_test(tc_core, test_negate_ok154);
    tcase_add_test(tc_core, test_negate_ok155);
    tcase_add_test(tc_core, test_negate_ok156);
    tcase_add_test(tc_core, test_negate_ok157);
    tcase_add_test(tc_core, test_negate_ok158);
    tcase_add_test(tc_core, test_negate_ok159);
    tcase_add_test(tc_core, test_negate_ok160);
    tcase_add_test(tc_core, test_negate_ok161);
    tcase_add_test(tc_core, test_negate_ok162);
    tcase_add_test(tc_core, test_negate_ok163);
    tcase_add_test(tc_core, test_negate_ok164);
    tcase_add_test(tc_core, test_negate_ok165);
    tcase_add_test(tc_core, test_negate_ok166);
    tcase_add_test(tc_core, test_negate_ok167);
    tcase_add_test(tc_core, test_negate_ok168);
    tcase_add_test(tc_core, test_negate_ok169);
    tcase_add_test(tc_core, test_negate_ok170);
    tcase_add_test(tc_core, test_negate_ok171);
    tcase_add_test(tc_core, test_negate_ok172);
    tcase_add_test(tc_core, test_negate_ok173);
    tcase_add_test(tc_core, test_negate_ok174);
    tcase_add_test(tc_core, test_negate_ok175);
    tcase_add_test(tc_core, test_negate_ok176);
    tcase_add_test(tc_core, test_negate_ok177);
    tcase_add_test(tc_core, test_negate_ok178);
    tcase_add_test(tc_core, test_negate_ok179);
    tcase_add_test(tc_core, test_negate_ok180);
    tcase_add_test(tc_core, test_negate_ok181);
    tcase_add_test(tc_core, test_negate_ok182);
    tcase_add_test(tc_core, test_negate_ok183);
    tcase_add_test(tc_core, test_negate_ok184);
    tcase_add_test(tc_core, test_negate_ok185);
    tcase_add_test(tc_core, test_negate_ok186);
    tcase_add_test(tc_core, test_negate_ok187);
    tcase_add_test(tc_core, test_negate_ok188);
    tcase_add_test(tc_core, test_negate_ok189);
    tcase_add_test(tc_core, test_negate_ok190);
    tcase_add_test(tc_core, test_negate_ok191);
    tcase_add_test(tc_core, test_negate_ok192);
    tcase_add_test(tc_core, test_negate_ok193);
    tcase_add_test(tc_core, test_negate_ok194);
    tcase_add_test(tc_core, test_negate_ok195);
    tcase_add_test(tc_core, test_negate_ok196);
    tcase_add_test(tc_core, test_negate_ok197);
    tcase_add_test(tc_core, test_negate_ok198);
    tcase_add_test(tc_core, test_negate_ok199);
    tcase_add_test(tc_core, test_negate_ok200);
    tcase_add_test(tc_core, test_negate_ok201);
    tcase_add_test(tc_core, test_negate_ok202);
    tcase_add_test(tc_core, test_negate_ok203);
    tcase_add_test(tc_core, test_negate_ok204);
    tcase_add_test(tc_core, test_negate_ok205);
    tcase_add_test(tc_core, test_negate_ok206);
    tcase_add_test(tc_core, test_negate_ok207);
    tcase_add_test(tc_core, test_negate_ok208);
    tcase_add_test(tc_core, test_negate_ok209);
    tcase_add_test(tc_core, test_negate_ok210);
    tcase_add_test(tc_core, test_negate_ok211);
    tcase_add_test(tc_core, test_negate_ok212);
    tcase_add_test(tc_core, test_negate_ok213);
    tcase_add_test(tc_core, test_negate_ok214);
    tcase_add_test(tc_core, test_negate_ok215);
    tcase_add_test(tc_core, test_negate_ok216);
    tcase_add_test(tc_core, test_negate_ok217);
    tcase_add_test(tc_core, test_negate_ok218);
    tcase_add_test(tc_core, test_negate_ok219);
    tcase_add_test(tc_core, test_negate_ok220);
    tcase_add_test(tc_core, test_negate_ok221);
    tcase_add_test(tc_core, test_negate_ok222);
    tcase_add_test(tc_core, test_negate_ok223);
    tcase_add_test(tc_core, test_negate_ok224);
    tcase_add_test(tc_core, test_negate_ok225);
    tcase_add_test(tc_core, test_negate_ok226);
    tcase_add_test(tc_core, test_negate_ok227);
    tcase_add_test(tc_core, test_negate_ok228);
    tcase_add_test(tc_core, test_negate_ok229);
    tcase_add_test(tc_core, test_negate_ok230);
    tcase_add_test(tc_core, test_negate_ok231);
    tcase_add_test(tc_core, test_negate_ok232);
    tcase_add_test(tc_core, test_negate_ok233);
    tcase_add_test(tc_core, test_negate_ok234);
    tcase_add_test(tc_core, test_negate_ok235);
    tcase_add_test(tc_core, test_negate_ok236);
    tcase_add_test(tc_core, test_negate_ok237);
    tcase_add_test(tc_core, test_negate_ok238);
    tcase_add_test(tc_core, test_negate_ok239);
    tcase_add_test(tc_core, test_negate_ok240);
    tcase_add_test(tc_core, test_negate_ok241);
    tcase_add_test(tc_core, test_negate_ok242);
    tcase_add_test(tc_core, test_negate_ok243);
    tcase_add_test(tc_core, test_negate_ok244);
    tcase_add_test(tc_core, test_negate_ok245);
    tcase_add_test(tc_core, test_negate_ok246);
    tcase_add_test(tc_core, test_negate_ok247);
    tcase_add_test(tc_core, test_negate_ok248);
    tcase_add_test(tc_core, test_negate_ok249);
    tcase_add_test(tc_core, test_negate_ok250);
    tcase_add_test(tc_core, test_negate_ok251);
    tcase_add_test(tc_core, test_negate_ok252);
    tcase_add_test(tc_core, test_negate_ok253);
    tcase_add_test(tc_core, test_negate_ok254);
    tcase_add_test(tc_core, test_negate_ok255);
    tcase_add_test(tc_core, test_negate_ok256);
    tcase_add_test(tc_core, test_negate_ok257);
    tcase_add_test(tc_core, test_negate_ok258);
    tcase_add_test(tc_core, test_negate_ok259);
    tcase_add_test(tc_core, test_negate_ok260);
    tcase_add_test(tc_core, test_negate_ok261);
    tcase_add_test(tc_core, test_negate_ok262);
    tcase_add_test(tc_core, test_negate_ok263);
    tcase_add_test(tc_core, test_negate_ok264);
    tcase_add_test(tc_core, test_negate_ok265);
    tcase_add_test(tc_core, test_negate_ok266);
    tcase_add_test(tc_core, test_negate_ok267);
    tcase_add_test(tc_core, test_negate_ok268);
    tcase_add_test(tc_core, test_negate_ok269);
    tcase_add_test(tc_core, test_negate_ok270);
    tcase_add_test(tc_core, test_negate_ok271);
    tcase_add_test(tc_core, test_negate_ok272);
    tcase_add_test(tc_core, test_negate_ok273);
    tcase_add_test(tc_core, test_negate_ok274);
    tcase_add_test(tc_core, test_negate_ok275);
    tcase_add_test(tc_core, test_negate_ok276);
    tcase_add_test(tc_core, test_negate_ok277);
    tcase_add_test(tc_core, test_negate_ok278);
    tcase_add_test(tc_core, test_negate_ok279);
    tcase_add_test(tc_core, test_negate_ok280);
    tcase_add_test(tc_core, test_negate_ok281);
    tcase_add_test(tc_core, test_negate_ok282);
    tcase_add_test(tc_core, test_negate_ok283);
    tcase_add_test(tc_core, test_negate_ok284);
    tcase_add_test(tc_core, test_negate_ok285);
    tcase_add_test(tc_core, test_negate_ok286);
    tcase_add_test(tc_core, test_negate_ok287);
    tcase_add_test(tc_core, test_negate_ok288);
    tcase_add_test(tc_core, test_negate_ok289);
    tcase_add_test(tc_core, test_negate_ok290);
    tcase_add_test(tc_core, test_negate_ok291);
    tcase_add_test(tc_core, test_negate_ok292);
    tcase_add_test(tc_core, test_negate_ok293);
    tcase_add_test(tc_core, test_negate_ok294);
    tcase_add_test(tc_core, test_negate_ok295);
    tcase_add_test(tc_core, test_negate_ok296);
    tcase_add_test(tc_core, test_negate_ok297);
    tcase_add_test(tc_core, test_negate_ok298);
    tcase_add_test(tc_core, test_negate_ok299);
    tcase_add_test(tc_core, test_negate_ok300);
    tcase_add_test(tc_core, test_negate_ok301);
    tcase_add_test(tc_core, test_negate_ok302);
    tcase_add_test(tc_core, test_negate_ok303);
    tcase_add_test(tc_core, test_negate_ok304);
    tcase_add_test(tc_core, test_negate_ok305);
    tcase_add_test(tc_core, test_negate_ok306);
    tcase_add_test(tc_core, test_negate_ok307);
    tcase_add_test(tc_core, test_negate_ok308);
    tcase_add_test(tc_core, test_negate_ok309);
    tcase_add_test(tc_core, test_negate_ok310);
    tcase_add_test(tc_core, test_negate_ok311);
    tcase_add_test(tc_core, test_negate_ok312);
    tcase_add_test(tc_core, test_negate_ok313);
    tcase_add_test(tc_core, test_negate_ok314);
    tcase_add_test(tc_core, test_negate_ok315);
    tcase_add_test(tc_core, test_negate_ok316);
    tcase_add_test(tc_core, test_negate_ok317);
    tcase_add_test(tc_core, test_negate_ok318);
    tcase_add_test(tc_core, test_negate_ok319);
    tcase_add_test(tc_core, test_negate_ok320);
    tcase_add_test(tc_core, test_negate_ok321);
    tcase_add_test(tc_core, test_negate_ok322);
    tcase_add_test(tc_core, test_negate_ok323);
    tcase_add_test(tc_core, test_negate_ok324);
    tcase_add_test(tc_core, test_negate_ok325);
    tcase_add_test(tc_core, test_negate_ok326);
    tcase_add_test(tc_core, test_negate_ok327);
    tcase_add_test(tc_core, test_negate_ok328);
    tcase_add_test(tc_core, test_negate_ok329);
    tcase_add_test(tc_core, test_negate_ok330);
    tcase_add_test(tc_core, test_negate_ok331);
    tcase_add_test(tc_core, test_negate_ok332);
    tcase_add_test(tc_core, test_negate_ok333);
    tcase_add_test(tc_core, test_negate_ok334);
    tcase_add_test(tc_core, test_negate_ok335);
    tcase_add_test(tc_core, test_negate_ok336);
    tcase_add_test(tc_core, test_negate_ok337);
    tcase_add_test(tc_core, test_negate_ok338);
    tcase_add_test(tc_core, test_negate_ok339);
    tcase_add_test(tc_core, test_negate_ok340);
    tcase_add_test(tc_core, test_negate_ok341);
    tcase_add_test(tc_core, test_negate_ok342);
    tcase_add_test(tc_core, test_negate_ok343);
    tcase_add_test(tc_core, test_negate_ok344);
    tcase_add_test(tc_core, test_negate_ok345);
    tcase_add_test(tc_core, test_negate_ok346);
    tcase_add_test(tc_core, test_negate_ok347);
    tcase_add_test(tc_core, test_negate_ok348);
    tcase_add_test(tc_core, test_negate_ok349);
    tcase_add_test(tc_core, test_negate_ok350);
    tcase_add_test(tc_core, test_negate_ok351);
    tcase_add_test(tc_core, test_negate_ok352);
    tcase_add_test(tc_core, test_negate_ok353);
    tcase_add_test(tc_core, test_negate_ok354);
    tcase_add_test(tc_core, test_negate_ok355);
    tcase_add_test(tc_core, test_negate_ok356);
    tcase_add_test(tc_core, test_negate_ok357);
    tcase_add_test(tc_core, test_negate_ok358);
    tcase_add_test(tc_core, test_negate_ok359);
    tcase_add_test(tc_core, test_negate_ok360);
    tcase_add_test(tc_core, test_negate_ok361);
    tcase_add_test(tc_core, test_negate_ok362);
    tcase_add_test(tc_core, test_negate_ok363);
    tcase_add_test(tc_core, test_negate_ok364);
    tcase_add_test(tc_core, test_negate_ok365);
    tcase_add_test(tc_core, test_negate_ok366);
    tcase_add_test(tc_core, test_negate_ok367);
    tcase_add_test(tc_core, test_negate_ok368);
    tcase_add_test(tc_core, test_negate_ok369);
    tcase_add_test(tc_core, test_negate_ok370);
    tcase_add_test(tc_core, test_negate_ok371);
    tcase_add_test(tc_core, test_negate_ok372);
    tcase_add_test(tc_core, test_negate_ok373);
    tcase_add_test(tc_core, test_negate_ok374);
    tcase_add_test(tc_core, test_negate_ok375);
    tcase_add_test(tc_core, test_negate_ok376);
    tcase_add_test(tc_core, test_negate_ok377);
    tcase_add_test(tc_core, test_negate_ok378);
    tcase_add_test(tc_core, test_negate_ok379);
    tcase_add_test(tc_core, test_negate_ok380);
    tcase_add_test(tc_core, test_negate_ok381);
    tcase_add_test(tc_core, test_negate_ok382);
    tcase_add_test(tc_core, test_negate_ok383);
    tcase_add_test(tc_core, test_negate_ok384);
    tcase_add_test(tc_core, test_negate_ok385);
    tcase_add_test(tc_core, test_negate_ok386);
    tcase_add_test(tc_core, test_negate_ok387);
    tcase_add_test(tc_core, test_negate_ok388);
    tcase_add_test(tc_core, test_negate_ok389);
    tcase_add_test(tc_core, test_negate_ok390);
    tcase_add_test(tc_core, test_negate_ok391);
    tcase_add_test(tc_core, test_negate_ok392);
    tcase_add_test(tc_core, test_negate_ok393);
    tcase_add_test(tc_core, test_negate_ok394);
    tcase_add_test(tc_core, test_negate_ok395);
    tcase_add_test(tc_core, test_negate_ok396);
    tcase_add_test(tc_core, test_negate_ok397);
    tcase_add_test(tc_core, test_negate_ok398);
    tcase_add_test(tc_core, test_negate_ok399);
    tcase_add_test(tc_core, test_negate_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *negate_suite2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("negate_suite2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_negate_ok401);
    tcase_add_test(tc_core, test_negate_ok402);
    tcase_add_test(tc_core, test_negate_ok403);
    tcase_add_test(tc_core, test_negate_ok404);
    tcase_add_test(tc_core, test_negate_ok405);
    tcase_add_test(tc_core, test_negate_ok406);
    tcase_add_test(tc_core, test_negate_ok407);
    tcase_add_test(tc_core, test_negate_ok408);
    tcase_add_test(tc_core, test_negate_ok409);
    tcase_add_test(tc_core, test_negate_ok410);
    tcase_add_test(tc_core, test_negate_ok411);
    tcase_add_test(tc_core, test_negate_ok412);
    tcase_add_test(tc_core, test_negate_ok413);
    tcase_add_test(tc_core, test_negate_ok414);
    tcase_add_test(tc_core, test_negate_ok415);
    tcase_add_test(tc_core, test_negate_ok416);
    tcase_add_test(tc_core, test_negate_ok417);
    tcase_add_test(tc_core, test_negate_ok418);
    tcase_add_test(tc_core, test_negate_ok419);
    tcase_add_test(tc_core, test_negate_ok420);
    tcase_add_test(tc_core, test_negate_ok421);
    tcase_add_test(tc_core, test_negate_ok422);
    tcase_add_test(tc_core, test_negate_ok423);
    tcase_add_test(tc_core, test_negate_ok424);
    tcase_add_test(tc_core, test_negate_ok425);
    tcase_add_test(tc_core, test_negate_ok426);
    tcase_add_test(tc_core, test_negate_ok427);
    tcase_add_test(tc_core, test_negate_ok428);
    tcase_add_test(tc_core, test_negate_ok429);
    tcase_add_test(tc_core, test_negate_ok430);
    tcase_add_test(tc_core, test_negate_ok431);
    tcase_add_test(tc_core, test_negate_ok432);
    tcase_add_test(tc_core, test_negate_ok433);
    tcase_add_test(tc_core, test_negate_ok434);
    tcase_add_test(tc_core, test_negate_ok435);
    tcase_add_test(tc_core, test_negate_ok436);
    tcase_add_test(tc_core, test_negate_ok437);
    tcase_add_test(tc_core, test_negate_ok438);
    tcase_add_test(tc_core, test_negate_ok439);
    tcase_add_test(tc_core, test_negate_ok440);
    tcase_add_test(tc_core, test_negate_ok441);
    tcase_add_test(tc_core, test_negate_ok442);
    tcase_add_test(tc_core, test_negate_ok443);
    tcase_add_test(tc_core, test_negate_ok444);
    tcase_add_test(tc_core, test_negate_ok445);
    tcase_add_test(tc_core, test_negate_ok446);
    tcase_add_test(tc_core, test_negate_ok447);
    tcase_add_test(tc_core, test_negate_ok448);
    tcase_add_test(tc_core, test_negate_ok449);
    tcase_add_test(tc_core, test_negate_ok450);
    tcase_add_test(tc_core, test_negate_ok451);
    tcase_add_test(tc_core, test_negate_ok452);
    tcase_add_test(tc_core, test_negate_ok453);
    tcase_add_test(tc_core, test_negate_ok454);
    tcase_add_test(tc_core, test_negate_ok455);
    tcase_add_test(tc_core, test_negate_ok456);
    tcase_add_test(tc_core, test_negate_ok457);
    tcase_add_test(tc_core, test_negate_ok458);
    tcase_add_test(tc_core, test_negate_ok459);
    tcase_add_test(tc_core, test_negate_ok460);
    tcase_add_test(tc_core, test_negate_ok461);
    tcase_add_test(tc_core, test_negate_ok462);
    tcase_add_test(tc_core, test_negate_ok463);
    tcase_add_test(tc_core, test_negate_ok464);
    tcase_add_test(tc_core, test_negate_ok465);
    tcase_add_test(tc_core, test_negate_ok466);
    tcase_add_test(tc_core, test_negate_ok467);
    tcase_add_test(tc_core, test_negate_ok468);
    tcase_add_test(tc_core, test_negate_ok469);
    tcase_add_test(tc_core, test_negate_ok470);
    tcase_add_test(tc_core, test_negate_ok471);
    tcase_add_test(tc_core, test_negate_ok472);
    tcase_add_test(tc_core, test_negate_ok473);
    tcase_add_test(tc_core, test_negate_ok474);
    tcase_add_test(tc_core, test_negate_ok475);
    tcase_add_test(tc_core, test_negate_ok476);
    tcase_add_test(tc_core, test_negate_ok477);
    tcase_add_test(tc_core, test_negate_ok478);
    tcase_add_test(tc_core, test_negate_ok479);
    tcase_add_test(tc_core, test_negate_ok480);
    tcase_add_test(tc_core, test_negate_ok481);
    tcase_add_test(tc_core, test_negate_ok482);
    tcase_add_test(tc_core, test_negate_ok483);
    tcase_add_test(tc_core, test_negate_ok484);
    tcase_add_test(tc_core, test_negate_ok485);
    tcase_add_test(tc_core, test_negate_ok486);
    tcase_add_test(tc_core, test_negate_ok487);
    tcase_add_test(tc_core, test_negate_ok488);
    tcase_add_test(tc_core, test_negate_ok489);
    tcase_add_test(tc_core, test_negate_ok490);
    tcase_add_test(tc_core, test_negate_ok491);
    tcase_add_test(tc_core, test_negate_ok492);
    tcase_add_test(tc_core, test_negate_ok493);
    tcase_add_test(tc_core, test_negate_ok494);
    tcase_add_test(tc_core, test_negate_ok495);
    tcase_add_test(tc_core, test_negate_ok496);
    tcase_add_test(tc_core, test_negate_ok497);
    tcase_add_test(tc_core, test_negate_ok498);
    tcase_add_test(tc_core, test_negate_ok499);
    tcase_add_test(tc_core, test_negate_ok500);
    tcase_add_test(tc_core, test_negate_ok501);
    tcase_add_test(tc_core, test_negate_ok502);
    tcase_add_test(tc_core, test_negate_ok503);
    tcase_add_test(tc_core, test_negate_ok504);
    tcase_add_test(tc_core, test_negate_ok505);
    tcase_add_test(tc_core, test_negate_ok506);
    tcase_add_test(tc_core, test_negate_ok507);
    tcase_add_test(tc_core, test_negate_ok508);
    tcase_add_test(tc_core, test_negate_ok509);
    tcase_add_test(tc_core, test_negate_ok510);
    tcase_add_test(tc_core, test_negate_ok511);
    tcase_add_test(tc_core, test_negate_ok512);
    tcase_add_test(tc_core, test_negate_ok513);
    tcase_add_test(tc_core, test_negate_ok514);
    tcase_add_test(tc_core, test_negate_ok515);
    tcase_add_test(tc_core, test_negate_ok516);
    tcase_add_test(tc_core, test_negate_ok517);
    tcase_add_test(tc_core, test_negate_ok518);
    tcase_add_test(tc_core, test_negate_ok519);
    tcase_add_test(tc_core, test_negate_ok520);
    tcase_add_test(tc_core, test_negate_ok521);
    tcase_add_test(tc_core, test_negate_ok522);
    tcase_add_test(tc_core, test_negate_ok523);
    tcase_add_test(tc_core, test_negate_ok524);
    tcase_add_test(tc_core, test_negate_ok525);
    tcase_add_test(tc_core, test_negate_ok526);
    tcase_add_test(tc_core, test_negate_ok527);
    tcase_add_test(tc_core, test_negate_ok528);
    tcase_add_test(tc_core, test_negate_ok529);
    tcase_add_test(tc_core, test_negate_ok530);
    tcase_add_test(tc_core, test_negate_ok531);
    tcase_add_test(tc_core, test_negate_ok532);
    tcase_add_test(tc_core, test_negate_ok533);
    tcase_add_test(tc_core, test_negate_ok534);
    tcase_add_test(tc_core, test_negate_ok535);
    tcase_add_test(tc_core, test_negate_ok536);
    tcase_add_test(tc_core, test_negate_ok537);
    tcase_add_test(tc_core, test_negate_ok538);
    tcase_add_test(tc_core, test_negate_ok539);
    tcase_add_test(tc_core, test_negate_ok540);
    tcase_add_test(tc_core, test_negate_ok541);
    tcase_add_test(tc_core, test_negate_ok542);
    tcase_add_test(tc_core, test_negate_ok543);
    tcase_add_test(tc_core, test_negate_ok544);
    tcase_add_test(tc_core, test_negate_ok545);
    tcase_add_test(tc_core, test_negate_ok546);
    tcase_add_test(tc_core, test_negate_ok547);
    tcase_add_test(tc_core, test_negate_ok548);
    tcase_add_test(tc_core, test_negate_ok549);
    tcase_add_test(tc_core, test_negate_ok550);
    tcase_add_test(tc_core, test_negate_ok551);
    tcase_add_test(tc_core, test_negate_ok552);
    tcase_add_test(tc_core, test_negate_ok553);
    tcase_add_test(tc_core, test_negate_ok554);
    tcase_add_test(tc_core, test_negate_ok555);
    tcase_add_test(tc_core, test_negate_ok556);
    tcase_add_test(tc_core, test_negate_ok557);
    tcase_add_test(tc_core, test_negate_ok558);
    tcase_add_test(tc_core, test_negate_ok559);
    tcase_add_test(tc_core, test_negate_ok560);
    tcase_add_test(tc_core, test_negate_ok561);
    tcase_add_test(tc_core, test_negate_ok562);
    tcase_add_test(tc_core, test_negate_ok563);
    tcase_add_test(tc_core, test_negate_ok564);
    tcase_add_test(tc_core, test_negate_ok565);
    tcase_add_test(tc_core, test_negate_ok566);
    tcase_add_test(tc_core, test_negate_ok567);
    tcase_add_test(tc_core, test_negate_ok568);
    tcase_add_test(tc_core, test_negate_ok569);
    tcase_add_test(tc_core, test_negate_ok570);
    tcase_add_test(tc_core, test_negate_ok571);
    tcase_add_test(tc_core, test_negate_ok572);
    tcase_add_test(tc_core, test_negate_ok573);
    tcase_add_test(tc_core, test_negate_ok574);
    tcase_add_test(tc_core, test_negate_ok575);
    tcase_add_test(tc_core, test_negate_ok576);
    tcase_add_test(tc_core, test_negate_ok577);
    tcase_add_test(tc_core, test_negate_ok578);
    tcase_add_test(tc_core, test_negate_ok579);
    tcase_add_test(tc_core, test_negate_ok580);
    tcase_add_test(tc_core, test_negate_ok581);
    tcase_add_test(tc_core, test_negate_ok582);
    tcase_add_test(tc_core, test_negate_ok583);
    tcase_add_test(tc_core, test_negate_ok584);
    tcase_add_test(tc_core, test_negate_ok585);
    tcase_add_test(tc_core, test_negate_ok586);
    tcase_add_test(tc_core, test_negate_ok587);
    tcase_add_test(tc_core, test_negate_ok588);
    tcase_add_test(tc_core, test_negate_ok589);
    tcase_add_test(tc_core, test_negate_ok590);
    tcase_add_test(tc_core, test_negate_ok591);
    tcase_add_test(tc_core, test_negate_ok592);
    tcase_add_test(tc_core, test_negate_ok593);
    tcase_add_test(tc_core, test_negate_ok594);
    tcase_add_test(tc_core, test_negate_ok595);
    tcase_add_test(tc_core, test_negate_ok596);
    tcase_add_test(tc_core, test_negate_ok597);
    tcase_add_test(tc_core, test_negate_ok598);
    tcase_add_test(tc_core, test_negate_ok599);
    tcase_add_test(tc_core, test_negate_ok600);
    tcase_add_test(tc_core, test_negate_ok601);
    tcase_add_test(tc_core, test_negate_ok602);
    tcase_add_test(tc_core, test_negate_ok603);
    tcase_add_test(tc_core, test_negate_ok604);
    tcase_add_test(tc_core, test_negate_ok605);
    tcase_add_test(tc_core, test_negate_ok606);
    tcase_add_test(tc_core, test_negate_ok607);
    tcase_add_test(tc_core, test_negate_ok608);
    tcase_add_test(tc_core, test_negate_ok609);
    tcase_add_test(tc_core, test_negate_ok610);
    tcase_add_test(tc_core, test_negate_ok611);
    tcase_add_test(tc_core, test_negate_ok612);
    tcase_add_test(tc_core, test_negate_ok613);
    tcase_add_test(tc_core, test_negate_ok614);
    tcase_add_test(tc_core, test_negate_ok615);
    tcase_add_test(tc_core, test_negate_ok616);
    tcase_add_test(tc_core, test_negate_ok617);
    tcase_add_test(tc_core, test_negate_ok618);
    tcase_add_test(tc_core, test_negate_ok619);
    tcase_add_test(tc_core, test_negate_ok620);
    tcase_add_test(tc_core, test_negate_ok621);
    tcase_add_test(tc_core, test_negate_ok622);
    tcase_add_test(tc_core, test_negate_ok623);
    tcase_add_test(tc_core, test_negate_ok624);
    tcase_add_test(tc_core, test_negate_ok625);
    tcase_add_test(tc_core, test_negate_ok626);
    tcase_add_test(tc_core, test_negate_ok627);
    tcase_add_test(tc_core, test_negate_ok628);
    tcase_add_test(tc_core, test_negate_ok629);
    tcase_add_test(tc_core, test_negate_ok630);
    tcase_add_test(tc_core, test_negate_ok631);
    tcase_add_test(tc_core, test_negate_ok632);
    tcase_add_test(tc_core, test_negate_ok633);
    tcase_add_test(tc_core, test_negate_ok634);
    tcase_add_test(tc_core, test_negate_ok635);
    tcase_add_test(tc_core, test_negate_ok636);
    tcase_add_test(tc_core, test_negate_ok637);
    tcase_add_test(tc_core, test_negate_ok638);
    tcase_add_test(tc_core, test_negate_ok639);
    tcase_add_test(tc_core, test_negate_ok640);
    tcase_add_test(tc_core, test_negate_ok641);
    tcase_add_test(tc_core, test_negate_ok642);
    tcase_add_test(tc_core, test_negate_ok643);
    tcase_add_test(tc_core, test_negate_ok644);
    tcase_add_test(tc_core, test_negate_ok645);
    tcase_add_test(tc_core, test_negate_ok646);
    tcase_add_test(tc_core, test_negate_ok647);
    tcase_add_test(tc_core, test_negate_ok648);
    tcase_add_test(tc_core, test_negate_ok649);
    tcase_add_test(tc_core, test_negate_ok650);
    tcase_add_test(tc_core, test_negate_ok651);
    tcase_add_test(tc_core, test_negate_ok652);
    tcase_add_test(tc_core, test_negate_ok653);
    tcase_add_test(tc_core, test_negate_ok654);
    tcase_add_test(tc_core, test_negate_ok655);
    tcase_add_test(tc_core, test_negate_ok656);
    tcase_add_test(tc_core, test_negate_ok657);
    tcase_add_test(tc_core, test_negate_ok658);
    tcase_add_test(tc_core, test_negate_ok659);
    tcase_add_test(tc_core, test_negate_ok660);
    tcase_add_test(tc_core, test_negate_ok661);
    tcase_add_test(tc_core, test_negate_ok662);
    tcase_add_test(tc_core, test_negate_ok663);
    tcase_add_test(tc_core, test_negate_ok664);
    tcase_add_test(tc_core, test_negate_ok665);
    tcase_add_test(tc_core, test_negate_ok666);
    tcase_add_test(tc_core, test_negate_ok667);
    tcase_add_test(tc_core, test_negate_ok668);
    tcase_add_test(tc_core, test_negate_ok669);
    tcase_add_test(tc_core, test_negate_ok670);
    tcase_add_test(tc_core, test_negate_ok671);
    tcase_add_test(tc_core, test_negate_ok672);
    tcase_add_test(tc_core, test_negate_ok673);
    tcase_add_test(tc_core, test_negate_ok674);
    tcase_add_test(tc_core, test_negate_ok675);
    tcase_add_test(tc_core, test_negate_ok676);
    tcase_add_test(tc_core, test_negate_ok677);
    tcase_add_test(tc_core, test_negate_ok678);
    tcase_add_test(tc_core, test_negate_ok679);
    tcase_add_test(tc_core, test_negate_ok680);
    tcase_add_test(tc_core, test_negate_ok681);
    tcase_add_test(tc_core, test_negate_ok682);
    tcase_add_test(tc_core, test_negate_ok683);
    tcase_add_test(tc_core, test_negate_ok684);
    tcase_add_test(tc_core, test_negate_ok685);
    tcase_add_test(tc_core, test_negate_ok686);
    tcase_add_test(tc_core, test_negate_ok687);
    tcase_add_test(tc_core, test_negate_ok688);
    tcase_add_test(tc_core, test_negate_ok689);
    tcase_add_test(tc_core, test_negate_ok690);
    tcase_add_test(tc_core, test_negate_ok691);
    tcase_add_test(tc_core, test_negate_ok692);
    tcase_add_test(tc_core, test_negate_ok693);
    tcase_add_test(tc_core, test_negate_ok694);
    tcase_add_test(tc_core, test_negate_ok695);
    tcase_add_test(tc_core, test_negate_ok696);
    tcase_add_test(tc_core, test_negate_ok697);
    tcase_add_test(tc_core, test_negate_ok698);
    tcase_add_test(tc_core, test_negate_ok699);
    tcase_add_test(tc_core, test_negate_ok700);
    tcase_add_test(tc_core, test_negate_ok701);
    tcase_add_test(tc_core, test_negate_ok702);
    tcase_add_test(tc_core, test_negate_ok703);
    tcase_add_test(tc_core, test_negate_ok704);
    tcase_add_test(tc_core, test_negate_ok705);
    tcase_add_test(tc_core, test_negate_ok706);
    tcase_add_test(tc_core, test_negate_ok707);
    tcase_add_test(tc_core, test_negate_ok708);
    tcase_add_test(tc_core, test_negate_ok709);
    tcase_add_test(tc_core, test_negate_ok710);
    tcase_add_test(tc_core, test_negate_ok711);
    tcase_add_test(tc_core, test_negate_ok712);
    tcase_add_test(tc_core, test_negate_ok713);
    tcase_add_test(tc_core, test_negate_ok714);
    tcase_add_test(tc_core, test_negate_ok715);
    tcase_add_test(tc_core, test_negate_ok716);
    tcase_add_test(tc_core, test_negate_ok717);
    tcase_add_test(tc_core, test_negate_ok718);
    tcase_add_test(tc_core, test_negate_ok719);
    tcase_add_test(tc_core, test_negate_ok720);
    tcase_add_test(tc_core, test_negate_ok721);
    tcase_add_test(tc_core, test_negate_ok722);
    tcase_add_test(tc_core, test_negate_ok723);
    tcase_add_test(tc_core, test_negate_ok724);
    tcase_add_test(tc_core, test_negate_ok725);
    tcase_add_test(tc_core, test_negate_ok726);
    tcase_add_test(tc_core, test_negate_ok727);
    tcase_add_test(tc_core, test_negate_ok728);
    tcase_add_test(tc_core, test_negate_ok729);
    tcase_add_test(tc_core, test_negate_ok730);
    tcase_add_test(tc_core, test_negate_ok731);
    tcase_add_test(tc_core, test_negate_ok732);
    tcase_add_test(tc_core, test_negate_ok733);
    tcase_add_test(tc_core, test_negate_ok734);
    tcase_add_test(tc_core, test_negate_ok735);
    tcase_add_test(tc_core, test_negate_ok736);
    tcase_add_test(tc_core, test_negate_ok737);
    tcase_add_test(tc_core, test_negate_ok738);
    tcase_add_test(tc_core, test_negate_ok739);
    tcase_add_test(tc_core, test_negate_ok740);
    tcase_add_test(tc_core, test_negate_ok741);
    tcase_add_test(tc_core, test_negate_ok742);
    tcase_add_test(tc_core, test_negate_ok743);
    tcase_add_test(tc_core, test_negate_ok744);
    tcase_add_test(tc_core, test_negate_ok745);
    tcase_add_test(tc_core, test_negate_ok746);
    tcase_add_test(tc_core, test_negate_ok747);
    tcase_add_test(tc_core, test_negate_ok748);
    tcase_add_test(tc_core, test_negate_ok749);
    tcase_add_test(tc_core, test_negate_ok750);
    tcase_add_test(tc_core, test_negate_ok751);
    tcase_add_test(tc_core, test_negate_ok752);
    tcase_add_test(tc_core, test_negate_ok753);
    tcase_add_test(tc_core, test_negate_ok754);
    tcase_add_test(tc_core, test_negate_ok755);
    tcase_add_test(tc_core, test_negate_ok756);
    tcase_add_test(tc_core, test_negate_ok757);
    tcase_add_test(tc_core, test_negate_ok758);
    tcase_add_test(tc_core, test_negate_ok759);
    tcase_add_test(tc_core, test_negate_ok760);
    tcase_add_test(tc_core, test_negate_ok761);
    tcase_add_test(tc_core, test_negate_ok762);
    tcase_add_test(tc_core, test_negate_ok763);
    tcase_add_test(tc_core, test_negate_ok764);
    tcase_add_test(tc_core, test_negate_ok765);
    tcase_add_test(tc_core, test_negate_ok766);
    tcase_add_test(tc_core, test_negate_ok767);
    tcase_add_test(tc_core, test_negate_ok768);
    tcase_add_test(tc_core, test_negate_ok769);
    tcase_add_test(tc_core, test_negate_ok770);
    tcase_add_test(tc_core, test_negate_ok771);
    tcase_add_test(tc_core, test_negate_ok772);
    tcase_add_test(tc_core, test_negate_ok773);
    tcase_add_test(tc_core, test_negate_ok774);
    tcase_add_test(tc_core, test_negate_ok775);
    tcase_add_test(tc_core, test_negate_ok776);
    tcase_add_test(tc_core, test_negate_ok777);
    tcase_add_test(tc_core, test_negate_ok778);
    tcase_add_test(tc_core, test_negate_ok779);
    tcase_add_test(tc_core, test_negate_ok780);
    tcase_add_test(tc_core, test_negate_ok781);
    tcase_add_test(tc_core, test_negate_ok782);
    tcase_add_test(tc_core, test_negate_ok783);
    tcase_add_test(tc_core, test_negate_ok784);
    tcase_add_test(tc_core, test_negate_ok785);
    tcase_add_test(tc_core, test_negate_ok786);
    tcase_add_test(tc_core, test_negate_ok787);
    tcase_add_test(tc_core, test_negate_ok788);
    tcase_add_test(tc_core, test_negate_ok789);
    tcase_add_test(tc_core, test_negate_ok790);
    tcase_add_test(tc_core, test_negate_ok791);
    tcase_add_test(tc_core, test_negate_ok792);
    tcase_add_test(tc_core, test_negate_ok793);
    tcase_add_test(tc_core, test_negate_ok794);
    tcase_add_test(tc_core, test_negate_ok795);
    tcase_add_test(tc_core, test_negate_ok796);
    tcase_add_test(tc_core, test_negate_ok797);
    tcase_add_test(tc_core, test_negate_ok798);
    tcase_add_test(tc_core, test_negate_ok799);
    tcase_add_test(tc_core, test_negate_ok800);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *negate_suite3(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("negate_suite3");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_negate_ok801);
    tcase_add_test(tc_core, test_negate_ok802);
    tcase_add_test(tc_core, test_negate_ok803);
    tcase_add_test(tc_core, test_negate_ok804);
    tcase_add_test(tc_core, test_negate_ok805);
    tcase_add_test(tc_core, test_negate_ok806);
    tcase_add_test(tc_core, test_negate_ok807);
    tcase_add_test(tc_core, test_negate_ok808);
    tcase_add_test(tc_core, test_negate_ok809);
    tcase_add_test(tc_core, test_negate_ok810);
    tcase_add_test(tc_core, test_negate_ok811);
    tcase_add_test(tc_core, test_negate_ok812);
    tcase_add_test(tc_core, test_negate_ok813);
    tcase_add_test(tc_core, test_negate_ok814);
    tcase_add_test(tc_core, test_negate_ok815);
    tcase_add_test(tc_core, test_negate_ok816);
    tcase_add_test(tc_core, test_negate_ok817);
    tcase_add_test(tc_core, test_negate_ok818);
    tcase_add_test(tc_core, test_negate_ok819);
    tcase_add_test(tc_core, test_negate_ok820);
    tcase_add_test(tc_core, test_negate_ok821);
    tcase_add_test(tc_core, test_negate_ok822);
    tcase_add_test(tc_core, test_negate_ok823);
    tcase_add_test(tc_core, test_negate_ok824);
    tcase_add_test(tc_core, test_negate_ok825);
    tcase_add_test(tc_core, test_negate_ok826);
    tcase_add_test(tc_core, test_negate_ok827);
    tcase_add_test(tc_core, test_negate_ok828);
    tcase_add_test(tc_core, test_negate_ok829);
    tcase_add_test(tc_core, test_negate_ok830);
    tcase_add_test(tc_core, test_negate_ok831);
    tcase_add_test(tc_core, test_negate_ok832);
    tcase_add_test(tc_core, test_negate_ok833);
    tcase_add_test(tc_core, test_negate_ok834);
    tcase_add_test(tc_core, test_negate_ok835);
    tcase_add_test(tc_core, test_negate_ok836);
    tcase_add_test(tc_core, test_negate_ok837);
    tcase_add_test(tc_core, test_negate_ok838);
    tcase_add_test(tc_core, test_negate_ok839);
    tcase_add_test(tc_core, test_negate_ok840);
    tcase_add_test(tc_core, test_negate_ok841);
    tcase_add_test(tc_core, test_negate_ok842);
    tcase_add_test(tc_core, test_negate_ok843);
    tcase_add_test(tc_core, test_negate_ok844);
    tcase_add_test(tc_core, test_negate_ok845);
    tcase_add_test(tc_core, test_negate_ok846);
    tcase_add_test(tc_core, test_negate_ok847);
    tcase_add_test(tc_core, test_negate_ok848);
    tcase_add_test(tc_core, test_negate_ok849);
    tcase_add_test(tc_core, test_negate_ok850);
    tcase_add_test(tc_core, test_negate_ok851);
    tcase_add_test(tc_core, test_negate_ok852);
    tcase_add_test(tc_core, test_negate_ok853);
    tcase_add_test(tc_core, test_negate_ok854);
    tcase_add_test(tc_core, test_negate_ok855);
    tcase_add_test(tc_core, test_negate_ok856);
    tcase_add_test(tc_core, test_negate_ok857);
    tcase_add_test(tc_core, test_negate_ok858);
    tcase_add_test(tc_core, test_negate_ok859);
    tcase_add_test(tc_core, test_negate_ok860);
    tcase_add_test(tc_core, test_negate_ok861);
    tcase_add_test(tc_core, test_negate_ok862);
    tcase_add_test(tc_core, test_negate_ok863);
    tcase_add_test(tc_core, test_negate_ok864);
    tcase_add_test(tc_core, test_negate_ok865);
    tcase_add_test(tc_core, test_negate_ok866);
    tcase_add_test(tc_core, test_negate_ok867);
    tcase_add_test(tc_core, test_negate_ok868);
    tcase_add_test(tc_core, test_negate_ok869);
    tcase_add_test(tc_core, test_negate_ok870);
    tcase_add_test(tc_core, test_negate_ok871);
    tcase_add_test(tc_core, test_negate_ok872);
    tcase_add_test(tc_core, test_negate_ok873);
    tcase_add_test(tc_core, test_negate_ok874);
    tcase_add_test(tc_core, test_negate_ok875);
    tcase_add_test(tc_core, test_negate_ok876);
    tcase_add_test(tc_core, test_negate_ok877);
    tcase_add_test(tc_core, test_negate_ok878);
    tcase_add_test(tc_core, test_negate_ok879);
    tcase_add_test(tc_core, test_negate_ok880);
    tcase_add_test(tc_core, test_negate_ok881);
    tcase_add_test(tc_core, test_negate_ok882);
    tcase_add_test(tc_core, test_negate_ok883);
    tcase_add_test(tc_core, test_negate_ok884);
    tcase_add_test(tc_core, test_negate_ok885);
    tcase_add_test(tc_core, test_negate_ok886);
    tcase_add_test(tc_core, test_negate_ok887);
    tcase_add_test(tc_core, test_negate_ok888);
    tcase_add_test(tc_core, test_negate_ok889);
    tcase_add_test(tc_core, test_negate_ok890);
    tcase_add_test(tc_core, test_negate_ok891);
    tcase_add_test(tc_core, test_negate_ok892);
    tcase_add_test(tc_core, test_negate_ok893);
    tcase_add_test(tc_core, test_negate_ok894);
    tcase_add_test(tc_core, test_negate_ok895);
    tcase_add_test(tc_core, test_negate_ok896);
    tcase_add_test(tc_core, test_negate_ok897);
    tcase_add_test(tc_core, test_negate_ok898);
    tcase_add_test(tc_core, test_negate_ok899);
    tcase_add_test(tc_core, test_negate_ok900);
    tcase_add_test(tc_core, test_negate_ok901);
    tcase_add_test(tc_core, test_negate_ok902);
    tcase_add_test(tc_core, test_negate_ok903);
    tcase_add_test(tc_core, test_negate_ok904);
    tcase_add_test(tc_core, test_negate_ok905);
    tcase_add_test(tc_core, test_negate_ok906);
    tcase_add_test(tc_core, test_negate_ok907);
    tcase_add_test(tc_core, test_negate_ok908);
    tcase_add_test(tc_core, test_negate_ok909);
    tcase_add_test(tc_core, test_negate_ok910);
    tcase_add_test(tc_core, test_negate_ok911);
    tcase_add_test(tc_core, test_negate_ok912);
    tcase_add_test(tc_core, test_negate_ok913);
    tcase_add_test(tc_core, test_negate_ok914);
    tcase_add_test(tc_core, test_negate_ok915);
    tcase_add_test(tc_core, test_negate_ok916);
    tcase_add_test(tc_core, test_negate_ok917);
    tcase_add_test(tc_core, test_negate_ok918);
    tcase_add_test(tc_core, test_negate_ok919);
    tcase_add_test(tc_core, test_negate_ok920);
    tcase_add_test(tc_core, test_negate_ok921);
    tcase_add_test(tc_core, test_negate_ok922);
    tcase_add_test(tc_core, test_negate_ok923);
    tcase_add_test(tc_core, test_negate_ok924);
    tcase_add_test(tc_core, test_negate_ok925);
    tcase_add_test(tc_core, test_negate_ok926);
    tcase_add_test(tc_core, test_negate_ok927);
    tcase_add_test(tc_core, test_negate_ok928);
    tcase_add_test(tc_core, test_negate_ok929);
    tcase_add_test(tc_core, test_negate_ok930);
    tcase_add_test(tc_core, test_negate_ok931);
    tcase_add_test(tc_core, test_negate_ok932);
    tcase_add_test(tc_core, test_negate_ok933);
    tcase_add_test(tc_core, test_negate_ok934);
    tcase_add_test(tc_core, test_negate_ok935);
    tcase_add_test(tc_core, test_negate_ok936);
    tcase_add_test(tc_core, test_negate_ok937);
    tcase_add_test(tc_core, test_negate_ok938);
    tcase_add_test(tc_core, test_negate_ok939);
    tcase_add_test(tc_core, test_negate_ok940);
    tcase_add_test(tc_core, test_negate_ok941);
    tcase_add_test(tc_core, test_negate_ok942);
    tcase_add_test(tc_core, test_negate_ok943);
    tcase_add_test(tc_core, test_negate_ok944);
    tcase_add_test(tc_core, test_negate_ok945);
    tcase_add_test(tc_core, test_negate_ok946);
    tcase_add_test(tc_core, test_negate_ok947);
    tcase_add_test(tc_core, test_negate_ok948);
    tcase_add_test(tc_core, test_negate_ok949);
    tcase_add_test(tc_core, test_negate_ok950);
    tcase_add_test(tc_core, test_negate_ok951);
    tcase_add_test(tc_core, test_negate_ok952);
    tcase_add_test(tc_core, test_negate_ok953);
    tcase_add_test(tc_core, test_negate_ok954);
    tcase_add_test(tc_core, test_negate_ok955);
    tcase_add_test(tc_core, test_negate_ok956);
    tcase_add_test(tc_core, test_negate_ok957);
    tcase_add_test(tc_core, test_negate_ok958);
    tcase_add_test(tc_core, test_negate_ok959);
    tcase_add_test(tc_core, test_negate_ok960);
    tcase_add_test(tc_core, test_negate_ok961);
    tcase_add_test(tc_core, test_negate_ok962);
    tcase_add_test(tc_core, test_negate_ok963);
    tcase_add_test(tc_core, test_negate_ok964);
    tcase_add_test(tc_core, test_negate_ok965);
    tcase_add_test(tc_core, test_negate_ok966);
    tcase_add_test(tc_core, test_negate_ok967);
    tcase_add_test(tc_core, test_negate_ok968);
    tcase_add_test(tc_core, test_negate_ok969);
    tcase_add_test(tc_core, test_negate_ok970);
    tcase_add_test(tc_core, test_negate_ok971);
    tcase_add_test(tc_core, test_negate_ok972);
    tcase_add_test(tc_core, test_negate_ok973);
    tcase_add_test(tc_core, test_negate_ok974);
    tcase_add_test(tc_core, test_negate_ok975);
    tcase_add_test(tc_core, test_negate_ok976);
    tcase_add_test(tc_core, test_negate_ok977);
    tcase_add_test(tc_core, test_negate_ok978);
    tcase_add_test(tc_core, test_negate_ok979);
    tcase_add_test(tc_core, test_negate_ok980);
    tcase_add_test(tc_core, test_negate_ok981);
    tcase_add_test(tc_core, test_negate_ok982);
    tcase_add_test(tc_core, test_negate_ok983);
    tcase_add_test(tc_core, test_negate_ok984);
    tcase_add_test(tc_core, test_negate_ok985);
    tcase_add_test(tc_core, test_negate_ok986);
    tcase_add_test(tc_core, test_negate_ok987);
    tcase_add_test(tc_core, test_negate_ok988);
    tcase_add_test(tc_core, test_negate_ok989);
    tcase_add_test(tc_core, test_negate_ok990);
    tcase_add_test(tc_core, test_negate_ok991);
    tcase_add_test(tc_core, test_negate_ok992);
    tcase_add_test(tc_core, test_negate_ok993);
    tcase_add_test(tc_core, test_negate_ok994);
    tcase_add_test(tc_core, test_negate_ok995);
    tcase_add_test(tc_core, test_negate_ok996);
    tcase_add_test(tc_core, test_negate_ok997);
    tcase_add_test(tc_core, test_negate_ok998);
    tcase_add_test(tc_core, test_negate_ok999);
    tcase_add_test(tc_core, test_negate_ok1000);
    tcase_add_test(tc_core, test_negate_ok1001);
    tcase_add_test(tc_core, test_negate_ok1002);
    tcase_add_test(tc_core, test_negate_ok1003);
    tcase_add_test(tc_core, test_negate_ok1004);
    tcase_add_test(tc_core, test_negate_ok1005);
    tcase_add_test(tc_core, test_negate_ok1006);
    tcase_add_test(tc_core, test_negate_ok1007);
    tcase_add_test(tc_core, test_negate_ok1008);
    tcase_add_test(tc_core, test_negate_ok1009);
    tcase_add_test(tc_core, test_negate_ok1010);
    tcase_add_test(tc_core, test_negate_ok1011);
    tcase_add_test(tc_core, test_negate_ok1012);
    tcase_add_test(tc_core, test_negate_ok1013);
    tcase_add_test(tc_core, test_negate_ok1014);
    tcase_add_test(tc_core, test_negate_ok1015);
    tcase_add_test(tc_core, test_negate_ok1016);
    tcase_add_test(tc_core, test_negate_ok1017);
    tcase_add_test(tc_core, test_negate_ok1018);
    tcase_add_test(tc_core, test_negate_ok1019);
    tcase_add_test(tc_core, test_negate_ok1020);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *negate_suite0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("negate_suite0");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_negate_fail1);
    tcase_add_test(tc_core, test_negate_fail2);
    tcase_add_test(tc_core, test_negate_fail3);
    tcase_add_test(tc_core, test_negate_fail4);
    tcase_add_test(tc_core, test_negate_fail5);
    tcase_add_test(tc_core, test_negate_fail6);
    tcase_add_test(tc_core, test_negate_fail7);
    tcase_add_test(tc_core, test_negate_fail8);
    tcase_add_test(tc_core, test_negate_fail9);

    suite_add_tcase(s, tc_core);
    return s;
}

void test_negate(s21_decimal decimal, s21_decimal decimal_check) {
    s21_decimal result;

    int code = s21_negate(decimal, &result);
    int sign_check = test_decimal_get_sign(decimal_check);
    int sign_result = test_decimal_get_sign(result);

    #if defined(__DEBUG)
    printf("---------------------------------\n");
    printf("\n\nTests:\n");
    s21_print_decimal_bits(decimal);
    s21_print_decimal_string(decimal);
    printf("\ncheck:\n");
    s21_print_decimal_bits(decimal_check);
    s21_print_decimal_string(decimal_check);
    printf("sign = %d\n", sign_check);
    printf("\nres:\n");
    s21_print_decimal_bits(result);
    s21_print_decimal_string(result);
    printf("sign = %d\n", sign_result);
    printf("---------------------------------\n\n\n\n");
    #endif

    ck_assert_int_eq(code, TEST_OTHER_OK);
    ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
    ck_assert_int_eq(sign_check, sign_result);
}
