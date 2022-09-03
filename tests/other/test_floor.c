#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные (ручные)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_floor_fail1) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

    int code = s21_floor(decimal, NULL);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}

START_TEST(test_floor_fail2) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail4) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail5) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail6) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail7) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail8) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

START_TEST(test_floor_fail9) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    s21_decimal result;

    int code = s21_floor(decimal, &result);

    ck_assert_int_eq(code, TEST_OTHER_ERROR);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_floor_ok1) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok2) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395034
    s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok5) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok6) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439504
    s21_decimal decimal_check = {{0x28F5C290, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok7) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok8) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543951
    s21_decimal decimal_check = {{0x9DB22D0F, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok9) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok10) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354396
    s21_decimal decimal_check = {{0x295E9E1C, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok11) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok12) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935440
    s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok13) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok14) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593544
    s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok15) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok16) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759355
    s21_decimal decimal_check = {{0xF485787B, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok17) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok18) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375936
    s21_decimal decimal_check = {{0x1873BF40, 0xF31DC461, 0x2A, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok19) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok20) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337594
    s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok21) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok22) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433760
    s21_decimal decimal_check = {{0x5EF6EAE0, 0x6DF37F67, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok23) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok24) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643376
    s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok25) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok26) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264338
    s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok27) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok28) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426434
    s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok29) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok30) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142644
    s21_decimal decimal_check = {{0x70D42574, 0x2D093, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok31) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok32) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514265
    s21_decimal decimal_check = {{0xBE7B9D59, 0x480E, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok33) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok34) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251427
    s21_decimal decimal_check = {{0xACA5F623, 0x734, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok35) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok36) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok37) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok38) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162515
    s21_decimal decimal_check = {{0x725DD1D3, 0x12, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok39) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok40) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816252
    s21_decimal decimal_check = {{0xD83C94FC, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok41) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok42) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281626
    s21_decimal decimal_check = {{0x2F39421A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok43) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok44) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228163
    s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok45) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok46) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922817
    s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok47) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok48) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792282
    s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok49) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok50) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79229
    s21_decimal decimal_check = {{0x1357D, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok51) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok52) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7923
    s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok53) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok54) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -793
    s21_decimal decimal_check = {{0x319, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok55) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok56) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -80
    s21_decimal decimal_check = {{0x50, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok57) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok58) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok59) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok60) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950334
    s21_decimal decimal_check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok61) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok62) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395034
    s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok63) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    // 792281625142643375935439503
    s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok64) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    // -792281625142643375935439504
    s21_decimal decimal_check = {{0x28F5C290, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok65) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    // 79228162514264337593543950
    s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok66) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    // -79228162514264337593543951
    s21_decimal decimal_check = {{0x9DB22D0F, 0x4BC6A7EF, 0x418937, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok67) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    // 7922816251426433759354395
    s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok68) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    // -7922816251426433759354396
    s21_decimal decimal_check = {{0x295E9E1C, 0xBAC710CB, 0x68DB8, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok69) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    // 792281625142643375935439
    s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok70) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    // -792281625142643375935440
    s21_decimal decimal_check = {{0x84230FD0, 0xAC471B47, 0xA7C5, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok71) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    // 79228162514264337593543
    s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok72) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    // -79228162514264337593544
    s21_decimal decimal_check = {{0x8D36B4C8, 0xF7A0B5ED, 0x10C6, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok73) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    // 7922816251426433759354
    s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok74) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    // -7922816251426433759355
    s21_decimal decimal_check = {{0xF485787B, 0x7F29ABCA, 0x1AD, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok75) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    // 792281625142643375935
    s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok76) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    // -792281625142643375936
    s21_decimal decimal_check = {{0x1873BF40, 0xF31DC461, 0x2A, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok77) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    // 79228162514264337593
    s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok78) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    // -79228162514264337594
    s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok79) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    // 7922816251426433759
    s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok80) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    // -7922816251426433760
    s21_decimal decimal_check = {{0x5EF6EAE0, 0x6DF37F67, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok81) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    // 792281625142643375
    s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok82) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    // -792281625142643376
    s21_decimal decimal_check = {{0xBCB24AB0, 0xAFEBFF0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok83) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    // 79228162514264337
    s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok84) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    // -79228162514264338
    s21_decimal decimal_check = {{0x12DEA112, 0x1197998, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok85) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    // 7922816251426433
    s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok86) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    // -7922816251426434
    s21_decimal decimal_check = {{0x68497682, 0x1C25C2, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok87) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    // 792281625142643
    s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok88) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    // -792281625142644
    s21_decimal decimal_check = {{0x70D42574, 0x2D093, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok89) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok90) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514265
    s21_decimal decimal_check = {{0xBE7B9D59, 0x480E, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok91) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    // 7922816251426
    s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok92) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    // -7922816251427
    s21_decimal decimal_check = {{0xACA5F623, 0x734, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok93) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok94) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok95) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    // 79228162514
    s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok96) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    // -79228162515
    s21_decimal decimal_check = {{0x725DD1D3, 0x12, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok97) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    // 7922816251
    s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok98) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    // -7922816252
    s21_decimal decimal_check = {{0xD83C94FC, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok99) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    // 792281625
    s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok100) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    // -792281626
    s21_decimal decimal_check = {{0x2F39421A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok101) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    // 79228162
    s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok102) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    // -79228163
    s21_decimal decimal_check = {{0x4B8ED03, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok103) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    // 7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok104) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    // -7922817
    s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok105) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    // 792281
    s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok106) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    // -792282
    s21_decimal decimal_check = {{0xC16DA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok107) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    // 79228
    s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok108) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    // -79229
    s21_decimal decimal_check = {{0x1357D, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok109) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    // 7922
    s21_decimal decimal_check = {{0x1EF2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok110) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    // -7923
    s21_decimal decimal_check = {{0x1EF3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok111) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    // 792
    s21_decimal decimal_check = {{0x318, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok112) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    // -793
    s21_decimal decimal_check = {{0x319, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok113) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    // 79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok114) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    // -80
    s21_decimal decimal_check = {{0x50, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok115) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok116) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok117) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok118) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558395695966890
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok119) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok120) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839569596689
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok121) {
    // 5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok122) {
    // -5281877500950955.8395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950956
    s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok123) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok124) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok125) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    // 52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok126) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    // -52818775009509558392832655360
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok127) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    // 5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok128) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    // -5281877500950955839283265536
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok129) {
    // 5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0xD0000}};
    // 5281877500950955
    s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok130) {
    // -5281877500950955.8392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
    // -5281877500950956
    s21_decimal decimal_check = {{0xF030F9AC, 0x12C3D6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok131) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok132) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok133) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok134) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729016086244010
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok135) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok136) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901608624401
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x11111111, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok137) {
    // 5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok138) {
    // -5281877499721172.9016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721173
    s21_decimal decimal_check = {{0xF01E35D5, 0x12C3D6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok139) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok140) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok141) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    // 52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok142) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    // -52818774997211729013222932480
    s21_decimal decimal_check = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok143) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    // 5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok144) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    // -5281877499721172901322293248
    s21_decimal decimal_check = {{0x0, 0x0, 0x11111111, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok145) {
    // 5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0xD0000}};
    // 5281877499721172
    s21_decimal decimal_check = {{0xF01E35D4, 0x12C3D6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok146) {
    // -5281877499721172.9013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x800D0000}};
    // -5281877499721173
    s21_decimal decimal_check = {{0xF01E35D5, 0x12C3D6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok147) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    // 5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok148) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok149) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok150) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829382473034410
    s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok151) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok152) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782938247303441
    s21_decimal decimal_check = {{0x11111111, 0x11111111, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok153) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok154) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978294
    s21_decimal decimal_check = {{0x7547FF6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok155) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok156) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok157) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    // 12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok158) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    // -12297829379609722880
    s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok159) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    // 1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok160) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    // -1229782937960972288
    s21_decimal decimal_check = {{0x0, 0x11111111, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok161) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    // 122978293
    s21_decimal decimal_check = {{0x7547FF5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok162) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    // -122978294
    s21_decimal decimal_check = {{0x7547FF6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok163) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok164) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok165) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    // 2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok166) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    // -2863311530
    s21_decimal decimal_check = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok167) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    // 286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok168) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    // -286331153
    s21_decimal decimal_check = {{0x11111111, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok169) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    // 286331
    s21_decimal decimal_check = {{0x45E7B, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok170) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    // -286332
    s21_decimal decimal_check = {{0x45E7C, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok171) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok172) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok173) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok174) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779197847983445
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok175) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919784798344
    s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok176) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919784798345
    s21_decimal decimal_check = {{0x88888889, 0x88888888, 0x8888888, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok177) {
    // 2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok178) {
    // -2640938750475477.9197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475478
    s21_decimal decimal_check = {{0x78187CD6, 0x961EB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok179) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok180) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok181) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    // 26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok182) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    // -26409387504754779196416327680
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok183) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    // 2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok184) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    // -2640938750475477919641632768
    s21_decimal decimal_check = {{0x80000000, 0x88888888, 0x8888888, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok185) {
    // 2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0xD0000}};
    // 2640938750475477
    s21_decimal decimal_check = {{0x78187CD5, 0x961EB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok186) {
    // -2640938750475477.9196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x800D0000}};
    // -2640938750475478
    s21_decimal decimal_check = {{0x78187CD6, 0x961EB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok187) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok188) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok189) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    // 26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok190) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864508043122005
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok191) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450804312200
    s21_decimal decimal_check = {{0x8888888, 0x80000000, 0x8888888, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok192) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450804312201
    s21_decimal decimal_check = {{0x8888889, 0x80000000, 0x8888888, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok193) {
    // 2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok194) {
    // -2640938749860586.4508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860587
    s21_decimal decimal_check = {{0x780F1AEB, 0x961EB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok195) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok196) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok197) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    // 26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok198) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    // -26409387498605864506611466240
    s21_decimal decimal_check = {{0x0, 0x0, 0x55555555, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok199) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    // 2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok200) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    // -2640938749860586450661146624
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x8888888, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok201) {
    // 2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0xD0000}};
    // 2640938749860586
    s21_decimal decimal_check = {{0x780F1AEA, 0x961EB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok202) {
    // -2640938749860586.4506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x800D0000}};
    // -2640938749860587
    s21_decimal decimal_check = {{0x780F1AEB, 0x961EB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok203) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok204) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok205) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    // 6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok206) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    // -6148914691236517205
    s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok207) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    // 614891469123651720
    s21_decimal decimal_check = {{0x88888888, 0x8888888, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok208) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    // -614891469123651721
    s21_decimal decimal_check = {{0x88888889, 0x8888888, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok209) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    // 6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok210) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    // -6148915
    s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok211) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok212) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok213) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    // 6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok214) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    // -6148914689804861440
    s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok215) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    // 614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok216) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    // -614891468980486144
    s21_decimal decimal_check = {{0x80000000, 0x8888888, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok217) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    // 6148914
    s21_decimal decimal_check = {{0x5DD332, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok218) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    // -6148915
    s21_decimal decimal_check = {{0x5DD333, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok219) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok220) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok221) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    // 1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok222) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    // -1431655765
    s21_decimal decimal_check = {{0x55555555, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok223) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    // 143165576
    s21_decimal decimal_check = {{0x8888888, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok224) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    // -143165577
    s21_decimal decimal_check = {{0x8888889, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok225) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    // 143165
    s21_decimal decimal_check = {{0x22F3D, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok226) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    // -143166
    s21_decimal decimal_check = {{0x22F3E, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok227) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok228) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok229) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    // 18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok230) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    // -18446744078004518913
    s21_decimal decimal_check = {{0x1, 0x1, 0x1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok231) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok232) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    // -1844674407800451892
    s21_decimal decimal_check = {{0xB3333334, 0x19999999, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok233) {
    // 184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000}};
    // 184467440780
    s21_decimal decimal_check = {{0xF31DC48C, 0x2A, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok234) {
    // -184467440780.04518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80080000}};
    // -184467440781
    s21_decimal decimal_check = {{0xF31DC48D, 0x2A, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok235) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok236) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok237) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    // 18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok238) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    // -18446744078004518912
    s21_decimal decimal_check = {{0x0, 0x1, 0x1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok239) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    // 1844674407800451891
    s21_decimal decimal_check = {{0xB3333333, 0x19999999, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok240) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    // -1844674407800451892
    s21_decimal decimal_check = {{0xB3333334, 0x19999999, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok241) {
    // 18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x90000}};
    // 18446744078
    s21_decimal decimal_check = {{0x4B82FA0E, 0x4, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok242) {
    // -18446744078.004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80090000}};
    // -18446744079
    s21_decimal decimal_check = {{0x4B82FA0F, 0x4, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok243) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok244) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok245) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    // 18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok246) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    // -18446744073709551617
    s21_decimal decimal_check = {{0x1, 0x0, 0x1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok247) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok248) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    // -1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok249) {
    // 1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xA0000}};
    // 1844674407
    s21_decimal decimal_check = {{0x6DF37F67, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok250) {
    // -1844674407.3709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800A0000}};
    // -1844674408
    s21_decimal decimal_check = {{0x6DF37F68, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok251) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok252) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok253) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    // 18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok254) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    // -18446744073709551616
    s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok255) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok256) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    // -1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok257) {
    // 184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xB0000}};
    // 184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok258) {
    // -184467440.73709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800B0000}};
    // -184467441
    s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok259) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok260) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok261) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    // 4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok262) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    // -4294967297
    s21_decimal decimal_check = {{0x1, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok263) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok264) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    // -429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok265) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok266) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    // -42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok267) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    // 429496
    s21_decimal decimal_check = {{0x68DB8, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok268) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    // -429497
    s21_decimal decimal_check = {{0x68DB9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok269) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok270) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok271) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok272) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    // -43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok273) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    // 4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok274) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    // -4294967296
    s21_decimal decimal_check = {{0x0, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok275) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok276) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    // -429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok277) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok278) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    // -42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok279) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    // 4294967
    s21_decimal decimal_check = {{0x418937, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok280) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    // -4294968
    s21_decimal decimal_check = {{0x418938, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok281) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok282) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok283) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok284) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    // -43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok285) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok286) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok287) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok288) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok289) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok290) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok291) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok292) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok293) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok294) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok295) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok296) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok297) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok298) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540835774234624
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok299) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083577423462
    s21_decimal decimal_check = {{0xA6666666, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok300) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083577423463
    s21_decimal decimal_check = {{0xA6666667, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok301) {
    // 39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
    // 39614081266355
    s21_decimal decimal_check = {{0x5F3DF2B3, 0x2407, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok302) {
    // -39614081266355.540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
    // -39614081266356
    s21_decimal decimal_check = {{0x5F3DF2B4, 0x2407, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok303) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok304) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok305) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    // 39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok306) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    // -39614081266355540833626750976
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x80000000, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok307) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    // 3961408126635554083362675097
    s21_decimal decimal_check = {{0x99999999, 0xD9999999, 0xCCCCCCC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok308) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    // -3961408126635554083362675098
    s21_decimal decimal_check = {{0x9999999A, 0xD9999999, 0xCCCCCCC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok309) {
    // 3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0xD0000}};
    // 3961408126635554
    s21_decimal decimal_check = {{0x3432CE22, 0xE12E1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok310) {
    // -3961408126635554.0833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x800D0000}};
    // -3961408126635555
    s21_decimal decimal_check = {{0x3432CE23, 0xE12E1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok311) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok312) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok313) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    // 39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok314) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168798919458816
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok315) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879891945881
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok316) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879891945882
    s21_decimal decimal_check = {{0xD999999A, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok317) {
    // 39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0xC0000}};
    // 39614081257132168
    s21_decimal decimal_check = {{0x96F5088, 0x8CBCCC, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok318) {
    // -39614081257132168.798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x800C0000}};
    // -39614081257132169
    s21_decimal decimal_check = {{0x96F5089, 0x8CBCCC, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok319) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok320) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok321) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    // 39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok322) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    // -39614081257132168796771975168
    s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok323) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    // 3961408125713216879677197516
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok324) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    // -3961408125713216879677197517
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCCC, 0xCCCCCCC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok325) {
    // 396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0xB0000}};
    // 396140812571321687
    s21_decimal decimal_check = {{0x5E592557, 0x57F5FF8, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok326) {
    // -396140812571321687.96771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x800B0000}};
    // -396140812571321688
    s21_decimal decimal_check = {{0x5E592558, 0x57F5FF8, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok327) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok328) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok329) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    // 9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok330) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    // -9223372039002259456
    s21_decimal decimal_check = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok331) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    // 922337203900225945
    s21_decimal decimal_check = {{0xD9999999, 0xCCCCCCC, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok332) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    // -922337203900225946
    s21_decimal decimal_check = {{0xD999999A, 0xCCCCCCC, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok333) {
    // 922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x70000}};
    // 922337203900
    s21_decimal decimal_check = {{0xBF94D6BC, 0xD6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok334) {
    // -922337203900.2259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80070000}};
    // -922337203901
    s21_decimal decimal_check = {{0xBF94D6BD, 0xD6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok335) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok336) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    // -10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok337) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    // 9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok338) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    // -9223372036854775808
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok339) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    // 922337203685477580
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCC, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok340) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    // -922337203685477581
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCC, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok341) {
    // 92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000}};
    // 92233720368
    s21_decimal decimal_check = {{0x798EE230, 0x15, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok342) {
    // -92233720368.54775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80080000}};
    // -92233720369
    s21_decimal decimal_check = {{0x798EE231, 0x15, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok343) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok344) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    // -10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok345) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    // 2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok346) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    // -2147483648
    s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok347) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    // 214748364
    s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok348) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    // -214748365
    s21_decimal decimal_check = {{0xCCCCCCD, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok349) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    // 21474836
    s21_decimal decimal_check = {{0x147AE14, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok350) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    // -21474837
    s21_decimal decimal_check = {{0x147AE15, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok351) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    // 214748
    s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok352) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    // -214749
    s21_decimal decimal_check = {{0x346DD, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok353) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    // 21
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok354) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    // -22
    s21_decimal decimal_check = {{0x16, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok355) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok356) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok357) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    // 156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok358) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695305426944
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x811800, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok359) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269530542694
    s21_decimal decimal_check = {{0x99A68266, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok360) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269530542695
    s21_decimal decimal_check = {{0x99A68267, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok361) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    // 1560647
    s21_decimal decimal_check = {{0x17D047, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok362) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    // -1560648
    s21_decimal decimal_check = {{0x17D048, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok363) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok364) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok365) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    // 156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok366) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    // -156064767562212695296966656
    s21_decimal decimal_check = {{0x0, 0x811800, 0x811800, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok367) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    // 15606476756221269529696665
    s21_decimal decimal_check = {{0x99999999, 0xCCD9B599, 0xCE8CC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok368) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    // -15606476756221269529696666
    s21_decimal decimal_check = {{0x9999999A, 0xCCD9B599, 0xCE8CC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok369) {
    // 15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x40000}};
    // 15606476756221269529696
    s21_decimal decimal_check = {{0x27525460, 0x75F7320, 0x34E, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok370) {
    // -15606476756221269529696.6656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80040000}};
    // -15606476756221269529697
    s21_decimal decimal_check = {{0x27525461, 0x75F7320, 0x34E, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok371) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok372) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok373) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    // 156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok374) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035030685696
    s21_decimal decimal_check = {{0x811800, 0x0, 0x811800, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok375) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    // 15606476752587603503068569
    s21_decimal decimal_check = {{0xCCD9B599, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok376) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603503068570
    s21_decimal decimal_check = {{0xCCD9B59A, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok377) {
    // 1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0xB0000}};
    // 1560647675258760
    s21_decimal decimal_check = {{0x9A4DA788, 0x58B66, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok378) {
    // -1560647675258760.35030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x800B0000}};
    // -1560647675258761
    s21_decimal decimal_check = {{0x9A4DA789, 0x58B66, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok379) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok380) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok381) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    // 156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok382) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    // -156064767525876035022225408
    s21_decimal decimal_check = {{0x0, 0x0, 0x811800, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok383) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    // 15606476752587603502222540
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCCCCCCCC, 0xCE8CC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok384) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    // -15606476752587603502222541
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCCCCCCCC, 0xCE8CC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok385) {
    // 15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x130000}};
    // 15606476
    s21_decimal decimal_check = {{0xEE22CC, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok386) {
    // -15606476.7525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80130000}};
    // -15606477
    s21_decimal decimal_check = {{0xEE22CD, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok387) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok388) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok389) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    // 36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok390) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    // -36336660283201536
    s21_decimal decimal_check = {{0x811800, 0x811800, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok391) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    // 3633666028320153
    s21_decimal decimal_check = {{0xCCD9B599, 0xCE8CC, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok392) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    // -3633666028320154
    s21_decimal decimal_check = {{0xCCD9B59A, 0xCE8CC, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok393) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    // 363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok394) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    // -363366603
    s21_decimal decimal_check = {{0x15A888CB, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok395) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok396) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok397) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    // 36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok398) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    // -36336660274741248
    s21_decimal decimal_check = {{0x0, 0x811800, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok399) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    // 3633666027474124
    s21_decimal decimal_check = {{0xCCCCCCCC, 0xCE8CC, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok400) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    // -3633666027474125
    s21_decimal decimal_check = {{0xCCCCCCCD, 0xCE8CC, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok401) {
    // 363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x20000}};
    // 363366602747412
    s21_decimal decimal_check = {{0xE147AE14, 0x14A7A, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok402) {
    // -363366602747412.48
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80020000}};
    // -363366602747413
    s21_decimal decimal_check = {{0xE147AE15, 0x14A7A, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok403) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    // 363366602
    s21_decimal decimal_check = {{0x15A888CA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok404) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    // -363366603
    s21_decimal decimal_check = {{0x15A888CB, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok405) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    // 36
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok406) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    // -37
    s21_decimal decimal_check = {{0x25, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok407) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok408) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok409) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    // 8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok410) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    // -8460288
    s21_decimal decimal_check = {{0x811800, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok411) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    // 846028
    s21_decimal decimal_check = {{0xCE8CC, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok412) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    // -846029
    s21_decimal decimal_check = {{0xCE8CD, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok413) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    // 84602
    s21_decimal decimal_check = {{0x14A7A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok414) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    // -84603
    s21_decimal decimal_check = {{0x14A7B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok415) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    // 8460
    s21_decimal decimal_check = {{0x210C, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok416) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    // -8461
    s21_decimal decimal_check = {{0x210D, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok417) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    // 84
    s21_decimal decimal_check = {{0x54, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok418) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    // -85
    s21_decimal decimal_check = {{0x55, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok419) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok420) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok421) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok422) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337593543950335
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok423) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433759354395033
    s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok424) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433759354395034
    s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok425) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    // 792281625142
    s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok426) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    // -792281625143
    s21_decimal decimal_check = {{0x77AA3237, 0xB8, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok427) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok428) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok429) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    // 79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok430) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    // -79228162514264337589248983040
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok431) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    // 7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok432) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    // -7922816251426433758924898304
    s21_decimal decimal_check = {{0x80000000, 0x99999999, 0x19999999, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok433) {
    // 79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    // 79228162514264
    s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok434) {
    // -79228162514264.337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    // -79228162514265
    s21_decimal decimal_check = {{0xBE7B9D59, 0x480E, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok435) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok436) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok437) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok438) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593524129366015
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok439) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759352412936601
    s21_decimal decimal_check = {{0x19999999, 0x80000000, 0x19999999, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok440) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759352412936602
    s21_decimal decimal_check = {{0x1999999A, 0x80000000, 0x19999999, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok441) {
    // 792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x110000}};
    // 792281624958
    s21_decimal decimal_check = {{0x77AA317E, 0xB8, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok442) {
    // -792281624958.17593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80110000}};
    // -792281624959
    s21_decimal decimal_check = {{0x77AA317F, 0xB8, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok443) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok444) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok445) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    // 79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok446) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    // -79228162495817593519834398720
    s21_decimal decimal_check = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok447) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    // 7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok448) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    // -7922816249581759351983439872
    s21_decimal decimal_check = {{0x0, 0x80000000, 0x19999999, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok449) {
    // 79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x120000}};
    // 79228162495
    s21_decimal decimal_check = {{0x725DD1BF, 0x12, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok450) {
    // -79228162495.817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80120000}};
    // -79228162496
    s21_decimal decimal_check = {{0x725DD1C0, 0x12, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok451) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    // 7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok452) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok453) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok454) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744073709551615
    s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok455) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674407370955161
    s21_decimal decimal_check = {{0x99999999, 0x19999999, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok456) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674407370955162
    s21_decimal decimal_check = {{0x9999999A, 0x19999999, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok457) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744073709551
    s21_decimal decimal_check = {{0x4BC6A7EF, 0x418937, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok458) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744073709552
    s21_decimal decimal_check = {{0x4BC6A7F0, 0x418937, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok459) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    // 184467440
    s21_decimal decimal_check = {{0xAFEBFF0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok460) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    // -184467441
    s21_decimal decimal_check = {{0xAFEBFF1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok461) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok462) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -185
    s21_decimal decimal_check = {{0xB9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok463) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok464) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok465) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    // 18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok466) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    // -18446744069414584320
    s21_decimal decimal_check = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok467) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    // 1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok468) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    // -1844674406941458432
    s21_decimal decimal_check = {{0x80000000, 0x19999999, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok469) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    // 18446744069414584
    s21_decimal decimal_check = {{0x4B851EB8, 0x418937, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok470) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    // -18446744069414585
    s21_decimal decimal_check = {{0x4B851EB9, 0x418937, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok471) {
    // 18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x90000}};
    // 18446744069
    s21_decimal decimal_check = {{0x4B82FA05, 0x4, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok472) {
    // -18446744069.414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80090000}};
    // -18446744070
    s21_decimal decimal_check = {{0x4B82FA06, 0x4, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok473) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    // 184
    s21_decimal decimal_check = {{0xB8, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok474) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    // -185
    s21_decimal decimal_check = {{0xB9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok475) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok476) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok477) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    // 4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok478) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    // -4294967295
    s21_decimal decimal_check = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok479) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    // 429496729
    s21_decimal decimal_check = {{0x19999999, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok480) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    // -429496730
    s21_decimal decimal_check = {{0x1999999A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok481) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    // 42949672
    s21_decimal decimal_check = {{0x28F5C28, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok482) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    // -42949673
    s21_decimal decimal_check = {{0x28F5C29, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok483) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    // 42949
    s21_decimal decimal_check = {{0xA7C5, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok484) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    // -42950
    s21_decimal decimal_check = {{0xA7C6, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok485) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    // 42
    s21_decimal decimal_check = {{0x2A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok486) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    // -43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok487) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok488) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok489) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok490) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok491) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok492) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok493) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok494) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok495) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok496) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok497) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok498) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok499) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok500) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok501) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok502) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok503) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok504) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok505) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok506) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok507) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    // 12
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok508) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    // -13
    s21_decimal decimal_check = {{0xD, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok509) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    // 123
    s21_decimal decimal_check = {{0x7B, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok510) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    // -124
    s21_decimal decimal_check = {{0x7C, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok511) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    // 1234
    s21_decimal decimal_check = {{0x4D2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok512) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    // -1235
    s21_decimal decimal_check = {{0x4D3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok513) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    // 12345
    s21_decimal decimal_check = {{0x3039, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok514) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    // -12346
    s21_decimal decimal_check = {{0x303A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok515) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    // 123456
    s21_decimal decimal_check = {{0x1E240, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok516) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    // -123457
    s21_decimal decimal_check = {{0x1E241, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok517) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    // 1234567
    s21_decimal decimal_check = {{0x12D687, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok518) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    // -1234568
    s21_decimal decimal_check = {{0x12D688, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok519) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    // 1234567890
    s21_decimal decimal_check = {{0x499602D2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok520) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    // -1234567891
    s21_decimal decimal_check = {{0x499602D3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok521) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    // 12345678901234
    s21_decimal decimal_check = {{0x73CE2FF2, 0xB3A, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok522) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    // -12345678901235
    s21_decimal decimal_check = {{0x73CE2FF3, 0xB3A, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok523) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok524) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    // -99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok525) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok526) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    // -10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok527) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    // 99
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok528) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    // -100
    s21_decimal decimal_check = {{0x64, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok529) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    // 999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok530) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    // -1000
    s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok531) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    // 9999
    s21_decimal decimal_check = {{0x270F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok532) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    // -10000
    s21_decimal decimal_check = {{0x2710, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok533) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    // 99999
    s21_decimal decimal_check = {{0x1869F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok534) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    // -100000
    s21_decimal decimal_check = {{0x186A0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok535) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    // 999999
    s21_decimal decimal_check = {{0xF423F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok536) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    // -1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok537) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    // 9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok538) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    // -10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok539) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    // 99999999
    s21_decimal decimal_check = {{0x5F5E0FF, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok540) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    // -100000000
    s21_decimal decimal_check = {{0x5F5E100, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok541) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    // 999999999
    s21_decimal decimal_check = {{0x3B9AC9FF, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok542) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    // -1000000000
    s21_decimal decimal_check = {{0x3B9ACA00, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok543) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    // 9999999999
    s21_decimal decimal_check = {{0x540BE3FF, 0x2, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok544) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    // -10000000000
    s21_decimal decimal_check = {{0x540BE400, 0x2, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok545) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok546) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok547) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok548) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok549) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok550) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok551) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok552) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok553) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok554) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok555) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok556) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok557) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok558) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok559) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok560) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok561) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok562) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok563) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok564) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok565) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok566) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok567) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok568) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok569) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok570) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok571) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok572) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok573) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok574) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok575) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok576) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok577) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok578) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok579) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    // -0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok580) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok581) {
    // 0.5
    s21_decimal decimal = {{0x5, 0x0, 0x0, 0x10000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok582) {
    // -0.5
    s21_decimal decimal = {{0x5, 0x0, 0x0, 0x80010000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok583) {
    // 0.49
    s21_decimal decimal = {{0x31, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok584) {
    // -0.49
    s21_decimal decimal = {{0x31, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok585) {
    // 0.51
    s21_decimal decimal = {{0x33, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok586) {
    // -0.51
    s21_decimal decimal = {{0x33, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok587) {
    // 0.49999999
    s21_decimal decimal = {{0x2FAF07F, 0x0, 0x0, 0x80000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok588) {
    // -0.49999999
    s21_decimal decimal = {{0x2FAF07F, 0x0, 0x0, 0x80080000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok589) {
    // 0.4999999999999999999999999999
    s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok590) {
    // -0.4999999999999999999999999999
    s21_decimal decimal = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok591) {
    // 0.5000000000000000000000000001
    s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok592) {
    // -0.5000000000000000000000000001
    s21_decimal decimal = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok593) {
    // 0.5000000000000000000000000000
    s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok594) {
    // -0.5000000000000000000000000000
    s21_decimal decimal = {{0x88000000, 0x1F128130, 0x1027E72F, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok595) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok596) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok597) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok598) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok599) {
    // 0.9999999999999999999999999999
    s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok600) {
    // -0.9999999999999999999999999999
    s21_decimal decimal = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok601) {
    // 1.0000000000000000000000000001
    s21_decimal decimal = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok602) {
    // -1.0000000000000000000000000001
    s21_decimal decimal = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok603) {
    // 1.5
    s21_decimal decimal = {{0xF, 0x0, 0x0, 0x10000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok604) {
    // -1.5
    s21_decimal decimal = {{0xF, 0x0, 0x0, 0x80010000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok605) {
    // 1.49
    s21_decimal decimal = {{0x95, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok606) {
    // -1.49
    s21_decimal decimal = {{0x95, 0x0, 0x0, 0x80020000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok607) {
    // 1.51
    s21_decimal decimal = {{0x97, 0x0, 0x0, 0x20000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok608) {
    // -1.51
    s21_decimal decimal = {{0x97, 0x0, 0x0, 0x80020000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok609) {
    // 1.49999999
    s21_decimal decimal = {{0x8F0D17F, 0x0, 0x0, 0x80000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok610) {
    // -1.49999999
    s21_decimal decimal = {{0x8F0D17F, 0x0, 0x0, 0x80080000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok611) {
    // 1.4999999999999999999999999999
    s21_decimal decimal = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok612) {
    // -1.4999999999999999999999999999
    s21_decimal decimal = {{0x97FFFFFF, 0x5D378391, 0x3077B58D, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok613) {
    // 1.5000000000000000000000000001
    s21_decimal decimal = {{0x98000001, 0x5D378391, 0x3077B58D, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok614) {
    // -1.5000000000000000000000000001
    s21_decimal decimal = {{0x98000001, 0x5D378391, 0x3077B58D, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok615) {
    // 1.5000000000000000000000000000
    s21_decimal decimal = {{0x98000000, 0x5D378391, 0x3077B58D, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok616) {
    // -1.5000000000000000000000000000
    s21_decimal decimal = {{0x98000000, 0x5D378391, 0x3077B58D, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok617) {
    // 1.999999
    s21_decimal decimal = {{0x1E847F, 0x0, 0x0, 0x60000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok618) {
    // -1.999999
    s21_decimal decimal = {{0x1E847F, 0x0, 0x0, 0x80060000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok619) {
    // 1.9999999999999999999999999999
    s21_decimal decimal = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok620) {
    // -1.9999999999999999999999999999
    s21_decimal decimal = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok621) {
    // 48360826706.052247521825664051
    s21_decimal decimal = {{0xFCD82C33, 0xE5146451, 0x9C432364, 0x120000}};
    // 48360826706
    s21_decimal decimal_check = {{0x4287A752, 0xB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok622) {
    // -48360826706.052247521825664051
    s21_decimal decimal = {{0xFCD82C33, 0xE5146451, 0x9C432364, 0x80120000}};
    // -48360826707
    s21_decimal decimal_check = {{0x4287A753, 0xB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok623) {
    // -33.921729845517543860643362663
    s21_decimal decimal = {{0xCD08F767, 0xA619619E, 0x6D9B65B3, 0x801B0000}};
    // -34
    s21_decimal decimal_check = {{0x22, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok624) {
    // 33.921729845517543860643362663
    s21_decimal decimal = {{0xCD08F767, 0xA619619E, 0x6D9B65B3, 0x1B0000}};
    // 33
    s21_decimal decimal_check = {{0x21, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok625) {
    // 61967322.371543640386428423394
    s21_decimal decimal = {{0x20CB4CE2, 0xEAB76369, 0xC83A2AEC, 0x150000}};
    // 61967322
    s21_decimal decimal_check = {{0x3B18BDA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok626) {
    // -61967322.371543640386428423394
    s21_decimal decimal = {{0x20CB4CE2, 0xEAB76369, 0xC83A2AEC, 0x80150000}};
    // -61967323
    s21_decimal decimal_check = {{0x3B18BDB, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok627) {
    // 295389308124643275.37602016296
    s21_decimal decimal = {{0xC6A33428, 0xFD179C63, 0x5F7207E7, 0xB0000}};
    // 295389308124643275
    s21_decimal decimal_check = {{0xBD37BFCB, 0x4196F02, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok628) {
    // -295389308124643275.37602016296
    s21_decimal decimal = {{0xC6A33428, 0xFD179C63, 0x5F7207E7, 0x800B0000}};
    // -295389308124643276
    s21_decimal decimal_check = {{0xBD37BFCC, 0x4196F02, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok629) {
    // 357330181.02488316402431952411
    s21_decimal decimal = {{0x570C061B, 0xCF202966, 0x7375A8E8, 0x140000}};
    // 357330181
    s21_decimal decimal_check = {{0x154C6D05, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok630) {
    // -357330181.02488316402431952411
    s21_decimal decimal = {{0x570C061B, 0xCF202966, 0x7375A8E8, 0x80140000}};
    // -357330182
    s21_decimal decimal_check = {{0x154C6D06, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok631) {
    // -5910370664729.8936253057150292
    s21_decimal decimal = {{0x77F12D54, 0x72870651, 0xBEF970B5, 0x80100000}};
    // -5910370664730
    s21_decimal decimal_check = {{0x1D8B411A, 0x560, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok632) {
    // 5910370664729.8936253057150292
    s21_decimal decimal = {{0x77F12D54, 0x72870651, 0xBEF970B5, 0x100000}};
    // 5910370664729
    s21_decimal decimal_check = {{0x1D8B4119, 0x560, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok633) {
    // 12859203424853299754301.588671
    s21_decimal decimal = {{0xE79304BF, 0x7BA29145, 0x298CE23E, 0x60000}};
    // 12859203424853299754301
    s21_decimal decimal_check = {{0xA376F53D, 0x194BE7EC, 0x2B9, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok634) {
    // -12859203424853299754301.588671
    s21_decimal decimal = {{0xE79304BF, 0x7BA29145, 0x298CE23E, 0x80060000}};
    // -12859203424853299754302
    s21_decimal decimal_check = {{0xA376F53E, 0x194BE7EC, 0x2B9, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok635) {
    // -693505482700413.31757497078907
    s21_decimal decimal = {{0x7386547B, 0xDF3A415B, 0xE0156DD2, 0x800E0000}};
    // -693505482700414
    s21_decimal decimal_check = {{0x53F2367E, 0x276BD, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok636) {
    // 693505482700413.31757497078907
    s21_decimal decimal = {{0x7386547B, 0xDF3A415B, 0xE0156DD2, 0xE0000}};
    // 693505482700413
    s21_decimal decimal_check = {{0x53F2367D, 0x276BD, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok637) {
    // -13.420800639975962666166799757
    s21_decimal decimal = {{0x31864D8D, 0x84911E9A, 0x2B5D6D14, 0x801B0000}};
    // -14
    s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok638) {
    // 13.420800639975962666166799757
    s21_decimal decimal = {{0x31864D8D, 0x84911E9A, 0x2B5D6D14, 0x1B0000}};
    // 13
    s21_decimal decimal_check = {{0xD, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok639) {
    // -248140846.98118409217490048071
    s21_decimal decimal = {{0x73C85447, 0xE59F789D, 0x502DBAD2, 0x80140000}};
    // -248140847
    s21_decimal decimal_check = {{0xECA542F, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok640) {
    // 248140846.98118409217490048071
    s21_decimal decimal = {{0x73C85447, 0xE59F789D, 0x502DBAD2, 0x140000}};
    // 248140846
    s21_decimal decimal_check = {{0xECA542E, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok641) {
    // 2991221486048612559449461.7951
    s21_decimal decimal = {{0x55C3C95F, 0xC794AD09, 0x60A6CDE0, 0x40000}};
    // 2991221486048612559449461
    s21_decimal decimal_check = {{0xDFE16D75, 0x7111CE8E, 0x2796A, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok642) {
    // -2991221486048612559449461.7951
    s21_decimal decimal = {{0x55C3C95F, 0xC794AD09, 0x60A6CDE0, 0x80040000}};
    // -2991221486048612559449462
    s21_decimal decimal_check = {{0xDFE16D76, 0x7111CE8E, 0x2796A, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok643) {
    // -29238170.246572049058153344687
    s21_decimal decimal = {{0xFABAEAF, 0xAAE5571, 0x5E793F61, 0x80150000}};
    // -29238171
    s21_decimal decimal_check = {{0x1BE239B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok644) {
    // 29238170.246572049058153344687
    s21_decimal decimal = {{0xFABAEAF, 0xAAE5571, 0x5E793F61, 0x150000}};
    // 29238170
    s21_decimal decimal_check = {{0x1BE239A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok645) {
    // 333808041.64428779864007934180
    s21_decimal decimal = {{0x79880E4, 0xB826DA1F, 0x6BDBF43B, 0x140000}};
    // 333808041
    s21_decimal decimal_check = {{0x13E581A9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok646) {
    // -333808041.64428779864007934180
    s21_decimal decimal = {{0x79880E4, 0xB826DA1F, 0x6BDBF43B, 0x80140000}};
    // -333808042
    s21_decimal decimal_check = {{0x13E581AA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok647) {
    // 718819874417448411237855368.37
    s21_decimal decimal = {{0x5C7AF545, 0x5884B916, 0xE84362EB, 0x20000}};
    // 718819874417448411237855368
    s21_decimal decimal_check = {{0x8B2A3088, 0x793486F8, 0x2529807, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok648) {
    // -718819874417448411237855368.37
    s21_decimal decimal = {{0x5C7AF545, 0x5884B916, 0xE84362EB, 0x80020000}};
    // -718819874417448411237855369
    s21_decimal decimal_check = {{0x8B2A3089, 0x793486F8, 0x2529807, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok649) {
    // 64372082949967202463423.313757
    s21_decimal decimal = {{0xE32EB75D, 0x16ACFB68, 0xCFFF56C9, 0x60000}};
    // 64372082949967202463423
    s21_decimal decimal_check = {{0x268BAEBF, 0x9E1BA115, 0xDA1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok650) {
    // -64372082949967202463423.313757
    s21_decimal decimal = {{0xE32EB75D, 0x16ACFB68, 0xCFFF56C9, 0x80060000}};
    // -64372082949967202463424
    s21_decimal decimal_check = {{0x268BAEC0, 0x9E1BA115, 0xDA1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok651) {
    // -449956197874944932372809398.5
    s21_decimal decimal = {{0x39A04321, 0xA131D147, 0xE89F34F, 0x80010000}};
    // -449956197874944932372809399
    s21_decimal decimal_check = {{0x529006B7, 0x5CEB61BA, 0x17431EE, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok652) {
    // 449956197874944932372809398.5
    s21_decimal decimal = {{0x39A04321, 0xA131D147, 0xE89F34F, 0x10000}};
    // 449956197874944932372809398
    s21_decimal decimal_check = {{0x529006B6, 0x5CEB61BA, 0x17431EE, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok653) {
    // -73860624893714339171759667544
    s21_decimal decimal = {{0xB7B5B958, 0x8B8BBA55, 0xEEA813B2, 0x80000000}};
    // -73860624893714339171759667544
    s21_decimal decimal_check = {{0xB7B5B958, 0x8B8BBA55, 0xEEA813B2, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok654) {
    // 73860624893714339171759667544
    s21_decimal decimal = {{0xB7B5B958, 0x8B8BBA55, 0xEEA813B2, 0x0}};
    // 73860624893714339171759667544
    s21_decimal decimal_check = {{0xB7B5B958, 0x8B8BBA55, 0xEEA813B2, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok655) {
    // -78.386864575674853298141000463
    s21_decimal decimal = {{0x8ECDF30F, 0x5D1A79AF, 0xFD48183B, 0x801B0000}};
    // -79
    s21_decimal decimal_check = {{0x4F, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok656) {
    // 78.386864575674853298141000463
    s21_decimal decimal = {{0x8ECDF30F, 0x5D1A79AF, 0xFD48183B, 0x1B0000}};
    // 78
    s21_decimal decimal_check = {{0x4E, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok657) {
    // -7620149204445128216634289.0070
    s21_decimal decimal = {{0x2C063256, 0xFC19E8E, 0xF6386599, 0x80040000}};
    // -7620149204445128216634290
    s21_decimal decimal_check = {{0xCB1D63B2, 0x1DB92209, 0x64DA1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok658) {
    // 7620149204445128216634289.0070
    s21_decimal decimal = {{0x2C063256, 0xFC19E8E, 0xF6386599, 0x40000}};
    // 7620149204445128216634289
    s21_decimal decimal_check = {{0xCB1D63B1, 0x1DB92209, 0x64DA1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok659) {
    // -693464066970301624.46613216306
    s21_decimal decimal = {{0xCEF3FC32, 0xBFC9B91D, 0xE01200CF, 0x800B0000}};
    // -693464066970301625
    s21_decimal decimal_check = {{0x104334B9, 0x99FADE5, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok660) {
    // 693464066970301624.46613216306
    s21_decimal decimal = {{0xCEF3FC32, 0xBFC9B91D, 0xE01200CF, 0xB0000}};
    // 693464066970301624
    s21_decimal decimal_check = {{0x104334B8, 0x99FADE5, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok661) {
    // -1948861638451.1734349398087077
    s21_decimal decimal = {{0xDA3D15A5, 0x242666C8, 0x3EF89B0B, 0x80100000}};
    // -1948861638452
    s21_decimal decimal_check = {{0xC134A734, 0x1C5, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok662) {
    // 1948861638451.1734349398087077
    s21_decimal decimal = {{0xDA3D15A5, 0x242666C8, 0x3EF89B0B, 0x100000}};
    // 1948861638451
    s21_decimal decimal_check = {{0xC134A733, 0x1C5, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok663) {
    // -2796367648052895.0753053774049
    s21_decimal decimal = {{0x207210E1, 0x8B270D93, 0x5A5B02D3, 0x800D0000}};
    // -2796367648052896
    s21_decimal decimal_check = {{0x1452D6A0, 0x9EF48, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok664) {
    // 2796367648052895.0753053774049
    s21_decimal decimal = {{0x207210E1, 0x8B270D93, 0x5A5B02D3, 0xD0000}};
    // 2796367648052895
    s21_decimal decimal_check = {{0x1452D69F, 0x9EF48, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok665) {
    // 42496606040.694761976605278065
    s21_decimal decimal = {{0x59617F71, 0xA10C4733, 0x89505E5D, 0x120000}};
    // 42496606040
    s21_decimal decimal_check = {{0xE4FEBF58, 0x9, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok666) {
    // -42496606040.694761976605278065
    s21_decimal decimal = {{0x59617F71, 0xA10C4733, 0x89505E5D, 0x80120000}};
    // -42496606041
    s21_decimal decimal_check = {{0xE4FEBF59, 0x9, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok667) {
    // -50827240029249572959212004.757
    s21_decimal decimal = {{0xD2B3E595, 0xEC754AF, 0xA43B4EBB, 0x80030000}};
    // -50827240029249572959212005
    s21_decimal decimal_check = {{0x74B0D1E5, 0x33FB9761, 0x2A0B16, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok668) {
    // 50827240029249572959212004.757
    s21_decimal decimal = {{0xD2B3E595, 0xEC754AF, 0xA43B4EBB, 0x30000}};
    // 50827240029249572959212004
    s21_decimal decimal_check = {{0x74B0D1E4, 0x33FB9761, 0x2A0B16, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok669) {
    // 54974115450986514.507351620987
    s21_decimal decimal = {{0x761E7D7B, 0x1F15C25A, 0xB1A185C2, 0xC0000}};
    // 54974115450986514
    s21_decimal decimal_check = {{0xAF4C2012, 0xC34EAA, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok670) {
    // -54974115450986514.507351620987
    s21_decimal decimal = {{0x761E7D7B, 0x1F15C25A, 0xB1A185C2, 0x800C0000}};
    // -54974115450986515
    s21_decimal decimal_check = {{0xAF4C2013, 0xC34EAA, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok671) {
    // 69556831074535822886977.537409
    s21_decimal decimal = {{0xE91A0581, 0x1C6729D3, 0xE0C00FE8, 0x60000}};
    // 69556831074535822886977
    s21_decimal decimal_check = {{0xA7E88841, 0xAEF13667, 0xEBA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok672) {
    // -69556831074535822886977.537409
    s21_decimal decimal = {{0xE91A0581, 0x1C6729D3, 0xE0C00FE8, 0x80060000}};
    // -69556831074535822886978
    s21_decimal decimal_check = {{0xA7E88842, 0xAEF13667, 0xEBA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok673) {
    // 5046504722835423612.8309708197
    s21_decimal decimal = {{0x77F285A5, 0xFA6F66BD, 0xA30FB56B, 0xA0000}};
    // 5046504722835423612
    s21_decimal decimal_check = {{0xD1EFC17C, 0x4608C94E, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok674) {
    // -5046504722835423612.8309708197
    s21_decimal decimal = {{0x77F285A5, 0xFA6F66BD, 0xA30FB56B, 0x800A0000}};
    // -5046504722835423613
    s21_decimal decimal_check = {{0xD1EFC17D, 0x4608C94E, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok675) {
    // -11611360338364982226927490878
    s21_decimal decimal = {{0x1F60173E, 0x37E6E2A0, 0x2584B131, 0x80000000}};
    // -11611360338364982226927490878
    s21_decimal decimal_check = {{0x1F60173E, 0x37E6E2A0, 0x2584B131, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok676) {
    // 11611360338364982226927490878
    s21_decimal decimal = {{0x1F60173E, 0x37E6E2A0, 0x2584B131, 0x0}};
    // 11611360338364982226927490878
    s21_decimal decimal_check = {{0x1F60173E, 0x37E6E2A0, 0x2584B131, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok677) {
    // 69.731861305602864417862499930
    s21_decimal decimal = {{0xE3AEBE5A, 0xF31AA77B, 0xE150D7FF, 0x1B0000}};
    // 69
    s21_decimal decimal_check = {{0x45, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok678) {
    // -69.731861305602864417862499930
    s21_decimal decimal = {{0xE3AEBE5A, 0xF31AA77B, 0xE150D7FF, 0x801B0000}};
    // -70
    s21_decimal decimal_check = {{0x46, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok679) {
    // 480554.15961587115362844735997
    s21_decimal decimal = {{0x2F4CF9FD, 0x432A78F4, 0x9B468227, 0x170000}};
    // 480554
    s21_decimal decimal_check = {{0x7552A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok680) {
    // -480554.15961587115362844735997
    s21_decimal decimal = {{0x2F4CF9FD, 0x432A78F4, 0x9B468227, 0x80170000}};
    // -480555
    s21_decimal decimal_check = {{0x7552B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok681) {
    // -206.87278524606820653610597187
    s21_decimal decimal = {{0xEE447B43, 0xF5A67F3A, 0x42D81D9F, 0x801A0000}};
    // -207
    s21_decimal decimal_check = {{0xCF, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok682) {
    // 206.87278524606820653610597187
    s21_decimal decimal = {{0xEE447B43, 0xF5A67F3A, 0x42D81D9F, 0x1A0000}};
    // 206
    s21_decimal decimal_check = {{0xCE, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok683) {
    // -274690341602.6381163614297876
    s21_decimal decimal = {{0x90DDDF14, 0x902CBF5C, 0x8E02F6C, 0x80100000}};
    // -274690341603
    s21_decimal decimal_check = {{0xF4D1FAE3, 0x3F, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok684) {
    // 274690341602.6381163614297876
    s21_decimal decimal = {{0x90DDDF14, 0x902CBF5C, 0x8E02F6C, 0x100000}};
    // 274690341602
    s21_decimal decimal_check = {{0xF4D1FAE2, 0x3F, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok685) {
    // -4592.6536165278386628939355028
    s21_decimal decimal = {{0x289A1394, 0x41A66D80, 0x94658A52, 0x80190000}};
    // -4593
    s21_decimal decimal_check = {{0x11F1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok686) {
    // 4592.6536165278386628939355028
    s21_decimal decimal = {{0x289A1394, 0x41A66D80, 0x94658A52, 0x190000}};
    // 4592
    s21_decimal decimal_check = {{0x11F0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok687) {
    // -340266589799020883.93164322588
    s21_decimal decimal = {{0xBB3BF71C, 0x6BF20C75, 0x6DF2314F, 0x800B0000}};
    // -340266589799020884
    s21_decimal decimal_check = {{0x1DE77954, 0x4B8DEA9, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok688) {
    // 340266589799020883.93164322588
    s21_decimal decimal = {{0xBB3BF71C, 0x6BF20C75, 0x6DF2314F, 0xB0000}};
    // 340266589799020883
    s21_decimal decimal_check = {{0x1DE77953, 0x4B8DEA9, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok689) {
    // -5867217451199157.6055823080097
    s21_decimal decimal = {{0xF07A1AA1, 0x847A93D6, 0xBD947C39, 0x800D0000}};
    // -5867217451199158
    s21_decimal decimal_check = {{0x3FFAAB6, 0x14D834, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok690) {
    // 5867217451199157.6055823080097
    s21_decimal decimal = {{0xF07A1AA1, 0x847A93D6, 0xBD947C39, 0xD0000}};
    // 5867217451199157
    s21_decimal decimal_check = {{0x3FFAAB5, 0x14D834, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok691) {
    // 209.78512106208732837426437097
    s21_decimal decimal = {{0xA52B1BE9, 0xDA1AC1C, 0x43C904BC, 0x1A0000}};
    // 209
    s21_decimal decimal_check = {{0xD1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok692) {
    // -209.78512106208732837426437097
    s21_decimal decimal = {{0xA52B1BE9, 0xDA1AC1C, 0x43C904BC, 0x801A0000}};
    // -210
    s21_decimal decimal_check = {{0xD2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok693) {
    // -70432.178945374148089049995715
    s21_decimal decimal = {{0x389B59C3, 0x45EB601D, 0xE3942207, 0x80180000}};
    // -70433
    s21_decimal decimal_check = {{0x11321, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok694) {
    // 70432.178945374148089049995715
    s21_decimal decimal = {{0x389B59C3, 0x45EB601D, 0xE3942207, 0x180000}};
    // 70432
    s21_decimal decimal_check = {{0x11320, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok695) {
    // -4773470136.605891588059185265
    s21_decimal decimal = {{0xDA8A4071, 0x9EC17262, 0xF6C859E, 0x80120000}};
    // -4773470137
    s21_decimal decimal_check = {{0x1C855FB9, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok696) {
    // 4773470136.605891588059185265
    s21_decimal decimal = {{0xDA8A4071, 0x9EC17262, 0xF6C859E, 0x120000}};
    // 4773470136
    s21_decimal decimal_check = {{0x1C855FB8, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok697) {
    // 0.003629609399653407744263156
    s21_decimal decimal = {{0x40E303F4, 0x8512D9FE, 0x30099, 0x1B0000}};
    // 0
    s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok698) {
    // -0.003629609399653407744263156
    s21_decimal decimal = {{0x40E303F4, 0x8512D9FE, 0x30099, 0x801B0000}};
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok699) {
    // 40783941947.021942753010569206
    s21_decimal decimal = {{0x86A2CFF6, 0x12FE640C, 0x83C7AFA3, 0x120000}};
    // 40783941947
    s21_decimal decimal_check = {{0x7EE9913B, 0x9, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok700) {
    // -40783941947.021942753010569206
    s21_decimal decimal = {{0x86A2CFF6, 0x12FE640C, 0x83C7AFA3, 0x80120000}};
    // -40783941948
    s21_decimal decimal_check = {{0x7EE9913C, 0x9, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok701) {
    // 48984213329.377379268759321362
    s21_decimal decimal = {{0xBEA2FB12, 0x75D0D7C4, 0x9E46CAA5, 0x120000}};
    // 48984213329
    s21_decimal decimal_check = {{0x67AFC751, 0xB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok702) {
    // -48984213329.377379268759321362
    s21_decimal decimal = {{0xBEA2FB12, 0x75D0D7C4, 0x9E46CAA5, 0x80120000}};
    // -48984213330
    s21_decimal decimal_check = {{0x67AFC752, 0xB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok703) {
    // -74992760089012.355264838704144
    s21_decimal decimal = {{0x50951C10, 0x75A67759, 0xF2508EA6, 0x800F0000}};
    // -74992760089013
    s21_decimal decimal_check = {{0x9CD369B5, 0x4434, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok704) {
    // 74992760089012.355264838704144
    s21_decimal decimal = {{0x50951C10, 0x75A67759, 0xF2508EA6, 0xF0000}};
    // 74992760089012
    s21_decimal decimal_check = {{0x9CD369B4, 0x4434, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok705) {
    // 44303850317791258046933.776877
    s21_decimal decimal = {{0x423C39ED, 0x337AEC2D, 0x8F27493A, 0x60000}};
    // 44303850317791258046933
    s21_decimal decimal_check = {{0x8FD71D5, 0xB76F0C2C, 0x961, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok706) {
    // -44303850317791258046933.776877
    s21_decimal decimal = {{0x423C39ED, 0x337AEC2D, 0x8F27493A, 0x80060000}};
    // -44303850317791258046934
    s21_decimal decimal_check = {{0x8FD71D6, 0xB76F0C2C, 0x961, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok707) {
    // 747540383931438132045.69866364
    s21_decimal decimal = {{0x42A9C07C, 0x6543D803, 0xF18B175D, 0x80000}};
    // 747540383931438132045
    s21_decimal decimal_check = {{0x47EEB4D, 0x8634F28C, 0x28, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok708) {
    // -747540383931438132045.69866364
    s21_decimal decimal = {{0x42A9C07C, 0x6543D803, 0xF18B175D, 0x80080000}};
    // -747540383931438132046
    s21_decimal decimal_check = {{0x47EEB4E, 0x8634F28C, 0x28, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok709) {
    // -47363900506.06836019809566272
    s21_decimal decimal = {{0x6EF13E40, 0x215D80CF, 0xF4DD99B, 0x80110000}};
    // -47363900507
    s21_decimal decimal_check = {{0x71BC45B, 0xB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok710) {
    // 47363900506.06836019809566272
    s21_decimal decimal = {{0x6EF13E40, 0x215D80CF, 0xF4DD99B, 0x110000}};
    // 47363900506
    s21_decimal decimal_check = {{0x71BC45A, 0xB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok711) {
    // -6340107908508531374338791042.3
    s21_decimal decimal = {{0x59AC6117, 0x1946F152, 0xCCDC24B8, 0x80010000}};
    // -6340107908508531374338791043
    s21_decimal decimal_check = {{0x3C2AD683, 0x68ED7E88, 0x147C6A12, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok712) {
    // 6340107908508531374338791042.3
    s21_decimal decimal = {{0x59AC6117, 0x1946F152, 0xCCDC24B8, 0x10000}};
    // 6340107908508531374338791042
    s21_decimal decimal_check = {{0x3C2AD682, 0x68ED7E88, 0x147C6A12, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok713) {
    // 721520051820949966870.94131620
    s21_decimal decimal = {{0xFF4DABA4, 0x617185CA, 0xE922BD66, 0x80000}};
    // 721520051820949966870
    s21_decimal decimal_check = {{0xA5289016, 0x1D1A285A, 0x27, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok714) {
    // -721520051820949966870.94131620
    s21_decimal decimal = {{0xFF4DABA4, 0x617185CA, 0xE922BD66, 0x80080000}};
    // -721520051820949966871
    s21_decimal decimal_check = {{0xA5289017, 0x1D1A285A, 0x27, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok715) {
    // 4993.6661393559203746804846493
    s21_decimal decimal = {{0x2902CF9D, 0x7A7EAB09, 0xA15AA35E, 0x190000}};
    // 4993
    s21_decimal decimal_check = {{0x1381, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok716) {
    // -4993.6661393559203746804846493
    s21_decimal decimal = {{0x2902CF9D, 0x7A7EAB09, 0xA15AA35E, 0x80190000}};
    // -4994
    s21_decimal decimal_check = {{0x1382, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok717) {
    // -74749350124.353529865952471028
    s21_decimal decimal = {{0xCDC6A7F4, 0xD5CEB5F0, 0xF1873695, 0x80120000}};
    // -74749350125
    s21_decimal decimal_check = {{0x676890ED, 0x11, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok718) {
    // 74749350124.353529865952471028
    s21_decimal decimal = {{0xCDC6A7F4, 0xD5CEB5F0, 0xF1873695, 0x120000}};
    // 74749350124
    s21_decimal decimal_check = {{0x676890EC, 0x11, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok719) {
    // -1827.5370620038439324865176887
    s21_decimal decimal = {{0x2C6EA537, 0x760F5AFE, 0x3B0D0842, 0x80190000}};
    // -1828
    s21_decimal decimal_check = {{0x724, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok720) {
    // 1827.5370620038439324865176887
    s21_decimal decimal = {{0x2C6EA537, 0x760F5AFE, 0x3B0D0842, 0x190000}};
    // 1827
    s21_decimal decimal_check = {{0x723, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok721) {
    // 727839308012512.3885293016376
    s21_decimal decimal = {{0xAE9538, 0x7BD77021, 0x17848BAF, 0xD0000}};
    // 727839308012512
    s21_decimal decimal_check = {{0x4B685BE0, 0x295F7, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok722) {
    // -727839308012512.3885293016376
    s21_decimal decimal = {{0xAE9538, 0x7BD77021, 0x17848BAF, 0x800D0000}};
    // -727839308012513
    s21_decimal decimal_check = {{0x4B685BE1, 0x295F7, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok723) {
    // 3294298090731510846.1927066857
    s21_decimal decimal = {{0xBCADECE9, 0x649A1F77, 0x6A71CB8D, 0xA0000}};
    // 3294298090731510846
    s21_decimal decimal_check = {{0xDA4C9C3E, 0x2DB7B2A8, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok724) {
    // -3294298090731510846.1927066857
    s21_decimal decimal = {{0xBCADECE9, 0x649A1F77, 0x6A71CB8D, 0x800A0000}};
    // -3294298090731510847
    s21_decimal decimal_check = {{0xDA4C9C3F, 0x2DB7B2A8, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok725) {
    // -788144810186.16194781419374178
    s21_decimal decimal = {{0x409B8662, 0x2F603171, 0xFEA9CF89, 0x80110000}};
    // -788144810187
    s21_decimal decimal_check = {{0x811768CB, 0xB7, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok726) {
    // 788144810186.16194781419374178
    s21_decimal decimal = {{0x409B8662, 0x2F603171, 0xFEA9CF89, 0x110000}};
    // 788144810186
    s21_decimal decimal_check = {{0x811768CA, 0xB7, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok727) {
    // 25543691340252202756590996.98
    s21_decimal decimal = {{0xC0C44E32, 0x38D530AC, 0x840ECB4, 0x20000}};
    // 25543691340252202756590996
    s21_decimal decimal_check = {{0x20A5CD94, 0x483F9268, 0x152116, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok728) {
    // -25543691340252202756590996.98
    s21_decimal decimal = {{0xC0C44E32, 0x38D530AC, 0x840ECB4, 0x80020000}};
    // -25543691340252202756590997
    s21_decimal decimal_check = {{0x20A5CD95, 0x483F9268, 0x152116, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok729) {
    // 22461263755373730797.837645518
    s21_decimal decimal = {{0x760876CE, 0x46E2973, 0x4893859C, 0x90000}};
    // 22461263755373730797
    s21_decimal decimal_check = {{0x71685BED, 0x37B67061, 0x1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok730) {
    // -22461263755373730797.837645518
    s21_decimal decimal = {{0x760876CE, 0x46E2973, 0x4893859C, 0x80090000}};
    // -22461263755373730798
    s21_decimal decimal_check = {{0x71685BEE, 0x37B67061, 0x1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok731) {
    // -6216950988.2715826627919969716
    s21_decimal decimal = {{0x59977DB4, 0xDC277188, 0xC8E169CB, 0x80130000}};
    // -6216950989
    s21_decimal decimal_check = {{0x728F24CD, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok732) {
    // 6216950988.2715826627919969716
    s21_decimal decimal = {{0x59977DB4, 0xDC277188, 0xC8E169CB, 0x130000}};
    // 6216950988
    s21_decimal decimal_check = {{0x728F24CC, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok733) {
    // 22035420107913.407414138047632
    s21_decimal decimal = {{0x4F340C90, 0xA1AB92A5, 0x473345B5, 0xF0000}};
    // 22035420107913
    s21_decimal decimal_check = {{0x85635489, 0x140A, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok734) {
    // -22035420107913.407414138047632
    s21_decimal decimal = {{0x4F340C90, 0xA1AB92A5, 0x473345B5, 0x800F0000}};
    // -22035420107914
    s21_decimal decimal_check = {{0x8563548A, 0x140A, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok735) {
    // -192989208538971997045050.83183
    s21_decimal decimal = {{0x20D0652F, 0xD230D338, 0x3E5BB173, 0x80050000}};
    // -192989208538971997045051
    s21_decimal decimal_check = {{0xB909813B, 0xF749098B, 0x28DD, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok736) {
    // 192989208538971997045050.83183
    s21_decimal decimal = {{0x20D0652F, 0xD230D338, 0x3E5BB173, 0x50000}};
    // 192989208538971997045050
    s21_decimal decimal_check = {{0xB909813A, 0xF749098B, 0x28DD, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok737) {
    // 5583719166.3646146995190774861
    s21_decimal decimal = {{0xA3643C4D, 0x5C58F731, 0xB46B7141, 0x130000}};
    // 5583719166
    s21_decimal decimal_check = {{0x4CD0CAFE, 0x1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok738) {
    // -5583719166.3646146995190774861
    s21_decimal decimal = {{0xA3643C4D, 0x5C58F731, 0xB46B7141, 0x80130000}};
    // -5583719167
    s21_decimal decimal_check = {{0x4CD0CAFF, 0x1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok739) {
    // -22072850000.005960892090296676
    s21_decimal decimal = {{0xBED62964, 0x25CCD074, 0x47523BCC, 0x80120000}};
    // -22072850001
    s21_decimal decimal_check = {{0x23A4F651, 0x5, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok740) {
    // 22072850000.005960892090296676
    s21_decimal decimal = {{0xBED62964, 0x25CCD074, 0x47523BCC, 0x120000}};
    // 22072850000
    s21_decimal decimal_check = {{0x23A4F650, 0x5, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok741) {
    // 246682741649029088483.88668926
    s21_decimal decimal = {{0xB4137DFE, 0xD839175, 0x4FB51E3E, 0x80000}};
    // 246682741649029088483
    s21_decimal decimal_check = {{0x71D644E3, 0x5F69268C, 0xD, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok742) {
    // -246682741649029088483.88668926
    s21_decimal decimal = {{0xB4137DFE, 0xD839175, 0x4FB51E3E, 0x80080000}};
    // -246682741649029088484
    s21_decimal decimal_check = {{0x71D644E4, 0x5F69268C, 0xD, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok743) {
    // 46692265.898979131501721460545
    s21_decimal decimal = {{0x48E89F41, 0x4C155437, 0x96DEEFE6, 0x150000}};
    // 46692265
    s21_decimal decimal_check = {{0x2C877A9, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok744) {
    // -46692265.898979131501721460545
    s21_decimal decimal = {{0x48E89F41, 0x4C155437, 0x96DEEFE6, 0x80150000}};
    // -46692266
    s21_decimal decimal_check = {{0x2C877AA, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok745) {
    // 109786560747366680212.45447421
    s21_decimal decimal = {{0x8AA18CFD, 0x5C2B2CD4, 0x237954DA, 0x80000}};
    // 109786560747366680212
    s21_decimal decimal_check = {{0x5AA28694, 0xF3983753, 0x5, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok746) {
    // -109786560747366680212.45447421
    s21_decimal decimal = {{0x8AA18CFD, 0x5C2B2CD4, 0x237954DA, 0x80080000}};
    // -109786560747366680213
    s21_decimal decimal_check = {{0x5AA28695, 0xF3983753, 0x5, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok747) {
    // 654620.30797470594473789462819
    s21_decimal decimal = {{0xEA8F9923, 0x4BE971FD, 0xD384EC38, 0x170000}};
    // 654620
    s21_decimal decimal_check = {{0x9FD1C, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok748) {
    // -654620.30797470594473789462819
    s21_decimal decimal = {{0xEA8F9923, 0x4BE971FD, 0xD384EC38, 0x80170000}};
    // -654621
    s21_decimal decimal_check = {{0x9FD1D, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok749) {
    // 600.43488288714866508073388568
    s21_decimal decimal = {{0x5009CA18, 0x4FC6FCCA, 0xC202CF36, 0x1A0000}};
    // 600
    s21_decimal decimal_check = {{0x258, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok750) {
    // -600.43488288714866508073388568
    s21_decimal decimal = {{0x5009CA18, 0x4FC6FCCA, 0xC202CF36, 0x801A0000}};
    // -601
    s21_decimal decimal_check = {{0x259, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok751) {
    // -114392.25740877630921430965635
    s21_decimal decimal = {{0xEA7A9D83, 0xFD96C101, 0x24F64E45, 0x80170000}};
    // -114393
    s21_decimal decimal_check = {{0x1BED9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok752) {
    // 114392.25740877630921430965635
    s21_decimal decimal = {{0xEA7A9D83, 0xFD96C101, 0x24F64E45, 0x170000}};
    // 114392
    s21_decimal decimal_check = {{0x1BED8, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok753) {
    // -13627740797945300616195.097536
    s21_decimal decimal = {{0xAE1843C0, 0xF5C7EC47, 0x2C089A5C, 0x80060000}};
    // -13627740797945300616196
    s21_decimal decimal_check = {{0xB4078404, 0xC2E524DD, 0x2E2, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok754) {
    // 13627740797945300616195.097536
    s21_decimal decimal = {{0xAE1843C0, 0xF5C7EC47, 0x2C089A5C, 0x60000}};
    // 13627740797945300616195
    s21_decimal decimal_check = {{0xB4078403, 0xC2E524DD, 0x2E2, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok755) {
    // 2496843545332974834370252.0621
    s21_decimal decimal = {{0x217D832D, 0x1A6BFBBE, 0x50AD67DE, 0x40000}};
    // 2496843545332974834370252
    s21_decimal decimal_check = {{0x579B46CC, 0x28E95446, 0x210BA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok756) {
    // -2496843545332974834370252.0621
    s21_decimal decimal = {{0x217D832D, 0x1A6BFBBE, 0x50AD67DE, 0x80040000}};
    // -2496843545332974834370253
    s21_decimal decimal_check = {{0x579B46CD, 0x28E95446, 0x210BA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok757) {
    // -5113227213564282705293919472.8
    s21_decimal decimal = {{0x8A2FB168, 0xADDFF96F, 0xA5379FCA, 0x80010000}};
    // -5113227213564282705293919473
    s21_decimal decimal_check = {{0xC104C4F1, 0xAAFCCC24, 0x10858FFA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok758) {
    // 5113227213564282705293919472.8
    s21_decimal decimal = {{0x8A2FB168, 0xADDFF96F, 0xA5379FCA, 0x10000}};
    // 5113227213564282705293919472
    s21_decimal decimal_check = {{0xC104C4F0, 0xAAFCCC24, 0x10858FFA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok759) {
    // -278109204418823661625895092.3
    s21_decimal decimal = {{0x4986170B, 0xCF3ECB9F, 0x8FC7725, 0x80010000}};
    // -278109204418823661625895093
    s21_decimal decimal_check = {{0xBA8D68B5, 0x2E53145C, 0xE60BEA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok760) {
    // 278109204418823661625895092.3
    s21_decimal decimal = {{0x4986170B, 0xCF3ECB9F, 0x8FC7725, 0x10000}};
    // 278109204418823661625895092
    s21_decimal decimal_check = {{0xBA8D68B4, 0x2E53145C, 0xE60BEA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok761) {
    // 2858991.0663632026106155001473
    s21_decimal decimal = {{0xC7E06681, 0xA241CE6D, 0x5C610512, 0x160000}};
    // 2858991
    s21_decimal decimal_check = {{0x2B9FEF, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok762) {
    // -2858991.0663632026106155001473
    s21_decimal decimal = {{0xC7E06681, 0xA241CE6D, 0x5C610512, 0x80160000}};
    // -2858992
    s21_decimal decimal_check = {{0x2B9FF0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok763) {
    // 3728547114886.6434319459762720
    s21_decimal decimal = {{0x6BCB4220, 0x165B35AF, 0x7879D1A1, 0x100000}};
    // 3728547114886
    s21_decimal decimal_check = {{0x1EB9EF86, 0x364, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok764) {
    // -3728547114886.6434319459762720
    s21_decimal decimal = {{0x6BCB4220, 0x165B35AF, 0x7879D1A1, 0x80100000}};
    // -3728547114887
    s21_decimal decimal_check = {{0x1EB9EF87, 0x364, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok765) {
    // 2459778590120103659356802.746
    s21_decimal decimal = {{0x25E7CEBA, 0x8FE44D90, 0x7F2AE60, 0x30000}};
    // 2459778590120103659356802
    s21_decimal decimal_check = {{0xB236C282, 0xDD53F0B7, 0x208E0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok766) {
    // -2459778590120103659356802.746
    s21_decimal decimal = {{0x25E7CEBA, 0x8FE44D90, 0x7F2AE60, 0x80030000}};
    // -2459778590120103659356803
    s21_decimal decimal_check = {{0xB236C283, 0xDD53F0B7, 0x208E0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok767) {
    // -1311498534527423378820679.3983
    s21_decimal decimal = {{0x10DDC4FF, 0x2C4FE189, 0x2A60762C, 0x80040000}};
    // -1311498534527423378820680
    s21_decimal decimal_check = {{0xBF1B0E48, 0x7A5F57A6, 0x115B8, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok768) {
    // 1311498534527423378820679.3983
    s21_decimal decimal = {{0x10DDC4FF, 0x2C4FE189, 0x2A60762C, 0x40000}};
    // 1311498534527423378820679
    s21_decimal decimal_check = {{0xBF1B0E47, 0x7A5F57A6, 0x115B8, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok769) {
    // 61183593741588.565649501783793
    s21_decimal decimal = {{0x95A106F1, 0xC14A6B14, 0xC5B1E1EE, 0xF0000}};
    // 61183593741588
    s21_decimal decimal_check = {{0x6A5EFD14, 0x37A5, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok770) {
    // -61183593741588.565649501783793
    s21_decimal decimal = {{0x95A106F1, 0xC14A6B14, 0xC5B1E1EE, 0x800F0000}};
    // -61183593741589
    s21_decimal decimal_check = {{0x6A5EFD15, 0x37A5, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok771) {
    // 6.8584154440702980259657579932
    s21_decimal decimal = {{0xDD207D9C, 0x227398E6, 0xDD9B7B9E, 0x1C0000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok772) {
    // -6.8584154440702980259657579932
    s21_decimal decimal = {{0xDD207D9C, 0x227398E6, 0xDD9B7B9E, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok773) {
    // -24665952940976545003461.36759
    s21_decimal decimal = {{0xB89188B7, 0xD33DAE7F, 0x7F851DE, 0x80050000}};
    // -24665952940976545003462
    s21_decimal decimal_check = {{0xA0A4F7C6, 0x24DC69FF, 0x539, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok774) {
    // 24665952940976545003461.36759
    s21_decimal decimal = {{0xB89188B7, 0xD33DAE7F, 0x7F851DE, 0x50000}};
    // 24665952940976545003461
    s21_decimal decimal_check = {{0xA0A4F7C5, 0x24DC69FF, 0x539, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok775) {
    // -2.6355282507020981429588039156
    s21_decimal decimal = {{0x53C595F4, 0x8770FFF9, 0x55289427, 0x801C0000}};
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok776) {
    // 2.6355282507020981429588039156
    s21_decimal decimal = {{0x53C595F4, 0x8770FFF9, 0x55289427, 0x1C0000}};
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok777) {
    // -635332607358654853667.63866470
    s21_decimal decimal = {{0x3DE4966, 0xBEE416DC, 0xCD497B45, 0x80080000}};
    // -635332607358654853668
    s21_decimal decimal_check = {{0x9B59B224, 0x7102D841, 0x22, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok778) {
    // 635332607358654853667.63866470
    s21_decimal decimal = {{0x3DE4966, 0xBEE416DC, 0xCD497B45, 0x80000}};
    // 635332607358654853667
    s21_decimal decimal_check = {{0x9B59B223, 0x7102D841, 0x22, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok779) {
    // 43.568442439785181850741866416
    s21_decimal decimal = {{0x4E497FB0, 0x405115EA, 0x8CC6F88D, 0x1B0000}};
    // 43
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok780) {
    // -43.568442439785181850741866416
    s21_decimal decimal = {{0x4E497FB0, 0x405115EA, 0x8CC6F88D, 0x801B0000}};
    // -44
    s21_decimal decimal_check = {{0x2C, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok781) {
    // 5715204266013793567030.3907431
    s21_decimal decimal = {{0x3A61DE67, 0xB48DD00C, 0xB8AB0FC8, 0x70000}};
    // 5715204266013793567030
    s21_decimal decimal_check = {{0x5545C136, 0xD2645F7D, 0x135, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok782) {
    // -5715204266013793567030.3907431
    s21_decimal decimal = {{0x3A61DE67, 0xB48DD00C, 0xB8AB0FC8, 0x80070000}};
    // -5715204266013793567031
    s21_decimal decimal_check = {{0x5545C137, 0xD2645F7D, 0x135, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok783) {
    // -57416009170059739003.108528415
    s21_decimal decimal = {{0xCF8D111F, 0xE19E3B45, 0xB98568DD, 0x80090000}};
    // -57416009170059739004
    s21_decimal decimal_check = {{0x19FB3F7C, 0x1CCEA423, 0x3, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok784) {
    // 57416009170059739003.108528415
    s21_decimal decimal = {{0xCF8D111F, 0xE19E3B45, 0xB98568DD, 0x90000}};
    // 57416009170059739003
    s21_decimal decimal_check = {{0x19FB3F7B, 0x1CCEA423, 0x3, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok785) {
    // -100902087775027460080498951.73
    s21_decimal decimal = {{0x40934705, 0xDEBAE2CC, 0x209A6CD1, 0x80020000}};
    // -100902087775027460080498952
    s21_decimal decimal_check = {{0x90017908, 0x2381DE6D, 0x5376D9, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok786) {
    // 100902087775027460080498951.73
    s21_decimal decimal = {{0x40934705, 0xDEBAE2CC, 0x209A6CD1, 0x20000}};
    // 100902087775027460080498951
    s21_decimal decimal_check = {{0x90017907, 0x2381DE6D, 0x5376D9, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok787) {
    // 495632491595345329368030.69298
    s21_decimal decimal = {{0xB6A0AD72, 0xB5DBC42B, 0xA025C240, 0x50000}};
    // 495632491595345329368030
    s21_decimal decimal_check = {{0x61D7ABDE, 0x4A8C8C7B, 0x68F4, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok788) {
    // -495632491595345329368030.69298
    s21_decimal decimal = {{0xB6A0AD72, 0xB5DBC42B, 0xA025C240, 0x80050000}};
    // -495632491595345329368031
    s21_decimal decimal_check = {{0x61D7ABDF, 0x4A8C8C7B, 0x68F4, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok789) {
    // 4154257838756815793.1079341712
    s21_decimal decimal = {{0x81BA1690, 0xEC2B73D3, 0x863B3726, 0xA0000}};
    // 4154257838756815793
    s21_decimal decimal_check = {{0x807B63B1, 0x39A6E37E, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok790) {
    // -4154257838756815793.1079341712
    s21_decimal decimal = {{0x81BA1690, 0xEC2B73D3, 0x863B3726, 0x800A0000}};
    // -4154257838756815794
    s21_decimal decimal_check = {{0x807B63B2, 0x39A6E37E, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok791) {
    // 439042372655894090607.06756498
    s21_decimal decimal = {{0xDB76A792, 0x3BCA31ED, 0x8DDCBBDF, 0x80000}};
    // 439042372655894090607
    s21_decimal decimal_check = {{0xCB3DD36F, 0xCCEFD7C8, 0x17, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok792) {
    // -439042372655894090607.06756498
    s21_decimal decimal = {{0xDB76A792, 0x3BCA31ED, 0x8DDCBBDF, 0x80080000}};
    // -439042372655894090608
    s21_decimal decimal_check = {{0xCB3DD370, 0xCCEFD7C8, 0x17, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok793) {
    // -6602719650081321722.8450135338
    s21_decimal decimal = {{0xE7CF7D2A, 0x7727AFE7, 0xD5586AB6, 0x800A0000}};
    // -6602719650081321723
    s21_decimal decimal_check = {{0xFE96B2FB, 0x5BA19289, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok794) {
    // 6602719650081321722.8450135338
    s21_decimal decimal = {{0xE7CF7D2A, 0x7727AFE7, 0xD5586AB6, 0xA0000}};
    // 6602719650081321722
    s21_decimal decimal_check = {{0xFE96B2FA, 0x5BA19289, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok795) {
    // -7500510513758041052494024960.5
    s21_decimal decimal = {{0x1C1A2A05, 0xE227A715, 0xF25AC4D0, 0x80010000}};
    // -7500510513758041052494024961
    s21_decimal decimal_check = {{0xE935D101, 0xB0372A4E, 0x183C46E1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok796) {
    // 7500510513758041052494024960.5
    s21_decimal decimal = {{0x1C1A2A05, 0xE227A715, 0xF25AC4D0, 0x10000}};
    // 7500510513758041052494024960
    s21_decimal decimal_check = {{0xE935D100, 0xB0372A4E, 0x183C46E1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok797) {
    // 3555977892615392225460271264.9
    s21_decimal decimal = {{0xF1973649, 0x3DF4D3DD, 0x72E65C16, 0x10000}};
    // 3555977892615392225460271264
    s21_decimal decimal_check = {{0x9828B8A0, 0xD2FEE1FC, 0xB7D6F9B, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok798) {
    // -3555977892615392225460271264.9
    s21_decimal decimal = {{0xF1973649, 0x3DF4D3DD, 0x72E65C16, 0x80010000}};
    // -3555977892615392225460271265
    s21_decimal decimal_check = {{0x9828B8A1, 0xD2FEE1FC, 0xB7D6F9B, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok799) {
    // 8298.102856650086172927479007
    s21_decimal decimal = {{0x26DC4CDF, 0x3C024601, 0x1AD007A1, 0x180000}};
    // 8298
    s21_decimal decimal_check = {{0x206A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok800) {
    // -8298.102856650086172927479007
    s21_decimal decimal = {{0x26DC4CDF, 0x3C024601, 0x1AD007A1, 0x80180000}};
    // -8299
    s21_decimal decimal_check = {{0x206B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok801) {
    // 3164952775793.0688894343055715
    s21_decimal decimal = {{0xD6CC0963, 0xAA1881FE, 0x6643E031, 0x100000}};
    // 3164952775793
    s21_decimal decimal_check = {{0xE5E2CC71, 0x2E0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok802) {
    // -3164952775793.0688894343055715
    s21_decimal decimal = {{0xD6CC0963, 0xAA1881FE, 0x6643E031, 0x80100000}};
    // -3164952775794
    s21_decimal decimal_check = {{0xE5E2CC72, 0x2E0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok803) {
    // 21143926234676763158655.948521
    s21_decimal decimal = {{0x13EA56E9, 0xECECE830, 0x4451D889, 0x60000}};
    // 21143926234676763158655
    s21_decimal decimal_check = {{0xBB19E87F, 0x36EBF51D, 0x47A, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok804) {
    // -21143926234676763158655.948521
    s21_decimal decimal = {{0x13EA56E9, 0xECECE830, 0x4451D889, 0x80060000}};
    // -21143926234676763158656
    s21_decimal decimal_check = {{0xBB19E880, 0x36EBF51D, 0x47A, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok805) {
    // -5152744243545511470681954397
    s21_decimal decimal = {{0xDBD2185D, 0x27DCADA9, 0x10A64009, 0x80000000}};
    // -5152744243545511470681954397
    s21_decimal decimal_check = {{0xDBD2185D, 0x27DCADA9, 0x10A64009, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok806) {
    // 5152744243545511470681954397
    s21_decimal decimal = {{0xDBD2185D, 0x27DCADA9, 0x10A64009, 0x0}};
    // 5152744243545511470681954397
    s21_decimal decimal_check = {{0xDBD2185D, 0x27DCADA9, 0x10A64009, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok807) {
    // -118933272468169822265562650.93
    s21_decimal decimal = {{0x7729A285, 0xF43964EC, 0x266DEE01, 0x80020000}};
    // -118933272468169822265562651
    s21_decimal decimal_check = {{0x7C12561B, 0x9E9A2C87, 0x626119, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok808) {
    // 118933272468169822265562650.93
    s21_decimal decimal = {{0x7729A285, 0xF43964EC, 0x266DEE01, 0x20000}};
    // 118933272468169822265562650
    s21_decimal decimal_check = {{0x7C12561A, 0x9E9A2C87, 0x626119, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok809) {
    // -11123628.496703127528877119470
    s21_decimal decimal = {{0xE3C4D7EE, 0x1A344107, 0x23F13FF5, 0x80150000}};
    // -11123629
    s21_decimal decimal_check = {{0xA9BBAD, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok810) {
    // 11123628.496703127528877119470
    s21_decimal decimal = {{0xE3C4D7EE, 0x1A344107, 0x23F13FF5, 0x150000}};
    // 11123628
    s21_decimal decimal_check = {{0xA9BBAC, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok811) {
    // 532086663270459428741280942.88
    s21_decimal decimal = {{0xC9599450, 0x578BBABB, 0xABED2D5D, 0x20000}};
    // 532086663270459428741280942
    s21_decimal decimal_check = {{0xC20374AE, 0xD03C46FC, 0x1B821BB, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok812) {
    // -532086663270459428741280942.88
    s21_decimal decimal = {{0xC9599450, 0x578BBABB, 0xABED2D5D, 0x80020000}};
    // -532086663270459428741280943
    s21_decimal decimal_check = {{0xC20374AF, 0xD03C46FC, 0x1B821BB, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok813) {
    // -695712498197752691014943297.90
    s21_decimal decimal = {{0x9973E1BE, 0xDB4A7BCA, 0xE0CBFD31, 0x80020000}};
    // -695712498197752691014943298
    s21_decimal decimal_check = {{0x39DAC242, 0x193B9FF5, 0x23F7ADA, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok814) {
    // 695712498197752691014943297.90
    s21_decimal decimal = {{0x9973E1BE, 0xDB4A7BCA, 0xE0CBFD31, 0x20000}};
    // 695712498197752691014943297
    s21_decimal decimal_check = {{0x39DAC241, 0x193B9FF5, 0x23F7ADA, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok815) {
    // 72023003580207062080029.273046
    s21_decimal decimal = {{0xF0092BD6, 0x879314B0, 0xE8B8083F, 0x60000}};
    // 72023003580207062080029
    s21_decimal decimal_check = {{0x91245A1D, 0x5FF601F8, 0xF40, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok816) {
    // -72023003580207062080029.273046
    s21_decimal decimal = {{0xF0092BD6, 0x879314B0, 0xE8B8083F, 0x80060000}};
    // -72023003580207062080030
    s21_decimal decimal_check = {{0x91245A1E, 0x5FF601F8, 0xF40, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok817) {
    // 13589618955629615557353877491
    s21_decimal decimal = {{0x8E6F2FF3, 0xBF47E9B3, 0x2BE911BF, 0x0}};
    // 13589618955629615557353877491
    s21_decimal decimal_check = {{0x8E6F2FF3, 0xBF47E9B3, 0x2BE911BF, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok818) {
    // -13589618955629615557353877491
    s21_decimal decimal = {{0x8E6F2FF3, 0xBF47E9B3, 0x2BE911BF, 0x80000000}};
    // -13589618955629615557353877491
    s21_decimal decimal_check = {{0x8E6F2FF3, 0xBF47E9B3, 0x2BE911BF, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok819) {
    // -7573.1945982414893866183955837
    s21_decimal decimal = {{0x829A157D, 0x8D208B7, 0xF4B3FF5A, 0x80190000}};
    // -7574
    s21_decimal decimal_check = {{0x1D96, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok820) {
    // 7573.1945982414893866183955837
    s21_decimal decimal = {{0x829A157D, 0x8D208B7, 0xF4B3FF5A, 0x190000}};
    // 7573
    s21_decimal decimal_check = {{0x1D95, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok821) {
    // 74372045.784570823114469514015
    s21_decimal decimal = {{0xEFE99B1F, 0x9755E57A, 0xF04F1D48, 0x150000}};
    // 74372045
    s21_decimal decimal_check = {{0x46ED3CD, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok822) {
    // -74372045.784570823114469514015
    s21_decimal decimal = {{0xEFE99B1F, 0x9755E57A, 0xF04F1D48, 0x80150000}};
    // -74372046
    s21_decimal decimal_check = {{0x46ED3CE, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok823) {
    // 223770186.65854867189823515341
    s21_decimal decimal = {{0x8E952ACD, 0x903CB8F3, 0x484DD604, 0x140000}};
    // 223770186
    s21_decimal decimal_check = {{0xD56764A, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok824) {
    // -223770186.65854867189823515341
    s21_decimal decimal = {{0x8E952ACD, 0x903CB8F3, 0x484DD604, 0x80140000}};
    // -223770187
    s21_decimal decimal_check = {{0xD56764B, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok825) {
    // -54147018.368819404611480365469
    s21_decimal decimal = {{0xC49AA99D, 0x744EAF9D, 0xAEF55D23, 0x80150000}};
    // -54147019
    s21_decimal decimal_check = {{0x33A37CB, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok826) {
    // 54147018.368819404611480365469
    s21_decimal decimal = {{0xC49AA99D, 0x744EAF9D, 0xAEF55D23, 0x150000}};
    // 54147018
    s21_decimal decimal_check = {{0x33A37CA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok827) {
    // -42014.104298244076096595478990
    s21_decimal decimal = {{0xD524C9CE, 0xC26AA66A, 0x87C140A5, 0x80180000}};
    // -42015
    s21_decimal decimal_check = {{0xA41F, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok828) {
    // 42014.104298244076096595478990
    s21_decimal decimal = {{0xD524C9CE, 0xC26AA66A, 0x87C140A5, 0x180000}};
    // 42014
    s21_decimal decimal_check = {{0xA41E, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok829) {
    // -26536341663941398222228.887651
    s21_decimal decimal = {{0xBB3F1863, 0x17D84042, 0x55BE58EC, 0x80060000}};
    // -26536341663941398222229
    s21_decimal decimal_check = {{0x7939D595, 0x89B803CA, 0x59E, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok830) {
    // 26536341663941398222228.887651
    s21_decimal decimal = {{0xBB3F1863, 0x17D84042, 0x55BE58EC, 0x60000}};
    // 26536341663941398222228
    s21_decimal decimal_check = {{0x7939D594, 0x89B803CA, 0x59E, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok831) {
    // 6.1936749694907885071874961088
    s21_decimal decimal = {{0xB934AEC0, 0xCBA5FEF5, 0xC820E0E8, 0x1C0000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok832) {
    // -6.1936749694907885071874961088
    s21_decimal decimal = {{0xB934AEC0, 0xCBA5FEF5, 0xC820E0E8, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok833) {
    // 2408952540394693410943666820.4
    s21_decimal decimal = {{0xFC38692C, 0xDAEE6F7A, 0x4DD6636C, 0x10000}};
    // 2408952540394693410943666820
    s21_decimal decimal_check = {{0x4C6C0A84, 0xE2B1718C, 0x7C8A38A, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok834) {
    // -2408952540394693410943666820.4
    s21_decimal decimal = {{0xFC38692C, 0xDAEE6F7A, 0x4DD6636C, 0x80010000}};
    // -2408952540394693410943666821
    s21_decimal decimal_check = {{0x4C6C0A85, 0xE2B1718C, 0x7C8A38A, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok835) {
    // 761781866670255.98034370369262
    s21_decimal decimal = {{0x856416EE, 0x50FC86E, 0xF6251E7E, 0xE0000}};
    // 761781866670255
    s21_decimal decimal_check = {{0x298F28AF, 0x2B4D6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok836) {
    // -761781866670255.98034370369262
    s21_decimal decimal = {{0x856416EE, 0x50FC86E, 0xF6251E7E, 0x800E0000}};
    // -761781866670256
    s21_decimal decimal_check = {{0x298F28B0, 0x2B4D6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok837) {
    // -70141033612.644172478715004270
    s21_decimal decimal = {{0xD294056E, 0x290EAAFB, 0xE2A34D9B, 0x80120000}};
    // -70141033613
    s21_decimal decimal_check = {{0x54BB3C8D, 0x10, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok838) {
    // 70141033612.644172478715004270
    s21_decimal decimal = {{0xD294056E, 0x290EAAFB, 0xE2A34D9B, 0x120000}};
    // 70141033612
    s21_decimal decimal_check = {{0x54BB3C8C, 0x10, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok839) {
    // -228.99457042623138959107055924
    s21_decimal decimal = {{0x24506134, 0xB7AFB101, 0x49FDFCA5, 0x801A0000}};
    // -229
    s21_decimal decimal_check = {{0xE5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok840) {
    // 228.99457042623138959107055924
    s21_decimal decimal = {{0x24506134, 0xB7AFB101, 0x49FDFCA5, 0x1A0000}};
    // 228
    s21_decimal decimal_check = {{0xE4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok841) {
    // 14304876.739190774748003985799
    s21_decimal decimal = {{0x40106987, 0xE36E2BD5, 0x2E38B779, 0x150000}};
    // 14304876
    s21_decimal decimal_check = {{0xDA466C, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok842) {
    // -14304876.739190774748003985799
    s21_decimal decimal = {{0x40106987, 0xE36E2BD5, 0x2E38B779, 0x80150000}};
    // -14304877
    s21_decimal decimal_check = {{0xDA466D, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok843) {
    // -7264502434576648043588.0229710
    s21_decimal decimal = {{0x95B17B4E, 0xCC0FFC66, 0xEABA8E44, 0x80070000}};
    // -7264502434576648043589
    s21_decimal decimal_check = {{0x957AFC45, 0xCF392B43, 0x189, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok844) {
    // 7264502434576648043588.0229710
    s21_decimal decimal = {{0x95B17B4E, 0xCC0FFC66, 0xEABA8E44, 0x70000}};
    // 7264502434576648043588
    s21_decimal decimal_check = {{0x957AFC44, 0xCF392B43, 0x189, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok845) {
    // -644582090748608.60716214807760
    s21_decimal decimal = {{0xD49A6CD0, 0xACA8C317, 0xD04694B3, 0x800E0000}};
    // -644582090748609
    s21_decimal decimal_check = {{0x768C32C1, 0x24A3E, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok846) {
    // 644582090748608.60716214807760
    s21_decimal decimal = {{0xD49A6CD0, 0xACA8C317, 0xD04694B3, 0xE0000}};
    // 644582090748608
    s21_decimal decimal_check = {{0x768C32C0, 0x24A3E, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok847) {
    // 5813171625565645953057000.3340
    s21_decimal decimal = {{0x6027738C, 0xBC14243B, 0xBBD56DBC, 0x40000}};
    // 5813171625565645953057000
    s21_decimal decimal_check = {{0xF5A440E8, 0xAA4F5CAC, 0x4CEFC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok848) {
    // -5813171625565645953057000.3340
    s21_decimal decimal = {{0x6027738C, 0xBC14243B, 0xBBD56DBC, 0x80040000}};
    // -5813171625565645953057001
    s21_decimal decimal_check = {{0xF5A440E9, 0xAA4F5CAC, 0x4CEFC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok849) {
    // 35335.214396053626493990389843
    s21_decimal decimal = {{0x8C48C853, 0xAC10199B, 0x722C9AB2, 0x180000}};
    // 35335
    s21_decimal decimal_check = {{0x8A07, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok850) {
    // -35335.214396053626493990389843
    s21_decimal decimal = {{0x8C48C853, 0xAC10199B, 0x722C9AB2, 0x80180000}};
    // -35336
    s21_decimal decimal_check = {{0x8A08, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok851) {
    // 6998381816196503.5946981857608
    s21_decimal decimal = {{0xF7A1948, 0x806C1D32, 0xE22141F0, 0xD0000}};
    // 6998381816196503
    s21_decimal decimal_check = {{0xBE282D97, 0x18DCFD, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok852) {
    // -6998381816196503.5946981857608
    s21_decimal decimal = {{0xF7A1948, 0x806C1D32, 0xE22141F0, 0x800D0000}};
    // -6998381816196504
    s21_decimal decimal_check = {{0xBE282D98, 0x18DCFD, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok853) {
    // -557792986297228.91503433241824
    s21_decimal decimal = {{0x3B3D54E0, 0xB4028DEC, 0xB43B8DED, 0x800E0000}};
    // -557792986297229
    s21_decimal decimal_check = {{0x4CCE738D, 0x1FB4F, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok854) {
    // 557792986297228.91503433241824
    s21_decimal decimal = {{0x3B3D54E0, 0xB4028DEC, 0xB43B8DED, 0xE0000}};
    // 557792986297228
    s21_decimal decimal_check = {{0x4CCE738C, 0x1FB4F, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok855) {
    // -609969045856921686.79602199695
    s21_decimal decimal = {{0x9CDB1C8F, 0x55BD91CF, 0xC51774F7, 0x800B0000}};
    // -609969045856921687
    s21_decimal decimal_check = {{0x8E492857, 0x8770B9D, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok856) {
    // 609969045856921686.79602199695
    s21_decimal decimal = {{0x9CDB1C8F, 0x55BD91CF, 0xC51774F7, 0xB0000}};
    // 609969045856921686
    s21_decimal decimal_check = {{0x8E492856, 0x8770B9D, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok857) {
    // 35502491.973187209991889487710
    s21_decimal decimal = {{0x8AEE075E, 0x4C873021, 0x72B6F91A, 0x150000}};
    // 35502491
    s21_decimal decimal_check = {{0x21DB99B, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok858) {
    // -35502491.973187209991889487710
    s21_decimal decimal = {{0x8AEE075E, 0x4C873021, 0x72B6F91A, 0x80150000}};
    // -35502492
    s21_decimal decimal_check = {{0x21DB99C, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok859) {
    // 17550051113712.508157032467261
    s21_decimal decimal = {{0x5A810B3D, 0x3C6664B0, 0x38B50FE1, 0xF0000}};
    // 17550051113712
    s21_decimal decimal_check = {{0x308FFAF0, 0xFF6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok860) {
    // -17550051113712.508157032467261
    s21_decimal decimal = {{0x5A810B3D, 0x3C6664B0, 0x38B50FE1, 0x800F0000}};
    // -17550051113713
    s21_decimal decimal_check = {{0x308FFAF1, 0xFF6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok861) {
    // -289.16086617195301293773006072
    s21_decimal decimal = {{0x9D47A4F8, 0x81D1D9E2, 0x5D6ED384, 0x801A0000}};
    // -290
    s21_decimal decimal_check = {{0x122, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok862) {
    // 289.16086617195301293773006072
    s21_decimal decimal = {{0x9D47A4F8, 0x81D1D9E2, 0x5D6ED384, 0x1A0000}};
    // 289
    s21_decimal decimal_check = {{0x121, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok863) {
    // 7580797528054.0727974800717692
    s21_decimal decimal = {{0xE1DCF77C, 0x8B634942, 0xF4F2E32E, 0x100000}};
    // 7580797528054
    s21_decimal decimal_check = {{0xABE67F6, 0x6E5, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok864) {
    // -7580797528054.0727974800717692
    s21_decimal decimal = {{0xE1DCF77C, 0x8B634942, 0xF4F2E32E, 0x80100000}};
    // -7580797528055
    s21_decimal decimal_check = {{0xABE67F7, 0x6E5, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok865) {
    // 9867.772107112238947404415232
    s21_decimal decimal = {{0x1A4D0100, 0xCE5FB171, 0x1FE26E05, 0x180000}};
    // 9867
    s21_decimal decimal_check = {{0x268B, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok866) {
    // -9867.772107112238947404415232
    s21_decimal decimal = {{0x1A4D0100, 0xCE5FB171, 0x1FE26E05, 0x80180000}};
    // -9868
    s21_decimal decimal_check = {{0x268C, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok867) {
    // 35867124395579729788727.122448
    s21_decimal decimal = {{0xF296DA10, 0x86574152, 0x73E49705, 0x60000}};
    // 35867124395579729788727
    s21_decimal decimal_check = {{0x3CF83F37, 0x5C57759C, 0x798, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok868) {
    // -35867124395579729788727.122448
    s21_decimal decimal = {{0xF296DA10, 0x86574152, 0x73E49705, 0x80060000}};
    // -35867124395579729788728
    s21_decimal decimal_check = {{0x3CF83F38, 0x5C57759C, 0x798, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok869) {
    // -6271506153946199.6585659968934
    s21_decimal decimal = {{0xBE60ADA6, 0x6EADD64A, 0xCAA4AEDA, 0x800D0000}};
    // -6271506153946200
    s21_decimal decimal_check = {{0xD0833C58, 0x1647E6, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok870) {
    // 6271506153946199.6585659968934
    s21_decimal decimal = {{0xBE60ADA6, 0x6EADD64A, 0xCAA4AEDA, 0xD0000}};
    // 6271506153946199
    s21_decimal decimal_check = {{0xD0833C57, 0x1647E6, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok871) {
    // -4744907511756.6906443242156603
    s21_decimal decimal = {{0xC4E8323B, 0x3EA46F71, 0x9950F47C, 0x80100000}};
    // -4744907511757
    s21_decimal decimal_check = {{0xC286D7CD, 0x450, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok872) {
    // 4744907511756.6906443242156603
    s21_decimal decimal = {{0xC4E8323B, 0x3EA46F71, 0x9950F47C, 0x100000}};
    // 4744907511756
    s21_decimal decimal_check = {{0xC286D7CC, 0x450, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok873) {
    // -27848009442765688472808.526305
    s21_decimal decimal = {{0x94A511E1, 0xDCB72D51, 0x59FB5560, 0x80060000}};
    // -27848009442765688472809
    s21_decimal decimal_check = {{0x2CAF04E9, 0xA4C4131E, 0x5E5, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok874) {
    // 27848009442765688472808.526305
    s21_decimal decimal = {{0x94A511E1, 0xDCB72D51, 0x59FB5560, 0x60000}};
    // 27848009442765688472808
    s21_decimal decimal_check = {{0x2CAF04E8, 0xA4C4131E, 0x5E5, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok875) {
    // 16066.739544792969751303352033
    s21_decimal decimal = {{0xF670EEE1, 0xF60EEAD0, 0x33EA186F, 0x180000}};
    // 16066
    s21_decimal decimal_check = {{0x3EC2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok876) {
    // -16066.739544792969751303352033
    s21_decimal decimal = {{0xF670EEE1, 0xF60EEAD0, 0x33EA186F, 0x80180000}};
    // -16067
    s21_decimal decimal_check = {{0x3EC3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok877) {
    // -4472858298557402270218785932.3
    s21_decimal decimal = {{0x206ECD7B, 0x42042DEC, 0x90869DDE, 0x80010000}};
    // -4472858298557402270218785933
    s21_decimal decimal_check = {{0xD00B148D, 0x39CD37CA, 0xE73DC96, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok878) {
    // 4472858298557402270218785932.3
    s21_decimal decimal = {{0x206ECD7B, 0x42042DEC, 0x90869DDE, 0x10000}};
    // 4472858298557402270218785932
    s21_decimal decimal_check = {{0xD00B148C, 0x39CD37CA, 0xE73DC96, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok879) {
    // -27183231679401811857695.116654
    s21_decimal decimal = {{0xE0110D6E, 0x1965EE18, 0x57D57136, 0x80060000}};
    // -27183231679401811857696
    s21_decimal decimal_check = {{0x62215120, 0x9B1F057B, 0x5C1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok880) {
    // 27183231679401811857695.116654
    s21_decimal decimal = {{0xE0110D6E, 0x1965EE18, 0x57D57136, 0x60000}};
    // 27183231679401811857695
    s21_decimal decimal_check = {{0x6221511F, 0x9B1F057B, 0x5C1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok881) {
    // -3695258075704016.020827238015
    s21_decimal decimal = {{0x7C236E7F, 0xADBBACBA, 0xBF0A555, 0x800C0000}};
    // -3695258075704017
    s21_decimal decimal_check = {{0x50F4AAD1, 0xD20D1, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok882) {
    // 3695258075704016.020827238015
    s21_decimal decimal = {{0x7C236E7F, 0xADBBACBA, 0xBF0A555, 0xC0000}};
    // 3695258075704016
    s21_decimal decimal_check = {{0x50F4AAD0, 0xD20D1, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok883) {
    // -4305720035497.0977854339082124
    s21_decimal decimal = {{0x2EEE78C, 0x4CD72D5E, 0x8B2014D4, 0x80100000}};
    // -4305720035498
    s21_decimal decimal_check = {{0x80E9C8AA, 0x3EA, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok884) {
    // 4305720035497.0977854339082124
    s21_decimal decimal = {{0x2EEE78C, 0x4CD72D5E, 0x8B2014D4, 0x100000}};
    // 4305720035497
    s21_decimal decimal_check = {{0x80E9C8A9, 0x3EA, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok885) {
    // 40094462.967487981175390493918
    s21_decimal decimal = {{0x95B65CDE, 0xB312ACC5, 0x818D5CC8, 0x150000}};
    // 40094462
    s21_decimal decimal_check = {{0x263CAFE, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok886) {
    // -40094462.967487981175390493918
    s21_decimal decimal = {{0x95B65CDE, 0xB312ACC5, 0x818D5CC8, 0x80150000}};
    // -40094463
    s21_decimal decimal_check = {{0x263CAFF, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok887) {
    // -660457428.36542893573839092119
    s21_decimal decimal = {{0x3ED57997, 0x5706227F, 0xD567C20D, 0x80140000}};
    // -660457429
    s21_decimal decimal_check = {{0x275DC7D5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok888) {
    // 660457428.36542893573839092119
    s21_decimal decimal = {{0x3ED57997, 0x5706227F, 0xD567C20D, 0x140000}};
    // 660457428
    s21_decimal decimal_check = {{0x275DC7D4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok889) {
    // -588768477848090181515495775.11
    s21_decimal decimal = {{0xA594A927, 0xDE91F884, 0xBE3DC979, 0x80020000}};
    // -588768477848090181515495776
    s21_decimal decimal_check = {{0x680E4960, 0x238175AF, 0x1E70493, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok890) {
    // 588768477848090181515495775.11
    s21_decimal decimal = {{0xA594A927, 0xDE91F884, 0xBE3DC979, 0x20000}};
    // 588768477848090181515495775
    s21_decimal decimal_check = {{0x680E495F, 0x238175AF, 0x1E70493, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok891) {
    // 4772654.8838883795178431952803
    s21_decimal decimal = {{0xEE7BB7A3, 0xD1529FC3, 0x9A3679D4, 0x160000}};
    // 4772654
    s21_decimal decimal_check = {{0x48D32E, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok892) {
    // -4772654.8838883795178431952803
    s21_decimal decimal = {{0xEE7BB7A3, 0xD1529FC3, 0x9A3679D4, 0x80160000}};
    // -4772655
    s21_decimal decimal_check = {{0x48D32F, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok893) {
    // 600.31637112284245059768507587
    s21_decimal decimal = {{0x47895CC3, 0xC0000A61, 0xC1F901A0, 0x1A0000}};
    // 600
    s21_decimal decimal_check = {{0x258, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok894) {
    // -600.31637112284245059768507587
    s21_decimal decimal = {{0x47895CC3, 0xC0000A61, 0xC1F901A0, 0x801A0000}};
    // -601
    s21_decimal decimal_check = {{0x259, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok895) {
    // -2776996307820966.5121042851638
    s21_decimal decimal = {{0xA2E46736, 0xF63C579F, 0x59BAC66A, 0x800D0000}};
    // -2776996307820967
    s21_decimal decimal_check = {{0xD67861A7, 0x9DDA9, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok896) {
    // 2776996307820966.5121042851638
    s21_decimal decimal = {{0xA2E46736, 0xF63C579F, 0x59BAC66A, 0xD0000}};
    // 2776996307820966
    s21_decimal decimal_check = {{0xD67861A6, 0x9DDA9, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok897) {
    // 69231585109968630977.489807574
    s21_decimal decimal = {{0xC3EC28D6, 0xACAA33C, 0xDFB30665, 0x90000}};
    // 69231585109968630977
    s21_decimal decimal_check = {{0x54E734C1, 0xC0C7FFDA, 0x3, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok898) {
    // -69231585109968630977.489807574
    s21_decimal decimal = {{0xC3EC28D6, 0xACAA33C, 0xDFB30665, 0x80090000}};
    // -69231585109968630978
    s21_decimal decimal_check = {{0x54E734C2, 0xC0C7FFDA, 0x3, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok899) {
    // 7120.7520400793708529155804637
    s21_decimal decimal = {{0xFFC78DDD, 0xCAD5895E, 0xE6157AF7, 0x190000}};
    // 7120
    s21_decimal decimal_check = {{0x1BD0, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok900) {
    // -7120.7520400793708529155804637
    s21_decimal decimal = {{0xFFC78DDD, 0xCAD5895E, 0xE6157AF7, 0x80190000}};
    // -7121
    s21_decimal decimal_check = {{0x1BD1, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok901) {
    // 76773353916641581588101651518
    s21_decimal decimal = {{0xEAADC3E, 0x45648F55, 0xF8116E0F, 0x0}};
    // 76773353916641581588101651518
    s21_decimal decimal_check = {{0xEAADC3E, 0x45648F55, 0xF8116E0F, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok902) {
    // -76773353916641581588101651518
    s21_decimal decimal = {{0xEAADC3E, 0x45648F55, 0xF8116E0F, 0x80000000}};
    // -76773353916641581588101651518
    s21_decimal decimal_check = {{0xEAADC3E, 0x45648F55, 0xF8116E0F, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok903) {
    // 48033576934267081017691296202
    s21_decimal decimal = {{0x219551CA, 0x3816E37C, 0x9B34718F, 0x0}};
    // 48033576934267081017691296202
    s21_decimal decimal_check = {{0x219551CA, 0x3816E37C, 0x9B34718F, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok904) {
    // -48033576934267081017691296202
    s21_decimal decimal = {{0x219551CA, 0x3816E37C, 0x9B34718F, 0x80000000}};
    // -48033576934267081017691296202
    s21_decimal decimal_check = {{0x219551CA, 0x3816E37C, 0x9B34718F, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok905) {
    // 20497477784010.478753940516768
    s21_decimal decimal = {{0x29B02FA0, 0x31E36857, 0x423B1DC1, 0xF0000}};
    // 20497477784010
    s21_decimal decimal_check = {{0x70E1D1CA, 0x12A4, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok906) {
    // -20497477784010.478753940516768
    s21_decimal decimal = {{0x29B02FA0, 0x31E36857, 0x423B1DC1, 0x800F0000}};
    // -20497477784011
    s21_decimal decimal_check = {{0x70E1D1CB, 0x12A4, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok907) {
    // -23373199.379517626489815951456
    s21_decimal decimal = {{0x183BE860, 0x42AFA70A, 0x4B85DB7D, 0x80150000}};
    // -23373200
    s21_decimal decimal_check = {{0x164A590, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok908) {
    // 23373199.379517626489815951456
    s21_decimal decimal = {{0x183BE860, 0x42AFA70A, 0x4B85DB7D, 0x150000}};
    // 23373199
    s21_decimal decimal_check = {{0x164A58F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok909) {
    // 340415880190741321.356998311
    s21_decimal decimal = {{0xC098F6A7, 0xD7B28F25, 0x11995DD, 0x90000}};
    // 340415880190741321
    s21_decimal decimal_check = {{0x7EABCB49, 0x4B96670, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok910) {
    // -340415880190741321.356998311
    s21_decimal decimal = {{0xC098F6A7, 0xD7B28F25, 0x11995DD, 0x80090000}};
    // -340415880190741322
    s21_decimal decimal_check = {{0x7EABCB4A, 0x4B96670, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok911) {
    // 6.3088881678789399064616234879
    s21_decimal decimal = {{0x37F1EF7F, 0xCA8D68B1, 0xCBD9E658, 0x1C0000}};
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok912) {
    // -6.3088881678789399064616234879
    s21_decimal decimal = {{0x37F1EF7F, 0xCA8D68B1, 0xCBD9E658, 0x801C0000}};
    // -7
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok913) {
    // -501541937089313999855.95656732
    s21_decimal decimal = {{0x166BAA1C, 0xEC929D3A, 0xA20E93A0, 0x80080000}};
    // -501541937089313999856
    s21_decimal decimal_check = {{0xE9DF8BF0, 0x304AE67F, 0x1B, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok914) {
    // 501541937089313999855.95656732
    s21_decimal decimal = {{0x166BAA1C, 0xEC929D3A, 0xA20E93A0, 0x80000}};
    // 501541937089313999855
    s21_decimal decimal_check = {{0xE9DF8BEF, 0x304AE67F, 0x1B, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok915) {
    // 6716.2096685279774385346371547
    s21_decimal decimal = {{0x3466DFDB, 0xBE3B3C8D, 0xD9032F2C, 0x190000}};
    // 6716
    s21_decimal decimal_check = {{0x1A3C, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok916) {
    // -6716.2096685279774385346371547
    s21_decimal decimal = {{0x3466DFDB, 0xBE3B3C8D, 0xD9032F2C, 0x80190000}};
    // -6717
    s21_decimal decimal_check = {{0x1A3D, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok917) {
    // 3485872167306.3419689711976781
    s21_decimal decimal = {{0xA590414D, 0x666FE4F6, 0x70A27570, 0x100000}};
    // 3485872167306
    s21_decimal decimal_check = {{0x9E2C198A, 0x32B, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok918) {
    // -3485872167306.3419689711976781
    s21_decimal decimal = {{0xA590414D, 0x666FE4F6, 0x70A27570, 0x80100000}};
    // -3485872167307
    s21_decimal decimal_check = {{0x9E2C198B, 0x32B, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok919) {
    // 38627956250562363153.483887989
    s21_decimal decimal = {{0x9654F575, 0x46D837B7, 0x7CD04BE8, 0x90000}};
    // 38627956250562363153
    s21_decimal decimal_check = {{0xDA197F11, 0x1812118C, 0x2, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok920) {
    // -38627956250562363153.483887989
    s21_decimal decimal = {{0x9654F575, 0x46D837B7, 0x7CD04BE8, 0x80090000}};
    // -38627956250562363154
    s21_decimal decimal_check = {{0xDA197F12, 0x1812118C, 0x2, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok921) {
    // -32159.3286074798265526606995
    s21_decimal decimal = {{0xE1DF5C93, 0xF89056A4, 0x10A0406, 0x80160000}};
    // -32160
    s21_decimal decimal_check = {{0x7DA0, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok922) {
    // 32159.3286074798265526606995
    s21_decimal decimal = {{0xE1DF5C93, 0xF89056A4, 0x10A0406, 0x160000}};
    // 32159
    s21_decimal decimal_check = {{0x7D9F, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok923) {
    // -764118124903968032215996.16415
    s21_decimal decimal = {{0x6114FD9F, 0x483BB180, 0xF6E65EAF, 0x80050000}};
    // -764118124903968032215997
    s21_decimal decimal_check = {{0xD330D3BD, 0xED3290D2, 0xA1CE, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok924) {
    // 764118124903968032215996.16415
    s21_decimal decimal = {{0x6114FD9F, 0x483BB180, 0xF6E65EAF, 0x50000}};
    // 764118124903968032215996
    s21_decimal decimal_check = {{0xD330D3BC, 0xED3290D2, 0xA1CE, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok925) {
    // -59647296606939936195790.539649
    s21_decimal decimal = {{0x7C588B81, 0x34E237A8, 0xC0BB165C, 0x80060000}};
    // -59647296606939936195791
    s21_decimal decimal_check = {{0x196C04CF, 0x7C868F17, 0xCA1, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok926) {
    // 59647296606939936195790.539649
    s21_decimal decimal = {{0x7C588B81, 0x34E237A8, 0xC0BB165C, 0x60000}};
    // 59647296606939936195790
    s21_decimal decimal_check = {{0x196C04CE, 0x7C868F17, 0xCA1, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok927) {
    // 37761.386032726781368386697026
    s21_decimal decimal = {{0x86CFB742, 0xA3269DCD, 0x7A037C86, 0x180000}};
    // 37761
    s21_decimal decimal_check = {{0x9381, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok928) {
    // -37761.386032726781368386697026
    s21_decimal decimal = {{0x86CFB742, 0xA3269DCD, 0x7A037C86, 0x80180000}};
    // -37762
    s21_decimal decimal_check = {{0x9382, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok929) {
    // 46763817371754136100138806461
    s21_decimal decimal = {{0x369E6CBD, 0x689768D1, 0x971A1F83, 0x0}};
    // 46763817371754136100138806461
    s21_decimal decimal_check = {{0x369E6CBD, 0x689768D1, 0x971A1F83, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok930) {
    // -46763817371754136100138806461
    s21_decimal decimal = {{0x369E6CBD, 0x689768D1, 0x971A1F83, 0x80000000}};
    // -46763817371754136100138806461
    s21_decimal decimal_check = {{0x369E6CBD, 0x689768D1, 0x971A1F83, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok931) {
    // 4.692231354228898465612305310
    s21_decimal decimal = {{0x431C139E, 0x67299B35, 0xF2952A3, 0x1B0000}};
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok932) {
    // -4.692231354228898465612305310
    s21_decimal decimal = {{0x431C139E, 0x67299B35, 0xF2952A3, 0x801B0000}};
    // -5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok933) {
    // -61305058628466607222376627.435
    s21_decimal decimal = {{0x15F3FCEB, 0x777BFDF7, 0xC6165B1F, 0x80030000}};
    // -61305058628466607222376628
    s21_decimal decimal_check = {{0x32F748B4, 0xE331051E, 0x32B5D9, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok934) {
    // 61305058628466607222376627.435
    s21_decimal decimal = {{0x15F3FCEB, 0x777BFDF7, 0xC6165B1F, 0x30000}};
    // 61305058628466607222376627
    s21_decimal decimal_check = {{0x32F748B3, 0xE331051E, 0x32B5D9, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok935) {
    // -39192623231215811.084203128156
    s21_decimal decimal = {{0x8F20F55C, 0xA26EB32E, 0x7EA360CA, 0x800C0000}};
    // -39192623231215812
    s21_decimal decimal_check = {{0xB18328C4, 0x8B3D7B, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok936) {
    // 39192623231215811.084203128156
    s21_decimal decimal = {{0x8F20F55C, 0xA26EB32E, 0x7EA360CA, 0xC0000}};
    // 39192623231215811
    s21_decimal decimal_check = {{0xB18328C3, 0x8B3D7B, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok937) {
    // 67843746328466757374755.342078
    s21_decimal decimal = {{0x17F606FE, 0xF1A71C97, 0xDB370819, 0x60000}};
    // 67843746328466757374755
    s21_decimal decimal_check = {{0xC501D323, 0xD11D9A2A, 0xE5D, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok938) {
    // -67843746328466757374755.342078
    s21_decimal decimal = {{0x17F606FE, 0xF1A71C97, 0xDB370819, 0x80060000}};
    // -67843746328466757374756
    s21_decimal decimal_check = {{0xC501D324, 0xD11D9A2A, 0xE5D, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok939) {
    // -52163407196874605062862088300
    s21_decimal decimal = {{0x7697286C, 0x5AD8E779, 0xA88C8F22, 0x80000000}};
    // -52163407196874605062862088300
    s21_decimal decimal_check = {{0x7697286C, 0x5AD8E779, 0xA88C8F22, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok940) {
    // 52163407196874605062862088300
    s21_decimal decimal = {{0x7697286C, 0x5AD8E779, 0xA88C8F22, 0x0}};
    // 52163407196874605062862088300
    s21_decimal decimal_check = {{0x7697286C, 0x5AD8E779, 0xA88C8F22, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok941) {
    // -10476335623387.591565155238476
    s21_decimal decimal = {{0xB2C0024C, 0x20D211D4, 0x21D9D25C, 0x800F0000}};
    // -10476335623388
    s21_decimal decimal_check = {{0x36436CDC, 0x987, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok942) {
    // 10476335623387.591565155238476
    s21_decimal decimal = {{0xB2C0024C, 0x20D211D4, 0x21D9D25C, 0xF0000}};
    // 10476335623387
    s21_decimal decimal_check = {{0x36436CDB, 0x987, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok943) {
    // -63781641.956401116328158816754
    s21_decimal decimal = {{0xAA93E9F2, 0xB0EE3075, 0xCE16F00A, 0x80150000}};
    // -63781642
    s21_decimal decimal_check = {{0x3CD3B0A, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok944) {
    // 63781641.956401116328158816754
    s21_decimal decimal = {{0xAA93E9F2, 0xB0EE3075, 0xCE16F00A, 0x150000}};
    // 63781641
    s21_decimal decimal_check = {{0x3CD3B09, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok945) {
    // -633286868.86943196741403421745
    s21_decimal decimal = {{0xA9802C31, 0x2C8501E3, 0xCCA04313, 0x80140000}};
    // -633286869
    s21_decimal decimal_check = {{0x25BF30D5, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok946) {
    // 633286868.86943196741403421745
    s21_decimal decimal = {{0xA9802C31, 0x2C8501E3, 0xCCA04313, 0x140000}};
    // 633286868
    s21_decimal decimal_check = {{0x25BF30D4, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok947) {
    // -168.64426257044855590654958581
    s21_decimal decimal = {{0x6CD1DBF5, 0x47CD9759, 0x367DED2B, 0x801A0000}};
    // -169
    s21_decimal decimal_check = {{0xA9, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok948) {
    // 168.64426257044855590654958581
    s21_decimal decimal = {{0x6CD1DBF5, 0x47CD9759, 0x367DED2B, 0x1A0000}};
    // 168
    s21_decimal decimal_check = {{0xA8, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok949) {
    // 659838203874218756167336.44738
    s21_decimal decimal = {{0xA67AC7C2, 0xA59510F2, 0xD5348976, 0x50000}};
    // 659838203874218756167336
    s21_decimal decimal_check = {{0x9B0A56A8, 0xE694B2F7, 0x8BB9, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok950) {
    // -659838203874218756167336.44738
    s21_decimal decimal = {{0xA67AC7C2, 0xA59510F2, 0xD5348976, 0x80050000}};
    // -659838203874218756167337
    s21_decimal decimal_check = {{0x9B0A56A9, 0xE694B2F7, 0x8BB9, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok951) {
    // 33505473283.521159124328454689
    s21_decimal decimal = {{0x3F391A21, 0x351A5B45, 0x6C4313F2, 0x120000}};
    // 33505473283
    s21_decimal decimal_check = {{0xCD14F303, 0x7, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok952) {
    // -33505473283.521159124328454689
    s21_decimal decimal = {{0x3F391A21, 0x351A5B45, 0x6C4313F2, 0x80120000}};
    // -33505473284
    s21_decimal decimal_check = {{0xCD14F304, 0x7, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok953) {
    // 42794156996734.364765895432863
    s21_decimal decimal = {{0x73529A9F, 0x46FA576B, 0x8A467F3B, 0xF0000}};
    // 42794156996734
    s21_decimal decimal_check = {{0xCA86B87E, 0x26EB, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok954) {
    // -42794156996734.364765895432863
    s21_decimal decimal = {{0x73529A9F, 0x46FA576B, 0x8A467F3B, 0x800F0000}};
    // -42794156996735
    s21_decimal decimal_check = {{0xCA86B87F, 0x26EB, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok955) {
    // 221835745721144256183.64586357
    s21_decimal decimal = {{0x95035975, 0x3AA1E3AB, 0x47ADD2A3, 0x80000}};
    // 221835745721144256183
    s21_decimal decimal_check = {{0xB0AF26B7, 0x696E365, 0xC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok956) {
    // -221835745721144256183.64586357
    s21_decimal decimal = {{0x95035975, 0x3AA1E3AB, 0x47ADD2A3, 0x80080000}};
    // -221835745721144256184
    s21_decimal decimal_check = {{0xB0AF26B8, 0x696E365, 0xC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok957) {
    // -78118641435.233640829805305200
    s21_decimal decimal = {{0x8D1E9D70, 0xC8EA26E7, 0xFC6A39C5, 0x80120000}};
    // -78118641436
    s21_decimal decimal_check = {{0x303BDF1C, 0x12, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok958) {
    // 78118641435.233640829805305200
    s21_decimal decimal = {{0x8D1E9D70, 0xC8EA26E7, 0xFC6A39C5, 0x120000}};
    // 78118641435
    s21_decimal decimal_check = {{0x303BDF1B, 0x12, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok959) {
    // -1826.9970014736306536530021530
    s21_decimal decimal = {{0x2638C9A, 0xFA4AA70, 0x3B0890A3, 0x80190000}};
    // -1827
    s21_decimal decimal_check = {{0x723, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok960) {
    // 1826.9970014736306536530021530
    s21_decimal decimal = {{0x2638C9A, 0xFA4AA70, 0x3B0890A3, 0x190000}};
    // 1826
    s21_decimal decimal_check = {{0x722, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok961) {
    // 403725251132738407528928915.67
    s21_decimal decimal = {{0x6678D1AF, 0xD3ACB79F, 0x82735EBB, 0x20000}};
    // 403725251132738407528928915
    s21_decimal decimal_check = {{0xE9FC1693, 0xB7E07279, 0x14DF425, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok962) {
    // -403725251132738407528928915.67
    s21_decimal decimal = {{0x6678D1AF, 0xD3ACB79F, 0x82735EBB, 0x80020000}};
    // -403725251132738407528928916
    s21_decimal decimal_check = {{0xE9FC1694, 0xB7E07279, 0x14DF425, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok963) {
    // -418075755937264206440123729.56
    s21_decimal decimal = {{0x92E233DC, 0x40E5D427, 0x87166A7E, 0x80020000}};
    // -418075755937264206440123730
    s21_decimal decimal_check = {{0x3C594D52, 0x247D2DA4, 0x159D2FC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok964) {
    // 418075755937264206440123729.56
    s21_decimal decimal = {{0x92E233DC, 0x40E5D427, 0x87166A7E, 0x20000}};
    // 418075755937264206440123729
    s21_decimal decimal_check = {{0x3C594D51, 0x247D2DA4, 0x159D2FC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok965) {
    // -5897558599823.724707705582381
    s21_decimal decimal = {{0x783CF32D, 0x508146BB, 0x130E589C, 0x800F0000}};
    // -5897558599824
    s21_decimal decimal_check = {{0x21E2A890, 0x55D, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok966) {
    // 5897558599823.724707705582381
    s21_decimal decimal = {{0x783CF32D, 0x508146BB, 0x130E589C, 0xF0000}};
    // 5897558599823
    s21_decimal decimal_check = {{0x21E2A88F, 0x55D, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok967) {
    // -2822114502781.064017994064325
    s21_decimal decimal = {{0x32B821C5, 0xBEF38F7A, 0x91E65FD, 0x800F0000}};
    // -2822114502782
    s21_decimal decimal_check = {{0x1321E87E, 0x291, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok968) {
    // 2822114502781.064017994064325
    s21_decimal decimal = {{0x32B821C5, 0xBEF38F7A, 0x91E65FD, 0xF0000}};
    // 2822114502781
    s21_decimal decimal_check = {{0x1321E87D, 0x291, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok969) {
    // -19652085016446477268462.30948
    s21_decimal decimal = {{0x71A2C1A4, 0x57EFFA09, 0x6599516, 0x80050000}};
    // -19652085016446477268463
    s21_decimal decimal_check = {{0xCCE7F5EF, 0x5777413F, 0x429, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok970) {
    // 19652085016446477268462.30948
    s21_decimal decimal = {{0x71A2C1A4, 0x57EFFA09, 0x6599516, 0x50000}};
    // 19652085016446477268462
    s21_decimal decimal_check = {{0xCCE7F5EE, 0x5777413F, 0x429, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok971) {
    // 6671072523184299681953844146.7
    s21_decimal decimal = {{0xF3BB74FB, 0x38EE555F, 0xD78DD18D, 0x10000}};
    // 6671072523184299681953844146
    s21_decimal decimal_check = {{0x985F8BB2, 0x1F4B0889, 0x158E2E8E, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok972) {
    // -6671072523184299681953844146.7
    s21_decimal decimal = {{0xF3BB74FB, 0x38EE555F, 0xD78DD18D, 0x80010000}};
    // -6671072523184299681953844147
    s21_decimal decimal_check = {{0x985F8BB3, 0x1F4B0889, 0x158E2E8E, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok973) {
    // -1323829833753506080519742.7458
    s21_decimal decimal = {{0xA1EAF302, 0xE0DABDCF, 0x2AC676B6, 0x80040000}};
    // -1323829833753506080519743
    s21_decimal decimal_check = {{0xBDE763F, 0xF586C7C0, 0x11854, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok974) {
    // 1323829833753506080519742.7458
    s21_decimal decimal = {{0xA1EAF302, 0xE0DABDCF, 0x2AC676B6, 0x40000}};
    // 1323829833753506080519742
    s21_decimal decimal_check = {{0xBDE763E, 0xF586C7C0, 0x11854, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok975) {
    // 70090781359870730295.175487829
    s21_decimal decimal = {{0x8772155, 0x1433EB61, 0xE279BC47, 0x90000}};
    // 70090781359870730295
    s21_decimal decimal_check = {{0x38AA6037, 0xCCB47A4A, 0x3, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok976) {
    // -70090781359870730295.175487829
    s21_decimal decimal = {{0x8772155, 0x1433EB61, 0xE279BC47, 0x80090000}};
    // -70090781359870730296
    s21_decimal decimal_check = {{0x38AA6038, 0xCCB47A4A, 0x3, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok977) {
    // 7838639824335946771.6076389392
    s21_decimal decimal = {{0x27A04410, 0x702EBCFF, 0xFD47B57B, 0xA0000}};
    // 7838639824335946771
    s21_decimal decimal_check = {{0xABC64413, 0x6CC87163, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok978) {
    // -7838639824335946771.6076389392
    s21_decimal decimal = {{0x27A04410, 0x702EBCFF, 0xFD47B57B, 0x800A0000}};
    // -7838639824335946772
    s21_decimal decimal_check = {{0xABC64414, 0x6CC87163, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok979) {
    // -49884113751604963262320001.100
    s21_decimal decimal = {{0x6FBAC04C, 0x19A72079, 0xA12F2BF9, 0x80030000}};
    // -49884113751604963262320002
    s21_decimal decimal_check = {{0xD34FCD82, 0x39A02AC8, 0x29435F, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok980) {
    // 49884113751604963262320001.100
    s21_decimal decimal = {{0x6FBAC04C, 0x19A72079, 0xA12F2BF9, 0x30000}};
    // 49884113751604963262320001
    s21_decimal decimal_check = {{0xD34FCD81, 0x39A02AC8, 0x29435F, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok981) {
    // -418.03667881090130984861937839
    s21_decimal decimal = {{0x7CF7B0AF, 0xBA1E0F96, 0x87132F00, 0x801A0000}};
    // -419
    s21_decimal decimal_check = {{0x1A3, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok982) {
    // 418.03667881090130984861937839
    s21_decimal decimal = {{0x7CF7B0AF, 0xBA1E0F96, 0x87132F00, 0x1A0000}};
    // 418
    s21_decimal decimal_check = {{0x1A2, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok983) {
    // 10.895949287935134738030218960
    s21_decimal decimal = {{0xD4A74ED0, 0x76ABBB28, 0x2334EB02, 0x1B0000}};
    // 10
    s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok984) {
    // -10.895949287935134738030218960
    s21_decimal decimal = {{0xD4A74ED0, 0x76ABBB28, 0x2334EB02, 0x801B0000}};
    // -11
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok985) {
    // -13248351991607.710738984961195
    s21_decimal decimal = {{0x7CDF84AB, 0x8EC492BF, 0x2ACEC7A8, 0x800F0000}};
    // -13248351991608
    s21_decimal decimal_check = {{0x9F507738, 0xC0C, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok986) {
    // 13248351991607.710738984961195
    s21_decimal decimal = {{0x7CDF84AB, 0x8EC492BF, 0x2ACEC7A8, 0xF0000}};
    // 13248351991607
    s21_decimal decimal_check = {{0x9F507737, 0xC0C, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok987) {
    // 67914878835999760.800404134171
    s21_decimal decimal = {{0xB65ED91B, 0xE76EFE1C, 0xDB71DEFE, 0xC0000}};
    // 67914878835999760
    s21_decimal decimal_check = {{0xF3FBC410, 0xF14838, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok988) {
    // -67914878835999760.800404134171
    s21_decimal decimal = {{0xB65ED91B, 0xE76EFE1C, 0xDB71DEFE, 0x800C0000}};
    // -67914878835999761
    s21_decimal decimal_check = {{0xF3FBC411, 0xF14838, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok989) {
    // -13.260140503658773017911273939
    s21_decimal decimal = {{0xB932A9D3, 0x13951634, 0x2AD887F9, 0x801B0000}};
    // -14
    s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok990) {
    // 13.260140503658773017911273939
    s21_decimal decimal = {{0xB932A9D3, 0x13951634, 0x2AD887F9, 0x1B0000}};
    // 13
    s21_decimal decimal_check = {{0xD, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok991) {
    // -15426903213682917.679016649010
    s21_decimal decimal = {{0xD3332132, 0xF32EB570, 0x31D8D5D2, 0x800C0000}};
    // -15426903213682918
    s21_decimal decimal_check = {{0xCE0930E6, 0x36CEAF, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok992) {
    // 15426903213682917.679016649010
    s21_decimal decimal = {{0xD3332132, 0xF32EB570, 0x31D8D5D2, 0xC0000}};
    // 15426903213682917
    s21_decimal decimal_check = {{0xCE0930E5, 0x36CEAF, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok993) {
    // 1099802757484705478867073.7973
    s21_decimal decimal = {{0x2B1B4E35, 0x7C383B4A, 0x23895AED, 0x40000}};
    // 1099802757484705478867073
    s21_decimal decimal_check = {{0xA903F881, 0x6D4C7F98, 0xE8E4, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok994) {
    // -1099802757484705478867073.7973
    s21_decimal decimal = {{0x2B1B4E35, 0x7C383B4A, 0x23895AED, 0x80040000}};
    // -1099802757484705478867074
    s21_decimal decimal_check = {{0xA903F882, 0x6D4C7F98, 0xE8E4, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok995) {
    // -37160482441386038.669183262143
    s21_decimal decimal = {{0x7EBF9DBF, 0xAD92037A, 0x78126E3D, 0x800C0000}};
    // -37160482441386039
    s21_decimal decimal_check = {{0xB99D837, 0x840543, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok996) {
    // 37160482441386038.669183262143
    s21_decimal decimal = {{0x7EBF9DBF, 0xAD92037A, 0x78126E3D, 0xC0000}};
    // 37160482441386038
    s21_decimal decimal_check = {{0xB99D836, 0x840543, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok997) {
    // 250022923982557000202802016.81
    s21_decimal decimal = {{0x63D491D1, 0xC3ECCE9E, 0x50C9695A, 0x20000}};
    // 250022923982557000202802016
    s21_decimal decimal_check = {{0xA9F55360, 0xDE1E872F, 0xCED069, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok998) {
    // -250022923982557000202802016.81
    s21_decimal decimal = {{0x63D491D1, 0xC3ECCE9E, 0x50C9695A, 0x80020000}};
    // -250022923982557000202802017
    s21_decimal decimal_check = {{0xA9F55361, 0xDE1E872F, 0xCED069, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok999) {
    // 1.352189313665630166626265632
    s21_decimal decimal = {{0x6EEEEA20, 0x930BBED3, 0x45E8139, 0x1B0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1000) {
    // -1.352189313665630166626265632
    s21_decimal decimal = {{0x6EEEEA20, 0x930BBED3, 0x45E8139, 0x801B0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1001) {
    // -4493.3014343213978931642865294
    s21_decimal decimal = {{0x7AB9968E, 0x5C9B68BF, 0x912FB7E4, 0x80190000}};
    // -4494
    s21_decimal decimal_check = {{0x118E, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1002) {
    // 4493.3014343213978931642865294
    s21_decimal decimal = {{0x7AB9968E, 0x5C9B68BF, 0x912FB7E4, 0x190000}};
    // 4493
    s21_decimal decimal_check = {{0x118D, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1003) {
    // 2804562322050080374522.2289274
    s21_decimal decimal = {{0xA678E77A, 0x380629B5, 0x5A9ECBB9, 0x70000}};
    // 2804562322050080374522
    s21_decimal decimal_check = {{0x4FB8FEFA, 0x91EECB2, 0x98, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1004) {
    // -2804562322050080374522.2289274
    s21_decimal decimal = {{0xA678E77A, 0x380629B5, 0x5A9ECBB9, 0x80070000}};
    // -2804562322050080374523
    s21_decimal decimal_check = {{0x4FB8FEFB, 0x91EECB2, 0x98, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1005) {
    // -1.3773595030477839624555241923
    s21_decimal decimal = {{0x51D0A1C3, 0xBFBD392C, 0x2C814032, 0x801C0000}};
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1006) {
    // 1.3773595030477839624555241923
    s21_decimal decimal = {{0x51D0A1C3, 0xBFBD392C, 0x2C814032, 0x1C0000}};
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1007) {
    // -6232396428889964695550075603.2
    s21_decimal decimal = {{0xABE25C40, 0xFF27B5EC, 0xC9612CC9, 0x80010000}};
    // -6232396428889964695550075604
    s21_decimal decimal_check = {{0x7796A2D4, 0x6650C564, 0x14235147, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1008) {
    // 6232396428889964695550075603.2
    s21_decimal decimal = {{0xABE25C40, 0xFF27B5EC, 0xC9612CC9, 0x10000}};
    // 6232396428889964695550075603
    s21_decimal decimal_check = {{0x7796A2D3, 0x6650C564, 0x14235147, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1009) {
    // 4071456280178008417014.1793669
    s21_decimal decimal = {{0x3558FD85, 0x130A2734, 0x838E4C08, 0x70000}};
    // 4071456280178008417014
    s21_decimal decimal_check = {{0x6F7A62F6, 0xB6CE6B52, 0xDC, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1010) {
    // -4071456280178008417014.1793669
    s21_decimal decimal = {{0x3558FD85, 0x130A2734, 0x838E4C08, 0x80070000}};
    // -4071456280178008417015
    s21_decimal decimal_check = {{0x6F7A62F7, 0xB6CE6B52, 0xDC, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1011) {
    // 62384159987888825957036205.053
    s21_decimal decimal = {{0x3623FD, 0x60AB863D, 0xC992F7B9, 0x30000}};
    // 62384159987888825957036205
    s21_decimal decimal_check = {{0x19DB30AD, 0x16E17397, 0x339A5C, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1012) {
    // -62384159987888825957036205.053
    s21_decimal decimal = {{0x3623FD, 0x60AB863D, 0xC992F7B9, 0x80030000}};
    // -62384159987888825957036206
    s21_decimal decimal_check = {{0x19DB30AE, 0x16E17397, 0x339A5C, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1013) {
    // -59661132671347.335693102082115
    s21_decimal decimal = {{0xB3C5E843, 0xC2D3267D, 0xC0C68842, 0x800F0000}};
    // -59661132671348
    s21_decimal decimal_check = {{0xF09EA974, 0x3642, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1014) {
    // 59661132671347.335693102082115
    s21_decimal decimal = {{0xB3C5E843, 0xC2D3267D, 0xC0C68842, 0xF0000}};
    // 59661132671347
    s21_decimal decimal_check = {{0xF09EA973, 0x3642, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1015) {
    // -1756702243.9163772433428207747
    s21_decimal decimal = {{0x43B95883, 0xA1D47999, 0x38C319B2, 0x80130000}};
    // -1756702244
    s21_decimal decimal_check = {{0x68B52624, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1016) {
    // 1756702243.9163772433428207747
    s21_decimal decimal = {{0x43B95883, 0xA1D47999, 0x38C319B2, 0x130000}};
    // 1756702243
    s21_decimal decimal_check = {{0x68B52623, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1017) {
    // 499690.17307003220935658068156
    s21_decimal decimal = {{0xDC4A58BC, 0xF995020, 0xA1756700, 0x170000}};
    // 499690
    s21_decimal decimal_check = {{0x79FEA, 0x0, 0x0, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1018) {
    // -499690.17307003220935658068156
    s21_decimal decimal = {{0xDC4A58BC, 0xF995020, 0xA1756700, 0x80170000}};
    // -499691
    s21_decimal decimal_check = {{0x79FEB, 0x0, 0x0, 0x80000000}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1019) {
    // 1724370152434521045164.8495949
    s21_decimal decimal = {{0x1F12C14D, 0xB826473C, 0x37B7A7D4, 0x70000}};
    // 1724370152434521045164
    s21_decimal decimal_check = {{0xD9CF78AC, 0x7A716D88, 0x5D, 0x0}};

    test_floor(decimal, decimal_check);
}

START_TEST(test_floor_ok1020) {
    // -1724370152434521045164.8495949
    s21_decimal decimal = {{0x1F12C14D, 0xB826473C, 0x37B7A7D4, 0x80070000}};
    // -1724370152434521045165
    s21_decimal decimal_check = {{0xD9CF78AD, 0x7A716D88, 0x5D, 0x80000000}};

    test_floor(decimal, decimal_check);
}


Suite *floor_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("floor_suite1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_floor_ok1);
    tcase_add_test(tc_core, test_floor_ok2);
    tcase_add_test(tc_core, test_floor_ok3);
    tcase_add_test(tc_core, test_floor_ok4);
    tcase_add_test(tc_core, test_floor_ok5);
    tcase_add_test(tc_core, test_floor_ok6);
    tcase_add_test(tc_core, test_floor_ok7);
    tcase_add_test(tc_core, test_floor_ok8);
    tcase_add_test(tc_core, test_floor_ok9);
    tcase_add_test(tc_core, test_floor_ok10);
    tcase_add_test(tc_core, test_floor_ok11);
    tcase_add_test(tc_core, test_floor_ok12);
    tcase_add_test(tc_core, test_floor_ok13);
    tcase_add_test(tc_core, test_floor_ok14);
    tcase_add_test(tc_core, test_floor_ok15);
    tcase_add_test(tc_core, test_floor_ok16);
    tcase_add_test(tc_core, test_floor_ok17);
    tcase_add_test(tc_core, test_floor_ok18);
    tcase_add_test(tc_core, test_floor_ok19);
    tcase_add_test(tc_core, test_floor_ok20);
    tcase_add_test(tc_core, test_floor_ok21);
    tcase_add_test(tc_core, test_floor_ok22);
    tcase_add_test(tc_core, test_floor_ok23);
    tcase_add_test(tc_core, test_floor_ok24);
    tcase_add_test(tc_core, test_floor_ok25);
    tcase_add_test(tc_core, test_floor_ok26);
    tcase_add_test(tc_core, test_floor_ok27);
    tcase_add_test(tc_core, test_floor_ok28);
    tcase_add_test(tc_core, test_floor_ok29);
    tcase_add_test(tc_core, test_floor_ok30);
    tcase_add_test(tc_core, test_floor_ok31);
    tcase_add_test(tc_core, test_floor_ok32);
    tcase_add_test(tc_core, test_floor_ok33);
    tcase_add_test(tc_core, test_floor_ok34);
    tcase_add_test(tc_core, test_floor_ok35);
    tcase_add_test(tc_core, test_floor_ok36);
    tcase_add_test(tc_core, test_floor_ok37);
    tcase_add_test(tc_core, test_floor_ok38);
    tcase_add_test(tc_core, test_floor_ok39);
    tcase_add_test(tc_core, test_floor_ok40);
    tcase_add_test(tc_core, test_floor_ok41);
    tcase_add_test(tc_core, test_floor_ok42);
    tcase_add_test(tc_core, test_floor_ok43);
    tcase_add_test(tc_core, test_floor_ok44);
    tcase_add_test(tc_core, test_floor_ok45);
    tcase_add_test(tc_core, test_floor_ok46);
    tcase_add_test(tc_core, test_floor_ok47);
    tcase_add_test(tc_core, test_floor_ok48);
    tcase_add_test(tc_core, test_floor_ok49);
    tcase_add_test(tc_core, test_floor_ok50);
    tcase_add_test(tc_core, test_floor_ok51);
    tcase_add_test(tc_core, test_floor_ok52);
    tcase_add_test(tc_core, test_floor_ok53);
    tcase_add_test(tc_core, test_floor_ok54);
    tcase_add_test(tc_core, test_floor_ok55);
    tcase_add_test(tc_core, test_floor_ok56);
    tcase_add_test(tc_core, test_floor_ok57);
    tcase_add_test(tc_core, test_floor_ok58);
    tcase_add_test(tc_core, test_floor_ok59);
    tcase_add_test(tc_core, test_floor_ok60);
    tcase_add_test(tc_core, test_floor_ok61);
    tcase_add_test(tc_core, test_floor_ok62);
    tcase_add_test(tc_core, test_floor_ok63);
    tcase_add_test(tc_core, test_floor_ok64);
    tcase_add_test(tc_core, test_floor_ok65);
    tcase_add_test(tc_core, test_floor_ok66);
    tcase_add_test(tc_core, test_floor_ok67);
    tcase_add_test(tc_core, test_floor_ok68);
    tcase_add_test(tc_core, test_floor_ok69);
    tcase_add_test(tc_core, test_floor_ok70);
    tcase_add_test(tc_core, test_floor_ok71);
    tcase_add_test(tc_core, test_floor_ok72);
    tcase_add_test(tc_core, test_floor_ok73);
    tcase_add_test(tc_core, test_floor_ok74);
    tcase_add_test(tc_core, test_floor_ok75);
    tcase_add_test(tc_core, test_floor_ok76);
    tcase_add_test(tc_core, test_floor_ok77);
    tcase_add_test(tc_core, test_floor_ok78);
    tcase_add_test(tc_core, test_floor_ok79);
    tcase_add_test(tc_core, test_floor_ok80);
    tcase_add_test(tc_core, test_floor_ok81);
    tcase_add_test(tc_core, test_floor_ok82);
    tcase_add_test(tc_core, test_floor_ok83);
    tcase_add_test(tc_core, test_floor_ok84);
    tcase_add_test(tc_core, test_floor_ok85);
    tcase_add_test(tc_core, test_floor_ok86);
    tcase_add_test(tc_core, test_floor_ok87);
    tcase_add_test(tc_core, test_floor_ok88);
    tcase_add_test(tc_core, test_floor_ok89);
    tcase_add_test(tc_core, test_floor_ok90);
    tcase_add_test(tc_core, test_floor_ok91);
    tcase_add_test(tc_core, test_floor_ok92);
    tcase_add_test(tc_core, test_floor_ok93);
    tcase_add_test(tc_core, test_floor_ok94);
    tcase_add_test(tc_core, test_floor_ok95);
    tcase_add_test(tc_core, test_floor_ok96);
    tcase_add_test(tc_core, test_floor_ok97);
    tcase_add_test(tc_core, test_floor_ok98);
    tcase_add_test(tc_core, test_floor_ok99);
    tcase_add_test(tc_core, test_floor_ok100);
    tcase_add_test(tc_core, test_floor_ok101);
    tcase_add_test(tc_core, test_floor_ok102);
    tcase_add_test(tc_core, test_floor_ok103);
    tcase_add_test(tc_core, test_floor_ok104);
    tcase_add_test(tc_core, test_floor_ok105);
    tcase_add_test(tc_core, test_floor_ok106);
    tcase_add_test(tc_core, test_floor_ok107);
    tcase_add_test(tc_core, test_floor_ok108);
    tcase_add_test(tc_core, test_floor_ok109);
    tcase_add_test(tc_core, test_floor_ok110);
    tcase_add_test(tc_core, test_floor_ok111);
    tcase_add_test(tc_core, test_floor_ok112);
    tcase_add_test(tc_core, test_floor_ok113);
    tcase_add_test(tc_core, test_floor_ok114);
    tcase_add_test(tc_core, test_floor_ok115);
    tcase_add_test(tc_core, test_floor_ok116);
    tcase_add_test(tc_core, test_floor_ok117);
    tcase_add_test(tc_core, test_floor_ok118);
    tcase_add_test(tc_core, test_floor_ok119);
    tcase_add_test(tc_core, test_floor_ok120);
    tcase_add_test(tc_core, test_floor_ok121);
    tcase_add_test(tc_core, test_floor_ok122);
    tcase_add_test(tc_core, test_floor_ok123);
    tcase_add_test(tc_core, test_floor_ok124);
    tcase_add_test(tc_core, test_floor_ok125);
    tcase_add_test(tc_core, test_floor_ok126);
    tcase_add_test(tc_core, test_floor_ok127);
    tcase_add_test(tc_core, test_floor_ok128);
    tcase_add_test(tc_core, test_floor_ok129);
    tcase_add_test(tc_core, test_floor_ok130);
    tcase_add_test(tc_core, test_floor_ok131);
    tcase_add_test(tc_core, test_floor_ok132);
    tcase_add_test(tc_core, test_floor_ok133);
    tcase_add_test(tc_core, test_floor_ok134);
    tcase_add_test(tc_core, test_floor_ok135);
    tcase_add_test(tc_core, test_floor_ok136);
    tcase_add_test(tc_core, test_floor_ok137);
    tcase_add_test(tc_core, test_floor_ok138);
    tcase_add_test(tc_core, test_floor_ok139);
    tcase_add_test(tc_core, test_floor_ok140);
    tcase_add_test(tc_core, test_floor_ok141);
    tcase_add_test(tc_core, test_floor_ok142);
    tcase_add_test(tc_core, test_floor_ok143);
    tcase_add_test(tc_core, test_floor_ok144);
    tcase_add_test(tc_core, test_floor_ok145);
    tcase_add_test(tc_core, test_floor_ok146);
    tcase_add_test(tc_core, test_floor_ok147);
    tcase_add_test(tc_core, test_floor_ok148);
    tcase_add_test(tc_core, test_floor_ok149);
    tcase_add_test(tc_core, test_floor_ok150);
    tcase_add_test(tc_core, test_floor_ok151);
    tcase_add_test(tc_core, test_floor_ok152);
    tcase_add_test(tc_core, test_floor_ok153);
    tcase_add_test(tc_core, test_floor_ok154);
    tcase_add_test(tc_core, test_floor_ok155);
    tcase_add_test(tc_core, test_floor_ok156);
    tcase_add_test(tc_core, test_floor_ok157);
    tcase_add_test(tc_core, test_floor_ok158);
    tcase_add_test(tc_core, test_floor_ok159);
    tcase_add_test(tc_core, test_floor_ok160);
    tcase_add_test(tc_core, test_floor_ok161);
    tcase_add_test(tc_core, test_floor_ok162);
    tcase_add_test(tc_core, test_floor_ok163);
    tcase_add_test(tc_core, test_floor_ok164);
    tcase_add_test(tc_core, test_floor_ok165);
    tcase_add_test(tc_core, test_floor_ok166);
    tcase_add_test(tc_core, test_floor_ok167);
    tcase_add_test(tc_core, test_floor_ok168);
    tcase_add_test(tc_core, test_floor_ok169);
    tcase_add_test(tc_core, test_floor_ok170);
    tcase_add_test(tc_core, test_floor_ok171);
    tcase_add_test(tc_core, test_floor_ok172);
    tcase_add_test(tc_core, test_floor_ok173);
    tcase_add_test(tc_core, test_floor_ok174);
    tcase_add_test(tc_core, test_floor_ok175);
    tcase_add_test(tc_core, test_floor_ok176);
    tcase_add_test(tc_core, test_floor_ok177);
    tcase_add_test(tc_core, test_floor_ok178);
    tcase_add_test(tc_core, test_floor_ok179);
    tcase_add_test(tc_core, test_floor_ok180);
    tcase_add_test(tc_core, test_floor_ok181);
    tcase_add_test(tc_core, test_floor_ok182);
    tcase_add_test(tc_core, test_floor_ok183);
    tcase_add_test(tc_core, test_floor_ok184);
    tcase_add_test(tc_core, test_floor_ok185);
    tcase_add_test(tc_core, test_floor_ok186);
    tcase_add_test(tc_core, test_floor_ok187);
    tcase_add_test(tc_core, test_floor_ok188);
    tcase_add_test(tc_core, test_floor_ok189);
    tcase_add_test(tc_core, test_floor_ok190);
    tcase_add_test(tc_core, test_floor_ok191);
    tcase_add_test(tc_core, test_floor_ok192);
    tcase_add_test(tc_core, test_floor_ok193);
    tcase_add_test(tc_core, test_floor_ok194);
    tcase_add_test(tc_core, test_floor_ok195);
    tcase_add_test(tc_core, test_floor_ok196);
    tcase_add_test(tc_core, test_floor_ok197);
    tcase_add_test(tc_core, test_floor_ok198);
    tcase_add_test(tc_core, test_floor_ok199);
    tcase_add_test(tc_core, test_floor_ok200);
    tcase_add_test(tc_core, test_floor_ok201);
    tcase_add_test(tc_core, test_floor_ok202);
    tcase_add_test(tc_core, test_floor_ok203);
    tcase_add_test(tc_core, test_floor_ok204);
    tcase_add_test(tc_core, test_floor_ok205);
    tcase_add_test(tc_core, test_floor_ok206);
    tcase_add_test(tc_core, test_floor_ok207);
    tcase_add_test(tc_core, test_floor_ok208);
    tcase_add_test(tc_core, test_floor_ok209);
    tcase_add_test(tc_core, test_floor_ok210);
    tcase_add_test(tc_core, test_floor_ok211);
    tcase_add_test(tc_core, test_floor_ok212);
    tcase_add_test(tc_core, test_floor_ok213);
    tcase_add_test(tc_core, test_floor_ok214);
    tcase_add_test(tc_core, test_floor_ok215);
    tcase_add_test(tc_core, test_floor_ok216);
    tcase_add_test(tc_core, test_floor_ok217);
    tcase_add_test(tc_core, test_floor_ok218);
    tcase_add_test(tc_core, test_floor_ok219);
    tcase_add_test(tc_core, test_floor_ok220);
    tcase_add_test(tc_core, test_floor_ok221);
    tcase_add_test(tc_core, test_floor_ok222);
    tcase_add_test(tc_core, test_floor_ok223);
    tcase_add_test(tc_core, test_floor_ok224);
    tcase_add_test(tc_core, test_floor_ok225);
    tcase_add_test(tc_core, test_floor_ok226);
    tcase_add_test(tc_core, test_floor_ok227);
    tcase_add_test(tc_core, test_floor_ok228);
    tcase_add_test(tc_core, test_floor_ok229);
    tcase_add_test(tc_core, test_floor_ok230);
    tcase_add_test(tc_core, test_floor_ok231);
    tcase_add_test(tc_core, test_floor_ok232);
    tcase_add_test(tc_core, test_floor_ok233);
    tcase_add_test(tc_core, test_floor_ok234);
    tcase_add_test(tc_core, test_floor_ok235);
    tcase_add_test(tc_core, test_floor_ok236);
    tcase_add_test(tc_core, test_floor_ok237);
    tcase_add_test(tc_core, test_floor_ok238);
    tcase_add_test(tc_core, test_floor_ok239);
    tcase_add_test(tc_core, test_floor_ok240);
    tcase_add_test(tc_core, test_floor_ok241);
    tcase_add_test(tc_core, test_floor_ok242);
    tcase_add_test(tc_core, test_floor_ok243);
    tcase_add_test(tc_core, test_floor_ok244);
    tcase_add_test(tc_core, test_floor_ok245);
    tcase_add_test(tc_core, test_floor_ok246);
    tcase_add_test(tc_core, test_floor_ok247);
    tcase_add_test(tc_core, test_floor_ok248);
    tcase_add_test(tc_core, test_floor_ok249);
    tcase_add_test(tc_core, test_floor_ok250);
    tcase_add_test(tc_core, test_floor_ok251);
    tcase_add_test(tc_core, test_floor_ok252);
    tcase_add_test(tc_core, test_floor_ok253);
    tcase_add_test(tc_core, test_floor_ok254);
    tcase_add_test(tc_core, test_floor_ok255);
    tcase_add_test(tc_core, test_floor_ok256);
    tcase_add_test(tc_core, test_floor_ok257);
    tcase_add_test(tc_core, test_floor_ok258);
    tcase_add_test(tc_core, test_floor_ok259);
    tcase_add_test(tc_core, test_floor_ok260);
    tcase_add_test(tc_core, test_floor_ok261);
    tcase_add_test(tc_core, test_floor_ok262);
    tcase_add_test(tc_core, test_floor_ok263);
    tcase_add_test(tc_core, test_floor_ok264);
    tcase_add_test(tc_core, test_floor_ok265);
    tcase_add_test(tc_core, test_floor_ok266);
    tcase_add_test(tc_core, test_floor_ok267);
    tcase_add_test(tc_core, test_floor_ok268);
    tcase_add_test(tc_core, test_floor_ok269);
    tcase_add_test(tc_core, test_floor_ok270);
    tcase_add_test(tc_core, test_floor_ok271);
    tcase_add_test(tc_core, test_floor_ok272);
    tcase_add_test(tc_core, test_floor_ok273);
    tcase_add_test(tc_core, test_floor_ok274);
    tcase_add_test(tc_core, test_floor_ok275);
    tcase_add_test(tc_core, test_floor_ok276);
    tcase_add_test(tc_core, test_floor_ok277);
    tcase_add_test(tc_core, test_floor_ok278);
    tcase_add_test(tc_core, test_floor_ok279);
    tcase_add_test(tc_core, test_floor_ok280);
    tcase_add_test(tc_core, test_floor_ok281);
    tcase_add_test(tc_core, test_floor_ok282);
    tcase_add_test(tc_core, test_floor_ok283);
    tcase_add_test(tc_core, test_floor_ok284);
    tcase_add_test(tc_core, test_floor_ok285);
    tcase_add_test(tc_core, test_floor_ok286);
    tcase_add_test(tc_core, test_floor_ok287);
    tcase_add_test(tc_core, test_floor_ok288);
    tcase_add_test(tc_core, test_floor_ok289);
    tcase_add_test(tc_core, test_floor_ok290);
    tcase_add_test(tc_core, test_floor_ok291);
    tcase_add_test(tc_core, test_floor_ok292);
    tcase_add_test(tc_core, test_floor_ok293);
    tcase_add_test(tc_core, test_floor_ok294);
    tcase_add_test(tc_core, test_floor_ok295);
    tcase_add_test(tc_core, test_floor_ok296);
    tcase_add_test(tc_core, test_floor_ok297);
    tcase_add_test(tc_core, test_floor_ok298);
    tcase_add_test(tc_core, test_floor_ok299);
    tcase_add_test(tc_core, test_floor_ok300);
    tcase_add_test(tc_core, test_floor_ok301);
    tcase_add_test(tc_core, test_floor_ok302);
    tcase_add_test(tc_core, test_floor_ok303);
    tcase_add_test(tc_core, test_floor_ok304);
    tcase_add_test(tc_core, test_floor_ok305);
    tcase_add_test(tc_core, test_floor_ok306);
    tcase_add_test(tc_core, test_floor_ok307);
    tcase_add_test(tc_core, test_floor_ok308);
    tcase_add_test(tc_core, test_floor_ok309);
    tcase_add_test(tc_core, test_floor_ok310);
    tcase_add_test(tc_core, test_floor_ok311);
    tcase_add_test(tc_core, test_floor_ok312);
    tcase_add_test(tc_core, test_floor_ok313);
    tcase_add_test(tc_core, test_floor_ok314);
    tcase_add_test(tc_core, test_floor_ok315);
    tcase_add_test(tc_core, test_floor_ok316);
    tcase_add_test(tc_core, test_floor_ok317);
    tcase_add_test(tc_core, test_floor_ok318);
    tcase_add_test(tc_core, test_floor_ok319);
    tcase_add_test(tc_core, test_floor_ok320);
    tcase_add_test(tc_core, test_floor_ok321);
    tcase_add_test(tc_core, test_floor_ok322);
    tcase_add_test(tc_core, test_floor_ok323);
    tcase_add_test(tc_core, test_floor_ok324);
    tcase_add_test(tc_core, test_floor_ok325);
    tcase_add_test(tc_core, test_floor_ok326);
    tcase_add_test(tc_core, test_floor_ok327);
    tcase_add_test(tc_core, test_floor_ok328);
    tcase_add_test(tc_core, test_floor_ok329);
    tcase_add_test(tc_core, test_floor_ok330);
    tcase_add_test(tc_core, test_floor_ok331);
    tcase_add_test(tc_core, test_floor_ok332);
    tcase_add_test(tc_core, test_floor_ok333);
    tcase_add_test(tc_core, test_floor_ok334);
    tcase_add_test(tc_core, test_floor_ok335);
    tcase_add_test(tc_core, test_floor_ok336);
    tcase_add_test(tc_core, test_floor_ok337);
    tcase_add_test(tc_core, test_floor_ok338);
    tcase_add_test(tc_core, test_floor_ok339);
    tcase_add_test(tc_core, test_floor_ok340);
    tcase_add_test(tc_core, test_floor_ok341);
    tcase_add_test(tc_core, test_floor_ok342);
    tcase_add_test(tc_core, test_floor_ok343);
    tcase_add_test(tc_core, test_floor_ok344);
    tcase_add_test(tc_core, test_floor_ok345);
    tcase_add_test(tc_core, test_floor_ok346);
    tcase_add_test(tc_core, test_floor_ok347);
    tcase_add_test(tc_core, test_floor_ok348);
    tcase_add_test(tc_core, test_floor_ok349);
    tcase_add_test(tc_core, test_floor_ok350);
    tcase_add_test(tc_core, test_floor_ok351);
    tcase_add_test(tc_core, test_floor_ok352);
    tcase_add_test(tc_core, test_floor_ok353);
    tcase_add_test(tc_core, test_floor_ok354);
    tcase_add_test(tc_core, test_floor_ok355);
    tcase_add_test(tc_core, test_floor_ok356);
    tcase_add_test(tc_core, test_floor_ok357);
    tcase_add_test(tc_core, test_floor_ok358);
    tcase_add_test(tc_core, test_floor_ok359);
    tcase_add_test(tc_core, test_floor_ok360);
    tcase_add_test(tc_core, test_floor_ok361);
    tcase_add_test(tc_core, test_floor_ok362);
    tcase_add_test(tc_core, test_floor_ok363);
    tcase_add_test(tc_core, test_floor_ok364);
    tcase_add_test(tc_core, test_floor_ok365);
    tcase_add_test(tc_core, test_floor_ok366);
    tcase_add_test(tc_core, test_floor_ok367);
    tcase_add_test(tc_core, test_floor_ok368);
    tcase_add_test(tc_core, test_floor_ok369);
    tcase_add_test(tc_core, test_floor_ok370);
    tcase_add_test(tc_core, test_floor_ok371);
    tcase_add_test(tc_core, test_floor_ok372);
    tcase_add_test(tc_core, test_floor_ok373);
    tcase_add_test(tc_core, test_floor_ok374);
    tcase_add_test(tc_core, test_floor_ok375);
    tcase_add_test(tc_core, test_floor_ok376);
    tcase_add_test(tc_core, test_floor_ok377);
    tcase_add_test(tc_core, test_floor_ok378);
    tcase_add_test(tc_core, test_floor_ok379);
    tcase_add_test(tc_core, test_floor_ok380);
    tcase_add_test(tc_core, test_floor_ok381);
    tcase_add_test(tc_core, test_floor_ok382);
    tcase_add_test(tc_core, test_floor_ok383);
    tcase_add_test(tc_core, test_floor_ok384);
    tcase_add_test(tc_core, test_floor_ok385);
    tcase_add_test(tc_core, test_floor_ok386);
    tcase_add_test(tc_core, test_floor_ok387);
    tcase_add_test(tc_core, test_floor_ok388);
    tcase_add_test(tc_core, test_floor_ok389);
    tcase_add_test(tc_core, test_floor_ok390);
    tcase_add_test(tc_core, test_floor_ok391);
    tcase_add_test(tc_core, test_floor_ok392);
    tcase_add_test(tc_core, test_floor_ok393);
    tcase_add_test(tc_core, test_floor_ok394);
    tcase_add_test(tc_core, test_floor_ok395);
    tcase_add_test(tc_core, test_floor_ok396);
    tcase_add_test(tc_core, test_floor_ok397);
    tcase_add_test(tc_core, test_floor_ok398);
    tcase_add_test(tc_core, test_floor_ok399);
    tcase_add_test(tc_core, test_floor_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *floor_suite2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("floor_suite2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_floor_ok401);
    tcase_add_test(tc_core, test_floor_ok402);
    tcase_add_test(tc_core, test_floor_ok403);
    tcase_add_test(tc_core, test_floor_ok404);
    tcase_add_test(tc_core, test_floor_ok405);
    tcase_add_test(tc_core, test_floor_ok406);
    tcase_add_test(tc_core, test_floor_ok407);
    tcase_add_test(tc_core, test_floor_ok408);
    tcase_add_test(tc_core, test_floor_ok409);
    tcase_add_test(tc_core, test_floor_ok410);
    tcase_add_test(tc_core, test_floor_ok411);
    tcase_add_test(tc_core, test_floor_ok412);
    tcase_add_test(tc_core, test_floor_ok413);
    tcase_add_test(tc_core, test_floor_ok414);
    tcase_add_test(tc_core, test_floor_ok415);
    tcase_add_test(tc_core, test_floor_ok416);
    tcase_add_test(tc_core, test_floor_ok417);
    tcase_add_test(tc_core, test_floor_ok418);
    tcase_add_test(tc_core, test_floor_ok419);
    tcase_add_test(tc_core, test_floor_ok420);
    tcase_add_test(tc_core, test_floor_ok421);
    tcase_add_test(tc_core, test_floor_ok422);
    tcase_add_test(tc_core, test_floor_ok423);
    tcase_add_test(tc_core, test_floor_ok424);
    tcase_add_test(tc_core, test_floor_ok425);
    tcase_add_test(tc_core, test_floor_ok426);
    tcase_add_test(tc_core, test_floor_ok427);
    tcase_add_test(tc_core, test_floor_ok428);
    tcase_add_test(tc_core, test_floor_ok429);
    tcase_add_test(tc_core, test_floor_ok430);
    tcase_add_test(tc_core, test_floor_ok431);
    tcase_add_test(tc_core, test_floor_ok432);
    tcase_add_test(tc_core, test_floor_ok433);
    tcase_add_test(tc_core, test_floor_ok434);
    tcase_add_test(tc_core, test_floor_ok435);
    tcase_add_test(tc_core, test_floor_ok436);
    tcase_add_test(tc_core, test_floor_ok437);
    tcase_add_test(tc_core, test_floor_ok438);
    tcase_add_test(tc_core, test_floor_ok439);
    tcase_add_test(tc_core, test_floor_ok440);
    tcase_add_test(tc_core, test_floor_ok441);
    tcase_add_test(tc_core, test_floor_ok442);
    tcase_add_test(tc_core, test_floor_ok443);
    tcase_add_test(tc_core, test_floor_ok444);
    tcase_add_test(tc_core, test_floor_ok445);
    tcase_add_test(tc_core, test_floor_ok446);
    tcase_add_test(tc_core, test_floor_ok447);
    tcase_add_test(tc_core, test_floor_ok448);
    tcase_add_test(tc_core, test_floor_ok449);
    tcase_add_test(tc_core, test_floor_ok450);
    tcase_add_test(tc_core, test_floor_ok451);
    tcase_add_test(tc_core, test_floor_ok452);
    tcase_add_test(tc_core, test_floor_ok453);
    tcase_add_test(tc_core, test_floor_ok454);
    tcase_add_test(tc_core, test_floor_ok455);
    tcase_add_test(tc_core, test_floor_ok456);
    tcase_add_test(tc_core, test_floor_ok457);
    tcase_add_test(tc_core, test_floor_ok458);
    tcase_add_test(tc_core, test_floor_ok459);
    tcase_add_test(tc_core, test_floor_ok460);
    tcase_add_test(tc_core, test_floor_ok461);
    tcase_add_test(tc_core, test_floor_ok462);
    tcase_add_test(tc_core, test_floor_ok463);
    tcase_add_test(tc_core, test_floor_ok464);
    tcase_add_test(tc_core, test_floor_ok465);
    tcase_add_test(tc_core, test_floor_ok466);
    tcase_add_test(tc_core, test_floor_ok467);
    tcase_add_test(tc_core, test_floor_ok468);
    tcase_add_test(tc_core, test_floor_ok469);
    tcase_add_test(tc_core, test_floor_ok470);
    tcase_add_test(tc_core, test_floor_ok471);
    tcase_add_test(tc_core, test_floor_ok472);
    tcase_add_test(tc_core, test_floor_ok473);
    tcase_add_test(tc_core, test_floor_ok474);
    tcase_add_test(tc_core, test_floor_ok475);
    tcase_add_test(tc_core, test_floor_ok476);
    tcase_add_test(tc_core, test_floor_ok477);
    tcase_add_test(tc_core, test_floor_ok478);
    tcase_add_test(tc_core, test_floor_ok479);
    tcase_add_test(tc_core, test_floor_ok480);
    tcase_add_test(tc_core, test_floor_ok481);
    tcase_add_test(tc_core, test_floor_ok482);
    tcase_add_test(tc_core, test_floor_ok483);
    tcase_add_test(tc_core, test_floor_ok484);
    tcase_add_test(tc_core, test_floor_ok485);
    tcase_add_test(tc_core, test_floor_ok486);
    tcase_add_test(tc_core, test_floor_ok487);
    tcase_add_test(tc_core, test_floor_ok488);
    tcase_add_test(tc_core, test_floor_ok489);
    tcase_add_test(tc_core, test_floor_ok490);
    tcase_add_test(tc_core, test_floor_ok491);
    tcase_add_test(tc_core, test_floor_ok492);
    tcase_add_test(tc_core, test_floor_ok493);
    tcase_add_test(tc_core, test_floor_ok494);
    tcase_add_test(tc_core, test_floor_ok495);
    tcase_add_test(tc_core, test_floor_ok496);
    tcase_add_test(tc_core, test_floor_ok497);
    tcase_add_test(tc_core, test_floor_ok498);
    tcase_add_test(tc_core, test_floor_ok499);
    tcase_add_test(tc_core, test_floor_ok500);
    tcase_add_test(tc_core, test_floor_ok501);
    tcase_add_test(tc_core, test_floor_ok502);
    tcase_add_test(tc_core, test_floor_ok503);
    tcase_add_test(tc_core, test_floor_ok504);
    tcase_add_test(tc_core, test_floor_ok505);
    tcase_add_test(tc_core, test_floor_ok506);
    tcase_add_test(tc_core, test_floor_ok507);
    tcase_add_test(tc_core, test_floor_ok508);
    tcase_add_test(tc_core, test_floor_ok509);
    tcase_add_test(tc_core, test_floor_ok510);
    tcase_add_test(tc_core, test_floor_ok511);
    tcase_add_test(tc_core, test_floor_ok512);
    tcase_add_test(tc_core, test_floor_ok513);
    tcase_add_test(tc_core, test_floor_ok514);
    tcase_add_test(tc_core, test_floor_ok515);
    tcase_add_test(tc_core, test_floor_ok516);
    tcase_add_test(tc_core, test_floor_ok517);
    tcase_add_test(tc_core, test_floor_ok518);
    tcase_add_test(tc_core, test_floor_ok519);
    tcase_add_test(tc_core, test_floor_ok520);
    tcase_add_test(tc_core, test_floor_ok521);
    tcase_add_test(tc_core, test_floor_ok522);
    tcase_add_test(tc_core, test_floor_ok523);
    tcase_add_test(tc_core, test_floor_ok524);
    tcase_add_test(tc_core, test_floor_ok525);
    tcase_add_test(tc_core, test_floor_ok526);
    tcase_add_test(tc_core, test_floor_ok527);
    tcase_add_test(tc_core, test_floor_ok528);
    tcase_add_test(tc_core, test_floor_ok529);
    tcase_add_test(tc_core, test_floor_ok530);
    tcase_add_test(tc_core, test_floor_ok531);
    tcase_add_test(tc_core, test_floor_ok532);
    tcase_add_test(tc_core, test_floor_ok533);
    tcase_add_test(tc_core, test_floor_ok534);
    tcase_add_test(tc_core, test_floor_ok535);
    tcase_add_test(tc_core, test_floor_ok536);
    tcase_add_test(tc_core, test_floor_ok537);
    tcase_add_test(tc_core, test_floor_ok538);
    tcase_add_test(tc_core, test_floor_ok539);
    tcase_add_test(tc_core, test_floor_ok540);
    tcase_add_test(tc_core, test_floor_ok541);
    tcase_add_test(tc_core, test_floor_ok542);
    tcase_add_test(tc_core, test_floor_ok543);
    tcase_add_test(tc_core, test_floor_ok544);
    tcase_add_test(tc_core, test_floor_ok545);
    tcase_add_test(tc_core, test_floor_ok546);
    tcase_add_test(tc_core, test_floor_ok547);
    tcase_add_test(tc_core, test_floor_ok548);
    tcase_add_test(tc_core, test_floor_ok549);
    tcase_add_test(tc_core, test_floor_ok550);
    tcase_add_test(tc_core, test_floor_ok551);
    tcase_add_test(tc_core, test_floor_ok552);
    tcase_add_test(tc_core, test_floor_ok553);
    tcase_add_test(tc_core, test_floor_ok554);
    tcase_add_test(tc_core, test_floor_ok555);
    tcase_add_test(tc_core, test_floor_ok556);
    tcase_add_test(tc_core, test_floor_ok557);
    tcase_add_test(tc_core, test_floor_ok558);
    tcase_add_test(tc_core, test_floor_ok559);
    tcase_add_test(tc_core, test_floor_ok560);
    tcase_add_test(tc_core, test_floor_ok561);
    tcase_add_test(tc_core, test_floor_ok562);
    tcase_add_test(tc_core, test_floor_ok563);
    tcase_add_test(tc_core, test_floor_ok564);
    tcase_add_test(tc_core, test_floor_ok565);
    tcase_add_test(tc_core, test_floor_ok566);
    tcase_add_test(tc_core, test_floor_ok567);
    tcase_add_test(tc_core, test_floor_ok568);
    tcase_add_test(tc_core, test_floor_ok569);
    tcase_add_test(tc_core, test_floor_ok570);
    tcase_add_test(tc_core, test_floor_ok571);
    tcase_add_test(tc_core, test_floor_ok572);
    tcase_add_test(tc_core, test_floor_ok573);
    tcase_add_test(tc_core, test_floor_ok574);
    tcase_add_test(tc_core, test_floor_ok575);
    tcase_add_test(tc_core, test_floor_ok576);
    tcase_add_test(tc_core, test_floor_ok577);
    tcase_add_test(tc_core, test_floor_ok578);
    tcase_add_test(tc_core, test_floor_ok579);
    tcase_add_test(tc_core, test_floor_ok580);
    tcase_add_test(tc_core, test_floor_ok581);
    tcase_add_test(tc_core, test_floor_ok582);
    tcase_add_test(tc_core, test_floor_ok583);
    tcase_add_test(tc_core, test_floor_ok584);
    tcase_add_test(tc_core, test_floor_ok585);
    tcase_add_test(tc_core, test_floor_ok586);
    tcase_add_test(tc_core, test_floor_ok587);
    tcase_add_test(tc_core, test_floor_ok588);
    tcase_add_test(tc_core, test_floor_ok589);
    tcase_add_test(tc_core, test_floor_ok590);
    tcase_add_test(tc_core, test_floor_ok591);
    tcase_add_test(tc_core, test_floor_ok592);
    tcase_add_test(tc_core, test_floor_ok593);
    tcase_add_test(tc_core, test_floor_ok594);
    tcase_add_test(tc_core, test_floor_ok595);
    tcase_add_test(tc_core, test_floor_ok596);
    tcase_add_test(tc_core, test_floor_ok597);
    tcase_add_test(tc_core, test_floor_ok598);
    tcase_add_test(tc_core, test_floor_ok599);
    tcase_add_test(tc_core, test_floor_ok600);
    tcase_add_test(tc_core, test_floor_ok601);
    tcase_add_test(tc_core, test_floor_ok602);
    tcase_add_test(tc_core, test_floor_ok603);
    tcase_add_test(tc_core, test_floor_ok604);
    tcase_add_test(tc_core, test_floor_ok605);
    tcase_add_test(tc_core, test_floor_ok606);
    tcase_add_test(tc_core, test_floor_ok607);
    tcase_add_test(tc_core, test_floor_ok608);
    tcase_add_test(tc_core, test_floor_ok609);
    tcase_add_test(tc_core, test_floor_ok610);
    tcase_add_test(tc_core, test_floor_ok611);
    tcase_add_test(tc_core, test_floor_ok612);
    tcase_add_test(tc_core, test_floor_ok613);
    tcase_add_test(tc_core, test_floor_ok614);
    tcase_add_test(tc_core, test_floor_ok615);
    tcase_add_test(tc_core, test_floor_ok616);
    tcase_add_test(tc_core, test_floor_ok617);
    tcase_add_test(tc_core, test_floor_ok618);
    tcase_add_test(tc_core, test_floor_ok619);
    tcase_add_test(tc_core, test_floor_ok620);
    tcase_add_test(tc_core, test_floor_ok621);
    tcase_add_test(tc_core, test_floor_ok622);
    tcase_add_test(tc_core, test_floor_ok623);
    tcase_add_test(tc_core, test_floor_ok624);
    tcase_add_test(tc_core, test_floor_ok625);
    tcase_add_test(tc_core, test_floor_ok626);
    tcase_add_test(tc_core, test_floor_ok627);
    tcase_add_test(tc_core, test_floor_ok628);
    tcase_add_test(tc_core, test_floor_ok629);
    tcase_add_test(tc_core, test_floor_ok630);
    tcase_add_test(tc_core, test_floor_ok631);
    tcase_add_test(tc_core, test_floor_ok632);
    tcase_add_test(tc_core, test_floor_ok633);
    tcase_add_test(tc_core, test_floor_ok634);
    tcase_add_test(tc_core, test_floor_ok635);
    tcase_add_test(tc_core, test_floor_ok636);
    tcase_add_test(tc_core, test_floor_ok637);
    tcase_add_test(tc_core, test_floor_ok638);
    tcase_add_test(tc_core, test_floor_ok639);
    tcase_add_test(tc_core, test_floor_ok640);
    tcase_add_test(tc_core, test_floor_ok641);
    tcase_add_test(tc_core, test_floor_ok642);
    tcase_add_test(tc_core, test_floor_ok643);
    tcase_add_test(tc_core, test_floor_ok644);
    tcase_add_test(tc_core, test_floor_ok645);
    tcase_add_test(tc_core, test_floor_ok646);
    tcase_add_test(tc_core, test_floor_ok647);
    tcase_add_test(tc_core, test_floor_ok648);
    tcase_add_test(tc_core, test_floor_ok649);
    tcase_add_test(tc_core, test_floor_ok650);
    tcase_add_test(tc_core, test_floor_ok651);
    tcase_add_test(tc_core, test_floor_ok652);
    tcase_add_test(tc_core, test_floor_ok653);
    tcase_add_test(tc_core, test_floor_ok654);
    tcase_add_test(tc_core, test_floor_ok655);
    tcase_add_test(tc_core, test_floor_ok656);
    tcase_add_test(tc_core, test_floor_ok657);
    tcase_add_test(tc_core, test_floor_ok658);
    tcase_add_test(tc_core, test_floor_ok659);
    tcase_add_test(tc_core, test_floor_ok660);
    tcase_add_test(tc_core, test_floor_ok661);
    tcase_add_test(tc_core, test_floor_ok662);
    tcase_add_test(tc_core, test_floor_ok663);
    tcase_add_test(tc_core, test_floor_ok664);
    tcase_add_test(tc_core, test_floor_ok665);
    tcase_add_test(tc_core, test_floor_ok666);
    tcase_add_test(tc_core, test_floor_ok667);
    tcase_add_test(tc_core, test_floor_ok668);
    tcase_add_test(tc_core, test_floor_ok669);
    tcase_add_test(tc_core, test_floor_ok670);
    tcase_add_test(tc_core, test_floor_ok671);
    tcase_add_test(tc_core, test_floor_ok672);
    tcase_add_test(tc_core, test_floor_ok673);
    tcase_add_test(tc_core, test_floor_ok674);
    tcase_add_test(tc_core, test_floor_ok675);
    tcase_add_test(tc_core, test_floor_ok676);
    tcase_add_test(tc_core, test_floor_ok677);
    tcase_add_test(tc_core, test_floor_ok678);
    tcase_add_test(tc_core, test_floor_ok679);
    tcase_add_test(tc_core, test_floor_ok680);
    tcase_add_test(tc_core, test_floor_ok681);
    tcase_add_test(tc_core, test_floor_ok682);
    tcase_add_test(tc_core, test_floor_ok683);
    tcase_add_test(tc_core, test_floor_ok684);
    tcase_add_test(tc_core, test_floor_ok685);
    tcase_add_test(tc_core, test_floor_ok686);
    tcase_add_test(tc_core, test_floor_ok687);
    tcase_add_test(tc_core, test_floor_ok688);
    tcase_add_test(tc_core, test_floor_ok689);
    tcase_add_test(tc_core, test_floor_ok690);
    tcase_add_test(tc_core, test_floor_ok691);
    tcase_add_test(tc_core, test_floor_ok692);
    tcase_add_test(tc_core, test_floor_ok693);
    tcase_add_test(tc_core, test_floor_ok694);
    tcase_add_test(tc_core, test_floor_ok695);
    tcase_add_test(tc_core, test_floor_ok696);
    tcase_add_test(tc_core, test_floor_ok697);
    tcase_add_test(tc_core, test_floor_ok698);
    tcase_add_test(tc_core, test_floor_ok699);
    tcase_add_test(tc_core, test_floor_ok700);
    tcase_add_test(tc_core, test_floor_ok701);
    tcase_add_test(tc_core, test_floor_ok702);
    tcase_add_test(tc_core, test_floor_ok703);
    tcase_add_test(tc_core, test_floor_ok704);
    tcase_add_test(tc_core, test_floor_ok705);
    tcase_add_test(tc_core, test_floor_ok706);
    tcase_add_test(tc_core, test_floor_ok707);
    tcase_add_test(tc_core, test_floor_ok708);
    tcase_add_test(tc_core, test_floor_ok709);
    tcase_add_test(tc_core, test_floor_ok710);
    tcase_add_test(tc_core, test_floor_ok711);
    tcase_add_test(tc_core, test_floor_ok712);
    tcase_add_test(tc_core, test_floor_ok713);
    tcase_add_test(tc_core, test_floor_ok714);
    tcase_add_test(tc_core, test_floor_ok715);
    tcase_add_test(tc_core, test_floor_ok716);
    tcase_add_test(tc_core, test_floor_ok717);
    tcase_add_test(tc_core, test_floor_ok718);
    tcase_add_test(tc_core, test_floor_ok719);
    tcase_add_test(tc_core, test_floor_ok720);
    tcase_add_test(tc_core, test_floor_ok721);
    tcase_add_test(tc_core, test_floor_ok722);
    tcase_add_test(tc_core, test_floor_ok723);
    tcase_add_test(tc_core, test_floor_ok724);
    tcase_add_test(tc_core, test_floor_ok725);
    tcase_add_test(tc_core, test_floor_ok726);
    tcase_add_test(tc_core, test_floor_ok727);
    tcase_add_test(tc_core, test_floor_ok728);
    tcase_add_test(tc_core, test_floor_ok729);
    tcase_add_test(tc_core, test_floor_ok730);
    tcase_add_test(tc_core, test_floor_ok731);
    tcase_add_test(tc_core, test_floor_ok732);
    tcase_add_test(tc_core, test_floor_ok733);
    tcase_add_test(tc_core, test_floor_ok734);
    tcase_add_test(tc_core, test_floor_ok735);
    tcase_add_test(tc_core, test_floor_ok736);
    tcase_add_test(tc_core, test_floor_ok737);
    tcase_add_test(tc_core, test_floor_ok738);
    tcase_add_test(tc_core, test_floor_ok739);
    tcase_add_test(tc_core, test_floor_ok740);
    tcase_add_test(tc_core, test_floor_ok741);
    tcase_add_test(tc_core, test_floor_ok742);
    tcase_add_test(tc_core, test_floor_ok743);
    tcase_add_test(tc_core, test_floor_ok744);
    tcase_add_test(tc_core, test_floor_ok745);
    tcase_add_test(tc_core, test_floor_ok746);
    tcase_add_test(tc_core, test_floor_ok747);
    tcase_add_test(tc_core, test_floor_ok748);
    tcase_add_test(tc_core, test_floor_ok749);
    tcase_add_test(tc_core, test_floor_ok750);
    tcase_add_test(tc_core, test_floor_ok751);
    tcase_add_test(tc_core, test_floor_ok752);
    tcase_add_test(tc_core, test_floor_ok753);
    tcase_add_test(tc_core, test_floor_ok754);
    tcase_add_test(tc_core, test_floor_ok755);
    tcase_add_test(tc_core, test_floor_ok756);
    tcase_add_test(tc_core, test_floor_ok757);
    tcase_add_test(tc_core, test_floor_ok758);
    tcase_add_test(tc_core, test_floor_ok759);
    tcase_add_test(tc_core, test_floor_ok760);
    tcase_add_test(tc_core, test_floor_ok761);
    tcase_add_test(tc_core, test_floor_ok762);
    tcase_add_test(tc_core, test_floor_ok763);
    tcase_add_test(tc_core, test_floor_ok764);
    tcase_add_test(tc_core, test_floor_ok765);
    tcase_add_test(tc_core, test_floor_ok766);
    tcase_add_test(tc_core, test_floor_ok767);
    tcase_add_test(tc_core, test_floor_ok768);
    tcase_add_test(tc_core, test_floor_ok769);
    tcase_add_test(tc_core, test_floor_ok770);
    tcase_add_test(tc_core, test_floor_ok771);
    tcase_add_test(tc_core, test_floor_ok772);
    tcase_add_test(tc_core, test_floor_ok773);
    tcase_add_test(tc_core, test_floor_ok774);
    tcase_add_test(tc_core, test_floor_ok775);
    tcase_add_test(tc_core, test_floor_ok776);
    tcase_add_test(tc_core, test_floor_ok777);
    tcase_add_test(tc_core, test_floor_ok778);
    tcase_add_test(tc_core, test_floor_ok779);
    tcase_add_test(tc_core, test_floor_ok780);
    tcase_add_test(tc_core, test_floor_ok781);
    tcase_add_test(tc_core, test_floor_ok782);
    tcase_add_test(tc_core, test_floor_ok783);
    tcase_add_test(tc_core, test_floor_ok784);
    tcase_add_test(tc_core, test_floor_ok785);
    tcase_add_test(tc_core, test_floor_ok786);
    tcase_add_test(tc_core, test_floor_ok787);
    tcase_add_test(tc_core, test_floor_ok788);
    tcase_add_test(tc_core, test_floor_ok789);
    tcase_add_test(tc_core, test_floor_ok790);
    tcase_add_test(tc_core, test_floor_ok791);
    tcase_add_test(tc_core, test_floor_ok792);
    tcase_add_test(tc_core, test_floor_ok793);
    tcase_add_test(tc_core, test_floor_ok794);
    tcase_add_test(tc_core, test_floor_ok795);
    tcase_add_test(tc_core, test_floor_ok796);
    tcase_add_test(tc_core, test_floor_ok797);
    tcase_add_test(tc_core, test_floor_ok798);
    tcase_add_test(tc_core, test_floor_ok799);
    tcase_add_test(tc_core, test_floor_ok800);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *floor_suite3(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("floor_suite3");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_floor_ok801);
    tcase_add_test(tc_core, test_floor_ok802);
    tcase_add_test(tc_core, test_floor_ok803);
    tcase_add_test(tc_core, test_floor_ok804);
    tcase_add_test(tc_core, test_floor_ok805);
    tcase_add_test(tc_core, test_floor_ok806);
    tcase_add_test(tc_core, test_floor_ok807);
    tcase_add_test(tc_core, test_floor_ok808);
    tcase_add_test(tc_core, test_floor_ok809);
    tcase_add_test(tc_core, test_floor_ok810);
    tcase_add_test(tc_core, test_floor_ok811);
    tcase_add_test(tc_core, test_floor_ok812);
    tcase_add_test(tc_core, test_floor_ok813);
    tcase_add_test(tc_core, test_floor_ok814);
    tcase_add_test(tc_core, test_floor_ok815);
    tcase_add_test(tc_core, test_floor_ok816);
    tcase_add_test(tc_core, test_floor_ok817);
    tcase_add_test(tc_core, test_floor_ok818);
    tcase_add_test(tc_core, test_floor_ok819);
    tcase_add_test(tc_core, test_floor_ok820);
    tcase_add_test(tc_core, test_floor_ok821);
    tcase_add_test(tc_core, test_floor_ok822);
    tcase_add_test(tc_core, test_floor_ok823);
    tcase_add_test(tc_core, test_floor_ok824);
    tcase_add_test(tc_core, test_floor_ok825);
    tcase_add_test(tc_core, test_floor_ok826);
    tcase_add_test(tc_core, test_floor_ok827);
    tcase_add_test(tc_core, test_floor_ok828);
    tcase_add_test(tc_core, test_floor_ok829);
    tcase_add_test(tc_core, test_floor_ok830);
    tcase_add_test(tc_core, test_floor_ok831);
    tcase_add_test(tc_core, test_floor_ok832);
    tcase_add_test(tc_core, test_floor_ok833);
    tcase_add_test(tc_core, test_floor_ok834);
    tcase_add_test(tc_core, test_floor_ok835);
    tcase_add_test(tc_core, test_floor_ok836);
    tcase_add_test(tc_core, test_floor_ok837);
    tcase_add_test(tc_core, test_floor_ok838);
    tcase_add_test(tc_core, test_floor_ok839);
    tcase_add_test(tc_core, test_floor_ok840);
    tcase_add_test(tc_core, test_floor_ok841);
    tcase_add_test(tc_core, test_floor_ok842);
    tcase_add_test(tc_core, test_floor_ok843);
    tcase_add_test(tc_core, test_floor_ok844);
    tcase_add_test(tc_core, test_floor_ok845);
    tcase_add_test(tc_core, test_floor_ok846);
    tcase_add_test(tc_core, test_floor_ok847);
    tcase_add_test(tc_core, test_floor_ok848);
    tcase_add_test(tc_core, test_floor_ok849);
    tcase_add_test(tc_core, test_floor_ok850);
    tcase_add_test(tc_core, test_floor_ok851);
    tcase_add_test(tc_core, test_floor_ok852);
    tcase_add_test(tc_core, test_floor_ok853);
    tcase_add_test(tc_core, test_floor_ok854);
    tcase_add_test(tc_core, test_floor_ok855);
    tcase_add_test(tc_core, test_floor_ok856);
    tcase_add_test(tc_core, test_floor_ok857);
    tcase_add_test(tc_core, test_floor_ok858);
    tcase_add_test(tc_core, test_floor_ok859);
    tcase_add_test(tc_core, test_floor_ok860);
    tcase_add_test(tc_core, test_floor_ok861);
    tcase_add_test(tc_core, test_floor_ok862);
    tcase_add_test(tc_core, test_floor_ok863);
    tcase_add_test(tc_core, test_floor_ok864);
    tcase_add_test(tc_core, test_floor_ok865);
    tcase_add_test(tc_core, test_floor_ok866);
    tcase_add_test(tc_core, test_floor_ok867);
    tcase_add_test(tc_core, test_floor_ok868);
    tcase_add_test(tc_core, test_floor_ok869);
    tcase_add_test(tc_core, test_floor_ok870);
    tcase_add_test(tc_core, test_floor_ok871);
    tcase_add_test(tc_core, test_floor_ok872);
    tcase_add_test(tc_core, test_floor_ok873);
    tcase_add_test(tc_core, test_floor_ok874);
    tcase_add_test(tc_core, test_floor_ok875);
    tcase_add_test(tc_core, test_floor_ok876);
    tcase_add_test(tc_core, test_floor_ok877);
    tcase_add_test(tc_core, test_floor_ok878);
    tcase_add_test(tc_core, test_floor_ok879);
    tcase_add_test(tc_core, test_floor_ok880);
    tcase_add_test(tc_core, test_floor_ok881);
    tcase_add_test(tc_core, test_floor_ok882);
    tcase_add_test(tc_core, test_floor_ok883);
    tcase_add_test(tc_core, test_floor_ok884);
    tcase_add_test(tc_core, test_floor_ok885);
    tcase_add_test(tc_core, test_floor_ok886);
    tcase_add_test(tc_core, test_floor_ok887);
    tcase_add_test(tc_core, test_floor_ok888);
    tcase_add_test(tc_core, test_floor_ok889);
    tcase_add_test(tc_core, test_floor_ok890);
    tcase_add_test(tc_core, test_floor_ok891);
    tcase_add_test(tc_core, test_floor_ok892);
    tcase_add_test(tc_core, test_floor_ok893);
    tcase_add_test(tc_core, test_floor_ok894);
    tcase_add_test(tc_core, test_floor_ok895);
    tcase_add_test(tc_core, test_floor_ok896);
    tcase_add_test(tc_core, test_floor_ok897);
    tcase_add_test(tc_core, test_floor_ok898);
    tcase_add_test(tc_core, test_floor_ok899);
    tcase_add_test(tc_core, test_floor_ok900);
    tcase_add_test(tc_core, test_floor_ok901);
    tcase_add_test(tc_core, test_floor_ok902);
    tcase_add_test(tc_core, test_floor_ok903);
    tcase_add_test(tc_core, test_floor_ok904);
    tcase_add_test(tc_core, test_floor_ok905);
    tcase_add_test(tc_core, test_floor_ok906);
    tcase_add_test(tc_core, test_floor_ok907);
    tcase_add_test(tc_core, test_floor_ok908);
    tcase_add_test(tc_core, test_floor_ok909);
    tcase_add_test(tc_core, test_floor_ok910);
    tcase_add_test(tc_core, test_floor_ok911);
    tcase_add_test(tc_core, test_floor_ok912);
    tcase_add_test(tc_core, test_floor_ok913);
    tcase_add_test(tc_core, test_floor_ok914);
    tcase_add_test(tc_core, test_floor_ok915);
    tcase_add_test(tc_core, test_floor_ok916);
    tcase_add_test(tc_core, test_floor_ok917);
    tcase_add_test(tc_core, test_floor_ok918);
    tcase_add_test(tc_core, test_floor_ok919);
    tcase_add_test(tc_core, test_floor_ok920);
    tcase_add_test(tc_core, test_floor_ok921);
    tcase_add_test(tc_core, test_floor_ok922);
    tcase_add_test(tc_core, test_floor_ok923);
    tcase_add_test(tc_core, test_floor_ok924);
    tcase_add_test(tc_core, test_floor_ok925);
    tcase_add_test(tc_core, test_floor_ok926);
    tcase_add_test(tc_core, test_floor_ok927);
    tcase_add_test(tc_core, test_floor_ok928);
    tcase_add_test(tc_core, test_floor_ok929);
    tcase_add_test(tc_core, test_floor_ok930);
    tcase_add_test(tc_core, test_floor_ok931);
    tcase_add_test(tc_core, test_floor_ok932);
    tcase_add_test(tc_core, test_floor_ok933);
    tcase_add_test(tc_core, test_floor_ok934);
    tcase_add_test(tc_core, test_floor_ok935);
    tcase_add_test(tc_core, test_floor_ok936);
    tcase_add_test(tc_core, test_floor_ok937);
    tcase_add_test(tc_core, test_floor_ok938);
    tcase_add_test(tc_core, test_floor_ok939);
    tcase_add_test(tc_core, test_floor_ok940);
    tcase_add_test(tc_core, test_floor_ok941);
    tcase_add_test(tc_core, test_floor_ok942);
    tcase_add_test(tc_core, test_floor_ok943);
    tcase_add_test(tc_core, test_floor_ok944);
    tcase_add_test(tc_core, test_floor_ok945);
    tcase_add_test(tc_core, test_floor_ok946);
    tcase_add_test(tc_core, test_floor_ok947);
    tcase_add_test(tc_core, test_floor_ok948);
    tcase_add_test(tc_core, test_floor_ok949);
    tcase_add_test(tc_core, test_floor_ok950);
    tcase_add_test(tc_core, test_floor_ok951);
    tcase_add_test(tc_core, test_floor_ok952);
    tcase_add_test(tc_core, test_floor_ok953);
    tcase_add_test(tc_core, test_floor_ok954);
    tcase_add_test(tc_core, test_floor_ok955);
    tcase_add_test(tc_core, test_floor_ok956);
    tcase_add_test(tc_core, test_floor_ok957);
    tcase_add_test(tc_core, test_floor_ok958);
    tcase_add_test(tc_core, test_floor_ok959);
    tcase_add_test(tc_core, test_floor_ok960);
    tcase_add_test(tc_core, test_floor_ok961);
    tcase_add_test(tc_core, test_floor_ok962);
    tcase_add_test(tc_core, test_floor_ok963);
    tcase_add_test(tc_core, test_floor_ok964);
    tcase_add_test(tc_core, test_floor_ok965);
    tcase_add_test(tc_core, test_floor_ok966);
    tcase_add_test(tc_core, test_floor_ok967);
    tcase_add_test(tc_core, test_floor_ok968);
    tcase_add_test(tc_core, test_floor_ok969);
    tcase_add_test(tc_core, test_floor_ok970);
    tcase_add_test(tc_core, test_floor_ok971);
    tcase_add_test(tc_core, test_floor_ok972);
    tcase_add_test(tc_core, test_floor_ok973);
    tcase_add_test(tc_core, test_floor_ok974);
    tcase_add_test(tc_core, test_floor_ok975);
    tcase_add_test(tc_core, test_floor_ok976);
    tcase_add_test(tc_core, test_floor_ok977);
    tcase_add_test(tc_core, test_floor_ok978);
    tcase_add_test(tc_core, test_floor_ok979);
    tcase_add_test(tc_core, test_floor_ok980);
    tcase_add_test(tc_core, test_floor_ok981);
    tcase_add_test(tc_core, test_floor_ok982);
    tcase_add_test(tc_core, test_floor_ok983);
    tcase_add_test(tc_core, test_floor_ok984);
    tcase_add_test(tc_core, test_floor_ok985);
    tcase_add_test(tc_core, test_floor_ok986);
    tcase_add_test(tc_core, test_floor_ok987);
    tcase_add_test(tc_core, test_floor_ok988);
    tcase_add_test(tc_core, test_floor_ok989);
    tcase_add_test(tc_core, test_floor_ok990);
    tcase_add_test(tc_core, test_floor_ok991);
    tcase_add_test(tc_core, test_floor_ok992);
    tcase_add_test(tc_core, test_floor_ok993);
    tcase_add_test(tc_core, test_floor_ok994);
    tcase_add_test(tc_core, test_floor_ok995);
    tcase_add_test(tc_core, test_floor_ok996);
    tcase_add_test(tc_core, test_floor_ok997);
    tcase_add_test(tc_core, test_floor_ok998);
    tcase_add_test(tc_core, test_floor_ok999);
    tcase_add_test(tc_core, test_floor_ok1000);
    tcase_add_test(tc_core, test_floor_ok1001);
    tcase_add_test(tc_core, test_floor_ok1002);
    tcase_add_test(tc_core, test_floor_ok1003);
    tcase_add_test(tc_core, test_floor_ok1004);
    tcase_add_test(tc_core, test_floor_ok1005);
    tcase_add_test(tc_core, test_floor_ok1006);
    tcase_add_test(tc_core, test_floor_ok1007);
    tcase_add_test(tc_core, test_floor_ok1008);
    tcase_add_test(tc_core, test_floor_ok1009);
    tcase_add_test(tc_core, test_floor_ok1010);
    tcase_add_test(tc_core, test_floor_ok1011);
    tcase_add_test(tc_core, test_floor_ok1012);
    tcase_add_test(tc_core, test_floor_ok1013);
    tcase_add_test(tc_core, test_floor_ok1014);
    tcase_add_test(tc_core, test_floor_ok1015);
    tcase_add_test(tc_core, test_floor_ok1016);
    tcase_add_test(tc_core, test_floor_ok1017);
    tcase_add_test(tc_core, test_floor_ok1018);
    tcase_add_test(tc_core, test_floor_ok1019);
    tcase_add_test(tc_core, test_floor_ok1020);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *floor_suite0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("floor_suite0");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_floor_fail1);
    tcase_add_test(tc_core, test_floor_fail2);
    tcase_add_test(tc_core, test_floor_fail3);
    tcase_add_test(tc_core, test_floor_fail4);
    tcase_add_test(tc_core, test_floor_fail5);
    tcase_add_test(tc_core, test_floor_fail6);
    tcase_add_test(tc_core, test_floor_fail7);
    tcase_add_test(tc_core, test_floor_fail8);
    tcase_add_test(tc_core, test_floor_fail9);

    suite_add_tcase(s, tc_core);
    return s;
}

void test_floor(s21_decimal decimal, s21_decimal decimal_check) {
    s21_decimal result;

    int code = s21_floor(decimal, &result);
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
