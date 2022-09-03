#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../test.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные (ручные)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
START_TEST(test_from_decimal_to_int_fail_manual1) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int code = s21_from_decimal_to_int(decimal, NULL);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}

START_TEST(test_from_decimal_to_int_fail_manual2) {
    // степень 154 (показатель степени должен быть от 0 до 28)
    // биты 0-15 не нули
    // биты 24-30 не нули
    s21_decimal decimal = {{0, 0, 0, 1000000000}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual3) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual4) {
    // степень 29 (показатель степени должен быть от 0 до 28)
    s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual5) {
    // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual6) {
    // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual7) {
    // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual8) {
    // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
    s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_fail_manual9) {
    // Просто все единицы
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_decimal_to_int_ok1) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int check = 792281625;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok2) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    int check = -792281625;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok3) {
    // 79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    int check = 79228162;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok4) {
    // -79228162.514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    int check = -79228162;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok5) {
    // 7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    int check = 7922816;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok6) {
    // -7922816.2514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    int check = -7922816;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok7) {
    // 792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    int check = 792281;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok8) {
    // -792281.62514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    int check = -792281;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok9) {
    // 79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    int check = 79228;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok10) {
    // -79228.162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    int check = -79228;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok11) {
    // 7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    int check = 7922;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok12) {
    // -7922.8162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    int check = -7922;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok13) {
    // 792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    int check = 792;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok14) {
    // -792.28162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    int check = -792;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok15) {
    // 79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    int check = 79;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok16) {
    // -79.228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    int check = -79;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok17) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok18) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok19) {
    // 792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int check = 792281625;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok20) {
    // -792281625.14264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    int check = -792281625;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok21) {
    // 79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    int check = 79228162;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok22) {
    // -79228162.514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    int check = -79228162;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok23) {
    // 7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
    int check = 7922816;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok24) {
    // -7922816.2514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
    int check = -7922816;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok25) {
    // 792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
    int check = 792281;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok26) {
    // -792281.62514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
    int check = -792281;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok27) {
    // 79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
    int check = 79228;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok28) {
    // -79228.162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
    int check = -79228;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok29) {
    // 7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
    int check = 7922;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok30) {
    // -7922.8162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
    int check = -7922;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok31) {
    // 792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
    int check = 792;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok32) {
    // -792.28162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
    int check = -792;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok33) {
    // 79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
    int check = 79;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok34) {
    // -79.228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
    int check = -79;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok35) {
    // 7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok36) {
    // -7.9228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok37) {
    // 528187750.09509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
    int check = 528187750;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok38) {
    // -528187750.09509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
    int check = -528187750;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok39) {
    // 5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    int check = 5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok40) {
    // -5.2818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    int check = -5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok41) {
    // 528187750.09509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
    int check = 528187750;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok42) {
    // -528187750.09509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
    int check = -528187750;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok43) {
    // 5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
    int check = 5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok44) {
    // -5.2818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
    int check = -5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok45) {
    // 528187749.97211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x140000}};
    int check = 528187749;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok46) {
    // -528187749.97211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80140000}};
    int check = -528187749;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok47) {
    // 5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x1C0000}};
    int check = 5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok48) {
    // -5.2818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x801C0000}};
    int check = -5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok49) {
    // 528187749.97211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x140000}};
    int check = 528187749;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok50) {
    // -528187749.97211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80140000}};
    int check = -528187749;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok51) {
    // 5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x1C0000}};
    int check = 5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok52) {
    // -5.2818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x801C0000}};
    int check = -5;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok53) {
    // 122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0xB0000}};
    int check = 122978293;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok54) {
    // -122978293.82473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x800B0000}};
    int check = -122978293;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok55) {
    // 1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok56) {
    // -1.2297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok57) {
    // 122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
    int check = 122978293;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok58) {
    // -122978293.79609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
    int check = -122978293;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok59) {
    // 1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok60) {
    // -1.2297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok61) {
    // 286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
    int check = 286331153;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok62) {
    // -286331153.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
    int check = -286331153;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok63) {
    // 286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x40000}};
    int check = 286331;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok64) {
    // -286331.1530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80040000}};
    int check = -286331;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok65) {
    // 2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x90000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok66) {
    // -2.863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80090000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok67) {
    // 264093875.04754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x140000}};
    int check = 264093875;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok68) {
    // -264093875.04754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80140000}};
    int check = -264093875;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok69) {
    // 2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok70) {
    // -2.6409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x801C0000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok71) {
    // 264093875.04754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x140000}};
    int check = 264093875;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok72) {
    // -264093875.04754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80140000}};
    int check = -264093875;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok73) {
    // 2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x1C0000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok74) {
    // -2.6409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x801C0000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok75) {
    // 264093874.98605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x140000}};
    int check = 264093874;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok76) {
    // -264093874.98605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80140000}};
    int check = -264093874;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok77) {
    // 2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok78) {
    // -2.6409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok79) {
    // 264093874.98605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x140000}};
    int check = 264093874;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok80) {
    // -264093874.98605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80140000}};
    int check = -264093874;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok81) {
    // 2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x1C0000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok82) {
    // -2.6409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x801C0000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok83) {
    // 6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0xC0000}};
    int check = 6148914;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok84) {
    // -6148914.691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x800C0000}};
    int check = -6148914;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok85) {
    // 6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x120000}};
    int check = 6;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok86) {
    // -6.148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80120000}};
    int check = -6;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok87) {
    // 6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0xC0000}};
    int check = 6148914;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok88) {
    // -6148914.689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x800C0000}};
    int check = -6148914;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok89) {
    // 6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x120000}};
    int check = 6;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok90) {
    // -6.148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80120000}};
    int check = -6;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok91) {
    // 1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x0}};
    int check = 1431655765;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok92) {
    // -1431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80000000}};
    int check = -1431655765;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok93) {
    // 143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x10000}};
    int check = 143165576;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok94) {
    // -143165576.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80010000}};
    int check = -143165576;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok95) {
    // 143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x40000}};
    int check = 143165;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok96) {
    // -143165.5765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80040000}};
    int check = -143165;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok97) {
    // 1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x90000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok98) {
    // -1.431655765
    s21_decimal decimal = {{0x55555555, 0x0, 0x0, 0x80090000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok99) {
    // 184467440.78004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0xB0000}};
    int check = 184467440;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok100) {
    // -184467440.78004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x800B0000}};
    int check = -184467440;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok101) {
    // 1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok102) {
    // -1.8446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok103) {
    // 18446744.078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0xC0000}};
    int check = 18446744;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok104) {
    // -18446744.078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x800C0000}};
    int check = -18446744;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok105) {
    // 1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok106) {
    // -1.8446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok107) {
    // 1844674.4073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0xD0000}};
    int check = 1844674;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok108) {
    // -1844674.4073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x800D0000}};
    int check = -1844674;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok109) {
    // 1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok110) {
    // -1.8446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok111) {
    // 184467.44073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0xE0000}};
    int check = 184467;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok112) {
    // -184467.44073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x800E0000}};
    int check = -184467;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok113) {
    // 1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok114) {
    // -1.8446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok115) {
    // 429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
    int check = 429496729;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok116) {
    // -429496729.7
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
    int check = -429496729;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok117) {
    // 42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x20000}};
    int check = 42949672;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok118) {
    // -42949672.97
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80020000}};
    int check = -42949672;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok119) {
    // 429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x40000}};
    int check = 429496;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok120) {
    // -429496.7297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80040000}};
    int check = -429496;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok121) {
    // 4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x90000}};
    int check = 4;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok122) {
    // -4.294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80090000}};
    int check = -4;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok123) {
    // 42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000}};
    int check = 42;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok124) {
    // -42.94967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80080000}};
    int check = -42;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok125) {
    // 429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x10000}};
    int check = 429496729;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok126) {
    // -429496729.6
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80010000}};
    int check = -429496729;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok127) {
    // 42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x20000}};
    int check = 42949672;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok128) {
    // -42949672.96
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80020000}};
    int check = -42949672;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok129) {
    // 4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x30000}};
    int check = 4294967;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok130) {
    // -4294967.296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80030000}};
    int check = -4294967;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok131) {
    // 4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x90000}};
    int check = 4;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok132) {
    // -4.294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80090000}};
    int check = -4;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok133) {
    // 42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000}};
    int check = 42;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok134) {
    // -42.94967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80080000}};
    int check = -42;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok135) {
    // 1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok136) {
    // -1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok137) {
    // 0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok138) {
    // -0.1
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok139) {
    // 0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xD0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok140) {
    // -0.0000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800D0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok141) {
    // 0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0xE0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok142) {
    // -0.00000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x800E0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok143) {
    // 0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1B0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok144) {
    // -0.000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801B0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok145) {
    // 0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok146) {
    // -0.0000000000000000000000000001
    s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok147) {
    // 396140812.66355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x140000}};
    int check = 396140812;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok148) {
    // -396140812.66355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80140000}};
    int check = -396140812;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok149) {
    // 3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x1C0000}};
    int check = 3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok150) {
    // -3.9614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
    int check = -3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok151) {
    // 39614081.266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x150000}};
    int check = 39614081;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok152) {
    // -39614081.266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80150000}};
    int check = -39614081;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok153) {
    // 3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x1C0000}};
    int check = 3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok154) {
    // -3.9614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x801C0000}};
    int check = -3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok155) {
    // 3961408.1257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x160000}};
    int check = 3961408;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok156) {
    // -3961408.1257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80160000}};
    int check = -3961408;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok157) {
    // 3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x1C0000}};
    int check = 3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok158) {
    // -3.9614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x801C0000}};
    int check = -3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok159) {
    // 396140.81257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x170000}};
    int check = 396140;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok160) {
    // -396140.81257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80170000}};
    int check = -396140;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok161) {
    // 3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x1C0000}};
    int check = 3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok162) {
    // -3.9614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x801C0000}};
    int check = -3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok163) {
    // 922337203.9002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0xA0000}};
    int check = 922337203;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok164) {
    // -922337203.9002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x800A0000}};
    int check = -922337203;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok165) {
    // 9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x120000}};
    int check = 9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok166) {
    // -9.223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80120000}};
    int check = -9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok167) {
    // 92233720.36854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0xB0000}};
    int check = 92233720;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok168) {
    // -92233720.36854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x800B0000}};
    int check = -92233720;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok169) {
    // 9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x120000}};
    int check = 9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok170) {
    // -9.223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80120000}};
    int check = -9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok171) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    int check = -2147483648;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok172) {
    // 214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
    int check = 214748364;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok173) {
    // -214748364.8
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
    int check = -214748364;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok174) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    int check = 21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok175) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    int check = -21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok176) {
    // 214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x40000}};
    int check = 214748;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok177) {
    // -214748.3648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80040000}};
    int check = -214748;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok178) {
    // 21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000}};
    int check = 21;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok179) {
    // -21.47483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80080000}};
    int check = -21;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok180) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok181) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok182) {
    // 1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x140000}};
    int check = 1560647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok183) {
    // -1560647.67562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80140000}};
    int check = -1560647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok184) {
    // 1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok185) {
    // -1.56064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok186) {
    // 15606476.7562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x130000}};
    int check = 15606476;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok187) {
    // -15606476.7562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80130000}};
    int check = -15606476;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok188) {
    // 1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x1A0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok189) {
    // -1.56064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x801A0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok190) {
    // 156064.767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x150000}};
    int check = 156064;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok191) {
    // -156064.767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80150000}};
    int check = -156064;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok192) {
    // 1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x1A0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok193) {
    // -1.56064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x801A0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok194) {
    // 15606.4767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x160000}};
    int check = 15606;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok195) {
    // -15606.4767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80160000}};
    int check = -15606;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok196) {
    // 1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x1A0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok197) {
    // -1.56064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x801A0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok198) {
    // 363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000}};
    int check = 363366602;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok199) {
    // -363366602.83201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80080000}};
    int check = -363366602;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok200) {
    // 3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x100000}};
    int check = 3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok201) {
    // -3.6336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80100000}};
    int check = -3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok202) {
    // 3633666.0274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xA0000}};
    int check = 3633666;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok203) {
    // -3633666.0274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800A0000}};
    int check = -3633666;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok204) {
    // 363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000}};
    int check = 363366602;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok205) {
    // -363366602.74741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80080000}};
    int check = -363366602;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok206) {
    // 36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0xF0000}};
    int check = 36;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok207) {
    // -36.336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x800F0000}};
    int check = -36;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok208) {
    // 3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x100000}};
    int check = 3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok209) {
    // -3.6336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80100000}};
    int check = -3;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok210) {
    // 8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
    int check = 8460288;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok211) {
    // -8460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
    int check = -8460288;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok212) {
    // 846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x10000}};
    int check = 846028;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok213) {
    // -846028.8
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80010000}};
    int check = -846028;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok214) {
    // 84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x20000}};
    int check = 84602;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok215) {
    // -84602.88
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80020000}};
    int check = -84602;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok216) {
    // 8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x30000}};
    int check = 8460;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok217) {
    // -8460.288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80030000}};
    int check = -8460;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok218) {
    // 84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x50000}};
    int check = 84;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok219) {
    // -84.60288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80050000}};
    int check = -84;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok220) {
    // 8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x60000}};
    int check = 8;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok221) {
    // -8.460288
    s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80060000}};
    int check = -8;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok222) {
    // 792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
    int check = 792281625;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok223) {
    // -792281625.14264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
    int check = -792281625;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok224) {
    // 7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok225) {
    // -7.9228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok226) {
    // 79228162.514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
    int check = 79228162;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok227) {
    // -79228162.514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
    int check = -79228162;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok228) {
    // 7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
    int check = 7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok229) {
    // -7.9228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
    int check = -7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok230) {
    // 7922816.2495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x160000}};
    int check = 7922816;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok231) {
    // -7922816.2495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80160000}};
    int check = -7922816;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok232) {
    // 7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x1C0000}};
    int check = 7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok233) {
    // -7.9228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x801C0000}};
    int check = -7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok234) {
    // 792281.62495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x170000}};
    int check = 792281;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok235) {
    // -792281.62495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80170000}};
    int check = -792281;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok236) {
    // 7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x1C0000}};
    int check = 7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok237) {
    // -7.9228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x801C0000}};
    int check = -7;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok238) {
    // 184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xB0000}};
    int check = 184467440;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok239) {
    // -184467440.73709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x800B0000}};
    int check = -184467440;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok240) {
    // 184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x110000}};
    int check = 184;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok241) {
    // -184.46744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80110000}};
    int check = -184;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok242) {
    // 1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok243) {
    // -1.8446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok244) {
    // 18446744.069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0xC0000}};
    int check = 18446744;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok245) {
    // -18446744.069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x800C0000}};
    int check = -18446744;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok246) {
    // 184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x110000}};
    int check = 184;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok247) {
    // -184.46744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80110000}};
    int check = -184;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok248) {
    // 1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x130000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok249) {
    // -1.8446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80130000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok250) {
    // 429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x10000}};
    int check = 429496729;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok251) {
    // -429496729.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80010000}};
    int check = -429496729;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok252) {
    // 42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x20000}};
    int check = 42949672;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok253) {
    // -42949672.95
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80020000}};
    int check = -42949672;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok254) {
    // 42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
    int check = 42949;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok255) {
    // -42949.67295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
    int check = -42949;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok256) {
    // 42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
    int check = 42;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok257) {
    // -42.94967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
    int check = -42;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok258) {
    // 4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x90000}};
    int check = 4;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok259) {
    // -4.294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80090000}};
    int check = -4;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok260) {
    // 1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok261) {
    // -1.0
    s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok262) {
    // 1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x20000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok263) {
    // -1.00
    s21_decimal decimal = {{0x64, 0x0, 0x0, 0x80020000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok264) {
    // 1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x30000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok265) {
    // -1.000
    s21_decimal decimal = {{0x3E8, 0x0, 0x0, 0x80030000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok266) {
    // 1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok267) {
    // -1.0000000000
    s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok268) {
    // 1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x100000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok269) {
    // -1.0000000000000000
    s21_decimal decimal = {{0x6FC10000, 0x2386F2, 0x0, 0x80100000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok270) {
    // 1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x170000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok271) {
    // -1.00000000000000000000000
    s21_decimal decimal = {{0xF6800000, 0x2C7E14A, 0x152D, 0x80170000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok272) {
    // 1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x1B0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok273) {
    // -1.000000000000000000000000000
    s21_decimal decimal = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x801B0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok274) {
    // 1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x1C0000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok275) {
    // -1.0000000000000000000000000000
    s21_decimal decimal = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x801C0000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok276) {
    // 1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x10000}};
    int check = 1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok277) {
    // -1.1
    s21_decimal decimal = {{0xB, 0x0, 0x0, 0x80010000}};
    int check = -1;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok278) {
    // 12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x20000}};
    int check = 12;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok279) {
    // -12.12
    s21_decimal decimal = {{0x4BC, 0x0, 0x0, 0x80020000}};
    int check = -12;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok280) {
    // 123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x30000}};
    int check = 123;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok281) {
    // -123.123
    s21_decimal decimal = {{0x1E0F3, 0x0, 0x0, 0x80030000}};
    int check = -123;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok282) {
    // 1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x40000}};
    int check = 1234;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok283) {
    // -1234.1234
    s21_decimal decimal = {{0xBC4FF2, 0x0, 0x0, 0x80040000}};
    int check = -1234;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok284) {
    // 12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x50000}};
    int check = 12345;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok285) {
    // -12345.12345
    s21_decimal decimal = {{0x499529D9, 0x0, 0x0, 0x80050000}};
    int check = -12345;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok286) {
    // 123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x60000}};
    int check = 123456;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok287) {
    // -123456.123456
    s21_decimal decimal = {{0xBE8EF240, 0x1C, 0x0, 0x80060000}};
    int check = -123456;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok288) {
    // 1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x70000}};
    int check = 1234567;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok289) {
    // -1234567.1234567
    s21_decimal decimal = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
    int check = -1234567;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok290) {
    // 1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
    int check = 1234567890;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok291) {
    // -1234567890.1234567890
    s21_decimal decimal = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
    int check = -1234567890;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok292) {
    // 99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x0}};
    int check = 99;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok293) {
    // -99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80000000}};
    int check = -99;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok294) {
    // 9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x10000}};
    int check = 9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok295) {
    // -9.9
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80010000}};
    int check = -9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok296) {
    // 99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
    int check = 99;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok297) {
    // -99.99
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
    int check = -99;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok298) {
    // 999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x30000}};
    int check = 999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok299) {
    // -999.999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80030000}};
    int check = -999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok300) {
    // 9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x40000}};
    int check = 9999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok301) {
    // -9999.9999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80040000}};
    int check = -9999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok302) {
    // 99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x50000}};
    int check = 99999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok303) {
    // -99999.99999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x80050000}};
    int check = -99999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok304) {
    // 999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x60000}};
    int check = 999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok305) {
    // -999999.999999
    s21_decimal decimal = {{0xD4A50FFF, 0xE8, 0x0, 0x80060000}};
    int check = -999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok306) {
    // 9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x70000}};
    int check = 9999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok307) {
    // -9999999.9999999
    s21_decimal decimal = {{0x107A3FFF, 0x5AF3, 0x0, 0x80070000}};
    int check = -9999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok308) {
    // 99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80000}};
    int check = 99999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok309) {
    // -99999999.99999999
    s21_decimal decimal = {{0x6FC0FFFF, 0x2386F2, 0x0, 0x80080000}};
    int check = -99999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok310) {
    // 999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x90000}};
    int check = 999999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok311) {
    // -999999999.999999999
    s21_decimal decimal = {{0xA763FFFF, 0xDE0B6B3, 0x0, 0x80090000}};
    int check = -999999999;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok312) {
    // 9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x0}};
    int check = 9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok313) {
    // -9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80000000}};
    int check = -9;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok314) {
    // 0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x10000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok315) {
    // -0.9
    s21_decimal decimal = {{0x9, 0x0, 0x0, 0x80010000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok316) {
    // 0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x20000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok317) {
    // -0.99
    s21_decimal decimal = {{0x63, 0x0, 0x0, 0x80020000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok318) {
    // 0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x30000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok319) {
    // -0.999
    s21_decimal decimal = {{0x3E7, 0x0, 0x0, 0x80030000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok320) {
    // 0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x40000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok321) {
    // -0.9999
    s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80040000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok322) {
    // 0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x50000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok323) {
    // -0.99999
    s21_decimal decimal = {{0x1869F, 0x0, 0x0, 0x80050000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok324) {
    // 0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x60000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok325) {
    // -0.999999
    s21_decimal decimal = {{0xF423F, 0x0, 0x0, 0x80060000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok326) {
    // 0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x70000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok327) {
    // -0.9999999
    s21_decimal decimal = {{0x98967F, 0x0, 0x0, 0x80070000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok328) {
    // 0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok329) {
    // -0.99999999
    s21_decimal decimal = {{0x5F5E0FF, 0x0, 0x0, 0x80080000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok330) {
    // 0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x90000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok331) {
    // -0.999999999
    s21_decimal decimal = {{0x3B9AC9FF, 0x0, 0x0, 0x80090000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok332) {
    // 0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok333) {
    // -0.9999999999
    s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok334) {
    // 0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok335) {
    // -0.99999999999999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok336) {
    // -0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok337) {
    // 0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok338) {
    // -0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok339) {
    // 0.0
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok340) {
    // -0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80020000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok341) {
    // 0.00
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x20000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok342) {
    // -0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x800E0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok343) {
    // 0.00000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0xE0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok344) {
    // -0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801B0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok345) {
    // 0.000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1B0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok346) {
    // -0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x801C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok347) {
    // 0.0000000000000000000000000000
    s21_decimal decimal = {{0x0, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok348) {
    // 2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x0}};
    int check = 2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok349) {
    // -2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80000000}};
    int check = -2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok350) {
    // 2147483646.00
    s21_decimal decimal = {{0xFFFFFF38, 0x31, 0x0, 0x20000}};
    int check = 2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok351) {
    // -2147483646.00
    s21_decimal decimal = {{0xFFFFFF38, 0x31, 0x0, 0x80020000}};
    int check = -2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok352) {
    // 2147483646.99
    s21_decimal decimal = {{0xFFFFFF9B, 0x31, 0x0, 0x20000}};
    int check = 2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok353) {
    // -2147483646.99
    s21_decimal decimal = {{0xFFFFFF9B, 0x31, 0x0, 0x80020000}};
    int check = -2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok354) {
    // 2147483646.999999999999999999
    s21_decimal decimal = {{0x589BFFFF, 0xC5D1494C, 0x6F05B59, 0x120000}};
    int check = 2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok355) {
    // -2147483646.999999999999999999
    s21_decimal decimal = {{0x589BFFFF, 0xC5D1494C, 0x6F05B59, 0x80120000}};
    int check = -2147483646;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok356) {
    // 21474836.46
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x20000}};
    int check = 21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok357) {
    // -21474836.46
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80020000}};
    int check = -21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok358) {
    // 214.7483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x70000}};
    int check = 214;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok359) {
    // -214.7483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80070000}};
    int check = -214;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok360) {
    // 2.147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x90000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok361) {
    // -2.147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x80090000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok362) {
    // 0.2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0xA0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok363) {
    // -0.2147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x800A0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok364) {
    // 0.0000000000000000002147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok365) {
    // -0.0000000000000000002147483646
    s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x801C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok366) {
    // 2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
    int check = 2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok367) {
    // -2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};
    int check = -2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok368) {
    // 2147483647.00
    s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x20000}};
    int check = 2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok369) {
    // -2147483647.00
    s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x80020000}};
    int check = -2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok370) {
    // 2147483647.99
    s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x20000}};
    int check = 2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok371) {
    // -2147483647.99
    s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x80020000}};
    int check = -2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok372) {
    // 2147483647.999999999999999999
    s21_decimal decimal = {{0xFFFFFFFF, 0xD3B1FFFF, 0x6F05B59, 0x120000}};
    int check = 2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok373) {
    // -2147483647.999999999999999999
    s21_decimal decimal = {{0xFFFFFFFF, 0xD3B1FFFF, 0x6F05B59, 0x80120000}};
    int check = -2147483647;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok374) {
    // 21474836.47
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x20000}};
    int check = 21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok375) {
    // -21474836.47
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80020000}};
    int check = -21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok376) {
    // 214.7483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x70000}};
    int check = 214;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok377) {
    // -214.7483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80070000}};
    int check = -214;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok378) {
    // 2.147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x90000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok379) {
    // -2.147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80090000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok380) {
    // 0.2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0xA0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok381) {
    // -0.2147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x800A0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok382) {
    // 0.0000000000000000002147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok383) {
    // -0.0000000000000000002147483647
    s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x801C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok384) {
    // -2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
    int check = -2147483648;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok385) {
    // -2147483648.00
    s21_decimal decimal = {{0x0, 0x32, 0x0, 0x80020000}};
    int check = -2147483648;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok386) {
    // -2147483648.99
    s21_decimal decimal = {{0x63, 0x32, 0x0, 0x80020000}};
    int check = -2147483648;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok387) {
    // -2147483648.999999999999999999
    s21_decimal decimal = {{0xA763FFFF, 0xE192B6B3, 0x6F05B59, 0x80120000}};
    int check = -2147483648;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok388) {
    // 21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
    int check = 21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok389) {
    // -21474836.48
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
    int check = -21474836;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok390) {
    // 214.7483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x70000}};
    int check = 214;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok391) {
    // -214.7483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80070000}};
    int check = -214;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok392) {
    // 2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
    int check = 2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok393) {
    // -2.147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
    int check = -2;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok394) {
    // 0.2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0xA0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok395) {
    // -0.2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x800A0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok396) {
    // 0.0000000000000000002147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok397) {
    // -0.0000000000000000002147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x801C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok398) {
    // -202378.6784
    s21_decimal decimal = {{0x78A08920, 0x0, 0x0, 0x80040000}};
    int check = -202378;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok399) {
    // 202378.6784
    s21_decimal decimal = {{0x78A08920, 0x0, 0x0, 0x40000}};
    int check = 202378;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok400) {
    // 1157199323
    s21_decimal decimal = {{0x44F975DB, 0x0, 0x0, 0x0}};
    int check = 1157199323;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok401) {
    // -1157199323
    s21_decimal decimal = {{0x44F975DB, 0x0, 0x0, 0x80000000}};
    int check = -1157199323;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok402) {
    // -1047971123
    s21_decimal decimal = {{0x3E76C533, 0x0, 0x0, 0x80000000}};
    int check = -1047971123;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok403) {
    // 1047971123
    s21_decimal decimal = {{0x3E76C533, 0x0, 0x0, 0x0}};
    int check = 1047971123;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok404) {
    // 1635973982
    s21_decimal decimal = {{0x6182FB5E, 0x0, 0x0, 0x0}};
    int check = 1635973982;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok405) {
    // -1635973982
    s21_decimal decimal = {{0x6182FB5E, 0x0, 0x0, 0x80000000}};
    int check = -1635973982;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok406) {
    // 1664922502
    s21_decimal decimal = {{0x633CB386, 0x0, 0x0, 0x0}};
    int check = 1664922502;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok407) {
    // -1664922502
    s21_decimal decimal = {{0x633CB386, 0x0, 0x0, 0x80000000}};
    int check = -1664922502;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok408) {
    // -1562427032
    s21_decimal decimal = {{0x5D20BE98, 0x0, 0x0, 0x80000000}};
    int check = -1562427032;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok409) {
    // 1562427032
    s21_decimal decimal = {{0x5D20BE98, 0x0, 0x0, 0x0}};
    int check = 1562427032;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok410) {
    // 18415446
    s21_decimal decimal = {{0x118FF56, 0x0, 0x0, 0x0}};
    int check = 18415446;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok411) {
    // -18415446
    s21_decimal decimal = {{0x118FF56, 0x0, 0x0, 0x80000000}};
    int check = -18415446;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok412) {
    // 2043799125
    s21_decimal decimal = {{0x79D1E655, 0x0, 0x0, 0x0}};
    int check = 2043799125;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok413) {
    // -2043799125
    s21_decimal decimal = {{0x79D1E655, 0x0, 0x0, 0x80000000}};
    int check = -2043799125;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok414) {
    // -699081605
    s21_decimal decimal = {{0x29AB2385, 0x0, 0x0, 0x80000000}};
    int check = -699081605;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok415) {
    // 699081605
    s21_decimal decimal = {{0x29AB2385, 0x0, 0x0, 0x0}};
    int check = 699081605;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok416) {
    // 7206047.80
    s21_decimal decimal = {{0x2AF38E6C, 0x0, 0x0, 0x20000}};
    int check = 7206047;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok417) {
    // -7206047.80
    s21_decimal decimal = {{0x2AF38E6C, 0x0, 0x0, 0x80020000}};
    int check = -7206047;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok418) {
    // -405011.4826
    s21_decimal decimal = {{0xF167D90A, 0x0, 0x0, 0x80040000}};
    int check = -405011;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok419) {
    // 405011.4826
    s21_decimal decimal = {{0xF167D90A, 0x0, 0x0, 0x40000}};
    int check = 405011;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok420) {
    // 0.0000000002899686912
    s21_decimal decimal = {{0xACD5B600, 0x0, 0x0, 0x130000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok421) {
    // -0.0000000002899686912
    s21_decimal decimal = {{0xACD5B600, 0x0, 0x0, 0x80130000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok422) {
    // -806251761
    s21_decimal decimal = {{0x300E6CF1, 0x0, 0x0, 0x80000000}};
    int check = -806251761;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok423) {
    // 806251761
    s21_decimal decimal = {{0x300E6CF1, 0x0, 0x0, 0x0}};
    int check = 806251761;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok424) {
    // -961415253
    s21_decimal decimal = {{0x394E0855, 0x0, 0x0, 0x80000000}};
    int check = -961415253;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok425) {
    // 961415253
    s21_decimal decimal = {{0x394E0855, 0x0, 0x0, 0x0}};
    int check = 961415253;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok426) {
    // 1362812644
    s21_decimal decimal = {{0x513ADEE4, 0x0, 0x0, 0x0}};
    int check = 1362812644;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok427) {
    // -1362812644
    s21_decimal decimal = {{0x513ADEE4, 0x0, 0x0, 0x80000000}};
    int check = -1362812644;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok428) {
    // 744018023
    s21_decimal decimal = {{0x2C58D067, 0x0, 0x0, 0x0}};
    int check = 744018023;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok429) {
    // -744018023
    s21_decimal decimal = {{0x2C58D067, 0x0, 0x0, 0x80000000}};
    int check = -744018023;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok430) {
    // -669134488
    s21_decimal decimal = {{0x27E22E98, 0x0, 0x0, 0x80000000}};
    int check = -669134488;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok431) {
    // 669134488
    s21_decimal decimal = {{0x27E22E98, 0x0, 0x0, 0x0}};
    int check = 669134488;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok432) {
    // 1135755779
    s21_decimal decimal = {{0x43B24203, 0x0, 0x0, 0x0}};
    int check = 1135755779;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok433) {
    // -1135755779
    s21_decimal decimal = {{0x43B24203, 0x0, 0x0, 0x80000000}};
    int check = -1135755779;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok434) {
    // -1066687460
    s21_decimal decimal = {{0x3F945BE4, 0x0, 0x0, 0x80000000}};
    int check = -1066687460;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok435) {
    // 1066687460
    s21_decimal decimal = {{0x3F945BE4, 0x0, 0x0, 0x0}};
    int check = 1066687460;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok436) {
    // 1775.200759
    s21_decimal decimal = {{0x69CF69F7, 0x0, 0x0, 0x60000}};
    int check = 1775;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok437) {
    // -1775.200759
    s21_decimal decimal = {{0x69CF69F7, 0x0, 0x0, 0x80060000}};
    int check = -1775;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok438) {
    // 2049377039
    s21_decimal decimal = {{0x7A27030F, 0x0, 0x0, 0x0}};
    int check = 2049377039;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok439) {
    // -2049377039
    s21_decimal decimal = {{0x7A27030F, 0x0, 0x0, 0x80000000}};
    int check = -2049377039;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok440) {
    // 644156872
    s21_decimal decimal = {{0x26650DC8, 0x0, 0x0, 0x0}};
    int check = 644156872;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok441) {
    // -644156872
    s21_decimal decimal = {{0x26650DC8, 0x0, 0x0, 0x80000000}};
    int check = -644156872;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok442) {
    // 411899256
    s21_decimal decimal = {{0x188D1578, 0x0, 0x0, 0x0}};
    int check = 411899256;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok443) {
    // -411899256
    s21_decimal decimal = {{0x188D1578, 0x0, 0x0, 0x80000000}};
    int check = -411899256;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok444) {
    // -0.0000000000000000321044217
    s21_decimal decimal = {{0x1322BEF9, 0x0, 0x0, 0x80190000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok445) {
    // 0.0000000000000000321044217
    s21_decimal decimal = {{0x1322BEF9, 0x0, 0x0, 0x190000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok446) {
    // 0.000000000000000003809359548
    s21_decimal decimal = {{0xE30E36BC, 0x0, 0x0, 0x1B0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok447) {
    // -0.000000000000000003809359548
    s21_decimal decimal = {{0xE30E36BC, 0x0, 0x0, 0x801B0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok448) {
    // -0.000000000002807144663
    s21_decimal decimal = {{0xA751A0D7, 0x0, 0x0, 0x80150000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok449) {
    // 0.000000000002807144663
    s21_decimal decimal = {{0xA751A0D7, 0x0, 0x0, 0x150000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok450) {
    // 1802612012
    s21_decimal decimal = {{0x6B71AD2C, 0x0, 0x0, 0x0}};
    int check = 1802612012;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok451) {
    // -1802612012
    s21_decimal decimal = {{0x6B71AD2C, 0x0, 0x0, 0x80000000}};
    int check = -1802612012;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok452) {
    // 1498496264
    s21_decimal decimal = {{0x59513D08, 0x0, 0x0, 0x0}};
    int check = 1498496264;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok453) {
    // -1498496264
    s21_decimal decimal = {{0x59513D08, 0x0, 0x0, 0x80000000}};
    int check = -1498496264;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok454) {
    // 0.000000001060195434
    s21_decimal decimal = {{0x3F314C6A, 0x0, 0x0, 0x120000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok455) {
    // -0.000000001060195434
    s21_decimal decimal = {{0x3F314C6A, 0x0, 0x0, 0x80120000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok456) {
    // -346.3980837
    s21_decimal decimal = {{0xCE782725, 0x0, 0x0, 0x80070000}};
    int check = -346;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok457) {
    // 346.3980837
    s21_decimal decimal = {{0xCE782725, 0x0, 0x0, 0x70000}};
    int check = 346;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok458) {
    // -0.0000000000000000000791281307
    s21_decimal decimal = {{0x2F29FE9B, 0x0, 0x0, 0x801C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok459) {
    // 0.0000000000000000000791281307
    s21_decimal decimal = {{0x2F29FE9B, 0x0, 0x0, 0x1C0000}};
    int check = 0;

    test_from_decimal_to_int(decimal, check);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Tests for incorrect data (auto)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_decimal_to_int_fail1) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail2) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail3) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail4) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail5) {
    // 792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail6) {
    // -792281625142643375935439503.35
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail7) {
    // 79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail8) {
    // -79228162514264337593543950.335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail9) {
    // 7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail10) {
    // -7922816251426433759354395.0335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail11) {
    // 792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail12) {
    // -792281625142643375935439.50335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail13) {
    // 79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail14) {
    // -79228162514264337593543.950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail15) {
    // 7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail16) {
    // -7922816251426433759354.3950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail17) {
    // 792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail18) {
    // -792281625142643375935.43950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail19) {
    // 79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail20) {
    // -79228162514264337593.543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail21) {
    // 7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail22) {
    // -7922816251426433759.3543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail23) {
    // 792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail24) {
    // -792281625142643375.93543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail25) {
    // 79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail26) {
    // -79228162514264337.593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail27) {
    // 7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail28) {
    // -7922816251426433.7593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail29) {
    // 792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail30) {
    // -792281625142643.37593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail31) {
    // 79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail32) {
    // -79228162514264.337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail33) {
    // 7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail34) {
    // -7922816251426.4337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail35) {
    // 792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail36) {
    // -792281625142.64337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail37) {
    // 79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail38) {
    // -79228162514.264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail39) {
    // 7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail40) {
    // -7922816251.4264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail41) {
    // 79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail42) {
    // -79228162514264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail43) {
    // 7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail44) {
    // -7922816251426433759354395033.4
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail45) {
    // 792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail46) {
    // -792281625142643375935439503.34
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail47) {
    // 79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail48) {
    // -79228162514264337593543950.334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail49) {
    // 7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail50) {
    // -7922816251426433759354395.0334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail51) {
    // 792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail52) {
    // -792281625142643375935439.50334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail53) {
    // 79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail54) {
    // -79228162514264337593543.950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail55) {
    // 7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail56) {
    // -7922816251426433759354.3950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail57) {
    // 792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail58) {
    // -792281625142643375935.43950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail59) {
    // 79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail60) {
    // -79228162514264337593.543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail61) {
    // 7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail62) {
    // -7922816251426433759.3543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail63) {
    // 792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail64) {
    // -792281625142643375.93543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail65) {
    // 79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail66) {
    // -79228162514264337.593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail67) {
    // 7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail68) {
    // -7922816251426433.7593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail69) {
    // 792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail70) {
    // -792281625142643.37593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail71) {
    // 79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail72) {
    // -79228162514264.337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail73) {
    // 7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail74) {
    // -7922816251426.4337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail75) {
    // 792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail76) {
    // -792281625142.64337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail77) {
    // 79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail78) {
    // -79228162514.264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail79) {
    // 7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail80) {
    // -7922816251.4264337593543950334
    s21_decimal decimal = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail81) {
    // 52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail82) {
    // -52818775009509558395695966890
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail83) {
    // 5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail84) {
    // -5281877500950955839569596689.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail85) {
    // 52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail86) {
    // -52818775009509558392832655360
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail87) {
    // 5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail88) {
    // -5281877500950955839283265536.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail89) {
    // 52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail90) {
    // -52818774997211729016086244010
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail91) {
    // 5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail92) {
    // -5281877499721172901608624401.0
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0xAAAAAAAA, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail93) {
    // 52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail94) {
    // -52818774997211729013222932480
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail95) {
    // 5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail96) {
    // -5281877499721172901322293248.0
    s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail97) {
    // 12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail98) {
    // -12297829382473034410
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail99) {
    // 1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail100) {
    // -1229782938247303441.0
    s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail101) {
    // 12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail102) {
    // -12297829379609722880
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail103) {
    // 1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail104) {
    // -1229782937960972288.0
    s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail105) {
    // 2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail106) {
    // -2863311530
    s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail107) {
    // 26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail108) {
    // -26409387504754779197847983445
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail109) {
    // 2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail110) {
    // -2640938750475477919784798344.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail111) {
    // 26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail112) {
    // -26409387504754779196416327680
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail113) {
    // 2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail114) {
    // -2640938750475477919641632768.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail115) {
    // 26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail116) {
    // -26409387498605864508043122005
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail117) {
    // 2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail118) {
    // -2640938749860586450804312200.5
    s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail119) {
    // 26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail120) {
    // -26409387498605864506611466240
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail121) {
    // 2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail122) {
    // -2640938749860586450661146624.0
    s21_decimal decimal = {{0x0, 0x0, 0x55555555, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail123) {
    // 6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail124) {
    // -6148914691236517205
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail125) {
    // 614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail126) {
    // -614891469123651720.5
    s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail127) {
    // 6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail128) {
    // -6148914689804861440
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail129) {
    // 614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail130) {
    // -614891468980486144.0
    s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail131) {
    // 18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail132) {
    // -18446744078004518913
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail133) {
    // 1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail134) {
    // -1844674407800451891.3
    s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail135) {
    // 18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail136) {
    // -18446744078004518912
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail137) {
    // 1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail138) {
    // -1844674407800451891.2
    s21_decimal decimal = {{0x0, 0x1, 0x1, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail139) {
    // 18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail140) {
    // -18446744073709551617
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail141) {
    // 1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail142) {
    // -1844674407370955161.7
    s21_decimal decimal = {{0x1, 0x0, 0x1, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail143) {
    // 18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail144) {
    // -18446744073709551616
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail145) {
    // 1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail146) {
    // -1844674407370955161.6
    s21_decimal decimal = {{0x0, 0x0, 0x1, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail147) {
    // 4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail148) {
    // -4294967297
    s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail149) {
    // 4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail150) {
    // -4294967296
    s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail151) {
    // 39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail152) {
    // -39614081266355540835774234624
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail153) {
    // 3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail154) {
    // -3961408126635554083577423462.4
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail155) {
    // 39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail156) {
    // -39614081266355540833626750976
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail157) {
    // 3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail158) {
    // -3961408126635554083362675097.6
    s21_decimal decimal = {{0x0, 0x80000000, 0x80000000, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail159) {
    // 39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail160) {
    // -39614081257132168798919458816
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail161) {
    // 3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail162) {
    // -3961408125713216879891945881.6
    s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail163) {
    // 39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail164) {
    // -39614081257132168796771975168
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail165) {
    // 3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail166) {
    // -3961408125713216879677197516.8
    s21_decimal decimal = {{0x0, 0x0, 0x80000000, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail167) {
    // 9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail168) {
    // -9223372039002259456
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail169) {
    // 922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail170) {
    // -922337203900225945.6
    s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail171) {
    // 9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail172) {
    // -9223372036854775808
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail173) {
    // 922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail174) {
    // -922337203685477580.8
    s21_decimal decimal = {{0x0, 0x80000000, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail175) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail176) {
    // 156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail177) {
    // -156064767562212695305426944
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail178) {
    // 15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail179) {
    // -15606476756221269530542694.4
    s21_decimal decimal = {{0x811800, 0x811800, 0x811800, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail180) {
    // 156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail181) {
    // -156064767562212695296966656
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail182) {
    // 15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail183) {
    // -15606476756221269529696665.6
    s21_decimal decimal = {{0x0, 0x811800, 0x811800, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail184) {
    // 156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail185) {
    // -156064767525876035030685696
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail186) {
    // 15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail187) {
    // -15606476752587603503068569.6
    s21_decimal decimal = {{0x811800, 0x0, 0x811800, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail188) {
    // 156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail189) {
    // -156064767525876035022225408
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail190) {
    // 15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail191) {
    // -15606476752587603502222540.8
    s21_decimal decimal = {{0x0, 0x0, 0x811800, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail192) {
    // 36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail193) {
    // -36336660283201536
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail194) {
    // 3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail195) {
    // -3633666028320153.6
    s21_decimal decimal = {{0x811800, 0x811800, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail196) {
    // 36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail197) {
    // -36336660274741248
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail198) {
    // 3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail199) {
    // -3633666027474124.8
    s21_decimal decimal = {{0x0, 0x811800, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail200) {
    // 79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail201) {
    // -79228162514264337593543950335
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail202) {
    // 7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail203) {
    // -7922816251426433759354395033.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail204) {
    // 79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail205) {
    // -79228162514264337589248983040
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail206) {
    // 7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail207) {
    // -7922816251426433758924898304.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail208) {
    // 79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail209) {
    // -79228162495817593524129366015
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail210) {
    // 7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail211) {
    // -7922816249581759352412936601.5
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail212) {
    // 79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail213) {
    // -79228162495817593519834398720
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail214) {
    // 7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail215) {
    // -7922816249581759351983439872.0
    s21_decimal decimal = {{0x0, 0x0, 0xFFFFFFFF, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail216) {
    // 18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail217) {
    // -18446744073709551615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail218) {
    // 1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail219) {
    // -1844674407370955161.5
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail220) {
    // 18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x30000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail221) {
    // -18446744073709551.615
    s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x80030000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail222) {
    // 18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail223) {
    // -18446744069414584320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail224) {
    // 1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail225) {
    // -1844674406941458432.0
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail226) {
    // 18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x30000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail227) {
    // -18446744069414584.320
    s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80030000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail228) {
    // 4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail229) {
    // -4294967295
    s21_decimal decimal = {{0xFFFFFFFF, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail230) {
    // 12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail231) {
    // -12345678901234.12345678901234
    s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail232) {
    // 9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail233) {
    // -9999999999.9999999999
    s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail234) {
    // 2147483648
    s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail235) {
    // 2147483648.00
    s21_decimal decimal = {{0x0, 0x32, 0x0, 0x20000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail236) {
    // 2147483648.99
    s21_decimal decimal = {{0x63, 0x32, 0x0, 0x20000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail237) {
    // 2147483648.999999999999999999
    s21_decimal decimal = {{0xA763FFFF, 0xE192B6B3, 0x6F05B59, 0x120000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail238) {
    // 3436350754
    s21_decimal decimal = {{0xCCD28D22, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail239) {
    // -3436350754
    s21_decimal decimal = {{0xCCD28D22, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail240) {
    // -2467171175
    s21_decimal decimal = {{0x930E0B67, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail241) {
    // 2467171175
    s21_decimal decimal = {{0x930E0B67, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail242) {
    // -2296067528
    s21_decimal decimal = {{0x88DB35C8, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail243) {
    // 2296067528
    s21_decimal decimal = {{0x88DB35C8, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail244) {
    // 3848964437
    s21_decimal decimal = {{0xE56A8955, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail245) {
    // -3848964437
    s21_decimal decimal = {{0xE56A8955, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail246) {
    // -3182863462
    s21_decimal decimal = {{0xBDB6A466, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail247) {
    // 3182863462
    s21_decimal decimal = {{0xBDB6A466, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail248) {
    // -48847109575696535634899575831
    s21_decimal decimal = {{0x26532417, 0x149403E0, 0x9DD561CC, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail249) {
    // 48847109575696535634899575831
    s21_decimal decimal = {{0x26532417, 0x149403E0, 0x9DD561CC, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail250) {
    // -3318846837
    s21_decimal decimal = {{0xC5D19575, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail251) {
    // 3318846837
    s21_decimal decimal = {{0xC5D19575, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail252) {
    // -2313332038
    s21_decimal decimal = {{0x89E2A546, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail253) {
    // 2313332038
    s21_decimal decimal = {{0x89E2A546, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail254) {
    // 3374693184
    s21_decimal decimal = {{0xC925BB40, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail255) {
    // -3374693184
    s21_decimal decimal = {{0xC925BB40, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail256) {
    // 4020511056
    s21_decimal decimal = {{0xEFA42150, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail257) {
    // -4020511056
    s21_decimal decimal = {{0xEFA42150, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail258) {
    // 3004972040
    s21_decimal decimal = {{0xB31C3C08, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail259) {
    // -3004972040
    s21_decimal decimal = {{0xB31C3C08, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail260) {
    // -2859313295
    s21_decimal decimal = {{0xAA6DA88F, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail261) {
    // 2859313295
    s21_decimal decimal = {{0xAA6DA88F, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail262) {
    // 3559609781
    s21_decimal decimal = {{0xD42B55B5, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail263) {
    // -3559609781
    s21_decimal decimal = {{0xD42B55B5, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail264) {
    // -2633735568
    s21_decimal decimal = {{0x9CFB9D90, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail265) {
    // 2633735568
    s21_decimal decimal = {{0x9CFB9D90, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail266) {
    // 3849297796
    s21_decimal decimal = {{0xE56F9F84, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail267) {
    // -3849297796
    s21_decimal decimal = {{0xE56F9F84, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail268) {
    // -66249387729842137051875589617
    s21_decimal decimal = {{0x75E13DF1, 0x206039BC, 0xD6103589, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail269) {
    // 66249387729842137051875589617
    s21_decimal decimal = {{0x75E13DF1, 0x206039BC, 0xD6103589, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail270) {
    // 4000259692
    s21_decimal decimal = {{0xEE6F1E6C, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail271) {
    // -4000259692
    s21_decimal decimal = {{0xEE6F1E6C, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail272) {
    // 299970448737931080006163233.37
    s21_decimal decimal = {{0xA9C59909, 0x3FD3888, 0x60ECF955, 0x20000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail273) {
    // -299970448737931080006163233.37
    s21_decimal decimal = {{0xA9C59909, 0x3FD3888, 0x60ECF955, 0x80020000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail274) {
    // -3238025630
    s21_decimal decimal = {{0xC100599E, 0x0, 0x0, 0x80000000}};

    test_from_decimal_to_int_fail(decimal);
}

START_TEST(test_from_decimal_to_int_fail275) {
    // 3238025630
    s21_decimal decimal = {{0xC100599E, 0x0, 0x0, 0x0}};

    test_from_decimal_to_int_fail(decimal);
}

Suite *from_decimal_to_int_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_decimal_to_int1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_decimal_to_int_ok1);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok2);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok3);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok4);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok5);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok6);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok7);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok8);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok9);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok10);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok11);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok12);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok13);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok14);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok15);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok16);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok17);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok18);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok19);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok20);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok21);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok22);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok23);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok24);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok25);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok26);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok27);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok28);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok29);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok30);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok31);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok32);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok33);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok34);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok35);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok36);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok37);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok38);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok39);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok40);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok41);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok42);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok43);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok44);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok45);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok46);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok47);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok48);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok49);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok50);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok51);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok52);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok53);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok54);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok55);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok56);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok57);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok58);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok59);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok60);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok61);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok62);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok63);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok64);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok65);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok66);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok67);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok68);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok69);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok70);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok71);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok72);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok73);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok74);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok75);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok76);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok77);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok78);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok79);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok80);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok81);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok82);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok83);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok84);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok85);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok86);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok87);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok88);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok89);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok90);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok91);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok92);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok93);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok94);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok95);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok96);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok97);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok98);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok99);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok100);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok101);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok102);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok103);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok104);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok105);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok106);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok107);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok108);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok109);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok110);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok111);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok112);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok113);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok114);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok115);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok116);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok117);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok118);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok119);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok120);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok121);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok122);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok123);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok124);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok125);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok126);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok127);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok128);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok129);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok130);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok131);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok132);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok133);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok134);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok135);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok136);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok137);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok138);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok139);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok140);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok141);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok142);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok143);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok144);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok145);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok146);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok147);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok148);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok149);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok150);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok151);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok152);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok153);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok154);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok155);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok156);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok157);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok158);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok159);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok160);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok161);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok162);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok163);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok164);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok165);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok166);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok167);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok168);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok169);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok170);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok171);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok172);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok173);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok174);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok175);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok176);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok177);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok178);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok179);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok180);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok181);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok182);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok183);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok184);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok185);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok186);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok187);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok188);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok189);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok190);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok191);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok192);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok193);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok194);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok195);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok196);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok197);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok198);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok199);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok200);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok201);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok202);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok203);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok204);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok205);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok206);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok207);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok208);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok209);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok210);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok211);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok212);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok213);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok214);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok215);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok216);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok217);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok218);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok219);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok220);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok221);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok222);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok223);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok224);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok225);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok226);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok227);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok228);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok229);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok230);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok231);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok232);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok233);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok234);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok235);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok236);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok237);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok238);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok239);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok240);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok241);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok242);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok243);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok244);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok245);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok246);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok247);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok248);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok249);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok250);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok251);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok252);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok253);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok254);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok255);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok256);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok257);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok258);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok259);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok260);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok261);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok262);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok263);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok264);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok265);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok266);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok267);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok268);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok269);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok270);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok271);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok272);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok273);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok274);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok275);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok276);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok277);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok278);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok279);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok280);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok281);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok282);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok283);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok284);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok285);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok286);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok287);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok288);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok289);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok290);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok291);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok292);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok293);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok294);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok295);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok296);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok297);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok298);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok299);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok300);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok301);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok302);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok303);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok304);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok305);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok306);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok307);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok308);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok309);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok310);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok311);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok312);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok313);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok314);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok315);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok316);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok317);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok318);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok319);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok320);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok321);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok322);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok323);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok324);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok325);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok326);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok327);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok328);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok329);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok330);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok331);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok332);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok333);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok334);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok335);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok336);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok337);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok338);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok339);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok340);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok341);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok342);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok343);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok344);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok345);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok346);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok347);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok348);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok349);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok350);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok351);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok352);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok353);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok354);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok355);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok356);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok357);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok358);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok359);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok360);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok361);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok362);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok363);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok364);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok365);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok366);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok367);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok368);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok369);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok370);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok371);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok372);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok373);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok374);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok375);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok376);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok377);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok378);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok379);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok380);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok381);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok382);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok383);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok384);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok385);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok386);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok387);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok388);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok389);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok390);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok391);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok392);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok393);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok394);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok395);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok396);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok397);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok398);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok399);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_decimal_to_int_suite2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_decimal_to_int2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_decimal_to_int_ok401);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok402);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok403);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok404);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok405);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok406);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok407);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok408);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok409);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok410);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok411);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok412);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok413);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok414);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok415);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok416);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok417);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok418);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok419);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok420);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok421);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok422);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok423);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok424);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok425);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok426);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok427);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok428);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok429);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok430);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok431);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok432);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok433);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok434);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok435);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok436);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok437);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok438);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok439);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok440);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok441);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok442);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok443);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok444);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok445);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok446);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok447);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok448);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok449);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok450);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok451);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok452);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok453);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok454);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok455);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok456);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok457);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok458);
    tcase_add_test(tc_core, test_from_decimal_to_int_ok459);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_decimal_to_int_suite3(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_decimal_to_int3");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_decimal_to_int_fail1);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail2);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail3);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail4);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail5);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail6);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail7);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail8);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail9);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail10);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail11);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail12);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail13);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail14);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail15);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail16);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail17);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail18);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail19);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail20);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail21);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail22);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail23);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail24);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail25);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail26);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail27);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail28);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail29);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail30);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail31);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail32);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail33);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail34);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail35);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail36);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail37);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail38);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail39);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail40);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail41);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail42);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail43);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail44);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail45);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail46);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail47);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail48);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail49);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail50);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail51);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail52);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail53);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail54);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail55);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail56);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail57);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail58);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail59);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail60);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail61);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail62);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail63);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail64);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail65);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail66);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail67);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail68);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail69);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail70);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail71);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail72);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail73);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail74);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail75);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail76);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail77);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail78);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail79);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail80);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail81);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail82);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail83);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail84);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail85);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail86);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail87);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail88);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail89);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail90);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail91);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail92);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail93);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail94);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail95);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail96);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail97);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail98);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail99);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail100);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail101);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail102);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail103);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail104);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail105);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail106);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail107);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail108);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail109);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail110);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail111);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail112);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail113);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail114);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail115);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail116);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail117);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail118);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail119);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail120);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail121);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail122);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail123);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail124);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail125);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail126);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail127);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail128);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail129);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail130);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail131);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail132);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail133);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail134);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail135);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail136);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail137);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail138);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail139);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail140);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail141);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail142);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail143);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail144);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail145);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail146);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail147);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail148);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail149);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail150);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail151);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail152);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail153);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail154);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail155);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail156);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail157);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail158);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail159);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail160);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail161);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail162);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail163);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail164);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail165);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail166);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail167);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail168);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail169);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail170);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail171);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail172);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail173);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail174);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail175);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail176);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail177);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail178);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail179);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail180);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail181);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail182);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail183);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail184);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail185);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail186);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail187);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail188);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail189);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail190);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail191);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail192);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail193);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail194);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail195);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail196);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail197);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail198);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail199);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail200);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail201);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail202);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail203);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail204);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail205);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail206);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail207);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail208);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail209);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail210);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail211);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail212);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail213);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail214);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail215);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail216);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail217);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail218);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail219);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail220);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail221);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail222);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail223);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail224);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail225);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail226);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail227);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail228);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail229);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail230);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail231);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail232);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail233);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail234);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail235);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail236);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail237);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail238);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail239);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail240);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail241);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail242);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail243);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail244);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail245);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail246);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail247);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail248);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail249);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail250);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail251);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail252);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail253);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail254);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail255);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail256);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail257);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail258);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail259);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail260);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail261);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail262);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail263);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail264);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail265);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail266);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail267);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail268);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail269);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail270);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail271);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail272);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail273);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail274);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail275);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_decimal_to_int_suite0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_decimal_to_int0");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual1);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual2);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual3);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual4);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual5);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual6);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual7);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual8);
    tcase_add_test(tc_core, test_from_decimal_to_int_fail_manual9);

    suite_add_tcase(s, tc_core);
    return s;
}

void test_from_decimal_to_int(s21_decimal decimal, int check) {
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(result, check);
    ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

void test_from_decimal_to_int_fail(s21_decimal decimal) {
    int result;
    int code = s21_from_decimal_to_int(decimal, &result);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
