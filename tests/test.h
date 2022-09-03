#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>

#include "./../s21_decimal.h"
#include "./_helpers/_debug.h"

// Отображение отладочной информации в тестах
// #define __DEBUG 1

#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3

Suite *add_suite0(void);
Suite *add_suite1(void);
Suite *add_suite2(void);
Suite *add_suite3(void);
Suite *add_suite4(void);
Suite *add_suite5(void);
Suite *add_suite6(void);
Suite *add_suite7(void);
Suite *add_suite8(void);
Suite *add_suite9(void);

Suite *sub_suite0(void);
Suite *sub_suite1(void);
Suite *sub_suite2(void);
Suite *sub_suite3(void);
Suite *sub_suite4(void);
Suite *sub_suite5(void);
Suite *sub_suite6(void);
Suite *sub_suite7(void);
Suite *sub_suite8(void);
Suite *sub_suite9(void);

Suite *mul_suite0(void);
Suite *mul_suite1(void);
Suite *mul_suite2(void);
Suite *mul_suite3(void);
Suite *mul_suite4(void);
Suite *mul_suite5(void);
Suite *mul_suite6(void);
Suite *mul_suite7(void);
Suite *mul_suite8(void);
Suite *mul_suite9(void);

Suite *div_suite0(void);
Suite *div_suite1(void);
Suite *div_suite2(void);
Suite *div_suite3(void);
Suite *div_suite4(void);
Suite *div_suite5(void);
Suite *div_suite6(void);
Suite *div_suite7(void);
Suite *div_suite8(void);
Suite *div_suite9(void);
Suite *div_suite10(void);
Suite *div_suite11(void);
Suite *div_suite12(void);
Suite *div_suite13(void);
Suite *div_suite14(void);
Suite *div_suite15(void);
Suite *div_suite16(void);
Suite *div_suite17(void);
Suite *div_suite18(void);

Suite *mod_suite0(void);
Suite *mod_suite1(void);
Suite *mod_suite2(void);
Suite *mod_suite3(void);
Suite *mod_suite4(void);
Suite *mod_suite5(void);
Suite *mod_suite6(void);
Suite *mod_suite7(void);
Suite *mod_suite8(void);
Suite *mod_suite9(void);
Suite *mod_suite10(void);
Suite *mod_suite11(void);
Suite *mod_suite12(void);
Suite *mod_suite13(void);
Suite *mod_suite14(void);
Suite *mod_suite15(void);
Suite *mod_suite16(void);
Suite *mod_suite17(void);
Suite *mod_suite18(void);

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2, s21_decimal decimal_check, int code_check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2, s21_decimal decimal_check, int code_check);
void test_mod(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mod_fail(s21_decimal decimal1, s21_decimal decimal2, int code_check);

#define TEST_COMPARISON_FALSE 0
#define TEST_COMPARISON_TRUE 1

Suite *is_less_suite1(void);
Suite *is_less_suite2(void);
Suite *is_less_suite3(void);
Suite *is_less_suite4(void);
Suite *is_less_suite5(void);
Suite *is_less_suite6(void);
Suite *is_less_suite7(void);
Suite *is_less_suite8(void);
Suite *is_less_suite9(void);
Suite *is_less_suite10(void);
Suite *is_less_suite11(void);
Suite *is_less_suite12(void);
Suite *is_less_suite13(void);
Suite *is_less_suite14(void);
Suite *is_less_suite15(void);
Suite *is_less_suite16(void);

Suite *is_equal_suite1(void);
Suite *is_equal_suite2(void);
Suite *is_equal_suite3(void);
Suite *is_equal_suite4(void);
Suite *is_equal_suite5(void);
Suite *is_equal_suite6(void);
Suite *is_equal_suite7(void);
Suite *is_equal_suite8(void);
Suite *is_equal_suite9(void);
Suite *is_equal_suite10(void);
Suite *is_equal_suite11(void);
Suite *is_equal_suite12(void);
Suite *is_equal_suite13(void);
Suite *is_equal_suite14(void);
Suite *is_equal_suite15(void);
Suite *is_equal_suite16(void);

Suite *is_less_or_equal_suite1(void);
Suite *is_less_or_equal_suite2(void);
Suite *is_less_or_equal_suite3(void);
Suite *is_less_or_equal_suite4(void);
Suite *is_less_or_equal_suite5(void);
Suite *is_less_or_equal_suite6(void);
Suite *is_less_or_equal_suite7(void);
Suite *is_less_or_equal_suite8(void);
Suite *is_less_or_equal_suite9(void);
Suite *is_less_or_equal_suite10(void);
Suite *is_less_or_equal_suite11(void);
Suite *is_less_or_equal_suite12(void);
Suite *is_less_or_equal_suite13(void);
Suite *is_less_or_equal_suite14(void);
Suite *is_less_or_equal_suite15(void);
Suite *is_less_or_equal_suite16(void);

Suite *is_greater_suite1(void);
Suite *is_greater_suite2(void);
Suite *is_greater_suite3(void);
Suite *is_greater_suite4(void);
Suite *is_greater_suite5(void);
Suite *is_greater_suite6(void);
Suite *is_greater_suite7(void);
Suite *is_greater_suite8(void);
Suite *is_greater_suite9(void);
Suite *is_greater_suite10(void);
Suite *is_greater_suite11(void);
Suite *is_greater_suite12(void);
Suite *is_greater_suite13(void);
Suite *is_greater_suite14(void);
Suite *is_greater_suite15(void);
Suite *is_greater_suite16(void);

Suite *is_greater_or_equal_suite1(void);
Suite *is_greater_or_equal_suite2(void);
Suite *is_greater_or_equal_suite3(void);
Suite *is_greater_or_equal_suite4(void);
Suite *is_greater_or_equal_suite5(void);
Suite *is_greater_or_equal_suite6(void);
Suite *is_greater_or_equal_suite7(void);
Suite *is_greater_or_equal_suite8(void);
Suite *is_greater_or_equal_suite9(void);
Suite *is_greater_or_equal_suite10(void);
Suite *is_greater_or_equal_suite11(void);
Suite *is_greater_or_equal_suite12(void);
Suite *is_greater_or_equal_suite13(void);
Suite *is_greater_or_equal_suite14(void);
Suite *is_greater_or_equal_suite15(void);
Suite *is_greater_or_equal_suite16(void);

Suite *is_not_equal_suite1(void);
Suite *is_not_equal_suite2(void);
Suite *is_not_equal_suite3(void);
Suite *is_not_equal_suite4(void);
Suite *is_not_equal_suite5(void);
Suite *is_not_equal_suite6(void);
Suite *is_not_equal_suite7(void);
Suite *is_not_equal_suite8(void);
Suite *is_not_equal_suite9(void);
Suite *is_not_equal_suite10(void);
Suite *is_not_equal_suite11(void);
Suite *is_not_equal_suite12(void);
Suite *is_not_equal_suite13(void);
Suite *is_not_equal_suite14(void);
Suite *is_not_equal_suite15(void);
Suite *is_not_equal_suite16(void);

void test_is_less(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_is_not_equal(s21_decimal decimal1, s21_decimal decimal2, int check);

#define TEST_CONVERSION_OK 0
#define TEST_CONVERSION_ERROR 1

Suite *from_int_to_decimal_suite(void);

Suite *from_float_to_decimal_suite0(void);
Suite *from_float_to_decimal_suite1(void);
Suite *from_float_to_decimal_suite2(void);
Suite *from_float_to_decimal_suite3(void);
Suite *from_float_to_decimal_suite4(void);
Suite *from_float_to_decimal_suite5(void);
Suite *from_float_to_decimal_suite6(void);
Suite *from_float_to_decimal_suite7(void);

Suite *from_decimal_to_int_suite0(void);
Suite *from_decimal_to_int_suite1(void);
Suite *from_decimal_to_int_suite2(void);
Suite *from_decimal_to_int_suite3(void);

Suite *from_decimal_to_float_suite0(void);
Suite *from_decimal_to_float_suite1(void);
Suite *from_decimal_to_float_suite2(void);
Suite *from_decimal_to_float_suite3(void);
Suite *from_decimal_to_float_suite4(void);
Suite *from_decimal_to_float_suite5(void);
Suite *from_decimal_to_float_suite6(void);
Suite *from_decimal_to_float_suite7(void);
Suite *from_decimal_to_float_suite8(void);

void test_from_int_to_decimal(int number, s21_decimal decimal_check);
void test_from_float_to_decimal(int f, s21_decimal decimal_check);
void test_from_decimal_to_int(s21_decimal decimal, int check);
void test_from_decimal_to_int_fail(s21_decimal decimal);
void test_from_decimal_to_float(s21_decimal decimal, int check);

typedef union float_cast_test {
    float f;
    struct {
        uint32_t mantisa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    } parts;
    uint32_t bytes;
    int int32_bytes;
} float_cast_test;

#define TEST_OTHER_OK 0
#define TEST_OTHER_ERROR 1

Suite *floor_suite0(void);
Suite *floor_suite1(void);
Suite *floor_suite2(void);
Suite *floor_suite3(void);

Suite *round_suite0(void);
Suite *round_suite1(void);
Suite *round_suite2(void);
Suite *round_suite3(void);

Suite *truncate_suite0(void);
Suite *truncate_suite1(void);
Suite *truncate_suite2(void);
Suite *truncate_suite3(void);

Suite *negate_suite0(void);
Suite *negate_suite1(void);
Suite *negate_suite2(void);
Suite *negate_suite3(void);

void test_floor(s21_decimal decimal, s21_decimal decimal_check);
void test_round(s21_decimal decimal, s21_decimal decimal_check);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);
void test_negate(s21_decimal decimal, s21_decimal decimal_check);

Suite *debug0(void);
Suite *debug1(void);
Suite *debug2(void);
Suite *debug3(void);

void test_debug(s21_decimal decimal, char *check);

// Количество случайных тестов одного типа
#define NUM_RANDOM_TEST 25

int s21_random_int(int min, int max);
int test_decimal_get_sign(s21_decimal value);
int test_decimal_get_power(s21_decimal value);
int test_is_correct_decimal(s21_decimal decimal);
int test_decimal_is_full_equal(s21_decimal value_1, s21_decimal value_2);

#endif  // SRC_TESTS_TEST_H_
