#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные decimal
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Степень от 0 до 28
// Для положительных чисел int[3] может быть:
// от 0x0 до 0x1C0000   (unsigned int)
// от 0x0 до 0x1C0000   (int)
// от 00000000 00000000 00000000 00000000 - степень 0
// до 00000000 00000000 00000000 00011100 - степень 28
//
// Для отрицательных чисел int[3] может быть:
// от 0x80000000 до 0x8000001C   (unsigned int)
// от -2147483648 до -2147483620 (int)
// от 10000000 00000000 00000000 00000000 - степень 0
// от 10000000 00000000 00000000 00011100 - степень 28
//
// Остальные значения не являются корректными

START_TEST(test_debug_fail1) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail2) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail4) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail5) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail6) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail7) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_fail8) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    char check[1024] = "(Incorrect Decimal)";

    test_debug(decimal, check);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты конструкторов
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// Тесты закомментированы, т.к. в тестируемой библиотеке их может не быть
// Для своей надо тесмтировать, иначе покрытия тестами не будет
START_TEST(test_debug_create1) {
    // s21_decimal decimal = s21_create_decimal_from_array(0xFFFFFFFF, 0x1, 0x0, 0x1C0000);
    // char check[1024] = "0.0000000000000000008589934591";

    // test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_create2) {
    // s21_decimal decimal = s21_create_decimal_from_data(1, 28, 0xFFFFFFFF, 0x1, 0x0);
    // char check[1024] = "-0.0000000000000000008589934591";

    // test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_create3) {
    // s21_decimal decimal = s21_create_decimal_from_strings(
    //     "11111111 11111111 11111111 11111111",
    //     "11111111 11111111 11111111 11111111",
    //     "00000000 00000000 00000000 00000001",
    //     "10000000 00011100 00000000 00000000");
    // char check[1024] = "-0.0000000036893488147419103231";

    // test_debug(decimal, check);
}
END_TEST

START_TEST(test_debug_create4) {
    // s21_decimal decimal = s21_create_decimal_from_strings(
    //     "11111111 11111111 11111111 11111111",
    //     "11111111 11111111 11111111 11111111",
    //     "00000000 00000000 00000000 00000051",
    //     "10000000 00011100 00000000 00000000");
    // char check[1024] = "(Incorrect Decimal)";

    // test_debug(decimal, check);
}
END_TEST


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_debug_ok1) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok2) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    char check[1024] = "7922816251426433759354395033.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    char check[1024] = "-7922816251426433759354395033.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok5) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    char check[1024] = "792281625142643375935439503.35";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok6) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    char check[1024] = "-792281625142643375935439503.35";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok7) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    char check[1024] = "79228162514264337593543950.335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok8) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    char check[1024] = "-79228162514264337593543950.335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok9) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    char check[1024] = "7922816251426433759354395.0335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok10) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    char check[1024] = "-7922816251426433759354395.0335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok11) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    char check[1024] = "792281625142643375935439.50335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok12) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    char check[1024] = "-792281625142643375935439.50335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok13) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    char check[1024] = "79228162514264337593543.950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok14) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    char check[1024] = "-79228162514264337593543.950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok15) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    char check[1024] = "7922816251426433759354.3950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok16) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    char check[1024] = "-7922816251426433759354.3950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok17) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    char check[1024] = "792281625142643375935.43950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok18) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    char check[1024] = "-792281625142643375935.43950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok19) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    char check[1024] = "79228162514264337593.543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok20) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    char check[1024] = "-79228162514264337593.543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok21) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    char check[1024] = "7922816251426433759.3543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok22) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    char check[1024] = "-7922816251426433759.3543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok23) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    char check[1024] = "792281625142643375.93543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok24) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    char check[1024] = "-792281625142643375.93543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok25) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    char check[1024] = "79228162514264337.593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok26) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    char check[1024] = "-79228162514264337.593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok27) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    char check[1024] = "7922816251426433.7593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok28) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    char check[1024] = "-7922816251426433.7593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok29) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    char check[1024] = "792281625142643.37593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok30) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    char check[1024] = "-792281625142643.37593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok31) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    char check[1024] = "79228162514264.337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok32) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    char check[1024] = "-79228162514264.337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok33) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    char check[1024] = "7922816251426.4337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok34) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    char check[1024] = "-7922816251426.4337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok35) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    char check[1024] = "792281625142.64337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok36) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    char check[1024] = "-792281625142.64337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok37) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    char check[1024] = "79228162514.264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok38) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    char check[1024] = "-79228162514.264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok39) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    char check[1024] = "7922816251.4264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok40) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    char check[1024] = "-7922816251.4264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok41) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    char check[1024] = "792281625.14264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok42) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    char check[1024] = "-792281625.14264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok43) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    char check[1024] = "79228162.514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok44) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    char check[1024] = "-79228162.514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok45) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    char check[1024] = "7922816.2514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok46) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    char check[1024] = "-7922816.2514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok47) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    char check[1024] = "792281.62514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok48) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    char check[1024] = "-792281.62514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok49) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    char check[1024] = "79228.162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok50) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    char check[1024] = "-79228.162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok51) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    char check[1024] = "7922.8162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok52) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    char check[1024] = "-7922.8162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok53) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    char check[1024] = "792.28162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok54) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    char check[1024] = "-792.28162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok55) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    char check[1024] = "79.228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok56) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    char check[1024] = "-79.228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok57) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok58) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    char check[1024] = "-7.9228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok59) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok60) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok61) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    char check[1024] = "7922816251426433759354395033.4";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok62) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    char check[1024] = "-7922816251426433759354395033.4";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok63) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
    char check[1024] = "792281625142643375935439503.34";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok64) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
    char check[1024] = "-792281625142643375935439503.34";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok65) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
    char check[1024] = "79228162514264337593543950.334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok66) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
    char check[1024] = "-79228162514264337593543950.334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok67) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
    char check[1024] = "7922816251426433759354395.0334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok68) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
    char check[1024] = "-7922816251426433759354395.0334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok69) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
    char check[1024] = "792281625142643375935439.50334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok70) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
    char check[1024] = "-792281625142643375935439.50334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok71) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
    char check[1024] = "79228162514264337593543.950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok72) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
    char check[1024] = "-79228162514264337593543.950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok73) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
    char check[1024] = "7922816251426433759354.3950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok74) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
    char check[1024] = "-7922816251426433759354.3950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok75) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
    char check[1024] = "792281625142643375935.43950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok76) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
    char check[1024] = "-792281625142643375935.43950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok77) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
    char check[1024] = "79228162514264337593.543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok78) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
    char check[1024] = "-79228162514264337593.543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok79) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
    char check[1024] = "7922816251426433759.3543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok80) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
    char check[1024] = "-7922816251426433759.3543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok81) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
    char check[1024] = "792281625142643375.93543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok82) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
    char check[1024] = "-792281625142643375.93543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok83) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
    char check[1024] = "79228162514264337.593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok84) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
    char check[1024] = "-79228162514264337.593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok85) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
    char check[1024] = "7922816251426433.7593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok86) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
    char check[1024] = "-7922816251426433.7593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok87) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
    char check[1024] = "792281625142643.37593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok88) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
    char check[1024] = "-792281625142643.37593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok89) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
    char check[1024] = "79228162514264.337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok90) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
    char check[1024] = "-79228162514264.337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok91) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
    char check[1024] = "7922816251426.4337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok92) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
    char check[1024] = "-7922816251426.4337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok93) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
    char check[1024] = "792281625142.64337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok94) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
    char check[1024] = "-792281625142.64337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok95) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
    char check[1024] = "79228162514.264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok96) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
    char check[1024] = "-79228162514.264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok97) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
    char check[1024] = "7922816251.4264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok98) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
    char check[1024] = "-7922816251.4264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok99) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    char check[1024] = "792281625.14264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok100) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    char check[1024] = "-792281625.14264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok101) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    char check[1024] = "79228162.514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok102) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    char check[1024] = "-79228162.514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok103) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    char check[1024] = "7922816.2514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok104) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    char check[1024] = "-7922816.2514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok105) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    char check[1024] = "792281.62514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok106) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    char check[1024] = "-792281.62514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok107) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    char check[1024] = "79228.162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok108) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    char check[1024] = "-79228.162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok109) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    char check[1024] = "7922.8162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok110) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    char check[1024] = "-7922.8162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok111) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    char check[1024] = "792.28162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok112) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    char check[1024] = "-792.28162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok113) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    char check[1024] = "79.228162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok114) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    char check[1024] = "-79.228162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok115) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok116) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    char check[1024] = "-7.9228162514264337593543950334";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok117) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    char check[1024] = "52818775009509558395695966890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok118) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    char check[1024] = "-52818775009509558395695966890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok119) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    char check[1024] = "5281877500950955839569596689.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok120) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    char check[1024] = "-5281877500950955839569596689.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok121) {
    // 528187750.09509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
    char check[1024] = "528187750.09509558395695966890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok122) {
    // -528187750.09509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
    char check[1024] = "-528187750.09509558395695966890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok123) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    char check[1024] = "5.2818775009509558395695966890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok124) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    char check[1024] = "-5.2818775009509558395695966890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok125) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
    char check[1024] = "52818775009509558392832655360";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok126) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
    char check[1024] = "-52818775009509558392832655360";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok127) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
    char check[1024] = "5281877500950955839283265536.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok128) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
    char check[1024] = "-5281877500950955839283265536.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok129) {
    // 528187750.09509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
    char check[1024] = "528187750.09509558392832655360";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok130) {
    // -528187750.09509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
    char check[1024] = "-528187750.09509558392832655360";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok131) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    char check[1024] = "5.2818775009509558392832655360";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok132) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    char check[1024] = "-5.2818775009509558392832655360";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok133) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};
    char check[1024] = "52818774997211729016086244010";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok134) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};
    char check[1024] = "-52818774997211729016086244010";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok135) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};
    char check[1024] = "5281877499721172901608624401.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok136) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};
    char check[1024] = "-5281877499721172901608624401.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok137) {
    // 528187749.97211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x140000}};
    char check[1024] = "528187749.97211729016086244010";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok138) {
    // -528187749.97211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80140000}};
    char check[1024] = "-528187749.97211729016086244010";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok139) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    char check[1024] = "5.2818774997211729016086244010";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok140) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    char check[1024] = "-5.2818774997211729016086244010";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok141) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};
    char check[1024] = "52818774997211729013222932480";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok142) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};
    char check[1024] = "-52818774997211729013222932480";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok143) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};
    char check[1024] = "5281877499721172901322293248.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok144) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};
    char check[1024] = "-5281877499721172901322293248.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok145) {
    // 528187749.97211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x140000}};
    char check[1024] = "528187749.97211729013222932480";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok146) {
    // -528187749.97211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80140000}};
    char check[1024] = "-528187749.97211729013222932480";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok147) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    char check[1024] = "5.2818774997211729013222932480";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok148) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    char check[1024] = "-5.2818774997211729013222932480";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok149) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};
    char check[1024] = "12297829382473034410";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok150) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};
    char check[1024] = "-12297829382473034410";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok151) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};
    char check[1024] = "1229782938247303441.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok152) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};
    char check[1024] = "-1229782938247303441.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok153) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    char check[1024] = "122978293.82473034410";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok154) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    char check[1024] = "-122978293.82473034410";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok155) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    char check[1024] = "1.2297829382473034410";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok156) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    char check[1024] = "-1.2297829382473034410";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok157) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};
    char check[1024] = "12297829379609722880";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok158) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};
    char check[1024] = "-12297829379609722880";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok159) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};
    char check[1024] = "1229782937960972288.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok160) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};
    char check[1024] = "-1229782937960972288.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok161) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    char check[1024] = "122978293.79609722880";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok162) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    char check[1024] = "-122978293.79609722880";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok163) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    char check[1024] = "1.2297829379609722880";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok164) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    char check[1024] = "-1.2297829379609722880";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok165) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};
    char check[1024] = "2863311530";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok166) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-2863311530";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok167) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    char check[1024] = "286331153.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok168) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-286331153.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok169) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    char check[1024] = "286331.1530";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok170) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    char check[1024] = "-286331.1530";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok171) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    char check[1024] = "2.863311530";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok172) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-2.863311530";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok173) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
    char check[1024] = "26409387504754779197847983445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok174) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
    char check[1024] = "-26409387504754779197847983445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok175) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
    char check[1024] = "2640938750475477919784798344.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok176) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};
    char check[1024] = "-2640938750475477919784798344.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok177) {
    // 264093875.04754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x140000}};
    char check[1024] = "264093875.04754779197847983445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok178) {
    // -264093875.04754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80140000}};
    char check[1024] = "-264093875.04754779197847983445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok179) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    char check[1024] = "2.6409387504754779197847983445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok180) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    char check[1024] = "-2.6409387504754779197847983445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok181) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};
    char check[1024] = "26409387504754779196416327680";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok182) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};
    char check[1024] = "-26409387504754779196416327680";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok183) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};
    char check[1024] = "2640938750475477919641632768.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok184) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};
    char check[1024] = "-2640938750475477919641632768.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok185) {
    // 264093875.04754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x140000}};
    char check[1024] = "264093875.04754779196416327680";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok186) {
    // -264093875.04754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80140000}};
    char check[1024] = "-264093875.04754779196416327680";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok187) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    char check[1024] = "2.6409387504754779196416327680";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok188) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    char check[1024] = "-2.6409387504754779196416327680";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok189) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};
    char check[1024] = "26409387498605864508043122005";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok190) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
    char check[1024] = "-26409387498605864508043122005";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok191) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};
    char check[1024] = "2640938749860586450804312200.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok192) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};
    char check[1024] = "-2640938749860586450804312200.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok193) {
    // 264093874.98605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x140000}};
    char check[1024] = "264093874.98605864508043122005";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok194) {
    // -264093874.98605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80140000}};
    char check[1024] = "-264093874.98605864508043122005";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok195) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    char check[1024] = "2.6409387498605864508043122005";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok196) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    char check[1024] = "-2.6409387498605864508043122005";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok197) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};
    char check[1024] = "26409387498605864506611466240";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok198) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};
    char check[1024] = "-26409387498605864506611466240";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok199) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};
    char check[1024] = "2640938749860586450661146624.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok200) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};
    char check[1024] = "-2640938749860586450661146624.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok201) {
    // 264093874.98605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x140000}};
    char check[1024] = "264093874.98605864506611466240";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok202) {
    // -264093874.98605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80140000}};
    char check[1024] = "-264093874.98605864506611466240";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok203) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    char check[1024] = "2.6409387498605864506611466240";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok204) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    char check[1024] = "-2.6409387498605864506611466240";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok205) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
    char check[1024] = "6148914691236517205";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok206) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
    char check[1024] = "-6148914691236517205";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok207) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};
    char check[1024] = "614891469123651720.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok208) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};
    char check[1024] = "-614891469123651720.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok209) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    char check[1024] = "6148914.691236517205";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok210) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    char check[1024] = "-6148914.691236517205";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok211) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    char check[1024] = "6.148914691236517205";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok212) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    char check[1024] = "-6.148914691236517205";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok213) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
    char check[1024] = "6148914689804861440";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok214) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
    char check[1024] = "-6148914689804861440";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok215) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};
    char check[1024] = "614891468980486144.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok216) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};
    char check[1024] = "-614891468980486144.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok217) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    char check[1024] = "6148914.689804861440";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok218) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    char check[1024] = "-6148914.689804861440";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok219) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    char check[1024] = "6.148914689804861440";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok220) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    char check[1024] = "-6.148914689804861440";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok221) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    char check[1024] = "1431655765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok222) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-1431655765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok223) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    char check[1024] = "143165576.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok224) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-143165576.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok225) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    char check[1024] = "143165.5765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok226) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    char check[1024] = "-143165.5765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok227) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    char check[1024] = "1.431655765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok228) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-1.431655765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok229) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
    char check[1024] = "18446744078004518913";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok230) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
    char check[1024] = "-18446744078004518913";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok231) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};
    char check[1024] = "1844674407800451891.3";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok232) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};
    char check[1024] = "-1844674407800451891.3";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok233) {
    // 184467440.78004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0xB0000}};
    char check[1024] = "184467440.78004518913";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok234) {
    // -184467440.78004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x800B0000}};
    char check[1024] = "-184467440.78004518913";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok235) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    char check[1024] = "1.8446744078004518913";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok236) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    char check[1024] = "-1.8446744078004518913";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok237) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};
    char check[1024] = "18446744078004518912";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok238) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};
    char check[1024] = "-18446744078004518912";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok239) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};
    char check[1024] = "1844674407800451891.2";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok240) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};
    char check[1024] = "-1844674407800451891.2";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok241) {
    // 18446744.078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0xC0000}};
    char check[1024] = "18446744.078004518912";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok242) {
    // -18446744.078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x800C0000}};
    char check[1024] = "-18446744.078004518912";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok243) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    char check[1024] = "1.8446744078004518912";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok244) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    char check[1024] = "-1.8446744078004518912";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok245) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};
    char check[1024] = "18446744073709551617";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok246) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};
    char check[1024] = "-18446744073709551617";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok247) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};
    char check[1024] = "1844674407370955161.7";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok248) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};
    char check[1024] = "-1844674407370955161.7";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok249) {
    // 1844674.4073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xD0000}};
    char check[1024] = "1844674.4073709551617";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok250) {
    // -1844674.4073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800D0000}};
    char check[1024] = "-1844674.4073709551617";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok251) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    char check[1024] = "1.8446744073709551617";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok252) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    char check[1024] = "-1.8446744073709551617";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok253) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};
    char check[1024] = "18446744073709551616";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok254) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};
    char check[1024] = "-18446744073709551616";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok255) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};
    char check[1024] = "1844674407370955161.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok256) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};
    char check[1024] = "-1844674407370955161.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok257) {
    // 184467.44073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xE0000}};
    char check[1024] = "184467.44073709551616";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok258) {
    // -184467.44073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800E0000}};
    char check[1024] = "-184467.44073709551616";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok259) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    char check[1024] = "1.8446744073709551616";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok260) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    char check[1024] = "-1.8446744073709551616";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok261) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};
    char check[1024] = "4294967297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok262) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};
    char check[1024] = "-4294967297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok263) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    char check[1024] = "429496729.7";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok264) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    char check[1024] = "-429496729.7";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok265) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    char check[1024] = "42949672.97";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok266) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    char check[1024] = "-42949672.97";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok267) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    char check[1024] = "429496.7297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok268) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    char check[1024] = "-429496.7297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok269) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    char check[1024] = "4.294967297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok270) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    char check[1024] = "-4.294967297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok271) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    char check[1024] = "42.94967297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok272) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    char check[1024] = "-42.94967297";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok273) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
    char check[1024] = "4294967296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok274) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
    char check[1024] = "-4294967296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok275) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    char check[1024] = "429496729.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok276) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    char check[1024] = "-429496729.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok277) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    char check[1024] = "42949672.96";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok278) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    char check[1024] = "-42949672.96";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok279) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    char check[1024] = "4294967.296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok280) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    char check[1024] = "-4294967.296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok281) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    char check[1024] = "4.294967296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok282) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    char check[1024] = "-4.294967296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok283) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    char check[1024] = "42.94967296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok284) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    char check[1024] = "-42.94967296";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok285) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    char check[1024] = "0.1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok286) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-0.1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok287) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    char check[1024] = "0.0000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok288) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    char check[1024] = "-0.0000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok289) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    char check[1024] = "0.00000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok290) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    char check[1024] = "-0.00000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok291) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    char check[1024] = "0.000000000000000000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok292) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    char check[1024] = "-0.000000000000000000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok293) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok294) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    char check[1024] = "-0.0000000000000000000000000001";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok295) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
    char check[1024] = "39614081266355540835774234624";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok296) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
    char check[1024] = "-39614081266355540835774234624";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok297) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};
    char check[1024] = "3961408126635554083577423462.4";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok298) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};
    char check[1024] = "-3961408126635554083577423462.4";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok299) {
    // 396140812.66355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x140000}};
    char check[1024] = "396140812.66355540835774234624";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok300) {
    // -396140812.66355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80140000}};
    char check[1024] = "-396140812.66355540835774234624";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok301) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    char check[1024] = "3.9614081266355540835774234624";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok302) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    char check[1024] = "-3.9614081266355540835774234624";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok303) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};
    char check[1024] = "39614081266355540833626750976";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok304) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};
    char check[1024] = "-39614081266355540833626750976";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok305) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};
    char check[1024] = "3961408126635554083362675097.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok306) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};
    char check[1024] = "-3961408126635554083362675097.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok307) {
    // 39614081.266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x150000}};
    char check[1024] = "39614081.266355540833626750976";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok308) {
    // -39614081.266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80150000}};
    char check[1024] = "-39614081.266355540833626750976";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok309) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    char check[1024] = "3.9614081266355540833626750976";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok310) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    char check[1024] = "-3.9614081266355540833626750976";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok311) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};
    char check[1024] = "39614081257132168798919458816";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok312) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
    char check[1024] = "-39614081257132168798919458816";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok313) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};
    char check[1024] = "3961408125713216879891945881.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok314) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};
    char check[1024] = "-3961408125713216879891945881.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok315) {
    // 3961408.1257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x160000}};
    char check[1024] = "3961408.1257132168798919458816";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok316) {
    // -3961408.1257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80160000}};
    char check[1024] = "-3961408.1257132168798919458816";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok317) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    char check[1024] = "3.9614081257132168798919458816";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok318) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    char check[1024] = "-3.9614081257132168798919458816";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok319) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};
    char check[1024] = "39614081257132168796771975168";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok320) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};
    char check[1024] = "-39614081257132168796771975168";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok321) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};
    char check[1024] = "3961408125713216879677197516.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok322) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};
    char check[1024] = "-3961408125713216879677197516.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok323) {
    // 396140.81257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x170000}};
    char check[1024] = "396140.81257132168796771975168";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok324) {
    // -396140.81257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80170000}};
    char check[1024] = "-396140.81257132168796771975168";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok325) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    char check[1024] = "3.9614081257132168796771975168";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok326) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    char check[1024] = "-3.9614081257132168796771975168";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok327) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};
    char check[1024] = "9223372039002259456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok328) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};
    char check[1024] = "-9223372039002259456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok329) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};
    char check[1024] = "922337203900225945.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok330) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};
    char check[1024] = "-922337203900225945.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok331) {
    // 922337203.9002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0xA0000}};
    char check[1024] = "922337203.9002259456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok332) {
    // -922337203.9002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x800A0000}};
    char check[1024] = "-922337203.9002259456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok333) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    char check[1024] = "9.223372039002259456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok334) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    char check[1024] = "-9.223372039002259456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok335) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};
    char check[1024] = "9223372036854775808";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok336) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};
    char check[1024] = "-9223372036854775808";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok337) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};
    char check[1024] = "922337203685477580.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok338) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};
    char check[1024] = "-922337203685477580.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok339) {
    // 92233720.36854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0xB0000}};
    char check[1024] = "92233720.36854775808";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok340) {
    // -92233720.36854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x800B0000}};
    char check[1024] = "-92233720.36854775808";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok341) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    char check[1024] = "9.223372036854775808";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok342) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    char check[1024] = "-9.223372036854775808";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok343) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    char check[1024] = "2147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok344) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-2147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok345) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    char check[1024] = "214748364.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok346) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-214748364.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok347) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    char check[1024] = "21474836.48";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok348) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-21474836.48";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok349) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    char check[1024] = "214748.3648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok350) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    char check[1024] = "-214748.3648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok351) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    char check[1024] = "21.47483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok352) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    char check[1024] = "-21.47483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok353) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    char check[1024] = "2.147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok354) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-2.147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok355) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};
    char check[1024] = "156064767562212695305426944";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok356) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};
    char check[1024] = "-156064767562212695305426944";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok357) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};
    char check[1024] = "15606476756221269530542694.4";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok358) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};
    char check[1024] = "-15606476756221269530542694.4";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok359) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    char check[1024] = "1560647.67562212695305426944";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok360) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    char check[1024] = "-1560647.67562212695305426944";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok361) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    char check[1024] = "1.56064767562212695305426944";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok362) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    char check[1024] = "-1.56064767562212695305426944";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok363) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};
    char check[1024] = "156064767562212695296966656";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok364) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};
    char check[1024] = "-156064767562212695296966656";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok365) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};
    char check[1024] = "15606476756221269529696665.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok366) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};
    char check[1024] = "-15606476756221269529696665.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok367) {
    // 15606476.7562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x130000}};
    char check[1024] = "15606476.7562212695296966656";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok368) {
    // -15606476.7562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80130000}};
    char check[1024] = "-15606476.7562212695296966656";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok369) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    char check[1024] = "1.56064767562212695296966656";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok370) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    char check[1024] = "-1.56064767562212695296966656";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok371) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};
    char check[1024] = "156064767525876035030685696";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok372) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};
    char check[1024] = "-156064767525876035030685696";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok373) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};
    char check[1024] = "15606476752587603503068569.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok374) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};
    char check[1024] = "-15606476752587603503068569.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok375) {
    // 156064.767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x150000}};
    char check[1024] = "156064.767525876035030685696";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok376) {
    // -156064.767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80150000}};
    char check[1024] = "-156064.767525876035030685696";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok377) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    char check[1024] = "1.56064767525876035030685696";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok378) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    char check[1024] = "-1.56064767525876035030685696";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok379) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};
    char check[1024] = "156064767525876035022225408";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok380) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};
    char check[1024] = "-156064767525876035022225408";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok381) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};
    char check[1024] = "15606476752587603502222540.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok382) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};
    char check[1024] = "-15606476752587603502222540.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok383) {
    // 15606.4767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x160000}};
    char check[1024] = "15606.4767525876035022225408";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok384) {
    // -15606.4767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80160000}};
    char check[1024] = "-15606.4767525876035022225408";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok385) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    char check[1024] = "1.56064767525876035022225408";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok386) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    char check[1024] = "-1.56064767525876035022225408";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok387) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};
    char check[1024] = "36336660283201536";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok388) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};
    char check[1024] = "-36336660283201536";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok389) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};
    char check[1024] = "3633666028320153.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok390) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};
    char check[1024] = "-3633666028320153.6";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok391) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    char check[1024] = "363366602.83201536";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok392) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    char check[1024] = "-363366602.83201536";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok393) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    char check[1024] = "3.6336660283201536";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok394) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    char check[1024] = "-3.6336660283201536";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok395) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};
    char check[1024] = "36336660274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok396) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};
    char check[1024] = "-36336660274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok397) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};
    char check[1024] = "3633666027474124.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok398) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};
    char check[1024] = "-3633666027474124.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok399) {
    // 3633666.0274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xA0000}};
    char check[1024] = "3633666.0274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok400) {
    // -3633666.0274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800A0000}};
    char check[1024] = "-3633666.0274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok401) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    char check[1024] = "363366602.74741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok402) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    char check[1024] = "-363366602.74741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok403) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    char check[1024] = "36.336660274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok404) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    char check[1024] = "-36.336660274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok405) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    char check[1024] = "3.6336660274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok406) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    char check[1024] = "-3.6336660274741248";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok407) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    char check[1024] = "8460288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok408) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-8460288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok409) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    char check[1024] = "846028.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok410) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-846028.8";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok411) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    char check[1024] = "84602.88";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok412) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-84602.88";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok413) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    char check[1024] = "8460.288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok414) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    char check[1024] = "-8460.288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok415) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    char check[1024] = "84.60288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok416) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    char check[1024] = "-84.60288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok417) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    char check[1024] = "8.460288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok418) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    char check[1024] = "-8.460288";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok419) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok420) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok421) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    char check[1024] = "7922816251426433759354395033.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok422) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    char check[1024] = "-7922816251426433759354395033.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok423) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    char check[1024] = "792281625.14264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok424) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    char check[1024] = "-792281625.14264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok425) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok426) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    char check[1024] = "-7.9228162514264337593543950335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok427) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162514264337589248983040";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok428) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162514264337589248983040";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok429) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
    char check[1024] = "7922816251426433758924898304.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok430) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
    char check[1024] = "-7922816251426433758924898304.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok431) {
    // 79228162.514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    char check[1024] = "79228162.514264337589248983040";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok432) {
    // -79228162.514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    char check[1024] = "-79228162.514264337589248983040";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok433) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162514264337589248983040";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok434) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    char check[1024] = "-7.9228162514264337589248983040";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok435) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162495817593524129366015";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok436) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162495817593524129366015";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok437) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};
    char check[1024] = "7922816249581759352412936601.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok438) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};
    char check[1024] = "-7922816249581759352412936601.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok439) {
    // 7922816.2495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x160000}};
    char check[1024] = "7922816.2495817593524129366015";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok440) {
    // -7922816.2495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80160000}};
    char check[1024] = "-7922816.2495817593524129366015";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok441) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162495817593524129366015";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok442) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    char check[1024] = "-7.9228162495817593524129366015";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok443) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};
    char check[1024] = "79228162495817593519834398720";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok444) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};
    char check[1024] = "-79228162495817593519834398720";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok445) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};
    char check[1024] = "7922816249581759351983439872.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok446) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};
    char check[1024] = "-7922816249581759351983439872.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok447) {
    // 792281.62495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x170000}};
    char check[1024] = "792281.62495817593519834398720";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok448) {
    // -792281.62495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80170000}};
    char check[1024] = "-792281.62495817593519834398720";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok449) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    char check[1024] = "7.9228162495817593519834398720";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok450) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    char check[1024] = "-7.9228162495817593519834398720";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok451) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};
    char check[1024] = "18446744073709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok452) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};
    char check[1024] = "-18446744073709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok453) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};
    char check[1024] = "1844674407370955161.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok454) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};
    char check[1024] = "-1844674407370955161.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok455) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};
    char check[1024] = "18446744073709551.615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok456) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};
    char check[1024] = "-18446744073709551.615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok457) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    char check[1024] = "184467440.73709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok458) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    char check[1024] = "-184467440.73709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok459) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    char check[1024] = "184.46744073709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok460) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    char check[1024] = "-184.46744073709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok461) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    char check[1024] = "1.8446744073709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok462) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    char check[1024] = "-1.8446744073709551615";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok463) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};
    char check[1024] = "18446744069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok464) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};
    char check[1024] = "-18446744069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok465) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};
    char check[1024] = "1844674406941458432.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok466) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};
    char check[1024] = "-1844674406941458432.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok467) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};
    char check[1024] = "18446744069414584.320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok468) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};
    char check[1024] = "-18446744069414584.320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok469) {
    // 18446744.069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0xC0000}};
    char check[1024] = "18446744.069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok470) {
    // -18446744.069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x800C0000}};
    char check[1024] = "-18446744.069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok471) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    char check[1024] = "184.46744069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok472) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    char check[1024] = "-184.46744069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok473) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    char check[1024] = "1.8446744069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok474) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    char check[1024] = "-1.8446744069414584320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok475) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
    char check[1024] = "4294967295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok476) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-4294967295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok477) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    char check[1024] = "429496729.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok478) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-429496729.5";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok479) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    char check[1024] = "42949672.95";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok480) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-42949672.95";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok481) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    char check[1024] = "42949.67295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok482) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    char check[1024] = "-42949.67295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok483) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    char check[1024] = "42.94967295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok484) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    char check[1024] = "-42.94967295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok485) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    char check[1024] = "4.294967295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok486) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-4.294967295";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok487) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    char check[1024] = "1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok488) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok489) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    char check[1024] = "1.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok490) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-1.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok491) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    char check[1024] = "1.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok492) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-1.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok493) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    char check[1024] = "1.000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok494) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    char check[1024] = "-1.000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok495) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    char check[1024] = "1.0000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok496) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    char check[1024] = "-1.0000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok497) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    char check[1024] = "1.0000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok498) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    char check[1024] = "-1.0000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok499) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    char check[1024] = "1.00000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok500) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    char check[1024] = "-1.00000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok501) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    char check[1024] = "1.000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok502) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    char check[1024] = "-1.000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok503) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    char check[1024] = "1.0000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok504) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    char check[1024] = "-1.0000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok505) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    char check[1024] = "1.1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok506) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-1.1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok507) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    char check[1024] = "12.12";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok508) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-12.12";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok509) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    char check[1024] = "123.123";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok510) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    char check[1024] = "-123.123";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok511) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    char check[1024] = "1234.1234";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok512) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    char check[1024] = "-1234.1234";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok513) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    char check[1024] = "12345.12345";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok514) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    char check[1024] = "-12345.12345";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok515) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    char check[1024] = "123456.123456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok516) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    char check[1024] = "-123456.123456";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok517) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    char check[1024] = "1234567.1234567";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok518) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    char check[1024] = "-1234567.1234567";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok519) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    char check[1024] = "1234567890.1234567890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok520) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    char check[1024] = "-1234567890.1234567890";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok521) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
    char check[1024] = "12345678901234.12345678901234";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok522) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
    char check[1024] = "-12345678901234.12345678901234";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok523) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    char check[1024] = "99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok524) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok525) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    char check[1024] = "9.9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok526) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-9.9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok527) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    char check[1024] = "99.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok528) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-99.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok529) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    char check[1024] = "999.999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok530) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    char check[1024] = "-999.999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok531) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    char check[1024] = "9999.9999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok532) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    char check[1024] = "-9999.9999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok533) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    char check[1024] = "99999.99999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok534) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    char check[1024] = "-99999.99999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok535) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    char check[1024] = "999999.999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok536) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    char check[1024] = "-999999.999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok537) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    char check[1024] = "9999999.9999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok538) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    char check[1024] = "-9999999.9999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok539) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    char check[1024] = "99999999.99999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok540) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    char check[1024] = "-99999999.99999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok541) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    char check[1024] = "999999999.999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok542) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    char check[1024] = "-999999999.999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok543) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
    char check[1024] = "9999999999.9999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok544) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
    char check[1024] = "-9999999999.9999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok545) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    char check[1024] = "9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok546) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok547) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    char check[1024] = "0.9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok548) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    char check[1024] = "-0.9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok549) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    char check[1024] = "0.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok550) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-0.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok551) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    char check[1024] = "0.999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok552) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    char check[1024] = "-0.999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok553) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    char check[1024] = "0.9999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok554) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    char check[1024] = "-0.9999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok555) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    char check[1024] = "0.99999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok556) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    char check[1024] = "-0.99999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok557) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    char check[1024] = "0.999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok558) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    char check[1024] = "-0.999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok559) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    char check[1024] = "0.9999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok560) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    char check[1024] = "-0.9999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok561) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    char check[1024] = "0.99999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok562) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    char check[1024] = "-0.99999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok563) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    char check[1024] = "0.999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok564) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-0.999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok565) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    char check[1024] = "0.9999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok566) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    char check[1024] = "-0.9999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok567) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    char check[1024] = "0.99999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok568) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    char check[1024] = "-0.99999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok569) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    char check[1024] = "0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok570) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    char check[1024] = "0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok571) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    char check[1024] = "0.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok572) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    char check[1024] = "0.0";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok573) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    char check[1024] = "0.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok574) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    char check[1024] = "0.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok575) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    char check[1024] = "0.00000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok576) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    char check[1024] = "0.00000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok577) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    char check[1024] = "0.000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok578) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    char check[1024] = "0.000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok579) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    char check[1024] = "0.0000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok580) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000000000000000";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok581) {
    // 2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x0}};
    char check[1024] = "2147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok582) {
    // -2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-2147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok583) {
    // 2147483646.00
    s21_decimal decimal = {{0xFFFFFF38, 0x31, 0x0, 0x20000}};
    char check[1024] = "2147483646.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok584) {
    // -2147483646.00
    s21_decimal decimal = {{0xFFFFFF38, 0x31, 0x0, 0x80020000}};
    char check[1024] = "-2147483646.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok585) {
    // 2147483646.99
    s21_decimal decimal = {{0xFFFFFF9B, 0x31, 0x0, 0x20000}};
    char check[1024] = "2147483646.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok586) {
    // -2147483646.99
    s21_decimal decimal = {{0xFFFFFF9B, 0x31, 0x0, 0x80020000}};
    char check[1024] = "-2147483646.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok587) {
    // 2147483646.999999999999999999
    s21_decimal decimal = {{0x589BFFFF, 0xC5D1494C, 0x6F05B59, 0x120000}};
    char check[1024] = "2147483646.999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok588) {
    // -2147483646.999999999999999999
    s21_decimal decimal = {{0x589BFFFF, 0xC5D1494C, 0x6F05B59, 0x80120000}};
    char check[1024] = "-2147483646.999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok589) {
    // 21474836.46
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x20000}};
    char check[1024] = "21474836.46";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok590) {
    // -21474836.46
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-21474836.46";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok591) {
    // 214.7483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x70000}};
    char check[1024] = "214.7483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok592) {
    // -214.7483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80070000}};
    char check[1024] = "-214.7483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok593) {
    // 2.147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x90000}};
    char check[1024] = "2.147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok594) {
    // -2.147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-2.147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok595) {
    // 0.2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0xA0000}};
    char check[1024] = "0.2147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok596) {
    // -0.2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x800A0000}};
    char check[1024] = "-0.2147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok597) {
    // 0.0000000000000000002147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000002147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok598) {
    // -0.0000000000000000002147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x801C0000}};
    char check[1024] = "-0.0000000000000000002147483646";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok599) {
    // 2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
    char check[1024] = "2147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok600) {
    // -2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-2147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok601) {
    // 2147483647.00
    s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x20000}};
    char check[1024] = "2147483647.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok602) {
    // -2147483647.00
    s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x80020000}};
    char check[1024] = "-2147483647.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok603) {
    // 2147483647.99
    s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x20000}};
    char check[1024] = "2147483647.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok604) {
    // -2147483647.99
    s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x80020000}};
    char check[1024] = "-2147483647.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok605) {
    // 2147483647.999999999999999999
    s21_decimal decimal = {{0xFFFFFFFF, 0xD3B1FFFF, 0x6F05B59, 0x120000}};
    char check[1024] = "2147483647.999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok606) {
    // -2147483647.999999999999999999
    s21_decimal decimal = {{0xFFFFFFFF, 0xD3B1FFFF, 0x6F05B59, 0x80120000}};
    char check[1024] = "-2147483647.999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok607) {
    // 21474836.47
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x20000}};
    char check[1024] = "21474836.47";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok608) {
    // -21474836.47
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-21474836.47";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok609) {
    // 214.7483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x70000}};
    char check[1024] = "214.7483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok610) {
    // -214.7483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80070000}};
    char check[1024] = "-214.7483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok611) {
    // 2.147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x90000}};
    char check[1024] = "2.147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok612) {
    // -2.147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-2.147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok613) {
    // 0.2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0xA0000}};
    char check[1024] = "0.2147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok614) {
    // -0.2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x800A0000}};
    char check[1024] = "-0.2147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok615) {
    // 0.0000000000000000002147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000002147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok616) {
    // -0.0000000000000000002147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x801C0000}};
    char check[1024] = "-0.0000000000000000002147483647";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok617) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};
    char check[1024] = "2147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok618) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    char check[1024] = "-2147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok619) {
    // 2147483648.00
    s21_decimal decimal = {{0x0, 0x32, 0x0, 0x20000}};
    char check[1024] = "2147483648.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok620) {
    // -2147483648.00
    s21_decimal decimal = {{0x0, 0x32, 0x0, 0x80020000}};
    char check[1024] = "-2147483648.00";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok621) {
    // 2147483648.99
    s21_decimal decimal = {{0x63, 0x32, 0x0, 0x20000}};
    char check[1024] = "2147483648.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok622) {
    // -2147483648.99
    s21_decimal decimal = {{0x63, 0x32, 0x0, 0x80020000}};
    char check[1024] = "-2147483648.99";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok623) {
    // 2147483648.999999999999999999
    s21_decimal decimal = {{0xA763FFFF, 0xE192B6B3, 0x6F05B59, 0x120000}};
    char check[1024] = "2147483648.999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok624) {
    // -2147483648.999999999999999999
    s21_decimal decimal = {{0xA763FFFF, 0xE192B6B3, 0x6F05B59, 0x80120000}};
    char check[1024] = "-2147483648.999999999999999999";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok625) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    char check[1024] = "21474836.48";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok626) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    char check[1024] = "-21474836.48";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok627) {
    // 214.7483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x70000}};
    char check[1024] = "214.7483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok628) {
    // -214.7483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80070000}};
    char check[1024] = "-214.7483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok629) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    char check[1024] = "2.147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok630) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    char check[1024] = "-2.147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok631) {
    // 0.2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0xA0000}};
    char check[1024] = "0.2147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok632) {
    // -0.2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x800A0000}};
    char check[1024] = "-0.2147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok633) {
    // 0.0000000000000000002147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x1C0000}};
    char check[1024] = "0.0000000000000000002147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok634) {
    // -0.0000000000000000002147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x801C0000}};
    char check[1024] = "-0.0000000000000000002147483648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok635) {
    // -84966884.15613141837474582841
    s21_decimal decimal = {{0x84B65139, 0xF4FE9092, 0x1B744BC1, 0x80140000}};
    char check[1024] = "-84966884.15613141837474582841";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok636) {
    // 84966884.15613141837474582841
    s21_decimal decimal = {{0x84B65139, 0xF4FE9092, 0x1B744BC1, 0x140000}};
    char check[1024] = "84966884.15613141837474582841";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok637) {
    // 430785.36689610368553590669637
    s21_decimal decimal = {{0xDBFB4145, 0x51900168, 0x8B31BAF9, 0x170000}};
    char check[1024] = "430785.36689610368553590669637";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok638) {
    // -430785.36689610368553590669637
    s21_decimal decimal = {{0xDBFB4145, 0x51900168, 0x8B31BAF9, 0x80170000}};
    char check[1024] = "-430785.36689610368553590669637";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok639) {
    // -44389006201633590448504510019
    s21_decimal decimal = {{0x1A751643, 0xEA07EC67, 0x8F6DB9AF, 0x80000000}};
    char check[1024] = "-44389006201633590448504510019";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok640) {
    // 44389006201633590448504510019
    s21_decimal decimal = {{0x1A751643, 0xEA07EC67, 0x8F6DB9AF, 0x0}};
    char check[1024] = "44389006201633590448504510019";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok641) {
    // -501391838188057782340.7888082
    s21_decimal decimal = {{0x8FE456D2, 0x1D70670B, 0x10336A84, 0x80070000}};
    char check[1024] = "-501391838188057782340.7888082";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok642) {
    // 501391838188057782340.7888082
    s21_decimal decimal = {{0x8FE456D2, 0x1D70670B, 0x10336A84, 0x70000}};
    char check[1024] = "501391838188057782340.7888082";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok643) {
    // 352100282.96513092625475156003
    s21_decimal decimal = {{0xED71B823, 0x9E26C3A5, 0x71C50D82, 0x140000}};
    char check[1024] = "352100282.96513092625475156003";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok644) {
    // -352100282.96513092625475156003
    s21_decimal decimal = {{0xED71B823, 0x9E26C3A5, 0x71C50D82, 0x80140000}};
    char check[1024] = "-352100282.96513092625475156003";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok645) {
    // 15834841991830798713483220.203
    s21_decimal decimal = {{0xA6C0D4EB, 0x6CE5D93C, 0x332A4638, 0x30000}};
    char check[1024] = "15834841991830798713483220.203";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok646) {
    // -15834841991830798713483220.203
    s21_decimal decimal = {{0xA6C0D4EB, 0x6CE5D93C, 0x332A4638, 0x80030000}};
    char check[1024] = "-15834841991830798713483220.203";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok647) {
    // 27109765607807321971.795351143
    s21_decimal decimal = {{0x8376D667, 0x60BC72EC, 0x5798AC2A, 0x90000}};
    char check[1024] = "27109765607807321971.795351143";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok648) {
    // -27109765607807321971.795351143
    s21_decimal decimal = {{0x8376D667, 0x60BC72EC, 0x5798AC2A, 0x80090000}};
    char check[1024] = "-27109765607807321971.795351143";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok649) {
    // -22.608144517601435513819058494
    s21_decimal decimal = {{0x6371513E, 0x17AD2C22, 0x490D04D2, 0x801B0000}};
    char check[1024] = "-22.608144517601435513819058494";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok650) {
    // 22.608144517601435513819058494
    s21_decimal decimal = {{0x6371513E, 0x17AD2C22, 0x490D04D2, 0x1B0000}};
    char check[1024] = "22.608144517601435513819058494";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok651) {
    // 47463239705.949939042819348711
    s21_decimal decimal = {{0x5E4998E7, 0x1E9B69F6, 0x995CABF4, 0x120000}};
    char check[1024] = "47463239705.949939042819348711";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok652) {
    // -47463239705.949939042819348711
    s21_decimal decimal = {{0x5E4998E7, 0x1E9B69F6, 0x995CABF4, 0x80120000}};
    char check[1024] = "-47463239705.949939042819348711";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok653) {
    // 38644898511940650527384.093243
    s21_decimal decimal = {{0x405F423B, 0x1B3CAC31, 0x7CDE4F92, 0x60000}};
    char check[1024] = "38644898511940650527384.093243";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok654) {
    // -38644898511940650527384.093243
    s21_decimal decimal = {{0x405F423B, 0x1B3CAC31, 0x7CDE4F92, 0x80060000}};
    char check[1024] = "-38644898511940650527384.093243";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok655) {
    // -53416522595.903440935527647266
    s21_decimal decimal = {{0x2D580822, 0x41463286, 0xAC991CA4, 0x80120000}};
    char check[1024] = "-53416522595.903440935527647266";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok656) {
    // 53416522595.903440935527647266
    s21_decimal decimal = {{0x2D580822, 0x41463286, 0xAC991CA4, 0x120000}};
    char check[1024] = "53416522595.903440935527647266";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok657) {
    // -3499005386397700568539876.4837
    s21_decimal decimal = {{0x64F6FD25, 0xBC456E22, 0x710F181C, 0x80040000}};
    char check[1024] = "-3499005386397700568539876.4837";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok658) {
    // 3499005386397700568539876.4837
    s21_decimal decimal = {{0x64F6FD25, 0xBC456E22, 0x710F181C, 0x40000}};
    char check[1024] = "3499005386397700568539876.4837";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok659) {
    // 5804313867127868784366285.0766
    s21_decimal decimal = {{0x611A6ACE, 0x438E2062, 0xBB8C28B4, 0x40000}};
    char check[1024] = "5804313867127868784366285.0766";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok660) {
    // -5804313867127868784366285.0766
    s21_decimal decimal = {{0x611A6ACE, 0x438E2062, 0xBB8C28B4, 0x80040000}};
    char check[1024] = "-5804313867127868784366285.0766";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok661) {
    // -527979783783034971.457603690
    s21_decimal decimal = {{0x302C486A, 0x6E281E86, 0x1B4BC11, 0x80090000}};
    char check[1024] = "-527979783783034971.457603690";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok662) {
    // 527979783783034971.457603690
    s21_decimal decimal = {{0x302C486A, 0x6E281E86, 0x1B4BC11, 0x90000}};
    char check[1024] = "527979783783034971.457603690";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok663) {
    // -366666303726510783781.37849371
    s21_decimal decimal = {{0x6EE80E1B, 0x6337651C, 0x7679ECFF, 0x80080000}};
    char check[1024] = "-366666303726510783781.37849371";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok664) {
    // 366666303726510783781.37849371
    s21_decimal decimal = {{0x6EE80E1B, 0x6337651C, 0x7679ECFF, 0x80000}};
    char check[1024] = "366666303726510783781.37849371";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok665) {
    // 77368958798214.660500952389886
    s21_decimal decimal = {{0xB70B18FE, 0x992996FA, 0xF9FE1A4C, 0xF0000}};
    char check[1024] = "77368958798214.660500952389886";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok666) {
    // -77368958798214.660500952389886
    s21_decimal decimal = {{0xB70B18FE, 0x992996FA, 0xF9FE1A4C, 0x800F0000}};
    char check[1024] = "-77368958798214.660500952389886";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok667) {
    // -7.0256503638787659340968799062
    s21_decimal decimal = {{0x5E0EAB56, 0xD20A15CB, 0xE302D155, 0x801C0000}};
    char check[1024] = "-7.0256503638787659340968799062";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok668) {
    // 7.0256503638787659340968799062
    s21_decimal decimal = {{0x5E0EAB56, 0xD20A15CB, 0xE302D155, 0x1C0000}};
    char check[1024] = "7.0256503638787659340968799062";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok669) {
    // 470.75167041950795779797384920
    s21_decimal decimal = {{0x31277ED8, 0xD99D1B60, 0x981BAA5E, 0x1A0000}};
    char check[1024] = "470.75167041950795779797384920";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok670) {
    // -470.75167041950795779797384920
    s21_decimal decimal = {{0x31277ED8, 0xD99D1B60, 0x981BAA5E, 0x801A0000}};
    char check[1024] = "-470.75167041950795779797384920";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok671) {
    // -0.476181089374254692357126100
    s21_decimal decimal = {{0xDE5C37D4, 0x946E09DB, 0x189E344, 0x801B0000}};
    char check[1024] = "-0.476181089374254692357126100";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok672) {
    // 0.476181089374254692357126100
    s21_decimal decimal = {{0xDE5C37D4, 0x946E09DB, 0x189E344, 0x1B0000}};
    char check[1024] = "0.476181089374254692357126100";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok673) {
    // 6357673359991586094808514.5689
    s21_decimal decimal = {{0x7D608059, 0x6D947E40, 0xCD6D7102, 0x40000}};
    char check[1024] = "6357673359991586094808514.5689";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok674) {
    // -6357673359991586094808514.5689
    s21_decimal decimal = {{0x7D608059, 0x6D947E40, 0xCD6D7102, 0x80040000}};
    char check[1024] = "-6357673359991586094808514.5689";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok675) {
    // -7770643047668729493331.3330834
    s21_decimal decimal = {{0xACC11E92, 0xF2271528, 0xFB1540B4, 0x80070000}};
    char check[1024] = "-7770643047668729493331.3330834";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok676) {
    // 7770643047668729493331.3330834
    s21_decimal decimal = {{0xACC11E92, 0xF2271528, 0xFB1540B4, 0x70000}};
    char check[1024] = "7770643047668729493331.3330834";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok677) {
    // -716057.48207294469325083428655
    s21_decimal decimal = {{0x2934C72F, 0x709F822F, 0xE75EE2FC, 0x80170000}};
    char check[1024] = "-716057.48207294469325083428655";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok678) {
    // 716057.48207294469325083428655
    s21_decimal decimal = {{0x2934C72F, 0x709F822F, 0xE75EE2FC, 0x170000}};
    char check[1024] = "716057.48207294469325083428655";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok679) {
    // -253267.34041835760026855829926
    s21_decimal decimal = {{0xC9FA71A6, 0x818C33F8, 0x51D5C88B, 0x80170000}};
    char check[1024] = "-253267.34041835760026855829926";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok680) {
    // 253267.34041835760026855829926
    s21_decimal decimal = {{0xC9FA71A6, 0x818C33F8, 0x51D5C88B, 0x170000}};
    char check[1024] = "253267.34041835760026855829926";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok681) {
    // -44705407026.635368759314252532
    s21_decimal decimal = {{0x61D682F4, 0x19F8139, 0x9073722B, 0x80120000}};
    char check[1024] = "-44705407026.635368759314252532";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok682) {
    // 44705407026.635368759314252532
    s21_decimal decimal = {{0x61D682F4, 0x19F8139, 0x9073722B, 0x120000}};
    char check[1024] = "44705407026.635368759314252532";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok683) {
    // 747970156051326230239009740.76
    s21_decimal decimal = {{0xF45BDBFC, 0xB9D13283, 0xF1AEA424, 0x20000}};
    char check[1024] = "747970156051326230239009740.76";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok684) {
    // -747970156051326230239009740.76
    s21_decimal decimal = {{0xF45BDBFC, 0xB9D13283, 0xF1AEA424, 0x80020000}};
    char check[1024] = "-747970156051326230239009740.76";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok685) {
    // 53987754357930817018618339470
    s21_decimal decimal = {{0x7656608E, 0x1FC62B3F, 0xAE719FAC, 0x0}};
    char check[1024] = "53987754357930817018618339470";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok686) {
    // -53987754357930817018618339470
    s21_decimal decimal = {{0x7656608E, 0x1FC62B3F, 0xAE719FAC, 0x80000000}};
    char check[1024] = "-53987754357930817018618339470";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok687) {
    // 310171940359945380570.75669445
    s21_decimal decimal = {{0x588639C5, 0xE9571CC2, 0x6438D251, 0x80000}};
    char check[1024] = "310171940359945380570.75669445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok688) {
    // -310171940359945380570.75669445
    s21_decimal decimal = {{0x588639C5, 0xE9571CC2, 0x6438D251, 0x80080000}};
    char check[1024] = "-310171940359945380570.75669445";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok689) {
    // 1421088291977.048476313845507
    s21_decimal decimal = {{0x19B1FF03, 0xAC3A19AC, 0x4977F26, 0xF0000}};
    char check[1024] = "1421088291977.048476313845507";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok690) {
    // -1421088291977.048476313845507
    s21_decimal decimal = {{0x19B1FF03, 0xAC3A19AC, 0x4977F26, 0x800F0000}};
    char check[1024] = "-1421088291977.048476313845507";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok691) {
    // -175.30894418077848033862465498
    s21_decimal decimal = {{0x52DDB7DA, 0xAF4884B9, 0x38A5374A, 0x801A0000}};
    char check[1024] = "-175.30894418077848033862465498";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok692) {
    // 175.30894418077848033862465498
    s21_decimal decimal = {{0x52DDB7DA, 0xAF4884B9, 0x38A5374A, 0x1A0000}};
    char check[1024] = "175.30894418077848033862465498";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok693) {
    // 20961160837918637117804124.679
    s21_decimal decimal = {{0x5B281A07, 0xEA1AE970, 0x43BAAA75, 0x30000}};
    char check[1024] = "20961160837918637117804124.679";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok694) {
    // -20961160837918637117804124.679
    s21_decimal decimal = {{0x5B281A07, 0xEA1AE970, 0x43BAAA75, 0x80030000}};
    char check[1024] = "-20961160837918637117804124.679";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok695) {
    // -540391125.2818810379406603919
    s21_decimal decimal = {{0xA7BEF68F, 0x2E156F4, 0x117602B8, 0x80130000}};
    char check[1024] = "-540391125.2818810379406603919";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok696) {
    // 540391125.2818810379406603919
    s21_decimal decimal = {{0xA7BEF68F, 0x2E156F4, 0x117602B8, 0x130000}};
    char check[1024] = "540391125.2818810379406603919";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok697) {
    // 6762980.6133399889226602583702
    s21_decimal decimal = {{0x34DB1696, 0xBAF3CD40, 0xDA861080, 0x160000}};
    char check[1024] = "6762980.6133399889226602583702";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok698) {
    // -6762980.6133399889226602583702
    s21_decimal decimal = {{0x34DB1696, 0xBAF3CD40, 0xDA861080, 0x80160000}};
    char check[1024] = "-6762980.6133399889226602583702";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok699) {
    // -678622099244.84571317995985778
    s21_decimal decimal = {{0xA10E5B72, 0x7D5B721B, 0xDB464DEB, 0x80110000}};
    char check[1024] = "-678622099244.84571317995985778";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok700) {
    // 678622099244.84571317995985778
    s21_decimal decimal = {{0xA10E5B72, 0x7D5B721B, 0xDB464DEB, 0x110000}};
    char check[1024] = "678622099244.84571317995985778";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok701) {
    // -6282855121790600545045326178.9
    s21_decimal decimal = {{0x28F99DDD, 0x3A8089A8, 0xCB028F3A, 0x80010000}};
    char check[1024] = "-6282855121790600545045326178.9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok702) {
    // 6282855121790600545045326178.9
    s21_decimal decimal = {{0x28F99DDD, 0x3A8089A8, 0xCB028F3A, 0x10000}};
    char check[1024] = "6282855121790600545045326178.9";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok703) {
    // 15324941537.140194085635176765
    s21_decimal decimal = {{0xC9393D, 0x6397F146, 0x31847E99, 0x120000}};
    char check[1024] = "15324941537.140194085635176765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok704) {
    // -15324941537.140194085635176765
    s21_decimal decimal = {{0xC9393D, 0x6397F146, 0x31847E99, 0x80120000}};
    char check[1024] = "-15324941537.140194085635176765";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok705) {
    // -199896.02009581067994553545631
    s21_decimal decimal = {{0xC97A739F, 0x4BA0A46D, 0x409702E0, 0x80170000}};
    char check[1024] = "-199896.02009581067994553545631";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok706) {
    // 199896.02009581067994553545631
    s21_decimal decimal = {{0xC97A739F, 0x4BA0A46D, 0x409702E0, 0x170000}};
    char check[1024] = "199896.02009581067994553545631";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok707) {
    // -137536457.9487297713757255827
    s21_decimal decimal = {{0x3A087893, 0x408238B0, 0x471ACC7, 0x80130000}};
    char check[1024] = "-137536457.9487297713757255827";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok708) {
    // 137536457.9487297713757255827
    s21_decimal decimal = {{0x3A087893, 0x408238B0, 0x471ACC7, 0x130000}};
    char check[1024] = "137536457.9487297713757255827";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok709) {
    // 5.0501509669208114994181180848
    s21_decimal decimal = {{0x860E0DB0, 0xDB8F6E55, 0xA32DDEA4, 0x1C0000}};
    char check[1024] = "5.0501509669208114994181180848";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok710) {
    // -5.0501509669208114994181180848
    s21_decimal decimal = {{0x860E0DB0, 0xDB8F6E55, 0xA32DDEA4, 0x801C0000}};
    char check[1024] = "-5.0501509669208114994181180848";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok711) {
    // -2640955263416491.0881837304784
    s21_decimal decimal = {{0x232A4BD0, 0x43F7AFD, 0x5555784D, 0x800D0000}};
    char check[1024] = "-2640955263416491.0881837304784";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok712) {
    // 2640955263416491.0881837304784
    s21_decimal decimal = {{0x232A4BD0, 0x43F7AFD, 0x5555784D, 0xD0000}};
    char check[1024] = "2640955263416491.0881837304784";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok713) {
    // 63378844447784825784946125896
    s21_decimal decimal = {{0xBB63EC48, 0xFED654CC, 0xCCC9C059, 0x0}};
    char check[1024] = "63378844447784825784946125896";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok714) {
    // -63378844447784825784946125896
    s21_decimal decimal = {{0xBB63EC48, 0xFED654CC, 0xCCC9C059, 0x80000000}};
    char check[1024] = "-63378844447784825784946125896";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok715) {
    // 3120892356.5440596689406971907
    s21_decimal decimal = {{0xCBE4D003, 0x877C1BB7, 0x64D76AA0, 0x130000}};
    char check[1024] = "3120892356.5440596689406971907";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok716) {
    // -3120892356.5440596689406971907
    s21_decimal decimal = {{0xCBE4D003, 0x877C1BB7, 0x64D76AA0, 0x80130000}};
    char check[1024] = "-3120892356.5440596689406971907";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok717) {
    // 255342960082.94301095191613314
    s21_decimal decimal = {{0x8E078F82, 0x41083150, 0x52817980, 0x110000}};
    char check[1024] = "255342960082.94301095191613314";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok718) {
    // -255342960082.94301095191613314
    s21_decimal decimal = {{0x8E078F82, 0x41083150, 0x52817980, 0x80110000}};
    char check[1024] = "-255342960082.94301095191613314";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok719) {
    // -14316487300359898045.037001025
    s21_decimal decimal = {{0x9159B941, 0xABAA43F7, 0x2E42521B, 0x80090000}};
    char check[1024] = "-14316487300359898045.037001025";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok720) {
    // 14316487300359898045.037001025
    s21_decimal decimal = {{0x9159B941, 0xABAA43F7, 0x2E42521B, 0x90000}};
    char check[1024] = "14316487300359898045.037001025";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok721) {
    // -439810095666814839492.96463512
    s21_decimal decimal = {{0x65AA2E98, 0x3DD0008, 0x8E1C3D0A, 0x80080000}};
    char check[1024] = "-439810095666814839492.96463512";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok722) {
    // 439810095666814839492.96463512
    s21_decimal decimal = {{0x65AA2E98, 0x3DD0008, 0x8E1C3D0A, 0x80000}};
    char check[1024] = "439810095666814839492.96463512";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok723) {
    // 7419220167640.3921165177722837
    s21_decimal decimal = {{0x7F5E17D5, 0xF3B5AABE, 0xEFBA59CF, 0x100000}};
    char check[1024] = "7419220167640.3921165177722837";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok724) {
    // -7419220167640.3921165177722837
    s21_decimal decimal = {{0x7F5E17D5, 0xF3B5AABE, 0xEFBA59CF, 0x80100000}};
    char check[1024] = "-7419220167640.3921165177722837";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok725) {
    // -596800606971092161664808315.46
    s21_decimal decimal = {{0x6395E43A, 0x17F81246, 0xC0D6306D, 0x80020000}};
    char check[1024] = "-596800606971092161664808315.46";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok726) {
    // 596800606971092161664808315.46
    s21_decimal decimal = {{0x6395E43A, 0x17F81246, 0xC0D6306D, 0x20000}};
    char check[1024] = "596800606971092161664808315.46";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok727) {
    // -821650937542173460525385.9128
    s21_decimal decimal = {{0x87415738, 0xC1055B60, 0x1A8C8989, 0x80040000}};
    char check[1024] = "-821650937542173460525385.9128";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok728) {
    // 821650937542173460525385.9128
    s21_decimal decimal = {{0x87415738, 0xC1055B60, 0x1A8C8989, 0x40000}};
    char check[1024] = "821650937542173460525385.9128";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok729) {
    // -28393504963209842679210759.452
    s21_decimal decimal = {{0x923ED51C, 0x478D85A0, 0x5BBE8E8C, 0x80030000}};
    char check[1024] = "-28393504963209842679210759.452";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok730) {
    // 28393504963209842679210759.452
    s21_decimal decimal = {{0x923ED51C, 0x478D85A0, 0x5BBE8E8C, 0x30000}};
    char check[1024] = "28393504963209842679210759.452";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok731) {
    // -73.696580396195915882976900270
    s21_decimal decimal = {{0x53E1F4AE, 0x83F21214, 0xEE2061EC, 0x801B0000}};
    char check[1024] = "-73.696580396195915882976900270";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok732) {
    // 73.696580396195915882976900270
    s21_decimal decimal = {{0x53E1F4AE, 0x83F21214, 0xEE2061EC, 0x1B0000}};
    char check[1024] = "73.696580396195915882976900270";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok733) {
    // -3.056542161306615709632888207
    s21_decimal decimal = {{0x93DCFD8F, 0x944075F8, 0x9E04FFA, 0x801B0000}};
    char check[1024] = "-3.056542161306615709632888207";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok734) {
    // 3.056542161306615709632888207
    s21_decimal decimal = {{0x93DCFD8F, 0x944075F8, 0x9E04FFA, 0x1B0000}};
    char check[1024] = "3.056542161306615709632888207";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok735) {
    // -480811544379106268.24011154160
    s21_decimal decimal = {{0xAB1482F0, 0xDC147E95, 0x9B5BCC7C, 0x800B0000}};
    char check[1024] = "-480811544379106268.24011154160";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok736) {
    // 480811544379106268.24011154160
    s21_decimal decimal = {{0xAB1482F0, 0xDC147E95, 0x9B5BCC7C, 0xB0000}};
    char check[1024] = "480811544379106268.24011154160";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok737) {
    // -1446636272407690.8765828407290
    s21_decimal decimal = {{0x6A60DFFA, 0xAB9DB5E3, 0x2EBE4B76, 0x800D0000}};
    char check[1024] = "-1446636272407690.8765828407290";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok738) {
    // 1446636272407690.8765828407290
    s21_decimal decimal = {{0x6A60DFFA, 0xAB9DB5E3, 0x2EBE4B76, 0xD0000}};
    char check[1024] = "1446636272407690.8765828407290";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok739) {
    // -3907063.7355032883565648347572
    s21_decimal decimal = {{0x333701B4, 0x937262B, 0x7E3E7947, 0x80160000}};
    char check[1024] = "-3907063.7355032883565648347572";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok740) {
    // 3907063.7355032883565648347572
    s21_decimal decimal = {{0x333701B4, 0x937262B, 0x7E3E7947, 0x160000}};
    char check[1024] = "3907063.7355032883565648347572";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok741) {
    // 557508977484709757421.28144062
    s21_decimal decimal = {{0xDC2FBEBE, 0xD870E272, 0xB4240FCE, 0x80000}};
    char check[1024] = "557508977484709757421.28144062";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok742) {
    // -557508977484709757421.28144062
    s21_decimal decimal = {{0xDC2FBEBE, 0xD870E272, 0xB4240FCE, 0x80080000}};
    char check[1024] = "-557508977484709757421.28144062";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok743) {
    // 4432978541471375388033428250.7
    s21_decimal decimal = {{0x83B9AF0B, 0x9F587D83, 0x8F3CBD32, 0x10000}};
    char check[1024] = "4432978541471375388033428250.7";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok744) {
    // -4432978541471375388033428250.7
    s21_decimal decimal = {{0x83B9AF0B, 0x9F587D83, 0x8F3CBD32, 0x80010000}};
    char check[1024] = "-4432978541471375388033428250.7";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok745) {
    // 84476498.849371918519200648
    s21_decimal decimal = {{0xE38F6B88, 0x2DC756A0, 0x45E098, 0x120000}};
    char check[1024] = "84476498.849371918519200648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok746) {
    // -84476498.849371918519200648
    s21_decimal decimal = {{0xE38F6B88, 0x2DC756A0, 0x45E098, 0x80120000}};
    char check[1024] = "-84476498.849371918519200648";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok747) {
    // 9233452317534056.351524682028
    s21_decimal decimal = {{0x1CFF792C, 0x1C4F6DAB, 0x1DD5BB95, 0xC0000}};
    char check[1024] = "9233452317534056.351524682028";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok748) {
    // -9233452317534056.351524682028
    s21_decimal decimal = {{0x1CFF792C, 0x1C4F6DAB, 0x1DD5BB95, 0x800C0000}};
    char check[1024] = "-9233452317534056.351524682028";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok749) {
    // -156.01018090952745103798591965
    s21_decimal decimal = {{0xD2D061DD, 0x5C1DE522, 0x3268DC15, 0x801A0000}};
    char check[1024] = "-156.01018090952745103798591965";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok750) {
    // 156.01018090952745103798591965
    s21_decimal decimal = {{0xD2D061DD, 0x5C1DE522, 0x3268DC15, 0x1A0000}};
    char check[1024] = "156.01018090952745103798591965";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok751) {
    // -555282413253792.36951843479173
    s21_decimal decimal = {{0x96E91E85, 0xF6BA128B, 0xB36BE279, 0x800E0000}};
    char check[1024] = "-555282413253792.36951843479173";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok752) {
    // 555282413253792.36951843479173
    s21_decimal decimal = {{0x96E91E85, 0xF6BA128B, 0xB36BE279, 0xE0000}};
    char check[1024] = "555282413253792.36951843479173";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok753) {
    // 660044249440575936213.17159308
    s21_decimal decimal = {{0x39B0098C, 0xE67266B4, 0xD54594A5, 0x80000}};
    char check[1024] = "660044249440575936213.17159308";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok754) {
    // -660044249440575936213.17159308
    s21_decimal decimal = {{0x39B0098C, 0xE67266B4, 0xD54594A5, 0x80080000}};
    char check[1024] = "-660044249440575936213.17159308";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok755) {
    // -28369449868483.736067303461803
    s21_decimal decimal = {{0x5F5AD3AB, 0xFB3F3DC1, 0x5BAAA8AE, 0x800F0000}};
    char check[1024] = "-28369449868483.736067303461803";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok756) {
    // 28369449868483.736067303461803
    s21_decimal decimal = {{0x5F5AD3AB, 0xFB3F3DC1, 0x5BAAA8AE, 0xF0000}};
    char check[1024] = "28369449868483.736067303461803";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok757) {
    // 593953434558151503.25001801754
    s21_decimal decimal = {{0x8662D01A, 0x84104D03, 0xBFEAAD34, 0xB0000}};
    char check[1024] = "593953434558151503.25001801754";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok758) {
    // -593953434558151503.25001801754
    s21_decimal decimal = {{0x8662D01A, 0x84104D03, 0xBFEAAD34, 0x800B0000}};
    char check[1024] = "-593953434558151503.25001801754";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok759) {
    // 12510192830044.667721361245703
    s21_decimal decimal = {{0x9CE1C607, 0x3A33A42F, 0x286C3060, 0xF0000}};
    char check[1024] = "12510192830044.667721361245703";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok760) {
    // -12510192830044.667721361245703
    s21_decimal decimal = {{0x9CE1C607, 0x3A33A42F, 0x286C3060, 0x800F0000}};
    char check[1024] = "-12510192830044.667721361245703";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok761) {
    // -394888216354110792369663827.27
    s21_decimal decimal = {{0xC2177C87, 0x4CDE1BD8, 0x7F98633E, 0x80020000}};
    char check[1024] = "-394888216354110792369663827.27";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok762) {
    // 394888216354110792369663827.27
    s21_decimal decimal = {{0xC2177C87, 0x4CDE1BD8, 0x7F98633E, 0x20000}};
    char check[1024] = "394888216354110792369663827.27";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok763) {
    // 22142496698.827556886549782974
    s21_decimal decimal = {{0x88E261BE, 0x418F98DB, 0x478BD80F, 0x120000}};
    char check[1024] = "22142496698.827556886549782974";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok764) {
    // -22142496698.827556886549782974
    s21_decimal decimal = {{0x88E261BE, 0x418F98DB, 0x478BD80F, 0x80120000}};
    char check[1024] = "-22142496698.827556886549782974";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok765) {
    // 565250712.65559445201470864911
    s21_decimal decimal = {{0x4ADBBE0F, 0x4D062EF1, 0xB6A4716D, 0x140000}};
    char check[1024] = "565250712.65559445201470864911";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok766) {
    // -565250712.65559445201470864911
    s21_decimal decimal = {{0x4ADBBE0F, 0x4D062EF1, 0xB6A4716D, 0x80140000}};
    char check[1024] = "-565250712.65559445201470864911";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok767) {
    // -4794680329068369715662.7500503
    s21_decimal decimal = {{0x83E20DD7, 0x9320D769, 0x9AECAA86, 0x80070000}};
    char check[1024] = "-4794680329068369715662.7500503";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok768) {
    // 4794680329068369715662.7500503
    s21_decimal decimal = {{0x83E20DD7, 0x9320D769, 0x9AECAA86, 0x70000}};
    char check[1024] = "4794680329068369715662.7500503";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok769) {
    // -7068375674488121576568237.3563
    s21_decimal decimal = {{0xD218C3BB, 0x1CA2AA29, 0xE4643BB3, 0x80040000}};
    char check[1024] = "-7068375674488121576568237.3563";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok770) {
    // 7068375674488121576568237.3563
    s21_decimal decimal = {{0xD218C3BB, 0x1CA2AA29, 0xE4643BB3, 0x40000}};
    char check[1024] = "7068375674488121576568237.3563";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok771) {
    // 71741171459.256625864756341919
    s21_decimal decimal = {{0x7726AC9F, 0xA3991BDD, 0xE7CEE7F9, 0x120000}};
    char check[1024] = "71741171459.256625864756341919";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok772) {
    // -71741171459.256625864756341919
    s21_decimal decimal = {{0x7726AC9F, 0xA3991BDD, 0xE7CEE7F9, 0x80120000}};
    char check[1024] = "-71741171459.256625864756341919";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok773) {
    // -19053780829416342484.472066484
    s21_decimal decimal = {{0x8F3071B4, 0x773E31A7, 0x3D90EB08, 0x80090000}};
    char check[1024] = "-19053780829416342484.472066484";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok774) {
    // 19053780829416342484.472066484
    s21_decimal decimal = {{0x8F3071B4, 0x773E31A7, 0x3D90EB08, 0x90000}};
    char check[1024] = "19053780829416342484.472066484";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok775) {
    // 6406081863262044633.1971339320
    s21_decimal decimal = {{0x29788438, 0xA264A959, 0xCEFDDE00, 0xA0000}};
    char check[1024] = "6406081863262044633.1971339320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok776) {
    // -6406081863262044633.1971339320
    s21_decimal decimal = {{0x29788438, 0xA264A959, 0xCEFDDE00, 0x800A0000}};
    char check[1024] = "-6406081863262044633.1971339320";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok777) {
    // 4059775420291717061.7988249731
    s21_decimal decimal = {{0xD0C57883, 0x3DE45C09, 0x832DACD9, 0xA0000}};
    char check[1024] = "4059775420291717061.7988249731";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok778) {
    // -4059775420291717061.7988249731
    s21_decimal decimal = {{0xD0C57883, 0x3DE45C09, 0x832DACD9, 0x800A0000}};
    char check[1024] = "-4059775420291717061.7988249731";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok779) {
    // 42329986997735627.158516495118
    s21_decimal decimal = {{0x2435730E, 0x361EB629, 0x88C68B69, 0xC0000}};
    char check[1024] = "42329986997735627.158516495118";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok780) {
    // -42329986997735627.158516495118
    s21_decimal decimal = {{0x2435730E, 0x361EB629, 0x88C68B69, 0x800C0000}};
    char check[1024] = "-42329986997735627.158516495118";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok781) {
    // -3384287639039795628.493918822
    s21_decimal decimal = {{0x6BFA5266, 0x87342255, 0xAEF6AC8, 0x80090000}};
    char check[1024] = "-3384287639039795628.493918822";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok782) {
    // 3384287639039795628.493918822
    s21_decimal decimal = {{0x6BFA5266, 0x87342255, 0xAEF6AC8, 0x90000}};
    char check[1024] = "3384287639039795628.493918822";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok783) {
    // -39.397875316172189294962577429
    s21_decimal decimal = {{0xF1AE9015, 0x74918C1C, 0x7F4D289C, 0x801B0000}};
    char check[1024] = "-39.397875316172189294962577429";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok784) {
    // 39.397875316172189294962577429
    s21_decimal decimal = {{0xF1AE9015, 0x74918C1C, 0x7F4D289C, 0x1B0000}};
    char check[1024] = "39.397875316172189294962577429";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok785) {
    // -6034759423205669715301590589
    s21_decimal decimal = {{0xA637663D, 0xDA750101, 0x137FD603, 0x80000000}};
    char check[1024] = "-6034759423205669715301590589";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok786) {
    // 6034759423205669715301590589
    s21_decimal decimal = {{0xA637663D, 0xDA750101, 0x137FD603, 0x0}};
    char check[1024] = "6034759423205669715301590589";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok787) {
    // 2327.611635692768350429195325
    s21_decimal decimal = {{0xF2E32C3D, 0x9B24E809, 0x7855AEF, 0x180000}};
    char check[1024] = "2327.611635692768350429195325";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok788) {
    // -2327.611635692768350429195325
    s21_decimal decimal = {{0xF2E32C3D, 0x9B24E809, 0x7855AEF, 0x80180000}};
    char check[1024] = "-2327.611635692768350429195325";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok789) {
    // -322689602.16491973718361438112
    s21_decimal decimal = {{0x2222F7A0, 0x87483577, 0x6844421E, 0x80140000}};
    char check[1024] = "-322689602.16491973718361438112";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok790) {
    // 322689602.16491973718361438112
    s21_decimal decimal = {{0x2222F7A0, 0x87483577, 0x6844421E, 0x140000}};
    char check[1024] = "322689602.16491973718361438112";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok791) {
    // -491.31300680550654731231588756
    s21_decimal decimal = {{0xD1127194, 0xBE9CABE6, 0x9EC0759A, 0x801A0000}};
    char check[1024] = "-491.31300680550654731231588756";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok792) {
    // 491.31300680550654731231588756
    s21_decimal decimal = {{0xD1127194, 0xBE9CABE6, 0x9EC0759A, 0x1A0000}};
    char check[1024] = "491.31300680550654731231588756";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok793) {
    // 3481122473295054102.2158132402
    s21_decimal decimal = {{0x4B1C14B2, 0x1E07B3BF, 0x707B2B92, 0xA0000}};
    char check[1024] = "3481122473295054102.2158132402";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok794) {
    // -3481122473295054102.2158132402
    s21_decimal decimal = {{0x4B1C14B2, 0x1E07B3BF, 0x707B2B92, 0x800A0000}};
    char check[1024] = "-3481122473295054102.2158132402";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok795) {
    // 134332845798310625573228.33489
    s21_decimal decimal = {{0xCD06EE51, 0x40E1A7D9, 0x2B67C0A8, 0x50000}};
    char check[1024] = "134332845798310625573228.33489";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok796) {
    // -134332845798310625573228.33489
    s21_decimal decimal = {{0xCD06EE51, 0x40E1A7D9, 0x2B67C0A8, 0x80050000}};
    char check[1024] = "-134332845798310625573228.33489";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok797) {
    // 5306276449259.5004085451612801
    s21_decimal decimal = {{0x50EFE281, 0xC43CB03, 0xAB747D73, 0x100000}};
    char check[1024] = "5306276449259.5004085451612801";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok798) {
    // -5306276449259.5004085451612801
    s21_decimal decimal = {{0x50EFE281, 0xC43CB03, 0xAB747D73, 0x80100000}};
    char check[1024] = "-5306276449259.5004085451612801";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok799) {
    // -349054.90891906427587598841046
    s21_decimal decimal = {{0x55BD74D6, 0xD57A433F, 0x70C92534, 0x80170000}};
    char check[1024] = "-349054.90891906427587598841046";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok800) {
    // 349054.90891906427587598841046
    s21_decimal decimal = {{0x55BD74D6, 0xD57A433F, 0x70C92534, 0x170000}};
    char check[1024] = "349054.90891906427587598841046";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok801) {
    // -2379081685975887.8560671288523
    s21_decimal decimal = {{0xB504CCCB, 0x3A4EF257, 0x4CDF4D6E, 0x800D0000}};
    char check[1024] = "-2379081685975887.8560671288523";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok802) {
    // 2379081685975887.8560671288523
    s21_decimal decimal = {{0xB504CCCB, 0x3A4EF257, 0x4CDF4D6E, 0xD0000}};
    char check[1024] = "2379081685975887.8560671288523";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok803) {
    // 9866161.438903573510507501335
    s21_decimal decimal = {{0x3BF89717, 0x4EBEC222, 0x1FE118F3, 0x150000}};
    char check[1024] = "9866161.438903573510507501335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok804) {
    // -9866161.438903573510507501335
    s21_decimal decimal = {{0x3BF89717, 0x4EBEC222, 0x1FE118F3, 0x80150000}};
    char check[1024] = "-9866161.438903573510507501335";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok805) {
    // -4520363744915042484248869.3979
    s21_decimal decimal = {{0xE372C4DB, 0x54AF4C2F, 0x920F9290, 0x80040000}};
    char check[1024] = "-4520363744915042484248869.3979";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok806) {
    // 4520363744915042484248869.3979
    s21_decimal decimal = {{0xE372C4DB, 0x54AF4C2F, 0x920F9290, 0x40000}};
    char check[1024] = "4520363744915042484248869.3979";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok807) {
    // 39988275074.118625709536458699
    s21_decimal decimal = {{0x8AEE37CB, 0x77225B51, 0x8135869F, 0x120000}};
    char check[1024] = "39988275074.118625709536458699";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok808) {
    // -39988275074.118625709536458699
    s21_decimal decimal = {{0x8AEE37CB, 0x77225B51, 0x8135869F, 0x80120000}};
    char check[1024] = "-39988275074.118625709536458699";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok809) {
    // 15280933527.104216793052835964
    s21_decimal decimal = {{0xA587707C, 0x62785612, 0x3160178A, 0x120000}};
    char check[1024] = "15280933527.104216793052835964";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok810) {
    // -15280933527.104216793052835964
    s21_decimal decimal = {{0xA587707C, 0x62785612, 0x3160178A, 0x80120000}};
    char check[1024] = "-15280933527.104216793052835964";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok811) {
    // -4468500505852390731662033825.1
    s21_decimal decimal = {{0xB12A244B, 0x194F76CE, 0x906291E2, 0x80010000}};
    char check[1024] = "-4468500505852390731662033825.1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok812) {
    // 4468500505852390731662033825.1
    s21_decimal decimal = {{0xB12A244B, 0x194F76CE, 0x906291E2, 0x10000}};
    char check[1024] = "4468500505852390731662033825.1";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok813) {
    // 4749477058558113699682117.3274
    s21_decimal decimal = {{0x6C21041A, 0x8785C871, 0x9976C0E0, 0x40000}};
    char check[1024] = "4749477058558113699682117.3274";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok814) {
    // -4749477058558113699682117.3274
    s21_decimal decimal = {{0x6C21041A, 0x8785C871, 0x9976C0E0, 0x80040000}};
    char check[1024] = "-4749477058558113699682117.3274";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok815) {
    // -20707026098623538272047.214167
    s21_decimal decimal = {{0xACC42E57, 0x1792D0A5, 0x42E87356, 0x80060000}};
    char check[1024] = "-20707026098623538272047.214167";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok816) {
    // 20707026098623538272047.214167
    s21_decimal decimal = {{0xACC42E57, 0x1792D0A5, 0x42E87356, 0x60000}};
    char check[1024] = "20707026098623538272047.214167";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok817) {
    // 615185080974.44192215807218692
    s21_decimal decimal = {{0xC392D404, 0x5DA55C86, 0xC6C6EACE, 0x110000}};
    char check[1024] = "615185080974.44192215807218692";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok818) {
    // -615185080974.44192215807218692
    s21_decimal decimal = {{0xC392D404, 0x5DA55C86, 0xC6C6EACE, 0x80110000}};
    char check[1024] = "-615185080974.44192215807218692";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok819) {
    // 66430498014144575663164.695097
    s21_decimal decimal = {{0x2ED12239, 0x4FBCF263, 0xD6A60521, 0x60000}};
    char check[1024] = "66430498014144575663164.695097";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok820) {
    // -66430498014144575663164.695097
    s21_decimal decimal = {{0x2ED12239, 0x4FBCF263, 0xD6A60521, 0x80060000}};
    char check[1024] = "-66430498014144575663164.695097";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok821) {
    // -732542010707.50782240090381965
    s21_decimal decimal = {{0xAB3A5E8D, 0x3ADA9B17, 0xECB27475, 0x80110000}};
    char check[1024] = "-732542010707.50782240090381965";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok822) {
    // 732542010707.50782240090381965
    s21_decimal decimal = {{0xAB3A5E8D, 0x3ADA9B17, 0xECB27475, 0x110000}};
    char check[1024] = "732542010707.50782240090381965";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok823) {
    // 38128751960634754705.645754634
    s21_decimal decimal = {{0x6BE5D90A, 0x7E7A8311, 0x7B335D49, 0x90000}};
    char check[1024] = "38128751960634754705.645754634";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok824) {
    // -38128751960634754705.645754634
    s21_decimal decimal = {{0x6BE5D90A, 0x7E7A8311, 0x7B335D49, 0x80090000}};
    char check[1024] = "-38128751960634754705.645754634";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok825) {
    // -50932806558122830.146140506149
    s21_decimal decimal = {{0x38220825, 0xE16D6F3, 0xA492A150, 0x800C0000}};
    char check[1024] = "-50932806558122830.146140506149";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok826) {
    // 50932806558122830.146140506149
    s21_decimal decimal = {{0x38220825, 0xE16D6F3, 0xA492A150, 0xC0000}};
    char check[1024] = "50932806558122830.146140506149";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok827) {
    // -60538513183207652957763792758
    s21_decimal decimal = {{0x512DEF76, 0x9D2248DE, 0xC39C48CF, 0x80000000}};
    char check[1024] = "-60538513183207652957763792758";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok828) {
    // 60538513183207652957763792758
    s21_decimal decimal = {{0x512DEF76, 0x9D2248DE, 0xC39C48CF, 0x0}};
    char check[1024] = "60538513183207652957763792758";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok829) {
    // 28794226455496.466189984474166
    s21_decimal decimal = {{0x57002436, 0xE7898F0A, 0x5D0A069F, 0xF0000}};
    char check[1024] = "28794226455496.466189984474166";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok830) {
    // -28794226455496.466189984474166
    s21_decimal decimal = {{0x57002436, 0xE7898F0A, 0x5D0A069F, 0x800F0000}};
    char check[1024] = "-28794226455496.466189984474166";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok831) {
    // 9331851834457631884121059.87
    s21_decimal decimal = {{0x625BC503, 0x2941B7B8, 0x303E9A6, 0x20000}};
    char check[1024] = "9331851834457631884121059.87";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok832) {
    // -9331851834457631884121059.87
    s21_decimal decimal = {{0x625BC503, 0x2941B7B8, 0x303E9A6, 0x80020000}};
    char check[1024] = "-9331851834457631884121059.87";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok833) {
    // -2089258557261.8254138526571674
    s21_decimal decimal = {{0xDEDA9C9A, 0x5566DE2F, 0x4381F115, 0x80100000}};
    char check[1024] = "-2089258557261.8254138526571674";

    test_debug(decimal, check);
}

START_TEST(test_debug_ok834) {
    // 2089258557261.8254138526571674
    s21_decimal decimal = {{0xDEDA9C9A, 0x5566DE2F, 0x4381F115, 0x100000}};
    char check[1024] = "2089258557261.8254138526571674";

    test_debug(decimal, check);
}


Suite * debug1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_debug_ok1);
    tcase_add_test(tc_core, test_debug_ok2);
    tcase_add_test(tc_core, test_debug_ok3);
    tcase_add_test(tc_core, test_debug_ok4);
    tcase_add_test(tc_core, test_debug_ok5);
    tcase_add_test(tc_core, test_debug_ok6);
    tcase_add_test(tc_core, test_debug_ok7);
    tcase_add_test(tc_core, test_debug_ok8);
    tcase_add_test(tc_core, test_debug_ok9);
    tcase_add_test(tc_core, test_debug_ok10);
    tcase_add_test(tc_core, test_debug_ok11);
    tcase_add_test(tc_core, test_debug_ok12);
    tcase_add_test(tc_core, test_debug_ok13);
    tcase_add_test(tc_core, test_debug_ok14);
    tcase_add_test(tc_core, test_debug_ok15);
    tcase_add_test(tc_core, test_debug_ok16);
    tcase_add_test(tc_core, test_debug_ok17);
    tcase_add_test(tc_core, test_debug_ok18);
    tcase_add_test(tc_core, test_debug_ok19);
    tcase_add_test(tc_core, test_debug_ok20);
    tcase_add_test(tc_core, test_debug_ok21);
    tcase_add_test(tc_core, test_debug_ok22);
    tcase_add_test(tc_core, test_debug_ok23);
    tcase_add_test(tc_core, test_debug_ok24);
    tcase_add_test(tc_core, test_debug_ok25);
    tcase_add_test(tc_core, test_debug_ok26);
    tcase_add_test(tc_core, test_debug_ok27);
    tcase_add_test(tc_core, test_debug_ok28);
    tcase_add_test(tc_core, test_debug_ok29);
    tcase_add_test(tc_core, test_debug_ok30);
    tcase_add_test(tc_core, test_debug_ok31);
    tcase_add_test(tc_core, test_debug_ok32);
    tcase_add_test(tc_core, test_debug_ok33);
    tcase_add_test(tc_core, test_debug_ok34);
    tcase_add_test(tc_core, test_debug_ok35);
    tcase_add_test(tc_core, test_debug_ok36);
    tcase_add_test(tc_core, test_debug_ok37);
    tcase_add_test(tc_core, test_debug_ok38);
    tcase_add_test(tc_core, test_debug_ok39);
    tcase_add_test(tc_core, test_debug_ok40);
    tcase_add_test(tc_core, test_debug_ok41);
    tcase_add_test(tc_core, test_debug_ok42);
    tcase_add_test(tc_core, test_debug_ok43);
    tcase_add_test(tc_core, test_debug_ok44);
    tcase_add_test(tc_core, test_debug_ok45);
    tcase_add_test(tc_core, test_debug_ok46);
    tcase_add_test(tc_core, test_debug_ok47);
    tcase_add_test(tc_core, test_debug_ok48);
    tcase_add_test(tc_core, test_debug_ok49);
    tcase_add_test(tc_core, test_debug_ok50);
    tcase_add_test(tc_core, test_debug_ok51);
    tcase_add_test(tc_core, test_debug_ok52);
    tcase_add_test(tc_core, test_debug_ok53);
    tcase_add_test(tc_core, test_debug_ok54);
    tcase_add_test(tc_core, test_debug_ok55);
    tcase_add_test(tc_core, test_debug_ok56);
    tcase_add_test(tc_core, test_debug_ok57);
    tcase_add_test(tc_core, test_debug_ok58);
    tcase_add_test(tc_core, test_debug_ok59);
    tcase_add_test(tc_core, test_debug_ok60);
    tcase_add_test(tc_core, test_debug_ok61);
    tcase_add_test(tc_core, test_debug_ok62);
    tcase_add_test(tc_core, test_debug_ok63);
    tcase_add_test(tc_core, test_debug_ok64);
    tcase_add_test(tc_core, test_debug_ok65);
    tcase_add_test(tc_core, test_debug_ok66);
    tcase_add_test(tc_core, test_debug_ok67);
    tcase_add_test(tc_core, test_debug_ok68);
    tcase_add_test(tc_core, test_debug_ok69);
    tcase_add_test(tc_core, test_debug_ok70);
    tcase_add_test(tc_core, test_debug_ok71);
    tcase_add_test(tc_core, test_debug_ok72);
    tcase_add_test(tc_core, test_debug_ok73);
    tcase_add_test(tc_core, test_debug_ok74);
    tcase_add_test(tc_core, test_debug_ok75);
    tcase_add_test(tc_core, test_debug_ok76);
    tcase_add_test(tc_core, test_debug_ok77);
    tcase_add_test(tc_core, test_debug_ok78);
    tcase_add_test(tc_core, test_debug_ok79);
    tcase_add_test(tc_core, test_debug_ok80);
    tcase_add_test(tc_core, test_debug_ok81);
    tcase_add_test(tc_core, test_debug_ok82);
    tcase_add_test(tc_core, test_debug_ok83);
    tcase_add_test(tc_core, test_debug_ok84);
    tcase_add_test(tc_core, test_debug_ok85);
    tcase_add_test(tc_core, test_debug_ok86);
    tcase_add_test(tc_core, test_debug_ok87);
    tcase_add_test(tc_core, test_debug_ok88);
    tcase_add_test(tc_core, test_debug_ok89);
    tcase_add_test(tc_core, test_debug_ok90);
    tcase_add_test(tc_core, test_debug_ok91);
    tcase_add_test(tc_core, test_debug_ok92);
    tcase_add_test(tc_core, test_debug_ok93);
    tcase_add_test(tc_core, test_debug_ok94);
    tcase_add_test(tc_core, test_debug_ok95);
    tcase_add_test(tc_core, test_debug_ok96);
    tcase_add_test(tc_core, test_debug_ok97);
    tcase_add_test(tc_core, test_debug_ok98);
    tcase_add_test(tc_core, test_debug_ok99);
    tcase_add_test(tc_core, test_debug_ok100);
    tcase_add_test(tc_core, test_debug_ok101);
    tcase_add_test(tc_core, test_debug_ok102);
    tcase_add_test(tc_core, test_debug_ok103);
    tcase_add_test(tc_core, test_debug_ok104);
    tcase_add_test(tc_core, test_debug_ok105);
    tcase_add_test(tc_core, test_debug_ok106);
    tcase_add_test(tc_core, test_debug_ok107);
    tcase_add_test(tc_core, test_debug_ok108);
    tcase_add_test(tc_core, test_debug_ok109);
    tcase_add_test(tc_core, test_debug_ok110);
    tcase_add_test(tc_core, test_debug_ok111);
    tcase_add_test(tc_core, test_debug_ok112);
    tcase_add_test(tc_core, test_debug_ok113);
    tcase_add_test(tc_core, test_debug_ok114);
    tcase_add_test(tc_core, test_debug_ok115);
    tcase_add_test(tc_core, test_debug_ok116);
    tcase_add_test(tc_core, test_debug_ok117);
    tcase_add_test(tc_core, test_debug_ok118);
    tcase_add_test(tc_core, test_debug_ok119);
    tcase_add_test(tc_core, test_debug_ok120);
    tcase_add_test(tc_core, test_debug_ok121);
    tcase_add_test(tc_core, test_debug_ok122);
    tcase_add_test(tc_core, test_debug_ok123);
    tcase_add_test(tc_core, test_debug_ok124);
    tcase_add_test(tc_core, test_debug_ok125);
    tcase_add_test(tc_core, test_debug_ok126);
    tcase_add_test(tc_core, test_debug_ok127);
    tcase_add_test(tc_core, test_debug_ok128);
    tcase_add_test(tc_core, test_debug_ok129);
    tcase_add_test(tc_core, test_debug_ok130);
    tcase_add_test(tc_core, test_debug_ok131);
    tcase_add_test(tc_core, test_debug_ok132);
    tcase_add_test(tc_core, test_debug_ok133);
    tcase_add_test(tc_core, test_debug_ok134);
    tcase_add_test(tc_core, test_debug_ok135);
    tcase_add_test(tc_core, test_debug_ok136);
    tcase_add_test(tc_core, test_debug_ok137);
    tcase_add_test(tc_core, test_debug_ok138);
    tcase_add_test(tc_core, test_debug_ok139);
    tcase_add_test(tc_core, test_debug_ok140);
    tcase_add_test(tc_core, test_debug_ok141);
    tcase_add_test(tc_core, test_debug_ok142);
    tcase_add_test(tc_core, test_debug_ok143);
    tcase_add_test(tc_core, test_debug_ok144);
    tcase_add_test(tc_core, test_debug_ok145);
    tcase_add_test(tc_core, test_debug_ok146);
    tcase_add_test(tc_core, test_debug_ok147);
    tcase_add_test(tc_core, test_debug_ok148);
    tcase_add_test(tc_core, test_debug_ok149);
    tcase_add_test(tc_core, test_debug_ok150);
    tcase_add_test(tc_core, test_debug_ok151);
    tcase_add_test(tc_core, test_debug_ok152);
    tcase_add_test(tc_core, test_debug_ok153);
    tcase_add_test(tc_core, test_debug_ok154);
    tcase_add_test(tc_core, test_debug_ok155);
    tcase_add_test(tc_core, test_debug_ok156);
    tcase_add_test(tc_core, test_debug_ok157);
    tcase_add_test(tc_core, test_debug_ok158);
    tcase_add_test(tc_core, test_debug_ok159);
    tcase_add_test(tc_core, test_debug_ok160);
    tcase_add_test(tc_core, test_debug_ok161);
    tcase_add_test(tc_core, test_debug_ok162);
    tcase_add_test(tc_core, test_debug_ok163);
    tcase_add_test(tc_core, test_debug_ok164);
    tcase_add_test(tc_core, test_debug_ok165);
    tcase_add_test(tc_core, test_debug_ok166);
    tcase_add_test(tc_core, test_debug_ok167);
    tcase_add_test(tc_core, test_debug_ok168);
    tcase_add_test(tc_core, test_debug_ok169);
    tcase_add_test(tc_core, test_debug_ok170);
    tcase_add_test(tc_core, test_debug_ok171);
    tcase_add_test(tc_core, test_debug_ok172);
    tcase_add_test(tc_core, test_debug_ok173);
    tcase_add_test(tc_core, test_debug_ok174);
    tcase_add_test(tc_core, test_debug_ok175);
    tcase_add_test(tc_core, test_debug_ok176);
    tcase_add_test(tc_core, test_debug_ok177);
    tcase_add_test(tc_core, test_debug_ok178);
    tcase_add_test(tc_core, test_debug_ok179);
    tcase_add_test(tc_core, test_debug_ok180);
    tcase_add_test(tc_core, test_debug_ok181);
    tcase_add_test(tc_core, test_debug_ok182);
    tcase_add_test(tc_core, test_debug_ok183);
    tcase_add_test(tc_core, test_debug_ok184);
    tcase_add_test(tc_core, test_debug_ok185);
    tcase_add_test(tc_core, test_debug_ok186);
    tcase_add_test(tc_core, test_debug_ok187);
    tcase_add_test(tc_core, test_debug_ok188);
    tcase_add_test(tc_core, test_debug_ok189);
    tcase_add_test(tc_core, test_debug_ok190);
    tcase_add_test(tc_core, test_debug_ok191);
    tcase_add_test(tc_core, test_debug_ok192);
    tcase_add_test(tc_core, test_debug_ok193);
    tcase_add_test(tc_core, test_debug_ok194);
    tcase_add_test(tc_core, test_debug_ok195);
    tcase_add_test(tc_core, test_debug_ok196);
    tcase_add_test(tc_core, test_debug_ok197);
    tcase_add_test(tc_core, test_debug_ok198);
    tcase_add_test(tc_core, test_debug_ok199);
    tcase_add_test(tc_core, test_debug_ok200);
    tcase_add_test(tc_core, test_debug_ok201);
    tcase_add_test(tc_core, test_debug_ok202);
    tcase_add_test(tc_core, test_debug_ok203);
    tcase_add_test(tc_core, test_debug_ok204);
    tcase_add_test(tc_core, test_debug_ok205);
    tcase_add_test(tc_core, test_debug_ok206);
    tcase_add_test(tc_core, test_debug_ok207);
    tcase_add_test(tc_core, test_debug_ok208);
    tcase_add_test(tc_core, test_debug_ok209);
    tcase_add_test(tc_core, test_debug_ok210);
    tcase_add_test(tc_core, test_debug_ok211);
    tcase_add_test(tc_core, test_debug_ok212);
    tcase_add_test(tc_core, test_debug_ok213);
    tcase_add_test(tc_core, test_debug_ok214);
    tcase_add_test(tc_core, test_debug_ok215);
    tcase_add_test(tc_core, test_debug_ok216);
    tcase_add_test(tc_core, test_debug_ok217);
    tcase_add_test(tc_core, test_debug_ok218);
    tcase_add_test(tc_core, test_debug_ok219);
    tcase_add_test(tc_core, test_debug_ok220);
    tcase_add_test(tc_core, test_debug_ok221);
    tcase_add_test(tc_core, test_debug_ok222);
    tcase_add_test(tc_core, test_debug_ok223);
    tcase_add_test(tc_core, test_debug_ok224);
    tcase_add_test(tc_core, test_debug_ok225);
    tcase_add_test(tc_core, test_debug_ok226);
    tcase_add_test(tc_core, test_debug_ok227);
    tcase_add_test(tc_core, test_debug_ok228);
    tcase_add_test(tc_core, test_debug_ok229);
    tcase_add_test(tc_core, test_debug_ok230);
    tcase_add_test(tc_core, test_debug_ok231);
    tcase_add_test(tc_core, test_debug_ok232);
    tcase_add_test(tc_core, test_debug_ok233);
    tcase_add_test(tc_core, test_debug_ok234);
    tcase_add_test(tc_core, test_debug_ok235);
    tcase_add_test(tc_core, test_debug_ok236);
    tcase_add_test(tc_core, test_debug_ok237);
    tcase_add_test(tc_core, test_debug_ok238);
    tcase_add_test(tc_core, test_debug_ok239);
    tcase_add_test(tc_core, test_debug_ok240);
    tcase_add_test(tc_core, test_debug_ok241);
    tcase_add_test(tc_core, test_debug_ok242);
    tcase_add_test(tc_core, test_debug_ok243);
    tcase_add_test(tc_core, test_debug_ok244);
    tcase_add_test(tc_core, test_debug_ok245);
    tcase_add_test(tc_core, test_debug_ok246);
    tcase_add_test(tc_core, test_debug_ok247);
    tcase_add_test(tc_core, test_debug_ok248);
    tcase_add_test(tc_core, test_debug_ok249);
    tcase_add_test(tc_core, test_debug_ok250);
    tcase_add_test(tc_core, test_debug_ok251);
    tcase_add_test(tc_core, test_debug_ok252);
    tcase_add_test(tc_core, test_debug_ok253);
    tcase_add_test(tc_core, test_debug_ok254);
    tcase_add_test(tc_core, test_debug_ok255);
    tcase_add_test(tc_core, test_debug_ok256);
    tcase_add_test(tc_core, test_debug_ok257);
    tcase_add_test(tc_core, test_debug_ok258);
    tcase_add_test(tc_core, test_debug_ok259);
    tcase_add_test(tc_core, test_debug_ok260);
    tcase_add_test(tc_core, test_debug_ok261);
    tcase_add_test(tc_core, test_debug_ok262);
    tcase_add_test(tc_core, test_debug_ok263);
    tcase_add_test(tc_core, test_debug_ok264);
    tcase_add_test(tc_core, test_debug_ok265);
    tcase_add_test(tc_core, test_debug_ok266);
    tcase_add_test(tc_core, test_debug_ok267);
    tcase_add_test(tc_core, test_debug_ok268);
    tcase_add_test(tc_core, test_debug_ok269);
    tcase_add_test(tc_core, test_debug_ok270);
    tcase_add_test(tc_core, test_debug_ok271);
    tcase_add_test(tc_core, test_debug_ok272);
    tcase_add_test(tc_core, test_debug_ok273);
    tcase_add_test(tc_core, test_debug_ok274);
    tcase_add_test(tc_core, test_debug_ok275);
    tcase_add_test(tc_core, test_debug_ok276);
    tcase_add_test(tc_core, test_debug_ok277);
    tcase_add_test(tc_core, test_debug_ok278);
    tcase_add_test(tc_core, test_debug_ok279);
    tcase_add_test(tc_core, test_debug_ok280);
    tcase_add_test(tc_core, test_debug_ok281);
    tcase_add_test(tc_core, test_debug_ok282);
    tcase_add_test(tc_core, test_debug_ok283);
    tcase_add_test(tc_core, test_debug_ok284);
    tcase_add_test(tc_core, test_debug_ok285);
    tcase_add_test(tc_core, test_debug_ok286);
    tcase_add_test(tc_core, test_debug_ok287);
    tcase_add_test(tc_core, test_debug_ok288);
    tcase_add_test(tc_core, test_debug_ok289);
    tcase_add_test(tc_core, test_debug_ok290);
    tcase_add_test(tc_core, test_debug_ok291);
    tcase_add_test(tc_core, test_debug_ok292);
    tcase_add_test(tc_core, test_debug_ok293);
    tcase_add_test(tc_core, test_debug_ok294);
    tcase_add_test(tc_core, test_debug_ok295);
    tcase_add_test(tc_core, test_debug_ok296);
    tcase_add_test(tc_core, test_debug_ok297);
    tcase_add_test(tc_core, test_debug_ok298);
    tcase_add_test(tc_core, test_debug_ok299);
    tcase_add_test(tc_core, test_debug_ok300);
    tcase_add_test(tc_core, test_debug_ok301);
    tcase_add_test(tc_core, test_debug_ok302);
    tcase_add_test(tc_core, test_debug_ok303);
    tcase_add_test(tc_core, test_debug_ok304);
    tcase_add_test(tc_core, test_debug_ok305);
    tcase_add_test(tc_core, test_debug_ok306);
    tcase_add_test(tc_core, test_debug_ok307);
    tcase_add_test(tc_core, test_debug_ok308);
    tcase_add_test(tc_core, test_debug_ok309);
    tcase_add_test(tc_core, test_debug_ok310);
    tcase_add_test(tc_core, test_debug_ok311);
    tcase_add_test(tc_core, test_debug_ok312);
    tcase_add_test(tc_core, test_debug_ok313);
    tcase_add_test(tc_core, test_debug_ok314);
    tcase_add_test(tc_core, test_debug_ok315);
    tcase_add_test(tc_core, test_debug_ok316);
    tcase_add_test(tc_core, test_debug_ok317);
    tcase_add_test(tc_core, test_debug_ok318);
    tcase_add_test(tc_core, test_debug_ok319);
    tcase_add_test(tc_core, test_debug_ok320);
    tcase_add_test(tc_core, test_debug_ok321);
    tcase_add_test(tc_core, test_debug_ok322);
    tcase_add_test(tc_core, test_debug_ok323);
    tcase_add_test(tc_core, test_debug_ok324);
    tcase_add_test(tc_core, test_debug_ok325);
    tcase_add_test(tc_core, test_debug_ok326);
    tcase_add_test(tc_core, test_debug_ok327);
    tcase_add_test(tc_core, test_debug_ok328);
    tcase_add_test(tc_core, test_debug_ok329);
    tcase_add_test(tc_core, test_debug_ok330);
    tcase_add_test(tc_core, test_debug_ok331);
    tcase_add_test(tc_core, test_debug_ok332);
    tcase_add_test(tc_core, test_debug_ok333);
    tcase_add_test(tc_core, test_debug_ok334);
    tcase_add_test(tc_core, test_debug_ok335);
    tcase_add_test(tc_core, test_debug_ok336);
    tcase_add_test(tc_core, test_debug_ok337);
    tcase_add_test(tc_core, test_debug_ok338);
    tcase_add_test(tc_core, test_debug_ok339);
    tcase_add_test(tc_core, test_debug_ok340);
    tcase_add_test(tc_core, test_debug_ok341);
    tcase_add_test(tc_core, test_debug_ok342);
    tcase_add_test(tc_core, test_debug_ok343);
    tcase_add_test(tc_core, test_debug_ok344);
    tcase_add_test(tc_core, test_debug_ok345);
    tcase_add_test(tc_core, test_debug_ok346);
    tcase_add_test(tc_core, test_debug_ok347);
    tcase_add_test(tc_core, test_debug_ok348);
    tcase_add_test(tc_core, test_debug_ok349);
    tcase_add_test(tc_core, test_debug_ok350);
    tcase_add_test(tc_core, test_debug_ok351);
    tcase_add_test(tc_core, test_debug_ok352);
    tcase_add_test(tc_core, test_debug_ok353);
    tcase_add_test(tc_core, test_debug_ok354);
    tcase_add_test(tc_core, test_debug_ok355);
    tcase_add_test(tc_core, test_debug_ok356);
    tcase_add_test(tc_core, test_debug_ok357);
    tcase_add_test(tc_core, test_debug_ok358);
    tcase_add_test(tc_core, test_debug_ok359);
    tcase_add_test(tc_core, test_debug_ok360);
    tcase_add_test(tc_core, test_debug_ok361);
    tcase_add_test(tc_core, test_debug_ok362);
    tcase_add_test(tc_core, test_debug_ok363);
    tcase_add_test(tc_core, test_debug_ok364);
    tcase_add_test(tc_core, test_debug_ok365);
    tcase_add_test(tc_core, test_debug_ok366);
    tcase_add_test(tc_core, test_debug_ok367);
    tcase_add_test(tc_core, test_debug_ok368);
    tcase_add_test(tc_core, test_debug_ok369);
    tcase_add_test(tc_core, test_debug_ok370);
    tcase_add_test(tc_core, test_debug_ok371);
    tcase_add_test(tc_core, test_debug_ok372);
    tcase_add_test(tc_core, test_debug_ok373);
    tcase_add_test(tc_core, test_debug_ok374);
    tcase_add_test(tc_core, test_debug_ok375);
    tcase_add_test(tc_core, test_debug_ok376);
    tcase_add_test(tc_core, test_debug_ok377);
    tcase_add_test(tc_core, test_debug_ok378);
    tcase_add_test(tc_core, test_debug_ok379);
    tcase_add_test(tc_core, test_debug_ok380);
    tcase_add_test(tc_core, test_debug_ok381);
    tcase_add_test(tc_core, test_debug_ok382);
    tcase_add_test(tc_core, test_debug_ok383);
    tcase_add_test(tc_core, test_debug_ok384);
    tcase_add_test(tc_core, test_debug_ok385);
    tcase_add_test(tc_core, test_debug_ok386);
    tcase_add_test(tc_core, test_debug_ok387);
    tcase_add_test(tc_core, test_debug_ok388);
    tcase_add_test(tc_core, test_debug_ok389);
    tcase_add_test(tc_core, test_debug_ok390);
    tcase_add_test(tc_core, test_debug_ok391);
    tcase_add_test(tc_core, test_debug_ok392);
    tcase_add_test(tc_core, test_debug_ok393);
    tcase_add_test(tc_core, test_debug_ok394);
    tcase_add_test(tc_core, test_debug_ok395);
    tcase_add_test(tc_core, test_debug_ok396);
    tcase_add_test(tc_core, test_debug_ok397);
    tcase_add_test(tc_core, test_debug_ok398);
    tcase_add_test(tc_core, test_debug_ok399);
    tcase_add_test(tc_core, test_debug_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * debug2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_debug_ok401);
    tcase_add_test(tc_core, test_debug_ok402);
    tcase_add_test(tc_core, test_debug_ok403);
    tcase_add_test(tc_core, test_debug_ok404);
    tcase_add_test(tc_core, test_debug_ok405);
    tcase_add_test(tc_core, test_debug_ok406);
    tcase_add_test(tc_core, test_debug_ok407);
    tcase_add_test(tc_core, test_debug_ok408);
    tcase_add_test(tc_core, test_debug_ok409);
    tcase_add_test(tc_core, test_debug_ok410);
    tcase_add_test(tc_core, test_debug_ok411);
    tcase_add_test(tc_core, test_debug_ok412);
    tcase_add_test(tc_core, test_debug_ok413);
    tcase_add_test(tc_core, test_debug_ok414);
    tcase_add_test(tc_core, test_debug_ok415);
    tcase_add_test(tc_core, test_debug_ok416);
    tcase_add_test(tc_core, test_debug_ok417);
    tcase_add_test(tc_core, test_debug_ok418);
    tcase_add_test(tc_core, test_debug_ok419);
    tcase_add_test(tc_core, test_debug_ok420);
    tcase_add_test(tc_core, test_debug_ok421);
    tcase_add_test(tc_core, test_debug_ok422);
    tcase_add_test(tc_core, test_debug_ok423);
    tcase_add_test(tc_core, test_debug_ok424);
    tcase_add_test(tc_core, test_debug_ok425);
    tcase_add_test(tc_core, test_debug_ok426);
    tcase_add_test(tc_core, test_debug_ok427);
    tcase_add_test(tc_core, test_debug_ok428);
    tcase_add_test(tc_core, test_debug_ok429);
    tcase_add_test(tc_core, test_debug_ok430);
    tcase_add_test(tc_core, test_debug_ok431);
    tcase_add_test(tc_core, test_debug_ok432);
    tcase_add_test(tc_core, test_debug_ok433);
    tcase_add_test(tc_core, test_debug_ok434);
    tcase_add_test(tc_core, test_debug_ok435);
    tcase_add_test(tc_core, test_debug_ok436);
    tcase_add_test(tc_core, test_debug_ok437);
    tcase_add_test(tc_core, test_debug_ok438);
    tcase_add_test(tc_core, test_debug_ok439);
    tcase_add_test(tc_core, test_debug_ok440);
    tcase_add_test(tc_core, test_debug_ok441);
    tcase_add_test(tc_core, test_debug_ok442);
    tcase_add_test(tc_core, test_debug_ok443);
    tcase_add_test(tc_core, test_debug_ok444);
    tcase_add_test(tc_core, test_debug_ok445);
    tcase_add_test(tc_core, test_debug_ok446);
    tcase_add_test(tc_core, test_debug_ok447);
    tcase_add_test(tc_core, test_debug_ok448);
    tcase_add_test(tc_core, test_debug_ok449);
    tcase_add_test(tc_core, test_debug_ok450);
    tcase_add_test(tc_core, test_debug_ok451);
    tcase_add_test(tc_core, test_debug_ok452);
    tcase_add_test(tc_core, test_debug_ok453);
    tcase_add_test(tc_core, test_debug_ok454);
    tcase_add_test(tc_core, test_debug_ok455);
    tcase_add_test(tc_core, test_debug_ok456);
    tcase_add_test(tc_core, test_debug_ok457);
    tcase_add_test(tc_core, test_debug_ok458);
    tcase_add_test(tc_core, test_debug_ok459);
    tcase_add_test(tc_core, test_debug_ok460);
    tcase_add_test(tc_core, test_debug_ok461);
    tcase_add_test(tc_core, test_debug_ok462);
    tcase_add_test(tc_core, test_debug_ok463);
    tcase_add_test(tc_core, test_debug_ok464);
    tcase_add_test(tc_core, test_debug_ok465);
    tcase_add_test(tc_core, test_debug_ok466);
    tcase_add_test(tc_core, test_debug_ok467);
    tcase_add_test(tc_core, test_debug_ok468);
    tcase_add_test(tc_core, test_debug_ok469);
    tcase_add_test(tc_core, test_debug_ok470);
    tcase_add_test(tc_core, test_debug_ok471);
    tcase_add_test(tc_core, test_debug_ok472);
    tcase_add_test(tc_core, test_debug_ok473);
    tcase_add_test(tc_core, test_debug_ok474);
    tcase_add_test(tc_core, test_debug_ok475);
    tcase_add_test(tc_core, test_debug_ok476);
    tcase_add_test(tc_core, test_debug_ok477);
    tcase_add_test(tc_core, test_debug_ok478);
    tcase_add_test(tc_core, test_debug_ok479);
    tcase_add_test(tc_core, test_debug_ok480);
    tcase_add_test(tc_core, test_debug_ok481);
    tcase_add_test(tc_core, test_debug_ok482);
    tcase_add_test(tc_core, test_debug_ok483);
    tcase_add_test(tc_core, test_debug_ok484);
    tcase_add_test(tc_core, test_debug_ok485);
    tcase_add_test(tc_core, test_debug_ok486);
    tcase_add_test(tc_core, test_debug_ok487);
    tcase_add_test(tc_core, test_debug_ok488);
    tcase_add_test(tc_core, test_debug_ok489);
    tcase_add_test(tc_core, test_debug_ok490);
    tcase_add_test(tc_core, test_debug_ok491);
    tcase_add_test(tc_core, test_debug_ok492);
    tcase_add_test(tc_core, test_debug_ok493);
    tcase_add_test(tc_core, test_debug_ok494);
    tcase_add_test(tc_core, test_debug_ok495);
    tcase_add_test(tc_core, test_debug_ok496);
    tcase_add_test(tc_core, test_debug_ok497);
    tcase_add_test(tc_core, test_debug_ok498);
    tcase_add_test(tc_core, test_debug_ok499);
    tcase_add_test(tc_core, test_debug_ok500);
    tcase_add_test(tc_core, test_debug_ok501);
    tcase_add_test(tc_core, test_debug_ok502);
    tcase_add_test(tc_core, test_debug_ok503);
    tcase_add_test(tc_core, test_debug_ok504);
    tcase_add_test(tc_core, test_debug_ok505);
    tcase_add_test(tc_core, test_debug_ok506);
    tcase_add_test(tc_core, test_debug_ok507);
    tcase_add_test(tc_core, test_debug_ok508);
    tcase_add_test(tc_core, test_debug_ok509);
    tcase_add_test(tc_core, test_debug_ok510);
    tcase_add_test(tc_core, test_debug_ok511);
    tcase_add_test(tc_core, test_debug_ok512);
    tcase_add_test(tc_core, test_debug_ok513);
    tcase_add_test(tc_core, test_debug_ok514);
    tcase_add_test(tc_core, test_debug_ok515);
    tcase_add_test(tc_core, test_debug_ok516);
    tcase_add_test(tc_core, test_debug_ok517);
    tcase_add_test(tc_core, test_debug_ok518);
    tcase_add_test(tc_core, test_debug_ok519);
    tcase_add_test(tc_core, test_debug_ok520);
    tcase_add_test(tc_core, test_debug_ok521);
    tcase_add_test(tc_core, test_debug_ok522);
    tcase_add_test(tc_core, test_debug_ok523);
    tcase_add_test(tc_core, test_debug_ok524);
    tcase_add_test(tc_core, test_debug_ok525);
    tcase_add_test(tc_core, test_debug_ok526);
    tcase_add_test(tc_core, test_debug_ok527);
    tcase_add_test(tc_core, test_debug_ok528);
    tcase_add_test(tc_core, test_debug_ok529);
    tcase_add_test(tc_core, test_debug_ok530);
    tcase_add_test(tc_core, test_debug_ok531);
    tcase_add_test(tc_core, test_debug_ok532);
    tcase_add_test(tc_core, test_debug_ok533);
    tcase_add_test(tc_core, test_debug_ok534);
    tcase_add_test(tc_core, test_debug_ok535);
    tcase_add_test(tc_core, test_debug_ok536);
    tcase_add_test(tc_core, test_debug_ok537);
    tcase_add_test(tc_core, test_debug_ok538);
    tcase_add_test(tc_core, test_debug_ok539);
    tcase_add_test(tc_core, test_debug_ok540);
    tcase_add_test(tc_core, test_debug_ok541);
    tcase_add_test(tc_core, test_debug_ok542);
    tcase_add_test(tc_core, test_debug_ok543);
    tcase_add_test(tc_core, test_debug_ok544);
    tcase_add_test(tc_core, test_debug_ok545);
    tcase_add_test(tc_core, test_debug_ok546);
    tcase_add_test(tc_core, test_debug_ok547);
    tcase_add_test(tc_core, test_debug_ok548);
    tcase_add_test(tc_core, test_debug_ok549);
    tcase_add_test(tc_core, test_debug_ok550);
    tcase_add_test(tc_core, test_debug_ok551);
    tcase_add_test(tc_core, test_debug_ok552);
    tcase_add_test(tc_core, test_debug_ok553);
    tcase_add_test(tc_core, test_debug_ok554);
    tcase_add_test(tc_core, test_debug_ok555);
    tcase_add_test(tc_core, test_debug_ok556);
    tcase_add_test(tc_core, test_debug_ok557);
    tcase_add_test(tc_core, test_debug_ok558);
    tcase_add_test(tc_core, test_debug_ok559);
    tcase_add_test(tc_core, test_debug_ok560);
    tcase_add_test(tc_core, test_debug_ok561);
    tcase_add_test(tc_core, test_debug_ok562);
    tcase_add_test(tc_core, test_debug_ok563);
    tcase_add_test(tc_core, test_debug_ok564);
    tcase_add_test(tc_core, test_debug_ok565);
    tcase_add_test(tc_core, test_debug_ok566);
    tcase_add_test(tc_core, test_debug_ok567);
    tcase_add_test(tc_core, test_debug_ok568);
    tcase_add_test(tc_core, test_debug_ok569);
    tcase_add_test(tc_core, test_debug_ok570);
    tcase_add_test(tc_core, test_debug_ok571);
    tcase_add_test(tc_core, test_debug_ok572);
    tcase_add_test(tc_core, test_debug_ok573);
    tcase_add_test(tc_core, test_debug_ok574);
    tcase_add_test(tc_core, test_debug_ok575);
    tcase_add_test(tc_core, test_debug_ok576);
    tcase_add_test(tc_core, test_debug_ok577);
    tcase_add_test(tc_core, test_debug_ok578);
    tcase_add_test(tc_core, test_debug_ok579);
    tcase_add_test(tc_core, test_debug_ok580);
    tcase_add_test(tc_core, test_debug_ok581);
    tcase_add_test(tc_core, test_debug_ok582);
    tcase_add_test(tc_core, test_debug_ok583);
    tcase_add_test(tc_core, test_debug_ok584);
    tcase_add_test(tc_core, test_debug_ok585);
    tcase_add_test(tc_core, test_debug_ok586);
    tcase_add_test(tc_core, test_debug_ok587);
    tcase_add_test(tc_core, test_debug_ok588);
    tcase_add_test(tc_core, test_debug_ok589);
    tcase_add_test(tc_core, test_debug_ok590);
    tcase_add_test(tc_core, test_debug_ok591);
    tcase_add_test(tc_core, test_debug_ok592);
    tcase_add_test(tc_core, test_debug_ok593);
    tcase_add_test(tc_core, test_debug_ok594);
    tcase_add_test(tc_core, test_debug_ok595);
    tcase_add_test(tc_core, test_debug_ok596);
    tcase_add_test(tc_core, test_debug_ok597);
    tcase_add_test(tc_core, test_debug_ok598);
    tcase_add_test(tc_core, test_debug_ok599);
    tcase_add_test(tc_core, test_debug_ok600);
    tcase_add_test(tc_core, test_debug_ok601);
    tcase_add_test(tc_core, test_debug_ok602);
    tcase_add_test(tc_core, test_debug_ok603);
    tcase_add_test(tc_core, test_debug_ok604);
    tcase_add_test(tc_core, test_debug_ok605);
    tcase_add_test(tc_core, test_debug_ok606);
    tcase_add_test(tc_core, test_debug_ok607);
    tcase_add_test(tc_core, test_debug_ok608);
    tcase_add_test(tc_core, test_debug_ok609);
    tcase_add_test(tc_core, test_debug_ok610);
    tcase_add_test(tc_core, test_debug_ok611);
    tcase_add_test(tc_core, test_debug_ok612);
    tcase_add_test(tc_core, test_debug_ok613);
    tcase_add_test(tc_core, test_debug_ok614);
    tcase_add_test(tc_core, test_debug_ok615);
    tcase_add_test(tc_core, test_debug_ok616);
    tcase_add_test(tc_core, test_debug_ok617);
    tcase_add_test(tc_core, test_debug_ok618);
    tcase_add_test(tc_core, test_debug_ok619);
    tcase_add_test(tc_core, test_debug_ok620);
    tcase_add_test(tc_core, test_debug_ok621);
    tcase_add_test(tc_core, test_debug_ok622);
    tcase_add_test(tc_core, test_debug_ok623);
    tcase_add_test(tc_core, test_debug_ok624);
    tcase_add_test(tc_core, test_debug_ok625);
    tcase_add_test(tc_core, test_debug_ok626);
    tcase_add_test(tc_core, test_debug_ok627);
    tcase_add_test(tc_core, test_debug_ok628);
    tcase_add_test(tc_core, test_debug_ok629);
    tcase_add_test(tc_core, test_debug_ok630);
    tcase_add_test(tc_core, test_debug_ok631);
    tcase_add_test(tc_core, test_debug_ok632);
    tcase_add_test(tc_core, test_debug_ok633);
    tcase_add_test(tc_core, test_debug_ok634);
    tcase_add_test(tc_core, test_debug_ok635);
    tcase_add_test(tc_core, test_debug_ok636);
    tcase_add_test(tc_core, test_debug_ok637);
    tcase_add_test(tc_core, test_debug_ok638);
    tcase_add_test(tc_core, test_debug_ok639);
    tcase_add_test(tc_core, test_debug_ok640);
    tcase_add_test(tc_core, test_debug_ok641);
    tcase_add_test(tc_core, test_debug_ok642);
    tcase_add_test(tc_core, test_debug_ok643);
    tcase_add_test(tc_core, test_debug_ok644);
    tcase_add_test(tc_core, test_debug_ok645);
    tcase_add_test(tc_core, test_debug_ok646);
    tcase_add_test(tc_core, test_debug_ok647);
    tcase_add_test(tc_core, test_debug_ok648);
    tcase_add_test(tc_core, test_debug_ok649);
    tcase_add_test(tc_core, test_debug_ok650);
    tcase_add_test(tc_core, test_debug_ok651);
    tcase_add_test(tc_core, test_debug_ok652);
    tcase_add_test(tc_core, test_debug_ok653);
    tcase_add_test(tc_core, test_debug_ok654);
    tcase_add_test(tc_core, test_debug_ok655);
    tcase_add_test(tc_core, test_debug_ok656);
    tcase_add_test(tc_core, test_debug_ok657);
    tcase_add_test(tc_core, test_debug_ok658);
    tcase_add_test(tc_core, test_debug_ok659);
    tcase_add_test(tc_core, test_debug_ok660);
    tcase_add_test(tc_core, test_debug_ok661);
    tcase_add_test(tc_core, test_debug_ok662);
    tcase_add_test(tc_core, test_debug_ok663);
    tcase_add_test(tc_core, test_debug_ok664);
    tcase_add_test(tc_core, test_debug_ok665);
    tcase_add_test(tc_core, test_debug_ok666);
    tcase_add_test(tc_core, test_debug_ok667);
    tcase_add_test(tc_core, test_debug_ok668);
    tcase_add_test(tc_core, test_debug_ok669);
    tcase_add_test(tc_core, test_debug_ok670);
    tcase_add_test(tc_core, test_debug_ok671);
    tcase_add_test(tc_core, test_debug_ok672);
    tcase_add_test(tc_core, test_debug_ok673);
    tcase_add_test(tc_core, test_debug_ok674);
    tcase_add_test(tc_core, test_debug_ok675);
    tcase_add_test(tc_core, test_debug_ok676);
    tcase_add_test(tc_core, test_debug_ok677);
    tcase_add_test(tc_core, test_debug_ok678);
    tcase_add_test(tc_core, test_debug_ok679);
    tcase_add_test(tc_core, test_debug_ok680);
    tcase_add_test(tc_core, test_debug_ok681);
    tcase_add_test(tc_core, test_debug_ok682);
    tcase_add_test(tc_core, test_debug_ok683);
    tcase_add_test(tc_core, test_debug_ok684);
    tcase_add_test(tc_core, test_debug_ok685);
    tcase_add_test(tc_core, test_debug_ok686);
    tcase_add_test(tc_core, test_debug_ok687);
    tcase_add_test(tc_core, test_debug_ok688);
    tcase_add_test(tc_core, test_debug_ok689);
    tcase_add_test(tc_core, test_debug_ok690);
    tcase_add_test(tc_core, test_debug_ok691);
    tcase_add_test(tc_core, test_debug_ok692);
    tcase_add_test(tc_core, test_debug_ok693);
    tcase_add_test(tc_core, test_debug_ok694);
    tcase_add_test(tc_core, test_debug_ok695);
    tcase_add_test(tc_core, test_debug_ok696);
    tcase_add_test(tc_core, test_debug_ok697);
    tcase_add_test(tc_core, test_debug_ok698);
    tcase_add_test(tc_core, test_debug_ok699);
    tcase_add_test(tc_core, test_debug_ok700);
    tcase_add_test(tc_core, test_debug_ok701);
    tcase_add_test(tc_core, test_debug_ok702);
    tcase_add_test(tc_core, test_debug_ok703);
    tcase_add_test(tc_core, test_debug_ok704);
    tcase_add_test(tc_core, test_debug_ok705);
    tcase_add_test(tc_core, test_debug_ok706);
    tcase_add_test(tc_core, test_debug_ok707);
    tcase_add_test(tc_core, test_debug_ok708);
    tcase_add_test(tc_core, test_debug_ok709);
    tcase_add_test(tc_core, test_debug_ok710);
    tcase_add_test(tc_core, test_debug_ok711);
    tcase_add_test(tc_core, test_debug_ok712);
    tcase_add_test(tc_core, test_debug_ok713);
    tcase_add_test(tc_core, test_debug_ok714);
    tcase_add_test(tc_core, test_debug_ok715);
    tcase_add_test(tc_core, test_debug_ok716);
    tcase_add_test(tc_core, test_debug_ok717);
    tcase_add_test(tc_core, test_debug_ok718);
    tcase_add_test(tc_core, test_debug_ok719);
    tcase_add_test(tc_core, test_debug_ok720);
    tcase_add_test(tc_core, test_debug_ok721);
    tcase_add_test(tc_core, test_debug_ok722);
    tcase_add_test(tc_core, test_debug_ok723);
    tcase_add_test(tc_core, test_debug_ok724);
    tcase_add_test(tc_core, test_debug_ok725);
    tcase_add_test(tc_core, test_debug_ok726);
    tcase_add_test(tc_core, test_debug_ok727);
    tcase_add_test(tc_core, test_debug_ok728);
    tcase_add_test(tc_core, test_debug_ok729);
    tcase_add_test(tc_core, test_debug_ok730);
    tcase_add_test(tc_core, test_debug_ok731);
    tcase_add_test(tc_core, test_debug_ok732);
    tcase_add_test(tc_core, test_debug_ok733);
    tcase_add_test(tc_core, test_debug_ok734);
    tcase_add_test(tc_core, test_debug_ok735);
    tcase_add_test(tc_core, test_debug_ok736);
    tcase_add_test(tc_core, test_debug_ok737);
    tcase_add_test(tc_core, test_debug_ok738);
    tcase_add_test(tc_core, test_debug_ok739);
    tcase_add_test(tc_core, test_debug_ok740);
    tcase_add_test(tc_core, test_debug_ok741);
    tcase_add_test(tc_core, test_debug_ok742);
    tcase_add_test(tc_core, test_debug_ok743);
    tcase_add_test(tc_core, test_debug_ok744);
    tcase_add_test(tc_core, test_debug_ok745);
    tcase_add_test(tc_core, test_debug_ok746);
    tcase_add_test(tc_core, test_debug_ok747);
    tcase_add_test(tc_core, test_debug_ok748);
    tcase_add_test(tc_core, test_debug_ok749);
    tcase_add_test(tc_core, test_debug_ok750);
    tcase_add_test(tc_core, test_debug_ok751);
    tcase_add_test(tc_core, test_debug_ok752);
    tcase_add_test(tc_core, test_debug_ok753);
    tcase_add_test(tc_core, test_debug_ok754);
    tcase_add_test(tc_core, test_debug_ok755);
    tcase_add_test(tc_core, test_debug_ok756);
    tcase_add_test(tc_core, test_debug_ok757);
    tcase_add_test(tc_core, test_debug_ok758);
    tcase_add_test(tc_core, test_debug_ok759);
    tcase_add_test(tc_core, test_debug_ok760);
    tcase_add_test(tc_core, test_debug_ok761);
    tcase_add_test(tc_core, test_debug_ok762);
    tcase_add_test(tc_core, test_debug_ok763);
    tcase_add_test(tc_core, test_debug_ok764);
    tcase_add_test(tc_core, test_debug_ok765);
    tcase_add_test(tc_core, test_debug_ok766);
    tcase_add_test(tc_core, test_debug_ok767);
    tcase_add_test(tc_core, test_debug_ok768);
    tcase_add_test(tc_core, test_debug_ok769);
    tcase_add_test(tc_core, test_debug_ok770);
    tcase_add_test(tc_core, test_debug_ok771);
    tcase_add_test(tc_core, test_debug_ok772);
    tcase_add_test(tc_core, test_debug_ok773);
    tcase_add_test(tc_core, test_debug_ok774);
    tcase_add_test(tc_core, test_debug_ok775);
    tcase_add_test(tc_core, test_debug_ok776);
    tcase_add_test(tc_core, test_debug_ok777);
    tcase_add_test(tc_core, test_debug_ok778);
    tcase_add_test(tc_core, test_debug_ok779);
    tcase_add_test(tc_core, test_debug_ok780);
    tcase_add_test(tc_core, test_debug_ok781);
    tcase_add_test(tc_core, test_debug_ok782);
    tcase_add_test(tc_core, test_debug_ok783);
    tcase_add_test(tc_core, test_debug_ok784);
    tcase_add_test(tc_core, test_debug_ok785);
    tcase_add_test(tc_core, test_debug_ok786);
    tcase_add_test(tc_core, test_debug_ok787);
    tcase_add_test(tc_core, test_debug_ok788);
    tcase_add_test(tc_core, test_debug_ok789);
    tcase_add_test(tc_core, test_debug_ok790);
    tcase_add_test(tc_core, test_debug_ok791);
    tcase_add_test(tc_core, test_debug_ok792);
    tcase_add_test(tc_core, test_debug_ok793);
    tcase_add_test(tc_core, test_debug_ok794);
    tcase_add_test(tc_core, test_debug_ok795);
    tcase_add_test(tc_core, test_debug_ok796);
    tcase_add_test(tc_core, test_debug_ok797);
    tcase_add_test(tc_core, test_debug_ok798);
    tcase_add_test(tc_core, test_debug_ok799);
    tcase_add_test(tc_core, test_debug_ok800);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * debug3(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug3");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_debug_ok801);
    tcase_add_test(tc_core, test_debug_ok802);
    tcase_add_test(tc_core, test_debug_ok803);
    tcase_add_test(tc_core, test_debug_ok804);
    tcase_add_test(tc_core, test_debug_ok805);
    tcase_add_test(tc_core, test_debug_ok806);
    tcase_add_test(tc_core, test_debug_ok807);
    tcase_add_test(tc_core, test_debug_ok808);
    tcase_add_test(tc_core, test_debug_ok809);
    tcase_add_test(tc_core, test_debug_ok810);
    tcase_add_test(tc_core, test_debug_ok811);
    tcase_add_test(tc_core, test_debug_ok812);
    tcase_add_test(tc_core, test_debug_ok813);
    tcase_add_test(tc_core, test_debug_ok814);
    tcase_add_test(tc_core, test_debug_ok815);
    tcase_add_test(tc_core, test_debug_ok816);
    tcase_add_test(tc_core, test_debug_ok817);
    tcase_add_test(tc_core, test_debug_ok818);
    tcase_add_test(tc_core, test_debug_ok819);
    tcase_add_test(tc_core, test_debug_ok820);
    tcase_add_test(tc_core, test_debug_ok821);
    tcase_add_test(tc_core, test_debug_ok822);
    tcase_add_test(tc_core, test_debug_ok823);
    tcase_add_test(tc_core, test_debug_ok824);
    tcase_add_test(tc_core, test_debug_ok825);
    tcase_add_test(tc_core, test_debug_ok826);
    tcase_add_test(tc_core, test_debug_ok827);
    tcase_add_test(tc_core, test_debug_ok828);
    tcase_add_test(tc_core, test_debug_ok829);
    tcase_add_test(tc_core, test_debug_ok830);
    tcase_add_test(tc_core, test_debug_ok831);
    tcase_add_test(tc_core, test_debug_ok832);
    tcase_add_test(tc_core, test_debug_ok833);
    tcase_add_test(tc_core, test_debug_ok834);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite * debug0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("debug0");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_debug_fail1);
    tcase_add_test(tc_core, test_debug_fail2);
    tcase_add_test(tc_core, test_debug_fail3);
    tcase_add_test(tc_core, test_debug_fail4);
    tcase_add_test(tc_core, test_debug_fail5);
    tcase_add_test(tc_core, test_debug_fail6);
    tcase_add_test(tc_core, test_debug_fail7);
    tcase_add_test(tc_core, test_debug_fail8);

    tcase_add_test(tc_core, test_debug_create1);
    tcase_add_test(tc_core, test_debug_create2);
    tcase_add_test(tc_core, test_debug_create3);
    tcase_add_test(tc_core, test_debug_create4);

    suite_add_tcase(s, tc_core);

    return s;
}

void test_debug(s21_decimal decimal, char *check) {
    #if defined(__DEBUG)
    s21_print_decimal_bits(decimal);
    s21_print_decimal_string(decimal);
    printf("%s\n", check);
    #endif

    char res[1024];
    s21_decimal_to_string(decimal, res);
    ck_assert_str_eq(check, res);
}
