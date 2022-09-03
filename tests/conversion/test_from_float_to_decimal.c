#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../../s21_decimal.h"
#include "./../test.h"
#include "./test_from_float_to_decimal.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на ненормальные float
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_float_to_decimal_unnormal1) {
    float f = 0.0;
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_OK);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal2) {
    float f = -0.0;
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

    int code = s21_from_float_to_decimal(f, &result);

    int sign_check = test_decimal_get_sign(check);
    int sign_result = test_decimal_get_sign(result);

    ck_assert_int_eq(code, TEST_CONVERSION_OK);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
    ck_assert_int_eq(sign_check, sign_result);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal3) {
    float f = INFINITY;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal4) {
    float f = -INFINITY;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal5) {
    float f = NAN;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal6) {
    float f = -NAN;
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Тесты на некорректные данные
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_float_to_decimal_incorrect1) {
    float f = 1.0f;
    int code = s21_from_float_to_decimal(f, NULL);

    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_big) {
    float f = fails_big[_i];
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_big_negate) {
    float f = -fails_big[_i];
    s21_decimal result;

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_small) {
    float f = fails_small[_i];
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_small_negate) {
    float f = -fails_small[_i];
    s21_decimal result;
    s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

    int code = s21_from_float_to_decimal(f, &result);
    ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
    ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Tests for correct data (automatic)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

START_TEST(test_from_float_to_decimal_ok1) {
    // 2.28401628E-19
    int f = 545706772;
    // 0.0000000000000000002284016
    s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2) {
    // -2.28401628E-19
    int f = -1601776876;
    // -0.0000000000000000002284016
    s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok3) {
    // 5.92141241E+23
    int f = 1727711253;
    // 592141200000000000000000
    s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok4) {
    // -5.92141241E+23
    int f = -419772395;
    // -592141200000000000000000
    s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok5) {
    // 2.1349025E-18
    int f = 572360491;
    // 0.000000000000000002134902
    s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok6) {
    // -2.1349025E-18
    int f = -1575123157;
    // -0.000000000000000002134902
    s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok7) {
    // 2.38582807E-08
    int f = 852291818;
    // 0.00000002385828
    s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok8) {
    // -2.38582807E-08
    int f = -1295191830;
    // -0.00000002385828
    s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok9) {
    // 7.91617864E+11
    int f = 1396199450;
    // 791617900000
    s21_decimal decimal_check = {{0x501A8DE0, 0xB8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok10) {
    // -7.91617864E+11
    int f = -751284198;
    // -791617900000
    s21_decimal decimal_check = {{0x501A8DE0, 0xB8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok11) {
    // 1.99102057E+21
    int f = 1658314220;
    // 1991021000000000000000
    s21_decimal decimal_check = {{0x5F048000, 0xEEF78A9E, 0x6B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok12) {
    // -1.99102057E+21
    int f = -489169428;
    // -1991021000000000000000
    s21_decimal decimal_check = {{0x5F048000, 0xEEF78A9E, 0x6B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok13) {
    // 9.29209423E+24
    int f = 1760949678;
    // 9292094000000000000000000
    s21_decimal decimal_check = {{0xE380000, 0x6CD28004, 0x7AFAD, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok14) {
    // -9.29209423E+24
    int f = -386533970;
    // -9292094000000000000000000
    s21_decimal decimal_check = {{0xE380000, 0x6CD28004, 0x7AFAD, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok15) {
    // 0.000115481133
    int f = 955395702;
    // 0.0001154811
    s21_decimal decimal_check = {{0x119EFB, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok16) {
    // -0.000115481133
    int f = -1192087946;
    // -0.0001154811
    s21_decimal decimal_check = {{0x119EFB, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok17) {
    // 8.66900895E-23
    int f = 449944209;
    // 0.0000000000000000000000866901
    s21_decimal decimal_check = {{0xD3A55, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok18) {
    // -8.66900895E-23
    int f = -1697539439;
    // -0.0000000000000000000000866901
    s21_decimal decimal_check = {{0xD3A55, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok19) {
    // 3.91406387E+11
    int f = 1387676487;
    // 391406400000
    s21_decimal decimal_check = {{0x21A3B200, 0x5B, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok20) {
    // -3.91406387E+11
    int f = -759807161;
    // -391406400000
    s21_decimal decimal_check = {{0x21A3B200, 0x5B, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok21) {
    // 1.54636995E-16
    int f = 624052425;
    // 0.000000000000000154637
    s21_decimal decimal_check = {{0x25C0D, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok22) {
    // -1.54636995E-16
    int f = -1523431223;
    // -0.000000000000000154637
    s21_decimal decimal_check = {{0x25C0D, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok23) {
    // 1.05583253E-13
    int f = 703447194;
    // 0.0000000000001055833
    s21_decimal decimal_check = {{0x101C59, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok24) {
    // -1.05583253E-13
    int f = -1444036454;
    // -0.0000000000001055833
    s21_decimal decimal_check = {{0x101C59, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok25) {
    // 4882.71582
    int f = 1167627706;
    // 4882.716
    s21_decimal decimal_check = {{0x4A811C, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok26) {
    // -4882.71582
    int f = -979855942;
    // -4882.716
    s21_decimal decimal_check = {{0x4A811C, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok27) {
    // 1.9929916E-26
    int f = 348479575;
    // 0.0000000000000000000000000199
    s21_decimal decimal_check = {{0xC7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok28) {
    // -1.9929916E-26
    int f = -1799004073;
    // -0.0000000000000000000000000199
    s21_decimal decimal_check = {{0xC7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok29) {
    // 3574.10864
    int f = 1163878845;
    // 3574.109
    s21_decimal decimal_check = {{0x36895D, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok30) {
    // -3574.10864
    int f = -983604803;
    // -3574.109
    s21_decimal decimal_check = {{0x36895D, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok31) {
    // 3.62930687E-13
    int f = 718032851;
    // 0.0000000000003629307
    s21_decimal decimal_check = {{0x3760FB, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok32) {
    // -3.62930687E-13
    int f = -1429450797;
    // -0.0000000000003629307
    s21_decimal decimal_check = {{0x3760FB, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok33) {
    // 2.1409382E-19
    int f = 545047011;
    // 0.0000000000000000002140938
    s21_decimal decimal_check = {{0x20AB0A, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok34) {
    // -2.1409382E-19
    int f = -1602436637;
    // -0.0000000000000000002140938
    s21_decimal decimal_check = {{0x20AB0A, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok35) {
    // 241.244507
    int f = 1131495064;
    // 241.2445
    s21_decimal decimal_check = {{0x24CF9D, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok36) {
    // -241.244507
    int f = -1015988584;
    // -241.2445
    s21_decimal decimal_check = {{0x24CF9D, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok37) {
    // 802580.063
    int f = 1229189441;
    // 802580.1
    s21_decimal decimal_check = {{0x7A76C9, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok38) {
    // -802580.063
    int f = -918294207;
    // -802580.1
    s21_decimal decimal_check = {{0x7A76C9, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok39) {
    // 8.38680669E+16
    int f = 1536490184;
    // 83868070000000000
    s21_decimal decimal_check = {{0xB858FC00, 0x129F590, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok40) {
    // -8.38680669E+16
    int f = -610993464;
    // -83868070000000000
    s21_decimal decimal_check = {{0xB858FC00, 0x129F590, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok41) {
    // 3.93541897E-17
    int f = 607485242;
    // 0.00000000000000003935419
    s21_decimal decimal_check = {{0x3C0CBB, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok42) {
    // -3.93541897E-17
    int f = -1539998406;
    // -0.00000000000000003935419
    s21_decimal decimal_check = {{0x3C0CBB, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok43) {
    // 1.45764168E-20
    int f = 512338845;
    // 0.00000000000000000001457642
    s21_decimal decimal_check = {{0x163DEA, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok44) {
    // -1.45764168E-20
    int f = -1635144803;
    // -0.00000000000000000001457642
    s21_decimal decimal_check = {{0x163DEA, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok45) {
    // 1.34647118E+20
    int f = 1625920341;
    // 134647100000000000000
    s21_decimal decimal_check = {{0x207FC000, 0x4C9A980F, 0x7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok46) {
    // -1.34647118E+20
    int f = -521563307;
    // -134647100000000000000
    s21_decimal decimal_check = {{0x207FC000, 0x4C9A980F, 0x7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok47) {
    // 2.20958198E-20
    int f = 516993130;
    // 0.00000000000000000002209582
    s21_decimal decimal_check = {{0x21B72E, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok48) {
    // -2.20958198E-20
    int f = -1630490518;
    // -0.00000000000000000002209582
    s21_decimal decimal_check = {{0x21B72E, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok49) {
    // 5.36623235E-09
    int f = 834167265;
    // 0.000000005366232
    s21_decimal decimal_check = {{0x51E1D8, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok50) {
    // -5.36623235E-09
    int f = -1313316383;
    // -0.000000005366232
    s21_decimal decimal_check = {{0x51E1D8, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok51) {
    // 4.71008997E+17
    int f = 1557212038;
    // 471009000000000000
    s21_decimal decimal_check = {{0xA3031000, 0x6895C30, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok52) {
    // -4.71008997E+17
    int f = -590271610;
    // -471009000000000000
    s21_decimal decimal_check = {{0xA3031000, 0x6895C30, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok53) {
    // 2.36363464E-11
    int f = 768600146;
    // 0.00000000002363635
    s21_decimal decimal_check = {{0x2410F3, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok54) {
    // -2.36363464E-11
    int f = -1378883502;
    // -0.00000000002363635
    s21_decimal decimal_check = {{0x2410F3, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok55) {
    // 0.0255207196
    int f = 1020334292;
    // 0.02552072
    s21_decimal decimal_check = {{0x26F108, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok56) {
    // -0.0255207196
    int f = -1127149356;
    // -0.02552072
    s21_decimal decimal_check = {{0x26F108, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok57) {
    // 3.9575282E-24
    int f = 412686710;
    // 0.0000000000000000000000039575
    s21_decimal decimal_check = {{0x9A97, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok58) {
    // -3.9575282E-24
    int f = -1734796938;
    // -0.0000000000000000000000039575
    s21_decimal decimal_check = {{0x9A97, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok59) {
    // 0.00399137754
    int f = 998427162;
    // 0.003991378
    s21_decimal decimal_check = {{0x3CE752, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok60) {
    // -0.00399137754
    int f = -1149056486;
    // -0.003991378
    s21_decimal decimal_check = {{0x3CE752, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok61) {
    // 1.95127377E-05
    int f = 933474121;
    // 0.00001951274
    s21_decimal decimal_check = {{0x1DC62A, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok62) {
    // -1.95127377E-05
    int f = -1214009527;
    // -0.00001951274
    s21_decimal decimal_check = {{0x1DC62A, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok63) {
    // 1.26745242E-20
    int f = 510618173;
    // 0.00000000000000000001267452
    s21_decimal decimal_check = {{0x1356FC, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok64) {
    // -1.26745242E-20
    int f = -1636865475;
    // -0.00000000000000000001267452
    s21_decimal decimal_check = {{0x1356FC, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok65) {
    // 0.0764362067
    int f = 1033669270;
    // 0.07643621
    s21_decimal decimal_check = {{0x74A1E5, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok66) {
    // -0.0764362067
    int f = -1113814378;
    // -0.07643621
    s21_decimal decimal_check = {{0x74A1E5, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok67) {
    // 1.19421885E-18
    int f = 565197904;
    // 0.000000000000000001194219
    s21_decimal decimal_check = {{0x1238EB, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok68) {
    // -1.19421885E-18
    int f = -1582285744;
    // -0.000000000000000001194219
    s21_decimal decimal_check = {{0x1238EB, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok69) {
    // 7.93902012E-16
    int f = 644141985;
    // 0.000000000000000793902
    s21_decimal decimal_check = {{0xC1D2E, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok70) {
    // -7.93902012E-16
    int f = -1503341663;
    // -0.000000000000000793902
    s21_decimal decimal_check = {{0xC1D2E, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok71) {
    // 5.86327048E-15
    int f = 668155680;
    // 0.00000000000000586327
    s21_decimal decimal_check = {{0x8F257, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok72) {
    // -5.86327048E-15
    int f = -1479327968;
    // -0.00000000000000586327
    s21_decimal decimal_check = {{0x8F257, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok73) {
    // 8.52215659E-11
    int f = 784033658;
    // 0.00000000008522157
    s21_decimal decimal_check = {{0x8209AD, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok74) {
    // -8.52215659E-11
    int f = -1363449990;
    // -0.00000000008522157
    s21_decimal decimal_check = {{0x8209AD, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok75) {
    // 9.61645806E-28
    int f = 311976189;
    // 0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok76) {
    // -9.61645806E-28
    int f = -1835507459;
    // -0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok77) {
    // 46282560
    int f = 1278250448;
    // 46282560
    s21_decimal decimal_check = {{0x2C23740, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok78) {
    // -46282560
    int f = -869233200;
    // -46282560
    s21_decimal decimal_check = {{0x2C23740, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok79) {
    // 1.15109615E-12
    int f = 732037276;
    // 0.000000000001151096
    s21_decimal decimal_check = {{0x119078, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok80) {
    // -1.15109615E-12
    int f = -1415446372;
    // -0.000000000001151096
    s21_decimal decimal_check = {{0x119078, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok81) {
    // 2.83794689E-11
    int f = 771334370;
    // 0.00000000002837947
    s21_decimal decimal_check = {{0x2B4DBB, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok82) {
    // -2.83794689E-11
    int f = -1376149278;
    // -0.00000000002837947
    s21_decimal decimal_check = {{0x2B4DBB, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok83) {
    // 8.43187742E-10
    int f = 812107280;
    // 0.0000000008431877
    s21_decimal decimal_check = {{0x80A905, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok84) {
    // -8.43187742E-10
    int f = -1335376368;
    // -0.0000000008431877
    s21_decimal decimal_check = {{0x80A905, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok85) {
    // 9.83161032E+17
    int f = 1566199356;
    // 983161000000000000
    s21_decimal decimal_check = {{0x72049000, 0xDA4E3B8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok86) {
    // -9.83161032E+17
    int f = -581284292;
    // -983161000000000000
    s21_decimal decimal_check = {{0x72049000, 0xDA4E3B8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok87) {
    // 5010.18115
    int f = 1167888755;
    // 5010.181
    s21_decimal decimal_check = {{0x4C7305, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok88) {
    // -5010.18115
    int f = -979594893;
    // -5010.181
    s21_decimal decimal_check = {{0x4C7305, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok89) {
    // 5.82704236E-25
    int f = 389306006;
    // 0.0000000000000000000000005827
    s21_decimal decimal_check = {{0x16C3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok90) {
    // -5.82704236E-25
    int f = -1758177642;
    // -0.0000000000000000000000005827
    s21_decimal decimal_check = {{0x16C3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok91) {
    // 5.07265574E+16
    int f = 1530148745;
    // 50726560000000000
    s21_decimal decimal_check = {{0x9D7A4000, 0xB43789, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok92) {
    // -5.07265574E+16
    int f = -617334903;
    // -50726560000000000
    s21_decimal decimal_check = {{0x9D7A4000, 0xB43789, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok93) {
    // 1.35639493E+19
    int f = 1597783252;
    // 13563950000000000000
    s21_decimal decimal_check = {{0xFD28E000, 0xBC3CD4A8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok94) {
    // -1.35639493E+19
    int f = -549700396;
    // -13563950000000000000
    s21_decimal decimal_check = {{0xFD28E000, 0xBC3CD4A8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok95) {
    // 1.2867606E+27
    int f = 1820658757;
    // 1286761000000000000000000000
    s21_decimal decimal_check = {{0x8FA00000, 0x955F02E9, 0x428623D, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok96) {
    // -1.2867606E+27
    int f = -326824891;
    // -1286761000000000000000000000
    s21_decimal decimal_check = {{0x8FA00000, 0x955F02E9, 0x428623D, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok97) {
    // 9.07980924E+20
    int f = 1648681745;
    // 907980900000000000000
    s21_decimal decimal_check = {{0x6B7A4000, 0x38C429DC, 0x31, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok98) {
    // -9.07980924E+20
    int f = -498801903;
    // -907980900000000000000
    s21_decimal decimal_check = {{0x6B7A4000, 0x38C429DC, 0x31, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok99) {
    // 15372566
    int f = 1265275158;
    // 15372570
    s21_decimal decimal_check = {{0xEA911A, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok100) {
    // -15372566
    int f = -882208490;
    // -15372570
    s21_decimal decimal_check = {{0xEA911A, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok101) {
    // 9.85001198E-23
    int f = 451815583;
    // 0.0000000000000000000000985001
    s21_decimal decimal_check = {{0xF07A9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok102) {
    // -9.85001198E-23
    int f = -1695668065;
    // -0.0000000000000000000000985001
    s21_decimal decimal_check = {{0xF07A9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok103) {
    // 4.58205132E-12
    int f = 748762995;
    // 0.000000000004582051
    s21_decimal decimal_check = {{0x45EAA3, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok104) {
    // -4.58205132E-12
    int f = -1398720653;
    // -0.000000000004582051
    s21_decimal decimal_check = {{0x45EAA3, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok105) {
    // 6.88863376E-12
    int f = 754081612;
    // 0.000000000006888634
    s21_decimal decimal_check = {{0x691CBA, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok106) {
    // -6.88863376E-12
    int f = -1393402036;
    // -0.000000000006888634
    s21_decimal decimal_check = {{0x691CBA, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok107) {
    // 1.94770514E+10
    int f = 1351687559;
    // 19477050000
    s21_decimal decimal_check = {{0x88EC3290, 0x4, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok108) {
    // -1.94770514E+10
    int f = -795796089;
    // -19477050000
    s21_decimal decimal_check = {{0x88EC3290, 0x4, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok109) {
    // 0.000745483907
    int f = 977497236;
    // 0.0007454839
    s21_decimal decimal_check = {{0x71C077, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok110) {
    // -0.000745483907
    int f = -1169986412;
    // -0.0007454839
    s21_decimal decimal_check = {{0x71C077, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok111) {
    // 7.85835969E+18
    int f = 1591352577;
    // 7858360000000000000
    s21_decimal decimal_check = {{0xDD238000, 0x6D0E80C8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok112) {
    // -7.85835969E+18
    int f = -556131071;
    // -7858360000000000000
    s21_decimal decimal_check = {{0xDD238000, 0x6D0E80C8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok113) {
    // 4.39337262E+21
    int f = 1668164171;
    // 4393373000000000000000
    s21_decimal decimal_check = {{0x883C8000, 0x2A4C5A69, 0xEE, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok114) {
    // -4.39337262E+21
    int f = -479319477;
    // -4393373000000000000000
    s21_decimal decimal_check = {{0x883C8000, 0x2A4C5A69, 0xEE, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok115) {
    // 4.8940947E+19
    int f = 1613352011;
    // 48940950000000000000
    s21_decimal decimal_check = {{0x88276000, 0xA7312EB9, 0x2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok116) {
    // -4.8940947E+19
    int f = -534131637;
    // -48940950000000000000
    s21_decimal decimal_check = {{0x88276000, 0xA7312EB9, 0x2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok117) {
    // 2.1753997E+18
    int f = 1576109204;
    // 2175400000000000000
    s21_decimal decimal_check = {{0x34628000, 0x1E3092C6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok118) {
    // -2.1753997E+18
    int f = -571374444;
    // -2175400000000000000
    s21_decimal decimal_check = {{0x34628000, 0x1E3092C6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok119) {
    // 8.42251829E+11
    int f = 1396972063;
    // 842251800000
    s21_decimal decimal_check = {{0x1A1E8DC0, 0xC4, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok120) {
    // -8.42251829E+11
    int f = -750511585;
    // -842251800000
    s21_decimal decimal_check = {{0x1A1E8DC0, 0xC4, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok121) {
    // 4.26393967E-07
    int f = 887417636;
    // 0.000000426394
    s21_decimal decimal_check = {{0x6819A, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok122) {
    // -4.26393967E-07
    int f = -1260066012;
    // -0.000000426394
    s21_decimal decimal_check = {{0x6819A, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok123) {
    // 1.84532337E-12
    int f = 738318948;
    // 0.000000000001845323
    s21_decimal decimal_check = {{0x1C284B, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok124) {
    // -1.84532337E-12
    int f = -1409164700;
    // -0.000000000001845323
    s21_decimal decimal_check = {{0x1C284B, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok125) {
    // 7.70974401E-20
    int f = 532023947;
    // 0.00000000000000000007709744
    s21_decimal decimal_check = {{0x75A430, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok126) {
    // -7.70974401E-20
    int f = -1615459701;
    // -0.00000000000000000007709744
    s21_decimal decimal_check = {{0x75A430, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok127) {
    // 0.0104842195
    int f = 1009501697;
    // 0.01048422
    s21_decimal decimal_check = {{0xFFF66, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok128) {
    // -0.0104842195
    int f = -1137981951;
    // -0.01048422
    s21_decimal decimal_check = {{0xFFF66, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok129) {
    // 1.98140566E-22
    int f = 460294537;
    // 0.0000000000000000000001981406
    s21_decimal decimal_check = {{0x1E3BDE, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok130) {
    // -1.98140566E-22
    int f = -1687189111;
    // -0.0000000000000000000001981406
    s21_decimal decimal_check = {{0x1E3BDE, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok131) {
    // 1.17932588E+22
    int f = 1679807510;
    // 11793260000000000000000
    s21_decimal decimal_check = {{0x6F3E0000, 0x505C1EA1, 0x27F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok132) {
    // -1.17932588E+22
    int f = -467676138;
    // -11793260000000000000000
    s21_decimal decimal_check = {{0x6F3E0000, 0x505C1EA1, 0x27F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok133) {
    // 356700.438
    int f = 1219373966;
    // 356700.4
    s21_decimal decimal_check = {{0x366D9C, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok134) {
    // -356700.438
    int f = -928109682;
    // -356700.4
    s21_decimal decimal_check = {{0x366D9C, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok135) {
    // 4.27844415E-17
    int f = 608521972;
    // 0.00000000000000004278444
    s21_decimal decimal_check = {{0x4148AC, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok136) {
    // -4.27844415E-17
    int f = -1538961676;
    // -0.00000000000000004278444
    s21_decimal decimal_check = {{0x4148AC, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok137) {
    // 12419649
    int f = 1262322241;
    // 12419650
    s21_decimal decimal_check = {{0xBD8242, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok138) {
    // -12419649
    int f = -885161407;
    // -12419650
    s21_decimal decimal_check = {{0xBD8242, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok139) {
    // 3.08497797E-21
    int f = 493426727;
    // 0.000000000000000000003084978
    s21_decimal decimal_check = {{0x2F12B2, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok140) {
    // -3.08497797E-21
    int f = -1654056921;
    // -0.000000000000000000003084978
    s21_decimal decimal_check = {{0x2F12B2, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok141) {
    // 4.18459603E+15
    int f = 1500372451;
    // 4184596000000000
    s21_decimal decimal_check = {{0x2E1BC800, 0xEDDDE, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok142) {
    // -4.18459603E+15
    int f = -647111197;
    // -4184596000000000
    s21_decimal decimal_check = {{0x2E1BC800, 0xEDDDE, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok143) {
    // 1.16865436E+26
    int f = 1791055472;
    // 116865400000000000000000000
    s21_decimal decimal_check = {{0xBAE00000, 0x7467DF7, 0x60AB36, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok144) {
    // -1.16865436E+26
    int f = -356428176;
    // -116865400000000000000000000
    s21_decimal decimal_check = {{0xBAE00000, 0x7467DF7, 0x60AB36, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok145) {
    // 2.70840103E+12
    int f = 1411229266;
    // 2708401000000
    s21_decimal decimal_check = {{0x99478E40, 0x276, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok146) {
    // -2.70840103E+12
    int f = -736254382;
    // -2708401000000
    s21_decimal decimal_check = {{0x99478E40, 0x276, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok147) {
    // 6.74712444E-21
    int f = 503244335;
    // 0.000000000000000000006747124
    s21_decimal decimal_check = {{0x66F3F4, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok148) {
    // -6.74712444E-21
    int f = -1644239313;
    // -0.000000000000000000006747124
    s21_decimal decimal_check = {{0x66F3F4, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok149) {
    // 5.64592297E-11
    int f = 779636593;
    // 0.00000000005645923
    s21_decimal decimal_check = {{0x562663, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok150) {
    // -5.64592297E-11
    int f = -1367847055;
    // -0.00000000005645923
    s21_decimal decimal_check = {{0x562663, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok151) {
    // 4.58151199E+10
    int f = 1361751220;
    // 45815120000
    s21_decimal decimal_check = {{0xAACB4080, 0xA, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok152) {
    // -4.58151199E+10
    int f = -785732428;
    // -45815120000
    s21_decimal decimal_check = {{0xAACB4080, 0xA, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok153) {
    // 1.48573706E-20
    int f = 512512747;
    // 0.00000000000000000001485737
    s21_decimal decimal_check = {{0x16ABA9, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok154) {
    // -1.48573706E-20
    int f = -1634970901;
    // -0.00000000000000000001485737
    s21_decimal decimal_check = {{0x16ABA9, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok155) {
    // 1.40592974E-22
    int f = 455735147;
    // 0.000000000000000000000140593
    s21_decimal decimal_check = {{0x22531, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok156) {
    // -1.40592974E-22
    int f = -1691748501;
    // -0.000000000000000000000140593
    s21_decimal decimal_check = {{0x22531, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok157) {
    // 1.83958331E+22
    int f = 1685671774;
    // 18395830000000000000000
    s21_decimal decimal_check = {{0x2A1F0000, 0x3D6CDFB7, 0x3E5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok158) {
    // -1.83958331E+22
    int f = -461811874;
    // -18395830000000000000000
    s21_decimal decimal_check = {{0x2A1F0000, 0x3D6CDFB7, 0x3E5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok159) {
    // 1.04831784E-07
    int f = 870391778;
    // 0.0000001048318
    s21_decimal decimal_check = {{0xFFEFE, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok160) {
    // -1.04831784E-07
    int f = -1277091870;
    // -0.0000001048318
    s21_decimal decimal_check = {{0xFFEFE, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok161) {
    // 3.40432057E+16
    int f = 1525802043;
    // 34043210000000000
    s21_decimal decimal_check = {{0x7F106400, 0x78F21E, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok162) {
    // -3.40432057E+16
    int f = -621681605;
    // -34043210000000000
    s21_decimal decimal_check = {{0x7F106400, 0x78F21E, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok163) {
    // 4.44212428E-21
    int f = 497537431;
    // 0.000000000000000000004442124
    s21_decimal decimal_check = {{0x43C80C, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok164) {
    // -4.44212428E-21
    int f = -1649946217;
    // -0.000000000000000000004442124
    s21_decimal decimal_check = {{0x43C80C, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok165) {
    // 2.77922045E-05
    int f = 938025806;
    // 0.0000277922
    s21_decimal decimal_check = {{0x43DA2, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok166) {
    // -2.77922045E-05
    int f = -1209457842;
    // -0.0000277922
    s21_decimal decimal_check = {{0x43DA2, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok167) {
    // 2.47787305E-13
    int f = 713784810;
    // 0.0000000000002477873
    s21_decimal decimal_check = {{0x25CF31, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok168) {
    // -2.47787305E-13
    int f = -1433698838;
    // -0.0000000000002477873
    s21_decimal decimal_check = {{0x25CF31, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok169) {
    // 8.1853854E-19
    int f = 561092358;
    // 0.0000000000000000008185385
    s21_decimal decimal_check = {{0x7CE629, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok170) {
    // -8.1853854E-19
    int f = -1586391290;
    // -0.0000000000000000008185385
    s21_decimal decimal_check = {{0x7CE629, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok171) {
    // 2.11021068E+24
    int f = 1742695776;
    // 2110211000000000000000000
    s21_decimal decimal_check = {{0xE22C0000, 0xC47CDAF3, 0x1BEDA, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok172) {
    // -2.11021068E+24
    int f = -404787872;
    // -2110211000000000000000000
    s21_decimal decimal_check = {{0xE22C0000, 0xC47CDAF3, 0x1BEDA, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok173) {
    // 1.82873229E+09
    int f = 1322909819;
    // 1828732000
    s21_decimal decimal_check = {{0x6D003C60, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok174) {
    // -1.82873229E+09
    int f = -824573829;
    // -1828732000
    s21_decimal decimal_check = {{0x6D003C60, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok175) {
    // 3807398.25
    int f = 1248354969;
    // 3807398
    s21_decimal decimal_check = {{0x3A18A6, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok176) {
    // -3807398.25
    int f = -899128679;
    // -3807398
    s21_decimal decimal_check = {{0x3A18A6, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok177) {
    // 807.082397
    int f = 1145685318;
    // 807.0824
    s21_decimal decimal_check = {{0x7B26A8, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok178) {
    // -807.082397
    int f = -1001798330;
    // -807.0824
    s21_decimal decimal_check = {{0x7B26A8, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok179) {
    // 1.00471938E-16
    int f = 619162666;
    // 0.0000000000000001004719
    s21_decimal decimal_check = {{0xF54AF, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok180) {
    // -1.00471938E-16
    int f = -1528320982;
    // -0.0000000000000001004719
    s21_decimal decimal_check = {{0xF54AF, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok181) {
    // 1.31486965E-18
    int f = 566364767;
    // 0.00000000000000000131487
    s21_decimal decimal_check = {{0x2019F, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok182) {
    // -1.31486965E-18
    int f = -1581118881;
    // -0.00000000000000000131487
    s21_decimal decimal_check = {{0x2019F, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok183) {
    // 8.47554286E-13
    int f = 728666297;
    // 0.0000000000008475543
    s21_decimal decimal_check = {{0x815397, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok184) {
    // -8.47554286E-13
    int f = -1418817351;
    // -0.0000000000008475543
    s21_decimal decimal_check = {{0x815397, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok185) {
    // 2.07975469E-28
    int f = 293851635;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok186) {
    // -2.07975469E-28
    int f = -1853632013;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok187) {
    // 2.76817269E+13
    int f = 1439263036;
    // 27681730000000
    s21_decimal decimal_check = {{0x27AEF480, 0x192D, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok188) {
    // -2.76817269E+13
    int f = -708220612;
    // -27681730000000
    s21_decimal decimal_check = {{0x27AEF480, 0x192D, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok189) {
    // 2.64643858E+12
    int f = 1410992898;
    // 2646439000000
    s21_decimal decimal_check = {{0x2C0E77C0, 0x268, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok190) {
    // -2.64643858E+12
    int f = -736490750;
    // -2646439000000
    s21_decimal decimal_check = {{0x2C0E77C0, 0x268, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok191) {
    // 7.66456801E+18
    int f = 1591000072;
    // 7664568000000000000
    s21_decimal decimal_check = {{0xC4D38000, 0x6A5E03FC, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok192) {
    // -7.66456801E+18
    int f = -556483576;
    // -7664568000000000000
    s21_decimal decimal_check = {{0xC4D38000, 0x6A5E03FC, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok193) {
    // 2.76005793E+27
    int f = 1829679376;
    // 2760058000000000000000000000
    s21_decimal decimal_check = {{0x38400000, 0xFD42C0C4, 0x8EB1103, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok194) {
    // -2.76005793E+27
    int f = -317804272;
    // -2760058000000000000000000000
    s21_decimal decimal_check = {{0x38400000, 0xFD42C0C4, 0x8EB1103, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok195) {
    // 4.72614865E-19
    int f = 554401221;
    // 0.0000000000000000004726149
    s21_decimal decimal_check = {{0x481D85, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok196) {
    // -4.72614865E-19
    int f = -1593082427;
    // -0.0000000000000000004726149
    s21_decimal decimal_check = {{0x481D85, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok197) {
    // 1.22559799E-13
    int f = 705297781;
    // 0.0000000000001225598
    s21_decimal decimal_check = {{0x12B37E, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok198) {
    // -1.22559799E-13
    int f = -1442185867;
    // -0.0000000000001225598
    s21_decimal decimal_check = {{0x12B37E, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok199) {
    // 4.67068756E+27
    int f = 1836152841;
    // 4670688000000000000000000000
    s21_decimal decimal_check = {{0x4C000000, 0xD4815AA5, 0xF1780A7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok200) {
    // -4.67068756E+27
    int f = -311330807;
    // -4670688000000000000000000000
    s21_decimal decimal_check = {{0x4C000000, 0xD4815AA5, 0xF1780A7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok201) {
    // 1.43260896E-27
    int f = 316866950;
    // 0.0000000000000000000000000014
    s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok202) {
    // -1.43260896E-27
    int f = -1830616698;
    // -0.0000000000000000000000000014
    s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok203) {
    // 0.00161657971
    int f = 986964842;
    // 0.00161658
    s21_decimal decimal_check = {{0x2777A, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok204) {
    // -0.00161657971
    int f = -1160518806;
    // -0.00161658
    s21_decimal decimal_check = {{0x2777A, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok205) {
    // 1.11468367E-18
    int f = 564428687;
    // 0.000000000000000001114684
    s21_decimal decimal_check = {{0x11023C, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok206) {
    // -1.11468367E-18
    int f = -1583054961;
    // -0.000000000000000001114684
    s21_decimal decimal_check = {{0x11023C, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok207) {
    // 1478.01416
    int f = 1152958580;
    // 1478.014
    s21_decimal decimal_check = {{0x168D7E, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok208) {
    // -1478.01416
    int f = -994525068;
    // -1478.014
    s21_decimal decimal_check = {{0x168D7E, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok209) {
    // 3.6517143E+09
    int f = 1331275965;
    // 3651714000
    s21_decimal decimal_check = {{0xD9A8BBD0, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok210) {
    // -3.6517143E+09
    int f = -816207683;
    // -3651714000
    s21_decimal decimal_check = {{0xD9A8BBD0, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok211) {
    // 2.08207478E+25
    int f = 1770637240;
    // 20820750000000000000000000
    s21_decimal decimal_check = {{0x13780000, 0x1E7FE2B2, 0x1138F7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok212) {
    // -2.08207478E+25
    int f = -376846408;
    // -20820750000000000000000000
    s21_decimal decimal_check = {{0x13780000, 0x1E7FE2B2, 0x1138F7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok213) {
    // 1.67284952E-06
    int f = 903906988;
    // 0.00000167285
    s21_decimal decimal_check = {{0x28D75, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok214) {
    // -1.67284952E-06
    int f = -1243576660;
    // -0.00000167285
    s21_decimal decimal_check = {{0x28D75, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok215) {
    // 1.00791645E+27
    int f = 1817210535;
    // 1007916000000000000000000000
    s21_decimal decimal_check = {{0xE3800000, 0xD819E2BC, 0x341BA83, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok216) {
    // -1.00791645E+27
    int f = -330273113;
    // -1007916000000000000000000000
    s21_decimal decimal_check = {{0xE3800000, 0xD819E2BC, 0x341BA83, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok217) {
    // 6.66145091E-18
    int f = 586531744;
    // 0.000000000000000006661451
    s21_decimal decimal_check = {{0x65A54B, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok218) {
    // -6.66145091E-18
    int f = -1560951904;
    // -0.000000000000000006661451
    s21_decimal decimal_check = {{0x65A54B, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok219) {
    // 15725.3545
    int f = 1182119275;
    // 15725.35
    s21_decimal decimal_check = {{0x17FEB7, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok220) {
    // -15725.3545
    int f = -965364373;
    // -15725.35
    s21_decimal decimal_check = {{0x17FEB7, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok221) {
    // 1.33397293
    int f = 1068154784;
    // 1.333973
    s21_decimal decimal_check = {{0x145AD5, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok222) {
    // -1.33397293
    int f = -1079328864;
    // -1.333973
    s21_decimal decimal_check = {{0x145AD5, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok223) {
    // 165025.641
    int f = 1210132585;
    // 165025.6
    s21_decimal decimal_check = {{0x192E50, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok224) {
    // -165025.641
    int f = -937351063;
    // -165025.6
    s21_decimal decimal_check = {{0x192E50, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok225) {
    // 1.2441821E+15
    int f = 1485664887;
    // 1244182000000000
    s21_decimal decimal_check = {{0xB2255C00, 0x46B93, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok226) {
    // -1.2441821E+15
    int f = -661818761;
    // -1244182000000000
    s21_decimal decimal_check = {{0xB2255C00, 0x46B93, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok227) {
    // 2.10811349E-13
    int f = 711809596;
    // 0.0000000000002108113
    s21_decimal decimal_check = {{0x202AD1, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok228) {
    // -2.10811349E-13
    int f = -1435674052;
    // -0.0000000000002108113
    s21_decimal decimal_check = {{0x202AD1, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok229) {
    // 2.40751309E+13
    int f = 1437543277;
    // 24075130000000
    s21_decimal decimal_check = {{0x6D925280, 0x15E5, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok230) {
    // -2.40751309E+13
    int f = -709940371;
    // -24075130000000
    s21_decimal decimal_check = {{0x6D925280, 0x15E5, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok231) {
    // 2.48895624E-25
    int f = 379195158;
    // 0.0000000000000000000000002489
    s21_decimal decimal_check = {{0x9B9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok232) {
    // -2.48895624E-25
    int f = -1768288490;
    // -0.0000000000000000000000002489
    s21_decimal decimal_check = {{0x9B9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok233) {
    // 1.31895402E+11
    int f = 1375055009;
    // 131895400000
    s21_decimal decimal_check = {{0xB5941640, 0x1E, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok234) {
    // -1.31895402E+11
    int f = -772428639;
    // -131895400000
    s21_decimal decimal_check = {{0xB5941640, 0x1E, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok235) {
    // 1.4550111E+11
    int f = 1376223787;
    // 145501100000
    s21_decimal decimal_check = {{0xE08A97E0, 0x21, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok236) {
    // -1.4550111E+11
    int f = -771259861;
    // -145501100000
    s21_decimal decimal_check = {{0xE08A97E0, 0x21, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok237) {
    // 6.25111367E-23
    int f = 446112901;
    // 0.0000000000000000000000625111
    s21_decimal decimal_check = {{0x989D7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok238) {
    // -6.25111367E-23
    int f = -1701370747;
    // -0.0000000000000000000000625111
    s21_decimal decimal_check = {{0x989D7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok239) {
    // 4.58558402E+27
    int f = 1835864499;
    // 4585584000000000000000000000
    s21_decimal decimal_check = {{0x66000000, 0xBEE8B75C, 0xED11B2E, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok240) {
    // -4.58558402E+27
    int f = -311619149;
    // -4585584000000000000000000000
    s21_decimal decimal_check = {{0x66000000, 0xBEE8B75C, 0xED11B2E, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok241) {
    // 3.28743145E-26
    int f = 354601253;
    // 0.0000000000000000000000000329
    s21_decimal decimal_check = {{0x149, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok242) {
    // -3.28743145E-26
    int f = -1792882395;
    // -0.0000000000000000000000000329
    s21_decimal decimal_check = {{0x149, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok243) {
    // 9.16167978E+16
    int f = 1537392255;
    // 91616800000000000
    s21_decimal decimal_check = {{0x83754000, 0x1457CFE, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok244) {
    // -9.16167978E+16
    int f = -610091393;
    // -91616800000000000
    s21_decimal decimal_check = {{0x83754000, 0x1457CFE, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok245) {
    // 0.026427852
    int f = 1020821305;
    // 0.02642785
    s21_decimal decimal_check = {{0x285361, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok246) {
    // -0.026427852
    int f = -1126662343;
    // -0.02642785
    s21_decimal decimal_check = {{0x285361, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok247) {
    // 1.24064249E-15
    int f = 649251745;
    // 0.000000000000001240642
    s21_decimal decimal_check = {{0x12EE42, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok248) {
    // -1.24064249E-15
    int f = -1498231903;
    // -0.000000000000001240642
    s21_decimal decimal_check = {{0x12EE42, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok249) {
    // 1.16119836E+15
    int f = 1485046610;
    // 1161198000000000
    s21_decimal decimal_check = {{0x7A4DCC00, 0x4201A, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok250) {
    // -1.16119836E+15
    int f = -662437038;
    // -1161198000000000
    s21_decimal decimal_check = {{0x7A4DCC00, 0x4201A, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok251) {
    // 2.50407264E-11
    int f = 769409716;
    // 0.00000000002504073
    s21_decimal decimal_check = {{0x263589, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok252) {
    // -2.50407264E-11
    int f = -1378073932;
    // -0.00000000002504073
    s21_decimal decimal_check = {{0x263589, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok253) {
    // 2.71758257E+15
    int f = 1494907400;
    // 2717583000000000
    s21_decimal decimal_check = {{0x995CD600, 0x9A7A0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok254) {
    // -2.71758257E+15
    int f = -652576248;
    // -2717583000000000
    s21_decimal decimal_check = {{0x995CD600, 0x9A7A0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok255) {
    // 9.97534673E+16
    int f = 1538339488;
    // 99753470000000000
    s21_decimal decimal_check = {{0xA0766C00, 0x1626540, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok256) {
    // -9.97534673E+16
    int f = -609144160;
    // -99753470000000000
    s21_decimal decimal_check = {{0xA0766C00, 0x1626540, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok257) {
    // 1.34486375E-15
    int f = 650236087;
    // 0.000000000000001344864
    s21_decimal decimal_check = {{0x148560, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok258) {
    // -1.34486375E-15
    int f = -1497247561;
    // -0.000000000000001344864
    s21_decimal decimal_check = {{0x148560, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok259) {
    // 1.82659161E-12
    int f = 738232563;
    // 0.000000000001826592
    s21_decimal decimal_check = {{0x1BDF20, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok260) {
    // -1.82659161E-12
    int f = -1409251085;
    // -0.000000000001826592
    s21_decimal decimal_check = {{0x1BDF20, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok261) {
    // 7.77944088
    int f = 1090056494;
    // 7.779441
    s21_decimal decimal_check = {{0x76B471, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok262) {
    // -7.77944088
    int f = -1057427154;
    // -7.779441
    s21_decimal decimal_check = {{0x76B471, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok263) {
    // 3.12144136E+16
    int f = 1524484784;
    // 31214410000000000
    s21_decimal decimal_check = {{0x2BEC6400, 0x6EE557, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok264) {
    // -3.12144136E+16
    int f = -622998864;
    // -31214410000000000
    s21_decimal decimal_check = {{0x2BEC6400, 0x6EE557, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok265) {
    // 530444320
    int f = 1308422017;
    // 530444300
    s21_decimal decimal_check = {{0x1F9DF00C, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok266) {
    // -530444320
    int f = -839061631;
    // -530444300
    s21_decimal decimal_check = {{0x1F9DF00C, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok267) {
    // 3.93075884E+12
    int f = 1415892191;
    // 3930759000000
    s21_decimal decimal_check = {{0x337E6FC0, 0x393, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok268) {
    // -3.93075884E+12
    int f = -731591457;
    // -3930759000000
    s21_decimal decimal_check = {{0x337E6FC0, 0x393, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok269) {
    // 7.42264215E-19
    int f = 559616998;
    // 0.0000000000000000007422642
    s21_decimal decimal_check = {{0x7142B2, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok270) {
    // -7.42264215E-19
    int f = -1587866650;
    // -0.0000000000000000007422642
    s21_decimal decimal_check = {{0x7142B2, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok271) {
    // 1.06286686E-19
    int f = 536540764;
    // 0.0000000000000000001062867
    s21_decimal decimal_check = {{0x1037D3, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok272) {
    // -1.06286686E-19
    int f = -1610942884;
    // -0.0000000000000000001062867
    s21_decimal decimal_check = {{0x1037D3, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok273) {
    // 3.94556822E+15
    int f = 1499482003;
    // 3945568000000000
    s21_decimal decimal_check = {{0x2313C000, 0xE0479, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok274) {
    // -3.94556822E+15
    int f = -648001645;
    // -3945568000000000
    s21_decimal decimal_check = {{0x2313C000, 0xE0479, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok275) {
    // 4.74276045E+09
    int f = 1334663268;
    // 4742760000
    s21_decimal decimal_check = {{0x1AB0C640, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok276) {
    // -4.74276045E+09
    int f = -812820380;
    // -4742760000
    s21_decimal decimal_check = {{0x1AB0C640, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok277) {
    // 6.8088455E-05
    int f = 948882102;
    // 0.00006808846
    s21_decimal decimal_check = {{0x67E50E, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok278) {
    // -6.8088455E-05
    int f = -1198601546;
    // -0.00006808846
    s21_decimal decimal_check = {{0x67E50E, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok279) {
    // 9.93429178E-27
    int f = 340051160;
    // 0.0000000000000000000000000099
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok280) {
    // -9.93429178E-27
    int f = -1807432488;
    // -0.0000000000000000000000000099
    s21_decimal decimal_check = {{0x63, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok281) {
    // 1.2797555E-08
    int f = 844880958;
    // 0.00000001279756
    s21_decimal decimal_check = {{0x13870C, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok282) {
    // -1.2797555E-08
    int f = -1302602690;
    // -0.00000001279756
    s21_decimal decimal_check = {{0x13870C, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok283) {
    // 1.80100608
    int f = 1072072542;
    // 1.801006
    s21_decimal decimal_check = {{0x1B7B2E, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok284) {
    // -1.80100608
    int f = -1075411106;
    // -1.801006
    s21_decimal decimal_check = {{0x1B7B2E, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok285) {
    // 2.88075291E-15
    int f = 659526787;
    // 0.000000000000002880753
    s21_decimal decimal_check = {{0x2BF4F1, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok286) {
    // -2.88075291E-15
    int f = -1487956861;
    // -0.000000000000002880753
    s21_decimal decimal_check = {{0x2BF4F1, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok287) {
    // 4.98270022E+16
    int f = 1529939301;
    // 49827000000000000
    s21_decimal decimal_check = {{0x7B393000, 0xB10564, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok288) {
    // -4.98270022E+16
    int f = -617544347;
    // -49827000000000000
    s21_decimal decimal_check = {{0x7B393000, 0xB10564, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok289) {
    // 19.2353897
    int f = 1100603924;
    // 19.23539
    s21_decimal decimal_check = {{0x1D59D3, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok290) {
    // -19.2353897
    int f = -1046879724;
    // -19.23539
    s21_decimal decimal_check = {{0x1D59D3, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok291) {
    // 7.56507507E-06
    int f = 922605440;
    // 0.000007565075
    s21_decimal decimal_check = {{0x736F13, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok292) {
    // -7.56507507E-06
    int f = -1224878208;
    // -0.000007565075
    s21_decimal decimal_check = {{0x736F13, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok293) {
    // 1.72874326E-10
    int f = 792597452;
    // 0.0000000001728743
    s21_decimal decimal_check = {{0x1A60E7, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok294) {
    // -1.72874326E-10
    int f = -1354886196;
    // -0.0000000001728743
    s21_decimal decimal_check = {{0x1A60E7, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok295) {
    // 973.707092
    int f = 1148415297;
    // 973.7071
    s21_decimal decimal_check = {{0x94936F, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok296) {
    // -973.707092
    int f = -999068351;
    // -973.7071
    s21_decimal decimal_check = {{0x94936F, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok297) {
    // 5.56646213E+17
    int f = 1559704409;
    // 556646200000000000
    s21_decimal decimal_check = {{0x8923000, 0x7B99AC5, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok298) {
    // -5.56646213E+17
    int f = -587779239;
    // -556646200000000000
    s21_decimal decimal_check = {{0x8923000, 0x7B99AC5, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok299) {
    // 0.0539412126
    int f = 1029501302;
    // 0.05394121
    s21_decimal decimal_check = {{0x524EC9, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok300) {
    // -0.0539412126
    int f = -1117982346;
    // -0.05394121
    s21_decimal decimal_check = {{0x524EC9, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok301) {
    // 5.68253473E+25
    int f = 1782318321;
    // 56825350000000000000000000
    s21_decimal decimal_check = {{0x84580000, 0x6567A044, 0x2F013C, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok302) {
    // -5.68253473E+25
    int f = -365165327;
    // -56825350000000000000000000
    s21_decimal decimal_check = {{0x84580000, 0x6567A044, 0x2F013C, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok303) {
    // 1.88714903E-22
    int f = 459547759;
    // 0.0000000000000000000001887149
    s21_decimal decimal_check = {{0x1CCBAD, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok304) {
    // -1.88714903E-22
    int f = -1687935889;
    // -0.0000000000000000000001887149
    s21_decimal decimal_check = {{0x1CCBAD, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok305) {
    // 3.86104686E+21
    int f = 1666272970;
    // 3861047000000000000000
    s21_decimal decimal_check = {{0xD7A58000, 0x4ECA7DCB, 0xD1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok306) {
    // -3.86104686E+21
    int f = -481210678;
    // -3861047000000000000000
    s21_decimal decimal_check = {{0xD7A58000, 0x4ECA7DCB, 0xD1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok307) {
    // 2.58369932E-23
    int f = 435806540;
    // 0.000000000000000000000025837
    s21_decimal decimal_check = {{0x64ED, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok308) {
    // -2.58369932E-23
    int f = -1711677108;
    // -0.000000000000000000000025837
    s21_decimal decimal_check = {{0x64ED, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok309) {
    // 3.77445417E+14
    int f = 1470866542;
    // 377445400000000
    s21_decimal decimal_check = {{0xDAFD3600, 0x15748, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok310) {
    // -3.77445417E+14
    int f = -676617106;
    // -377445400000000
    s21_decimal decimal_check = {{0xDAFD3600, 0x15748, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok311) {
    // 3.96881507E-27
    int f = 329070737;
    // 0.000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok312) {
    // -3.96881507E-27
    int f = -1818412911;
    // -0.000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok313) {
    // 6.08972547E+16
    int f = 1532516795;
    // 60897250000000000
    s21_decimal decimal_check = {{0xEA0C5400, 0xD859B9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok314) {
    // -6.08972547E+16
    int f = -614966853;
    // -60897250000000000
    s21_decimal decimal_check = {{0xEA0C5400, 0xD859B9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok315) {
    // 4.54454516E+14
    int f = 1473161592;
    // 454454500000000
    s21_decimal decimal_check = {{0xEF0A0100, 0x19D52, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok316) {
    // -4.54454516E+14
    int f = -674322056;
    // -454454500000000
    s21_decimal decimal_check = {{0xEF0A0100, 0x19D52, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok317) {
    // 298389.375
    int f = 1217508012;
    // 298389.4
    s21_decimal decimal_check = {{0x2D87D6, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok318) {
    // -298389.375
    int f = -929975636;
    // -298389.4
    s21_decimal decimal_check = {{0x2D87D6, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok319) {
    // 7.39824756E-19
    int f = 559569812;
    // 0.0000000000000000007398248
    s21_decimal decimal_check = {{0x70E368, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok320) {
    // -7.39824756E-19
    int f = -1587913836;
    // -0.0000000000000000007398248
    s21_decimal decimal_check = {{0x70E368, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok321) {
    // 7.90202733E+27
    int f = 1842103099;
    // 7902027000000000000000000000
    s21_decimal decimal_check = {{0x18E00000, 0x59EE2CE, 0x1988674E, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok322) {
    // -7.90202733E+27
    int f = -305380549;
    // -7902027000000000000000000000
    s21_decimal decimal_check = {{0x18E00000, 0x59EE2CE, 0x1988674E, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok323) {
    // 8.36178333E-06
    int f = 923552150;
    // 0.000008361783
    s21_decimal decimal_check = {{0x7F9737, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok324) {
    // -8.36178333E-06
    int f = -1223931498;
    // -0.000008361783
    s21_decimal decimal_check = {{0x7F9737, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok325) {
    // 3769.21729
    int f = 1164678010;
    // 3769.217
    s21_decimal decimal_check = {{0x398381, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok326) {
    // -3769.21729
    int f = -982805638;
    // -3769.217
    s21_decimal decimal_check = {{0x398381, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok327) {
    // 1.80550409E+12
    int f = 1406283831;
    // 1805504000000
    s21_decimal decimal_check = {{0x606CB000, 0x1A4, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok328) {
    // -1.80550409E+12
    int f = -741199817;
    // -1805504000000
    s21_decimal decimal_check = {{0x606CB000, 0x1A4, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok329) {
    // 2.00816507E+21
    int f = 1658436039;
    // 2008165000000000000000
    s21_decimal decimal_check = {{0x2C508000, 0xDCE343C9, 0x6C, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok330) {
    // -2.00816507E+21
    int f = -489047609;
    // -2008165000000000000000
    s21_decimal decimal_check = {{0x2C508000, 0xDCE343C9, 0x6C, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok331) {
    // 42.4789772
    int f = 1110043257;
    // 42.47898
    s21_decimal decimal_check = {{0x40D15A, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok332) {
    // -42.4789772
    int f = -1037440391;
    // -42.47898
    s21_decimal decimal_check = {{0x40D15A, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok333) {
    // 1.42036498E+14
    int f = 1459695219;
    // 142036500000000
    s21_decimal decimal_check = {{0x7320AD00, 0x812E, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok334) {
    // -1.42036498E+14
    int f = -687788429;
    // -142036500000000
    s21_decimal decimal_check = {{0x7320AD00, 0x812E, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok335) {
    // 3.08074432E+20
    int f = 1636145954;
    // 308074400000000000000
    s21_decimal decimal_check = {{0x479A0000, 0xB364228D, 0x10, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok336) {
    // -3.08074432E+20
    int f = -511337694;
    // -308074400000000000000
    s21_decimal decimal_check = {{0x479A0000, 0xB364228D, 0x10, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok337) {
    // 2.82437522E+23
    int f = 1718565856;
    // 282437500000000000000000
    s21_decimal decimal_check = {{0xCDA60000, 0xF7B1A7FD, 0x3BCE, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok338) {
    // -2.82437522E+23
    int f = -428917792;
    // -282437500000000000000000
    s21_decimal decimal_check = {{0xCDA60000, 0xF7B1A7FD, 0x3BCE, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok339) {
    // 2.16314857E-06
    int f = 907094684;
    // 0.000002163149
    s21_decimal decimal_check = {{0x2101CD, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok340) {
    // -2.16314857E-06
    int f = -1240388964;
    // -0.000002163149
    s21_decimal decimal_check = {{0x2101CD, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok341) {
    // 3.11719901E-23
    int f = 437697806;
    // 0.000000000000000000000031172
    s21_decimal decimal_check = {{0x79C4, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok342) {
    // -3.11719901E-23
    int f = -1709785842;
    // -0.000000000000000000000031172
    s21_decimal decimal_check = {{0x79C4, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok343) {
    // 7.10805625E+18
    int f = 1589987783;
    // 7108056000000000000
    s21_decimal decimal_check = {{0x9B958000, 0x62A4E345, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok344) {
    // -7.10805625E+18
    int f = -557495865;
    // -7108056000000000000
    s21_decimal decimal_check = {{0x9B958000, 0x62A4E345, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok345) {
    // 1.10467782E-23
    int f = 425045247;
    // 0.0000000000000000000000110468
    s21_decimal decimal_check = {{0x1AF84, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok346) {
    // -1.10467782E-23
    int f = -1722438401;
    // -0.0000000000000000000000110468
    s21_decimal decimal_check = {{0x1AF84, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok347) {
    // 6.46864174E+21
    int f = 1672435000;
    // 6468642000000000000000
    s21_decimal decimal_check = {{0x745D0000, 0xAA70EAAA, 0x15E, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok348) {
    // -6.46864174E+21
    int f = -475048648;
    // -6468642000000000000000
    s21_decimal decimal_check = {{0x745D0000, 0xAA70EAAA, 0x15E, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok349) {
    // 0.00363415456
    int f = 997075711;
    // 0.003634155
    s21_decimal decimal_check = {{0x3773EB, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok350) {
    // -0.00363415456
    int f = -1150407937;
    // -0.003634155
    s21_decimal decimal_check = {{0x3773EB, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok351) {
    // 1.78366992E-08
    int f = 848901969;
    // 0.0000000178367
    s21_decimal decimal_check = {{0x2B8BF, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok352) {
    // -1.78366992E-08
    int f = -1298581679;
    // -0.0000000178367
    s21_decimal decimal_check = {{0x2B8BF, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok353) {
    // 3.28054909E-07
    int f = 883957638;
    // 0.0000003280549
    s21_decimal decimal_check = {{0x320EA5, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok354) {
    // -3.28054909E-07
    int f = -1263526010;
    // -0.0000003280549
    s21_decimal decimal_check = {{0x320EA5, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok355) {
    // 0.129331082
    int f = 1040478046;
    // 0.1293311
    s21_decimal decimal_check = {{0x13BBFF, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok356) {
    // -0.129331082
    int f = -1107005602;
    // -0.1293311
    s21_decimal decimal_check = {{0x13BBFF, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok357) {
    // 30.7339287
    int f = 1106632470;
    // 30.73393
    s21_decimal decimal_check = {{0x2EE571, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok358) {
    // -30.7339287
    int f = -1040851178;
    // -30.73393
    s21_decimal decimal_check = {{0x2EE571, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok359) {
    // 3.0781897E-18
    int f = 576921948;
    // 0.00000000000000000307819
    s21_decimal decimal_check = {{0x4B26B, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok360) {
    // -3.0781897E-18
    int f = -1570561700;
    // -0.00000000000000000307819
    s21_decimal decimal_check = {{0x4B26B, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok361) {
    // 1.41380582E+17
    int f = 1543185522;
    // 141380600000000000
    s21_decimal decimal_check = {{0x1921B000, 0x1F648E8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok362) {
    // -1.41380582E+17
    int f = -604298126;
    // -141380600000000000
    s21_decimal decimal_check = {{0x1921B000, 0x1F648E8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok363) {
    // 1.33295075E-26
    int f = 344195665;
    // 0.0000000000000000000000000133
    s21_decimal decimal_check = {{0x85, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok364) {
    // -1.33295075E-26
    int f = -1803287983;
    // -0.0000000000000000000000000133
    s21_decimal decimal_check = {{0x85, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok365) {
    // 8.498085E+16
    int f = 1536619729;
    // 84980850000000000
    s21_decimal decimal_check = {{0xF5F400, 0x12DE9A2, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok366) {
    // -8.498085E+16
    int f = -610863919;
    // -84980850000000000
    s21_decimal decimal_check = {{0xF5F400, 0x12DE9A2, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok367) {
    // 12405.1982
    int f = 1178719435;
    // 12405.2
    s21_decimal decimal_check = {{0x1E494, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok368) {
    // -12405.1982
    int f = -968764213;
    // -12405.2
    s21_decimal decimal_check = {{0x1E494, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok369) {
    // 1.70968087E-20
    int f = 513898892;
    // 0.00000000000000000001709681
    s21_decimal decimal_check = {{0x1A1671, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok370) {
    // -1.70968087E-20
    int f = -1633584756;
    // -0.00000000000000000001709681
    s21_decimal decimal_check = {{0x1A1671, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok371) {
    // 2.09692443E-16
    int f = 628212297;
    // 0.0000000000000002096924
    s21_decimal decimal_check = {{0x1FFF1C, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok372) {
    // -2.09692443E-16
    int f = -1519271351;
    // -0.0000000000000002096924
    s21_decimal decimal_check = {{0x1FFF1C, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok373) {
    // 8.02104489E+12
    int f = 1424585073;
    // 8021045000000
    s21_decimal decimal_check = {{0x8B89B740, 0x74B, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok374) {
    // -8.02104489E+12
    int f = -722898575;
    // -8021045000000
    s21_decimal decimal_check = {{0x8B89B740, 0x74B, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok375) {
    // 1.04314942E-07
    int f = 870319039;
    // 0.0000001043149
    s21_decimal decimal_check = {{0xFEACD, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok376) {
    // -1.04314942E-07
    int f = -1277164609;
    // -0.0000001043149
    s21_decimal decimal_check = {{0xFEACD, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok377) {
    // 2.64088815E+15
    int f = 1494621691;
    // 2640888000000000
    s21_decimal decimal_check = {{0xA721B000, 0x961DF, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok378) {
    // -2.64088815E+15
    int f = -652861957;
    // -2640888000000000
    s21_decimal decimal_check = {{0xA721B000, 0x961DF, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok379) {
    // 4.67902401E+25
    int f = 1780142304;
    // 46790240000000000000000000
    s21_decimal decimal_check = {{0xDD800000, 0xFE325BBC, 0x26B437, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok380) {
    // -4.67902401E+25
    int f = -367341344;
    // -46790240000000000000000000
    s21_decimal decimal_check = {{0xDD800000, 0xFE325BBC, 0x26B437, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok381) {
    // 1.73181625E-18
    int f = 570397227;
    // 0.000000000000000001731816
    s21_decimal decimal_check = {{0x1A6CE8, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok382) {
    // -1.73181625E-18
    int f = -1577086421;
    // -0.000000000000000001731816
    s21_decimal decimal_check = {{0x1A6CE8, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok383) {
    // 4.29781641E+18
    int f = 1584305061;
    // 4297816000000000000
    s21_decimal decimal_check = {{0x95FD8000, 0x3BA4E8E1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok384) {
    // -4.29781641E+18
    int f = -563178587;
    // -4297816000000000000
    s21_decimal decimal_check = {{0x95FD8000, 0x3BA4E8E1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok385) {
    // 7.99136845E+21
    int f = 1675139906;
    // 7991368000000000000000
    s21_decimal decimal_check = {{0xEFD40000, 0x368267EA, 0x1B1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok386) {
    // -7.99136845E+21
    int f = -472343742;
    // -7991368000000000000000
    s21_decimal decimal_check = {{0xEFD40000, 0x368267EA, 0x1B1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok387) {
    // 4.69790976E-25
    int f = 387015853;
    // 0.0000000000000000000000004698
    s21_decimal decimal_check = {{0x125A, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok388) {
    // -4.69790976E-25
    int f = -1760467795;
    // -0.0000000000000000000000004698
    s21_decimal decimal_check = {{0x125A, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok389) {
    // 1.23054447E+20
    int f = 1624602407;
    // 123054400000000000000
    s21_decimal decimal_check = {{0x70D40000, 0xABB90CD4, 0x6, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok390) {
    // -1.23054447E+20
    int f = -522881241;
    // -123054400000000000000
    s21_decimal decimal_check = {{0x70D40000, 0xABB90CD4, 0x6, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok391) {
    // 7.58803818E+14
    int f = 1479313458;
    // 758803800000000
    s21_decimal decimal_check = {{0xC6F40600, 0x2B220, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok392) {
    // -7.58803818E+14
    int f = -668170190;
    // -758803800000000
    s21_decimal decimal_check = {{0xC6F40600, 0x2B220, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok393) {
    // 2.37397573E+14
    int f = 1465379182;
    // 237397600000000
    s21_decimal decimal_check = {{0x6F9E5800, 0xD7E9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok394) {
    // -2.37397573E+14
    int f = -682104466;
    // -237397600000000
    s21_decimal decimal_check = {{0x6F9E5800, 0xD7E9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok395) {
    // 7.94356025E-10
    int f = 811227606;
    // 0.000000000794356
    s21_decimal decimal_check = {{0xC1EF4, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok396) {
    // -7.94356025E-10
    int f = -1336256042;
    // -0.000000000794356
    s21_decimal decimal_check = {{0xC1EF4, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok397) {
    // 2.47739942E+13
    int f = 1437876521;
    // 24773990000000
    s21_decimal decimal_check = {{0x24DFA580, 0x1688, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok398) {
    // -2.47739942E+13
    int f = -709607127;
    // -24773990000000
    s21_decimal decimal_check = {{0x24DFA580, 0x1688, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok399) {
    // 4.61453107E+17
    int f = 1556933925;
    // 461453100000000000
    s21_decimal decimal_check = {{0x4A00B800, 0x6676926, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok400) {
    // -4.61453107E+17
    int f = -590549723;
    // -461453100000000000
    s21_decimal decimal_check = {{0x4A00B800, 0x6676926, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok401) {
    // 0.0132824397
    int f = 1012506263;
    // 0.01328244
    s21_decimal decimal_check = {{0x144474, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok402) {
    // -0.0132824397
    int f = -1134977385;
    // -0.01328244
    s21_decimal decimal_check = {{0x144474, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok403) {
    // 2.65441857E-13
    int f = 714436148;
    // 0.0000000000002654419
    s21_decimal decimal_check = {{0x2880D3, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok404) {
    // -2.65441857E-13
    int f = -1433047500;
    // -0.0000000000002654419
    s21_decimal decimal_check = {{0x2880D3, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok405) {
    // 0.00343554723
    int f = 996222699;
    // 0.003435547
    s21_decimal decimal_check = {{0x346C1B, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok406) {
    // -0.00343554723
    int f = -1151260949;
    // -0.003435547
    s21_decimal decimal_check = {{0x346C1B, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok407) {
    // 1.35303762E-15
    int f = 650313287;
    // 0.000000000000001353038
    s21_decimal decimal_check = {{0x14A54E, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok408) {
    // -1.35303762E-15
    int f = -1497170361;
    // -0.000000000000001353038
    s21_decimal decimal_check = {{0x14A54E, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok409) {
    // 4.42256499E-18
    int f = 581118450;
    // 0.000000000000000004422565
    s21_decimal decimal_check = {{0x437BA5, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok410) {
    // -4.42256499E-18
    int f = -1566365198;
    // -0.000000000000000004422565
    s21_decimal decimal_check = {{0x437BA5, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok411) {
    // 3.9987157E+24
    int f = 1750315188;
    // 3998716000000000000000000
    s21_decimal decimal_check = {{0xF2700000, 0xD426D6A2, 0x34EC2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok412) {
    // -3.9987157E+24
    int f = -397168460;
    // -3998716000000000000000000
    s21_decimal decimal_check = {{0xF2700000, 0xD426D6A2, 0x34EC2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok413) {
    // 1.69642088E+19
    int f = 1600875770;
    // 16964210000000000000
    s21_decimal decimal_check = {{0x61212000, 0xEB6CFB1D, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok414) {
    // -1.69642088E+19
    int f = -546607878;
    // -16964210000000000000
    s21_decimal decimal_check = {{0x61212000, 0xEB6CFB1D, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok415) {
    // 2.8703019E+17
    int f = 1551822620;
    // 287030200000000000
    s21_decimal decimal_check = {{0x36CF3000, 0x3FBBC72, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok416) {
    // -2.8703019E+17
    int f = -595661028;
    // -287030200000000000
    s21_decimal decimal_check = {{0x36CF3000, 0x3FBBC72, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok417) {
    // 0.00710056303
    int f = 1005104087;
    // 0.007100563
    s21_decimal decimal_check = {{0x6C5893, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok418) {
    // -0.00710056303
    int f = -1142379561;
    // -0.007100563
    s21_decimal decimal_check = {{0x6C5893, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok419) {
    // 2.07633703E-16
    int f = 628056743;
    // 0.0000000000000002076337
    s21_decimal decimal_check = {{0x1FAEB1, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok420) {
    // -2.07633703E-16
    int f = -1519426905;
    // -0.0000000000000002076337
    s21_decimal decimal_check = {{0x1FAEB1, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok421) {
    // 0.0123325782
    int f = 1011486357;
    // 0.01233258
    s21_decimal decimal_check = {{0x12D16A, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok422) {
    // -0.0123325782
    int f = -1135997291;
    // -0.01233258
    s21_decimal decimal_check = {{0x12D16A, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok423) {
    // 1.17045804E-21
    int f = 481353703;
    // 0.000000000000000000001170458
    s21_decimal decimal_check = {{0x11DC1A, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok424) {
    // -1.17045804E-21
    int f = -1666129945;
    // -0.000000000000000000001170458
    s21_decimal decimal_check = {{0x11DC1A, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok425) {
    // 7.34081171E-26
    int f = 364232684;
    // 0.0000000000000000000000000734
    s21_decimal decimal_check = {{0x2DE, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok426) {
    // -7.34081171E-26
    int f = -1783250964;
    // -0.0000000000000000000000000734
    s21_decimal decimal_check = {{0x2DE, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok427) {
    // 9.68161412E-16
    int f = 646678234;
    // 0.0000000000000009681614
    s21_decimal decimal_check = {{0x93BACE, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok428) {
    // -9.68161412E-16
    int f = -1500805414;
    // -0.0000000000000009681614
    s21_decimal decimal_check = {{0x93BACE, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok429) {
    // 5.10048003E-18
    int f = 582757548;
    // 0.00000000000000000510048
    s21_decimal decimal_check = {{0x7C860, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok430) {
    // -5.10048003E-18
    int f = -1564726100;
    // -0.00000000000000000510048
    s21_decimal decimal_check = {{0x7C860, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok431) {
    // 1.45322634E+15
    int f = 1487222388;
    // 1453226000000000
    s21_decimal decimal_check = {{0x8B822400, 0x529B3, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok432) {
    // -1.45322634E+15
    int f = -660261260;
    // -1453226000000000
    s21_decimal decimal_check = {{0x8B822400, 0x529B3, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok433) {
    // 5.01371069E-05
    int f = 944917071;
    // 0.00005013711
    s21_decimal decimal_check = {{0x4C80CF, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok434) {
    // -5.01371069E-05
    int f = -1202566577;
    // -0.00005013711
    s21_decimal decimal_check = {{0x4C80CF, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok435) {
    // 1.51663215E+17
    int f = 1543943225;
    // 151663200000000000
    s21_decimal decimal_check = {{0x797FC000, 0x21AD0E0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok436) {
    // -1.51663215E+17
    int f = -603540423;
    // -151663200000000000
    s21_decimal decimal_check = {{0x797FC000, 0x21AD0E0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok437) {
    // 2.63885937E-07
    int f = 881699893;
    // 0.0000002638859
    s21_decimal decimal_check = {{0x28440B, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok438) {
    // -2.63885937E-07
    int f = -1265783755;
    // -0.0000002638859
    s21_decimal decimal_check = {{0x28440B, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok439) {
    // 0.0961552188
    int f = 1036315911;
    // 0.09615522
    s21_decimal decimal_check = {{0x92B8A2, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok440) {
    // -0.0961552188
    int f = -1111167737;
    // -0.09615522
    s21_decimal decimal_check = {{0x92B8A2, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok441) {
    // 5158729.5
    int f = 1251831443;
    // 5158730
    s21_decimal decimal_check = {{0x4EB74A, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok442) {
    // -5158729.5
    int f = -895652205;
    // -5158730
    s21_decimal decimal_check = {{0x4EB74A, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok443) {
    // 2.75523903E-17
    int f = 603856958;
    // 0.00000000000000002755239
    s21_decimal decimal_check = {{0x2A0AA7, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok444) {
    // -2.75523903E-17
    int f = -1543626690;
    // -0.00000000000000002755239
    s21_decimal decimal_check = {{0x2A0AA7, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok445) {
    // 6.03424028E+22
    int f = 1699508913;
    // 60342400000000000000000
    s21_decimal decimal_check = {{0x43400000, 0x2B05E443, 0xCC7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok446) {
    // -6.03424028E+22
    int f = -447974735;
    // -60342400000000000000000
    s21_decimal decimal_check = {{0x43400000, 0x2B05E443, 0xCC7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok447) {
    // 3.12045131E+15
    int f = 1496408203;
    // 3120451000000000
    s21_decimal decimal_check = {{0x9D64DE00, 0xB1608, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok448) {
    // -3.12045131E+15
    int f = -651075445;
    // -3120451000000000
    s21_decimal decimal_check = {{0x9D64DE00, 0xB1608, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok449) {
    // 1.204393E-26
    int f = 342789627;
    // 0.000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok450) {
    // -1.204393E-26
    int f = -1804694021;
    // -0.000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok451) {
    // 6.88218899E-24
    int f = 419766003;
    // 0.0000000000000000000000068822
    s21_decimal decimal_check = {{0x10CD6, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok452) {
    // -6.88218899E-24
    int f = -1727717645;
    // -0.0000000000000000000000068822
    s21_decimal decimal_check = {{0x10CD6, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok453) {
    // 8.86825921E+14
    int f = 1481221136;
    // 886825900000000
    s21_decimal decimal_check = {{0x3EBF4300, 0x32690, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok454) {
    // -8.86825921E+14
    int f = -666262512;
    // -886825900000000
    s21_decimal decimal_check = {{0x3EBF4300, 0x32690, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok455) {
    // 1.16186845E+19
    int f = 1596014044;
    // 11618680000000000000
    s21_decimal decimal_check = {{0xCEEF8000, 0xA13DD7E6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok456) {
    // -1.16186845E+19
    int f = -551469604;
    // -11618680000000000000
    s21_decimal decimal_check = {{0xCEEF8000, 0xA13DD7E6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok457) {
    // 5.2696175E+19
    int f = 1614205851;
    // 52696180000000000000
    s21_decimal decimal_check = {{0x800B4000, 0xDB4E7083, 0x2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok458) {
    // -5.2696175E+19
    int f = -533277797;
    // -52696180000000000000
    s21_decimal decimal_check = {{0x800B4000, 0xDB4E7083, 0x2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok459) {
    // 1.23902404
    int f = 1067358295;
    // 1.239024
    s21_decimal decimal_check = {{0x12E7F0, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok460) {
    // -1.23902404
    int f = -1080125353;
    // -1.239024
    s21_decimal decimal_check = {{0x12E7F0, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok461) {
    // 7.54658613E-05
    int f = 949896045;
    // 0.00007546586
    s21_decimal decimal_check = {{0x7326DA, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok462) {
    // -7.54658613E-05
    int f = -1197587603;
    // -0.00007546586
    s21_decimal decimal_check = {{0x7326DA, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok463) {
    // 2.06063239E+20
    int f = 1630714683;
    // 206063200000000000000
    s21_decimal decimal_check = {{0x60460000, 0x2BB38CA1, 0xB, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok464) {
    // -2.06063239E+20
    int f = -516768965;
    // -206063200000000000000
    s21_decimal decimal_check = {{0x60460000, 0x2BB38CA1, 0xB, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok465) {
    // 5540.46826
    int f = 1168974783;
    // 5540.468
    s21_decimal decimal_check = {{0x548A74, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok466) {
    // -5540.46826
    int f = -978508865;
    // -5540.468
    s21_decimal decimal_check = {{0x548A74, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok467) {
    // 33.4760551
    int f = 1107683195;
    // 33.47606
    s21_decimal decimal_check = {{0x331496, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok468) {
    // -33.4760551
    int f = -1039800453;
    // -33.47606
    s21_decimal decimal_check = {{0x331496, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok469) {
    // 230.469971
    int f = 1130788944;
    // 230.47
    s21_decimal decimal_check = {{0x5A07, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok470) {
    // -230.469971
    int f = -1016694704;
    // -230.47
    s21_decimal decimal_check = {{0x5A07, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok471) {
    // 2.83283619E-09
    int f = 826452936;
    // 0.000000002832836
    s21_decimal decimal_check = {{0x2B39C4, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok472) {
    // -2.83283619E-09
    int f = -1321030712;
    // -0.000000002832836
    s21_decimal decimal_check = {{0x2B39C4, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok473) {
    // 3.81195787E-06
    int f = 914346224;
    // 0.000003811958
    s21_decimal decimal_check = {{0x3A2A76, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok474) {
    // -3.81195787E-06
    int f = -1233137424;
    // -0.000003811958
    s21_decimal decimal_check = {{0x3A2A76, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok475) {
    // 3.29543241E-07
    int f = 884010004;
    // 0.0000003295432
    s21_decimal decimal_check = {{0x3248C8, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok476) {
    // -3.29543241E-07
    int f = -1263473644;
    // -0.0000003295432
    s21_decimal decimal_check = {{0x3248C8, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok477) {
    // 2.72814009E-17
    int f = 603693155;
    // 0.0000000000000000272814
    s21_decimal decimal_check = {{0x429AE, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok478) {
    // -2.72814009E-17
    int f = -1543790493;
    // -0.0000000000000000272814
    s21_decimal decimal_check = {{0x429AE, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok479) {
    // 4.3101769E-27
    int f = 329956963;
    // 0.0000000000000000000000000043
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok480) {
    // -4.3101769E-27
    int f = -1817526685;
    // -0.0000000000000000000000000043
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok481) {
    // 6.16077213E-18
    int f = 585321177;
    // 0.000000000000000006160772
    s21_decimal decimal_check = {{0x5E0184, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok482) {
    // -6.16077213E-18
    int f = -1562162471;
    // -0.000000000000000006160772
    s21_decimal decimal_check = {{0x5E0184, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok483) {
    // 1.37073535E+13
    int f = 1430747103;
    // 13707350000000
    s21_decimal decimal_check = {{0x7DBA4180, 0xC77, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok484) {
    // -1.37073535E+13
    int f = -716736545;
    // -13707350000000
    s21_decimal decimal_check = {{0x7DBA4180, 0xC77, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok485) {
    // 1.45893181E+13
    int f = 1431588210;
    // 14589320000000
    s21_decimal decimal_check = {{0xD73C7200, 0xD44, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok486) {
    // -1.45893181E+13
    int f = -715895438;
    // -14589320000000
    s21_decimal decimal_check = {{0xD73C7200, 0xD44, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok487) {
    // 1.22646696E-07
    int f = 872657118;
    // 0.0000001226467
    s21_decimal decimal_check = {{0x12B6E3, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok488) {
    // -1.22646696E-07
    int f = -1274826530;
    // -0.0000001226467
    s21_decimal decimal_check = {{0x12B6E3, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok489) {
    // 1.97494607E-11
    int f = 766359509;
    // 0.00000000001974946
    s21_decimal decimal_check = {{0x1E22A2, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok490) {
    // -1.97494607E-11
    int f = -1381124139;
    // -0.00000000001974946
    s21_decimal decimal_check = {{0x1E22A2, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok491) {
    // 7.9162121E+20
    int f = 1647028174;
    // 791621200000000000000
    s21_decimal decimal_check = {{0xC750000, 0xE9F37736, 0x2A, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok492) {
    // -7.9162121E+20
    int f = -500455474;
    // -791621200000000000000
    s21_decimal decimal_check = {{0xC750000, 0xE9F37736, 0x2A, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok493) {
    // 153381.047
    int f = 1209387331;
    // 153381
    s21_decimal decimal_check = {{0x25725, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok494) {
    // -153381.047
    int f = -938096317;
    // -153381
    s21_decimal decimal_check = {{0x25725, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok495) {
    // 0.0415133908
    int f = 1026165234;
    // 0.04151339
    s21_decimal decimal_check = {{0x3F582B, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok496) {
    // -0.0415133908
    int f = -1121318414;
    // -0.04151339
    s21_decimal decimal_check = {{0x3F582B, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok497) {
    // 9.56585329E+10
    int f = 1370631563;
    // 95658530000
    s21_decimal decimal_check = {{0x45B154D0, 0x16, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok498) {
    // -9.56585329E+10
    int f = -776852085;
    // -95658530000
    s21_decimal decimal_check = {{0x45B154D0, 0x16, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok499) {
    // 2.08391936E+22
    int f = 1686976061;
    // 20839190000000000000000
    s21_decimal decimal_check = {{0x488F0000, 0xB1DB5E3D, 0x469, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok500) {
    // -2.08391936E+22
    int f = -460507587;
    // -20839190000000000000000
    s21_decimal decimal_check = {{0x488F0000, 0xB1DB5E3D, 0x469, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok501) {
    // 7.7588598E-20
    int f = 532099950;
    // 0.0000000000000000000775886
    s21_decimal decimal_check = {{0xBD6CE, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok502) {
    // -7.7588598E-20
    int f = -1615383698;
    // -0.0000000000000000000775886
    s21_decimal decimal_check = {{0xBD6CE, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok503) {
    // 7.65994465E+14
    int f = 1479420607;
    // 765994500000000
    s21_decimal decimal_check = {{0xFE128900, 0x2B8AA, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok504) {
    // -7.65994465E+14
    int f = -668063041;
    // -765994500000000
    s21_decimal decimal_check = {{0xFE128900, 0x2B8AA, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok505) {
    // 1.49214613E+15
    int f = 1487512363;
    // 1492146000000000
    s21_decimal decimal_check = {{0x50487400, 0x54D19, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok506) {
    // -1.49214613E+15
    int f = -659971285;
    // -1492146000000000
    s21_decimal decimal_check = {{0x50487400, 0x54D19, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok507) {
    // 2.64035748E-24
    int f = 407652779;
    // 0.0000000000000000000000026404
    s21_decimal decimal_check = {{0x6724, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok508) {
    // -2.64035748E-24
    int f = -1739830869;
    // -0.0000000000000000000000026404
    s21_decimal decimal_check = {{0x6724, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok509) {
    // 4.43193314E-28
    int f = 302806045;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok510) {
    // -4.43193314E-28
    int f = -1844677603;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok511) {
    // 4.76799009E-24
    int f = 414741475;
    // 0.000000000000000000000004768
    s21_decimal decimal_check = {{0x12A0, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok512) {
    // -4.76799009E-24
    int f = -1732742173;
    // -0.000000000000000000000004768
    s21_decimal decimal_check = {{0x12A0, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok513) {
    // 2.2489281E-18
    int f = 572911885;
    // 0.000000000000000002248928
    s21_decimal decimal_check = {{0x2250E0, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok514) {
    // -2.2489281E-18
    int f = -1574571763;
    // -0.000000000000000002248928
    s21_decimal decimal_check = {{0x2250E0, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok515) {
    // 0.549742341
    int f = 1057799146;
    // 0.5497423
    s21_decimal decimal_check = {{0x53E24F, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok516) {
    // -0.549742341
    int f = -1089684502;
    // -0.5497423
    s21_decimal decimal_check = {{0x53E24F, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok517) {
    // 1.11953749E-27
    int f = 313615830;
    // 0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok518) {
    // -1.11953749E-27
    int f = -1833867818;
    // -0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok519) {
    // 5.9266193E+23
    int f = 1727725705;
    // 592661900000000000000000
    s21_decimal decimal_check = {{0x510E0000, 0x441708AD, 0x7D80, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok520) {
    // -5.9266193E+23
    int f = -419757943;
    // -592661900000000000000000
    s21_decimal decimal_check = {{0x510E0000, 0x441708AD, 0x7D80, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok521) {
    // 4.46835452E+27
    int f = 1835467310;
    // 4468355000000000000000000000
    s21_decimal decimal_check = {{0xABE00000, 0xEBFC9CC1, 0xE7022F9, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok522) {
    // -4.46835452E+27
    int f = -312016338;
    // -4468355000000000000000000000
    s21_decimal decimal_check = {{0xABE00000, 0xEBFC9CC1, 0xE7022F9, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok523) {
    // 7.5274607E+17
    int f = 1562846377;
    // 752746100000000000
    s21_decimal decimal_check = {{0xF88F8800, 0xA724A96, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok524) {
    // -7.5274607E+17
    int f = -584637271;
    // -752746100000000000
    s21_decimal decimal_check = {{0xF88F8800, 0xA724A96, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok525) {
    // 2.90388188E+15
    int f = 1495601419;
    // 2903882000000000
    s21_decimal decimal_check = {{0xB7146400, 0xA5110, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok526) {
    // -2.90388188E+15
    int f = -651882229;
    // -2903882000000000
    s21_decimal decimal_check = {{0xB7146400, 0xA5110, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok527) {
    // 1.46925811E+15
    int f = 1487341834;
    // 1469258000000000
    s21_decimal decimal_check = {{0x492C6400, 0x53848, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok528) {
    // -1.46925811E+15
    int f = -660141814;
    // -1469258000000000
    s21_decimal decimal_check = {{0x492C6400, 0x53848, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok529) {
    // 713036.25
    int f = 1227756740;
    // 713036.2
    s21_decimal decimal_check = {{0x6CCCFA, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok530) {
    // -713036.25
    int f = -919726908;
    // -713036.2
    s21_decimal decimal_check = {{0x6CCCFA, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok531) {
    // 5.8242018E-05
    int f = 947144932;
    // 0.00005824202
    s21_decimal decimal_check = {{0x58DECA, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok532) {
    // -5.8242018E-05
    int f = -1200338716;
    // -0.00005824202
    s21_decimal decimal_check = {{0x58DECA, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok533) {
    // 1.04631354E-07
    int f = 870363570;
    // 0.0000001046314
    s21_decimal decimal_check = {{0xFF72A, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok534) {
    // -1.04631354E-07
    int f = -1277120078;
    // -0.0000001046314
    s21_decimal decimal_check = {{0xFF72A, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok535) {
    // 1.02448827E-09
    int f = 814534138;
    // 0.000000001024488
    s21_decimal decimal_check = {{0xFA1E8, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok536) {
    // -1.02448827E-09
    int f = -1332949510;
    // -0.000000001024488
    s21_decimal decimal_check = {{0xFA1E8, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok537) {
    // 4.06299782
    int f = 1082262548;
    // 4.062998
    s21_decimal decimal_check = {{0x3DFF16, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok538) {
    // -4.06299782
    int f = -1065221100;
    // -4.062998
    s21_decimal decimal_check = {{0x3DFF16, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok539) {
    // 1.79904282E+09
    int f = 1322677870;
    // 1799043000
    s21_decimal decimal_check = {{0x6B3B37B8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok540) {
    // -1.79904282E+09
    int f = -824805778;
    // -1799043000
    s21_decimal decimal_check = {{0x6B3B37B8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok541) {
    // 1.76664872E-18
    int f = 570579725;
    // 0.000000000000000001766649
    s21_decimal decimal_check = {{0x1AF4F9, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok542) {
    // -1.76664872E-18
    int f = -1576903923;
    // -0.000000000000000001766649
    s21_decimal decimal_check = {{0x1AF4F9, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok543) {
    // 7.33048273E+19
    int f = 1618891716;
    // 73304830000000000000
    s21_decimal decimal_check = {{0xD665E000, 0xF94F127F, 0x3, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok544) {
    // -7.33048273E+19
    int f = -528591932;
    // -73304830000000000000
    s21_decimal decimal_check = {{0xD665E000, 0xF94F127F, 0x3, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok545) {
    // 0.000110643683
    int f = 954730848;
    // 0.0001106437
    s21_decimal decimal_check = {{0x10E205, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok546) {
    // -0.000110643683
    int f = -1192752800;
    // -0.0001106437
    s21_decimal decimal_check = {{0x10E205, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok547) {
    // 6.501423E-19
    int f = 557835101;
    // 0.0000000000000000006501423
    s21_decimal decimal_check = {{0x63342F, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok548) {
    // -6.501423E-19
    int f = -1589648547;
    // -0.0000000000000000006501423
    s21_decimal decimal_check = {{0x63342F, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok549) {
    // 7.88272731E-23
    int f = 448698296;
    // 0.0000000000000000000000788273
    s21_decimal decimal_check = {{0xC0731, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok550) {
    // -7.88272731E-23
    int f = -1698785352;
    // -0.0000000000000000000000788273
    s21_decimal decimal_check = {{0xC0731, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok551) {
    // 1.92116916E+11
    int f = 1379068990;
    // 192116900000
    s21_decimal decimal_check = {{0xBB0F40A0, 0x2C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok552) {
    // -1.92116916E+11
    int f = -768414658;
    // -192116900000
    s21_decimal decimal_check = {{0xBB0F40A0, 0x2C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok553) {
    // 9.57687705E-13
    int f = 730253398;
    // 0.0000000000009576877
    s21_decimal decimal_check = {{0x9221AD, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok554) {
    // -9.57687705E-13
    int f = -1417230250;
    // -0.0000000000009576877
    s21_decimal decimal_check = {{0x9221AD, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok555) {
    // 2.41148923E-09
    int f = 824555358;
    // 0.000000002411489
    s21_decimal decimal_check = {{0x24CBE1, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok556) {
    // -2.41148923E-09
    int f = -1322928290;
    // -0.000000002411489
    s21_decimal decimal_check = {{0x24CBE1, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok557) {
    // 7.98004024E-13
    int f = 727752256;
    // 0.000000000000798004
    s21_decimal decimal_check = {{0xC2D34, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok558) {
    // -7.98004024E-13
    int f = -1419731392;
    // -0.000000000000798004
    s21_decimal decimal_check = {{0xC2D34, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok559) {
    // 7.73027191E+26
    int f = 1814027192;
    // 773027200000000000000000000
    s21_decimal decimal_check = {{0x66000000, 0x7B44D9C0, 0x27F6EE0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok560) {
    // -7.73027191E+26
    int f = -333456456;
    // -773027200000000000000000000
    s21_decimal decimal_check = {{0x66000000, 0x7B44D9C0, 0x27F6EE0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok561) {
    // 2.32255222E-11
    int f = 768363322;
    // 0.00000000002322552
    s21_decimal decimal_check = {{0x237078, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok562) {
    // -2.32255222E-11
    int f = -1379120326;
    // -0.00000000002322552
    s21_decimal decimal_check = {{0x237078, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok563) {
    // 2.08913693E-22
    int f = 461148072;
    // 0.0000000000000000000002089137
    s21_decimal decimal_check = {{0x1FE0B1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok564) {
    // -2.08913693E-22
    int f = -1686335576;
    // -0.0000000000000000000002089137
    s21_decimal decimal_check = {{0x1FE0B1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok565) {
    // 1.23324259E+26
    int f = 1791755739;
    // 123324300000000000000000000
    s21_decimal decimal_check = {{0x46B00000, 0xB2F27F22, 0x6602EF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok566) {
    // -1.23324259E+26
    int f = -355727909;
    // -123324300000000000000000000
    s21_decimal decimal_check = {{0x46B00000, 0xB2F27F22, 0x6602EF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok567) {
    // 1.18372413E+15
    int f = 1485214440;
    // 1183724000000000
    s21_decimal decimal_check = {{0x38883800, 0x43497, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok568) {
    // -1.18372413E+15
    int f = -662269208;
    // -1183724000000000
    s21_decimal decimal_check = {{0x38883800, 0x43497, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok569) {
    // 1.66317729E-19
    int f = 541350515;
    // 0.0000000000000000001663177
    s21_decimal decimal_check = {{0x1960C9, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok570) {
    // -1.66317729E-19
    int f = -1606133133;
    // -0.0000000000000000001663177
    s21_decimal decimal_check = {{0x1960C9, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok571) {
    // 0.100124776
    int f = 1036848696;
    // 0.1001248
    s21_decimal decimal_check = {{0xF4720, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok572) {
    // -0.100124776
    int f = -1110634952;
    // -0.1001248
    s21_decimal decimal_check = {{0xF4720, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok573) {
    // 1.35799399E+23
    int f = 1709575578;
    // 135799400000000000000000
    s21_decimal decimal_check = {{0x4DA40000, 0xB341F3F1, 0x1CC1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok574) {
    // -1.35799399E+23
    int f = -437908070;
    // -135799400000000000000000
    s21_decimal decimal_check = {{0x4DA40000, 0xB341F3F1, 0x1CC1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok575) {
    // 1.07895064E-11
    int f = 759025566;
    // 0.00000000001078951
    s21_decimal decimal_check = {{0x1076A7, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok576) {
    // -1.07895064E-11
    int f = -1388458082;
    // -0.00000000001078951
    s21_decimal decimal_check = {{0x1076A7, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok577) {
    // 7.80018328E-10
    int f = 810969321;
    // 0.0000000007800183
    s21_decimal decimal_check = {{0x770577, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok578) {
    // -7.80018328E-10
    int f = -1336514327;
    // -0.0000000007800183
    s21_decimal decimal_check = {{0x770577, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok579) {
    // 1.23435862E-13
    int f = 705362423;
    // 0.0000000000001234359
    s21_decimal decimal_check = {{0x12D5B7, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok580) {
    // -1.23435862E-13
    int f = -1442121225;
    // -0.0000000000001234359
    s21_decimal decimal_check = {{0x12D5B7, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok581) {
    // 6.03709877E+26
    int f = 1811525701;
    // 603709900000000000000000000
    s21_decimal decimal_check = {{0x47B00000, 0x41AD4854, 0x1F3608B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok582) {
    // -6.03709877E+26
    int f = -335957947;
    // -603709900000000000000000000
    s21_decimal decimal_check = {{0x47B00000, 0x41AD4854, 0x1F3608B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok583) {
    // 3.57412189E+12
    int f = 1414531729;
    // 3574122000000
    s21_decimal decimal_check = {{0x2A45AE80, 0x340, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok584) {
    // -3.57412189E+12
    int f = -732951919;
    // -3574122000000
    s21_decimal decimal_check = {{0x2A45AE80, 0x340, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok585) {
    // 2.9881089E-18
    int f = 576486344;
    // 0.000000000000000002988109
    s21_decimal decimal_check = {{0x2D984D, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok586) {
    // -2.9881089E-18
    int f = -1570997304;
    // -0.000000000000000002988109
    s21_decimal decimal_check = {{0x2D984D, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok587) {
    // 2.29112028E-23
    int f = 433952100;
    // 0.0000000000000000000000229112
    s21_decimal decimal_check = {{0x37EF8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok588) {
    // -2.29112028E-23
    int f = -1713531548;
    // -0.0000000000000000000000229112
    s21_decimal decimal_check = {{0x37EF8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok589) {
    // 4.63169801E+19
    int f = 1612755390;
    // 46316980000000000000
    s21_decimal decimal_check = {{0x80DF4000, 0x82C6F7E9, 0x2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok590) {
    // -4.63169801E+19
    int f = -534728258;
    // -46316980000000000000
    s21_decimal decimal_check = {{0x80DF4000, 0x82C6F7E9, 0x2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok591) {
    // 4.15000939E-18
    int f = 580459451;
    // 0.000000000000000004150009
    s21_decimal decimal_check = {{0x3F52F9, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok592) {
    // -4.15000939E-18
    int f = -1567024197;
    // -0.000000000000000004150009
    s21_decimal decimal_check = {{0x3F52F9, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok593) {
    // 4.49235487E+15
    int f = 1501518942;
    // 4492355000000000
    s21_decimal decimal_check = {{0xE7FADE00, 0xFF5C5, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok594) {
    // -4.49235487E+15
    int f = -645964706;
    // -4492355000000000
    s21_decimal decimal_check = {{0xE7FADE00, 0xFF5C5, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok595) {
    // 2.43170365E+15
    int f = 1493842418;
    // 2431704000000000
    s21_decimal decimal_check = {{0x351E7000, 0x8A39F, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok596) {
    // -2.43170365E+15
    int f = -653641230;
    // -2431704000000000
    s21_decimal decimal_check = {{0x351E7000, 0x8A39F, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok597) {
    // 91427.2813
    int f = 1202885028;
    // 91427.28
    s21_decimal decimal_check = {{0x8B81C8, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok598) {
    // -91427.2813
    int f = -944598620;
    // -91427.28
    s21_decimal decimal_check = {{0x8B81C8, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok599) {
    // 1.61482719E+11
    int f = 1377199227;
    // 161482700000
    s21_decimal decimal_check = {{0x991E74E0, 0x25, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok600) {
    // -1.61482719E+11
    int f = -770284421;
    // -161482700000
    s21_decimal decimal_check = {{0x991E74E0, 0x25, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok601) {
    // 3.81807017E-11
    int f = 774368166;
    // 0.0000000000381807
    s21_decimal decimal_check = {{0x5D36F, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok602) {
    // -3.81807017E-11
    int f = -1373115482;
    // -0.0000000000381807
    s21_decimal decimal_check = {{0x5D36F, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok603) {
    // 1.48595707E-24
    int f = 400945363;
    // 0.000000000000000000000001486
    s21_decimal decimal_check = {{0x5CE, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok604) {
    // -1.48595707E-24
    int f = -1746538285;
    // -0.000000000000000000000001486
    s21_decimal decimal_check = {{0x5CE, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok605) {
    // 2.33944506E+15
    int f = 1493498728;
    // 2339445000000000
    s21_decimal decimal_check = {{0x7C325200, 0x84FB6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok606) {
    // -2.33944506E+15
    int f = -653984920;
    // -2339445000000000
    s21_decimal decimal_check = {{0x7C325200, 0x84FB6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok607) {
    // 2.66143914E+19
    int f = 1605938344;
    // 26614390000000000000
    s21_decimal decimal_check = {{0x27B56000, 0x71594EB2, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok608) {
    // -2.66143914E+19
    int f = -541545304;
    // -26614390000000000000
    s21_decimal decimal_check = {{0x27B56000, 0x71594EB2, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok609) {
    // 57.9538345
    int f = 1114099898;
    // 57.95383
    s21_decimal decimal_check = {{0x586E37, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok610) {
    // -57.9538345
    int f = -1033383750;
    // -57.95383
    s21_decimal decimal_check = {{0x586E37, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok611) {
    // 4.9575518E-22
    int f = 471192883;
    // 0.0000000000000000000004957552
    s21_decimal decimal_check = {{0x4BA570, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok612) {
    // -4.9575518E-22
    int f = -1676290765;
    // -0.0000000000000000000004957552
    s21_decimal decimal_check = {{0x4BA570, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok613) {
    // 3.45355434E-20
    int f = 522393321;
    // 0.00000000000000000003453554
    s21_decimal decimal_check = {{0x34B272, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok614) {
    // -3.45355434E-20
    int f = -1625090327;
    // -0.00000000000000000003453554
    s21_decimal decimal_check = {{0x34B272, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok615) {
    // 1.1843942E-05
    int f = 927380824;
    // 0.00001184394
    s21_decimal decimal_check = {{0x12128A, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok616) {
    // -1.1843942E-05
    int f = -1220102824;
    // -0.00001184394
    s21_decimal decimal_check = {{0x12128A, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok617) {
    // 3.30246499E+16
    int f = 1525327741;
    // 33024650000000000
    s21_decimal decimal_check = {{0x8414E400, 0x7553BE, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok618) {
    // -3.30246499E+16
    int f = -622155907;
    // -33024650000000000
    s21_decimal decimal_check = {{0x8414E400, 0x7553BE, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok619) {
    // 1.20761675E-21
    int f = 481721705;
    // 0.000000000000000000001207617
    s21_decimal decimal_check = {{0x126D41, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok620) {
    // -1.20761675E-21
    int f = -1665761943;
    // -0.000000000000000000001207617
    s21_decimal decimal_check = {{0x126D41, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok621) {
    // 2336837.75
    int f = 1242472727;
    // 2336838
    s21_decimal decimal_check = {{0x23A846, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok622) {
    // -2336837.75
    int f = -905010921;
    // -2336838
    s21_decimal decimal_check = {{0x23A846, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok623) {
    // 463857440
    int f = 1306341177;
    // 463857400
    s21_decimal decimal_check = {{0x1BA5E6F8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok624) {
    // -463857440
    int f = -841142471;
    // -463857400
    s21_decimal decimal_check = {{0x1BA5E6F8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok625) {
    // 3.46025978E-27
    int f = 327750452;
    // 0.0000000000000000000000000035
    s21_decimal decimal_check = {{0x23, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok626) {
    // -3.46025978E-27
    int f = -1819733196;
    // -0.0000000000000000000000000035
    s21_decimal decimal_check = {{0x23, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok627) {
    // 1.37485124E+20
    int f = 1626242985;
    // 137485100000000000000
    s21_decimal decimal_check = {{0xD10EC000, 0x73FD3205, 0x7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok628) {
    // -1.37485124E+20
    int f = -521240663;
    // -137485100000000000000
    s21_decimal decimal_check = {{0xD10EC000, 0x73FD3205, 0x7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok629) {
    // 0.000133197187
    int f = 957065945;
    // 0.0001331972
    s21_decimal decimal_check = {{0x145304, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok630) {
    // -0.000133197187
    int f = -1190417703;
    // -0.0001331972
    s21_decimal decimal_check = {{0x145304, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok631) {
    // 2.14111109E+11
    int f = 1380411409;
    // 214111100000
    s21_decimal decimal_check = {{0xDA041C60, 0x31, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok632) {
    // -2.14111109E+11
    int f = -767072239;
    // -214111100000
    s21_decimal decimal_check = {{0xDA041C60, 0x31, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok633) {
    // 3.08834099E+09
    int f = 1329075288;
    // 3088341000
    s21_decimal decimal_check = {{0xB8145808, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok634) {
    // -3.08834099E+09
    int f = -818408360;
    // -3088341000
    s21_decimal decimal_check = {{0xB8145808, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok635) {
    // 1.13243857E+18
    int f = 1568371630;
    // 1132439000000000000
    s21_decimal decimal_check = {{0x44CC7000, 0xFB73B45, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok636) {
    // -1.13243857E+18
    int f = -579112018;
    // -1132439000000000000
    s21_decimal decimal_check = {{0x44CC7000, 0xFB73B45, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok637) {
    // 9.13816111E-05
    int f = 952083489;
    // 0.00009138161
    s21_decimal decimal_check = {{0x8B6FF1, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok638) {
    // -9.13816111E-05
    int f = -1195400159;
    // -0.00009138161
    s21_decimal decimal_check = {{0x8B6FF1, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok639) {
    // 7.17742002E+24
    int f = 1757281303;
    // 7177420000000000000000000
    s21_decimal decimal_check = {{0xF3B00000, 0xB7C47F0C, 0x5EFE0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok640) {
    // -7.17742002E+24
    int f = -390202345;
    // -7177420000000000000000000
    s21_decimal decimal_check = {{0xF3B00000, 0xB7C47F0C, 0x5EFE0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok641) {
    // 4.27809455E-10
    int f = 803942612;
    // 0.0000000004278095
    s21_decimal decimal_check = {{0x41474F, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok642) {
    // -4.27809455E-10
    int f = -1343541036;
    // -0.0000000004278095
    s21_decimal decimal_check = {{0x41474F, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok643) {
    // 9.43891319E+21
    int f = 1677711262;
    // 9438913000000000000000
    s21_decimal decimal_check = {{0xE0A68000, 0xAF3B53FE, 0x1FF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok644) {
    // -9.43891319E+21
    int f = -469772386;
    // -9438913000000000000000
    s21_decimal decimal_check = {{0xE0A68000, 0xAF3B53FE, 0x1FF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok645) {
    // 6.63623162E+17
    int f = 1561549468;
    // 663623200000000000
    s21_decimal decimal_check = {{0xCCB54000, 0x935A9C8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok646) {
    // -6.63623162E+17
    int f = -585934180;
    // -663623200000000000
    s21_decimal decimal_check = {{0xCCB54000, 0x935A9C8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok647) {
    // 1.71251152E-25
    int f = 374603688;
    // 0.0000000000000000000000001713
    s21_decimal decimal_check = {{0x6B1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok648) {
    // -1.71251152E-25
    int f = -1772879960;
    // -0.0000000000000000000000001713
    s21_decimal decimal_check = {{0x6B1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok649) {
    // 1.45104063
    int f = 1069136819;
    // 1.451041
    s21_decimal decimal_check = {{0x162421, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok650) {
    // -1.45104063
    int f = -1078346829;
    // -1.451041
    s21_decimal decimal_check = {{0x162421, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok651) {
    // 5.09009881E-13
    int f = 722421255;
    // 0.0000000000005090099
    s21_decimal decimal_check = {{0x4DAB33, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok652) {
    // -5.09009881E-13
    int f = -1425062393;
    // -0.0000000000005090099
    s21_decimal decimal_check = {{0x4DAB33, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok653) {
    // 0.248830885
    int f = 1048497542;
    // 0.2488309
    s21_decimal decimal_check = {{0x25F7F5, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok654) {
    // -0.248830885
    int f = -1098986106;
    // -0.2488309
    s21_decimal decimal_check = {{0x25F7F5, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok655) {
    // 2.45017198E-20
    int f = 518482310;
    // 0.00000000000000000002450172
    s21_decimal decimal_check = {{0x2562FC, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok656) {
    // -2.45017198E-20
    int f = -1629001338;
    // -0.00000000000000000002450172
    s21_decimal decimal_check = {{0x2562FC, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok657) {
    // 6.67443312E-21
    int f = 503064360;
    // 0.000000000000000000006674433
    s21_decimal decimal_check = {{0x65D801, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok658) {
    // -6.67443312E-21
    int f = -1644419288;
    // -0.000000000000000000006674433
    s21_decimal decimal_check = {{0x65D801, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok659) {
    // 4.48200389E+12
    int f = 1417834888;
    // 4482004000000
    s21_decimal decimal_check = {{0x8C419D00, 0x413, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok660) {
    // -4.48200389E+12
    int f = -729648760;
    // -4482004000000
    s21_decimal decimal_check = {{0x8C419D00, 0x413, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok661) {
    // 1.98628354E+13
    int f = 1435534698;
    // 19862840000000
    s21_decimal decimal_check = {{0xAD85BE00, 0x1210, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok662) {
    // -1.98628354E+13
    int f = -711948950;
    // -19862840000000
    s21_decimal decimal_check = {{0xAD85BE00, 0x1210, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok663) {
    // 1.97829059E-10
    int f = 794395630;
    // 0.0000000001978291
    s21_decimal decimal_check = {{0x1E2FB3, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok664) {
    // -1.97829059E-10
    int f = -1353088018;
    // -0.0000000001978291
    s21_decimal decimal_check = {{0x1E2FB3, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok665) {
    // 13318.8164
    int f = 1179654980;
    // 13318.82
    s21_decimal decimal_check = {{0x1452AA, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok666) {
    // -13318.8164
    int f = -967828668;
    // -13318.82
    s21_decimal decimal_check = {{0x1452AA, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok667) {
    // 1.24562382E-06
    int f = 900149071;
    // 0.000001245624
    s21_decimal decimal_check = {{0x1301B8, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok668) {
    // -1.24562382E-06
    int f = -1247334577;
    // -0.000001245624
    s21_decimal decimal_check = {{0x1301B8, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok669) {
    // 0.10395357
    int f = 1037362588;
    // 0.1039536
    s21_decimal decimal_check = {{0xFDCB0, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok670) {
    // -0.10395357
    int f = -1110121060;
    // -0.1039536
    s21_decimal decimal_check = {{0xFDCB0, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok671) {
    // 7.88859981E-26
    int f = 365121521;
    // 0.0000000000000000000000000789
    s21_decimal decimal_check = {{0x315, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok672) {
    // -7.88859981E-26
    int f = -1782362127;
    // -0.0000000000000000000000000789
    s21_decimal decimal_check = {{0x315, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok673) {
    // 2.25033613E-20
    int f = 517245386;
    // 0.00000000000000000002250336
    s21_decimal decimal_check = {{0x225660, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok674) {
    // -2.25033613E-20
    int f = -1630238262;
    // -0.00000000000000000002250336
    s21_decimal decimal_check = {{0x225660, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok675) {
    // 2.26964084E+24
    int f = 1743802045;
    // 2269641000000000000000000
    s21_decimal decimal_check = {{0x51840000, 0x7C32AA9C, 0x1E09D, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok676) {
    // -2.26964084E+24
    int f = -403681603;
    // -2269641000000000000000000
    s21_decimal decimal_check = {{0x51840000, 0x7C32AA9C, 0x1E09D, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok677) {
    // 2.03335899E-25
    int f = 377206712;
    // 0.0000000000000000000000002033
    s21_decimal decimal_check = {{0x7F1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok678) {
    // -2.03335899E-25
    int f = -1770276936;
    // -0.0000000000000000000000002033
    s21_decimal decimal_check = {{0x7F1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok679) {
    // 8.0404541E+19
    int f = 1619753674;
    // 80404540000000000000
    s21_decimal decimal_check = {{0xE4AFC000, 0x5BD64F20, 0x4, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok680) {
    // -8.0404541E+19
    int f = -527729974;
    // -80404540000000000000
    s21_decimal decimal_check = {{0xE4AFC000, 0x5BD64F20, 0x4, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok681) {
    // 7.14287988E-21
    int f = 503770329;
    // 0.00000000000000000000714288
    s21_decimal decimal_check = {{0xAE630, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok682) {
    // -7.14287988E-21
    int f = -1643713319;
    // -0.00000000000000000000714288
    s21_decimal decimal_check = {{0xAE630, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok683) {
    // 5.73672637E-11
    int f = 779898316;
    // 0.00000000005736726
    s21_decimal decimal_check = {{0x578916, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok684) {
    // -5.73672637E-11
    int f = -1367585332;
    // -0.00000000005736726
    s21_decimal decimal_check = {{0x578916, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok685) {
    // 3.20352939E-10
    int f = 800071083;
    // 0.0000000003203529
    s21_decimal decimal_check = {{0x30E1C9, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok686) {
    // -3.20352939E-10
    int f = -1347412565;
    // -0.0000000003203529
    s21_decimal decimal_check = {{0x30E1C9, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok687) {
    // 3.19178245E-27
    int f = 326951178;
    // 0.0000000000000000000000000032
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok688) {
    // -3.19178245E-27
    int f = -1820532470;
    // -0.0000000000000000000000000032
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok689) {
    // 0.0530532971
    int f = 1029262954;
    // 0.0530533
    s21_decimal decimal_check = {{0x81865, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok690) {
    // -0.0530532971
    int f = -1118220694;
    // -0.0530533
    s21_decimal decimal_check = {{0x81865, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok691) {
    // 1.32064732E-20
    int f = 511276694;
    // 0.00000000000000000001320647
    s21_decimal decimal_check = {{0x1426C7, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok692) {
    // -1.32064732E-20
    int f = -1636206954;
    // -0.00000000000000000001320647
    s21_decimal decimal_check = {{0x1426C7, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok693) {
    // 2.56133413
    int f = 1076096230;
    // 2.561334
    s21_decimal decimal_check = {{0x271536, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok694) {
    // -2.56133413
    int f = -1071387418;
    // -2.561334
    s21_decimal decimal_check = {{0x271536, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok695) {
    // 2.14875318E-20
    int f = 516616618;
    // 0.00000000000000000002148753
    s21_decimal decimal_check = {{0x20C991, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok696) {
    // -2.14875318E-20
    int f = -1630867030;
    // -0.00000000000000000002148753
    s21_decimal decimal_check = {{0x20C991, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok697) {
    // 0.0853883401
    int f = 1034870805;
    // 0.08538834
    s21_decimal decimal_check = {{0x824AD2, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok698) {
    // -0.0853883401
    int f = -1112612843;
    // -0.08538834
    s21_decimal decimal_check = {{0x824AD2, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok699) {
    // 1.10161521E+26
    int f = 1790328632;
    // 110161500000000000000000000
    s21_decimal decimal_check = {{0x1FF00000, 0xE1972E6F, 0x5B1F9A, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok700) {
    // -1.10161521E+26
    int f = -357155016;
    // -110161500000000000000000000
    s21_decimal decimal_check = {{0x1FF00000, 0xE1972E6F, 0x5B1F9A, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok701) {
    // 6.91172286E-10
    int f = 809368813;
    // 0.0000000006911723
    s21_decimal decimal_check = {{0x6976EB, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok702) {
    // -6.91172286E-10
    int f = -1338114835;
    // -0.0000000006911723
    s21_decimal decimal_check = {{0x6976EB, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok703) {
    // 1.97796062E+15
    int f = 1491131963;
    // 1977961000000000
    s21_decimal decimal_check = {{0xEEC8DA00, 0x706F1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok704) {
    // -1.97796062E+15
    int f = -656351685;
    // -1977961000000000
    s21_decimal decimal_check = {{0xEEC8DA00, 0x706F1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok705) {
    // 1.41915604E-19
    int f = 539462492;
    // 0.0000000000000000001419156
    s21_decimal decimal_check = {{0x15A794, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok706) {
    // -1.41915604E-19
    int f = -1608021156;
    // -0.0000000000000000001419156
    s21_decimal decimal_check = {{0x15A794, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok707) {
    // 0.00639475463
    int f = 1003588375;
    // 0.006394755
    s21_decimal decimal_check = {{0x619383, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok708) {
    // -0.00639475463
    int f = -1143895273;
    // -0.006394755
    s21_decimal decimal_check = {{0x619383, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok709) {
    // 3.6906487E-18
    int f = 579348785;
    // 0.000000000000000003690649
    s21_decimal decimal_check = {{0x385099, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok710) {
    // -3.6906487E-18
    int f = -1568134863;
    // -0.000000000000000003690649
    s21_decimal decimal_check = {{0x385099, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok711) {
    // 3.69252917E-15
    int f = 663030162;
    // 0.000000000000003692529
    s21_decimal decimal_check = {{0x3857F1, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok712) {
    // -3.69252917E-15
    int f = -1484453486;
    // -0.000000000000003692529
    s21_decimal decimal_check = {{0x3857F1, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok713) {
    // 5.67219439E-25
    int f = 388991937;
    // 0.0000000000000000000000005672
    s21_decimal decimal_check = {{0x1628, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok714) {
    // -5.67219439E-25
    int f = -1758491711;
    // -0.0000000000000000000000005672
    s21_decimal decimal_check = {{0x1628, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok715) {
    // 141.942535
    int f = 1124987210;
    // 141.9425
    s21_decimal decimal_check = {{0x15A8A1, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok716) {
    // -141.942535
    int f = -1022496438;
    // -141.9425
    s21_decimal decimal_check = {{0x15A8A1, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok717) {
    // 9.31314315E-20
    int f = 534505087;
    // 0.00000000000000000009313143
    s21_decimal decimal_check = {{0x8E1B77, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok718) {
    // -9.31314315E-20
    int f = -1612978561;
    // -0.00000000000000000009313143
    s21_decimal decimal_check = {{0x8E1B77, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok719) {
    // 5.86461137E-25
    int f = 389382205;
    // 0.0000000000000000000000005865
    s21_decimal decimal_check = {{0x16E9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok720) {
    // -5.86461137E-25
    int f = -1758101443;
    // -0.0000000000000000000000005865
    s21_decimal decimal_check = {{0x16E9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok721) {
    // 0.00372297852
    int f = 997457207;
    // 0.003722979
    s21_decimal decimal_check = {{0x38CEE3, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok722) {
    // -0.00372297852
    int f = -1150026441;
    // -0.003722979
    s21_decimal decimal_check = {{0x38CEE3, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok723) {
    // 1.37482673E+18
    int f = 1570284269;
    // 1374827000000000000
    s21_decimal decimal_check = {{0x529DB000, 0x13145DDF, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok724) {
    // -1.37482673E+18
    int f = -577199379;
    // -1374827000000000000
    s21_decimal decimal_check = {{0x529DB000, 0x13145DDF, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok725) {
    // 8.66029961E-24
    int f = 422020026;
    // 0.0000000000000000000000086603
    s21_decimal decimal_check = {{0x1524B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok726) {
    // -8.66029961E-24
    int f = -1725463622;
    // -0.0000000000000000000000086603
    s21_decimal decimal_check = {{0x1524B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok727) {
    // 3.63714309E+21
    int f = 1665477504;
    // 3637143000000000000000
    s21_decimal decimal_check = {{0x2A958000, 0x2B7FB017, 0xC5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok728) {
    // -3.63714309E+21
    int f = -482006144;
    // -3637143000000000000000
    s21_decimal decimal_check = {{0x2A958000, 0x2B7FB017, 0xC5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok729) {
    // 1.41952283E-17
    int f = 595783049;
    // 0.00000000000000001419523
    s21_decimal decimal_check = {{0x15A903, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok730) {
    // -1.41952283E-17
    int f = -1551700599;
    // -0.00000000000000001419523
    s21_decimal decimal_check = {{0x15A903, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok731) {
    // 6.04143949E-23
    int f = 445780659;
    // 0.0000000000000000000000604144
    s21_decimal decimal_check = {{0x937F0, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok732) {
    // -6.04143949E-23
    int f = -1701702989;
    // -0.0000000000000000000000604144
    s21_decimal decimal_check = {{0x937F0, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok733) {
    // 1.72688895E+22
    int f = 1684670847;
    // 17268890000000000000000
    s21_decimal decimal_check = {{0xDF690000, 0x25FDB87F, 0x3A8, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok734) {
    // -1.72688895E+22
    int f = -462812801;
    // -17268890000000000000000
    s21_decimal decimal_check = {{0xDF690000, 0x25FDB87F, 0x3A8, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok735) {
    // 0.00291212997
    int f = 993974639;
    // 0.00291213
    s21_decimal decimal_check = {{0x4718D, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok736) {
    // -0.00291212997
    int f = -1153509009;
    // -0.00291213
    s21_decimal decimal_check = {{0x4718D, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok737) {
    // 6.68304653E-18
    int f = 586583959;
    // 0.000000000000000006683047
    s21_decimal decimal_check = {{0x65F9A7, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok738) {
    // -6.68304653E-18
    int f = -1560899689;
    // -0.000000000000000006683047
    s21_decimal decimal_check = {{0x65F9A7, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok739) {
    // 8.96170288E-18
    int f = 589647986;
    // 0.000000000000000008961703
    s21_decimal decimal_check = {{0x88BEA7, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok740) {
    // -8.96170288E-18
    int f = -1557835662;
    // -0.000000000000000008961703
    s21_decimal decimal_check = {{0x88BEA7, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok741) {
    // 9.67771783E-08
    int f = 869258193;
    // 0.00000009677718
    s21_decimal decimal_check = {{0x93AB96, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok742) {
    // -9.67771783E-08
    int f = -1278225455;
    // -0.00000009677718
    s21_decimal decimal_check = {{0x93AB96, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok743) {
    // 1317.84827
    int f = 1151646501;
    // 1317.848
    s21_decimal decimal_check = {{0x141BD8, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok744) {
    // -1317.84827
    int f = -995837147;
    // -1317.848
    s21_decimal decimal_check = {{0x141BD8, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok745) {
    // 56497.5
    int f = 1197257088;
    // 56497.5
    s21_decimal decimal_check = {{0x89EEF, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok746) {
    // -56497.5
    int f = -950226560;
    // -56497.5
    s21_decimal decimal_check = {{0x89EEF, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok747) {
    // 5.40616441E-07
    int f = 890314465;
    // 0.0000005406164
    s21_decimal decimal_check = {{0x527DD4, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok748) {
    // -5.40616441E-07
    int f = -1257169183;
    // -0.0000005406164
    s21_decimal decimal_check = {{0x527DD4, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok749) {
    // 4850276
    int f = 1251214536;
    // 4850276
    s21_decimal decimal_check = {{0x4A0264, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok750) {
    // -4850276
    int f = -896269112;
    // -4850276
    s21_decimal decimal_check = {{0x4A0264, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok751) {
    // 7.34432536E+18
    int f = 1590417554;
    // 7344325000000000000
    s21_decimal decimal_check = {{0xF4055000, 0x65EC48AC, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok752) {
    // -7.34432536E+18
    int f = -557066094;
    // -7344325000000000000
    s21_decimal decimal_check = {{0xF4055000, 0x65EC48AC, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok753) {
    // 8.04129527E-08
    int f = 866955133;
    // 0.00000008041295
    s21_decimal decimal_check = {{0x7AB34F, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok754) {
    // -8.04129527E-08
    int f = -1280528515;
    // -0.00000008041295
    s21_decimal decimal_check = {{0x7AB34F, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok755) {
    // 1994211.5
    int f = 1240690460;
    // 1994212
    s21_decimal decimal_check = {{0x1E6DE4, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok756) {
    // -1994211.5
    int f = -906793188;
    // -1994212
    s21_decimal decimal_check = {{0x1E6DE4, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok757) {
    // 3.2134576E-06
    int f = 911713992;
    // 0.000003213458
    s21_decimal decimal_check = {{0x310892, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok758) {
    // -3.2134576E-06
    int f = -1235769656;
    // -0.000003213458
    s21_decimal decimal_check = {{0x310892, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok759) {
    // 1.0654259E-18
    int f = 563952295;
    // 0.000000000000000001065426
    s21_decimal decimal_check = {{0x1041D2, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok760) {
    // -1.0654259E-18
    int f = -1583531353;
    // -0.000000000000000001065426
    s21_decimal decimal_check = {{0x1041D2, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok761) {
    // 205114.672
    int f = 1212698283;
    // 205114.7
    s21_decimal decimal_check = {{0x1F4C4B, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok762) {
    // -205114.672
    int f = -934785365;
    // -205114.7
    s21_decimal decimal_check = {{0x1F4C4B, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok763) {
    // 6.13327929E-20
    int f = 529584486;
    // 0.00000000000000000006133279
    s21_decimal decimal_check = {{0x5D961F, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok764) {
    // -6.13327929E-20
    int f = -1617899162;
    // -0.00000000000000000006133279
    s21_decimal decimal_check = {{0x5D961F, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok765) {
    // 0.145992219
    int f = 1041596156;
    // 0.1459922
    s21_decimal decimal_check = {{0x1646D2, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok766) {
    // -0.145992219
    int f = -1105887492;
    // -0.1459922
    s21_decimal decimal_check = {{0x1646D2, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok767) {
    // 3.15027032E+27
    int f = 1831001467;
    // 3150270000000000000000000000
    s21_decimal decimal_check = {{0xDAC00000, 0xE552DAA3, 0xA2DD79E, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok768) {
    // -3.15027032E+27
    int f = -316482181;
    // -3150270000000000000000000000
    s21_decimal decimal_check = {{0xDAC00000, 0xE552DAA3, 0xA2DD79E, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok769) {
    // 3.50012179E-17
    int f = 606169637;
    // 0.00000000000000003500122
    s21_decimal decimal_check = {{0x35685A, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok770) {
    // -3.50012179E-17
    int f = -1541314011;
    // -0.00000000000000003500122
    s21_decimal decimal_check = {{0x35685A, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok771) {
    // 9.89470378E+15
    int f = 1510775993;
    // 9894704000000000
    s21_decimal decimal_check = {{0x4D13E000, 0x23272E, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok772) {
    // -9.89470378E+15
    int f = -636707655;
    // -9894704000000000
    s21_decimal decimal_check = {{0x4D13E000, 0x23272E, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok773) {
    // 3.45583812E+26
    int f = 1804529180;
    // 345583800000000000000000000
    s21_decimal decimal_check = {{0xFE00000, 0x5637DB47, 0x11DDC37, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok774) {
    // -3.45583812E+26
    int f = -342954468;
    // -345583800000000000000000000
    s21_decimal decimal_check = {{0xFE00000, 0x5637DB47, 0x11DDC37, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok775) {
    // 2.07332973E+24
    int f = 1742439863;
    // 2073330000000000000000000
    s21_decimal decimal_check = {{0x84880000, 0x71CBAADD, 0x1B70B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok776) {
    // -2.07332973E+24
    int f = -405043785;
    // -2073330000000000000000000
    s21_decimal decimal_check = {{0x84880000, 0x71CBAADD, 0x1B70B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok777) {
    // 3.18047301E-27
    int f = 326892456;
    // 0.0000000000000000000000000032
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok778) {
    // -3.18047301E-27
    int f = -1820591192;
    // -0.0000000000000000000000000032
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok779) {
    // 1.39601805E-25
    int f = 372035988;
    // 0.0000000000000000000000001396
    s21_decimal decimal_check = {{0x574, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok780) {
    // -1.39601805E-25
    int f = -1775447660;
    // -0.0000000000000000000000001396
    s21_decimal decimal_check = {{0x574, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok781) {
    // 6.77582029E+16
    int f = 1534114234;
    // 67758200000000000
    s21_decimal decimal_check = {{0x519EB000, 0xF0B9B9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok782) {
    // -6.77582029E+16
    int f = -613369414;
    // -67758200000000000
    s21_decimal decimal_check = {{0x519EB000, 0xF0B9B9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok783) {
    // 7.79890252E-05
    int f = 950242826;
    // 0.00007798903
    s21_decimal decimal_check = {{0x770077, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok784) {
    // -7.79890252E-05
    int f = -1197240822;
    // -0.00007798903
    s21_decimal decimal_check = {{0x770077, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok785) {
    // 123579.57
    int f = 1207000521;
    // 123579.6
    s21_decimal decimal_check = {{0x12DB54, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok786) {
    // -123579.57
    int f = -940483127;
    // -123579.6
    s21_decimal decimal_check = {{0x12DB54, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok787) {
    // 1.83719683E+17
    int f = 1545809157;
    // 183719700000000000
    s21_decimal decimal_check = {{0xBDC800, 0x28CB418, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok788) {
    // -1.83719683E+17
    int f = -601674491;
    // -183719700000000000
    s21_decimal decimal_check = {{0xBDC800, 0x28CB418, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok789) {
    // 2.12026283E-16
    int f = 628388637;
    // 0.0000000000000002120263
    s21_decimal decimal_check = {{0x205A47, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok790) {
    // -2.12026283E-16
    int f = -1519095011;
    // -0.0000000000000002120263
    s21_decimal decimal_check = {{0x205A47, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok791) {
    // 5.37992697E-21
    int f = 499859318;
    // 0.000000000000000000005379927
    s21_decimal decimal_check = {{0x521757, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok792) {
    // -5.37992697E-21
    int f = -1647624330;
    // -0.000000000000000000005379927
    s21_decimal decimal_check = {{0x521757, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok793) {
    // 1.79480092E-26
    int f = 347193244;
    // 0.0000000000000000000000000179
    s21_decimal decimal_check = {{0xB3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok794) {
    // -1.79480092E-26
    int f = -1800290404;
    // -0.0000000000000000000000000179
    s21_decimal decimal_check = {{0xB3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok795) {
    // 4.43878502E-14
    int f = 692578229;
    // 0.00000000000004438785
    s21_decimal decimal_check = {{0x43BB01, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok796) {
    // -4.43878502E-14
    int f = -1454905419;
    // -0.00000000000004438785
    s21_decimal decimal_check = {{0x43BB01, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok797) {
    // 112674904
    int f = 1289152779;
    // 112674900
    s21_decimal decimal_check = {{0x6B74854, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok798) {
    // -112674904
    int f = -858330869;
    // -112674900
    s21_decimal decimal_check = {{0x6B74854, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok799) {
    // 2.22522193E-18
    int f = 572797249;
    // 0.000000000000000002225222
    s21_decimal decimal_check = {{0x21F446, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok800) {
    // -2.22522193E-18
    int f = -1574686399;
    // -0.000000000000000002225222
    s21_decimal decimal_check = {{0x21F446, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok801) {
    // 3.81901E-25
    int f = 384590497;
    // 0.0000000000000000000000003819
    s21_decimal decimal_check = {{0xEEB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok802) {
    // -3.81901E-25
    int f = -1762893151;
    // -0.0000000000000000000000003819
    s21_decimal decimal_check = {{0xEEB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok803) {
    // 8.94829288E+20
    int f = 1648494849;
    // 894829300000000000000
    s21_decimal decimal_check = {{0x57734000, 0x82404B57, 0x30, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok804) {
    // -8.94829288E+20
    int f = -498988799;
    // -894829300000000000000
    s21_decimal decimal_check = {{0x57734000, 0x82404B57, 0x30, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok805) {
    // 1.55991883E+15
    int f = 1488017309;
    // 1559919000000000
    s21_decimal decimal_check = {{0xF1DF9600, 0x58ABC, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok806) {
    // -1.55991883E+15
    int f = -659466339;
    // -1559919000000000
    s21_decimal decimal_check = {{0xF1DF9600, 0x58ABC, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok807) {
    // 4.76704638E-23
    int f = 442926381;
    // 0.0000000000000000000000476705
    s21_decimal decimal_check = {{0x74621, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok808) {
    // -4.76704638E-23
    int f = -1704557267;
    // -0.0000000000000000000000476705
    s21_decimal decimal_check = {{0x74621, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok809) {
    // 1.16454767E-05
    int f = 927162609;
    // 0.00001164548
    s21_decimal decimal_check = {{0x11C504, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok810) {
    // -1.16454767E-05
    int f = -1220321039;
    // -0.00001164548
    s21_decimal decimal_check = {{0x11C504, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok811) {
    // 504250.563
    int f = 1224095570;
    // 504250.6
    s21_decimal decimal_check = {{0x4CF14A, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok812) {
    // -504250.563
    int f = -923388078;
    // -504250.6
    s21_decimal decimal_check = {{0x4CF14A, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok813) {
    // 3.5519861E-28
    int f = 299967045;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok814) {
    // -3.5519861E-28
    int f = -1847516603;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok815) {
    // 249224.078
    int f = 1215521285;
    // 249224.1
    s21_decimal decimal_check = {{0x260751, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok816) {
    // -249224.078
    int f = -931962363;
    // -249224.1
    s21_decimal decimal_check = {{0x260751, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok817) {
    // 647951936
    int f = 1310358489;
    // 647951900
    s21_decimal decimal_check = {{0x269EF61C, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok818) {
    // -647951936
    int f = -837125159;
    // -647951900
    s21_decimal decimal_check = {{0x269EF61C, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok819) {
    // 5.19312726E-19
    int f = 555304489;
    // 0.0000000000000000005193127
    s21_decimal decimal_check = {{0x4F3DA7, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok820) {
    // -5.19312726E-19
    int f = -1592179159;
    // -0.0000000000000000005193127
    s21_decimal decimal_check = {{0x4F3DA7, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok821) {
    // 2.43351511E+10
    int f = 1354059678;
    // 24335150000
    s21_decimal decimal_check = {{0xAA7CEBB0, 0x5, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok822) {
    // -2.43351511E+10
    int f = -793423970;
    // -24335150000
    s21_decimal decimal_check = {{0xAA7CEBB0, 0x5, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok823) {
    // 2.71908798E-13
    int f = 714674736;
    // 0.0000000000002719088
    s21_decimal decimal_check = {{0x297D70, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok824) {
    // -2.71908798E-13
    int f = -1432808912;
    // -0.0000000000002719088
    s21_decimal decimal_check = {{0x297D70, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok825) {
    // 2.22518185E+25
    int f = 1771257868;
    // 22251820000000000000000000
    s21_decimal decimal_check = {{0x49300000, 0x944C34E1, 0x126801, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok826) {
    // -2.22518185E+25
    int f = -376225780;
    // -22251820000000000000000000
    s21_decimal decimal_check = {{0x49300000, 0x944C34E1, 0x126801, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok827) {
    // 4.38060637E+16
    int f = 1528537442;
    // 43806060000000000
    s21_decimal decimal_check = {{0x254F3800, 0x9BA161, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok828) {
    // -4.38060637E+16
    int f = -618946206;
    // -43806060000000000
    s21_decimal decimal_check = {{0x254F3800, 0x9BA161, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok829) {
    // 2.87276366E-12
    int f = 743057180;
    // 0.000000000002872764
    s21_decimal decimal_check = {{0x2BD5BC, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok830) {
    // -2.87276366E-12
    int f = -1404426468;
    // -0.000000000002872764
    s21_decimal decimal_check = {{0x2BD5BC, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok831) {
    // 3.1785291E-22
    int f = 465576283;
    // 0.0000000000000000000003178529
    s21_decimal decimal_check = {{0x308021, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok832) {
    // -3.1785291E-22
    int f = -1681907365;
    // -0.0000000000000000000003178529
    s21_decimal decimal_check = {{0x308021, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok833) {
    // 4.7454922E-20
    int f = 526391675;
    // 0.00000000000000000004745492
    s21_decimal decimal_check = {{0x486914, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok834) {
    // -4.7454922E-20
    int f = -1621091973;
    // -0.00000000000000000004745492
    s21_decimal decimal_check = {{0x486914, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok835) {
    // 2.66351547E+23
    int f = 1717672905;
    // 266351500000000000000000
    s21_decimal decimal_check = {{0xA80E0000, 0xF1996B45, 0x3866, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok836) {
    // -2.66351547E+23
    int f = -429810743;
    // -266351500000000000000000
    s21_decimal decimal_check = {{0xA80E0000, 0xF1996B45, 0x3866, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok837) {
    // 0.251395375
    int f = 1048622821;
    // 0.2513954
    s21_decimal decimal_check = {{0x265C22, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok838) {
    // -0.251395375
    int f = -1098860827;
    // -0.2513954
    s21_decimal decimal_check = {{0x265C22, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok839) {
    // 1.4660135E-15
    int f = 651380314;
    // 0.000000000000001466013
    s21_decimal decimal_check = {{0x165E9D, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok840) {
    // -1.4660135E-15
    int f = -1496103334;
    // -0.000000000000001466013
    s21_decimal decimal_check = {{0x165E9D, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok841) {
    // 1.69326734E+25
    int f = 1767905825;
    // 16932670000000000000000000
    s21_decimal decimal_check = {{0xA6380000, 0xE1479D68, 0xE01A1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok842) {
    // -1.69326734E+25
    int f = -379577823;
    // -16932670000000000000000000
    s21_decimal decimal_check = {{0xA6380000, 0xE1479D68, 0xE01A1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok843) {
    // 8.28500158E+15
    int f = 1508604242;
    // 8285002000000000
    s21_decimal decimal_check = {{0x592C6400, 0x1D6F2A, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok844) {
    // -8.28500158E+15
    int f = -638879406;
    // -8285002000000000
    s21_decimal decimal_check = {{0x592C6400, 0x1D6F2A, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok845) {
    // 4.43604749E-15
    int f = 664785745;
    // 0.000000000000004436047
    s21_decimal decimal_check = {{0x43B04F, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok846) {
    // -4.43604749E-15
    int f = -1482697903;
    // -0.000000000000004436047
    s21_decimal decimal_check = {{0x43B04F, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok847) {
    // 2.51911965E+25
    int f = 1772532620;
    // 25191200000000000000000000
    s21_decimal decimal_check = {{0x98800000, 0xB0396630, 0x14D671, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok848) {
    // -2.51911965E+25
    int f = -374951028;
    // -25191200000000000000000000
    s21_decimal decimal_check = {{0x98800000, 0xB0396630, 0x14D671, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok849) {
    // 6.3121332E-17
    int f = 613518402;
    // 0.00000000000000006312133
    s21_decimal decimal_check = {{0x6050C5, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok850) {
    // -6.3121332E-17
    int f = -1533965246;
    // -0.00000000000000006312133
    s21_decimal decimal_check = {{0x6050C5, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok851) {
    // 3.0177571E+14
    int f = 1468611409;
    // 301775700000000
    s21_decimal decimal_check = {{0xA1667D00, 0x11276, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok852) {
    // -3.0177571E+14
    int f = -678872239;
    // -301775700000000
    s21_decimal decimal_check = {{0xA1667D00, 0x11276, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok853) {
    // 5.07794359E+15
    int f = 1502630631;
    // 5077944000000000
    s21_decimal decimal_check = {{0xF84F3000, 0x120A5C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok854) {
    // -5.07794359E+15
    int f = -644853017;
    // -5077944000000000
    s21_decimal decimal_check = {{0xF84F3000, 0x120A5C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok855) {
    // 77044.0391
    int f = 1201043973;
    // 77044.04
    s21_decimal decimal_check = {{0x758F54, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok856) {
    // -77044.0391
    int f = -946439675;
    // -77044.04
    s21_decimal decimal_check = {{0x758F54, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok857) {
    // 2.41427415E+27
    int f = 1828299086;
    // 2414274000000000000000000000
    s21_decimal decimal_check = {{0x75400000, 0xC9EC668C, 0x7CD0A67, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok858) {
    // -2.41427415E+27
    int f = -319184562;
    // -2414274000000000000000000000
    s21_decimal decimal_check = {{0x75400000, 0xC9EC668C, 0x7CD0A67, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok859) {
    // 9.4206561E-12
    int f = 757447389;
    // 0.000000000009420656
    s21_decimal decimal_check = {{0x8FBF70, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok860) {
    // -9.4206561E-12
    int f = -1390036259;
    // -0.000000000009420656
    s21_decimal decimal_check = {{0x8FBF70, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok861) {
    // 2023888
    int f = 1240927872;
    // 2023888
    s21_decimal decimal_check = {{0x1EE1D0, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok862) {
    // -2023888
    int f = -906555776;
    // -2023888
    s21_decimal decimal_check = {{0x1EE1D0, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok863) {
    // 9.14909147E+23
    int f = 1732361555;
    // 914909100000000000000000
    s21_decimal decimal_check = {{0x92DE0000, 0x525A6DD6, 0xC1BD, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok864) {
    // -9.14909147E+23
    int f = -415122093;
    // -914909100000000000000000
    s21_decimal decimal_check = {{0x92DE0000, 0x525A6DD6, 0xC1BD, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok865) {
    // 1.75557937E+16
    int f = 1517910939;
    // 17555790000000000
    s21_decimal decimal_check = {{0xE2B38C00, 0x3E5EE5, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok866) {
    // -1.75557937E+16
    int f = -629572709;
    // -17555790000000000
    s21_decimal decimal_check = {{0xE2B38C00, 0x3E5EE5, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok867) {
    // 3.645629E-27
    int f = 328231698;
    // 0.0000000000000000000000000036
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok868) {
    // -3.645629E-27
    int f = -1819251950;
    // -0.0000000000000000000000000036
    s21_decimal decimal_check = {{0x24, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok869) {
    // 2.67858282E+24
    int f = 1745735057;
    // 2678583000000000000000000
    s21_decimal decimal_check = {{0x127C0000, 0x467FE709, 0x23736, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok870) {
    // -2.67858282E+24
    int f = -401748591;
    // -2678583000000000000000000
    s21_decimal decimal_check = {{0x127C0000, 0x467FE709, 0x23736, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok871) {
    // 113.615631
    int f = 1122188084;
    // 113.6156
    s21_decimal decimal_check = {{0x11561C, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok872) {
    // -113.615631
    int f = -1025295564;
    // -113.6156
    s21_decimal decimal_check = {{0x11561C, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok873) {
    // 2.04301485E-17
    int f = 599551827;
    // 0.00000000000000002043015
    s21_decimal decimal_check = {{0x1F2C87, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok874) {
    // -2.04301485E-17
    int f = -1547931821;
    // -0.00000000000000002043015
    s21_decimal decimal_check = {{0x1F2C87, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok875) {
    // 1.51717779E-17
    int f = 596373337;
    // 0.00000000000000001517178
    s21_decimal decimal_check = {{0x17267A, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok876) {
    // -1.51717779E-17
    int f = -1551110311;
    // -0.00000000000000001517178
    s21_decimal decimal_check = {{0x17267A, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok877) {
    // 1.40402926E-06
    int f = 901542420;
    // 0.000001404029
    s21_decimal decimal_check = {{0x156C7D, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok878) {
    // -1.40402926E-06
    int f = -1245941228;
    // -0.000001404029
    s21_decimal decimal_check = {{0x156C7D, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok879) {
    // 3.24625216E-05
    int f = 940058718;
    // 0.00003246252
    s21_decimal decimal_check = {{0x3188AC, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok880) {
    // -3.24625216E-05
    int f = -1207424930;
    // -0.00003246252
    s21_decimal decimal_check = {{0x3188AC, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok881) {
    // 139711.969
    int f = 1208512510;
    // 139712
    s21_decimal decimal_check = {{0x221C0, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok882) {
    // -139711.969
    int f = -938971138;
    // -139712
    s21_decimal decimal_check = {{0x221C0, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok883) {
    // 2.69431139E-17
    int f = 603488673;
    // 0.00000000000000002694311
    s21_decimal decimal_check = {{0x291CA7, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok884) {
    // -2.69431139E-17
    int f = -1543994975;
    // -0.00000000000000002694311
    s21_decimal decimal_check = {{0x291CA7, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok885) {
    // 1.63365789E-23
    int f = 429784937;
    // 0.0000000000000000000000163366
    s21_decimal decimal_check = {{0x27E26, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok886) {
    // -1.63365789E-23
    int f = -1717698711;
    // -0.0000000000000000000000163366
    s21_decimal decimal_check = {{0x27E26, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok887) {
    // 3.21565747E+09
    int f = 1329572618;
    // 3215657000
    s21_decimal decimal_check = {{0xBFAB0828, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok888) {
    // -3.21565747E+09
    int f = -817911030;
    // -3215657000
    s21_decimal decimal_check = {{0xBFAB0828, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok889) {
    // 2.87946203E-18
    int f = 575960960;
    // 0.000000000000000002879462
    s21_decimal decimal_check = {{0x2BEFE6, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok890) {
    // -2.87946203E-18
    int f = -1571522688;
    // -0.000000000000000002879462
    s21_decimal decimal_check = {{0x2BEFE6, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok891) {
    // 1.31413691E-09
    int f = 817143061;
    // 0.000000001314137
    s21_decimal decimal_check = {{0x140D59, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok892) {
    // -1.31413691E-09
    int f = -1330340587;
    // -0.000000001314137
    s21_decimal decimal_check = {{0x140D59, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok893) {
    // 1.68586065E-12
    int f = 736969608;
    // 0.000000000001685861
    s21_decimal decimal_check = {{0x19B965, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok894) {
    // -1.68586065E-12
    int f = -1410514040;
    // -0.000000000001685861
    s21_decimal decimal_check = {{0x19B965, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok895) {
    // 1463870.13
    int f = 1236447729;
    // 1463870
    s21_decimal decimal_check = {{0x16563E, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok896) {
    // -1463870.13
    int f = -911035919;
    // -1463870
    s21_decimal decimal_check = {{0x16563E, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok897) {
    // 6.62047472E-10
    int f = 808844147;
    // 0.0000000006620475
    s21_decimal decimal_check = {{0x65053B, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok898) {
    // -6.62047472E-10
    int f = -1338639501;
    // -0.0000000006620475
    s21_decimal decimal_check = {{0x65053B, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok899) {
    // 3.43029168E+23
    int f = 1720797004;
    // 343029200000000000000000
    s21_decimal decimal_check = {{0xF9C80000, 0xA6731167, 0x48A3, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok900) {
    // -3.43029168E+23
    int f = -426686644;
    // -343029200000000000000000
    s21_decimal decimal_check = {{0xF9C80000, 0xA6731167, 0x48A3, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok901) {
    // 5.63252534E+16
    int f = 1531452293;
    // 56325250000000000
    s21_decimal decimal_check = {{0x36229400, 0xC81B84, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok902) {
    // -5.63252534E+16
    int f = -616031355;
    // -56325250000000000
    s21_decimal decimal_check = {{0x36229400, 0xC81B84, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok903) {
    // 3.26974937E+24
    int f = 1747786078;
    // 3269749000000000000000000
    s21_decimal decimal_check = {{0x90B40000, 0x72CE8B54, 0x2B465, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok904) {
    // -3.26974937E+24
    int f = -399697570;
    // -3269749000000000000000000
    s21_decimal decimal_check = {{0x90B40000, 0x72CE8B54, 0x2B465, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok905) {
    // 42022.3516
    int f = 1193551450;
    // 42022.35
    s21_decimal decimal_check = {{0x401EFB, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok906) {
    // -42022.3516
    int f = -953932198;
    // -42022.35
    s21_decimal decimal_check = {{0x401EFB, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok907) {
    // 3.89609586E-16
    int f = 635476026;
    // 0.0000000000000003896096
    s21_decimal decimal_check = {{0x3B7320, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok908) {
    // -3.89609586E-16
    int f = -1512007622;
    // -0.0000000000000003896096
    s21_decimal decimal_check = {{0x3B7320, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok909) {
    // 1.30094713E-25
    int f = 371264681;
    // 0.0000000000000000000000001301
    s21_decimal decimal_check = {{0x515, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok910) {
    // -1.30094713E-25
    int f = -1776218967;
    // -0.0000000000000000000000001301
    s21_decimal decimal_check = {{0x515, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok911) {
    // 2.29408719E-23
    int f = 433970905;
    // 0.0000000000000000000000229409
    s21_decimal decimal_check = {{0x38021, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok912) {
    // -2.29408719E-23
    int f = -1713512743;
    // -0.0000000000000000000000229409
    s21_decimal decimal_check = {{0x38021, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok913) {
    // 0.000973391929
    int f = 981412666;
    // 0.0009733919
    s21_decimal decimal_check = {{0x94871F, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok914) {
    // -0.000973391929
    int f = -1166070982;
    // -0.0009733919
    s21_decimal decimal_check = {{0x94871F, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok915) {
    // 60712556
    int f = 1281857947;
    // 60712560
    s21_decimal decimal_check = {{0x39E6670, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok916) {
    // -60712556
    int f = -865625701;
    // -60712560
    s21_decimal decimal_check = {{0x39E6670, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok917) {
    // 3.82104928E+11
    int f = 1387392629;
    // 382104900000
    s21_decimal decimal_check = {{0xF73A11A0, 0x58, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok918) {
    // -3.82104928E+11
    int f = -760091019;
    // -382104900000
    s21_decimal decimal_check = {{0xF73A11A0, 0x58, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok919) {
    // 0.00922278408
    int f = 1008147241;
    // 0.009222784
    s21_decimal decimal_check = {{0x8CBA80, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok920) {
    // -0.00922278408
    int f = -1139336407;
    // -0.009222784
    s21_decimal decimal_check = {{0x8CBA80, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok921) {
    // 51079124
    int f = 1279449589;
    // 51079120
    s21_decimal decimal_check = {{0x30B67D0, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok922) {
    // -51079124
    int f = -868034059;
    // -51079120
    s21_decimal decimal_check = {{0x30B67D0, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok923) {
    // 1.16307216E-15
    int f = 648519114;
    // 0.000000000000001163072
    s21_decimal decimal_check = {{0x11BF40, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok924) {
    // -1.16307216E-15
    int f = -1498964534;
    // -0.000000000000001163072
    s21_decimal decimal_check = {{0x11BF40, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok925) {
    // 5.11913131E-05
    int f = 945206849;
    // 0.00005119131
    s21_decimal decimal_check = {{0x4E1C9B, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok926) {
    // -5.11913131E-05
    int f = -1202276799;
    // -0.00005119131
    s21_decimal decimal_check = {{0x4E1C9B, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok927) {
    // 3.55267611E-19
    int f = 550614662;
    // 0.0000000000000000003552676
    s21_decimal decimal_check = {{0x3635A4, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok928) {
    // -3.55267611E-19
    int f = -1596868986;
    // -0.0000000000000000003552676
    s21_decimal decimal_check = {{0x3635A4, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok929) {
    // 2.3765169E-07
    int f = 880749875;
    // 0.0000002376517
    s21_decimal decimal_check = {{0x244345, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok930) {
    // -2.3765169E-07
    int f = -1266733773;
    // -0.0000002376517
    s21_decimal decimal_check = {{0x244345, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok931) {
    // 13345.959
    int f = 1179682774;
    // 13345.96
    s21_decimal decimal_check = {{0x145D44, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok932) {
    // -13345.959
    int f = -967800874;
    // -13345.96
    s21_decimal decimal_check = {{0x145D44, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok933) {
    // 1.43556538E-11
    int f = 763137054;
    // 0.00000000001435565
    s21_decimal decimal_check = {{0x15E7AD, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok934) {
    // -1.43556538E-11
    int f = -1384346594;
    // -0.00000000001435565
    s21_decimal decimal_check = {{0x15E7AD, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok935) {
    // 6.15152269E+13
    int f = 1449118341;
    // 61515230000000
    s21_decimal decimal_check = {{0xA16EB380, 0x37F2, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok936) {
    // -6.15152269E+13
    int f = -698365307;
    // -61515230000000
    s21_decimal decimal_check = {{0xA16EB380, 0x37F2, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok937) {
    // 1.57562583E+10
    int f = 1349175643;
    // 15756260000
    s21_decimal decimal_check = {{0xAB2572A0, 0x3, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok938) {
    // -1.57562583E+10
    int f = -798308005;
    // -15756260000
    s21_decimal decimal_check = {{0xAB2572A0, 0x3, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok939) {
    // 12536.3623
    int f = 1178853747;
    // 12536.36
    s21_decimal decimal_check = {{0x132104, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok940) {
    // -12536.3623
    int f = -968629901;
    // -12536.36
    s21_decimal decimal_check = {{0x132104, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok941) {
    // 7.71907283E+12
    int f = 1424009107;
    // 7719073000000
    s21_decimal decimal_check = {{0x3C9AAA40, 0x705, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok942) {
    // -7.71907283E+12
    int f = -723474541;
    // -7719073000000
    s21_decimal decimal_check = {{0x3C9AAA40, 0x705, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok943) {
    // 1.5579967E+15
    int f = 1488002988;
    // 1557997000000000
    s21_decimal decimal_check = {{0x71BF0200, 0x588FD, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok944) {
    // -1.5579967E+15
    int f = -659480660;
    // -1557997000000000
    s21_decimal decimal_check = {{0x71BF0200, 0x588FD, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok945) {
    // 9.46762557E-10
    int f = 813834047;
    // 0.0000000009467626
    s21_decimal decimal_check = {{0x9076EA, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok946) {
    // -9.46762557E-10
    int f = -1333649601;
    // -0.0000000009467626
    s21_decimal decimal_check = {{0x9076EA, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok947) {
    // 7.87734575E+21
    int f = 1674937361;
    // 7877346000000000000000
    s21_decimal decimal_check = {{0x3C3D0000, 0x822E308, 0x1AB, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok948) {
    // -7.87734575E+21
    int f = -472546287;
    // -7877346000000000000000
    s21_decimal decimal_check = {{0x3C3D0000, 0x822E308, 0x1AB, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok949) {
    // 0.00256037107
    int f = 992463846;
    // 0.002560371
    s21_decimal decimal_check = {{0x271173, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok950) {
    // -0.00256037107
    int f = -1155019802;
    // -0.002560371
    s21_decimal decimal_check = {{0x271173, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok951) {
    // 3144.87744
    int f = 1162120714;
    // 3144.877
    s21_decimal decimal_check = {{0x2FFCAD, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok952) {
    // -3144.87744
    int f = -985362934;
    // -3144.877
    s21_decimal decimal_check = {{0x2FFCAD, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok953) {
    // 2.66305232
    int f = 1076522867;
    // 2.663052
    s21_decimal decimal_check = {{0x28A28C, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok954) {
    // -2.66305232
    int f = -1070960781;
    // -2.663052
    s21_decimal decimal_check = {{0x28A28C, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok955) {
    // 1.40902762E-06
    int f = 901586386;
    // 0.000001409028
    s21_decimal decimal_check = {{0x158004, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok956) {
    // -1.40902762E-06
    int f = -1245897262;
    // -0.000001409028
    s21_decimal decimal_check = {{0x158004, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok957) {
    // 89699.1719
    int f = 1202663830;
    // 89699.17
    s21_decimal decimal_check = {{0x88DEBD, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok958) {
    // -89699.1719
    int f = -944819818;
    // -89699.17
    s21_decimal decimal_check = {{0x88DEBD, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok959) {
    // 4.99003843E+10
    int f = 1362748599;
    // 49900380000
    s21_decimal decimal_check = {{0x9E4B5F60, 0xB, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok960) {
    // -4.99003843E+10
    int f = -784735049;
    // -49900380000
    s21_decimal decimal_check = {{0x9E4B5F60, 0xB, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok961) {
    // 3.53746611E-12
    int f = 746122579;
    // 0.000000000003537466
    s21_decimal decimal_check = {{0x35FA3A, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok962) {
    // -3.53746611E-12
    int f = -1401361069;
    // -0.000000000003537466
    s21_decimal decimal_check = {{0x35FA3A, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok963) {
    // 3.6091347E+27
    int f = 1832556160;
    // 3609135000000000000000000000
    s21_decimal decimal_check = {{0x1F600000, 0x63C1A55B, 0xBA96810, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok964) {
    // -3.6091347E+27
    int f = -314927488;
    // -3609135000000000000000000000
    s21_decimal decimal_check = {{0x1F600000, 0x63C1A55B, 0xBA96810, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok965) {
    // 1.22431489E-24
    int f = 398291996;
    // 0.0000000000000000000000012243
    s21_decimal decimal_check = {{0x2FD3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok966) {
    // -1.22431489E-24
    int f = -1749191652;
    // -0.0000000000000000000000012243
    s21_decimal decimal_check = {{0x2FD3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok967) {
    // 3.63974054E+21
    int f = 1665486732;
    // 3639741000000000000000
    s21_decimal decimal_check = {{0x610C8000, 0x4F8DA353, 0xC5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok968) {
    // -3.63974054E+21
    int f = -481996916;
    // -3639741000000000000000
    s21_decimal decimal_check = {{0x610C8000, 0x4F8DA353, 0xC5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok969) {
    // 1.69694953E-10
    int f = 792368354;
    // 0.000000000169695
    s21_decimal decimal_check = {{0x296DF, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok970) {
    // -1.69694953E-10
    int f = -1355115294;
    // -0.000000000169695
    s21_decimal decimal_check = {{0x296DF, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok971) {
    // 0.326009154
    int f = 1051126444;
    // 0.3260092
    s21_decimal decimal_check = {{0x31BEBC, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok972) {
    // -0.326009154
    int f = -1096357204;
    // -0.3260092
    s21_decimal decimal_check = {{0x31BEBC, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok973) {
    // 1.06111569E-19
    int f = 536513666;
    // 0.0000000000000000001061116
    s21_decimal decimal_check = {{0x1030FC, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok974) {
    // -1.06111569E-19
    int f = -1610969982;
    // -0.0000000000000000001061116
    s21_decimal decimal_check = {{0x1030FC, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok975) {
    // 2.28963174E-07
    int f = 880138475;
    // 0.0000002289632
    s21_decimal decimal_check = {{0x22EFE0, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok976) {
    // -2.28963174E-07
    int f = -1267345173;
    // -0.0000002289632
    s21_decimal decimal_check = {{0x22EFE0, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok977) {
    // 1.43782985E+16
    int f = 1514951666;
    // 14378300000000000
    s21_decimal decimal_check = {{0xD7F95800, 0x3314FC, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok978) {
    // -1.43782985E+16
    int f = -632531982;
    // -14378300000000000
    s21_decimal decimal_check = {{0xD7F95800, 0x3314FC, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok979) {
    // 590942336
    int f = 1309467714;
    // 590942300
    s21_decimal decimal_check = {{0x2339105C, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok980) {
    // -590942336
    int f = -838015934;
    // -590942300
    s21_decimal decimal_check = {{0x2339105C, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok981) {
    // 5.69699048E+22
    int f = 1698760068;
    // 56969900000000000000000
    s21_decimal decimal_check = {{0x965E0000, 0x582F0288, 0xC10, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok982) {
    // -5.69699048E+22
    int f = -448723580;
    // -56969900000000000000000
    s21_decimal decimal_check = {{0x965E0000, 0x582F0288, 0xC10, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok983) {
    // 3.31167087E-07
    int f = 884067138;
    // 0.0000003311671
    s21_decimal decimal_check = {{0x328837, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok984) {
    // -3.31167087E-07
    int f = -1263416510;
    // -0.0000003311671
    s21_decimal decimal_check = {{0x328837, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok985) {
    // 4.16008825E-11
    int f = 775353966;
    // 0.00000000004160088
    s21_decimal decimal_check = {{0x3F7A58, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok986) {
    // -4.16008825E-11
    int f = -1372129682;
    // -0.00000000004160088
    s21_decimal decimal_check = {{0x3F7A58, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok987) {
    // 3.5816223E+13
    int f = 1442991221;
    // 35816220000000
    s21_decimal decimal_check = {{0x1D11FF00, 0x2093, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok988) {
    // -3.5816223E+13
    int f = -704492427;
    // -35816220000000
    s21_decimal decimal_check = {{0x1D11FF00, 0x2093, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok989) {
    // 664639.188
    int f = 1226982387;
    // 664639.2
    s21_decimal decimal_check = {{0x656A78, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok990) {
    // -664639.188
    int f = -920501261;
    // -664639.2
    s21_decimal decimal_check = {{0x656A78, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok991) {
    // 1.28600095E-18
    int f = 566085566;
    // 0.000000000000000001286001
    s21_decimal decimal_check = {{0x139F71, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok992) {
    // -1.28600095E-18
    int f = -1581398082;
    // -0.000000000000000001286001
    s21_decimal decimal_check = {{0x139F71, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok993) {
    // 260867.656
    int f = 1216266474;
    // 260867.7
    s21_decimal decimal_check = {{0x27CE25, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok994) {
    // -260867.656
    int f = -931217174;
    // -260867.7
    s21_decimal decimal_check = {{0x27CE25, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok995) {
    // 2.32606977E+13
    int f = 1437154925;
    // 23260700000000
    s21_decimal decimal_check = {{0xCDC2BF00, 0x1527, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok996) {
    // -2.32606977E+13
    int f = -710328723;
    // -23260700000000
    s21_decimal decimal_check = {{0xCDC2BF00, 0x1527, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok997) {
    // 1.30240166E-22
    int f = 454914913;
    // 0.0000000000000000000001302402
    s21_decimal decimal_check = {{0x13DF82, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok998) {
    // -1.30240166E-22
    int f = -1692568735;
    // -0.0000000000000000000001302402
    s21_decimal decimal_check = {{0x13DF82, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok999) {
    // 0.000107238448
    int f = 954262836;
    // 0.0001072384
    s21_decimal decimal_check = {{0x105D00, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1000) {
    // -0.000107238448
    int f = -1193220812;
    // -0.0001072384
    s21_decimal decimal_check = {{0x105D00, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1001) {
    // 8.59072888E+19
    int f = 1620379264;
    // 85907290000000000000
    s21_decimal decimal_check = {{0x4277A000, 0xA8340119, 0x4, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1002) {
    // -8.59072888E+19
    int f = -527104384;
    // -85907290000000000000
    s21_decimal decimal_check = {{0x4277A000, 0xA8340119, 0x4, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1003) {
    // 1.3645729E-08
    int f = 845835917;
    // 0.00000001364573
    s21_decimal decimal_check = {{0x14D25D, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1004) {
    // -1.3645729E-08
    int f = -1301647731;
    // -0.00000001364573
    s21_decimal decimal_check = {{0x14D25D, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1005) {
    // 9.06369633E+13
    int f = 1453645344;
    // 90636960000000
    s21_decimal decimal_check = {{0xFCDE800, 0x526F, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1006) {
    // -9.06369633E+13
    int f = -693838304;
    // -90636960000000
    s21_decimal decimal_check = {{0xFCDE800, 0x526F, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1007) {
    // 53007.5391
    int f = 1196363658;
    // 53007.54
    s21_decimal decimal_check = {{0x50E212, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1008) {
    // -53007.5391
    int f = -951119990;
    // -53007.54
    s21_decimal decimal_check = {{0x50E212, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1009) {
    // 2.23378672E-28
    int f = 294491459;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1010) {
    // -2.23378672E-28
    int f = -1852992189;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1011) {
    // 1.75779386E+19
    int f = 1601433954;
    // 17577940000000000000
    s21_decimal decimal_check = {{0x4F214000, 0xF3F1634C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1012) {
    // -1.75779386E+19
    int f = -546049694;
    // -17577940000000000000
    s21_decimal decimal_check = {{0x4F214000, 0xF3F1634C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1013) {
    // 1.62048545E-05
    int f = 931655593;
    // 0.00001620485
    s21_decimal decimal_check = {{0x18BA05, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1014) {
    // -1.62048545E-05
    int f = -1215828055;
    // -0.00001620485
    s21_decimal decimal_check = {{0x18BA05, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1015) {
    // 5.36228323
    int f = 1084987347;
    // 5.362283
    s21_decimal decimal_check = {{0x51D26B, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1016) {
    // -5.36228323
    int f = -1062496301;
    // -5.362283
    s21_decimal decimal_check = {{0x51D26B, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1017) {
    // 76675.7344
    int f = 1200996830;
    // 76675.73
    s21_decimal decimal_check = {{0x74FF75, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1018) {
    // -76675.7344
    int f = -946486818;
    // -76675.73
    s21_decimal decimal_check = {{0x74FF75, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1019) {
    // 4.21673009E-11
    int f = 775517225;
    // 0.0000000000421673
    s21_decimal decimal_check = {{0x66F29, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1020) {
    // -4.21673009E-11
    int f = -1371966423;
    // -0.0000000000421673
    s21_decimal decimal_check = {{0x66F29, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1021) {
    // 2.15164255E-06
    int f = 907044080;
    // 0.000002151643
    s21_decimal decimal_check = {{0x20D4DB, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1022) {
    // -2.15164255E-06
    int f = -1240439568;
    // -0.000002151643
    s21_decimal decimal_check = {{0x20D4DB, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1023) {
    // 3.66655567E+20
    int f = 1637810930;
    // 366655600000000000000
    s21_decimal decimal_check = {{0x4BB70000, 0xE05E5D93, 0x13, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1024) {
    // -3.66655567E+20
    int f = -509672718;
    // -366655600000000000000
    s21_decimal decimal_check = {{0x4BB70000, 0xE05E5D93, 0x13, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1025) {
    // 3.44413309E+20
    int f = 1637178767;
    // 344413300000000000000
    s21_decimal decimal_check = {{0xF40B4000, 0xABB1D791, 0x12, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1026) {
    // -3.44413309E+20
    int f = -510304881;
    // -344413300000000000000
    s21_decimal decimal_check = {{0xF40B4000, 0xABB1D791, 0x12, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1027) {
    // 7.67403261E+18
    int f = 1591017288;
    // 7674033000000000000
    s21_decimal decimal_check = {{0xCFA01000, 0x6A7FA45A, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1028) {
    // -7.67403261E+18
    int f = -556466360;
    // -7674033000000000000
    s21_decimal decimal_check = {{0xCFA01000, 0x6A7FA45A, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1029) {
    // 4.85771895E+27
    int f = 1836786528;
    // 4857719000000000000000000000
    s21_decimal decimal_check = {{0xDC600000, 0xA7FD172F, 0xFB23602, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1030) {
    // -4.85771895E+27
    int f = -310697120;
    // -4857719000000000000000000000
    s21_decimal decimal_check = {{0xDC600000, 0xA7FD172F, 0xFB23602, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1031) {
    // 0.0139906397
    int f = 1013266687;
    // 0.01399064
    s21_decimal decimal_check = {{0x155918, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1032) {
    // -0.0139906397
    int f = -1134216961;
    // -0.01399064
    s21_decimal decimal_check = {{0x155918, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1033) {
    // 9.62894658E+26
    int f = 1816600376;
    // 962894700000000000000000000
    s21_decimal decimal_check = {{0x2A300000, 0x47DE8134, 0x31C7CE2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1034) {
    // -9.62894658E+26
    int f = -330883272;
    // -962894700000000000000000000
    s21_decimal decimal_check = {{0x2A300000, 0x47DE8134, 0x31C7CE2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1035) {
    // 1.38743976E-08
    int f = 846093375;
    // 0.0000000138744
    s21_decimal decimal_check = {{0x21DF8, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1036) {
    // -1.38743976E-08
    int f = -1301390273;
    // -0.0000000138744
    s21_decimal decimal_check = {{0x21DF8, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1037) {
    // 1.02378995E+09
    int f = 1316230958;
    // 1023790000
    s21_decimal decimal_check = {{0x3D05CBB0, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1038) {
    // -1.02378995E+09
    int f = -831252690;
    // -1023790000
    s21_decimal decimal_check = {{0x3D05CBB0, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1039) {
    // 1.94582413E+11
    int f = 1379219472;
    // 194582400000
    s21_decimal decimal_check = {{0x4E03CC00, 0x2D, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1040) {
    // -1.94582413E+11
    int f = -768264176;
    // -194582400000
    s21_decimal decimal_check = {{0x4E03CC00, 0x2D, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1041) {
    // 6.20825917E-16
    int f = 640872670;
    // 0.0000000000000006208259
    s21_decimal decimal_check = {{0x5EBB03, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1042) {
    // -6.20825917E-16
    int f = -1506610978;
    // -0.0000000000000006208259
    s21_decimal decimal_check = {{0x5EBB03, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1043) {
    // 6.25784662E+13
    int f = 1449371837;
    // 62578470000000
    s21_decimal decimal_check = {{0x2F799580, 0x38EA, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1044) {
    // -6.25784662E+13
    int f = -698111811;
    // -62578470000000
    s21_decimal decimal_check = {{0x2F799580, 0x38EA, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1045) {
    // 4.22955387E+15
    int f = 1500539932;
    // 4229554000000000
    s21_decimal decimal_check = {{0xC7BA7400, 0xF06C1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1046) {
    // -4.22955387E+15
    int f = -646943716;
    // -4229554000000000
    s21_decimal decimal_check = {{0xC7BA7400, 0xF06C1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1047) {
    // 6.73212718E+18
    int f = 1589303972;
    // 6732127000000000000
    s21_decimal decimal_check = {{0x91D0F000, 0x5D6D51D6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1048) {
    // -6.73212718E+18
    int f = -558179676;
    // -6732127000000000000
    s21_decimal decimal_check = {{0x91D0F000, 0x5D6D51D6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1049) {
    // 0.109286256
    int f = 1038078329;
    // 0.1092863
    s21_decimal decimal_check = {{0x10ACFF, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1050) {
    // -0.109286256
    int f = -1109405319;
    // -0.1092863
    s21_decimal decimal_check = {{0x10ACFF, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1051) {
    // 1.18431933E-19
    int f = 537645531;
    // 0.0000000000000000001184319
    s21_decimal decimal_check = {{0x12123F, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1052) {
    // -1.18431933E-19
    int f = -1609838117;
    // -0.0000000000000000001184319
    s21_decimal decimal_check = {{0x12123F, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1053) {
    // 3.82130308E-13
    int f = 718741192;
    // 0.0000000000003821303
    s21_decimal decimal_check = {{0x3A4EF7, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1054) {
    // -3.82130308E-13
    int f = -1428742456;
    // -0.0000000000003821303
    s21_decimal decimal_check = {{0x3A4EF7, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1055) {
    // 2.63193288E-05
    int f = 937216084;
    // 0.00002631933
    s21_decimal decimal_check = {{0x2828FD, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1056) {
    // -2.63193288E-05
    int f = -1210267564;
    // -0.00002631933
    s21_decimal decimal_check = {{0x2828FD, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1057) {
    // 2.98218484E-23
    int f = 437269929;
    // 0.0000000000000000000000298218
    s21_decimal decimal_check = {{0x48CEA, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1058) {
    // -2.98218484E-23
    int f = -1710213719;
    // -0.0000000000000000000000298218
    s21_decimal decimal_check = {{0x48CEA, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1059) {
    // 2.05735713E-23
    int f = 432470450;
    // 0.0000000000000000000000205736
    s21_decimal decimal_check = {{0x323A8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1060) {
    // -2.05735713E-23
    int f = -1715013198;
    // -0.0000000000000000000000205736
    s21_decimal decimal_check = {{0x323A8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1061) {
    // 1.14532465E+16
    int f = 1512227499;
    // 11453250000000000
    s21_decimal decimal_check = {{0x91C61400, 0x28B0AB, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1062) {
    // -1.14532465E+16
    int f = -635256149;
    // -11453250000000000
    s21_decimal decimal_check = {{0x91C61400, 0x28B0AB, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1063) {
    // 113741.125
    int f = 1205741200;
    // 113741.1
    s21_decimal decimal_check = {{0x115B03, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1064) {
    // -113741.125
    int f = -941742448;
    // -113741.1
    s21_decimal decimal_check = {{0x115B03, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1065) {
    // 1.0448322E-22
    int f = 452763643;
    // 0.0000000000000000000001044832
    s21_decimal decimal_check = {{0xFF160, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1066) {
    // -1.0448322E-22
    int f = -1694720005;
    // -0.0000000000000000000001044832
    s21_decimal decimal_check = {{0xFF160, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1067) {
    // 4.14075245E+26
    int f = 1806385644;
    // 414075200000000000000000000
    s21_decimal decimal_check = {{0x5D000000, 0x92140D9D, 0x15683D5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1068) {
    // -4.14075245E+26
    int f = -341098004;
    // -414075200000000000000000000
    s21_decimal decimal_check = {{0x5D000000, 0x92140D9D, 0x15683D5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1069) {
    // 272267296
    int f = 1300353985;
    // 272267300
    s21_decimal decimal_check = {{0x103A7824, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1070) {
    // -272267296
    int f = -847129663;
    // -272267300
    s21_decimal decimal_check = {{0x103A7824, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1071) {
    // 1.29442395E+14
    int f = 1458271312;
    // 129442400000000
    s21_decimal decimal_check = {{0x28455800, 0x75BA, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1072) {
    // -1.29442395E+14
    int f = -689212336;
    // -129442400000000
    s21_decimal decimal_check = {{0x28455800, 0x75BA, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1073) {
    // 1.96034819E-25
    int f = 376614378;
    // 0.000000000000000000000000196
    s21_decimal decimal_check = {{0xC4, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1074) {
    // -1.96034819E-25
    int f = -1770869270;
    // -0.000000000000000000000000196
    s21_decimal decimal_check = {{0xC4, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1075) {
    // 1.15592232E-11
    int f = 759912989;
    // 0.00000000001155922
    s21_decimal decimal_check = {{0x11A352, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1076) {
    // -1.15592232E-11
    int f = -1387570659;
    // -0.00000000001155922
    s21_decimal decimal_check = {{0x11A352, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1077) {
    // 3.99128125E+10
    int f = 1360310227;
    // 39912810000
    s21_decimal decimal_check = {{0x4AFD2610, 0x9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1078) {
    // -3.99128125E+10
    int f = -787173421;
    // -39912810000
    s21_decimal decimal_check = {{0x4AFD2610, 0x9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1079) {
    // 9.29945877E-12
    int f = 757307658;
    // 0.000000000009299459
    s21_decimal decimal_check = {{0x8DE603, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1080) {
    // -9.29945877E-12
    int f = -1390175990;
    // -0.000000000009299459
    s21_decimal decimal_check = {{0x8DE603, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1081) {
    // 1.85898651E+22
    int f = 1685844109;
    // 18589870000000000000000
    s21_decimal decimal_check = {{0xC2EB0000, 0xC2456FA5, 0x3EF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1082) {
    // -1.85898651E+22
    int f = -461639539;
    // -18589870000000000000000
    s21_decimal decimal_check = {{0xC2EB0000, 0xC2456FA5, 0x3EF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1083) {
    // 0.0104928548
    int f = 1009510969;
    // 0.01049285
    s21_decimal decimal_check = {{0x1002C5, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1084) {
    // -0.0104928548
    int f = -1137972679;
    // -0.01049285
    s21_decimal decimal_check = {{0x1002C5, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1085) {
    // 1548690.88
    int f = 1237126295;
    // 1548691
    s21_decimal decimal_check = {{0x17A193, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1086) {
    // -1548690.88
    int f = -910357353;
    // -1548691
    s21_decimal decimal_check = {{0x17A193, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1087) {
    // 3.40823615E-12
    int f = 745526611;
    // 0.000000000003408236
    s21_decimal decimal_check = {{0x34016C, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1088) {
    // -3.40823615E-12
    int f = -1401957037;
    // -0.000000000003408236
    s21_decimal decimal_check = {{0x34016C, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1089) {
    // 2.81055916E-24
    int f = 408515804;
    // 0.0000000000000000000000028106
    s21_decimal decimal_check = {{0x6DCA, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1090) {
    // -2.81055916E-24
    int f = -1738967844;
    // -0.0000000000000000000000028106
    s21_decimal decimal_check = {{0x6DCA, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1091) {
    // 1.46979724E+20
    int f = 1627322396;
    // 146979700000000000000
    s21_decimal decimal_check = {{0xD7B4000, 0xF7C0CA6B, 0x7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1092) {
    // -1.46979724E+20
    int f = -520161252;
    // -146979700000000000000
    s21_decimal decimal_check = {{0xD7B4000, 0xF7C0CA6B, 0x7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1093) {
    // 4.53633492E-10
    int f = 804873021;
    // 0.0000000004536335
    s21_decimal decimal_check = {{0x45380F, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1094) {
    // -4.53633492E-10
    int f = -1342610627;
    // -0.0000000004536335
    s21_decimal decimal_check = {{0x45380F, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1095) {
    // 2.71320141E-12
    int f = 742321329;
    // 0.000000000002713201
    s21_decimal decimal_check = {{0x296671, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1096) {
    // -2.71320141E-12
    int f = -1405162319;
    // -0.000000000002713201
    s21_decimal decimal_check = {{0x296671, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1097) {
    // 7299.82764
    int f = 1172577951;
    // 7299.828
    s21_decimal decimal_check = {{0x6F62F4, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1098) {
    // -7299.82764
    int f = -974905697;
    // -7299.828
    s21_decimal decimal_check = {{0x6F62F4, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1099) {
    // 4.65442251E+25
    int f = 1780088958;
    // 46544230000000000000000000
    s21_decimal decimal_check = {{0x65D80000, 0xC39E3C94, 0x26801F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1100) {
    // -4.65442251E+25
    int f = -367394690;
    // -46544230000000000000000000
    s21_decimal decimal_check = {{0x65D80000, 0xC39E3C94, 0x26801F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1101) {
    // 6.67746875E-28
    int f = 307469840;
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1102) {
    // -6.67746875E-28
    int f = -1840013808;
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1103) {
    // 1.91731719E-25
    int f = 376265269;
    // 0.0000000000000000000000001917
    s21_decimal decimal_check = {{0x77D, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1104) {
    // -1.91731719E-25
    int f = -1771218379;
    // -0.0000000000000000000000001917
    s21_decimal decimal_check = {{0x77D, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1105) {
    // 1.07811953E+22
    int f = 1678908617;
    // 10781200000000000000000
    s21_decimal decimal_check = {{0x19680000, 0x7334B6C1, 0x248, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1106) {
    // -1.07811953E+22
    int f = -468575031;
    // -10781200000000000000000
    s21_decimal decimal_check = {{0x19680000, 0x7334B6C1, 0x248, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1107) {
    // 3.42071582E-16
    int f = 633680091;
    // 0.0000000000000003420716
    s21_decimal decimal_check = {{0x34322C, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1108) {
    // -3.42071582E-16
    int f = -1513803557;
    // -0.0000000000000003420716
    s21_decimal decimal_check = {{0x34322C, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1109) {
    // 4.38333952E-28
    int f = 302705120;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1110) {
    // -4.38333952E-28
    int f = -1844778528;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1111) {
    // 6.72112669E+23
    int f = 1728992077;
    // 672112700000000000000000
    s21_decimal decimal_check = {{0x2E860000, 0x4D6EFC4C, 0x8E53, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1112) {
    // -6.72112669E+23
    int f = -418491571;
    // -672112700000000000000000
    s21_decimal decimal_check = {{0x2E860000, 0x4D6EFC4C, 0x8E53, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1113) {
    // 3.20328286E-06
    int f = 911669243;
    // 0.000003203283
    s21_decimal decimal_check = {{0x30E0D3, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1114) {
    // -3.20328286E-06
    int f = -1235814405;
    // -0.000003203283
    s21_decimal decimal_check = {{0x30E0D3, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1115) {
    // 6.83665156E+12
    int f = 1422326022;
    // 6836652000000
    s21_decimal decimal_check = {{0xC836C300, 0x637, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1116) {
    // -6.83665156E+12
    int f = -725157626;
    // -6836652000000
    s21_decimal decimal_check = {{0xC836C300, 0x637, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1117) {
    // 2.41078679E+23
    int f = 1716269979;
    // 241078700000000000000000
    s21_decimal decimal_check = {{0x23DE0000, 0xE70B284E, 0x330C, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1118) {
    // -2.41078679E+23
    int f = -431213669;
    // -241078700000000000000000
    s21_decimal decimal_check = {{0x23DE0000, 0xE70B284E, 0x330C, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1119) {
    // 1.86833126E+09
    int f = 1323219186;
    // 1868331000
    s21_decimal decimal_check = {{0x6F5C77F8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1120) {
    // -1.86833126E+09
    int f = -824264462;
    // -1868331000
    s21_decimal decimal_check = {{0x6F5C77F8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1121) {
    // 4.65254857E-07
    int f = 888784932;
    // 0.0000004652549
    s21_decimal decimal_check = {{0x46FE05, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1122) {
    // -4.65254857E-07
    int f = -1258698716;
    // -0.0000004652549
    s21_decimal decimal_check = {{0x46FE05, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1123) {
    // 3.06498727E+17
    int f = 1552424159;
    // 306498700000000000
    s21_decimal decimal_check = {{0x999E7800, 0x440E6F1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1124) {
    // -3.06498727E+17
    int f = -595059489;
    // -306498700000000000
    s21_decimal decimal_check = {{0x999E7800, 0x440E6F1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1125) {
    // 1.72322299E-15
    int f = 653809589;
    // 0.000000000000001723223
    s21_decimal decimal_check = {{0x1A4B57, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1126) {
    // -1.72322299E-15
    int f = -1493674059;
    // -0.000000000000001723223
    s21_decimal decimal_check = {{0x1A4B57, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1127) {
    // 3.90493957E-11
    int f = 774618550;
    // 0.0000000000390494
    s21_decimal decimal_check = {{0x5F55E, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1128) {
    // -3.90493957E-11
    int f = -1372865098;
    // -0.0000000000390494
    s21_decimal decimal_check = {{0x5F55E, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1129) {
    // 1.77280512E-09
    int f = 821274377;
    // 0.000000001772805
    s21_decimal decimal_check = {{0x1B0D05, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1130) {
    // -1.77280512E-09
    int f = -1326209271;
    // -0.000000001772805
    s21_decimal decimal_check = {{0x1B0D05, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1131) {
    // 18769876
    int f = 1267676138;
    // 18769880
    s21_decimal decimal_check = {{0x11E67D8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1132) {
    // -18769876
    int f = -879807510;
    // -18769880
    s21_decimal decimal_check = {{0x11E67D8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1133) {
    // 65368.5078
    int f = 1199528066;
    // 65368.51
    s21_decimal decimal_check = {{0x63BE93, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1134) {
    // -65368.5078
    int f = -947955582;
    // -65368.51
    s21_decimal decimal_check = {{0x63BE93, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1135) {
    // 4.27493327E+11
    int f = 1388777773;
    // 427493300000
    s21_decimal decimal_check = {{0x88961720, 0x63, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1136) {
    // -4.27493327E+11
    int f = -758705875;
    // -427493300000
    s21_decimal decimal_check = {{0x88961720, 0x63, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1137) {
    // 1.38941413E-28
    int f = 288366865;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1138) {
    // -1.38941413E-28
    int f = -1859116783;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1139) {
    // 1.91158673E-25
    int f = 376218778;
    // 0.0000000000000000000000001912
    s21_decimal decimal_check = {{0x778, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1140) {
    // -1.91158673E-25
    int f = -1771264870;
    // -0.0000000000000000000000001912
    s21_decimal decimal_check = {{0x778, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1141) {
    // 3.5995933E-16
    int f = 634355871;
    // 0.0000000000000003599593
    s21_decimal decimal_check = {{0x36ECE9, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1142) {
    // -3.5995933E-16
    int f = -1513127777;
    // -0.0000000000000003599593
    s21_decimal decimal_check = {{0x36ECE9, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1143) {
    // 0.423298985
    int f = 1054390949;
    // 0.423299
    s21_decimal decimal_check = {{0x67583, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1144) {
    // -0.423298985
    int f = -1093092699;
    // -0.423299
    s21_decimal decimal_check = {{0x67583, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1145) {
    // 0.0891761109
    int f = 1035379191;
    // 0.08917611
    s21_decimal decimal_check = {{0x88126B, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1146) {
    // -0.0891761109
    int f = -1112104457;
    // -0.08917611
    s21_decimal decimal_check = {{0x88126B, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1147) {
    // 5.87677807E-19
    int f = 556626862;
    // 0.0000000000000000005876778
    s21_decimal decimal_check = {{0x59AC2A, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1148) {
    // -5.87677807E-19
    int f = -1590856786;
    // -0.0000000000000000005876778
    s21_decimal decimal_check = {{0x59AC2A, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1149) {
    // 9846029
    int f = 1259748621;
    // 9846029
    s21_decimal decimal_check = {{0x963D0D, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1150) {
    // -9846029
    int f = -887735027;
    // -9846029
    s21_decimal decimal_check = {{0x963D0D, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1151) {
    // 58364.1836
    int f = 1197734959;
    // 58364.18
    s21_decimal decimal_check = {{0x590E82, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1152) {
    // -58364.1836
    int f = -949748689;
    // -58364.18
    s21_decimal decimal_check = {{0x590E82, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1153) {
    // 1.9882159E+25
    int f = 1770230192;
    // 19882160000000000000000000
    s21_decimal decimal_check = {{0x94C00000, 0xDA419A4, 0x107236, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1154) {
    // -1.9882159E+25
    int f = -377253456;
    // -19882160000000000000000000
    s21_decimal decimal_check = {{0x94C00000, 0xDA419A4, 0x107236, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1155) {
    // 6.2967769E-12
    int f = 752716883;
    // 0.000000000006296777
    s21_decimal decimal_check = {{0x6014C9, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1156) {
    // -6.2967769E-12
    int f = -1394766765;
    // -0.000000000006296777
    s21_decimal decimal_check = {{0x6014C9, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1157) {
    // 24365.6602
    int f = 1186880338;
    // 24365.66
    s21_decimal decimal_check = {{0x252DD6, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1158) {
    // -24365.6602
    int f = -960603310;
    // -24365.66
    s21_decimal decimal_check = {{0x252DD6, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1159) {
    // 0.000724060868
    int f = 977129191;
    // 0.0007240609
    s21_decimal decimal_check = {{0x6E7BA1, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1160) {
    // -0.000724060868
    int f = -1170354457;
    // -0.0007240609
    s21_decimal decimal_check = {{0x6E7BA1, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1161) {
    // 502039808
    int f = 1307534376;
    // 502039800
    s21_decimal decimal_check = {{0x1DEC84F8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1162) {
    // -502039808
    int f = -839949272;
    // -502039800
    s21_decimal decimal_check = {{0x1DEC84F8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1163) {
    // 6.9004946E+16
    int f = 1534404514;
    // 69004950000000000
    s21_decimal decimal_check = {{0xEC7E5C00, 0xF527A2, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1164) {
    // -6.9004946E+16
    int f = -613079134;
    // -69004950000000000
    s21_decimal decimal_check = {{0xEC7E5C00, 0xF527A2, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1165) {
    // 1.79199168E+09
    int f = 1322622783;
    // 1791992000
    s21_decimal decimal_check = {{0x6ACFA0C0, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1166) {
    // -1.79199168E+09
    int f = -824860865;
    // -1791992000
    s21_decimal decimal_check = {{0x6ACFA0C0, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1167) {
    // 6.38212565E+25
    int f = 1783835317;
    // 63821260000000000000000000
    s21_decimal decimal_check = {{0x97B00000, 0x6FE84883, 0x34CAAD, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1168) {
    // -6.38212565E+25
    int f = -363648331;
    // -63821260000000000000000000
    s21_decimal decimal_check = {{0x97B00000, 0x6FE84883, 0x34CAAD, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1169) {
    // 1.53710873E+22
    int f = 1682985260;
    // 15371090000000000000000
    s21_decimal decimal_check = {{0x8F150000, 0x44B9B379, 0x341, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1170) {
    // -1.53710873E+22
    int f = -464498388;
    // -15371090000000000000000
    s21_decimal decimal_check = {{0x8F150000, 0x44B9B379, 0x341, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1171) {
    // 292.734375
    int f = 1133665792;
    // 292.7344
    s21_decimal decimal_check = {{0x2CAAF0, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1172) {
    // -292.734375
    int f = -1013817856;
    // -292.7344
    s21_decimal decimal_check = {{0x2CAAF0, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1173) {
    // 2.64058328
    int f = 1076428625;
    // 2.640583
    s21_decimal decimal_check = {{0x284AC7, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1174) {
    // -2.64058328
    int f = -1071055023;
    // -2.640583
    s21_decimal decimal_check = {{0x284AC7, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1175) {
    // 1.59336006E+11
    int f = 1377068202;
    // 159336000000
    s21_decimal decimal_check = {{0x192A6A00, 0x25, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1176) {
    // -1.59336006E+11
    int f = -770415446;
    // -159336000000
    s21_decimal decimal_check = {{0x192A6A00, 0x25, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1177) {
    // 4.45615473E+15
    int f = 1501384086;
    // 4456155000000000
    s21_decimal decimal_check = {{0x6FD6CE00, 0xFD4D9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1178) {
    // -4.45615473E+15
    int f = -646099562;
    // -4456155000000000
    s21_decimal decimal_check = {{0x6FD6CE00, 0xFD4D9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1179) {
    // 208.460907
    int f = 1129346558;
    // 208.4609
    s21_decimal decimal_check = {{0x1FCF01, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1180) {
    // -208.460907
    int f = -1018137090;
    // -208.4609
    s21_decimal decimal_check = {{0x1FCF01, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1181) {
    // 4.09023416E-19
    int f = 552694239;
    // 0.0000000000000000004090234
    s21_decimal decimal_check = {{0x3E697A, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1182) {
    // -4.09023416E-19
    int f = -1594789409;
    // -0.0000000000000000004090234
    s21_decimal decimal_check = {{0x3E697A, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1183) {
    // 7.23502489E-21
    int f = 503884399;
    // 0.000000000000000000007235025
    s21_decimal decimal_check = {{0x6E65D1, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1184) {
    // -7.23502489E-21
    int f = -1643599249;
    // -0.000000000000000000007235025
    s21_decimal decimal_check = {{0x6E65D1, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1185) {
    // 4.77286522E-17
    int f = 610016268;
    // 0.00000000000000004772865
    s21_decimal decimal_check = {{0x48D401, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1186) {
    // -4.77286522E-17
    int f = -1537467380;
    // -0.00000000000000004772865
    s21_decimal decimal_check = {{0x48D401, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1187) {
    // 2.11739089E+19
    int f = 1603464299;
    // 21173910000000000000
    s21_decimal decimal_check = {{0xF8176000, 0x25D8D6F5, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1188) {
    // -2.11739089E+19
    int f = -544019349;
    // -21173910000000000000
    s21_decimal decimal_check = {{0xF8176000, 0x25D8D6F5, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1189) {
    // 1.8523353E+13
    int f = 1434895983;
    // 18523350000000
    s21_decimal decimal_check = {{0xCDB26180, 0x10D8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1190) {
    // -1.8523353E+13
    int f = -712587665;
    // -18523350000000
    s21_decimal decimal_check = {{0xCDB26180, 0x10D8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1191) {
    // 1.54056884E+22
    int f = 1683015992;
    // 15405690000000000000000
    s21_decimal decimal_check = {{0xFB990000, 0x24E59827, 0x343, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1192) {
    // -1.54056884E+22
    int f = -464467656;
    // -15405690000000000000000
    s21_decimal decimal_check = {{0xFB990000, 0x24E59827, 0x343, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1193) {
    // 5.83757933E-26
    int f = 361793550;
    // 0.0000000000000000000000000584
    s21_decimal decimal_check = {{0x248, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1194) {
    // -5.83757933E-26
    int f = -1785690098;
    // -0.0000000000000000000000000584
    s21_decimal decimal_check = {{0x248, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1195) {
    // 1.97090056E-22
    int f = 460211307;
    // 0.0000000000000000000001970901
    s21_decimal decimal_check = {{0x1E12D5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1196) {
    // -1.97090056E-22
    int f = -1687272341;
    // -0.0000000000000000000001970901
    s21_decimal decimal_check = {{0x1E12D5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1197) {
    // 9.54991615E+14
    int f = 1482236884;
    // 954991600000000
    s21_decimal decimal_check = {{0x4F14DC00, 0x3648F, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1198) {
    // -9.54991615E+14
    int f = -665246764;
    // -954991600000000
    s21_decimal decimal_check = {{0x4F14DC00, 0x3648F, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1199) {
    // 3.71287067E-14
    int f = 690435708;
    // 0.00000000000003712871
    s21_decimal decimal_check = {{0x38A767, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1200) {
    // -3.71287067E-14
    int f = -1457047940;
    // -0.00000000000003712871
    s21_decimal decimal_check = {{0x38A767, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1201) {
    // 1.14038529E-23
    int f = 425497893;
    // 0.0000000000000000000000114039
    s21_decimal decimal_check = {{0x1BD77, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1202) {
    // -1.14038529E-23
    int f = -1721985755;
    // -0.0000000000000000000000114039
    s21_decimal decimal_check = {{0x1BD77, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1203) {
    // 0.000273284328
    int f = 965691290;
    // 0.0002732843
    s21_decimal decimal_check = {{0x29B32B, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1204) {
    // -0.000273284328
    int f = -1181792358;
    // -0.0002732843
    s21_decimal decimal_check = {{0x29B32B, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1205) {
    // 1.95011591E-22
    int f = 460046634;
    // 0.0000000000000000000001950116
    s21_decimal decimal_check = {{0x1DC1A4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1206) {
    // -1.95011591E-22
    int f = -1687437014;
    // -0.0000000000000000000001950116
    s21_decimal decimal_check = {{0x1DC1A4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1207) {
    // 3.86418425E-10
    int f = 802451343;
    // 0.0000000003864184
    s21_decimal decimal_check = {{0x3AF678, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1208) {
    // -3.86418425E-10
    int f = -1345032305;
    // -0.0000000003864184
    s21_decimal decimal_check = {{0x3AF678, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1209) {
    // 1339.66907
    int f = 1151825257;
    // 1339.669
    s21_decimal decimal_check = {{0x147115, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1210) {
    // -1339.66907
    int f = -995658391;
    // -1339.669
    s21_decimal decimal_check = {{0x147115, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1211) {
    // 1.57049718E-09
    int f = 819452149;
    // 0.000000001570497
    s21_decimal decimal_check = {{0x17F6C1, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1212) {
    // -1.57049718E-09
    int f = -1328031499;
    // -0.000000001570497
    s21_decimal decimal_check = {{0x17F6C1, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1213) {
    // 5.50146524E-07
    int f = 890482120;
    // 0.0000005501465
    s21_decimal decimal_check = {{0x53F219, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1214) {
    // -5.50146524E-07
    int f = -1257001528;
    // -0.0000005501465
    s21_decimal decimal_check = {{0x53F219, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1215) {
    // 193.619705
    int f = 1128373925;
    // 193.6197
    s21_decimal decimal_check = {{0x1D8B45, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1216) {
    // -193.619705
    int f = -1019109723;
    // -193.6197
    s21_decimal decimal_check = {{0x1D8B45, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1217) {
    // 8.3393752E-06
    int f = 923527512;
    // 0.000008339375
    s21_decimal decimal_check = {{0x7F3FAF, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1218) {
    // -8.3393752E-06
    int f = -1223956136;
    // -0.000008339375
    s21_decimal decimal_check = {{0x7F3FAF, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1219) {
    // 7.32123356E-15
    int f = 671343419;
    // 0.000000000000007321234
    s21_decimal decimal_check = {{0x6FB692, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1220) {
    // -7.32123356E-15
    int f = -1476140229;
    // -0.000000000000007321234
    s21_decimal decimal_check = {{0x6FB692, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1221) {
    // 3.26110489E+16
    int f = 1525135143;
    // 32611050000000000
    s21_decimal decimal_check = {{0xC300A400, 0x73DB93, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1222) {
    // -3.26110489E+16
    int f = -622348505;
    // -32611050000000000
    s21_decimal decimal_check = {{0xC300A400, 0x73DB93, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1223) {
    // 2.53094841E+23
    int f = 1716937010;
    // 253094800000000000000000
    s21_decimal decimal_check = {{0x67280000, 0x4BEDFE47, 0x3598, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1224) {
    // -2.53094841E+23
    int f = -430546638;
    // -253094800000000000000000
    s21_decimal decimal_check = {{0x67280000, 0x4BEDFE47, 0x3598, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1225) {
    // 2.77539344E+26
    int f = 1801818942;
    // 277539300000000000000000000
    s21_decimal decimal_check = {{0x19100000, 0x99BAB743, 0xE5933B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1226) {
    // -2.77539344E+26
    int f = -345664706;
    // -277539300000000000000000000
    s21_decimal decimal_check = {{0x19100000, 0x99BAB743, 0xE5933B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1227) {
    // 1.67228015E-12
    int f = 736844350;
    // 0.00000000000167228
    s21_decimal decimal_check = {{0x28D3C, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1228) {
    // -1.67228015E-12
    int f = -1410639298;
    // -0.00000000000167228
    s21_decimal decimal_check = {{0x28D3C, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1229) {
    // 3.68016767E+18
    int f = 1582058068;
    // 3680168000000000000
    s21_decimal decimal_check = {{0x31C28000, 0x3312954C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1230) {
    // -3.68016767E+18
    int f = -565425580;
    // -3680168000000000000
    s21_decimal decimal_check = {{0x31C28000, 0x3312954C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1231) {
    // 3.36149537E-06
    int f = 912365069;
    // 0.000003361495
    s21_decimal decimal_check = {{0x334AD7, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1232) {
    // -3.36149537E-06
    int f = -1235118579;
    // -0.000003361495
    s21_decimal decimal_check = {{0x334AD7, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1233) {
    // 1.73420258E+26
    int f = 1796174635;
    // 173420300000000000000000000
    s21_decimal decimal_check = {{0x34B00000, 0x4CF7AFBF, 0x8F732D, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1234) {
    // -1.73420258E+26
    int f = -351309013;
    // -173420300000000000000000000
    s21_decimal decimal_check = {{0x34B00000, 0x4CF7AFBF, 0x8F732D, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1235) {
    // 1.34556352E-23
    int f = 427958922;
    // 0.0000000000000000000000134556
    s21_decimal decimal_check = {{0x20D9C, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1236) {
    // -1.34556352E-23
    int f = -1719524726;
    // -0.0000000000000000000000134556
    s21_decimal decimal_check = {{0x20D9C, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1237) {
    // 2.55882978E-15
    int f = 658006548;
    // 0.00000000000000255883
    s21_decimal decimal_check = {{0x3E78B, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1238) {
    // -2.55882978E-15
    int f = -1489477100;
    // -0.00000000000000255883
    s21_decimal decimal_check = {{0x3E78B, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1239) {
    // 3116964.75
    int f = 1245593235;
    // 3116965
    s21_decimal decimal_check = {{0x2F8FA5, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1240) {
    // -3116964.75
    int f = -901890413;
    // -3116965
    s21_decimal decimal_check = {{0x2F8FA5, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1241) {
    // 7.37311E+24
    int f = 1757620771;
    // 7373110000000000000000000
    s21_decimal decimal_check = {{0xB3180000, 0x18104CFE, 0x61951, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1242) {
    // -7.37311E+24
    int f = -389862877;
    // -7373110000000000000000000
    s21_decimal decimal_check = {{0xB3180000, 0x18104CFE, 0x61951, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1243) {
    // 2.14653485E+11
    int f = 1380444513;
    // 214653500000
    s21_decimal decimal_check = {{0xFA587A60, 0x31, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1244) {
    // -2.14653485E+11
    int f = -767039135;
    // -214653500000
    s21_decimal decimal_check = {{0xFA587A60, 0x31, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1245) {
    // 9.16570264E+13
    int f = 1453766945;
    // 91657030000000
    s21_decimal decimal_check = {{0x90B6DD80, 0x535C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1246) {
    // -9.16570264E+13
    int f = -693716703;
    // -91657030000000
    s21_decimal decimal_check = {{0x90B6DD80, 0x535C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1247) {
    // 6.70139129E-13
    int f = 725393565;
    // 0.0000000000006701391
    s21_decimal decimal_check = {{0x66414F, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1248) {
    // -6.70139129E-13
    int f = -1422090083;
    // -0.0000000000006701391
    s21_decimal decimal_check = {{0x66414F, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1249) {
    // 4.64194306E+11
    int f = 1389897798;
    // 464194300000
    s21_decimal decimal_check = {{0x1422E860, 0x6C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1250) {
    // -4.64194306E+11
    int f = -757585850;
    // -464194300000
    s21_decimal decimal_check = {{0x1422E860, 0x6C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1251) {
    // 1.20859973E+22
    int f = 1680067514;
    // 12086000000000000000000
    s21_decimal decimal_check = {{0xAB180000, 0x2EF185A0, 0x28F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1252) {
    // -1.20859973E+22
    int f = -467416134;
    // -12086000000000000000000
    s21_decimal decimal_check = {{0xAB180000, 0x2EF185A0, 0x28F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1253) {
    // 8.99884305E-23
    int f = 450466852;
    // 0.0000000000000000000000899884
    s21_decimal decimal_check = {{0xDBB2C, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1254) {
    // -8.99884305E-23
    int f = -1697016796;
    // -0.0000000000000000000000899884
    s21_decimal decimal_check = {{0xDBB2C, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1255) {
    // 0.00196332252
    int f = 989899542;
    // 0.001963323
    s21_decimal decimal_check = {{0x1DF53B, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1256) {
    // -0.00196332252
    int f = -1157584106;
    // -0.001963323
    s21_decimal decimal_check = {{0x1DF53B, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1257) {
    // 1.46145184E-14
    int f = 679715529;
    // 0.00000000000001461452
    s21_decimal decimal_check = {{0x164CCC, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1258) {
    // -1.46145184E-14
    int f = -1467768119;
    // -0.00000000000001461452
    s21_decimal decimal_check = {{0x164CCC, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1259) {
    // 324.823212
    int f = 1134717279;
    // 324.8232
    s21_decimal decimal_check = {{0x319068, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1260) {
    // -324.823212
    int f = -1012766369;
    // -324.8232
    s21_decimal decimal_check = {{0x319068, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1261) {
    // 5.13428722E-09
    int f = 833644971;
    // 0.000000005134287
    s21_decimal decimal_check = {{0x4E57CF, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1262) {
    // -5.13428722E-09
    int f = -1313838677;
    // -0.000000005134287
    s21_decimal decimal_check = {{0x4E57CF, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1263) {
    // 1.01611616E+09
    int f = 1316111055;
    // 1016116000
    s21_decimal decimal_check = {{0x3C90B320, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1264) {
    // -1.01611616E+09
    int f = -831372593;
    // -1016116000
    s21_decimal decimal_check = {{0x3C90B320, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1265) {
    // 6.55905241E-09
    int f = 836853257;
    // 0.000000006559052
    s21_decimal decimal_check = {{0x64154C, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1266) {
    // -6.55905241E-09
    int f = -1310630391;
    // -0.000000006559052
    s21_decimal decimal_check = {{0x64154C, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1267) {
    // 3.23067667E-21
    int f = 494148192;
    // 0.000000000000000000003230677
    s21_decimal decimal_check = {{0x314BD5, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1268) {
    // -3.23067667E-21
    int f = -1653335456;
    // -0.000000000000000000003230677
    s21_decimal decimal_check = {{0x314BD5, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1269) {
    // 3.22185504E-19
    int f = 549334860;
    // 0.0000000000000000003221855
    s21_decimal decimal_check = {{0x31295F, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1270) {
    // -3.22185504E-19
    int f = -1598148788;
    // -0.0000000000000000003221855
    s21_decimal decimal_check = {{0x31295F, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1271) {
    // 4.77281494E-27
    int f = 331158040;
    // 0.0000000000000000000000000048
    s21_decimal decimal_check = {{0x30, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1272) {
    // -4.77281494E-27
    int f = -1816325608;
    // -0.0000000000000000000000000048
    s21_decimal decimal_check = {{0x30, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1273) {
    // 1.79968286
    int f = 1072061442;
    // 1.799683
    s21_decimal decimal_check = {{0x1B7603, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1274) {
    // -1.79968286
    int f = -1075422206;
    // -1.799683
    s21_decimal decimal_check = {{0x1B7603, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1275) {
    // 4.70411217E-20
    int f = 526263610;
    // 0.00000000000000000004704112
    s21_decimal decimal_check = {{0x47C770, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1276) {
    // -4.70411217E-20
    int f = -1621220038;
    // -0.00000000000000000004704112
    s21_decimal decimal_check = {{0x47C770, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1277) {
    // 1.18540011E-16
    int f = 621325014;
    // 0.00000000000000011854
    s21_decimal decimal_check = {{0x2E4E, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1278) {
    // -1.18540011E-16
    int f = -1526158634;
    // -0.00000000000000011854
    s21_decimal decimal_check = {{0x2E4E, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1279) {
    // 4.96927477E-08
    int f = 861236673;
    // 0.00000004969275
    s21_decimal decimal_check = {{0x4BD33B, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1280) {
    // -4.96927477E-08
    int f = -1286246975;
    // -0.00000004969275
    s21_decimal decimal_check = {{0x4BD33B, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1281) {
    // 5.31075047E+26
    int f = 1809556930;
    // 531075000000000000000000000
    s21_decimal decimal_check = {{0x2BE00000, 0x7008F9DD, 0x1B74B81, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1282) {
    // -5.31075047E+26
    int f = -337926718;
    // -531075000000000000000000000
    s21_decimal decimal_check = {{0x2BE00000, 0x7008F9DD, 0x1B74B81, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1283) {
    // 6.90798567E+15
    int f = 1506039350;
    // 6907986000000000
    s21_decimal decimal_check = {{0xD3A4B400, 0x188AC6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1284) {
    // -6.90798567E+15
    int f = -641444298;
    // -6907986000000000
    s21_decimal decimal_check = {{0xD3A4B400, 0x188AC6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1285) {
    // 9.48945206E-23
    int f = 451244253;
    // 0.0000000000000000000000948945
    s21_decimal decimal_check = {{0xE7AD1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1286) {
    // -9.48945206E-23
    int f = -1696239395;
    // -0.0000000000000000000000948945
    s21_decimal decimal_check = {{0xE7AD1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1287) {
    // 3.11956083E-09
    int f = 827744229;
    // 0.000000003119561
    s21_decimal decimal_check = {{0x2F99C9, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1288) {
    // -3.11956083E-09
    int f = -1319739419;
    // -0.000000003119561
    s21_decimal decimal_check = {{0x2F99C9, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1289) {
    // 3163.27368
    int f = 1162196065;
    // 3163.274
    s21_decimal decimal_check = {{0x30448A, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1290) {
    // -3163.27368
    int f = -985287583;
    // -3163.274
    s21_decimal decimal_check = {{0x30448A, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1291) {
    // 8.01409661E-25
    int f = 393741879;
    // 0.0000000000000000000000008014
    s21_decimal decimal_check = {{0x1F4E, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1292) {
    // -8.01409661E-25
    int f = -1753741769;
    // -0.0000000000000000000000008014
    s21_decimal decimal_check = {{0x1F4E, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1293) {
    // 2.47684167E+27
    int f = 1828719802;
    // 2476842000000000000000000000
    s21_decimal decimal_check = {{0x66400000, 0xDD7B971F, 0x800CBB1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1294) {
    // -2.47684167E+27
    int f = -318763846;
    // -2476842000000000000000000000
    s21_decimal decimal_check = {{0x66400000, 0xDD7B971F, 0x800CBB1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1295) {
    // 1.41367076E+13
    int f = 1431156567;
    // 14136710000000
    s21_decimal decimal_check = {{0x7593ED80, 0xCDB, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1296) {
    // -1.41367076E+13
    int f = -716327081;
    // -14136710000000
    s21_decimal decimal_check = {{0x7593ED80, 0xCDB, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1297) {
    // 5.89403379E+18
    int f = 1587779489;
    // 5894034000000000000
    s21_decimal decimal_check = {{0xF0132000, 0x51CBD0B1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1298) {
    // -5.89403379E+18
    int f = -559704159;
    // -5894034000000000000
    s21_decimal decimal_check = {{0xF0132000, 0x51CBD0B1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1299) {
    // 2.75599423E-20
    int f = 520234477;
    // 0.00000000000000000002755994
    s21_decimal decimal_check = {{0x2A0D9A, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1300) {
    // -2.75599423E-20
    int f = -1627249171;
    // -0.00000000000000000002755994
    s21_decimal decimal_check = {{0x2A0D9A, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1301) {
    // 2.17559387E+13
    int f = 1436437400;
    // 21755940000000
    s21_decimal decimal_check = {{0x73135100, 0x13C9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1302) {
    // -2.17559387E+13
    int f = -711046248;
    // -21755940000000
    s21_decimal decimal_check = {{0x73135100, 0x13C9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1303) {
    // 2.07021048E+15
    int f = 1491819278;
    // 2070210000000000
    s21_decimal decimal_check = {{0x53A91400, 0x75AD8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1304) {
    // -2.07021048E+15
    int f = -655664370;
    // -2070210000000000
    s21_decimal decimal_check = {{0x53A91400, 0x75AD8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1305) {
    // 3.94179461E+10
    int f = 1360189410;
    // 39417950000
    s21_decimal decimal_check = {{0x2D7E2F30, 0x9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1306) {
    // -3.94179461E+10
    int f = -787294238;
    // -39417950000
    s21_decimal decimal_check = {{0x2D7E2F30, 0x9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1307) {
    // 2.99637916E+26
    int f = 1803016908;
    // 299637900000000000000000000
    s21_decimal decimal_check = {{0x7AB00000, 0x1B610E7E, 0xF7DACB, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1308) {
    // -2.99637916E+26
    int f = -344466740;
    // -299637900000000000000000000
    s21_decimal decimal_check = {{0x7AB00000, 0x1B610E7E, 0xF7DACB, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1309) {
    // 5.10886255E-21
    int f = 499188195;
    // 0.000000000000000000005108863
    s21_decimal decimal_check = {{0x4DF47F, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1310) {
    // -5.10886255E-21
    int f = -1648295453;
    // -0.000000000000000000005108863
    s21_decimal decimal_check = {{0x4DF47F, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1311) {
    // 5.23951718E-17
    int f = 611426637;
    // 0.00000000000000005239517
    s21_decimal decimal_check = {{0x4FF2DD, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1312) {
    // -5.23951718E-17
    int f = -1536057011;
    // -0.00000000000000005239517
    s21_decimal decimal_check = {{0x4FF2DD, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1313) {
    // 3.08618259
    int f = 1078297604;
    // 3.086183
    s21_decimal decimal_check = {{0x2F1767, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1314) {
    // -3.08618259
    int f = -1069186044;
    // -3.086183
    s21_decimal decimal_check = {{0x2F1767, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1315) {
    // 146891104
    int f = 1292637718;
    // 146891100
    s21_decimal decimal_check = {{0x8C1615C, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1316) {
    // -146891104
    int f = -854845930;
    // -146891100
    s21_decimal decimal_check = {{0x8C1615C, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1317) {
    // 0.000414347829
    int f = 970538195;
    // 0.0004143478
    s21_decimal decimal_check = {{0x3F3976, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1318) {
    // -0.000414347829
    int f = -1176945453;
    // -0.0004143478
    s21_decimal decimal_check = {{0x3F3976, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1319) {
    // 0.0548393428
    int f = 1029742392;
    // 0.05483934
    s21_decimal decimal_check = {{0x53AD9E, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1320) {
    // -0.0548393428
    int f = -1117741256;
    // -0.05483934
    s21_decimal decimal_check = {{0x53AD9E, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1321) {
    // 1.77090941E-25
    int f = 375077468;
    // 0.0000000000000000000000001771
    s21_decimal decimal_check = {{0x6EB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1322) {
    // -1.77090941E-25
    int f = -1772406180;
    // -0.0000000000000000000000001771
    s21_decimal decimal_check = {{0x6EB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1323) {
    // 1.31924719E+14
    int f = 1458567228;
    // 131924700000000
    s21_decimal decimal_check = {{0x1CE16F00, 0x77FC, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1324) {
    // -1.31924719E+14
    int f = -688916420;
    // -131924700000000
    s21_decimal decimal_check = {{0x1CE16F00, 0x77FC, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1325) {
    // 3.20414537E-23
    int f = 437973350;
    // 0.0000000000000000000000320415
    s21_decimal decimal_check = {{0x4E39F, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1326) {
    // -3.20414537E-23
    int f = -1709510298;
    // -0.0000000000000000000000320415
    s21_decimal decimal_check = {{0x4E39F, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1327) {
    // 1.33183601E+10
    int f = 1346794883;
    // 13318360000
    s21_decimal decimal_check = {{0x19D60BC0, 0x3, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1328) {
    // -1.33183601E+10
    int f = -800688765;
    // -13318360000
    s21_decimal decimal_check = {{0x19D60BC0, 0x3, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1329) {
    // 7.57778219E+11
    int f = 1395683098;
    // 757778200000
    s21_decimal decimal_check = {{0x6F19B5C0, 0xB0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1330) {
    // -7.57778219E+11
    int f = -751800550;
    // -757778200000
    s21_decimal decimal_check = {{0x6F19B5C0, 0xB0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1331) {
    // 3.17968049E+25
    int f = 1775397346;
    // 31796800000000000000000000
    s21_decimal decimal_check = {{0xD1000000, 0xFB5E1571, 0x1A4D3B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1332) {
    // -3.17968049E+25
    int f = -372086302;
    // -31796800000000000000000000
    s21_decimal decimal_check = {{0xD1000000, 0xFB5E1571, 0x1A4D3B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1333) {
    // 3.91102361E-07
    int f = 886175923;
    // 0.0000003911024
    s21_decimal decimal_check = {{0x3BAD70, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1334) {
    // -3.91102361E-07
    int f = -1261307725;
    // -0.0000003911024
    s21_decimal decimal_check = {{0x3BAD70, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1335) {
    // 865835520
    int f = 1313762920;
    // 865835500
    s21_decimal decimal_check = {{0x339B99EC, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1336) {
    // -865835520
    int f = -833720728;
    // -865835500
    s21_decimal decimal_check = {{0x339B99EC, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1337) {
    // 2.60914322E+24
    int f = 1745494140;
    // 2609143000000000000000000
    s21_decimal decimal_check = {{0x5D7C0000, 0xECEA0BEC, 0x22881, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1338) {
    // -2.60914322E+24
    int f = -401989508;
    // -2609143000000000000000000
    s21_decimal decimal_check = {{0x5D7C0000, 0xECEA0BEC, 0x22881, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1339) {
    // 7739107
    int f = 1256992198;
    // 7739107
    s21_decimal decimal_check = {{0x7616E3, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1340) {
    // -7739107
    int f = -890491450;
    // -7739107
    s21_decimal decimal_check = {{0x7616E3, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1341) {
    // 9.2851123E+11
    int f = 1398288277;
    // 928511200000
    s21_decimal decimal_check = {{0x2F948B00, 0xD8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1342) {
    // -9.2851123E+11
    int f = -749195371;
    // -928511200000
    s21_decimal decimal_check = {{0x2F948B00, 0xD8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1343) {
    // 37293544
    int f = 1276003194;
    // 37293540
    s21_decimal decimal_check = {{0x2390DE4, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1344) {
    // -37293544
    int f = -871480454;
    // -37293540
    s21_decimal decimal_check = {{0x2390DE4, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1345) {
    // 5.75597363E+10
    int f = 1364618558;
    // 57559740000
    s21_decimal decimal_check = {{0x66D3EE60, 0xD, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1346) {
    // -5.75597363E+10
    int f = -782865090;
    // -57559740000
    s21_decimal decimal_check = {{0x66D3EE60, 0xD, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1347) {
    // 2.57581978E+10
    int f = 1354754525;
    // 25758200000
    s21_decimal decimal_check = {{0xFF4EF0C0, 0x5, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1348) {
    // -2.57581978E+10
    int f = -792729123;
    // -25758200000
    s21_decimal decimal_check = {{0xFF4EF0C0, 0x5, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1349) {
    // 0.00292291376
    int f = 994020955;
    // 0.002922914
    s21_decimal decimal_check = {{0x2C99A2, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1350) {
    // -0.00292291376
    int f = -1153462693;
    // -0.002922914
    s21_decimal decimal_check = {{0x2C99A2, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1351) {
    // 5.31412291E+26
    int f = 1809566071;
    // 531412300000000000000000000
    s21_decimal decimal_check = {{0x65B00000, 0x81DCD5DF, 0x1B792EE, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1352) {
    // -5.31412291E+26
    int f = -337917577;
    // -531412300000000000000000000
    s21_decimal decimal_check = {{0x65B00000, 0x81DCD5DF, 0x1B792EE, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1353) {
    // 2.28202243E-05
    int f = 935292431;
    // 0.00002282022
    s21_decimal decimal_check = {{0x22D226, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1354) {
    // -2.28202243E-05
    int f = -1212191217;
    // -0.00002282022
    s21_decimal decimal_check = {{0x22D226, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1355) {
    // 1.50320475E-16
    int f = 623726278;
    // 0.0000000000000001503205
    s21_decimal decimal_check = {{0x16EFE5, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1356) {
    // -1.50320475E-16
    int f = -1523757370;
    // -0.0000000000000001503205
    s21_decimal decimal_check = {{0x16EFE5, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1357) {
    // 105.940971
    int f = 1121182151;
    // 105.941
    s21_decimal decimal_check = {{0x19DD5, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1358) {
    // -105.940971
    int f = -1026301497;
    // -105.941
    s21_decimal decimal_check = {{0x19DD5, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1359) {
    // 0.00288531766
    int f = 993859481;
    // 0.002885318
    s21_decimal decimal_check = {{0x2C06C6, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1360) {
    // -0.00288531766
    int f = -1153624167;
    // -0.002885318
    s21_decimal decimal_check = {{0x2C06C6, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1361) {
    // 2.21113903E+12
    int f = 1409332362;
    // 2211139000000
    s21_decimal decimal_check = {{0xD22796C0, 0x202, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1362) {
    // -2.21113903E+12
    int f = -738151286;
    // -2211139000000
    s21_decimal decimal_check = {{0xD22796C0, 0x202, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1363) {
    // 3.15532139E-18
    int f = 577294934;
    // 0.000000000000000003155321
    s21_decimal decimal_check = {{0x302579, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1364) {
    // -3.15532139E-18
    int f = -1570188714;
    // -0.000000000000000003155321
    s21_decimal decimal_check = {{0x302579, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1365) {
    // 0.000354833872
    int f = 968493311;
    // 0.0003548339
    s21_decimal decimal_check = {{0x3624B3, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1366) {
    // -0.000354833872
    int f = -1178990337;
    // -0.0003548339
    s21_decimal decimal_check = {{0x3624B3, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1367) {
    // 2.62618927E+23
    int f = 1717465703;
    // 262618900000000000000000
    s21_decimal decimal_check = {{0x39020000, 0x995E576F, 0x379C, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1368) {
    // -2.62618927E+23
    int f = -430017945;
    // -262618900000000000000000
    s21_decimal decimal_check = {{0x39020000, 0x995E576F, 0x379C, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1369) {
    // 14750546
    int f = 1264653138;
    // 14750550
    s21_decimal decimal_check = {{0xE11356, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1370) {
    // -14750546
    int f = -882830510;
    // -14750550
    s21_decimal decimal_check = {{0xE11356, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1371) {
    // 1.20711491E-06
    int f = 899810343;
    // 0.000001207115
    s21_decimal decimal_check = {{0x126B4B, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1372) {
    // -1.20711491E-06
    int f = -1247673305;
    // -0.000001207115
    s21_decimal decimal_check = {{0x126B4B, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1373) {
    // 1.325584E+16
    int f = 1513906295;
    // 13255840000000000
    s21_decimal decimal_check = {{0xC2664000, 0x2F181D, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1374) {
    // -1.325584E+16
    int f = -633577353;
    // -13255840000000000
    s21_decimal decimal_check = {{0xC2664000, 0x2F181D, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1375) {
    // 2.15183559E-17
    int f = 600209608;
    // 0.00000000000000002151836
    s21_decimal decimal_check = {{0x20D59C, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1376) {
    // -2.15183559E-17
    int f = -1547274040;
    // -0.00000000000000002151836
    s21_decimal decimal_check = {{0x20D59C, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1377) {
    // 1.62191279E+17
    int f = 1544556039;
    // 162191300000000000
    s21_decimal decimal_check = {{0xC628A800, 0x2403820, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1378) {
    // -1.62191279E+17
    int f = -602927609;
    // -162191300000000000
    s21_decimal decimal_check = {{0xC628A800, 0x2403820, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1379) {
    // 5.96423694E+15
    int f = 1504281481;
    // 5964237000000000
    s21_decimal decimal_check = {{0x23BDC200, 0x153071, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1380) {
    // -5.96423694E+15
    int f = -643202167;
    // -5964237000000000
    s21_decimal decimal_check = {{0x23BDC200, 0x153071, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1381) {
    // 7.73121955E-10
    int f = 810845087;
    // 0.000000000773122
    s21_decimal decimal_check = {{0xBCC02, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1382) {
    // -7.73121955E-10
    int f = -1336638561;
    // -0.000000000773122
    s21_decimal decimal_check = {{0xBCC02, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1383) {
    // 6.14825472E+09
    int f = 1337408374;
    // 6148255000
    s21_decimal decimal_check = {{0x6E76ED18, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1384) {
    // -6.14825472E+09
    int f = -810075274;
    // -6148255000
    s21_decimal decimal_check = {{0x6E76ED18, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1385) {
    // 56.4667435
    int f = 1113710066;
    // 56.46674
    s21_decimal decimal_check = {{0x562952, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1386) {
    // -56.4667435
    int f = -1033773582;
    // -56.46674
    s21_decimal decimal_check = {{0x562952, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1387) {
    // 2128.07227
    int f = 1157955880;
    // 2128.072
    s21_decimal decimal_check = {{0x2078C8, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1388) {
    // -2128.07227
    int f = -989527768;
    // -2128.072
    s21_decimal decimal_check = {{0x2078C8, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1389) {
    // 2.84761773E-21
    int f = 492251376;
    // 0.000000000000000000002847618
    s21_decimal decimal_check = {{0x2B7382, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1390) {
    // -2.84761773E-21
    int f = -1655232272;
    // -0.000000000000000000002847618
    s21_decimal decimal_check = {{0x2B7382, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1391) {
    // 2.0259156E-26
    int f = 348693264;
    // 0.0000000000000000000000000203
    s21_decimal decimal_check = {{0xCB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1392) {
    // -2.0259156E-26
    int f = -1798790384;
    // -0.0000000000000000000000000203
    s21_decimal decimal_check = {{0xCB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1393) {
    // 0.524816155
    int f = 1057380954;
    // 0.5248162
    s21_decimal decimal_check = {{0x5014A2, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1394) {
    // -0.524816155
    int f = -1090102694;
    // -0.5248162
    s21_decimal decimal_check = {{0x5014A2, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1395) {
    // 3.49638345E-15
    int f = 662434020;
    // 0.000000000000003496383
    s21_decimal decimal_check = {{0x3559BF, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1396) {
    // -3.49638345E-15
    int f = -1485049628;
    // -0.000000000000003496383
    s21_decimal decimal_check = {{0x3559BF, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1397) {
    // 0.000998685719
    int f = 981657173;
    // 0.0009986857
    s21_decimal decimal_check = {{0x986329, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1398) {
    // -0.000998685719
    int f = -1165826475;
    // -0.0009986857
    s21_decimal decimal_check = {{0x986329, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1399) {
    // 9.93013964E-05
    int f = 953171976;
    // 0.0000993014
    s21_decimal decimal_check = {{0xF26F6, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1400) {
    // -9.93013964E-05
    int f = -1194311672;
    // -0.0000993014
    s21_decimal decimal_check = {{0xF26F6, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1401) {
    // 1.02353072
    int f = 1065550606;
    // 1.023531
    s21_decimal decimal_check = {{0xF9E2B, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1402) {
    // -1.02353072
    int f = -1081933042;
    // -1.023531
    s21_decimal decimal_check = {{0xF9E2B, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1403) {
    // 1.5095988E-20
    int f = 512660444;
    // 0.00000000000000000001509599
    s21_decimal decimal_check = {{0x1708DF, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1404) {
    // -1.5095988E-20
    int f = -1634823204;
    // -0.00000000000000000001509599
    s21_decimal decimal_check = {{0x1708DF, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1405) {
    // 2630425.25
    int f = 1243647077;
    // 2630425
    s21_decimal decimal_check = {{0x282319, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1406) {
    // -2630425.25
    int f = -903836571;
    // -2630425
    s21_decimal decimal_check = {{0x282319, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1407) {
    // 7.49090375E-27
    int f = 336879461;
    // 0.0000000000000000000000000075
    s21_decimal decimal_check = {{0x4B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1408) {
    // -7.49090375E-27
    int f = -1810604187;
    // -0.0000000000000000000000000075
    s21_decimal decimal_check = {{0x4B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1409) {
    // 1.49792864E-14
    int f = 679930850;
    // 0.00000000000001497929
    s21_decimal decimal_check = {{0x16DB49, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1410) {
    // -1.49792864E-14
    int f = -1467552798;
    // -0.00000000000001497929
    s21_decimal decimal_check = {{0x16DB49, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1411) {
    // 5.59578775E+23
    int f = 1726807463;
    // 559578800000000000000000
    s21_decimal decimal_check = {{0xFB780000, 0xD3D92073, 0x767E, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1412) {
    // -5.59578775E+23
    int f = -420676185;
    // -559578800000000000000000
    s21_decimal decimal_check = {{0xFB780000, 0xD3D92073, 0x767E, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1413) {
    // 3.56963841E+22
    int f = 1693573979;
    // 35696380000000000000000
    s21_decimal decimal_check = {{0x1E660000, 0x1AC98279, 0x78F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1414) {
    // -3.56963841E+22
    int f = -453909669;
    // -35696380000000000000000
    s21_decimal decimal_check = {{0x1E660000, 0x1AC98279, 0x78F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1415) {
    // 7.92133188E+17
    int f = 1563419535;
    // 792133200000000000
    s21_decimal decimal_check = {{0xD0CB2000, 0xAFE38F2, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1416) {
    // -7.92133188E+17
    int f = -584064113;
    // -792133200000000000
    s21_decimal decimal_check = {{0xD0CB2000, 0xAFE38F2, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1417) {
    // 2.71498241E-10
    int f = 798310907;
    // 0.0000000002714982
    s21_decimal decimal_check = {{0x296D66, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1418) {
    // -2.71498241E-10
    int f = -1349172741;
    // -0.0000000002714982
    s21_decimal decimal_check = {{0x296D66, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1419) {
    // 9.38994614E+26
    int f = 1816276470;
    // 938994600000000000000000000
    s21_decimal decimal_check = {{0xA5A00000, 0x437BCE0A, 0x308B7D7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1420) {
    // -9.38994614E+26
    int f = -331207178;
    // -938994600000000000000000000
    s21_decimal decimal_check = {{0xA5A00000, 0x437BCE0A, 0x308B7D7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1421) {
    // 1172761
    int f = 1234118856;
    // 1172761
    s21_decimal decimal_check = {{0x11E519, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1422) {
    // -1172761
    int f = -913364792;
    // -1172761
    s21_decimal decimal_check = {{0x11E519, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1423) {
    // 2.02797484E-22
    int f = 460663496;
    // 0.0000000000000000000002027975
    s21_decimal decimal_check = {{0x1EF1C7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1424) {
    // -2.02797484E-22
    int f = -1686820152;
    // -0.0000000000000000000002027975
    s21_decimal decimal_check = {{0x1EF1C7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1425) {
    // 1.40880926E+24
    int f = 1737828826;
    // 1408809000000000000000000
    s21_decimal decimal_check = {{0x6B040000, 0xB05D1E04, 0x12A53, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1426) {
    // -1.40880926E+24
    int f = -409654822;
    // -1408809000000000000000000
    s21_decimal decimal_check = {{0x6B040000, 0xB05D1E04, 0x12A53, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1427) {
    // 1.40233397E+17
    int f = 1543051972;
    // 140233400000000000
    s21_decimal decimal_check = {{0xC8A53000, 0x1F23588, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1428) {
    // -1.40233397E+17
    int f = -604431676;
    // -140233400000000000
    s21_decimal decimal_check = {{0xC8A53000, 0x1F23588, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1429) {
    // 12088.0547
    int f = 1178394680;
    // 12088.05
    s21_decimal decimal_check = {{0x1271E5, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1430) {
    // -12088.0547
    int f = -969088968;
    // -12088.05
    s21_decimal decimal_check = {{0x1271E5, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1431) {
    // 2.78321213E+10
    int f = 1355767183;
    // 27832120000
    s21_decimal decimal_check = {{0x7AEC72C0, 0x6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1432) {
    // -2.78321213E+10
    int f = -791716465;
    // -27832120000
    s21_decimal decimal_check = {{0x7AEC72C0, 0x6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1433) {
    // 1.94412142E-21
    int f = 487777479;
    // 0.000000000000000000001944121
    s21_decimal decimal_check = {{0x1DAA39, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1434) {
    // -1.94412142E-21
    int f = -1659706169;
    // -0.000000000000000000001944121
    s21_decimal decimal_check = {{0x1DAA39, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1435) {
    // 1.21054832E-28
    int f = 286880906;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1436) {
    // -1.21054832E-28
    int f = -1860602742;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1437) {
    // 8.96247499E+20
    int f = 1648515003;
    // 896247500000000000000
    s21_decimal decimal_check = {{0x2BE8C000, 0x95EEC0BA, 0x30, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1438) {
    // -8.96247499E+20
    int f = -498968645;
    // -896247500000000000000
    s21_decimal decimal_check = {{0x2BE8C000, 0x95EEC0BA, 0x30, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1439) {
    // 6.23037486E-21
    int f = 501964925;
    // 0.000000000000000000006230375
    s21_decimal decimal_check = {{0x5F1167, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1440) {
    // -6.23037486E-21
    int f = -1645518723;
    // -0.000000000000000000006230375
    s21_decimal decimal_check = {{0x5F1167, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1441) {
    // 1.1750562E+27
    int f = 1819475701;
    // 1175056000000000000000000000
    s21_decimal decimal_check = {{0xAA000000, 0x664C99F6, 0x3CBFBC9, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1442) {
    // -1.1750562E+27
    int f = -328007947;
    // -1175056000000000000000000000
    s21_decimal decimal_check = {{0xAA000000, 0x664C99F6, 0x3CBFBC9, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1443) {
    // 8.99281548E+27
    int f = 1843950966;
    // 8992815000000000000000000000
    s21_decimal decimal_check = {{0xDF600000, 0xFCEE53A6, 0x1D0EAEA5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1444) {
    // -8.99281548E+27
    int f = -303532682;
    // -8992815000000000000000000000
    s21_decimal decimal_check = {{0xDF600000, 0xFCEE53A6, 0x1D0EAEA5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1445) {
    // 1.3030496E+09
    int f = 1318802923;
    // 1303050000
    s21_decimal decimal_check = {{0x4DAAF710, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1446) {
    // -1.3030496E+09
    int f = -828680725;
    // -1303050000
    s21_decimal decimal_check = {{0x4DAAF710, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1447) {
    // 2.29178751E+26
    int f = 1799197309;
    // 229178800000000000000000000
    s21_decimal decimal_check = {{0xE8C00000, 0xA4731590, 0xBD927F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1448) {
    // -2.29178751E+26
    int f = -348286339;
    // -229178800000000000000000000
    s21_decimal decimal_check = {{0xE8C00000, 0xA4731590, 0xBD927F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1449) {
    // 5.05870151E-23
    int f = 443850673;
    // 0.000000000000000000000050587
    s21_decimal decimal_check = {{0xC59B, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1450) {
    // -5.05870151E-23
    int f = -1703632975;
    // -0.000000000000000000000050587
    s21_decimal decimal_check = {{0xC59B, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1451) {
    // 1.46370735E+20
    int f = 1627253162;
    // 146370700000000000000
    s21_decimal decimal_check = {{0x1144C000, 0xEF4D3025, 0x7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1452) {
    // -1.46370735E+20
    int f = -520230486;
    // -146370700000000000000
    s21_decimal decimal_check = {{0x1144C000, 0xEF4D3025, 0x7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1453) {
    // 6.48644231E+23
    int f = 1728666387;
    // 648644200000000000000000
    s21_decimal decimal_check = {{0x57A40000, 0x129203BD, 0x895B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1454) {
    // -6.48644231E+23
    int f = -418817261;
    // -648644200000000000000000
    s21_decimal decimal_check = {{0x57A40000, 0x129203BD, 0x895B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1455) {
    // 1.31758809E+25
    int f = 1764647327;
    // 13175880000000000000000000
    s21_decimal decimal_check = {{0xC4200000, 0xE2D23BE3, 0xAE619, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1456) {
    // -1.31758809E+25
    int f = -382836321;
    // -13175880000000000000000000
    s21_decimal decimal_check = {{0xC4200000, 0xE2D23BE3, 0xAE619, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1457) {
    // 9.20671752E-08
    int f = 868595319;
    // 0.00000009206718
    s21_decimal decimal_check = {{0x8C7BBE, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1458) {
    // -9.20671752E-08
    int f = -1278888329;
    // -0.00000009206718
    s21_decimal decimal_check = {{0x8C7BBE, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1459) {
    // 1.4702007E-15
    int f = 651419861;
    // 0.000000000000001470201
    s21_decimal decimal_check = {{0x166EF9, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1460) {
    // -1.4702007E-15
    int f = -1496063787;
    // -0.000000000000001470201
    s21_decimal decimal_check = {{0x166EF9, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1461) {
    // 2.53511968E-12
    int f = 741500072;
    // 0.00000000000253512
    s21_decimal decimal_check = {{0x3DE48, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1462) {
    // -2.53511968E-12
    int f = -1405983576;
    // -0.00000000000253512
    s21_decimal decimal_check = {{0x3DE48, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1463) {
    // 3.10351712E+27
    int f = 1830843061;
    // 3103517000000000000000000000
    s21_decimal decimal_check = {{0x18200000, 0xAFF1E4ED, 0xA072B49, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1464) {
    // -3.10351712E+27
    int f = -316640587;
    // -3103517000000000000000000000
    s21_decimal decimal_check = {{0x18200000, 0xAFF1E4ED, 0xA072B49, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1465) {
    // 34653.9805
    int f = 1191665147;
    // 34653.98
    s21_decimal decimal_check = {{0x34E0B6, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1466) {
    // -34653.9805
    int f = -955818501;
    // -34653.98
    s21_decimal decimal_check = {{0x34E0B6, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1467) {
    // 1.06060081E+24
    int f = 1734383433;
    // 1060601000000000000000000
    s21_decimal decimal_check = {{0xC8440000, 0x4BA07311, 0xE097, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1468) {
    // -1.06060081E+24
    int f = -413100215;
    // -1060601000000000000000000
    s21_decimal decimal_check = {{0xC8440000, 0x4BA07311, 0xE097, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1469) {
    // 6.64278231E+14
    int f = 1477904917;
    // 664278200000000
    s21_decimal decimal_check = {{0x52249E00, 0x25C28, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1470) {
    // -6.64278231E+14
    int f = -669578731;
    // -664278200000000
    s21_decimal decimal_check = {{0x52249E00, 0x25C28, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1471) {
    // 7.71458417E-07
    int f = 894375480;
    // 0.0000007714584
    s21_decimal decimal_check = {{0x75B718, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1472) {
    // -7.71458417E-07
    int f = -1253108168;
    // -0.0000007714584
    s21_decimal decimal_check = {{0x75B718, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1473) {
    // 6.15538454E-07
    int f = 891632507;
    // 0.0000006155385
    s21_decimal decimal_check = {{0x5DEC79, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1474) {
    // -6.15538454E-07
    int f = -1255851141;
    // -0.0000006155385
    s21_decimal decimal_check = {{0x5DEC79, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1475) {
    // 2.26592457E-16
    int f = 629317413;
    // 0.0000000000000002265925
    s21_decimal decimal_check = {{0x229345, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1476) {
    // -2.26592457E-16
    int f = -1518166235;
    // -0.0000000000000002265925
    s21_decimal decimal_check = {{0x229345, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1477) {
    // 0.088127248
    int f = 1035238415;
    // 0.08812725
    s21_decimal decimal_check = {{0x8678B5, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1478) {
    // -0.088127248
    int f = -1112245233;
    // -0.08812725
    s21_decimal decimal_check = {{0x8678B5, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1479) {
    // 13.0652351
    int f = 1095830324;
    // 13.06524
    s21_decimal decimal_check = {{0x13EF9C, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1480) {
    // -13.0652351
    int f = -1051653324;
    // -13.06524
    s21_decimal decimal_check = {{0x13EF9C, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1481) {
    // 1.60397633E-11
    int f = 764221014;
    // 0.00000000001603976
    s21_decimal decimal_check = {{0x187988, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1482) {
    // -1.60397633E-11
    int f = -1383262634;
    // -0.00000000001603976
    s21_decimal decimal_check = {{0x187988, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1483) {
    // 1.64273759E+16
    int f = 1516860018;
    // 16427380000000000
    s21_decimal decimal_check = {{0x757D8800, 0x3A5C9D, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1484) {
    // -1.64273759E+16
    int f = -630623630;
    // -16427380000000000
    s21_decimal decimal_check = {{0x757D8800, 0x3A5C9D, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1485) {
    // 3.81643284E+10
    int f = 1359883351;
    // 38164330000
    s21_decimal decimal_check = {{0xE2C57610, 0x8, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1486) {
    // -3.81643284E+10
    int f = -787600297;
    // -38164330000
    s21_decimal decimal_check = {{0xE2C57610, 0x8, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1487) {
    // 179132864
    int f = 1294652828;
    // 179132900
    s21_decimal decimal_check = {{0xAAD59E4, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1488) {
    // -179132864
    int f = -852830820;
    // -179132900
    s21_decimal decimal_check = {{0xAAD59E4, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1489) {
    // 4.7837416E+27
    int f = 1836535883;
    // 4783742000000000000000000000
    s21_decimal decimal_check = {{0x52C00000, 0x73547746, 0xF7504C5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1490) {
    // -4.7837416E+27
    int f = -310947765;
    // -4783742000000000000000000000
    s21_decimal decimal_check = {{0x52C00000, 0x73547746, 0xF7504C5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1491) {
    // 1.90140623E-26
    int f = 347885152;
    // 0.000000000000000000000000019
    s21_decimal decimal_check = {{0x13, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1492) {
    // -1.90140623E-26
    int f = -1799598496;
    // -0.000000000000000000000000019
    s21_decimal decimal_check = {{0x13, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1493) {
    // 4080.44678
    int f = 1165952806;
    // 4080.447
    s21_decimal decimal_check = {{0x3E433F, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1494) {
    // -4080.44678
    int f = -981530842;
    // -4080.447
    s21_decimal decimal_check = {{0x3E433F, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1495) {
    // 395.443115
    int f = 1137031352;
    // 395.4431
    s21_decimal decimal_check = {{0x3C56FF, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1496) {
    // -395.443115
    int f = -1010452296;
    // -395.4431
    s21_decimal decimal_check = {{0x3C56FF, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1497) {
    // 9.29361688E+16
    int f = 1537545850;
    // 92936170000000000
    s21_decimal decimal_check = {{0x47A2A400, 0x14A2CF4, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1498) {
    // -9.29361688E+16
    int f = -609937798;
    // -92936170000000000
    s21_decimal decimal_check = {{0x47A2A400, 0x14A2CF4, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1499) {
    // 5.07934996E-14
    int f = 694468843;
    // 0.0000000000000507935
    s21_decimal decimal_check = {{0x7C01F, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1500) {
    // -5.07934996E-14
    int f = -1453014805;
    // -0.0000000000000507935
    s21_decimal decimal_check = {{0x7C01F, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1501) {
    // 5.0406574E+12
    int f = 1418900435;
    // 5040657000000
    s21_decimal decimal_check = {{0x9E91E640, 0x495, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1502) {
    // -5.0406574E+12
    int f = -728583213;
    // -5040657000000
    s21_decimal decimal_check = {{0x9E91E640, 0x495, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1503) {
    // 4.58969321E-11
    int f = 776592218;
    // 0.00000000004589693
    s21_decimal decimal_check = {{0x46087D, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1504) {
    // -4.58969321E-11
    int f = -1370891430;
    // -0.00000000004589693
    s21_decimal decimal_check = {{0x46087D, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1505) {
    // 1.02021675E-18
    int f = 563515059;
    // 0.000000000000000001020217
    s21_decimal decimal_check = {{0xF9139, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1506) {
    // -1.02021675E-18
    int f = -1583968589;
    // -0.000000000000000001020217
    s21_decimal decimal_check = {{0xF9139, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1507) {
    // 3.23569185E-21
    int f = 494173026;
    // 0.000000000000000000003235692
    s21_decimal decimal_check = {{0x315F6C, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1508) {
    // -3.23569185E-21
    int f = -1653310622;
    // -0.000000000000000000003235692
    s21_decimal decimal_check = {{0x315F6C, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1509) {
    // 4.1347666E-14
    int f = 691680925;
    // 0.00000000000004134767
    s21_decimal decimal_check = {{0x3F176F, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1510) {
    // -4.1347666E-14
    int f = -1455802723;
    // -0.00000000000004134767
    s21_decimal decimal_check = {{0x3F176F, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1511) {
    // 2.25111083E-10
    int f = 796361507;
    // 0.0000000002251111
    s21_decimal decimal_check = {{0x225967, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1512) {
    // -2.25111083E-10
    int f = -1351122141;
    // -0.0000000002251111
    s21_decimal decimal_check = {{0x225967, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1513) {
    // 1.18348621E-11
    int f = 760230779;
    // 0.00000000001183486
    s21_decimal decimal_check = {{0x120EFE, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1514) {
    // -1.18348621E-11
    int f = -1387252869;
    // -0.00000000001183486
    s21_decimal decimal_check = {{0x120EFE, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1515) {
    // 0.00585740153
    int f = 1002434418;
    // 0.005857402
    s21_decimal decimal_check = {{0x59607A, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1516) {
    // -0.00585740153
    int f = -1145049230;
    // -0.005857402
    s21_decimal decimal_check = {{0x59607A, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1517) {
    // 1.38927671E+14
    int f = 1459402045;
    // 138927700000000
    s21_decimal decimal_check = {{0xA0353D00, 0x7E5A, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1518) {
    // -1.38927671E+14
    int f = -688081603;
    // -138927700000000
    s21_decimal decimal_check = {{0xA0353D00, 0x7E5A, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1519) {
    // 1.99465274E-16
    int f = 627439554;
    // 0.0000000000000001994653
    s21_decimal decimal_check = {{0x1E6F9D, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1520) {
    // -1.99465274E-16
    int f = -1520044094;
    // -0.0000000000000001994653
    s21_decimal decimal_check = {{0x1E6F9D, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1521) {
    // 4.33683636E+17
    int f = 1556125727;
    // 433683600000000000
    s21_decimal decimal_check = {{0xBAE9A000, 0x604C0EF, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1522) {
    // -4.33683636E+17
    int f = -591357921;
    // -433683600000000000
    s21_decimal decimal_check = {{0xBAE9A000, 0x604C0EF, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1523) {
    // 1.41147295E+15
    int f = 1486911301;
    // 1411473000000000
    s21_decimal decimal_check = {{0x2AC66A00, 0x503BA, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1524) {
    // -1.41147295E+15
    int f = -660572347;
    // -1411473000000000
    s21_decimal decimal_check = {{0x2AC66A00, 0x503BA, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1525) {
    // 4.42169156E-14
    int f = 692527778;
    // 0.00000000000004421692
    s21_decimal decimal_check = {{0x43783C, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1526) {
    // -4.42169156E-14
    int f = -1454955870;
    // -0.00000000000004421692
    s21_decimal decimal_check = {{0x43783C, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1527) {
    // 9.34666258E+22
    int f = 1704875696;
    // 93466630000000000000000
    s21_decimal decimal_check = {{0x14A70000, 0xD60EE992, 0x13CA, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1528) {
    // -9.34666258E+22
    int f = -442607952;
    // -93466630000000000000000
    s21_decimal decimal_check = {{0x14A70000, 0xD60EE992, 0x13CA, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1529) {
    // 3.69914818
    int f = 1080868568;
    // 3.699148
    s21_decimal decimal_check = {{0x3871CC, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1530) {
    // -3.69914818
    int f = -1066615080;
    // -3.699148
    s21_decimal decimal_check = {{0x3871CC, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1531) {
    // 0.000194235196
    int f = 961260445;
    // 0.0001942352
    s21_decimal decimal_check = {{0x1DA350, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1532) {
    // -0.000194235196
    int f = -1186223203;
    // -0.0001942352
    s21_decimal decimal_check = {{0x1DA350, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1533) {
    // 1.47526702E-09
    int f = 818594392;
    // 0.000000001475267
    s21_decimal decimal_check = {{0x1682C3, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1534) {
    // -1.47526702E-09
    int f = -1328889256;
    // -0.000000001475267
    s21_decimal decimal_check = {{0x1682C3, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1535) {
    // 6.55416339E+17
    int f = 1561430043;
    // 655416300000000000
    s21_decimal decimal_check = {{0xFD803800, 0x91881A6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1536) {
    // -6.55416339E+17
    int f = -586053605;
    // -655416300000000000
    s21_decimal decimal_check = {{0xFD803800, 0x91881A6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1537) {
    // 5.50590079E+19
    int f = 1614743097;
    // 55059010000000000000
    s21_decimal decimal_check = {{0x3EAE2000, 0xFC18E5E1, 0x2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1538) {
    // -5.50590079E+19
    int f = -532740551;
    // -55059010000000000000
    s21_decimal decimal_check = {{0x3EAE2000, 0xFC18E5E1, 0x2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1539) {
    // 7.84344106E+27
    int f = 1842003850;
    // 7843441000000000000000000000
    s21_decimal decimal_check = {{0x4A00000, 0x991CAE08, 0x1957F13C, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1540) {
    // -7.84344106E+27
    int f = -305479798;
    // -7843441000000000000000000000
    s21_decimal decimal_check = {{0x4A00000, 0x991CAE08, 0x1957F13C, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1541) {
    // 2.23491388E-22
    int f = 461838238;
    // 0.0000000000000000000002234914
    s21_decimal decimal_check = {{0x221A22, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1542) {
    // -2.23491388E-22
    int f = -1685645410;
    // -0.0000000000000000000002234914
    s21_decimal decimal_check = {{0x221A22, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1543) {
    // 4.07559995E+12
    int f = 1416444716;
    // 4075600000000
    s21_decimal decimal_check = {{0xECB0B400, 0x3B4, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1544) {
    // -4.07559995E+12
    int f = -731038932;
    // -4075600000000
    s21_decimal decimal_check = {{0xECB0B400, 0x3B4, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1545) {
    // 1.41102474E-09
    int f = 818015749;
    // 0.000000001411025
    s21_decimal decimal_check = {{0x1587D1, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1546) {
    // -1.41102474E-09
    int f = -1329467899;
    // -0.000000001411025
    s21_decimal decimal_check = {{0x1587D1, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1547) {
    // 3.49414765E-19
    int f = 550388241;
    // 0.0000000000000000003494148
    s21_decimal decimal_check = {{0x355104, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1548) {
    // -3.49414765E-19
    int f = -1597095407;
    // -0.0000000000000000003494148
    s21_decimal decimal_check = {{0x355104, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1549) {
    // 98172296
    int f = 1287339953;
    // 98172300
    s21_decimal decimal_check = {{0x5D9FD8C, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1550) {
    // -98172296
    int f = -860143695;
    // -98172300
    s21_decimal decimal_check = {{0x5D9FD8C, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1551) {
    // 7.27355032E-28
    int f = 308707853;
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1552) {
    // -7.27355032E-28
    int f = -1838775795;
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1553) {
    // 1.21261214E-21
    int f = 481771177;
    // 0.000000000000000000001212612
    s21_decimal decimal_check = {{0x1280C4, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1554) {
    // -1.21261214E-21
    int f = -1665712471;
    // -0.000000000000000000001212612
    s21_decimal decimal_check = {{0x1280C4, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1555) {
    // 7.40248952E+18
    int f = 1590523354;
    // 7402490000000000000
    s21_decimal decimal_check = {{0x5761A000, 0x66BAED6F, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1556) {
    // -7.40248952E+18
    int f = -556960294;
    // -7402490000000000000
    s21_decimal decimal_check = {{0x5761A000, 0x66BAED6F, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1557) {
    // 4.59417018E+16
    int f = 1529034684;
    // 45941700000000000
    s21_decimal decimal_check = {{0x94E0A800, 0xA337BB, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1558) {
    // -4.59417018E+16
    int f = -618448964;
    // -45941700000000000
    s21_decimal decimal_check = {{0x94E0A800, 0xA337BB, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1559) {
    // 6.88417635E+20
    int f = 1645561563;
    // 688417600000000000000
    s21_decimal decimal_check = {{0xA6F40000, 0x51B69FCE, 0x25, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1560) {
    // -6.88417635E+20
    int f = -501922085;
    // -688417600000000000000
    s21_decimal decimal_check = {{0xA6F40000, 0x51B69FCE, 0x25, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1561) {
    // 3.63701329E-22
    int f = 467392526;
    // 0.0000000000000000000003637013
    s21_decimal decimal_check = {{0x377F15, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1562) {
    // -3.63701329E-22
    int f = -1680091122;
    // -0.0000000000000000000003637013
    s21_decimal decimal_check = {{0x377F15, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1563) {
    // 8.7057823E-18
    int f = 589338597;
    // 0.000000000000000008705782
    s21_decimal decimal_check = {{0x84D6F6, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1564) {
    // -8.7057823E-18
    int f = -1558145051;
    // -0.000000000000000008705782
    s21_decimal decimal_check = {{0x84D6F6, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1565) {
    // 6.95896041E+25
    int f = 1785086128;
    // 69589600000000000000000000
    s21_decimal decimal_check = {{0xED800000, 0xC66E415D, 0x39902B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1566) {
    // -6.95896041E+25
    int f = -362397520;
    // -69589600000000000000000000
    s21_decimal decimal_check = {{0xED800000, 0xC66E415D, 0x39902B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1567) {
    // 1.79372781E+24
    int f = 1740499735;
    // 1793728000000000000000000
    s21_decimal decimal_check = {{0x43000000, 0x3091A5C0, 0x17BD6, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1568) {
    // -1.79372781E+24
    int f = -406983913;
    // -1793728000000000000000000
    s21_decimal decimal_check = {{0x43000000, 0x3091A5C0, 0x17BD6, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1569) {
    // 1.43822898E-10
    int f = 790504076;
    // 0.0000000001438229
    s21_decimal decimal_check = {{0x15F215, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1570) {
    // -1.43822898E-10
    int f = -1356979572;
    // -0.0000000001438229
    s21_decimal decimal_check = {{0x15F215, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1571) {
    // 2.77950161E+16
    int f = 1522892503;
    // 27795020000000000
    s21_decimal decimal_check = {{0x659FF800, 0x62BF6C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1572) {
    // -2.77950161E+16
    int f = -624591145;
    // -27795020000000000
    s21_decimal decimal_check = {{0x659FF800, 0x62BF6C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1573) {
    // 30257946
    int f = 1273420173;
    // 30257950
    s21_decimal decimal_check = {{0x1CDB31E, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1574) {
    // -30257946
    int f = -874063475;
    // -30257950
    s21_decimal decimal_check = {{0x1CDB31E, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1575) {
    // 1.06512259E-13
    int f = 703584291;
    // 0.0000000000001065123
    s21_decimal decimal_check = {{0x1040A3, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1576) {
    // -1.06512259E-13
    int f = -1443899357;
    // -0.0000000000001065123
    s21_decimal decimal_check = {{0x1040A3, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1577) {
    // 0.0641292781
    int f = 1032017462;
    // 0.06412928
    s21_decimal decimal_check = {{0x61DA80, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1578) {
    // -0.0641292781
    int f = -1115466186;
    // -0.06412928
    s21_decimal decimal_check = {{0x61DA80, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1579) {
    // 5.60632134E-14
    int f = 696024188;
    // 0.00000000000005606321
    s21_decimal decimal_check = {{0x558BB1, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1580) {
    // -5.60632134E-14
    int f = -1451459460;
    // -0.00000000000005606321
    s21_decimal decimal_check = {{0x558BB1, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1581) {
    // 6.4886742E+22
    int f = 1700517959;
    // 64886740000000000000000
    s21_decimal decimal_check = {{0x49E20000, 0x8468C551, 0xDBD, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1582) {
    // -6.4886742E+22
    int f = -446965689;
    // -64886740000000000000000
    s21_decimal decimal_check = {{0x49E20000, 0x8468C551, 0xDBD, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1583) {
    // 5.33967237E+13
    int f = 1447182739;
    // 53396720000000
    s21_decimal decimal_check = {{0x64871C00, 0x3090, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1584) {
    // -5.33967237E+13
    int f = -700300909;
    // -53396720000000
    s21_decimal decimal_check = {{0x64871C00, 0x3090, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1585) {
    // 3.22405687E-12
    int f = 744677234;
    // 0.000000000003224057
    s21_decimal decimal_check = {{0x3131F9, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1586) {
    // -3.22405687E-12
    int f = -1402806414;
    // -0.000000000003224057
    s21_decimal decimal_check = {{0x3131F9, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1587) {
    // 2.21627454E-24
    int f = 405502423;
    // 0.0000000000000000000000022163
    s21_decimal decimal_check = {{0x5693, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1588) {
    // -2.21627454E-24
    int f = -1741981225;
    // -0.0000000000000000000000022163
    s21_decimal decimal_check = {{0x5693, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1589) {
    // 29.6760864
    int f = 1106077856;
    // 29.67609
    s21_decimal decimal_check = {{0x2D4839, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1590) {
    // -29.6760864
    int f = -1041405792;
    // -29.67609
    s21_decimal decimal_check = {{0x2D4839, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1591) {
    // 1.17335288E-08
    int f = 843682971;
    // 0.00000001173353
    s21_decimal decimal_check = {{0x11E769, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1592) {
    // -1.17335288E-08
    int f = -1303800677;
    // -0.00000001173353
    s21_decimal decimal_check = {{0x11E769, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1593) {
    // 1.85734028E-09
    int f = 822035802;
    // 0.00000000185734
    s21_decimal decimal_check = {{0x2D586, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1594) {
    // -1.85734028E-09
    int f = -1325447846;
    // -0.00000000185734
    s21_decimal decimal_check = {{0x2D586, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1595) {
    // 209708.766
    int f = 1212992305;
    // 209708.8
    s21_decimal decimal_check = {{0x1FFFC0, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1596) {
    // -209708.766
    int f = -934491343;
    // -209708.8
    s21_decimal decimal_check = {{0x1FFFC0, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1597) {
    // 2.34302012E+25
    int f = 1771768910;
    // 23430200000000000000000000
    s21_decimal decimal_check = {{0x2DE00000, 0xAFE50810, 0x136189, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1598) {
    // -2.34302012E+25
    int f = -375714738;
    // -23430200000000000000000000
    s21_decimal decimal_check = {{0x2DE00000, 0xAFE50810, 0x136189, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1599) {
    // 1.27220915E-07
    int f = 872979000;
    // 0.0000001272209
    s21_decimal decimal_check = {{0x136991, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1600) {
    // -1.27220915E-07
    int f = -1274504648;
    // -0.0000001272209
    s21_decimal decimal_check = {{0x136991, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1601) {
    // 6.45331717
    int f = 1087275411;
    // 6.453317
    s21_decimal decimal_check = {{0x627845, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1602) {
    // -6.45331717
    int f = -1060208237;
    // -6.453317
    s21_decimal decimal_check = {{0x627845, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1603) {
    // 1619.64319
    int f = 1154118805;
    // 1619.643
    s21_decimal decimal_check = {{0x18B6BB, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1604) {
    // -1619.64319
    int f = -993364843;
    // -1619.643
    s21_decimal decimal_check = {{0x18B6BB, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1605) {
    // 7.1142621
    int f = 1088661513;
    // 7.114262
    s21_decimal decimal_check = {{0x6C8E16, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1606) {
    // -7.1142621
    int f = -1058822135;
    // -7.114262
    s21_decimal decimal_check = {{0x6C8E16, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1607) {
    // 12012666
    int f = 1261915258;
    // 12012670
    s21_decimal decimal_check = {{0xB74C7E, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1608) {
    // -12012666
    int f = -885568390;
    // -12012670
    s21_decimal decimal_check = {{0xB74C7E, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1609) {
    // 5.64025756E+25
    int f = 1782226647;
    // 56402580000000000000000000
    s21_decimal decimal_check = {{0xDD00000, 0xFD0DA3BA, 0x2EA7B5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1610) {
    // -5.64025756E+25
    int f = -365257001;
    // -56402580000000000000000000
    s21_decimal decimal_check = {{0xDD00000, 0xFD0DA3BA, 0x2EA7B5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1611) {
    // 5.87406459E+17
    int f = 1560440369;
    // 587406500000000000
    s21_decimal decimal_check = {{0x7B416800, 0x826E319, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1612) {
    // -5.87406459E+17
    int f = -587043279;
    // -587406500000000000
    s21_decimal decimal_check = {{0x7B416800, 0x826E319, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1613) {
    // 3.2212871E+16
    int f = 1524949727;
    // 32212870000000000
    s21_decimal decimal_check = {{0x418BBC00, 0x72716F, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1614) {
    // -3.2212871E+16
    int f = -622533921;
    // -32212870000000000
    s21_decimal decimal_check = {{0x418BBC00, 0x72716F, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1615) {
    // 1.48851609E+18
    int f = 1571111468;
    // 1488516000000000000
    s21_decimal decimal_check = {{0x5E7C4000, 0x14A8456A, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1616) {
    // -1.48851609E+18
    int f = -576372180;
    // -1488516000000000000
    s21_decimal decimal_check = {{0x5E7C4000, 0x14A8456A, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1617) {
    // 1.70748884E-11
    int f = 764817723;
    // 0.00000000001707489
    s21_decimal decimal_check = {{0x1A0DE1, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1618) {
    // -1.70748884E-11
    int f = -1382665925;
    // -0.00000000001707489
    s21_decimal decimal_check = {{0x1A0DE1, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1619) {
    // 2.85416827E-25
    int f = 380676634;
    // 0.0000000000000000000000002854
    s21_decimal decimal_check = {{0xB26, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1620) {
    // -2.85416827E-25
    int f = -1766807014;
    // -0.0000000000000000000000002854
    s21_decimal decimal_check = {{0xB26, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1621) {
    // 4.96119746E-28
    int f = 303905284;
    // 0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1622) {
    // -4.96119746E-28
    int f = -1843578364;
    // -0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1623) {
    // 7.9474166E-13
    int f = 727692076;
    // 0.0000000000007947417
    s21_decimal decimal_check = {{0x794499, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1624) {
    // -7.9474166E-13
    int f = -1419791572;
    // -0.0000000000007947417
    s21_decimal decimal_check = {{0x794499, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1625) {
    // 0.121912479
    int f = 1039772992;
    // 0.1219125
    s21_decimal decimal_check = {{0x129A35, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1626) {
    // -0.121912479
    int f = -1107710656;
    // -0.1219125
    s21_decimal decimal_check = {{0x129A35, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1627) {
    // 5.27181251E+10
    int f = 1363436524;
    // 52718130000
    s21_decimal decimal_check = {{0x463ED350, 0xC, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1628) {
    // -5.27181251E+10
    int f = -784047124;
    // -52718130000
    s21_decimal decimal_check = {{0x463ED350, 0xC, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1629) {
    // 2.72814645E+23
    int f = 1718031679;
    // 272814600000000000000000
    s21_decimal decimal_check = {{0xFB340000, 0x4F21324C, 0x39C5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1630) {
    // -2.72814645E+23
    int f = -429451969;
    // -272814600000000000000000
    s21_decimal decimal_check = {{0xFB340000, 0x4F21324C, 0x39C5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1631) {
    // 0.000241241476
    int f = 964490692;
    // 0.0002412415
    s21_decimal decimal_check = {{0x24CF7F, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1632) {
    // -0.000241241476
    int f = -1182992956;
    // -0.0002412415
    s21_decimal decimal_check = {{0x24CF7F, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1633) {
    // 9907232
    int f = 1259809824;
    // 9907232
    s21_decimal decimal_check = {{0x972C20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1634) {
    // -9907232
    int f = -887673824;
    // -9907232
    s21_decimal decimal_check = {{0x972C20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1635) {
    // 2.43708427E-20
    int f = 518401301;
    // 0.00000000000000000002437084
    s21_decimal decimal_check = {{0x252FDC, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1636) {
    // -2.43708427E-20
    int f = -1629082347;
    // -0.00000000000000000002437084
    s21_decimal decimal_check = {{0x252FDC, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1637) {
    // 6.59116495E-06
    int f = 920463789;
    // 0.000006591165
    s21_decimal decimal_check = {{0x6492BD, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1638) {
    // -6.59116495E-06
    int f = -1227019859;
    // -0.000006591165
    s21_decimal decimal_check = {{0x6492BD, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1639) {
    // 66.1045761
    int f = 1115960715;
    // 66.10458
    s21_decimal decimal_check = {{0x64DE1A, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1640) {
    // -66.1045761
    int f = -1031522933;
    // -66.10458
    s21_decimal decimal_check = {{0x64DE1A, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1641) {
    // 3174886.75
    int f = 1245824923;
    // 3174887
    s21_decimal decimal_check = {{0x3071E7, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1642) {
    // -3174886.75
    int f = -901658725;
    // -3174887
    s21_decimal decimal_check = {{0x3071E7, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1643) {
    // 1.35675071E+22
    int f = 1681383359;
    // 13567510000000000000000
    s21_decimal decimal_check = {{0x500F0000, 0x7F065D40, 0x2DF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1644) {
    // -1.35675071E+22
    int f = -466100289;
    // -13567510000000000000000
    s21_decimal decimal_check = {{0x500F0000, 0x7F065D40, 0x2DF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1645) {
    // 4.97958076E-20
    int f = 527116144;
    // 0.00000000000000000004979581
    s21_decimal decimal_check = {{0x4BFB7D, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1646) {
    // -4.97958076E-20
    int f = -1620367504;
    // -0.00000000000000000004979581
    s21_decimal decimal_check = {{0x4BFB7D, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1647) {
    // 4.75338629E-06
    int f = 916422471;
    // 0.000004753386
    s21_decimal decimal_check = {{0x4887EA, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1648) {
    // -4.75338629E-06
    int f = -1231061177;
    // -0.000004753386
    s21_decimal decimal_check = {{0x4887EA, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1649) {
    // 1.2033919E+23
    int f = 1707859150;
    // 120339200000000000000000
    s21_decimal decimal_check = {{0xBF800000, 0x99E1EF97, 0x197B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1650) {
    // -1.2033919E+23
    int f = -439624498;
    // -120339200000000000000000
    s21_decimal decimal_check = {{0xBF800000, 0x99E1EF97, 0x197B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1651) {
    // 4.38546883E-18
    int f = 581028757;
    // 0.000000000000000004385469
    s21_decimal decimal_check = {{0x42EABD, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1652) {
    // -4.38546883E-18
    int f = -1566454891;
    // -0.000000000000000004385469
    s21_decimal decimal_check = {{0x42EABD, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1653) {
    // 1.28406985E-14
    int f = 677859653;
    // 0.0000000000000128407
    s21_decimal decimal_check = {{0x1F597, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1654) {
    // -1.28406985E-14
    int f = -1469623995;
    // -0.0000000000000128407
    s21_decimal decimal_check = {{0x1F597, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1655) {
    // 3.14603882E-24
    int f = 410216888;
    // 0.000000000000000000000003146
    s21_decimal decimal_check = {{0xC4A, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1656) {
    // -3.14603882E-24
    int f = -1737266760;
    // -0.000000000000000000000003146
    s21_decimal decimal_check = {{0xC4A, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1657) {
    // 0.0115849925
    int f = 1010683643;
    // 0.01158499
    s21_decimal decimal_check = {{0x11AD63, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1658) {
    // -0.0115849925
    int f = -1136800005;
    // -0.01158499
    s21_decimal decimal_check = {{0x11AD63, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1659) {
    // 4.27295534E-23
    int f = 441360544;
    // 0.0000000000000000000000427296
    s21_decimal decimal_check = {{0x68520, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1660) {
    // -4.27295534E-23
    int f = -1706123104;
    // -0.0000000000000000000000427296
    s21_decimal decimal_check = {{0x68520, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1661) {
    // 0.383195788
    int f = 1053045309;
    // 0.3831958
    s21_decimal decimal_check = {{0x3A7896, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1662) {
    // -0.383195788
    int f = -1094438339;
    // -0.3831958
    s21_decimal decimal_check = {{0x3A7896, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1663) {
    // 5.80359982E-09
    int f = 835152129;
    // 0.0000000058036
    s21_decimal decimal_check = {{0xE2B4, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1664) {
    // -5.80359982E-09
    int f = -1312331519;
    // -0.0000000058036
    s21_decimal decimal_check = {{0xE2B4, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1665) {
    // 7.69719501E+10
    int f = 1368350486;
    // 76971950000
    s21_decimal decimal_check = {{0xEBE2BFB0, 0x11, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1666) {
    // -7.69719501E+10
    int f = -779133162;
    // -76971950000
    s21_decimal decimal_check = {{0xEBE2BFB0, 0x11, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1667) {
    // 3.43578544E-15
    int f = 662147854;
    // 0.000000000000003435785
    s21_decimal decimal_check = {{0x346D09, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1668) {
    // -3.43578544E-15
    int f = -1485335794;
    // -0.000000000000003435785
    s21_decimal decimal_check = {{0x346D09, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1669) {
    // 1.10947616E-18
    int f = 564378323;
    // 0.000000000000000001109476
    s21_decimal decimal_check = {{0x10EDE4, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1670) {
    // -1.10947616E-18
    int f = -1583105325;
    // -0.000000000000000001109476
    s21_decimal decimal_check = {{0x10EDE4, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1671) {
    // 2.21978596E-07
    int f = 879646979;
    // 0.0000002219786
    s21_decimal decimal_check = {{0x21DF0A, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1672) {
    // -2.21978596E-07
    int f = -1267836669;
    // -0.0000002219786
    s21_decimal decimal_check = {{0x21DF0A, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1673) {
    // 1.2023133
    int f = 1067050343;
    // 1.202313
    s21_decimal decimal_check = {{0x125889, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1674) {
    // -1.2023133
    int f = -1080433305;
    // -1.202313
    s21_decimal decimal_check = {{0x125889, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1675) {
    // 2.96277484E-20
    int f = 520874432;
    // 0.00000000000000000002962775
    s21_decimal decimal_check = {{0x2D3557, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1676) {
    // -2.96277484E-20
    int f = -1626609216;
    // -0.00000000000000000002962775
    s21_decimal decimal_check = {{0x2D3557, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1677) {
    // 3.15613653E+16
    int f = 1524646346;
    // 31561370000000000
    s21_decimal decimal_check = {{0x17798400, 0x7020E6, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1678) {
    // -3.15613653E+16
    int f = -622837302;
    // -31561370000000000
    s21_decimal decimal_check = {{0x17798400, 0x7020E6, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1679) {
    // 2.26158287E-10
    int f = 796436966;
    // 0.0000000002261583
    s21_decimal decimal_check = {{0x22824F, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1680) {
    // -2.26158287E-10
    int f = -1351046682;
    // -0.0000000002261583
    s21_decimal decimal_check = {{0x22824F, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1681) {
    // 4.26870065E+17
    int f = 1555927426;
    // 426870100000000000
    s21_decimal decimal_check = {{0x23BC4800, 0x5EC8C18, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1682) {
    // -4.26870065E+17
    int f = -591556222;
    // -426870100000000000
    s21_decimal decimal_check = {{0x23BC4800, 0x5EC8C18, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1683) {
    // 5195381.5
    int f = 1251904747;
    // 5195382
    s21_decimal decimal_check = {{0x4F4676, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1684) {
    // -5195381.5
    int f = -895578901;
    // -5195382
    s21_decimal decimal_check = {{0x4F4676, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1685) {
    // 3.2125287E+15
    int f = 1496751218;
    // 3212529000000000
    s21_decimal decimal_check = {{0x31E02A00, 0xB69C7, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1686) {
    // -3.2125287E+15
    int f = -650732430;
    // -3212529000000000
    s21_decimal decimal_check = {{0x31E02A00, 0xB69C7, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1687) {
    // 2.43737585E-15
    int f = 657432998;
    // 0.000000000000002437376
    s21_decimal decimal_check = {{0x253100, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1688) {
    // -2.43737585E-15
    int f = -1490050650;
    // -0.000000000000002437376
    s21_decimal decimal_check = {{0x253100, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1689) {
    // 6.0816773E-25
    int f = 389822467;
    // 0.0000000000000000000000006082
    s21_decimal decimal_check = {{0x17C2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1690) {
    // -6.0816773E-25
    int f = -1757661181;
    // -0.0000000000000000000000006082
    s21_decimal decimal_check = {{0x17C2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1691) {
    // 0.000414093171
    int f = 970529445;
    // 0.0004140932
    s21_decimal decimal_check = {{0x3F2F84, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1692) {
    // -0.000414093171
    int f = -1176954203;
    // -0.0004140932
    s21_decimal decimal_check = {{0x3F2F84, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1693) {
    // 2.13953533E-24
    int f = 405113309;
    // 0.0000000000000000000000021395
    s21_decimal decimal_check = {{0x5393, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1694) {
    // -2.13953533E-24
    int f = -1742370339;
    // -0.0000000000000000000000021395
    s21_decimal decimal_check = {{0x5393, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1695) {
    // 2.99741787E-05
    int f = 939225359;
    // 0.00002997418
    s21_decimal decimal_check = {{0x2DBCAA, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1696) {
    // -2.99741787E-05
    int f = -1208258289;
    // -0.00002997418
    s21_decimal decimal_check = {{0x2DBCAA, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1697) {
    // 7.80250789E+26
    int f = 1814125090;
    // 780250800000000000000000000
    s21_decimal decimal_check = {{0xCC00000, 0x9F4708AD, 0x2856888, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1698) {
    // -7.80250789E+26
    int f = -333358558;
    // -780250800000000000000000000
    s21_decimal decimal_check = {{0xCC00000, 0x9F4708AD, 0x2856888, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1699) {
    // 1.21251368E+23
    int f = 1707960422;
    // 121251400000000000000000
    s21_decimal decimal_check = {{0xCED40000, 0xD335A8C, 0x19AD, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1700) {
    // -1.21251368E+23
    int f = -439523226;
    // -121251400000000000000000
    s21_decimal decimal_check = {{0xCED40000, 0xD335A8C, 0x19AD, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1701) {
    // 286.734528
    int f = 1133469189;
    // 286.7345
    s21_decimal decimal_check = {{0x2BC091, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1702) {
    // -286.734528
    int f = -1014014459;
    // -286.7345
    s21_decimal decimal_check = {{0x2BC091, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1703) {
    // 7.76409335E-28
    int f = 309726671;
    // 0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1704) {
    // -7.76409335E-28
    int f = -1837756977;
    // -0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1705) {
    // 1.61393098E-28
    int f = 290232078;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1706) {
    // -1.61393098E-28
    int f = -1857251570;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1707) {
    // 3.3833776E-15
    int f = 661900365;
    // 0.000000000000003383378
    s21_decimal decimal_check = {{0x33A052, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1708) {
    // -3.3833776E-15
    int f = -1485583283;
    // -0.000000000000003383378
    s21_decimal decimal_check = {{0x33A052, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1709) {
    // 20964.0762
    int f = 1185138727;
    // 20964.08
    s21_decimal decimal_check = {{0x1FFD18, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1710) {
    // -20964.0762
    int f = -962344921;
    // -20964.08
    s21_decimal decimal_check = {{0x1FFD18, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1711) {
    // 0.000464613491
    int f = 972265310;
    // 0.0004646135
    s21_decimal decimal_check = {{0x46E4F7, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1712) {
    // -0.000464613491
    int f = -1175218338;
    // -0.0004646135
    s21_decimal decimal_check = {{0x46E4F7, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1713) {
    // 1.6328994E-16
    int f = 624706223;
    // 0.0000000000000001632899
    s21_decimal decimal_check = {{0x18EA83, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1714) {
    // -1.6328994E-16
    int f = -1522777425;
    // -0.0000000000000001632899
    s21_decimal decimal_check = {{0x18EA83, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1715) {
    // 3.80429941E+23
    int f = 1721835084;
    // 380429900000000000000000
    s21_decimal decimal_check = {{0x41EE0000, 0x256D8E01, 0x508F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1716) {
    // -3.80429941E+23
    int f = -425648564;
    // -380429900000000000000000
    s21_decimal decimal_check = {{0x41EE0000, 0x256D8E01, 0x508F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1717) {
    // 100.197678
    int f = 1120429366;
    // 100.1977
    s21_decimal decimal_check = {{0xF49F9, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1718) {
    // -100.197678
    int f = -1027054282;
    // -100.1977
    s21_decimal decimal_check = {{0xF49F9, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1719) {
    // 62920.7969
    int f = 1198901452;
    // 62920.8
    s21_decimal decimal_check = {{0x999D8, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1720) {
    // -62920.7969
    int f = -948582196;
    // -62920.8
    s21_decimal decimal_check = {{0x999D8, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1721) {
    // 4.62070318E-07
    int f = 888672886;
    // 0.0000004620703
    s21_decimal decimal_check = {{0x46819F, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1722) {
    // -4.62070318E-07
    int f = -1258810762;
    // -0.0000004620703
    s21_decimal decimal_check = {{0x46819F, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1723) {
    // 103.216202
    int f = 1120825010;
    // 103.2162
    s21_decimal decimal_check = {{0xFBFE2, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1724) {
    // -103.216202
    int f = -1026658638;
    // -103.2162
    s21_decimal decimal_check = {{0xFBFE2, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1725) {
    // 1.33091985E-18
    int f = 566519995;
    // 0.00000000000000000133092
    s21_decimal decimal_check = {{0x207E4, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1726) {
    // -1.33091985E-18
    int f = -1580963653;
    // -0.00000000000000000133092
    s21_decimal decimal_check = {{0x207E4, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1727) {
    // 2.07658485E-27
    int f = 321160741;
    // 0.0000000000000000000000000021
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1728) {
    // -2.07658485E-27
    int f = -1826322907;
    // -0.0000000000000000000000000021
    s21_decimal decimal_check = {{0x15, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1729) {
    // 7.50375364E-07
    int f = 894004583;
    // 0.0000007503754
    s21_decimal decimal_check = {{0x727F8A, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1730) {
    // -7.50375364E-07
    int f = -1253479065;
    // -0.0000007503754
    s21_decimal decimal_check = {{0x727F8A, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1731) {
    // 0.043646384
    int f = 1026737805;
    // 0.04364638
    s21_decimal decimal_check = {{0x42995E, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1732) {
    // -0.043646384
    int f = -1120745843;
    // -0.04364638
    s21_decimal decimal_check = {{0x42995E, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1733) {
    // 2.58218643E-06
    int f = 908937632;
    // 0.000002582186
    s21_decimal decimal_check = {{0x2766AA, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1734) {
    // -2.58218643E-06
    int f = -1238546016;
    // -0.000002582186
    s21_decimal decimal_check = {{0x2766AA, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1735) {
    // 3.60375229E-25
    int f = 383717308;
    // 0.0000000000000000000000003604
    s21_decimal decimal_check = {{0xE14, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1736) {
    // -3.60375229E-25
    int f = -1763766340;
    // -0.0000000000000000000000003604
    s21_decimal decimal_check = {{0xE14, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1737) {
    // 4.61331529E-10
    int f = 805150372;
    // 0.0000000004613315
    s21_decimal decimal_check = {{0x4664C3, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1738) {
    // -4.61331529E-10
    int f = -1342333276;
    // -0.0000000004613315
    s21_decimal decimal_check = {{0x4664C3, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1739) {
    // 1.24386528E-08
    int f = 844476870;
    // 0.00000001243865
    s21_decimal decimal_check = {{0x12FAD9, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1740) {
    // -1.24386528E-08
    int f = -1303006778;
    // -0.00000001243865
    s21_decimal decimal_check = {{0x12FAD9, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1741) {
    // 1.05565791E+14
    int f = 1455424999;
    // 105565800000000
    s21_decimal decimal_check = {{0xF4026A00, 0x6002, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1742) {
    // -1.05565791E+14
    int f = -692058649;
    // -105565800000000
    s21_decimal decimal_check = {{0xF4026A00, 0x6002, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1743) {
    // 3.30002215E-12
    int f = 745027562;
    // 0.000000000003300022
    s21_decimal decimal_check = {{0x325AB6, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1744) {
    // -3.30002215E-12
    int f = -1402456086;
    // -0.000000000003300022
    s21_decimal decimal_check = {{0x325AB6, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1745) {
    // 7.68693463E-19
    int f = 560128214;
    // 0.0000000000000000007686935
    s21_decimal decimal_check = {{0x754B17, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1746) {
    // -7.68693463E-19
    int f = -1587355434;
    // -0.0000000000000000007686935
    s21_decimal decimal_check = {{0x754B17, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1747) {
    // 2.85494034E+22
    int f = 1690400082;
    // 28549400000000000000000
    s21_decimal decimal_check = {{0xC91C0000, 0xAA83E6CB, 0x60B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1748) {
    // -2.85494034E+22
    int f = -457083566;
    // -28549400000000000000000
    s21_decimal decimal_check = {{0xC91C0000, 0xAA83E6CB, 0x60B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1749) {
    // 81.7999496
    int f = 1118017939;
    // 81.79995
    s21_decimal decimal_check = {{0x7CD11B, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1750) {
    // -81.7999496
    int f = -1029465709;
    // -81.79995
    s21_decimal decimal_check = {{0x7CD11B, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1751) {
    // 2.88654581E+17
    int f = 1551904826;
    // 288654600000000000
    s21_decimal decimal_check = {{0x4FC85000, 0x40181D4, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1752) {
    // -2.88654581E+17
    int f = -595578822;
    // -288654600000000000
    s21_decimal decimal_check = {{0x4FC85000, 0x40181D4, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1753) {
    // 2.09882774E+24
    int f = 1742616791;
    // 2098828000000000000000000
    s21_decimal decimal_check = {{0xE2B00000, 0xB1A10CAB, 0x1BC71, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1754) {
    // -2.09882774E+24
    int f = -404866857;
    // -2098828000000000000000000
    s21_decimal decimal_check = {{0xE2B00000, 0xB1A10CAB, 0x1BC71, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1755) {
    // 1.04784661E+13
    int f = 1427667796;
    // 10478470000000
    s21_decimal decimal_check = {{0xB57B6D80, 0x987, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1756) {
    // -1.04784661E+13
    int f = -719815852;
    // -10478470000000
    s21_decimal decimal_check = {{0xB57B6D80, 0x987, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1757) {
    // 8.14157623E-20
    int f = 532692175;
    // 0.00000000000000000008141576
    s21_decimal decimal_check = {{0x7C3B08, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1758) {
    // -8.14157623E-20
    int f = -1614791473;
    // -0.00000000000000000008141576
    s21_decimal decimal_check = {{0x7C3B08, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1759) {
    // 1.47592203E-12
    int f = 735033266;
    // 0.000000000001475922
    s21_decimal decimal_check = {{0x168552, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1760) {
    // -1.47592203E-12
    int f = -1412450382;
    // -0.000000000001475922
    s21_decimal decimal_check = {{0x168552, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1761) {
    // 2.05154571E+24
    int f = 1742288706;
    // 2051546000000000000000000
    s21_decimal decimal_check = {{0x9F280000, 0x8810E371, 0x1B26E, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1762) {
    // -2.05154571E+24
    int f = -405194942;
    // -2051546000000000000000000
    s21_decimal decimal_check = {{0x9F280000, 0x8810E371, 0x1B26E, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1763) {
    // 421181408
    int f = 1305007551;
    // 421181400
    s21_decimal decimal_check = {{0x191AB7D8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1764) {
    // -421181408
    int f = -842476097;
    // -421181400
    s21_decimal decimal_check = {{0x191AB7D8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1765) {
    // 2.06627169E+23
    int f = 1714357536;
    // 206627200000000000000000
    s21_decimal decimal_check = {{0xD9C00000, 0x486FDA2C, 0x2BC1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1766) {
    // -2.06627169E+23
    int f = -433126112;
    // -206627200000000000000000
    s21_decimal decimal_check = {{0xD9C00000, 0x486FDA2C, 0x2BC1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1767) {
    // 4.78140691E-08
    int f = 860707872;
    // 0.00000004781407
    s21_decimal decimal_check = {{0x48F55F, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1768) {
    // -4.78140691E-08
    int f = -1286775776;
    // -0.00000004781407
    s21_decimal decimal_check = {{0x48F55F, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1769) {
    // 3.63726436E-08
    int f = 857487397;
    // 0.00000003637264
    s21_decimal decimal_check = {{0x378010, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1770) {
    // -3.63726436E-08
    int f = -1289996251;
    // -0.00000003637264
    s21_decimal decimal_check = {{0x378010, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1771) {
    // 4.86299542E-12
    int f = 749410808;
    // 0.000000000004862995
    s21_decimal decimal_check = {{0x4A3413, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1772) {
    // -4.86299542E-12
    int f = -1398072840;
    // -0.000000000004862995
    s21_decimal decimal_check = {{0x4A3413, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1773) {
    // 1.82772135E-19
    int f = 542623613;
    // 0.0000000000000000001827721
    s21_decimal decimal_check = {{0x1BE389, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1774) {
    // -1.82772135E-19
    int f = -1604860035;
    // -0.0000000000000000001827721
    s21_decimal decimal_check = {{0x1BE389, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1775) {
    // 4.41482463E-13
    int f = 720930900;
    // 0.0000000000004414825
    s21_decimal decimal_check = {{0x435D69, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1776) {
    // -4.41482463E-13
    int f = -1426552748;
    // -0.0000000000004414825
    s21_decimal decimal_check = {{0x435D69, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1777) {
    // 0.0863045529
    int f = 1034993777;
    // 0.08630455
    s21_decimal decimal_check = {{0x83B0B7, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1778) {
    // -0.0863045529
    int f = -1112489871;
    // -0.08630455
    s21_decimal decimal_check = {{0x83B0B7, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1779) {
    // 1128.78113
    int f = 1150097663;
    // 1128.781
    s21_decimal decimal_check = {{0x11394D, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1780) {
    // -1128.78113
    int f = -997385985;
    // -1128.781
    s21_decimal decimal_check = {{0x11394D, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1781) {
    // 3.45864867E+26
    int f = 1804536798;
    // 345864900000000000000000000
    s21_decimal decimal_check = {{0xD0900000, 0xCC5EF7A5, 0x11E17BD, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1782) {
    // -3.45864867E+26
    int f = -342946850;
    // -345864900000000000000000000
    s21_decimal decimal_check = {{0xD0900000, 0xCC5EF7A5, 0x11E17BD, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1783) {
    // 1.59246395E-06
    int f = 903199909;
    // 0.000001592464
    s21_decimal decimal_check = {{0x184C90, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1784) {
    // -1.59246395E-06
    int f = -1244283739;
    // -0.000001592464
    s21_decimal decimal_check = {{0x184C90, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1785) {
    // 0.000306085334
    int f = 966818324;
    // 0.0003060853
    s21_decimal decimal_check = {{0x2EB475, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1786) {
    // -0.000306085334
    int f = -1180665324;
    // -0.0003060853
    s21_decimal decimal_check = {{0x2EB475, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1787) {
    // 2.51718273E-27
    int f = 323448456;
    // 0.0000000000000000000000000025
    s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1788) {
    // -2.51718273E-27
    int f = -1824035192;
    // -0.0000000000000000000000000025
    s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1789) {
    // 2.43597559E+14
    int f = 1465748730;
    // 243597600000000
    s21_decimal decimal_check = {{0xFC6A8800, 0xDD8C, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1790) {
    // -2.43597559E+14
    int f = -681734918;
    // -243597600000000
    s21_decimal decimal_check = {{0xFC6A8800, 0xDD8C, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1791) {
    // 4.22058854E-23
    int f = 441194587;
    // 0.0000000000000000000000422059
    s21_decimal decimal_check = {{0x670AB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1792) {
    // -4.22058854E-23
    int f = -1706289061;
    // -0.0000000000000000000000422059
    s21_decimal decimal_check = {{0x670AB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1793) {
    // 4.06564769E-14
    int f = 691476922;
    // 0.00000000000004065648
    s21_decimal decimal_check = {{0x3E0970, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1794) {
    // -4.06564769E-14
    int f = -1456006726;
    // -0.00000000000004065648
    s21_decimal decimal_check = {{0x3E0970, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1795) {
    // 15298.9609
    int f = 1181682648;
    // 15298.96
    s21_decimal decimal_check = {{0x175828, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1796) {
    // -15298.9609
    int f = -965801000;
    // -15298.96
    s21_decimal decimal_check = {{0x175828, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1797) {
    // 1.63714765E+09
    int f = 1321413064;
    // 1637148000
    s21_decimal decimal_check = {{0x6194E560, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1798) {
    // -1.63714765E+09
    int f = -826070584;
    // -1637148000
    s21_decimal decimal_check = {{0x6194E560, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1799) {
    // 6.86652493E-06
    int f = 921069312;
    // 0.000006866525
    s21_decimal decimal_check = {{0x68C65D, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1800) {
    // -6.86652493E-06
    int f = -1226414336;
    // -0.000006866525
    s21_decimal decimal_check = {{0x68C65D, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1801) {
    // 7.88457853E+19
    int f = 1619576464;
    // 78845790000000000000
    s21_decimal decimal_check = {{0x190BE000, 0x46348443, 0x4, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1802) {
    // -7.88457853E+19
    int f = -527907184;
    // -78845790000000000000
    s21_decimal decimal_check = {{0x190BE000, 0x46348443, 0x4, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1803) {
    // 5.88840978E+18
    int f = 1587769259;
    // 5888410000000000000
    s21_decimal decimal_check = {{0x65DBA000, 0x51B7D5B2, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1804) {
    // -5.88840978E+18
    int f = -559714389;
    // -5888410000000000000
    s21_decimal decimal_check = {{0x65DBA000, 0x51B7D5B2, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1805) {
    // 6.45727826E+22
    int f = 1700448246;
    // 64572780000000000000000
    s21_decimal decimal_check = {{0xB83E0000, 0x7F56C8BF, 0xDAC, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1806) {
    // -6.45727826E+22
    int f = -447035402;
    // -64572780000000000000000
    s21_decimal decimal_check = {{0xB83E0000, 0x7F56C8BF, 0xDAC, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1807) {
    // 0.000321611034
    int f = 967351783;
    // 0.000321611
    s21_decimal decimal_check = {{0x4E84B, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1808) {
    // -0.000321611034
    int f = -1180131865;
    // -0.000321611
    s21_decimal decimal_check = {{0x4E84B, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1809) {
    // 5.66608752E+26
    int f = 1810520073;
    // 566608800000000000000000000
    s21_decimal decimal_check = {{0xCA800000, 0x9870BCBD, 0x1D4B014, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1810) {
    // -5.66608752E+26
    int f = -336963575;
    // -566608800000000000000000000
    s21_decimal decimal_check = {{0xCA800000, 0x9870BCBD, 0x1D4B014, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1811) {
    // 8.53727853E-25
    int f = 394533797;
    // 0.0000000000000000000000008537
    s21_decimal decimal_check = {{0x2159, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1812) {
    // -8.53727853E-25
    int f = -1752949851;
    // -0.0000000000000000000000008537
    s21_decimal decimal_check = {{0x2159, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1813) {
    // 1.00719846E+09
    int f = 1315971716;
    // 1007198000
    s21_decimal decimal_check = {{0x3C089F30, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1814) {
    // -1.00719846E+09
    int f = -831511932;
    // -1007198000
    s21_decimal decimal_check = {{0x3C089F30, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1815) {
    // 5.48009208E+23
    int f = 1726486343;
    // 548009200000000000000000
    s21_decimal decimal_check = {{0x2C180000, 0xA364F2D2, 0x740B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1816) {
    // -5.48009208E+23
    int f = -420997305;
    // -548009200000000000000000
    s21_decimal decimal_check = {{0x2C180000, 0xA364F2D2, 0x740B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1817) {
    // 21.6446609
    int f = 1101867076;
    // 21.64466
    s21_decimal decimal_check = {{0x2106F2, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1818) {
    // -21.6446609
    int f = -1045616572;
    // -21.64466
    s21_decimal decimal_check = {{0x2106F2, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1819) {
    // 16454.7344
    int f = 1182829944;
    // 16454.73
    s21_decimal decimal_check = {{0x191BA1, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1820) {
    // -16454.7344
    int f = -964653704;
    // -16454.73
    s21_decimal decimal_check = {{0x191BA1, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1821) {
    // 2.20396382E-10
    int f = 796021777;
    // 0.0000000002203964
    s21_decimal decimal_check = {{0x21A13C, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1822) {
    // -2.20396382E-10
    int f = -1351461871;
    // -0.0000000002203964
    s21_decimal decimal_check = {{0x21A13C, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1823) {
    // 3.65895031E-12
    int f = 746634469;
    // 0.00000000000365895
    s21_decimal decimal_check = {{0x59547, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1824) {
    // -3.65895031E-12
    int f = -1400849179;
    // -0.00000000000365895
    s21_decimal decimal_check = {{0x59547, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1825) {
    // 48599.0273
    int f = 1195235079;
    // 48599.03
    s21_decimal decimal_check = {{0x4A27FF, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1826) {
    // -48599.0273
    int f = -952248569;
    // -48599.03
    s21_decimal decimal_check = {{0x4A27FF, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1827) {
    // 3.45149079E-25
    int f = 383099662;
    // 0.0000000000000000000000003451
    s21_decimal decimal_check = {{0xD7B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1828) {
    // -3.45149079E-25
    int f = -1764383986;
    // -0.0000000000000000000000003451
    s21_decimal decimal_check = {{0xD7B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1829) {
    // 0.0304599181
    int f = 1022986004;
    // 0.03045992
    s21_decimal decimal_check = {{0x2E7A68, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1830) {
    // -0.0304599181
    int f = -1124497644;
    // -0.03045992
    s21_decimal decimal_check = {{0x2E7A68, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1831) {
    // 560.785217
    int f = 1141649985;
    // 560.7852
    s21_decimal decimal_check = {{0x5591AC, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1832) {
    // -560.785217
    int f = -1005833663;
    // -560.7852
    s21_decimal decimal_check = {{0x5591AC, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1833) {
    // 0.000481360476
    int f = 972840732;
    // 0.0004813605
    s21_decimal decimal_check = {{0x497325, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1834) {
    // -0.000481360476
    int f = -1174642916;
    // -0.0004813605
    s21_decimal decimal_check = {{0x497325, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1835) {
    // 13894181
    int f = 1263796773;
    // 13894180
    s21_decimal decimal_check = {{0xD40224, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1836) {
    // -13894181
    int f = -883686875;
    // -13894180
    s21_decimal decimal_check = {{0xD40224, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1837) {
    // 0.0279863067
    int f = 1021657994;
    // 0.02798631
    s21_decimal decimal_check = {{0x2AB427, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1838) {
    // -0.0279863067
    int f = -1125825654;
    // -0.02798631
    s21_decimal decimal_check = {{0x2AB427, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1839) {
    // 1.48332521E+23
    int f = 1710967034;
    // 148332500000000000000000
    s21_decimal decimal_check = {{0x9DE20000, 0x1EF5C2BB, 0x1F69, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1840) {
    // -1.48332521E+23
    int f = -436516614;
    // -148332500000000000000000
    s21_decimal decimal_check = {{0x9DE20000, 0x1EF5C2BB, 0x1F69, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1841) {
    // 2.43463044E-21
    int f = 490206362;
    // 0.00000000000000000000243463
    s21_decimal decimal_check = {{0x3B707, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1842) {
    // -2.43463044E-21
    int f = -1657277286;
    // -0.00000000000000000000243463
    s21_decimal decimal_check = {{0x3B707, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1843) {
    // 5.50492694E+24
    int f = 1754379990;
    // 5504927000000000000000000
    s21_decimal decimal_check = {{0x931C0000, 0xB0CDB2BD, 0x48DB6, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1844) {
    // -5.50492694E+24
    int f = -393103658;
    // -5504927000000000000000000
    s21_decimal decimal_check = {{0x931C0000, 0xB0CDB2BD, 0x48DB6, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1845) {
    // 2.07526796E-06
    int f = 906708181;
    // 0.000002075268
    s21_decimal decimal_check = {{0x1FAA84, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1846) {
    // -2.07526796E-06
    int f = -1240775467;
    // -0.000002075268
    s21_decimal decimal_check = {{0x1FAA84, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1847) {
    // 210412.734
    int f = 1213037359;
    // 210412.7
    s21_decimal decimal_check = {{0x201B3F, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1848) {
    // -210412.734
    int f = -934446289;
    // -210412.7
    s21_decimal decimal_check = {{0x201B3F, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1849) {
    // 1.77383291E-17
    int f = 597924722;
    // 0.00000000000000001773833
    s21_decimal decimal_check = {{0x1B1109, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1850) {
    // -1.77383291E-17
    int f = -1549558926;
    // -0.00000000000000001773833
    s21_decimal decimal_check = {{0x1B1109, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1851) {
    // 3.37534668E-19
    int f = 549928652;
    // 0.0000000000000000003375347
    s21_decimal decimal_check = {{0x3380F3, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1852) {
    // -3.37534668E-19
    int f = -1597554996;
    // -0.0000000000000000003375347
    s21_decimal decimal_check = {{0x3380F3, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1853) {
    // 5.5264384E+09
    int f = 1336193889;
    // 5526438000
    s21_decimal decimal_check = {{0x4966C070, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1854) {
    // -5.5264384E+09
    int f = -811289759;
    // -5526438000
    s21_decimal decimal_check = {{0x4966C070, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1855) {
    // 1.50151996E+26
    int f = 1794664408;
    // 150152000000000000000000000
    s21_decimal decimal_check = {{0x85000000, 0x3AEB40B8, 0x7C33EC, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1856) {
    // -1.50151996E+26
    int f = -352819240;
    // -150152000000000000000000000
    s21_decimal decimal_check = {{0x85000000, 0x3AEB40B8, 0x7C33EC, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1857) {
    // 5.82903923E+25
    int f = 1782636002;
    // 58290390000000000000000000
    s21_decimal decimal_check = {{0xAD980000, 0x5FA79DAD, 0x303778, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1858) {
    // -5.82903923E+25
    int f = -364847646;
    // -58290390000000000000000000
    s21_decimal decimal_check = {{0xAD980000, 0x5FA79DAD, 0x303778, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1859) {
    // 2.00355191E-14
    int f = 682915523;
    // 0.00000000000002003552
    s21_decimal decimal_check = {{0x1E9260, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1860) {
    // -2.00355191E-14
    int f = -1464568125;
    // -0.00000000000002003552
    s21_decimal decimal_check = {{0x1E9260, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1861) {
    // 7.73216726E-08
    int f = 866520074;
    // 0.00000007732167
    s21_decimal decimal_check = {{0x75FBC7, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1862) {
    // -7.73216726E-08
    int f = -1280963574;
    // -0.00000007732167
    s21_decimal decimal_check = {{0x75FBC7, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1863) {
    // 1.38327191E-18
    int f = 567026313;
    // 0.000000000000000001383272
    s21_decimal decimal_check = {{0x151B68, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1864) {
    // -1.38327191E-18
    int f = -1580457335;
    // -0.000000000000000001383272
    s21_decimal decimal_check = {{0x151B68, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1865) {
    // 6.57728545E+21
    int f = 1672627990;
    // 6577285000000000000000
    s21_decimal decimal_check = {{0xF1208000, 0x8E2A638C, 0x164, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1866) {
    // -6.57728545E+21
    int f = -474855658;
    // -6577285000000000000000
    s21_decimal decimal_check = {{0xF1208000, 0x8E2A638C, 0x164, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1867) {
    // 5849.41846
    int f = 1169607513;
    // 5849.418
    s21_decimal decimal_check = {{0x59414A, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1868) {
    // -5849.41846
    int f = -977876135;
    // -5849.418
    s21_decimal decimal_check = {{0x59414A, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1869) {
    // 9.09833749E-15
    int f = 673441453;
    // 0.000000000000009098337
    s21_decimal decimal_check = {{0x8AD461, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1870) {
    // -9.09833749E-15
    int f = -1474042195;
    // -0.000000000000009098337
    s21_decimal decimal_check = {{0x8AD461, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1871) {
    // 8.66192899E+22
    int f = 1704115489;
    // 86619290000000000000000
    s21_decimal decimal_check = {{0x31690000, 0xA4206E55, 0x1257, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1872) {
    // -8.66192899E+22
    int f = -443368159;
    // -86619290000000000000000
    s21_decimal decimal_check = {{0x31690000, 0xA4206E55, 0x1257, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1873) {
    // 3248.20801
    int f = 1162543956;
    // 3248.208
    s21_decimal decimal_check = {{0x319050, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1874) {
    // -3248.20801
    int f = -984939692;
    // -3248.208
    s21_decimal decimal_check = {{0x319050, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1875) {
    // 3.23101333E-12
    int f = 744709315;
    // 0.000000000003231013
    s21_decimal decimal_check = {{0x314D25, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1876) {
    // -3.23101333E-12
    int f = -1402774333;
    // -0.000000000003231013
    s21_decimal decimal_check = {{0x314D25, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1877) {
    // 4.16279669E-17
    int f = 608172449;
    // 0.00000000000000004162797
    s21_decimal decimal_check = {{0x3F84ED, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1878) {
    // -4.16279669E-17
    int f = -1539311199;
    // -0.00000000000000004162797
    s21_decimal decimal_check = {{0x3F84ED, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1879) {
    // 4.05435075E-22
    int f = 469045770;
    // 0.0000000000000000000004054351
    s21_decimal decimal_check = {{0x3DDD4F, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1880) {
    // -4.05435075E-22
    int f = -1678437878;
    // -0.0000000000000000000004054351
    s21_decimal decimal_check = {{0x3DDD4F, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1881) {
    // 0.00463640597
    int f = 999812350;
    // 0.004636406
    s21_decimal decimal_check = {{0x46BEF6, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1882) {
    // -0.00463640597
    int f = -1147671298;
    // -0.004636406
    s21_decimal decimal_check = {{0x46BEF6, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1883) {
    // 3.30625805E-25
    int f = 382510528;
    // 0.0000000000000000000000003306
    s21_decimal decimal_check = {{0xCEA, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1884) {
    // -3.30625805E-25
    int f = -1764973120;
    // -0.0000000000000000000000003306
    s21_decimal decimal_check = {{0xCEA, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1885) {
    // 10773.4004
    int f = 1177048474;
    // 10773.4
    s21_decimal decimal_check = {{0x1A4D6, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1886) {
    // -10773.4004
    int f = -970435174;
    // -10773.4
    s21_decimal decimal_check = {{0x1A4D6, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1887) {
    // 1.21254013E+12
    int f = 1401759875;
    // 1212540000000
    s21_decimal decimal_check = {{0x51041700, 0x11A, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1888) {
    // -1.21254013E+12
    int f = -745723773;
    // -1212540000000
    s21_decimal decimal_check = {{0x51041700, 0x11A, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1889) {
    // 1.00056701E-25
    int f = 368556664;
    // 0.0000000000000000000000001001
    s21_decimal decimal_check = {{0x3E9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1890) {
    // -1.00056701E-25
    int f = -1778926984;
    // -0.0000000000000000000000001001
    s21_decimal decimal_check = {{0x3E9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1891) {
    // 0.459507078
    int f = 1055605891;
    // 0.4595071
    s21_decimal decimal_check = {{0x461D7F, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1892) {
    // -0.459507078
    int f = -1091877757;
    // -0.4595071
    s21_decimal decimal_check = {{0x461D7F, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1893) {
    // 32093776
    int f = 1274338088;
    // 32093780
    s21_decimal decimal_check = {{0x1E9B654, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1894) {
    // -32093776
    int f = -873145560;
    // -32093780
    s21_decimal decimal_check = {{0x1E9B654, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1895) {
    // 4.54820297E-18
    int f = 581422224;
    // 0.000000000000000004548203
    s21_decimal decimal_check = {{0x45666B, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1896) {
    // -4.54820297E-18
    int f = -1566061424;
    // -0.000000000000000004548203
    s21_decimal decimal_check = {{0x45666B, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1897) {
    // 3.97821971E-08
    int f = 858447101;
    // 0.0000000397822
    s21_decimal decimal_check = {{0x611FE, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1898) {
    // -3.97821971E-08
    int f = -1289036547;
    // -0.0000000397822
    s21_decimal decimal_check = {{0x611FE, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1899) {
    // 2.20014597E-27
    int f = 321802307;
    // 0.0000000000000000000000000022
    s21_decimal decimal_check = {{0x16, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1900) {
    // -2.20014597E-27
    int f = -1825681341;
    // -0.0000000000000000000000000022
    s21_decimal decimal_check = {{0x16, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1901) {
    // 0.0843177512
    int f = 1034727113;
    // 0.08431775
    s21_decimal decimal_check = {{0x80A89F, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1902) {
    // -0.0843177512
    int f = -1112756535;
    // -0.08431775
    s21_decimal decimal_check = {{0x80A89F, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1903) {
    // 0.00146523479
    int f = 985664799;
    // 0.001465235
    s21_decimal decimal_check = {{0x165B93, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1904) {
    // -0.00146523479
    int f = -1161818849;
    // -0.001465235
    s21_decimal decimal_check = {{0x165B93, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1905) {
    // 2.72411573E+23
    int f = 1718009304;
    // 272411600000000000000000
    s21_decimal decimal_check = {{0x78C80000, 0x7661957C, 0x39AF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1906) {
    // -2.72411573E+23
    int f = -429474344;
    // -272411600000000000000000
    s21_decimal decimal_check = {{0x78C80000, 0x7661957C, 0x39AF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1907) {
    // 10549.5869
    int f = 1176819289;
    // 10549.59
    s21_decimal decimal_check = {{0x1018EF, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1908) {
    // -10549.5869
    int f = -970664359;
    // -10549.59
    s21_decimal decimal_check = {{0x1018EF, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1909) {
    // 1.44142447E-23
    int f = 428566513;
    // 0.0000000000000000000000144142
    s21_decimal decimal_check = {{0x2330E, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1910) {
    // -1.44142447E-23
    int f = -1718917135;
    // -0.0000000000000000000000144142
    s21_decimal decimal_check = {{0x2330E, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1911) {
    // 7.28497127E+12
    int f = 1423181124;
    // 7284971000000
    s21_decimal decimal_check = {{0x2A1BD0C0, 0x6A0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1912) {
    // -7.28497127E+12
    int f = -724302524;
    // -7284971000000
    s21_decimal decimal_check = {{0x2A1BD0C0, 0x6A0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1913) {
    // 2.72145045E-14
    int f = 687153248;
    // 0.0000000000000272145
    s21_decimal decimal_check = {{0x42711, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1914) {
    // -2.72145045E-14
    int f = -1460330400;
    // -0.0000000000000272145
    s21_decimal decimal_check = {{0x42711, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1915) {
    // 3.10039269E-21
    int f = 493503057;
    // 0.000000000000000000003100393
    s21_decimal decimal_check = {{0x2F4EE9, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1916) {
    // -3.10039269E-21
    int f = -1653980591;
    // -0.000000000000000000003100393
    s21_decimal decimal_check = {{0x2F4EE9, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1917) {
    // 1.8253609E-25
    int f = 375519231;
    // 0.0000000000000000000000001825
    s21_decimal decimal_check = {{0x721, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1918) {
    // -1.8253609E-25
    int f = -1771964417;
    // -0.0000000000000000000000001825
    s21_decimal decimal_check = {{0x721, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1919) {
    // 8392391
    int f = 1258294983;
    // 8392391
    s21_decimal decimal_check = {{0x800EC7, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1920) {
    // -8392391
    int f = -889188665;
    // -8392391
    s21_decimal decimal_check = {{0x800EC7, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1921) {
    // 8.16909213E-17
    int f = 616324559;
    // 0.00000000000000008169092
    s21_decimal decimal_check = {{0x7CA684, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1922) {
    // -8.16909213E-17
    int f = -1531159089;
    // -0.00000000000000008169092
    s21_decimal decimal_check = {{0x7CA684, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1923) {
    // 3.32325506
    int f = 1079291958;
    // 3.323255
    s21_decimal decimal_check = {{0x32B577, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1924) {
    // -3.32325506
    int f = -1068191690;
    // -3.323255
    s21_decimal decimal_check = {{0x32B577, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1925) {
    // 2.32539381E+15
    int f = 1493446383;
    // 2325394000000000
    s21_decimal decimal_check = {{0xFB553400, 0x842EE, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1926) {
    // -2.32539381E+15
    int f = -654037265;
    // -2325394000000000
    s21_decimal decimal_check = {{0xFB553400, 0x842EE, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1927) {
    // 5.52278798E-24
    int f = 416655115;
    // 0.0000000000000000000000055228
    s21_decimal decimal_check = {{0xD7BC, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1928) {
    // -5.52278798E-24
    int f = -1730828533;
    // -0.0000000000000000000000055228
    s21_decimal decimal_check = {{0xD7BC, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1929) {
    // 2.31565034E-27
    int f = 322402040;
    // 0.0000000000000000000000000023
    s21_decimal decimal_check = {{0x17, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1930) {
    // -2.31565034E-27
    int f = -1825081608;
    // -0.0000000000000000000000000023
    s21_decimal decimal_check = {{0x17, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1931) {
    // 3.96384467E+25
    int f = 1778591506;
    // 39638450000000000000000000
    s21_decimal decimal_check = {{0x97880000, 0xAE217320, 0x20C9C4, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1932) {
    // -3.96384467E+25
    int f = -368892142;
    // -39638450000000000000000000
    s21_decimal decimal_check = {{0x97880000, 0xAE217320, 0x20C9C4, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1933) {
    // 5.94730261E-16
    int f = 640379737;
    // 0.0000000000000005947303
    s21_decimal decimal_check = {{0x5ABFA7, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1934) {
    // -5.94730261E-16
    int f = -1507103911;
    // -0.0000000000000005947303
    s21_decimal decimal_check = {{0x5ABFA7, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1935) {
    // 4.1073689E+18
    int f = 1583612217;
    // 4107369000000000000
    s21_decimal decimal_check = {{0xFE739000, 0x39004E57, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1936) {
    // -4.1073689E+18
    int f = -563871431;
    // -4107369000000000000
    s21_decimal decimal_check = {{0xFE739000, 0x39004E57, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1937) {
    // 18703318
    int f = 1267642859;
    // 18703320
    s21_decimal decimal_check = {{0x11D63D8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1938) {
    // -18703318
    int f = -879840789;
    // -18703320
    s21_decimal decimal_check = {{0x11D63D8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1939) {
    // 9.11522733E-08
    int f = 868466558;
    // 0.00000009115227
    s21_decimal decimal_check = {{0x8B165B, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1940) {
    // -9.11522733E-08
    int f = -1279017090;
    // -0.00000009115227
    s21_decimal decimal_check = {{0x8B165B, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1941) {
    // 8.90262797E+16
    int f = 1537090679;
    // 89026280000000000
    s21_decimal decimal_check = {{0x13131000, 0x13C48EE, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1942) {
    // -8.90262797E+16
    int f = -610392969;
    // -89026280000000000
    s21_decimal decimal_check = {{0x13131000, 0x13C48EE, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1943) {
    // 7.43393594E+25
    int f = 1786116067;
    // 74339360000000000000000000
    s21_decimal decimal_check = {{0xBC800000, 0xC7D94659, 0x3D7DF8, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1944) {
    // -7.43393594E+25
    int f = -361367581;
    // -74339360000000000000000000
    s21_decimal decimal_check = {{0xBC800000, 0xC7D94659, 0x3D7DF8, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1945) {
    // 1.67222081E-15
    int f = 653327887;
    // 0.000000000000001672221
    s21_decimal decimal_check = {{0x19841D, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1946) {
    // -1.67222081E-15
    int f = -1494155761;
    // -0.000000000000001672221
    s21_decimal decimal_check = {{0x19841D, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1947) {
    // 3.47541821E-19
    int f = 550315785;
    // 0.0000000000000000003475418
    s21_decimal decimal_check = {{0x3507DA, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1948) {
    // -3.47541821E-19
    int f = -1597167863;
    // -0.0000000000000000003475418
    s21_decimal decimal_check = {{0x3507DA, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1949) {
    // 1.70813098E-13
    int f = 708858246;
    // 0.0000000000001708131
    s21_decimal decimal_check = {{0x1A1063, 0x0, 0x0, 0x130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1950) {
    // -1.70813098E-13
    int f = -1438625402;
    // -0.0000000000001708131
    s21_decimal decimal_check = {{0x1A1063, 0x0, 0x0, 0x80130000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1951) {
    // 7.38855376E+21
    int f = 1674069092;
    // 7388554000000000000000
    s21_decimal decimal_check = {{0x5F810000, 0x88C8DCC3, 0x190, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1952) {
    // -7.38855376E+21
    int f = -473414556;
    // -7388554000000000000000
    s21_decimal decimal_check = {{0x5F810000, 0x88C8DCC3, 0x190, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1953) {
    // 5.37598825E-18
    int f = 583423686;
    // 0.000000000000000005375988
    s21_decimal decimal_check = {{0x5207F4, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1954) {
    // -5.37598825E-18
    int f = -1564059962;
    // -0.000000000000000005375988
    s21_decimal decimal_check = {{0x5207F4, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1955) {
    // 0.855741262
    int f = 1062932956;
    // 0.8557413
    s21_decimal decimal_check = {{0x829365, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1956) {
    // -0.855741262
    int f = -1084550692;
    // -0.8557413
    s21_decimal decimal_check = {{0x829365, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1957) {
    // 1.04024034E-08
    int f = 842184257;
    // 0.0000000104024
    s21_decimal decimal_check = {{0x19658, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1958) {
    // -1.04024034E-08
    int f = -1305299391;
    // -0.0000000104024
    s21_decimal decimal_check = {{0x19658, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1959) {
    // 18.6623402
    int f = 1100303481;
    // 18.66234
    s21_decimal decimal_check = {{0x1C79FA, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1960) {
    // -18.6623402
    int f = -1047180167;
    // -18.66234
    s21_decimal decimal_check = {{0x1C79FA, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1961) {
    // 1.02066178E-08
    int f = 841963822;
    // 0.00000001020662
    s21_decimal decimal_check = {{0xF92F6, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1962) {
    // -1.02066178E-08
    int f = -1305519826;
    // -0.00000001020662
    s21_decimal decimal_check = {{0xF92F6, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1963) {
    // 1.23839506E-11
    int f = 760863835;
    // 0.00000000001238395
    s21_decimal decimal_check = {{0x12E57B, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1964) {
    // -1.23839506E-11
    int f = -1386619813;
    // -0.00000000001238395
    s21_decimal decimal_check = {{0x12E57B, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1965) {
    // 1.01626838E-05
    int f = 925532261;
    // 0.00001016268
    s21_decimal decimal_check = {{0xF81CC, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1966) {
    // -1.01626838E-05
    int f = -1221951387;
    // -0.00001016268
    s21_decimal decimal_check = {{0xF81CC, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1967) {
    // 2.63346624E+14
    int f = 1466925866;
    // 263346600000000
    s21_decimal decimal_check = {{0x288BBA00, 0xEF83, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1968) {
    // -2.63346624E+14
    int f = -680557782;
    // -263346600000000
    s21_decimal decimal_check = {{0x288BBA00, 0xEF83, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1969) {
    // 234230.063
    int f = 1214561668;
    // 234230.1
    s21_decimal decimal_check = {{0x23BD9D, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1970) {
    // -234230.063
    int f = -932921980;
    // -234230.1
    s21_decimal decimal_check = {{0x23BD9D, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1971) {
    // 2.67943988E+13
    int f = 1438839925;
    // 26794400000000
    s21_decimal decimal_check = {{0x8EB1A800, 0x185E, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1972) {
    // -2.67943988E+13
    int f = -708643723;
    // -26794400000000
    s21_decimal decimal_check = {{0x8EB1A800, 0x185E, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1973) {
    // 5.02389341E-24
    int f = 415390267;
    // 0.0000000000000000000000050239
    s21_decimal decimal_check = {{0xC43F, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1974) {
    // -5.02389341E-24
    int f = -1732093381;
    // -0.0000000000000000000000050239
    s21_decimal decimal_check = {{0xC43F, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1975) {
    // 3.10225183E-21
    int f = 493512263;
    // 0.000000000000000000003102252
    s21_decimal decimal_check = {{0x2F562C, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1976) {
    // -3.10225183E-21
    int f = -1653971385;
    // -0.000000000000000000003102252
    s21_decimal decimal_check = {{0x2F562C, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1977) {
    // 1.9376137E-12
    int f = 738744562;
    // 0.000000000001937614
    s21_decimal decimal_check = {{0x1D90CE, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1978) {
    // -1.9376137E-12
    int f = -1408739086;
    // -0.000000000001937614
    s21_decimal decimal_check = {{0x1D90CE, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1979) {
    // 6.28786967E-10
    int f = 808244979;
    // 0.000000000628787
    s21_decimal decimal_check = {{0x99833, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1980) {
    // -6.28786967E-10
    int f = -1339238669;
    // -0.000000000628787
    s21_decimal decimal_check = {{0x99833, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1981) {
    // 0.0611746721
    int f = 1031443019;
    // 0.06117467
    s21_decimal decimal_check = {{0x5D585B, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1982) {
    // -0.0611746721
    int f = -1116040629;
    // -0.06117467
    s21_decimal decimal_check = {{0x5D585B, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1983) {
    // 1.0531192E-14
    int f = 675133069;
    // 0.00000000000001053119
    s21_decimal decimal_check = {{0x1011BF, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1984) {
    // -1.0531192E-14
    int f = -1472350579;
    // -0.00000000000001053119
    s21_decimal decimal_check = {{0x1011BF, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1985) {
    // 1.79615123E-25
    int f = 375282254;
    // 0.0000000000000000000000001796
    s21_decimal decimal_check = {{0x704, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1986) {
    // -1.79615123E-25
    int f = -1772201394;
    // -0.0000000000000000000000001796
    s21_decimal decimal_check = {{0x704, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1987) {
    // 2.3376424E-06
    int f = 907862116;
    // 0.000002337642
    s21_decimal decimal_check = {{0x23AB6A, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1988) {
    // -2.3376424E-06
    int f = -1239621532;
    // -0.000002337642
    s21_decimal decimal_check = {{0x23AB6A, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1989) {
    // 2.57119381E+12
    int f = 1410705862;
    // 2571194000000
    s21_decimal decimal_check = {{0xA71AE280, 0x256, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1990) {
    // -2.57119381E+12
    int f = -736777786;
    // -2571194000000
    s21_decimal decimal_check = {{0xA71AE280, 0x256, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1991) {
    // 7.04551938E+14
    int f = 1478505042;
    // 704551900000000
    s21_decimal decimal_check = {{0x45B9AF00, 0x280C9, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1992) {
    // -7.04551938E+14
    int f = -668978606;
    // -704551900000000
    s21_decimal decimal_check = {{0x45B9AF00, 0x280C9, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1993) {
    // 3.42087291E-23
    int f = 438660187;
    // 0.0000000000000000000000342087
    s21_decimal decimal_check = {{0x53847, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1994) {
    // -3.42087291E-23
    int f = -1708823461;
    // -0.0000000000000000000000342087
    s21_decimal decimal_check = {{0x53847, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1995) {
    // 9.9840353E-12
    int f = 758096921;
    // 0.000000000009984035
    s21_decimal decimal_check = {{0x985823, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1996) {
    // -9.9840353E-12
    int f = -1389386727;
    // -0.000000000009984035
    s21_decimal decimal_check = {{0x985823, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1997) {
    // 2.79144812
    int f = 1077061398;
    // 2.791448
    s21_decimal decimal_check = {{0x2A9818, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1998) {
    // -2.79144812
    int f = -1070422250;
    // -2.791448
    s21_decimal decimal_check = {{0x2A9818, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok1999) {
    // 6.18437859E+22
    int f = 1699842287;
    // 61843790000000000000000
    s21_decimal decimal_check = {{0xBEFB0000, 0x8EFEAE8E, 0xD18, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2000) {
    // -6.18437859E+22
    int f = -447641361;
    // -61843790000000000000000
    s21_decimal decimal_check = {{0xBEFB0000, 0x8EFEAE8E, 0xD18, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2001) {
    // 7.92281578E+28
    int f = 1870659583;
    // 79228160000000000000000000000
    s21_decimal decimal_check = {{0x20000000, 0xB392B21A, 0xFFFFFF77, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2002) {
    // -7.92281578E+28
    int f = -276824065;
    // -79228160000000000000000000000
    s21_decimal decimal_check = {{0x20000000, 0xB392B21A, 0xFFFFFF77, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2003) {
    // 7.92281531E+28
    int f = 1870659582;
    // 79228150000000000000000000000
    s21_decimal decimal_check = {{0x6DC00000, 0x99B1E85F, 0xFFFFFD59, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2004) {
    // -7.92281531E+28
    int f = -276824066;
    // -79228150000000000000000000000
    s21_decimal decimal_check = {{0x6DC00000, 0x99B1E85F, 0xFFFFFD59, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2005) {
    // 7.92281483E+28
    int f = 1870659581;
    // 79228150000000000000000000000
    s21_decimal decimal_check = {{0x6DC00000, 0x99B1E85F, 0xFFFFFD59, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2006) {
    // -7.92281483E+28
    int f = -276824067;
    // -79228150000000000000000000000
    s21_decimal decimal_check = {{0x6DC00000, 0x99B1E85F, 0xFFFFFD59, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2007) {
    // 7.92281436E+28
    int f = 1870659580;
    // 79228140000000000000000000000
    s21_decimal decimal_check = {{0xBB800000, 0x7FD11EA4, 0xFFFFFB3B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2008) {
    // -7.92281436E+28
    int f = -276824068;
    // -79228140000000000000000000000
    s21_decimal decimal_check = {{0xBB800000, 0x7FD11EA4, 0xFFFFFB3B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2009) {
    // 7.92281389E+28
    int f = 1870659579;
    // 79228140000000000000000000000
    s21_decimal decimal_check = {{0xBB800000, 0x7FD11EA4, 0xFFFFFB3B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2010) {
    // -7.92281389E+28
    int f = -276824069;
    // -79228140000000000000000000000
    s21_decimal decimal_check = {{0xBB800000, 0x7FD11EA4, 0xFFFFFB3B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2011) {
    // 7.92281342E+28
    int f = 1870659578;
    // 79228130000000000000000000000
    s21_decimal decimal_check = {{0x9400000, 0x65F054EA, 0xFFFFF91D, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2012) {
    // -7.92281342E+28
    int f = -276824070;
    // -79228130000000000000000000000
    s21_decimal decimal_check = {{0x9400000, 0x65F054EA, 0xFFFFF91D, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2013) {
    // 7.92281295E+28
    int f = 1870659577;
    // 79228130000000000000000000000
    s21_decimal decimal_check = {{0x9400000, 0x65F054EA, 0xFFFFF91D, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2014) {
    // -7.92281295E+28
    int f = -276824071;
    // -79228130000000000000000000000
    s21_decimal decimal_check = {{0x9400000, 0x65F054EA, 0xFFFFF91D, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2015) {
    // 7.92281247E+28
    int f = 1870659576;
    // 79228120000000000000000000000
    s21_decimal decimal_check = {{0x57000000, 0x4C0F8B2F, 0xFFFFF6FF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2016) {
    // -7.92281247E+28
    int f = -276824072;
    // -79228120000000000000000000000
    s21_decimal decimal_check = {{0x57000000, 0x4C0F8B2F, 0xFFFFF6FF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2017) {
    // 7.9228087E+28
    int f = 1870659568;
    // 79228090000000000000000000000
    s21_decimal decimal_check = {{0x40400000, 0xFE6D2DFF, 0xFFFFF0A4, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2018) {
    // -7.9228087E+28
    int f = -276824080;
    // -79228090000000000000000000000
    s21_decimal decimal_check = {{0x40400000, 0xFE6D2DFF, 0xFFFFF0A4, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2019) {
    // 7.92280114E+28
    int f = 1870659552;
    // 79228010000000000000000000000
    s21_decimal decimal_check = {{0xAE400000, 0x2F66E029, 0xFFFFDFB4, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2020) {
    // -7.92280114E+28
    int f = -276824096;
    // -79228010000000000000000000000
    s21_decimal decimal_check = {{0xAE400000, 0x2F66E029, 0xFFFFDFB4, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2021) {
    // 7.92278603E+28
    int f = 1870659520;
    // 79227860000000000000000000000
    s21_decimal decimal_check = {{0x3C800000, 0xAB3B0E39, 0xFFFFBFF0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2022) {
    // -7.92278603E+28
    int f = -276824128;
    // -79227860000000000000000000000
    s21_decimal decimal_check = {{0x3C800000, 0xAB3B0E39, 0xFFFFBFF0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2023) {
    // 6.60234672E+28
    int f = 1867863381;
    // 66023470000000000000000000000
    s21_decimal decimal_check = {{0xC00000, 0x739A8254, 0xD5555598, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2024) {
    // -6.60234672E+28
    int f = -279620267;
    // -66023470000000000000000000000
    s21_decimal decimal_check = {{0xC00000, 0x739A8254, 0xD5555598, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2025) {
    // 5.94211219E+28
    int f = 1866465280;
    // 59421120000000000000000000000
    s21_decimal decimal_check = {{0x98000000, 0xC6AE0593, 0xBFFFFF99, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2026) {
    // -5.94211219E+28
    int f = -281018368;
    // -59421120000000000000000000000
    s21_decimal decimal_check = {{0x98000000, 0xC6AE0593, 0xBFFFFF99, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2027) {
    // 5.28187719E+28
    int f = 1865067178;
    // 52818770000000000000000000000
    s21_decimal decimal_check = {{0x2F400000, 0x19C188D3, 0xAAAAA99B, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2028) {
    // -5.28187719E+28
    int f = -282416470;
    // -52818770000000000000000000000
    s21_decimal decimal_check = {{0x2F400000, 0x19C188D3, 0xAAAAA99B, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2029) {
    // 3.96140813E+28
    int f = 1862270976;
    // 39614080000000000000000000000
    s21_decimal decimal_check = {{0x10000000, 0xD9C9590D, 0x7FFFFFBB, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2030) {
    // -3.96140813E+28
    int f = -285212672;
    // -39614080000000000000000000000
    s21_decimal decimal_check = {{0x10000000, 0xD9C9590D, 0x7FFFFFBB, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2031) {
    // 1.65058668E+28
    int f = 1851086165;
    // 16505870000000000000000000000
    s21_decimal decimal_check = {{0xACC00000, 0xA35ED303, 0x355555ED, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2032) {
    // -1.65058668E+28
    int f = -296397483;
    // -16505870000000000000000000000
    s21_decimal decimal_check = {{0xACC00000, 0xA35ED303, 0x355555ED, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2033) {
    // 1.3204693E+28
    int f = 1848289962;
    // 13204690000000000000000000000
    s21_decimal decimal_check = {{0x1F400000, 0x3FF82FC6, 0x2AAAA9DF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2034) {
    // -1.3204693E+28
    int f = -299193686;
    // -13204690000000000000000000000
    s21_decimal decimal_check = {{0x1F400000, 0x3FF82FC6, 0x2AAAA9DF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2035) {
    // 1.03161667E+27
    int f = 1817531733;
    // 1031617000000000000000000000
    s21_decimal decimal_check = {{0xF6A00000, 0xA0EF22E8, 0x3555565, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2036) {
    // -1.03161667E+27
    int f = -329951915;
    // -1031617000000000000000000000
    s21_decimal decimal_check = {{0xF6A00000, 0xA0EF22E8, 0x3555565, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2037) {
    // 8.2529331E+26
    int f = 1814735530;
    // 825293300000000000000000000
    s21_decimal decimal_check = {{0xCF500000, 0x709C67CB, 0x2AAAAA7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2038) {
    // -8.2529331E+26
    int f = -332748118;
    // -825293300000000000000000000
    s21_decimal decimal_check = {{0xCF500000, 0x709C67CB, 0x2AAAAA7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2039) {
    // 4.02975264E+24
    int f = 1750422869;
    // 4029753000000000000000000
    s21_decimal decimal_check = {{0x19440000, 0x590D4990, 0x35555, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2040) {
    // -4.02975264E+24
    int f = -397060779;
    // -4029753000000000000000000
    s21_decimal decimal_check = {{0x19440000, 0x590D4990, 0x35555, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2041) {
    // 2.41785164E+24
    int f = 1744830464;
    // 2417852000000000000000000
    s21_decimal decimal_check = {{0xFD700000, 0x501B713, 0x20000, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2042) {
    // -2.41785164E+24
    int f = -402653184;
    // -2417852000000000000000000
    s21_decimal decimal_check = {{0xFD700000, 0x501B713, 0x20000, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2043) {
    // 2.4178515E+24
    int f = 1744830463;
    // 2417851000000000000000000
    s21_decimal decimal_check = {{0x560C0000, 0xF7210060, 0x1FFFF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2044) {
    // -2.4178515E+24
    int f = -402653185;
    // -2417851000000000000000000
    s21_decimal decimal_check = {{0x560C0000, 0xF7210060, 0x1FFFF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2045) {
    // 2.41785135E+24
    int f = 1744830462;
    // 2417851000000000000000000
    s21_decimal decimal_check = {{0x560C0000, 0xF7210060, 0x1FFFF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2046) {
    // -2.41785135E+24
    int f = -402653186;
    // -2417851000000000000000000
    s21_decimal decimal_check = {{0x560C0000, 0xF7210060, 0x1FFFF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2047) {
    // 3.22380199E+24
    int f = 1747626666;
    // 3223802000000000000000000
    s21_decimal decimal_check = {{0x37A80000, 0xA81724F8, 0x2AAAA, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2048) {
    // -3.22380199E+24
    int f = -399856982;
    // -3223802000000000000000000
    s21_decimal decimal_check = {{0x37A80000, 0xA81724F8, 0x2AAAA, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2049) {
    // 2.01487632E+24
    int f = 1742034261;
    // 2014876000000000000000000
    s21_decimal decimal_check = {{0x38F00000, 0xA596496E, 0x1AAAA, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2050) {
    // -2.01487632E+24
    int f = -405449387;
    // -2014876000000000000000000
    s21_decimal decimal_check = {{0x38F00000, 0xA596496E, 0x1AAAA, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2051) {
    // 1.611901E+24
    int f = 1739238058;
    // 1611901000000000000000000
    s21_decimal decimal_check = {{0x1BD40000, 0x540B927C, 0x15555, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2052) {
    // -1.611901E+24
    int f = -408245590;
    // -1611901000000000000000000
    s21_decimal decimal_check = {{0x1BD40000, 0x540B927C, 0x15555, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2053) {
    // 9.44473297E+21
    int f = 1677721600;
    // 9444733000000000000000
    s21_decimal decimal_check = {{0xF16C8000, 0x1F28, 0x200, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2054) {
    // -9.44473297E+21
    int f = -469762048;
    // -9444733000000000000000
    s21_decimal decimal_check = {{0xF16C8000, 0x1F28, 0x200, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2055) {
    // 9.4447324E+21
    int f = 1677721599;
    // 9444732000000000000000
    s21_decimal decimal_check = {{0x4CA60000, 0xFFFC91AA, 0x1FF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2056) {
    // -9.4447324E+21
    int f = -469762049;
    // -9444732000000000000000
    s21_decimal decimal_check = {{0x4CA60000, 0xFFFC91AA, 0x1FF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2057) {
    // 9.44473184E+21
    int f = 1677721598;
    // 9444732000000000000000
    s21_decimal decimal_check = {{0x4CA60000, 0xFFFC91AA, 0x1FF, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2058) {
    // -9.44473184E+21
    int f = -469762050;
    // -9444732000000000000000
    s21_decimal decimal_check = {{0x4CA60000, 0xFFFC91AA, 0x1FF, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2059) {
    // 7.87061062E+21
    int f = 1674925397;
    // 7870611000000000000000
    s21_decimal decimal_check = {{0x39FB8000, 0xAAAB5C37, 0x1AA, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2060) {
    // -7.87061062E+21
    int f = -472558251;
    // -7870611000000000000000
    s21_decimal decimal_check = {{0x39FB8000, 0xAAAB5C37, 0x1AA, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2061) {
    // 6.29648827E+21
    int f = 1672129194;
    // 6296488000000000000000
    s21_decimal decimal_check = {{0xDDC40000, 0x55530BC6, 0x155, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2062) {
    // -6.29648827E+21
    int f = -475354454;
    // -6296488000000000000000
    s21_decimal decimal_check = {{0xDDC40000, 0x55530BC6, 0x155, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2063) {
    // 5.9029581E+20
    int f = 1644167168;
    // 590295800000000000000
    s21_decimal decimal_check = {{0x2D078000, 0xFFFFF694, 0x1F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2064) {
    // -5.9029581E+20
    int f = -503316480;
    // -590295800000000000000
    s21_decimal decimal_check = {{0x2D078000, 0xFFFFF694, 0x1F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2065) {
    // 5.90295775E+20
    int f = 1644167167;
    // 590295800000000000000
    s21_decimal decimal_check = {{0x2D078000, 0xFFFFF694, 0x1F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2066) {
    // -5.90295775E+20
    int f = -503316481;
    // -590295800000000000000
    s21_decimal decimal_check = {{0x2D078000, 0xFFFFF694, 0x1F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2067) {
    // 5.9029574E+20
    int f = 1644167166;
    // 590295700000000000000
    s21_decimal decimal_check = {{0x1C8D4000, 0xFFFF9BA1, 0x1F, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2068) {
    // -5.9029574E+20
    int f = -503316482;
    // -590295700000000000000
    s21_decimal decimal_check = {{0x1C8D4000, 0xFFFF9BA1, 0x1F, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2069) {
    // 4.91913164E+20
    int f = 1641370965;
    // 491913200000000000000
    s21_decimal decimal_check = {{0xD5AF0000, 0xAAAAC121, 0x1A, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2070) {
    // -4.91913164E+20
    int f = -506112683;
    // -491913200000000000000
    s21_decimal decimal_check = {{0xD5AF0000, 0xAAAAC121, 0x1A, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2071) {
    // 3.93530517E+20
    int f = 1638574762;
    // 393530500000000000000
    s21_decimal decimal_check = {{0x6DDC4000, 0x555530BC, 0x15, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2072) {
    // -3.93530517E+20
    int f = -508908886;
    // -393530500000000000000
    s21_decimal decimal_check = {{0x6DDC4000, 0x555530BC, 0x15, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2073) {
    // 1.47573953E+20
    int f = 1627389952;
    // 147574000000000000000
    s21_decimal decimal_check = {{0x937F0000, 0x2B1E, 0x8, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2074) {
    // -1.47573953E+20
    int f = -520093696;
    // -147574000000000000000
    s21_decimal decimal_check = {{0x937F0000, 0x2B1E, 0x8, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2075) {
    // 1.47573944E+20
    int f = 1627389951;
    // 147573900000000000000
    s21_decimal decimal_check = {{0x8304C000, 0xFFFFD02B, 0x7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2076) {
    // -1.47573944E+20
    int f = -520093697;
    // -147573900000000000000
    s21_decimal decimal_check = {{0x8304C000, 0xFFFFD02B, 0x7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2077) {
    // 1.47573935E+20
    int f = 1627389950;
    // 147573900000000000000
    s21_decimal decimal_check = {{0x8304C000, 0xFFFFD02B, 0x7, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2078) {
    // -1.47573935E+20
    int f = -520093698;
    // -147573900000000000000
    s21_decimal decimal_check = {{0x8304C000, 0xFFFFD02B, 0x7, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2079) {
    // 1.22978291E+20
    int f = 1624593749;
    // 122978300000000000000
    s21_decimal decimal_check = {{0x756BC000, 0xAAAAB048, 0x6, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2080) {
    // -1.22978291E+20
    int f = -522889899;
    // -122978300000000000000
    s21_decimal decimal_check = {{0x756BC000, 0xAAAAB048, 0x6, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2081) {
    // 9.83826292E+19
    int f = 1621797546;
    // 98382630000000000000
    s21_decimal decimal_check = {{0x42B06000, 0x555550BB, 0x5, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2082) {
    // -9.83826292E+19
    int f = -525686102;
    // -98382630000000000000
    s21_decimal decimal_check = {{0x42B06000, 0x555550BB, 0x5, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2083) {
    // 6.14891454E+19
    int f = 1616205141;
    // 61489150000000000000
    s21_decimal decimal_check = {{0x3AB5E000, 0x55555824, 0x3, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2084) {
    // -6.14891454E+19
    int f = -531278507;
    // -61489150000000000000
    s21_decimal decimal_check = {{0x3AB5E000, 0x55555824, 0x3, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2085) {
    // 3.68934881E+19
    int f = 1610612736;
    // 36893490000000000000
    s21_decimal decimal_check = {{0x566D2000, 0x1AF, 0x2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2086) {
    // -3.68934881E+19
    int f = -536870912;
    // -36893490000000000000
    s21_decimal decimal_check = {{0x566D2000, 0x1AF, 0x2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2087) {
    // 3.68934859E+19
    int f = 1610612735;
    // 36893490000000000000
    s21_decimal decimal_check = {{0x566D2000, 0x1AF, 0x2, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2088) {
    // -3.68934859E+19
    int f = -536870913;
    // -36893490000000000000
    s21_decimal decimal_check = {{0x566D2000, 0x1AF, 0x2, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2089) {
    // 3.68934837E+19
    int f = 1610612734;
    // 36893480000000000000
    s21_decimal decimal_check = {{0x7FA8000, 0xFFFFF897, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2090) {
    // -3.68934837E+19
    int f = -536870914;
    // -36893480000000000000
    s21_decimal decimal_check = {{0x7FA8000, 0xFFFFF897, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2091) {
    // 3.07445727E+19
    int f = 1607816533;
    // 30744570000000000000
    s21_decimal decimal_check = {{0xF621A000, 0xAAAAA785, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2092) {
    // -3.07445727E+19
    int f = -539667115;
    // -30744570000000000000
    s21_decimal decimal_check = {{0xF621A000, 0xAAAAA785, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2093) {
    // 2.76701161E+19
    int f = 1606418432;
    // 27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2094) {
    // -2.76701161E+19
    int f = -541065216;
    // -27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2095) {
    // 2.45956573E+19
    int f = 1605020330;
    // 24595660000000000000
    s21_decimal decimal_check = {{0xE448C000, 0x55555674, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2096) {
    // -2.45956573E+19
    int f = -542463318;
    // -24595660000000000000
    s21_decimal decimal_check = {{0xE448C000, 0x55555674, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2097) {
    // 8.58993459E+09
    int f = 1342177280;
    // 8589935000
    s21_decimal decimal_check = {{0x198, 0x2, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2098) {
    // -8.58993459E+09
    int f = -805306368;
    // -8589935000
    s21_decimal decimal_check = {{0x198, 0x2, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2099) {
    // 8.58993408E+09
    int f = 1342177279;
    // 8589934000
    s21_decimal decimal_check = {{0xFFFFFDB0, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2100) {
    // -8.58993408E+09
    int f = -805306369;
    // -8589934000
    s21_decimal decimal_check = {{0xFFFFFDB0, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2101) {
    // 8.58993357E+09
    int f = 1342177278;
    // 8589934000
    s21_decimal decimal_check = {{0xFFFFFDB0, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2102) {
    // -8.58993357E+09
    int f = -805306370;
    // -8589934000
    s21_decimal decimal_check = {{0xFFFFFDB0, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2103) {
    // 7.15827866E+09
    int f = 1339381077;
    // 7158279000
    s21_decimal decimal_check = {{0xAAAAAB58, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2104) {
    // -7.15827866E+09
    int f = -808102571;
    // -7158279000
    s21_decimal decimal_check = {{0xAAAAAB58, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2105) {
    // 6.44245094E+09
    int f = 1337982976;
    // 6442451000
    s21_decimal decimal_check = {{0x80000038, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2106) {
    // -6.44245094E+09
    int f = -809500672;
    // -6442451000
    s21_decimal decimal_check = {{0x80000038, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2107) {
    // 5.72662272E+09
    int f = 1336584874;
    // 5726623000
    s21_decimal decimal_check = {{0x55555518, 0x1, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2108) {
    // -5.72662272E+09
    int f = -810898774;
    // -5726623000
    s21_decimal decimal_check = {{0x55555518, 0x1, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2109) {
    // 5131067.5
    int f = 1251776119;
    // 5131068
    s21_decimal decimal_check = {{0x4E4B3C, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2110) {
    // -5131067.5
    int f = -895707529;
    // -5131068
    s21_decimal decimal_check = {{0x4E4B3C, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2111) {
    // 5131067
    int f = 1251776118;
    // 5131067
    s21_decimal decimal_check = {{0x4E4B3B, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2112) {
    // -5131067
    int f = -895707530;
    // -5131067
    s21_decimal decimal_check = {{0x4E4B3B, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2113) {
    // 5131066.5
    int f = 1251776117;
    // 5131066
    s21_decimal decimal_check = {{0x4E4B3A, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2114) {
    // -5131066.5
    int f = -895707531;
    // -5131066
    s21_decimal decimal_check = {{0x4E4B3A, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2115) {
    // 1131071.13
    int f = 1233785337;
    // 1131071
    s21_decimal decimal_check = {{0x11423F, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2116) {
    // -1131071.13
    int f = -913698311;
    // -1131071
    s21_decimal decimal_check = {{0x11423F, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2117) {
    // 1131071
    int f = 1233785336;
    // 1131071
    s21_decimal decimal_check = {{0x11423F, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2118) {
    // -1131071
    int f = -913698312;
    // -1131071
    s21_decimal decimal_check = {{0x11423F, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2119) {
    // 1131070.88
    int f = 1233785335;
    // 1131071
    s21_decimal decimal_check = {{0x11423F, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2120) {
    // -1131070.88
    int f = -913698313;
    // -1131071
    s21_decimal decimal_check = {{0x11423F, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2121) {
    // 131071.992
    int f = 1207959551;
    // 131072
    s21_decimal decimal_check = {{0x20000, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2122) {
    // -131071.992
    int f = -939524097;
    // -131072
    s21_decimal decimal_check = {{0x20000, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2123) {
    // 131071.008
    int f = 1207959425;
    // 131071
    s21_decimal decimal_check = {{0x1FFFF, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2124) {
    // -131071.008
    int f = -939524223;
    // -131071
    s21_decimal decimal_check = {{0x1FFFF, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2125) {
    // 131071
    int f = 1207959424;
    // 131071
    s21_decimal decimal_check = {{0x1FFFF, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2126) {
    // -131071
    int f = -939524224;
    // -131071
    s21_decimal decimal_check = {{0x1FFFF, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2127) {
    // 131070.992
    int f = 1207959423;
    // 131071
    s21_decimal decimal_check = {{0x1FFFF, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2128) {
    // -131070.992
    int f = -939524225;
    // -131071
    s21_decimal decimal_check = {{0x1FFFF, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2129) {
    // 109226.664
    int f = 1205163349;
    // 109226.7
    s21_decimal decimal_check = {{0x10AAAB, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2130) {
    // -109226.664
    int f = -942320299;
    // -109226.7
    s21_decimal decimal_check = {{0x10AAAB, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2131) {
    // 98304.0078
    int f = 1203765249;
    // 98304.01
    s21_decimal decimal_check = {{0x960001, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2132) {
    // -98304.0078
    int f = -943718399;
    // -98304.01
    s21_decimal decimal_check = {{0x960001, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2133) {
    // 98304
    int f = 1203765248;
    // 98304
    s21_decimal decimal_check = {{0x18000, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2134) {
    // -98304
    int f = -943718400;
    // -98304
    s21_decimal decimal_check = {{0x18000, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2135) {
    // 98303.9922
    int f = 1203765247;
    // 98303.99
    s21_decimal decimal_check = {{0x95FFFF, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2136) {
    // -98303.9922
    int f = -943718401;
    // -98303.99
    s21_decimal decimal_check = {{0x95FFFF, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2137) {
    // 87381.3281
    int f = 1202367146;
    // 87381.33
    s21_decimal decimal_check = {{0x855555, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2138) {
    // -87381.3281
    int f = -945116502;
    // -87381.33
    s21_decimal decimal_check = {{0x855555, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2139) {
    // 87381.0078
    int f = 1202367105;
    // 87381.01
    s21_decimal decimal_check = {{0x855535, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2140) {
    // -87381.0078
    int f = -945116543;
    // -87381.01
    s21_decimal decimal_check = {{0x855535, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2141) {
    // 87381
    int f = 1202367104;
    // 87381
    s21_decimal decimal_check = {{0x15555, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2142) {
    // -87381
    int f = -945116544;
    // -87381
    s21_decimal decimal_check = {{0x15555, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2143) {
    // 87380.9922
    int f = 1202367103;
    // 87380.99
    s21_decimal decimal_check = {{0x855533, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2144) {
    // -87380.9922
    int f = -945116545;
    // -87380.99
    s21_decimal decimal_check = {{0x855533, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2145) {
    // 50000.0039
    int f = 1195593729;
    // 50000
    s21_decimal decimal_check = {{0xC350, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2146) {
    // -50000.0039
    int f = -951889919;
    // -50000
    s21_decimal decimal_check = {{0xC350, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2147) {
    // 50000
    int f = 1195593728;
    // 50000
    s21_decimal decimal_check = {{0xC350, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2148) {
    // -50000
    int f = -951889920;
    // -50000
    s21_decimal decimal_check = {{0xC350, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2149) {
    // 49999.9961
    int f = 1195593727;
    // 50000
    s21_decimal decimal_check = {{0xC350, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2150) {
    // -49999.9961
    int f = -951889921;
    // -50000
    s21_decimal decimal_check = {{0xC350, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2151) {
    // 32000.002
    int f = 1190789121;
    // 32000
    s21_decimal decimal_check = {{0x7D00, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2152) {
    // -32000.002
    int f = -956694527;
    // -32000
    s21_decimal decimal_check = {{0x7D00, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2153) {
    // 32000
    int f = 1190789120;
    // 32000
    s21_decimal decimal_check = {{0x7D00, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2154) {
    // -32000
    int f = -956694528;
    // -32000
    s21_decimal decimal_check = {{0x7D00, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2155) {
    // 31999.998
    int f = 1190789119;
    // 32000
    s21_decimal decimal_check = {{0x7D00, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2156) {
    // -31999.998
    int f = -956694529;
    // -32000
    s21_decimal decimal_check = {{0x7D00, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2157) {
    // 1024.00012
    int f = 1149239297;
    // 1024
    s21_decimal decimal_check = {{0x400, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2158) {
    // -1024.00012
    int f = -998244351;
    // -1024
    s21_decimal decimal_check = {{0x400, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2159) {
    // 1024
    int f = 1149239296;
    // 1024
    s21_decimal decimal_check = {{0x400, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2160) {
    // -1024
    int f = -998244352;
    // -1024
    s21_decimal decimal_check = {{0x400, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2161) {
    // 1023.99994
    int f = 1149239295;
    // 1024
    s21_decimal decimal_check = {{0x400, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2162) {
    // -1023.99994
    int f = -998244353;
    // -1024
    s21_decimal decimal_check = {{0x400, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2163) {
    // 512.000061
    int f = 1140850689;
    // 512.0001
    s21_decimal decimal_check = {{0x4E2001, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2164) {
    // -512.000061
    int f = -1006632959;
    // -512.0001
    s21_decimal decimal_check = {{0x4E2001, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2165) {
    // 512
    int f = 1140850688;
    // 512
    s21_decimal decimal_check = {{0x200, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2166) {
    // -512
    int f = -1006632960;
    // -512
    s21_decimal decimal_check = {{0x200, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2167) {
    // 511.999969
    int f = 1140850687;
    // 512
    s21_decimal decimal_check = {{0x200, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2168) {
    // -511.999969
    int f = -1006632961;
    // -512
    s21_decimal decimal_check = {{0x200, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2169) {
    // 511.999939
    int f = 1140850686;
    // 511.9999
    s21_decimal decimal_check = {{0x4E1FFF, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2170) {
    // -511.999939
    int f = -1006632962;
    // -511.9999
    s21_decimal decimal_check = {{0x4E1FFF, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2171) {
    // 426.666656
    int f = 1138054485;
    // 426.6667
    s21_decimal decimal_check = {{0x411AAB, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2172) {
    // -426.666656
    int f = -1009429163;
    // -426.6667
    s21_decimal decimal_check = {{0x411AAB, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2173) {
    // 384
    int f = 1136656384;
    // 384
    s21_decimal decimal_check = {{0x180, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2174) {
    // -384
    int f = -1010827264;
    // -384
    s21_decimal decimal_check = {{0x180, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2175) {
    // 341.333313
    int f = 1135258282;
    // 341.3333
    s21_decimal decimal_check = {{0x341555, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2176) {
    // -341.333313
    int f = -1012225366;
    // -341.3333
    s21_decimal decimal_check = {{0x341555, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2177) {
    // 64.0000076
    int f = 1115684865;
    // 64.00001
    s21_decimal decimal_check = {{0x61A801, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2178) {
    // -64.0000076
    int f = -1031798783;
    // -64.00001
    s21_decimal decimal_check = {{0x61A801, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2179) {
    // 64
    int f = 1115684864;
    // 64
    s21_decimal decimal_check = {{0x40, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2180) {
    // -64
    int f = -1031798784;
    // -64
    s21_decimal decimal_check = {{0x40, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2181) {
    // 63.9999962
    int f = 1115684863;
    // 64
    s21_decimal decimal_check = {{0x40, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2182) {
    // -63.9999962
    int f = -1031798785;
    // -64
    s21_decimal decimal_check = {{0x40, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2183) {
    // 32
    int f = 1107296256;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2184) {
    // -32
    int f = -1040187392;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2185) {
    // 31.9999981
    int f = 1107296255;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2186) {
    // -31.9999981
    int f = -1040187393;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2187) {
    // 31.9999962
    int f = 1107296254;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2188) {
    // -31.9999962
    int f = -1040187394;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2189) {
    // 26.666666
    int f = 1104500053;
    // 26.66667
    s21_decimal decimal_check = {{0x28B0AB, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2190) {
    // -26.666666
    int f = -1042983595;
    // -26.66667
    s21_decimal decimal_check = {{0x28B0AB, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2191) {
    // 24
    int f = 1103101952;
    // 24
    s21_decimal decimal_check = {{0x18, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2192) {
    // -24
    int f = -1044381696;
    // -24
    s21_decimal decimal_check = {{0x18, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2193) {
    // 21.3333321
    int f = 1101703850;
    // 21.33333
    s21_decimal decimal_check = {{0x208D55, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2194) {
    // -21.3333321
    int f = -1045779798;
    // -21.33333
    s21_decimal decimal_check = {{0x208D55, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2195) {
    // 16.0000019
    int f = 1098907649;
    // 16
    s21_decimal decimal_check = {{0x10, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2196) {
    // -16.0000019
    int f = -1048575999;
    // -16
    s21_decimal decimal_check = {{0x10, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2197) {
    // 16
    int f = 1098907648;
    // 16
    s21_decimal decimal_check = {{0x10, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2198) {
    // -16
    int f = -1048576000;
    // -16
    s21_decimal decimal_check = {{0x10, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2199) {
    // 15.999999
    int f = 1098907647;
    // 16
    s21_decimal decimal_check = {{0x10, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2200) {
    // -15.999999
    int f = -1048576001;
    // -16
    s21_decimal decimal_check = {{0x10, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2201) {
    // 10.9803553
    int f = 1093644169;
    // 10.98036
    s21_decimal decimal_check = {{0x10C134, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2202) {
    // -10.9803553
    int f = -1053839479;
    // -10.98036
    s21_decimal decimal_check = {{0x10C134, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2203) {
    // 9.00000095
    int f = 1091567617;
    // 9.000001
    s21_decimal decimal_check = {{0x895441, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2204) {
    // -9.00000095
    int f = -1055916031;
    // -9.000001
    s21_decimal decimal_check = {{0x895441, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2205) {
    // 9
    int f = 1091567616;
    // 9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2206) {
    // -9
    int f = -1055916032;
    // -9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2207) {
    // 8.99999905
    int f = 1091567615;
    // 8.999999
    s21_decimal decimal_check = {{0x89543F, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2208) {
    // -8.99999905
    int f = -1055916033;
    // -8.999999
    s21_decimal decimal_check = {{0x89543F, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2209) {
    // 8
    int f = 1090519040;
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2210) {
    // -8
    int f = -1056964608;
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2211) {
    // 7.99999952
    int f = 1090519039;
    // 8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2212) {
    // -7.99999952
    int f = -1056964609;
    // -8
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2213) {
    // 6.66666651
    int f = 1087722837;
    // 6.666667
    s21_decimal decimal_check = {{0x65B9AB, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2214) {
    // -6.66666651
    int f = -1059760811;
    // -6.666667
    s21_decimal decimal_check = {{0x65B9AB, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2215) {
    // 6
    int f = 1086324736;
    // 6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2216) {
    // -6
    int f = -1061158912;
    // -6
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2217) {
    // 5.33333302
    int f = 1084926634;
    // 5.333333
    s21_decimal decimal_check = {{0x516155, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2218) {
    // -5.33333302
    int f = -1062557014;
    // -5.333333
    s21_decimal decimal_check = {{0x516155, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2219) {
    // 4
    int f = 1082130432;
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2220) {
    // -4
    int f = -1065353216;
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2221) {
    // 3.99999976
    int f = 1082130431;
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2222) {
    // -3.99999976
    int f = -1065353217;
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2223) {
    // 3.99999952
    int f = 1082130430;
    // 4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2224) {
    // -3.99999952
    int f = -1065353218;
    // -4
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2225) {
    // 3.33333325
    int f = 1079334229;
    // 3.333333
    s21_decimal decimal_check = {{0x32DCD5, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2226) {
    // -3.33333325
    int f = -1068149419;
    // -3.333333
    s21_decimal decimal_check = {{0x32DCD5, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2227) {
    // 3
    int f = 1077936128;
    // 3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2228) {
    // -3
    int f = -1069547520;
    // -3
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2229) {
    // 2.66666651
    int f = 1076538026;
    // 2.666667
    s21_decimal decimal_check = {{0x28B0AB, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2230) {
    // -2.66666651
    int f = -1070945622;
    // -2.666667
    s21_decimal decimal_check = {{0x28B0AB, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2231) {
    // 2.00000024
    int f = 1073741825;
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2232) {
    // -2.00000024
    int f = -1073741823;
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2233) {
    // 2
    int f = 1073741824;
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2234) {
    // -2
    int f = -1073741824;
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2235) {
    // 1.99999988
    int f = 1073741823;
    // 2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2236) {
    // -1.99999988
    int f = -1073741825;
    // -2
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2237) {
    // 1.50000012
    int f = 1069547521;
    // 1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2238) {
    // -1.50000012
    int f = -1077936127;
    // -1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2239) {
    // 1.5
    int f = 1069547520;
    // 1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2240) {
    // -1.5
    int f = -1077936128;
    // -1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2241) {
    // 1.49999988
    int f = 1069547519;
    // 1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2242) {
    // -1.49999988
    int f = -1077936129;
    // -1.5
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2243) {
    // 1
    int f = 1065353216;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2244) {
    // -1
    int f = -1082130432;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2245) {
    // 1
    int f = 1065353216;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2246) {
    // -1
    int f = -1082130432;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2247) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2248) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2249) {
    // 1
    int f = 1065353216;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2250) {
    // -1
    int f = -1082130432;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2251) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2252) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2253) {
    // 1
    int f = 1065353216;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2254) {
    // -1
    int f = -1082130432;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2255) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2256) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2257) {
    // 1
    int f = 1065353216;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2258) {
    // -1
    int f = -1082130432;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2259) {
    // 1.00000024
    int f = 1065353218;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2260) {
    // -1.00000024
    int f = -1082130430;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2261) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2262) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2263) {
    // 1.00000024
    int f = 1065353218;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2264) {
    // -1.00000024
    int f = -1082130430;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2265) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2266) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2267) {
    // 1.00000024
    int f = 1065353218;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2268) {
    // -1.00000024
    int f = -1082130430;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2269) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2270) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2271) {
    // 1.00000024
    int f = 1065353218;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2272) {
    // -1.00000024
    int f = -1082130430;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2273) {
    // 1.00000024
    int f = 1065353218;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2274) {
    // -1.00000024
    int f = -1082130430;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2275) {
    // 2.76701183E+19
    int f = 1606418433;
    // 27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2276) {
    // -2.76701183E+19
    int f = -541065215;
    // -27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2277) {
    // 2.76701161E+19
    int f = 1606418432;
    // 27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2278) {
    // -2.76701161E+19
    int f = -541065216;
    // -27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2279) {
    // 2.76701161E+19
    int f = 1606418432;
    // 27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2280) {
    // -2.76701161E+19
    int f = -541065216;
    // -27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2281) {
    // 2.76701161E+19
    int f = 1606418432;
    // 27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2282) {
    // -2.76701161E+19
    int f = -541065216;
    // -27670120000000000000
    s21_decimal decimal_check = {{0x946E8000, 0x80000389, 0x1, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2283) {
    // 87381.3359
    int f = 1202367147;
    // 87381.34
    s21_decimal decimal_check = {{0x855556, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2284) {
    // -87381.3359
    int f = -945116501;
    // -87381.34
    s21_decimal decimal_check = {{0x855556, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2285) {
    // 87381.3359
    int f = 1202367147;
    // 87381.34
    s21_decimal decimal_check = {{0x855556, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2286) {
    // -87381.3359
    int f = -945116501;
    // -87381.34
    s21_decimal decimal_check = {{0x855556, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2287) {
    // 87381.3281
    int f = 1202367146;
    // 87381.33
    s21_decimal decimal_check = {{0x855555, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2288) {
    // -87381.3281
    int f = -945116502;
    // -87381.33
    s21_decimal decimal_check = {{0x855555, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2289) {
    // 87381.3281
    int f = 1202367146;
    // 87381.33
    s21_decimal decimal_check = {{0x855555, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2290) {
    // -87381.3281
    int f = -945116502;
    // -87381.33
    s21_decimal decimal_check = {{0x855555, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2291) {
    // 32.0000038
    int f = 1107296257;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2292) {
    // -32.0000038
    int f = -1040187391;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2293) {
    // 32.0000038
    int f = 1107296257;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2294) {
    // -32.0000038
    int f = -1040187391;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2295) {
    // 32
    int f = 1107296256;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2296) {
    // -32
    int f = -1040187392;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2297) {
    // 32
    int f = 1107296256;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2298) {
    // -32
    int f = -1040187392;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2299) {
    // 32
    int f = 1107296256;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2300) {
    // -32
    int f = -1040187392;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2301) {
    // 32
    int f = 1107296256;
    // 32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2302) {
    // -32
    int f = -1040187392;
    // -32
    s21_decimal decimal_check = {{0x20, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2303) {
    // 0.15625
    int f = 1042284544;
    // 0.15625
    s21_decimal decimal_check = {{0x3D09, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2304) {
    // -0.15625
    int f = -1105199104;
    // -0.15625
    s21_decimal decimal_check = {{0x3D09, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2305) {
    // 0.99999994
    int f = 1065353215;
    // 0.9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2306) {
    // -0.99999994
    int f = -1082130433;
    // -0.9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2307) {
    // 0.249999985
    int f = 1048575999;
    // 0.25
    s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2308) {
    // -0.249999985
    int f = -1098907649;
    // -0.25
    s21_decimal decimal_check = {{0x19, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2309) {
    // 0.0156249991
    int f = 1015021567;
    // 0.015625
    s21_decimal decimal_check = {{0x3D09, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2310) {
    // -0.0156249991
    int f = -1132462081;
    // -0.015625
    s21_decimal decimal_check = {{0x3D09, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2311) {
    // 6.10351526E-05
    int f = 947912703;
    // 0.00006103515
    s21_decimal decimal_check = {{0x5D21DB, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2312) {
    // -6.10351526E-05
    int f = -1199570945;
    // -0.00006103515
    s21_decimal decimal_check = {{0x5D21DB, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2313) {
    // 9.31322519E-10
    int f = 813694975;
    // 0.0000000009313225
    s21_decimal decimal_check = {{0x8E1BC9, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2314) {
    // -9.31322519E-10
    int f = -1333788673;
    // -0.0000000009313225
    s21_decimal decimal_check = {{0x8E1BC9, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2315) {
    // 2.16840422E-19
    int f = 545259519;
    // 0.0000000000000000002168404
    s21_decimal decimal_check = {{0x211654, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2316) {
    // -2.16840422E-19
    int f = -1602224129;
    // -0.0000000000000000002168404
    s21_decimal decimal_check = {{0x211654, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2317) {
    // 1.08420211E-19
    int f = 536870911;
    // 0.0000000000000000001084202
    s21_decimal decimal_check = {{0x108B2A, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2318) {
    // -1.08420211E-19
    int f = -1610612737;
    // -0.0000000000000000001084202
    s21_decimal decimal_check = {{0x108B2A, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2319) {
    // 5.42101054E-20
    int f = 528482303;
    // 0.00000000000000000005421011
    s21_decimal decimal_check = {{0x52B7D3, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2320) {
    // -5.42101054E-20
    int f = -1619001345;
    // -0.00000000000000000005421011
    s21_decimal decimal_check = {{0x52B7D3, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2321) {
    // 1.35525263E-20
    int f = 511705087;
    // 0.00000000000000000001355253
    s21_decimal decimal_check = {{0x14ADF5, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2322) {
    // -1.35525263E-20
    int f = -1635778561;
    // -0.00000000000000000001355253
    s21_decimal decimal_check = {{0x14ADF5, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2323) {
    // 8.47032897E-22
    int f = 478150655;
    // 0.0000000000000000000008470329
    s21_decimal decimal_check = {{0x813F39, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2324) {
    // -8.47032897E-22
    int f = -1669332993;
    // -0.0000000000000000000008470329
    s21_decimal decimal_check = {{0x813F39, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2325) {
    // 3.30872225E-24
    int f = 411041791;
    // 0.0000000000000000000000033087
    s21_decimal decimal_check = {{0x813F, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2326) {
    // -3.30872225E-24
    int f = -1736441857;
    // -0.0000000000000000000000033087
    s21_decimal decimal_check = {{0x813F, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2327) {
    // 1.0097419E-28
    int f = 285212671;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2328) {
    // -1.0097419E-28
    int f = -1862270977;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2329) {
    // 4.03896759E-28
    int f = 301989887;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2330) {
    // -4.03896759E-28
    int f = -1845493761;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2331) {
    // 6.46234815E-27
    int f = 335544319;
    // 0.0000000000000000000000000065
    s21_decimal decimal_check = {{0x41, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2332) {
    // -6.46234815E-27
    int f = -1811939329;
    // -0.0000000000000000000000000065
    s21_decimal decimal_check = {{0x41, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2333) {
    // 1.65436113E-24
    int f = 402653183;
    // 0.0000000000000000000000016544
    s21_decimal decimal_check = {{0x40A0, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2334) {
    // -1.65436113E-24
    int f = -1744830465;
    // -0.0000000000000000000000016544
    s21_decimal decimal_check = {{0x40A0, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2335) {
    // 1.33333325
    int f = 1068149418;
    // 1.333333
    s21_decimal decimal_check = {{0x145855, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2336) {
    // -1.33333325
    int f = -1079334230;
    // -1.333333
    s21_decimal decimal_check = {{0x145855, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2337) {
    // 0.666666627
    int f = 1059760810;
    // 0.6666666
    s21_decimal decimal_check = {{0x65B9AA, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2338) {
    // -0.666666627
    int f = -1087722838;
    // -0.6666666
    s21_decimal decimal_check = {{0x65B9AA, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2339) {
    // 0.166666657
    int f = 1042983594;
    // 0.1666667
    s21_decimal decimal_check = {{0x196E6B, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2340) {
    // -0.166666657
    int f = -1104500054;
    // -0.1666667
    s21_decimal decimal_check = {{0x196E6B, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2341) {
    // 0.010416666
    int f = 1009429162;
    // 0.01041667
    s21_decimal decimal_check = {{0xFE503, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2342) {
    // -0.010416666
    int f = -1138054486;
    // -0.01041667
    s21_decimal decimal_check = {{0xFE503, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2343) {
    // 4.06901017E-05
    int f = 942320298;
    // 0.0000406901
    s21_decimal decimal_check = {{0x63575, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2344) {
    // -4.06901017E-05
    int f = -1205163350;
    // -0.0000406901
    s21_decimal decimal_check = {{0x63575, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2345) {
    // 6.20881679E-10
    int f = 808102570;
    // 0.0000000006208817
    s21_decimal decimal_check = {{0x5EBD31, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2346) {
    // -6.20881679E-10
    int f = -1339381078;
    // -0.0000000006208817
    s21_decimal decimal_check = {{0x5EBD31, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2347) {
    // 1.5522042E-10
    int f = 791325354;
    // 0.0000000001552204
    s21_decimal decimal_check = {{0x17AF4C, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2348) {
    // -1.5522042E-10
    int f = -1356158294;
    // -0.0000000001552204
    s21_decimal decimal_check = {{0x17AF4C, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2349) {
    // 3.8805105E-11
    int f = 774548138;
    // 0.0000000000388051
    s21_decimal decimal_check = {{0x5EBD3, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2350) {
    // -3.8805105E-11
    int f = -1372935510;
    // -0.0000000000388051
    s21_decimal decimal_check = {{0x5EBD3, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2351) {
    // 2.42531906E-12
    int f = 740993706;
    // 0.000000000002425319
    s21_decimal decimal_check = {{0x2501E7, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2352) {
    // -2.42531906E-12
    int f = -1406489942;
    // -0.000000000002425319
    s21_decimal decimal_check = {{0x2501E7, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2353) {
    // 9.47390258E-15
    int f = 673884842;
    // 0.000000000000009473903
    s21_decimal decimal_check = {{0x908F6F, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2354) {
    // -9.47390258E-15
    int f = -1473598806;
    // -0.000000000000009473903
    s21_decimal decimal_check = {{0x908F6F, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2355) {
    // 4.73695129E-15
    int f = 665496234;
    // 0.000000000000004736951
    s21_decimal decimal_check = {{0x4847B7, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2356) {
    // -4.73695129E-15
    int f = -1481987414;
    // -0.000000000000004736951
    s21_decimal decimal_check = {{0x4847B7, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2357) {
    // 1.8503716E-17
    int f = 598387370;
    // 0.00000000000000001850372
    s21_decimal decimal_check = {{0x1C3C04, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2358) {
    // -1.8503716E-17
    int f = -1549096278;
    // -0.00000000000000001850372
    s21_decimal decimal_check = {{0x1C3C04, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2359) {
    // 1.15648225E-18
    int f = 564832938;
    // 0.000000000000000001156482
    s21_decimal decimal_check = {{0x11A582, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2360) {
    // -1.15648225E-18
    int f = -1582650710;
    // -0.000000000000000001156482
    s21_decimal decimal_check = {{0x11A582, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2361) {
    // 1.44560281E-19
    int f = 539667114;
    // 0.0000000000000000001445603
    s21_decimal decimal_check = {{0x160EE3, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2362) {
    // -1.44560281E-19
    int f = -1607816534;
    // -0.0000000000000000001445603
    s21_decimal decimal_check = {{0x160EE3, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2363) {
    // 7.22801405E-20
    int f = 531278506;
    // 0.00000000000000000007228014
    s21_decimal decimal_check = {{0x6E4A6E, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2364) {
    // -7.22801405E-20
    int f = -1616205142;
    // -0.00000000000000000007228014
    s21_decimal decimal_check = {{0x6E4A6E, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2365) {
    // 3.61400703E-20
    int f = 522889898;
    // 0.00000000000000000003614007
    s21_decimal decimal_check = {{0x372537, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2366) {
    // -3.61400703E-20
    int f = -1624593750;
    // -0.00000000000000000003614007
    s21_decimal decimal_check = {{0x372537, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2367) {
    // 9.03501757E-21
    int f = 506112682;
    // 0.000000000000000000009035018
    s21_decimal decimal_check = {{0x89DD0A, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2368) {
    // -9.03501757E-21
    int f = -1641370966;
    // -0.000000000000000000009035018
    s21_decimal decimal_check = {{0x89DD0A, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2369) {
    // 5.64688598E-22
    int f = 472558250;
    // 0.0000000000000000000005646886
    s21_decimal decimal_check = {{0x562A26, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2370) {
    // -5.64688598E-22
    int f = -1674925398;
    // -0.0000000000000000000005646886
    s21_decimal decimal_check = {{0x562A26, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2371) {
    // 2.20581484E-24
    int f = 405449386;
    // 0.0000000000000000000000022058
    s21_decimal decimal_check = {{0x562A, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2372) {
    // -2.20581484E-24
    int f = -1742034262;
    // -0.0000000000000000000000022058
    s21_decimal decimal_check = {{0x562A, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2373) {
    // 5.51453709E-25
    int f = 388672170;
    // 0.0000000000000000000000005515
    s21_decimal decimal_check = {{0x158B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2374) {
    // -5.51453709E-25
    int f = -1758811478;
    // -0.0000000000000000000000005515
    s21_decimal decimal_check = {{0x158B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2375) {
    // 1.72329284E-26
    int f = 346729130;
    // 0.0000000000000000000000000172
    s21_decimal decimal_check = {{0xAC, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2376) {
    // -1.72329284E-26
    int f = -1800754518;
    // -0.0000000000000000000000000172
    s21_decimal decimal_check = {{0xAC, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2377) {
    // 4.3082321E-27
    int f = 329951914;
    // 0.0000000000000000000000000043
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2378) {
    // -4.3082321E-27
    int f = -1817531734;
    // -0.0000000000000000000000000043
    s21_decimal decimal_check = {{0x2B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2379) {
    // 2.69264506E-28
    int f = 296397482;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2380) {
    // -2.69264506E-28
    int f = -1851086166;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2381) {
    // 1.66666663
    int f = 1070945621;
    // 1.666667
    s21_decimal decimal_check = {{0x196E6B, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2382) {
    // -1.66666663
    int f = -1076538027;
    // -1.666667
    s21_decimal decimal_check = {{0x196E6B, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2383) {
    // 0.833333313
    int f = 1062557013;
    // 0.8333333
    s21_decimal decimal_check = {{0x7F2815, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2384) {
    // -0.833333313
    int f = -1084926635;
    // -0.8333333
    s21_decimal decimal_check = {{0x7F2815, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2385) {
    // 0.208333328
    int f = 1045779797;
    // 0.2083333
    s21_decimal decimal_check = {{0x1FCA05, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2386) {
    // -0.208333328
    int f = -1101703851;
    // -0.2083333
    s21_decimal decimal_check = {{0x1FCA05, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2387) {
    // 0.013020833
    int f = 1012225365;
    // 0.01302083
    s21_decimal decimal_check = {{0x13DE43, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2388) {
    // -0.013020833
    int f = -1135258283;
    // -0.01302083
    s21_decimal decimal_check = {{0x13DE43, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2389) {
    // 5.0862629E-05
    int f = 945116501;
    // 0.00005086263
    s21_decimal decimal_check = {{0x4D9C37, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2390) {
    // -5.0862629E-05
    int f = -1202367147;
    // -0.00005086263
    s21_decimal decimal_check = {{0x4D9C37, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2391) {
    // 7.76102127E-10
    int f = 810898773;
    // 0.0000000007761021
    s21_decimal decimal_check = {{0x766C7D, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2392) {
    // -7.76102127E-10
    int f = -1336584875;
    // -0.0000000007761021
    s21_decimal decimal_check = {{0x766C7D, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2393) {
    // 1.94025532E-10
    int f = 794121557;
    // 0.0000000001940255
    s21_decimal decimal_check = {{0x1D9B1F, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2394) {
    // -1.94025532E-10
    int f = -1353362091;
    // -0.0000000001940255
    s21_decimal decimal_check = {{0x1D9B1F, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2395) {
    // 4.85063829E-11
    int f = 777344341;
    // 0.00000000004850638
    s21_decimal decimal_check = {{0x4A03CE, 0x0, 0x0, 0x110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2396) {
    // -4.85063829E-11
    int f = -1370139307;
    // -0.00000000004850638
    s21_decimal decimal_check = {{0x4A03CE, 0x0, 0x0, 0x80110000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2397) {
    // 3.03164893E-12
    int f = 743789909;
    // 0.000000000003031649
    s21_decimal decimal_check = {{0x2E4261, 0x0, 0x0, 0x120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2398) {
    // -3.03164893E-12
    int f = -1403693739;
    // -0.000000000003031649
    s21_decimal decimal_check = {{0x2E4261, 0x0, 0x0, 0x80120000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2399) {
    // 1.18423786E-14
    int f = 676681045;
    // 0.00000000000001184238
    s21_decimal decimal_check = {{0x1211EE, 0x0, 0x0, 0x140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2400) {
    // -1.18423786E-14
    int f = -1470802603;
    // -0.00000000000001184238
    s21_decimal decimal_check = {{0x1211EE, 0x0, 0x0, 0x80140000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2401) {
    // 5.92118932E-15
    int f = 668292437;
    // 0.000000000000005921189
    s21_decimal decimal_check = {{0x5A59A5, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2402) {
    // -5.92118932E-15
    int f = -1479191211;
    // -0.000000000000005921189
    s21_decimal decimal_check = {{0x5A59A5, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2403) {
    // 7.40148665E-16
    int f = 643126613;
    // 0.0000000000000007401487
    s21_decimal decimal_check = {{0x70F00F, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2404) {
    // -7.40148665E-16
    int f = -1504357035;
    // -0.0000000000000007401487
    s21_decimal decimal_check = {{0x70F00F, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2405) {
    // 2.31296458E-17
    int f = 601183573;
    // 0.00000000000000002312965
    s21_decimal decimal_check = {{0x234B05, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2406) {
    // -2.31296458E-17
    int f = -1546300075;
    // -0.00000000000000002312965
    s21_decimal decimal_check = {{0x234B05, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2407) {
    // 1.44560286E-18
    int f = 567629141;
    // 0.000000000000000001445603
    s21_decimal decimal_check = {{0x160EE3, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2408) {
    // -1.44560286E-18
    int f = -1579854507;
    // -0.000000000000000001445603
    s21_decimal decimal_check = {{0x160EE3, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2409) {
    // 3.61400716E-19
    int f = 550851925;
    // 0.0000000000000000003614007
    s21_decimal decimal_check = {{0x372537, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2410) {
    // -3.61400716E-19
    int f = -1596631723;
    // -0.0000000000000000003614007
    s21_decimal decimal_check = {{0x372537, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2411) {
    // 1.80700358E-19
    int f = 542463317;
    // 0.0000000000000000001807004
    s21_decimal decimal_check = {{0x1B929C, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2412) {
    // -1.80700358E-19
    int f = -1605020331;
    // -0.0000000000000000001807004
    s21_decimal decimal_check = {{0x1B929C, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2413) {
    // 9.03501789E-20
    int f = 534074709;
    // 0.00000000000000000009035018
    s21_decimal decimal_check = {{0x89DD0A, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2414) {
    // -9.03501789E-20
    int f = -1613408939;
    // -0.00000000000000000009035018
    s21_decimal decimal_check = {{0x89DD0A, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2415) {
    // 4.51750894E-20
    int f = 525686101;
    // 0.00000000000000000004517509
    s21_decimal decimal_check = {{0x44EE85, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2416) {
    // -4.51750894E-20
    int f = -1621797547;
    // -0.00000000000000000004517509
    s21_decimal decimal_check = {{0x44EE85, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2417) {
    // 1.12937724E-20
    int f = 508908885;
    // 0.00000000000000000001129377
    s21_decimal decimal_check = {{0x113BA1, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2418) {
    // -1.12937724E-20
    int f = -1638574763;
    // -0.00000000000000000001129377
    s21_decimal decimal_check = {{0x113BA1, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2419) {
    // 7.05860773E-22
    int f = 475354453;
    // 0.0000000000000000000007058608
    s21_decimal decimal_check = {{0x6BB4B0, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2420) {
    // -7.05860773E-22
    int f = -1672129195;
    // -0.0000000000000000000007058608
    s21_decimal decimal_check = {{0x6BB4B0, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2421) {
    // 2.75726864E-24
    int f = 408245589;
    // 0.0000000000000000000000027573
    s21_decimal decimal_check = {{0x6BB5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2422) {
    // -2.75726864E-24
    int f = -1739238059;
    // -0.0000000000000000000000027573
    s21_decimal decimal_check = {{0x6BB5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2423) {
    // 1.37863432E-24
    int f = 399856981;
    // 0.0000000000000000000000013786
    s21_decimal decimal_check = {{0x35DA, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2424) {
    // -1.37863432E-24
    int f = -1747626667;
    // -0.0000000000000000000000013786
    s21_decimal decimal_check = {{0x35DA, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2425) {
    // 6.89317161E-25
    int f = 391468373;
    // 0.0000000000000000000000006893
    s21_decimal decimal_check = {{0x1AED, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2426) {
    // -6.89317161E-25
    int f = -1756015275;
    // -0.0000000000000000000000006893
    s21_decimal decimal_check = {{0x1AED, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2427) {
    // 1.7232929E-25
    int f = 374691157;
    // 0.0000000000000000000000001723
    s21_decimal decimal_check = {{0x6BB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2428) {
    // -1.7232929E-25
    int f = -1772792491;
    // -0.0000000000000000000000001723
    s21_decimal decimal_check = {{0x6BB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2429) {
    // 5.38529032E-27
    int f = 332748117;
    // 0.0000000000000000000000000054
    s21_decimal decimal_check = {{0x36, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2430) {
    // -5.38529032E-27
    int f = -1814735531;
    // -0.0000000000000000000000000054
    s21_decimal decimal_check = {{0x36, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2431) {
    // 3.36580645E-28
    int f = 299193685;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2432) {
    // -3.36580645E-28
    int f = -1848289963;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2433) {
    // 0.75
    int f = 1061158912;
    // 0.75
    s21_decimal decimal_check = {{0x4B, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2434) {
    // -0.75
    int f = -1086324736;
    // -0.75
    s21_decimal decimal_check = {{0x4B, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2435) {
    // 0.5
    int f = 1056964608;
    // 0.5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2436) {
    // -0.5
    int f = -1090519040;
    // -0.5
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2437) {
    // 0.1875
    int f = 1044381696;
    // 0.1875
    s21_decimal decimal_check = {{0x753, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2438) {
    // -0.1875
    int f = -1103101952;
    // -0.1875
    s21_decimal decimal_check = {{0x753, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2439) {
    // 0.125
    int f = 1040187392;
    // 0.125
    s21_decimal decimal_check = {{0x7D, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2440) {
    // -0.125
    int f = -1107296256;
    // -0.125
    s21_decimal decimal_check = {{0x7D, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2441) {
    // 0.0625
    int f = 1031798784;
    // 0.0625
    s21_decimal decimal_check = {{0x271, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2442) {
    // -0.0625
    int f = -1115684864;
    // -0.0625
    s21_decimal decimal_check = {{0x271, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2443) {
    // 0.015625
    int f = 1015021568;
    // 0.015625
    s21_decimal decimal_check = {{0x3D09, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2444) {
    // -0.015625
    int f = -1132462080;
    // -0.015625
    s21_decimal decimal_check = {{0x3D09, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2445) {
    // 0.01171875
    int f = 1010827264;
    // 0.01171875
    s21_decimal decimal_check = {{0x11E1A3, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2446) {
    // -0.01171875
    int f = -1136656384;
    // -0.01171875
    s21_decimal decimal_check = {{0x11E1A3, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2447) {
    // 0.0078125
    int f = 1006632960;
    // 0.0078125
    s21_decimal decimal_check = {{0x1312D, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2448) {
    // -0.0078125
    int f = -1140850688;
    // -0.0078125
    s21_decimal decimal_check = {{0x1312D, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2449) {
    // 0.00390625
    int f = 998244352;
    // 0.00390625
    s21_decimal decimal_check = {{0x5F5E1, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2450) {
    // -0.00390625
    int f = -1149239296;
    // -0.00390625
    s21_decimal decimal_check = {{0x5F5E1, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2451) {
    // 0.000244140625
    int f = 964689920;
    // 0.0002441406
    s21_decimal decimal_check = {{0x2540BE, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2452) {
    // -0.000244140625
    int f = -1182793728;
    // -0.0002441406
    s21_decimal decimal_check = {{0x2540BE, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2453) {
    // 4.57763672E-05
    int f = 943718400;
    // 0.00004577637
    s21_decimal decimal_check = {{0x45D965, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2454) {
    // -4.57763672E-05
    int f = -1203765248;
    // -0.00004577637
    s21_decimal decimal_check = {{0x45D965, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2455) {
    // 3.05175781E-05
    int f = 939524096;
    // 0.00003051758
    s21_decimal decimal_check = {{0x2E90EE, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2456) {
    // -3.05175781E-05
    int f = -1207959552;
    // -0.00003051758
    s21_decimal decimal_check = {{0x2E90EE, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2457) {
    // 1.52587891E-05
    int f = 931135488;
    // 0.00001525879
    s21_decimal decimal_check = {{0x174877, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2458) {
    // -1.52587891E-05
    int f = -1216348160;
    // -0.00001525879
    s21_decimal decimal_check = {{0x174877, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2459) {
    // 4.65661287E-10
    int f = 805306368;
    // 0.0000000004656613
    s21_decimal decimal_check = {{0x470DE5, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2460) {
    // -4.65661287E-10
    int f = -1342177280;
    // -0.0000000004656613
    s21_decimal decimal_check = {{0x470DE5, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2461) {
    // 6.98491931E-10
    int f = 809500672;
    // 0.0000000006984919
    s21_decimal decimal_check = {{0x6A94D7, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2462) {
    // -6.98491931E-10
    int f = -1337982976;
    // -0.0000000006984919
    s21_decimal decimal_check = {{0x6A94D7, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2463) {
    // 1.08420217E-19
    int f = 536870912;
    // 0.0000000000000000001084202
    s21_decimal decimal_check = {{0x108B2A, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2464) {
    // -1.08420217E-19
    int f = -1610612736;
    // -0.0000000000000000001084202
    s21_decimal decimal_check = {{0x108B2A, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2465) {
    // 0.100000001
    int f = 1036831949;
    // 0.1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2466) {
    // -0.100000001
    int f = -1110651699;
    // -0.1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2467) {
    // 0.999000013
    int f = 1065336439;
    // 0.999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x30000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2468) {
    // -0.999000013
    int f = -1082147209;
    // -0.999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80030000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2469) {
    // 0.899999976
    int f = 1063675494;
    // 0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2470) {
    // -0.899999976
    int f = -1083808154;
    // -0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2471) {
    // 0.0998999998
    int f = 1036818527;
    // 0.0999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x40000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2472) {
    // -0.0998999998
    int f = -1110665121;
    // -0.0999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80040000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2473) {
    // 0.00999000017
    int f = 1008971033;
    // 0.00999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x50000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2474) {
    // -0.00999000017
    int f = -1138512615;
    // -0.00999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80050000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2475) {
    // 0.00099900004
    int f = 981659873;
    // 0.000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2476) {
    // -0.00099900004
    int f = -1165823775;
    // -0.000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2477) {
    // 9.98999967E-05
    int f = 953254247;
    // 0.0000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2478) {
    // -9.98999967E-05
    int f = -1194229401;
    // -0.0000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2479) {
    // 9.98999985E-06
    int f = 925342393;
    // 0.00000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2480) {
    // -9.98999985E-06
    int f = -1222141255;
    // -0.00000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80080000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2481) {
    // 9.99000008E-07
    int f = 897979745;
    // 0.000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2482) {
    // -9.99000008E-07
    int f = -1249503903;
    // -0.000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2483) {
    // 9.98999994E-08
    int f = 869697691;
    // 0.0000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2484) {
    // -9.98999994E-08
    int f = -1277785957;
    // -0.0000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2485) {
    // 9.98999994E-09
    int f = 841719932;
    // 0.00000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0xB0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2486) {
    // -9.98999994E-09
    int f = -1305763716;
    // -0.00000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x800B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2487) {
    // 9.98999994E-10
    int f = 814304560;
    // 0.000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0xC0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2488) {
    // -9.98999994E-10
    int f = -1333179088;
    // -0.000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x800C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2489) {
    // 9.9899998E-11
    int f = 786149043;
    // 0.0000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0xD0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2490) {
    // -9.9899998E-11
    int f = -1361334605;
    // -0.0000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x800D0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2491) {
    // 9.99000015E-12
    int f = 758103798;
    // 0.00000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0xE0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2492) {
    // -9.99000015E-12
    int f = -1389379850;
    // -0.00000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x800E0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2493) {
    // 9.99000036E-13
    int f = 730634437;
    // 0.000000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0xF0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2494) {
    // -9.99000036E-13
    int f = -1416849211;
    // -0.000000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x800F0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2495) {
    // 9.99000009E-14
    int f = 702608494;
    // 0.0000000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2496) {
    // -9.99000009E-14
    int f = -1444875154;
    // -0.0000000000000999
    s21_decimal decimal_check = {{0x3E7, 0x0, 0x0, 0x80100000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2497) {
    // 9.15344799E-15
    int f = 673506516;
    // 0.000000000000009153448
    s21_decimal decimal_check = {{0x8BABA8, 0x0, 0x0, 0x150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2498) {
    // -9.15344799E-15
    int f = -1473977132;
    // -0.000000000000009153448
    s21_decimal decimal_check = {{0x8BABA8, 0x0, 0x0, 0x80150000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2499) {
    // 1.15344831E-16
    int f = 621083593;
    // 0.0000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2500) {
    // -1.15344831E-16
    int f = -1526400055;
    // -0.0000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x80160000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2501) {
    // 1.15344827E-17
    int f = 592758286;
    // 0.00000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2502) {
    // -1.15344827E-17
    int f = -1554725362;
    // -0.00000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x80170000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2503) {
    // 1.15344825E-18
    int f = 564803595;
    // 0.000000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2504) {
    // -1.15344825E-18
    int f = -1582680053;
    // -0.000000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x80180000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2505) {
    // 1.62630326E-19
    int f = 541065216;
    // 0.0000000000000000001626303
    s21_decimal decimal_check = {{0x18D0BF, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2506) {
    // -1.62630326E-19
    int f = -1606418432;
    // -0.0000000000000000001626303
    s21_decimal decimal_check = {{0x18D0BF, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2507) {
    // 1.1534483E-19
    int f = 537406678;
    // 0.0000000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2508) {
    // -1.1534483E-19
    int f = -1610076970;
    // -0.0000000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x80190000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2509) {
    // 1.15344827E-20
    int f = 509206870;
    // 0.00000000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x1A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2510) {
    // -1.15344827E-20
    int f = -1638276778;
    // -0.00000000000000000001153448
    s21_decimal decimal_check = {{0x1199A8, 0x0, 0x0, 0x801A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2511) {
    // 7.15344824E-21
    int f = 503783412;
    // 0.000000000000000000007153448
    s21_decimal decimal_check = {{0x6D2728, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2512) {
    // -7.15344824E-21
    int f = -1643700236;
    // -0.000000000000000000007153448
    s21_decimal decimal_check = {{0x6D2728, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2513) {
    // 7.15344744E-21
    int f = 503783411;
    // 0.000000000000000000007153447
    s21_decimal decimal_check = {{0x6D2727, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2514) {
    // -7.15344744E-21
    int f = -1643700237;
    // -0.000000000000000000007153447
    s21_decimal decimal_check = {{0x6D2727, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2515) {
    // 7.53447488E-22
    int f = 476297005;
    // 0.0000000000000000000007534475
    s21_decimal decimal_check = {{0x72F78B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2516) {
    // -7.53447488E-22
    int f = -1671186643;
    // -0.0000000000000000000007534475
    s21_decimal decimal_check = {{0x72F78B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2517) {
    // 7.53447437E-22
    int f = 476297004;
    // 0.0000000000000000000007534474
    s21_decimal decimal_check = {{0x72F78A, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2518) {
    // -7.53447437E-22
    int f = -1671186644;
    // -0.0000000000000000000007534474
    s21_decimal decimal_check = {{0x72F78A, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2519) {
    // 7.54474521E-23
    int f = 448162742;
    // 0.0000000000000000000000754475
    s21_decimal decimal_check = {{0xB832B, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2520) {
    // -7.54474521E-23
    int f = -1699320906;
    // -0.0000000000000000000000754475
    s21_decimal decimal_check = {{0xB832B, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2521) {
    // 7.54474458E-23
    int f = 448162741;
    // 0.0000000000000000000000754474
    s21_decimal decimal_check = {{0xB832A, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2522) {
    // -7.54474458E-23
    int f = -1699320907;
    // -0.0000000000000000000000754474
    s21_decimal decimal_check = {{0xB832A, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2523) {
    // 9.54475074E-24
    int f = 423141201;
    // 0.0000000000000000000000095448
    s21_decimal decimal_check = {{0x174D8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2524) {
    // -9.54475074E-24
    int f = -1724342447;
    // -0.0000000000000000000000095448
    s21_decimal decimal_check = {{0x174D8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2525) {
    // 9.54474995E-24
    int f = 423141200;
    // 0.0000000000000000000000095447
    s21_decimal decimal_check = {{0x174D7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2526) {
    // -9.54474995E-24
    int f = -1724342448;
    // -0.0000000000000000000000095447
    s21_decimal decimal_check = {{0x174D7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2527) {
    // 5.44500023E-26
    int f = 361156554;
    // 0.0000000000000000000000000545
    s21_decimal decimal_check = {{0x221, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2528) {
    // -5.44500023E-26
    int f = -1786327094;
    // -0.0000000000000000000000000545
    s21_decimal decimal_check = {{0x221, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2529) {
    // 5.44499962E-26
    int f = 361156553;
    // 0.0000000000000000000000000544
    s21_decimal decimal_check = {{0x220, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2530) {
    // -5.44499962E-26
    int f = -1786327095;
    // -0.0000000000000000000000000544
    s21_decimal decimal_check = {{0x220, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2531) {
    // 1.44500012E-26
    int f = 344922907;
    // 0.0000000000000000000000000145
    s21_decimal decimal_check = {{0x91, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2532) {
    // -1.44500012E-26
    int f = -1802560741;
    // -0.0000000000000000000000000145
    s21_decimal decimal_check = {{0x91, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2533) {
    // 1.44499997E-26
    int f = 344922906;
    // 0.0000000000000000000000000144
    s21_decimal decimal_check = {{0x90, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2534) {
    // -1.44499997E-26
    int f = -1802560742;
    // -0.0000000000000000000000000144
    s21_decimal decimal_check = {{0x90, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2535) {
    // 1.50000004E-27
    int f = 317566779;
    // 0.0000000000000000000000000015
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2536) {
    // -1.50000004E-27
    int f = -1829916869;
    // -0.0000000000000000000000000015
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2537) {
    // 1.49999994E-27
    int f = 317566778;
    // 0.0000000000000000000000000015
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2538) {
    // -1.49999994E-27
    int f = -1829916870;
    // -0.0000000000000000000000000015
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2539) {
    // 1.45000001E-27
    int f = 317047549;
    // 0.0000000000000000000000000015
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2540) {
    // -1.45000001E-27
    int f = -1830436099;
    // -0.0000000000000000000000000015
    s21_decimal decimal_check = {{0xF, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2541) {
    // 1.44999991E-27
    int f = 317047548;
    // 0.0000000000000000000000000014
    s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2542) {
    // -1.44999991E-27
    int f = -1830436100;
    // -0.0000000000000000000000000014
    s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2543) {
    // 1.20000005E-27
    int f = 314451401;
    // 0.0000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2544) {
    // -1.20000005E-27
    int f = -1833032247;
    // -0.0000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2545) {
    // 1.19999996E-27
    int f = 314451400;
    // 0.0000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2546) {
    // -1.19999996E-27
    int f = -1833032248;
    // -0.0000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2547) {
    // 1.15000002E-27
    int f = 313932171;
    // 0.0000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2548) {
    // -1.15000002E-27
    int f = -1833551477;
    // -0.0000000000000000000000000012
    s21_decimal decimal_check = {{0xC, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2549) {
    // 1.14999993E-27
    int f = 313932170;
    // 0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2550) {
    // -1.14999993E-27
    int f = -1833551478;
    // -0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2551) {
    // 1.10000009E-27
    int f = 313412942;
    // 0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2552) {
    // -1.10000009E-27
    int f = -1834070706;
    // -0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2553) {
    // 1.09999999E-27
    int f = 313412941;
    // 0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2554) {
    // -1.09999999E-27
    int f = -1834070707;
    // -0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2555) {
    // 1.05000006E-27
    int f = 312893712;
    // 0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2556) {
    // -1.05000006E-27
    int f = -1834589936;
    // -0.0000000000000000000000000011
    s21_decimal decimal_check = {{0xB, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2557) {
    // 1.04999996E-27
    int f = 312893711;
    // 0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2558) {
    // -1.04999996E-27
    int f = -1834589937;
    // -0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2559) {
    // 1.00000003E-27
    int f = 312374482;
    // 0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2560) {
    // -1.00000003E-27
    int f = -1835109166;
    // -0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2561) {
    // 9.99999931E-28
    int f = 312374481;
    // 0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2562) {
    // -9.99999931E-28
    int f = -1835109167;
    // -0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2563) {
    // 9.50000093E-28
    int f = 311855253;
    // 0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2564) {
    // -9.50000093E-28
    int f = -1835628395;
    // -0.000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2565) {
    // 9.49999997E-28
    int f = 311855252;
    // 0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2566) {
    // -9.49999997E-28
    int f = -1835628396;
    // -0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2567) {
    // 9.00000063E-28
    int f = 311336023;
    // 0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2568) {
    // -9.00000063E-28
    int f = -1836147625;
    // -0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2569) {
    // 8.99999967E-28
    int f = 311336022;
    // 0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2570) {
    // -8.99999967E-28
    int f = -1836147626;
    // -0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2571) {
    // 8.50000033E-28
    int f = 310816793;
    // 0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2572) {
    // -8.50000033E-28
    int f = -1836666855;
    // -0.0000000000000000000000000009
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2573) {
    // 8.49999936E-28
    int f = 310816792;
    // 0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2574) {
    // -8.49999936E-28
    int f = -1836666856;
    // -0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2575) {
    // 8.00000003E-28
    int f = 310216630;
    // 0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2576) {
    // -8.00000003E-28
    int f = -1837267018;
    // -0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2577) {
    // 7.99999954E-28
    int f = 310216629;
    // 0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2578) {
    // -7.99999954E-28
    int f = -1837267019;
    // -0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2579) {
    // 7.5000002E-28
    int f = 309178171;
    // 0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2580) {
    // -7.5000002E-28
    int f = -1838305477;
    // -0.0000000000000000000000000008
    s21_decimal decimal_check = {{0x8, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2581) {
    // 7.49999972E-28
    int f = 309178170;
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2582) {
    // -7.49999972E-28
    int f = -1838305478;
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2583) {
    // 7.00000038E-28
    int f = 308139712;
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2584) {
    // -7.00000038E-28
    int f = -1839343936;
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2585) {
    // 6.9999999E-28
    int f = 308139711;
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2586) {
    // -6.9999999E-28
    int f = -1839343937;
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2587) {
    // 6.50000008E-28
    int f = 307101252;
    // 0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2588) {
    // -6.50000008E-28
    int f = -1840382396;
    // -0.0000000000000000000000000007
    s21_decimal decimal_check = {{0x7, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2589) {
    // 6.4999996E-28
    int f = 307101251;
    // 0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2590) {
    // -6.4999996E-28
    int f = -1840382397;
    // -0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2591) {
    // 6.00000026E-28
    int f = 306062793;
    // 0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2592) {
    // -6.00000026E-28
    int f = -1841420855;
    // -0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2593) {
    // 5.99999978E-28
    int f = 306062792;
    // 0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2594) {
    // -5.99999978E-28
    int f = -1841420856;
    // -0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2595) {
    // 5.50000044E-28
    int f = 305024334;
    // 0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2596) {
    // -5.50000044E-28
    int f = -1842459314;
    // -0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2597) {
    // 5.49999996E-28
    int f = 305024333;
    // 0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2598) {
    // -5.49999996E-28
    int f = -1842459315;
    // -0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2599) {
    // 5.00000014E-28
    int f = 303985874;
    // 0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2600) {
    // -5.00000014E-28
    int f = -1843497774;
    // -0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2601) {
    // 4.99999965E-28
    int f = 303985873;
    // 0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2602) {
    // -4.99999965E-28
    int f = -1843497775;
    // -0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2603) {
    // 4.50000032E-28
    int f = 302947415;
    // 0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2604) {
    // -4.50000032E-28
    int f = -1844536233;
    // -0.0000000000000000000000000005
    s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2605) {
    // 4.49999983E-28
    int f = 302947414;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2606) {
    // -4.49999983E-28
    int f = -1844536234;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2607) {
    // 4.00000001E-28
    int f = 301828022;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2608) {
    // -4.00000001E-28
    int f = -1845655626;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2609) {
    // 3.99999977E-28
    int f = 301828021;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2610) {
    // -3.99999977E-28
    int f = -1845655627;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2611) {
    // 3.50000043E-28
    int f = 299751105;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2612) {
    // -3.50000043E-28
    int f = -1847732543;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2613) {
    // 3.50000019E-28
    int f = 299751104;
    // 0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2614) {
    // -3.50000019E-28
    int f = -1847732544;
    // -0.0000000000000000000000000004
    s21_decimal decimal_check = {{0x4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2615) {
    // 3.49999995E-28
    int f = 299751103;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2616) {
    // -3.49999995E-28
    int f = -1847732545;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2617) {
    // 3.49999971E-28
    int f = 299751102;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2618) {
    // -3.49999971E-28
    int f = -1847732546;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2619) {
    // 3.00000013E-28
    int f = 297674185;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2620) {
    // -3.00000013E-28
    int f = -1849809463;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2621) {
    // 2.99999989E-28
    int f = 297674184;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2622) {
    // -2.99999989E-28
    int f = -1849809464;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2623) {
    // 2.99999965E-28
    int f = 297674183;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2624) {
    // -2.99999965E-28
    int f = -1849809465;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2625) {
    // 2.50000031E-28
    int f = 295597267;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2626) {
    // -2.50000031E-28
    int f = -1851886381;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2627) {
    // 2.50000007E-28
    int f = 295597266;
    // 0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2628) {
    // -2.50000007E-28
    int f = -1851886382;
    // -0.0000000000000000000000000003
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2629) {
    // 2.49999983E-28
    int f = 295597265;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2630) {
    // -2.49999983E-28
    int f = -1851886383;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2631) {
    // 2.00000013E-28
    int f = 293439415;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2632) {
    // -2.00000013E-28
    int f = -1854044233;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2633) {
    // 2.00000001E-28
    int f = 293439414;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2634) {
    // -2.00000001E-28
    int f = -1854044234;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2635) {
    // 1.99999989E-28
    int f = 293439413;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2636) {
    // -1.99999989E-28
    int f = -1854044235;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2637) {
    // 1.50000019E-28
    int f = 289285578;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2638) {
    // -1.50000019E-28
    int f = -1858198070;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2639) {
    // 1.50000006E-28
    int f = 289285577;
    // 0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2640) {
    // -1.50000006E-28
    int f = -1858198071;
    // -0.0000000000000000000000000002
    s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2641) {
    // 1.49999994E-28
    int f = 289285576;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2642) {
    // -1.49999994E-28
    int f = -1858198072;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2643) {
    // 1.49999814E-28
    int f = 289285561;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2644) {
    // -1.49999814E-28
    int f = -1858198087;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2645) {
    // 1.00000018E-28
    int f = 285050809;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2646) {
    // -1.00000018E-28
    int f = -1862432839;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2647) {
    // 1.00000012E-28
    int f = 285050808;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2648) {
    // -1.00000012E-28
    int f = -1862432840;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2649) {
    // 1.00000006E-28
    int f = 285050807;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2650) {
    // -1.00000006E-28
    int f = -1862432841;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2651) {
    // 1E-28
    int f = 285050806;
    // 0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2652) {
    // -1E-28
    int f = -1862432842;
    // -0.0000000000000000000000000001
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2653) {
    // 10000005
    int f = 1259902597;
    // 10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2654) {
    // -10000005
    int f = -887581051;
    // -10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2655) {
    // 10000002
    int f = 1259902594;
    // 10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2656) {
    // -10000002
    int f = -887581054;
    // -10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2657) {
    // 10000001
    int f = 1259902593;
    // 10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2658) {
    // -10000001
    int f = -887581055;
    // -10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2659) {
    // 10000000
    int f = 1259902592;
    // 10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2660) {
    // -10000000
    int f = -887581056;
    // -10000000
    s21_decimal decimal_check = {{0x989680, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2661) {
    // 9999999
    int f = 1259902591;
    // 9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2662) {
    // -9999999
    int f = -887581057;
    // -9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2663) {
    // 9999998
    int f = 1259902590;
    // 9999998
    s21_decimal decimal_check = {{0x98967E, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2664) {
    // -9999998
    int f = -887581058;
    // -9999998
    s21_decimal decimal_check = {{0x98967E, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2665) {
    // 1000001.56
    int f = 1232348185;
    // 1000002
    s21_decimal decimal_check = {{0xF4242, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2666) {
    // -1000001.56
    int f = -915135463;
    // -1000002
    s21_decimal decimal_check = {{0xF4242, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2667) {
    // 1000001.5
    int f = 1232348184;
    // 1000002
    s21_decimal decimal_check = {{0xF4242, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2668) {
    // -1000001.5
    int f = -915135464;
    // -1000002
    s21_decimal decimal_check = {{0xF4242, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2669) {
    // 1000001.44
    int f = 1232348183;
    // 1000001
    s21_decimal decimal_check = {{0xF4241, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2670) {
    // -1000001.44
    int f = -915135465;
    // -1000001
    s21_decimal decimal_check = {{0xF4241, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2671) {
    // 1000000.56
    int f = 1232348169;
    // 1000001
    s21_decimal decimal_check = {{0xF4241, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2672) {
    // -1000000.56
    int f = -915135479;
    // -1000001
    s21_decimal decimal_check = {{0xF4241, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2673) {
    // 1000000.5
    int f = 1232348168;
    // 1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2674) {
    // -1000000.5
    int f = -915135480;
    // -1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2675) {
    // 1000000.44
    int f = 1232348167;
    // 1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2676) {
    // -1000000.44
    int f = -915135481;
    // -1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2677) {
    // 1000000.06
    int f = 1232348161;
    // 1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2678) {
    // -1000000.06
    int f = -915135487;
    // -1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2679) {
    // 1000000
    int f = 1232348160;
    // 1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2680) {
    // -1000000
    int f = -915135488;
    // -1000000
    s21_decimal decimal_check = {{0xF4240, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2681) {
    // 999999.938
    int f = 1232348159;
    // 999999.9
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2682) {
    // -999999.938
    int f = -915135489;
    // -999999.9
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2683) {
    // 999999.5
    int f = 1232348152;
    // 999999.5
    s21_decimal decimal_check = {{0x98967B, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2684) {
    // -999999.5
    int f = -915135496;
    // -999999.5
    s21_decimal decimal_check = {{0x98967B, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2685) {
    // 999999.438
    int f = 1232348151;
    // 999999.4
    s21_decimal decimal_check = {{0x98967A, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2686) {
    // -999999.438
    int f = -915135497;
    // -999999.4
    s21_decimal decimal_check = {{0x98967A, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2687) {
    // 999998.563
    int f = 1232348137;
    // 999998.6
    s21_decimal decimal_check = {{0x989672, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2688) {
    // -999998.563
    int f = -915135511;
    // -999998.6
    s21_decimal decimal_check = {{0x989672, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2689) {
    // 999998.5
    int f = 1232348136;
    // 999998.5
    s21_decimal decimal_check = {{0x989671, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2690) {
    // -999998.5
    int f = -915135512;
    // -999998.5
    s21_decimal decimal_check = {{0x989671, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2691) {
    // 999998.438
    int f = 1232348135;
    // 999998.4
    s21_decimal decimal_check = {{0x989670, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2692) {
    // -999998.438
    int f = -915135513;
    // -999998.4
    s21_decimal decimal_check = {{0x989670, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2693) {
    // 2.57396453E-21
    int f = 490896311;
    // 0.000000000000000000002573965
    s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2694) {
    // -2.57396453E-21
    int f = -1656587337;
    // -0.000000000000000000002573965
    s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2695) {
    // 2.57396453E-21
    int f = 490896311;
    // 0.000000000000000000002573965
    s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x1B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2696) {
    // -2.57396453E-21
    int f = -1656587337;
    // -0.000000000000000000002573965
    s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x801B0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2697) {
    // 2.5739646
    int f = 1076149206;
    // 2.573965
    s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2698) {
    // -2.5739646
    int f = -1071334442;
    // -2.573965
    s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2699) {
    // 0.001953125
    int f = 989855744;
    // 0.001953125
    s21_decimal decimal_check = {{0x1DCD65, 0x0, 0x0, 0x90000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2700) {
    // -0.001953125
    int f = -1157627904;
    // -0.001953125
    s21_decimal decimal_check = {{0x1DCD65, 0x0, 0x0, 0x80090000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2701) {
    // 15555555
    int f = 1265458147;
    // 15555560
    s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2702) {
    // -15555555
    int f = -882025501;
    // -15555560
    s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2703) {
    // 15555565
    int f = 1265458157;
    // 15555560
    s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2704) {
    // -15555565
    int f = -882025491;
    // -15555560
    s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2705) {
    // 3901384.5
    int f = 1248730914;
    // 3901384
    s21_decimal decimal_check = {{0x3B87C8, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2706) {
    // -3901384.5
    int f = -898752734;
    // -3901384
    s21_decimal decimal_check = {{0x3B87C8, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2707) {
    // 3901385.5
    int f = 1248730918;
    // 3901386
    s21_decimal decimal_check = {{0x3B87CA, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2708) {
    // -3901385.5
    int f = -898752730;
    // -3901386
    s21_decimal decimal_check = {{0x3B87CA, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2709) {
    // 0.792281568
    int f = 1061868279;
    // 0.7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2710) {
    // -0.792281568
    int f = -1085615369;
    // -0.7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2711) {
    // 0.792281628
    int f = 1061868280;
    // 0.7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2712) {
    // -0.792281628
    int f = -1085615368;
    // -0.7922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2713) {
    // 0.792281687
    int f = 1061868281;
    // 0.7922817
    s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2714) {
    // -0.792281687
    int f = -1085615367;
    // -0.7922817
    s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2715) {
    // 7.9228158
    int f = 1090357173;
    // 7.922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2716) {
    // -7.9228158
    int f = -1057126475;
    // -7.922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2717) {
    // 7.92281628
    int f = 1090357174;
    // 7.922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2718) {
    // -7.92281628
    int f = -1057126474;
    // -7.922816
    s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2719) {
    // 7.92281675
    int f = 1090357175;
    // 7.922817
    s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x60000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2720) {
    // -7.92281675
    int f = -1057126473;
    // -7.922817
    s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x80060000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2721) {
    // 0.00048828125
    int f = 973078528;
    // 0.0004882812
    s21_decimal decimal_check = {{0x4A817C, 0x0, 0x0, 0xA0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2722) {
    // -0.00048828125
    int f = -1174405120;
    // -0.0004882812
    s21_decimal decimal_check = {{0x4A817C, 0x0, 0x0, 0x800A0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2723) {
    // 5.55555671E-23
    int f = 445010747;
    // 0.0000000000000000000000555556
    s21_decimal decimal_check = {{0x87A24, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2724) {
    // -5.55555671E-23
    int f = -1702472901;
    // -0.0000000000000000000000555556
    s21_decimal decimal_check = {{0x87A24, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2725) {
    // 5.55555684E-22
    int f = 472377354;
    // 0.0000000000000000000005555557
    s21_decimal decimal_check = {{0x54C565, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2726) {
    // -5.55555684E-22
    int f = -1675106294;
    // -0.0000000000000000000005555557
    s21_decimal decimal_check = {{0x54C565, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2727) {
    // 5.55555687E-24
    int f = 416738194;
    // 0.0000000000000000000000055556
    s21_decimal decimal_check = {{0xD904, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2728) {
    // -5.55555687E-24
    int f = -1730745454;
    // -0.0000000000000000000000055556
    s21_decimal decimal_check = {{0xD904, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2729) {
    // 5.55555687E-25
    int f = 388755368;
    // 0.0000000000000000000000005556
    s21_decimal decimal_check = {{0x15B4, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2730) {
    // -5.55555687E-25
    int f = -1758728280;
    // -0.0000000000000000000000005556
    s21_decimal decimal_check = {{0x15B4, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2731) {
    // 5.55555662E-26
    int f = 361335942;
    // 0.0000000000000000000000000556
    s21_decimal decimal_check = {{0x22C, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2732) {
    // -5.55555662E-26
    int f = -1786147706;
    // -0.0000000000000000000000000556
    s21_decimal decimal_check = {{0x22C, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2733) {
    // 5.55555678E-27
    int f = 333190154;
    // 0.0000000000000000000000000056
    s21_decimal decimal_check = {{0x38, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2734) {
    // -5.55555678E-27
    int f = -1814293494;
    // -0.0000000000000000000000000056
    s21_decimal decimal_check = {{0x38, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2735) {
    // 5.55555678E-28
    int f = 305139720;
    // 0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2736) {
    // -5.55555678E-28
    int f = -1842343928;
    // -0.0000000000000000000000000006
    s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2737) {
    // 0.0299999993
    int f = 1022739087;
    // 0.03
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x20000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2738) {
    // -0.0299999993
    int f = -1124744561;
    // -0.03
    s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80020000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2739) {
    // 0.100000001
    int f = 1036831949;
    // 0.1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2740) {
    // -0.100000001
    int f = -1110651699;
    // -0.1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2741) {
    // 0.899999976
    int f = 1063675494;
    // 0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x10000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2742) {
    // -0.899999976
    int f = -1083808154;
    // -0.9
    s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80010000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2743) {
    // 0.99999994
    int f = 1065353215;
    // 0.9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x70000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2744) {
    // -0.99999994
    int f = -1082130433;
    // -0.9999999
    s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80070000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2745) {
    // 1
    int f = 1065353216;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2746) {
    // -1
    int f = -1082130432;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2747) {
    // 1.00000012
    int f = 1065353217;
    // 1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

    test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2748) {
    // -1.00000012
    int f = -1082130431;
    // -1
    s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

    test_from_float_to_decimal(f, decimal_check);
}


Suite *from_float_to_decimal_suite1(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite1");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok3);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok4);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok5);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok6);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok7);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok8);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok9);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok10);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok11);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok12);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok13);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok14);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok15);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok16);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok17);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok18);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok19);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok20);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok21);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok22);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok23);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok24);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok25);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok26);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok27);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok28);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok29);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok30);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok31);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok32);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok33);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok34);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok35);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok36);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok37);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok38);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok39);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok40);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok41);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok42);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok43);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok44);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok45);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok46);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok47);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok48);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok49);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok50);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok51);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok52);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok53);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok54);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok55);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok56);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok57);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok58);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok59);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok60);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok61);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok62);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok63);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok64);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok65);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok66);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok67);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok68);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok69);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok70);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok71);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok72);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok73);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok74);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok75);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok76);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok77);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok78);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok79);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok80);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok81);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok82);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok83);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok84);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok85);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok86);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok87);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok88);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok89);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok90);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok91);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok92);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok93);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok94);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok95);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok96);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok97);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok98);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok99);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok100);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok101);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok102);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok103);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok104);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok105);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok106);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok107);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok108);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok109);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok110);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok111);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok112);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok113);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok114);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok115);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok116);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok117);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok118);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok119);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok120);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok121);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok122);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok123);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok124);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok125);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok126);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok127);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok128);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok129);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok130);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok131);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok132);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok133);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok134);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok135);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok136);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok137);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok138);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok139);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok140);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok141);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok142);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok143);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok144);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok145);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok146);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok147);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok148);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok149);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok150);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok151);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok152);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok153);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok154);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok155);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok156);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok157);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok158);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok159);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok160);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok161);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok162);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok163);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok164);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok165);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok166);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok167);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok168);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok169);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok170);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok171);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok172);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok173);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok174);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok175);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok176);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok177);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok178);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok179);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok180);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok181);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok182);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok183);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok184);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok185);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok186);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok187);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok188);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok189);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok190);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok191);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok192);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok193);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok194);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok195);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok196);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok197);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok198);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok199);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok200);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok201);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok202);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok203);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok204);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok205);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok206);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok207);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok208);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok209);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok210);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok211);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok212);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok213);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok214);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok215);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok216);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok217);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok218);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok219);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok220);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok221);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok222);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok223);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok224);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok225);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok226);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok227);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok228);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok229);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok230);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok231);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok232);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok233);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok234);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok235);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok236);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok237);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok238);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok239);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok240);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok241);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok242);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok243);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok244);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok245);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok246);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok247);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok248);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok249);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok250);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok251);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok252);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok253);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok254);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok255);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok256);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok257);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok258);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok259);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok260);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok261);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok262);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok263);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok264);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok265);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok266);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok267);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok268);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok269);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok270);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok271);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok272);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok273);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok274);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok275);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok276);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok277);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok278);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok279);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok280);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok281);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok282);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok283);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok284);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok285);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok286);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok287);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok288);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok289);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok290);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok291);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok292);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok293);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok294);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok295);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok296);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok297);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok298);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok299);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok300);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok301);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok302);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok303);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok304);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok305);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok306);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok307);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok308);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok309);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok310);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok311);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok312);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok313);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok314);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok315);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok316);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok317);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok318);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok319);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok320);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok321);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok322);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok323);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok324);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok325);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok326);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok327);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok328);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok329);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok330);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok331);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok332);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok333);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok334);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok335);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok336);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok337);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok338);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok339);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok340);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok341);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok342);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok343);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok344);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok345);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok346);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok347);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok348);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok349);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok350);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok351);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok352);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok353);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok354);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok355);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok356);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok357);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok358);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok359);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok360);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok361);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok362);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok363);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok364);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok365);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok366);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok367);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok368);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok369);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok370);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok371);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok372);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok373);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok374);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok375);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok376);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok377);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok378);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok379);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok380);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok381);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok382);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok383);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok384);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok385);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok386);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok387);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok388);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok389);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok390);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok391);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok392);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok393);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok394);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok395);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok396);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok397);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok398);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok399);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite2(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite2");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok401);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok402);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok403);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok404);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok405);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok406);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok407);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok408);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok409);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok410);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok411);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok412);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok413);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok414);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok415);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok416);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok417);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok418);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok419);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok420);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok421);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok422);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok423);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok424);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok425);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok426);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok427);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok428);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok429);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok430);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok431);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok432);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok433);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok434);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok435);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok436);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok437);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok438);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok439);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok440);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok441);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok442);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok443);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok444);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok445);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok446);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok447);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok448);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok449);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok450);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok451);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok452);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok453);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok454);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok455);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok456);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok457);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok458);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok459);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok460);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok461);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok462);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok463);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok464);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok465);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok466);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok467);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok468);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok469);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok470);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok471);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok472);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok473);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok474);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok475);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok476);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok477);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok478);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok479);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok480);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok481);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok482);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok483);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok484);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok485);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok486);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok487);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok488);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok489);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok490);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok491);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok492);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok493);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok494);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok495);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok496);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok497);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok498);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok499);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok500);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok501);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok502);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok503);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok504);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok505);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok506);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok507);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok508);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok509);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok510);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok511);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok512);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok513);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok514);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok515);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok516);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok517);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok518);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok519);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok520);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok521);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok522);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok523);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok524);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok525);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok526);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok527);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok528);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok529);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok530);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok531);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok532);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok533);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok534);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok535);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok536);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok537);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok538);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok539);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok540);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok541);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok542);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok543);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok544);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok545);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok546);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok547);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok548);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok549);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok550);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok551);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok552);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok553);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok554);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok555);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok556);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok557);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok558);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok559);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok560);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok561);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok562);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok563);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok564);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok565);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok566);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok567);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok568);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok569);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok570);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok571);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok572);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok573);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok574);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok575);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok576);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok577);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok578);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok579);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok580);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok581);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok582);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok583);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok584);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok585);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok586);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok587);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok588);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok589);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok590);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok591);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok592);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok593);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok594);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok595);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok596);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok597);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok598);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok599);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok600);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok601);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok602);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok603);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok604);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok605);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok606);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok607);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok608);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok609);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok610);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok611);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok612);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok613);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok614);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok615);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok616);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok617);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok618);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok619);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok620);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok621);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok622);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok623);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok624);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok625);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok626);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok627);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok628);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok629);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok630);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok631);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok632);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok633);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok634);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok635);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok636);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok637);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok638);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok639);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok640);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok641);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok642);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok643);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok644);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok645);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok646);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok647);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok648);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok649);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok650);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok651);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok652);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok653);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok654);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok655);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok656);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok657);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok658);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok659);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok660);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok661);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok662);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok663);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok664);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok665);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok666);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok667);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok668);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok669);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok670);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok671);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok672);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok673);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok674);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok675);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok676);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok677);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok678);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok679);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok680);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok681);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok682);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok683);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok684);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok685);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok686);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok687);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok688);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok689);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok690);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok691);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok692);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok693);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok694);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok695);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok696);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok697);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok698);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok699);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok700);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok701);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok702);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok703);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok704);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok705);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok706);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok707);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok708);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok709);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok710);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok711);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok712);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok713);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok714);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok715);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok716);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok717);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok718);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok719);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok720);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok721);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok722);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok723);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok724);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok725);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok726);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok727);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok728);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok729);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok730);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok731);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok732);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok733);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok734);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok735);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok736);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok737);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok738);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok739);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok740);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok741);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok742);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok743);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok744);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok745);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok746);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok747);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok748);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok749);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok750);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok751);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok752);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok753);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok754);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok755);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok756);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok757);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok758);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok759);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok760);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok761);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok762);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok763);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok764);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok765);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok766);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok767);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok768);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok769);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok770);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok771);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok772);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok773);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok774);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok775);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok776);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok777);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok778);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok779);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok780);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok781);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok782);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok783);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok784);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok785);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok786);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok787);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok788);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok789);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok790);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok791);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok792);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok793);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok794);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok795);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok796);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok797);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok798);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok799);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok800);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite3(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite3");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok801);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok802);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok803);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok804);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok805);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok806);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok807);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok808);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok809);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok810);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok811);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok812);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok813);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok814);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok815);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok816);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok817);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok818);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok819);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok820);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok821);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok822);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok823);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok824);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok825);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok826);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok827);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok828);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok829);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok830);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok831);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok832);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok833);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok834);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok835);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok836);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok837);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok838);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok839);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok840);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok841);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok842);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok843);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok844);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok845);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok846);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok847);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok848);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok849);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok850);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok851);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok852);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok853);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok854);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok855);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok856);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok857);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok858);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok859);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok860);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok861);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok862);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok863);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok864);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok865);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok866);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok867);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok868);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok869);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok870);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok871);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok872);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok873);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok874);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok875);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok876);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok877);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok878);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok879);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok880);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok881);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok882);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok883);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok884);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok885);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok886);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok887);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok888);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok889);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok890);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok891);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok892);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok893);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok894);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok895);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok896);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok897);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok898);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok899);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok900);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok901);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok902);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok903);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok904);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok905);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok906);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok907);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok908);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok909);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok910);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok911);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok912);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok913);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok914);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok915);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok916);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok917);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok918);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok919);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok920);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok921);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok922);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok923);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok924);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok925);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok926);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok927);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok928);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok929);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok930);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok931);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok932);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok933);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok934);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok935);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok936);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok937);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok938);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok939);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok940);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok941);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok942);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok943);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok944);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok945);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok946);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok947);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok948);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok949);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok950);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok951);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok952);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok953);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok954);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok955);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok956);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok957);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok958);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok959);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok960);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok961);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok962);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok963);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok964);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok965);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok966);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok967);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok968);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok969);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok970);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok971);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok972);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok973);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok974);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok975);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok976);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok977);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok978);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok979);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok980);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok981);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok982);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok983);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok984);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok985);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok986);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok987);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok988);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok989);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok990);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok991);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok992);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok993);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok994);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok995);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok996);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok997);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok998);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok999);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1000);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1001);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1002);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1003);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1004);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1005);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1006);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1007);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1008);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1009);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1010);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1011);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1012);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1013);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1014);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1015);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1016);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1017);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1018);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1019);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1020);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1021);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1022);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1023);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1024);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1025);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1026);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1027);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1028);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1029);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1030);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1031);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1032);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1033);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1034);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1035);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1036);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1037);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1038);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1039);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1040);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1041);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1042);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1043);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1044);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1045);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1046);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1047);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1048);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1049);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1050);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1051);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1052);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1053);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1054);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1055);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1056);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1057);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1058);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1059);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1060);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1061);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1062);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1063);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1064);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1065);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1066);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1067);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1068);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1069);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1070);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1071);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1072);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1073);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1074);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1075);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1076);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1077);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1078);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1079);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1080);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1081);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1082);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1083);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1084);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1085);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1086);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1087);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1088);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1089);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1090);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1091);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1092);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1093);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1094);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1095);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1096);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1097);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1098);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1099);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1100);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1101);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1102);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1103);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1104);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1105);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1106);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1107);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1108);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1109);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1110);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1111);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1112);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1113);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1114);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1115);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1116);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1117);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1118);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1119);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1120);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1121);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1122);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1123);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1124);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1125);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1126);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1127);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1128);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1129);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1130);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1131);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1132);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1133);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1134);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1135);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1136);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1137);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1138);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1139);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1140);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1141);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1142);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1143);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1144);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1145);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1146);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1147);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1148);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1149);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1150);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1151);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1152);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1153);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1154);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1155);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1156);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1157);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1158);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1159);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1160);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1161);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1162);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1163);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1164);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1165);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1166);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1167);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1168);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1169);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1170);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1171);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1172);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1173);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1174);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1175);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1176);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1177);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1178);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1179);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1180);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1181);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1182);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1183);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1184);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1185);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1186);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1187);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1188);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1189);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1190);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1191);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1192);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1193);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1194);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1195);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1196);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1197);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1198);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1199);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1200);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite4(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite4");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1201);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1202);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1203);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1204);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1205);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1206);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1207);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1208);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1209);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1210);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1211);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1212);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1213);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1214);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1215);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1216);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1217);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1218);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1219);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1220);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1221);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1222);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1223);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1224);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1225);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1226);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1227);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1228);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1229);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1230);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1231);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1232);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1233);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1234);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1235);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1236);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1237);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1238);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1239);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1240);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1241);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1242);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1243);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1244);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1245);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1246);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1247);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1248);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1249);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1250);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1251);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1252);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1253);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1254);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1255);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1256);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1257);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1258);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1259);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1260);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1261);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1262);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1263);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1264);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1265);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1266);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1267);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1268);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1269);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1270);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1271);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1272);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1273);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1274);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1275);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1276);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1277);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1278);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1279);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1280);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1281);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1282);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1283);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1284);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1285);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1286);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1287);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1288);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1289);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1290);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1291);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1292);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1293);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1294);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1295);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1296);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1297);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1298);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1299);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1300);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1301);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1302);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1303);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1304);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1305);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1306);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1307);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1308);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1309);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1310);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1311);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1312);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1313);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1314);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1315);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1316);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1317);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1318);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1319);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1320);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1321);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1322);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1323);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1324);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1325);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1326);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1327);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1328);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1329);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1330);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1331);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1332);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1333);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1334);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1335);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1336);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1337);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1338);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1339);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1340);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1341);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1342);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1343);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1344);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1345);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1346);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1347);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1348);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1349);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1350);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1351);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1352);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1353);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1354);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1355);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1356);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1357);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1358);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1359);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1360);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1361);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1362);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1363);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1364);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1365);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1366);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1367);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1368);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1369);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1370);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1371);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1372);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1373);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1374);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1375);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1376);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1377);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1378);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1379);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1380);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1381);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1382);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1383);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1384);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1385);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1386);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1387);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1388);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1389);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1390);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1391);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1392);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1393);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1394);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1395);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1396);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1397);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1398);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1399);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1400);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1401);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1402);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1403);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1404);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1405);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1406);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1407);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1408);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1409);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1410);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1411);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1412);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1413);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1414);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1415);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1416);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1417);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1418);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1419);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1420);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1421);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1422);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1423);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1424);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1425);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1426);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1427);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1428);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1429);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1430);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1431);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1432);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1433);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1434);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1435);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1436);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1437);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1438);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1439);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1440);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1441);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1442);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1443);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1444);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1445);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1446);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1447);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1448);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1449);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1450);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1451);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1452);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1453);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1454);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1455);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1456);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1457);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1458);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1459);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1460);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1461);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1462);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1463);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1464);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1465);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1466);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1467);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1468);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1469);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1470);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1471);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1472);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1473);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1474);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1475);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1476);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1477);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1478);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1479);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1480);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1481);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1482);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1483);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1484);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1485);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1486);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1487);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1488);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1489);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1490);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1491);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1492);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1493);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1494);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1495);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1496);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1497);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1498);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1499);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1500);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1501);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1502);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1503);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1504);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1505);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1506);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1507);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1508);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1509);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1510);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1511);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1512);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1513);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1514);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1515);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1516);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1517);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1518);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1519);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1520);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1521);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1522);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1523);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1524);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1525);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1526);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1527);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1528);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1529);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1530);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1531);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1532);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1533);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1534);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1535);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1536);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1537);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1538);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1539);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1540);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1541);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1542);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1543);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1544);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1545);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1546);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1547);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1548);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1549);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1550);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1551);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1552);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1553);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1554);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1555);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1556);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1557);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1558);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1559);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1560);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1561);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1562);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1563);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1564);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1565);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1566);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1567);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1568);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1569);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1570);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1571);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1572);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1573);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1574);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1575);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1576);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1577);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1578);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1579);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1580);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1581);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1582);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1583);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1584);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1585);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1586);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1587);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1588);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1589);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1590);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1591);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1592);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1593);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1594);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1595);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1596);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1597);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1598);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1599);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1600);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite5(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite5");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1601);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1602);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1603);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1604);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1605);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1606);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1607);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1608);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1609);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1610);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1611);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1612);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1613);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1614);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1615);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1616);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1617);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1618);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1619);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1620);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1621);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1622);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1623);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1624);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1625);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1626);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1627);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1628);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1629);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1630);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1631);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1632);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1633);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1634);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1635);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1636);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1637);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1638);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1639);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1640);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1641);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1642);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1643);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1644);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1645);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1646);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1647);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1648);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1649);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1650);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1651);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1652);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1653);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1654);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1655);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1656);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1657);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1658);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1659);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1660);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1661);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1662);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1663);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1664);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1665);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1666);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1667);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1668);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1669);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1670);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1671);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1672);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1673);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1674);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1675);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1676);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1677);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1678);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1679);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1680);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1681);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1682);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1683);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1684);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1685);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1686);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1687);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1688);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1689);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1690);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1691);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1692);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1693);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1694);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1695);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1696);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1697);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1698);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1699);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1700);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1701);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1702);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1703);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1704);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1705);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1706);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1707);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1708);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1709);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1710);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1711);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1712);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1713);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1714);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1715);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1716);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1717);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1718);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1719);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1720);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1721);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1722);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1723);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1724);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1725);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1726);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1727);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1728);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1729);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1730);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1731);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1732);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1733);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1734);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1735);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1736);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1737);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1738);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1739);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1740);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1741);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1742);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1743);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1744);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1745);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1746);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1747);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1748);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1749);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1750);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1751);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1752);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1753);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1754);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1755);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1756);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1757);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1758);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1759);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1760);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1761);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1762);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1763);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1764);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1765);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1766);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1767);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1768);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1769);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1770);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1771);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1772);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1773);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1774);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1775);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1776);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1777);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1778);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1779);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1780);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1781);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1782);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1783);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1784);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1785);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1786);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1787);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1788);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1789);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1790);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1791);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1792);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1793);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1794);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1795);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1796);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1797);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1798);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1799);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1800);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1801);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1802);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1803);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1804);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1805);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1806);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1807);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1808);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1809);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1810);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1811);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1812);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1813);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1814);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1815);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1816);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1817);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1818);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1819);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1820);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1821);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1822);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1823);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1824);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1825);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1826);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1827);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1828);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1829);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1830);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1831);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1832);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1833);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1834);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1835);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1836);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1837);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1838);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1839);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1840);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1841);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1842);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1843);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1844);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1845);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1846);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1847);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1848);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1849);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1850);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1851);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1852);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1853);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1854);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1855);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1856);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1857);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1858);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1859);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1860);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1861);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1862);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1863);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1864);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1865);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1866);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1867);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1868);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1869);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1870);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1871);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1872);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1873);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1874);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1875);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1876);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1877);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1878);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1879);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1880);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1881);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1882);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1883);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1884);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1885);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1886);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1887);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1888);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1889);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1890);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1891);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1892);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1893);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1894);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1895);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1896);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1897);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1898);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1899);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1900);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1901);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1902);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1903);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1904);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1905);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1906);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1907);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1908);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1909);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1910);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1911);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1912);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1913);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1914);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1915);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1916);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1917);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1918);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1919);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1920);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1921);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1922);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1923);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1924);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1925);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1926);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1927);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1928);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1929);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1930);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1931);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1932);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1933);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1934);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1935);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1936);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1937);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1938);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1939);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1940);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1941);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1942);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1943);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1944);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1945);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1946);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1947);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1948);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1949);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1950);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1951);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1952);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1953);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1954);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1955);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1956);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1957);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1958);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1959);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1960);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1961);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1962);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1963);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1964);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1965);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1966);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1967);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1968);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1969);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1970);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1971);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1972);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1973);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1974);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1975);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1976);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1977);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1978);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1979);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1980);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1981);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1982);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1983);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1984);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1985);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1986);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1987);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1988);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1989);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1990);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1991);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1992);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1993);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1994);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1995);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1996);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1997);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1998);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok1999);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2000);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite6(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite6");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2001);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2002);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2003);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2004);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2005);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2006);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2007);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2008);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2009);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2010);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2011);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2012);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2013);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2014);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2015);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2016);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2017);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2018);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2019);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2020);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2021);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2022);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2023);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2024);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2025);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2026);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2027);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2028);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2029);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2030);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2031);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2032);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2033);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2034);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2035);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2036);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2037);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2038);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2039);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2040);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2041);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2042);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2043);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2044);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2045);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2046);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2047);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2048);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2049);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2050);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2051);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2052);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2053);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2054);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2055);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2056);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2057);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2058);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2059);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2060);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2061);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2062);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2063);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2064);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2065);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2066);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2067);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2068);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2069);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2070);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2071);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2072);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2073);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2074);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2075);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2076);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2077);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2078);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2079);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2080);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2081);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2082);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2083);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2084);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2085);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2086);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2087);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2088);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2089);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2090);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2091);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2092);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2093);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2094);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2095);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2096);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2097);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2098);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2099);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2100);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2101);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2102);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2103);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2104);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2105);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2106);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2107);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2108);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2109);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2110);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2111);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2112);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2113);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2114);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2115);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2116);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2117);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2118);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2119);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2120);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2121);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2122);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2123);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2124);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2125);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2126);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2127);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2128);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2129);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2130);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2131);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2132);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2133);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2134);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2135);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2136);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2137);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2138);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2139);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2140);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2141);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2142);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2143);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2144);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2145);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2146);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2147);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2148);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2149);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2150);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2151);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2152);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2153);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2154);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2155);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2156);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2157);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2158);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2159);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2160);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2161);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2162);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2163);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2164);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2165);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2166);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2167);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2168);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2169);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2170);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2171);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2172);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2173);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2174);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2175);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2176);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2177);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2178);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2179);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2180);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2181);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2182);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2183);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2184);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2185);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2186);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2187);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2188);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2189);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2190);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2191);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2192);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2193);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2194);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2195);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2196);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2197);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2198);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2199);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2200);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2201);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2202);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2203);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2204);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2205);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2206);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2207);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2208);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2209);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2210);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2211);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2212);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2213);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2214);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2215);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2216);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2217);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2218);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2219);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2220);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2221);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2222);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2223);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2224);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2225);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2226);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2227);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2228);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2229);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2230);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2231);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2232);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2233);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2234);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2235);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2236);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2237);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2238);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2239);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2240);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2241);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2242);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2243);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2244);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2245);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2246);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2247);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2248);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2249);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2250);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2251);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2252);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2253);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2254);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2255);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2256);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2257);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2258);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2259);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2260);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2261);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2262);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2263);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2264);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2265);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2266);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2267);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2268);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2269);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2270);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2271);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2272);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2273);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2274);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2275);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2276);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2277);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2278);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2279);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2280);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2281);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2282);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2283);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2284);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2285);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2286);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2287);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2288);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2289);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2290);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2291);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2292);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2293);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2294);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2295);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2296);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2297);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2298);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2299);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2300);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2301);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2302);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2303);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2304);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2305);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2306);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2307);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2308);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2309);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2310);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2311);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2312);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2313);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2314);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2315);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2316);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2317);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2318);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2319);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2320);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2321);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2322);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2323);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2324);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2325);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2326);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2327);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2328);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2329);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2330);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2331);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2332);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2333);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2334);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2335);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2336);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2337);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2338);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2339);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2340);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2341);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2342);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2343);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2344);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2345);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2346);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2347);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2348);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2349);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2350);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2351);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2352);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2353);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2354);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2355);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2356);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2357);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2358);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2359);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2360);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2361);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2362);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2363);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2364);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2365);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2366);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2367);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2368);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2369);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2370);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2371);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2372);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2373);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2374);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2375);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2376);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2377);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2378);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2379);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2380);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2381);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2382);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2383);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2384);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2385);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2386);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2387);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2388);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2389);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2390);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2391);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2392);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2393);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2394);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2395);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2396);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2397);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2398);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2399);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2400);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite7(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal_suite7");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2401);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2402);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2403);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2404);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2405);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2406);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2407);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2408);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2409);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2410);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2411);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2412);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2413);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2414);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2415);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2416);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2417);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2418);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2419);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2420);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2421);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2422);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2423);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2424);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2425);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2426);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2427);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2428);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2429);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2430);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2431);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2432);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2433);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2434);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2435);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2436);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2437);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2438);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2439);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2440);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2441);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2442);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2443);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2444);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2445);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2446);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2447);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2448);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2449);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2450);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2451);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2452);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2453);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2454);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2455);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2456);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2457);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2458);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2459);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2460);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2461);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2462);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2463);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2464);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2465);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2466);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2467);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2468);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2469);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2470);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2471);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2472);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2473);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2474);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2475);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2476);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2477);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2478);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2479);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2480);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2481);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2482);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2483);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2484);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2485);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2486);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2487);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2488);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2489);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2490);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2491);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2492);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2493);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2494);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2495);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2496);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2497);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2498);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2499);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2500);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2501);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2502);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2503);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2504);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2505);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2506);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2507);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2508);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2509);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2510);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2511);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2512);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2513);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2514);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2515);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2516);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2517);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2518);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2519);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2520);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2521);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2522);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2523);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2524);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2525);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2526);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2527);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2528);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2529);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2530);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2531);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2532);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2533);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2534);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2535);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2536);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2537);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2538);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2539);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2540);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2541);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2542);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2543);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2544);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2545);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2546);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2547);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2548);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2549);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2550);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2551);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2552);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2553);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2554);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2555);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2556);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2557);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2558);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2559);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2560);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2561);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2562);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2563);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2564);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2565);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2566);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2567);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2568);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2569);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2570);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2571);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2572);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2573);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2574);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2575);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2576);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2577);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2578);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2579);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2580);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2581);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2582);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2583);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2584);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2585);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2586);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2587);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2588);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2589);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2590);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2591);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2592);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2593);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2594);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2595);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2596);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2597);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2598);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2599);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2600);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2601);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2602);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2603);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2604);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2605);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2606);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2607);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2608);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2609);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2610);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2611);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2612);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2613);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2614);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2615);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2616);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2617);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2618);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2619);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2620);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2621);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2622);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2623);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2624);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2625);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2626);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2627);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2628);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2629);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2630);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2631);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2632);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2633);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2634);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2635);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2636);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2637);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2638);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2639);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2640);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2641);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2642);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2643);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2644);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2645);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2646);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2647);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2648);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2649);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2650);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2651);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2652);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2653);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2654);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2655);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2656);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2657);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2658);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2659);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2660);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2661);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2662);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2663);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2664);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2665);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2666);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2667);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2668);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2669);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2670);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2671);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2672);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2673);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2674);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2675);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2676);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2677);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2678);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2679);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2680);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2681);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2682);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2683);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2684);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2685);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2686);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2687);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2688);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2689);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2690);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2691);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2692);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2693);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2694);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2695);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2696);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2697);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2698);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2699);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2700);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2701);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2702);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2703);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2704);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2705);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2706);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2707);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2708);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2709);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2710);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2711);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2712);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2713);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2714);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2715);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2716);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2717);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2718);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2719);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2720);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2721);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2722);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2723);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2724);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2725);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2726);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2727);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2728);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2729);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2730);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2731);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2732);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2733);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2734);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2735);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2736);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2737);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2738);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2739);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2740);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2741);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2742);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2743);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2744);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2745);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2746);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2747);
    tcase_add_test(tc_core, test_from_float_to_decimal_ok2748);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *from_float_to_decimal_suite0(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("from_float_to_decimal0");
    tc_core = tcase_create("Core");

    tcase_add_loop_test(tc_core, test_from_float_to_decimal_fail_big, 0,
                        sizeof(fails_big) / sizeof(*fails_big));
    tcase_add_loop_test(tc_core, test_from_float_to_decimal_fail_big_negate, 0,
                        sizeof(fails_big) / sizeof(*fails_big));
    tcase_add_loop_test(tc_core, test_from_float_to_decimal_fail_small, 0,
                        sizeof(fails_small) / sizeof(*fails_small));
    tcase_add_loop_test(tc_core, test_from_float_to_decimal_fail_small_negate, 0,
                        sizeof(fails_small) / sizeof(*fails_small));

    tcase_add_test(tc_core, test_from_float_to_decimal_incorrect1);
    tcase_add_test(tc_core, test_from_float_to_decimal_unnormal1);
    tcase_add_test(tc_core, test_from_float_to_decimal_unnormal2);
    tcase_add_test(tc_core, test_from_float_to_decimal_unnormal3);
    tcase_add_test(tc_core, test_from_float_to_decimal_unnormal4);
    tcase_add_test(tc_core, test_from_float_to_decimal_unnormal5);
    tcase_add_test(tc_core, test_from_float_to_decimal_unnormal6);

    suite_add_tcase(s, tc_core);

    return s;
}

void test_from_float_to_decimal(int f, s21_decimal decimal_check) {
    s21_decimal result;

    float_cast_test cast_float;
    cast_float.int32_bytes = f;

    int code = s21_from_float_to_decimal(cast_float.f, &result);

    #if defined(__DEBUG)
    printf("---------------------------------\n");
    printf("Float:   %.28f\n", cast_float.f);
    printf("Decimal_check: \n");
    s21_print_decimal_bits(decimal_check);
    s21_print_decimal_string(decimal_check);
    printf("Decimal_result: \n");
    s21_print_decimal_bits(result);
    s21_print_decimal_string(result);
    #endif

    ck_assert_int_eq(code, TEST_CONVERSION_OK);
    ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}
