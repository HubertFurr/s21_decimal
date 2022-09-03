#include <stdlib.h>

#include "./../s21_decimal.h"
#include "./test.h"

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(NULL);
    srunner_add_suite(sr, add_suite0());
    srunner_add_suite(sr, add_suite1());
    srunner_add_suite(sr, add_suite2());
    srunner_add_suite(sr, add_suite3());
    srunner_add_suite(sr, add_suite4());
    srunner_add_suite(sr, add_suite5());
    srunner_add_suite(sr, add_suite6());
    srunner_add_suite(sr, add_suite7());
    srunner_add_suite(sr, add_suite8());
    srunner_add_suite(sr, add_suite9());

    srunner_add_suite(sr, sub_suite0());
    srunner_add_suite(sr, sub_suite1());
    srunner_add_suite(sr, sub_suite2());
    srunner_add_suite(sr, sub_suite3());
    srunner_add_suite(sr, sub_suite4());
    srunner_add_suite(sr, sub_suite5());
    srunner_add_suite(sr, sub_suite6());
    srunner_add_suite(sr, sub_suite7());
    srunner_add_suite(sr, sub_suite8());
    srunner_add_suite(sr, sub_suite9());

    srunner_add_suite(sr, mul_suite0());
    srunner_add_suite(sr, mul_suite1());
    srunner_add_suite(sr, mul_suite2());
    srunner_add_suite(sr, mul_suite3());
    srunner_add_suite(sr, mul_suite4());
    srunner_add_suite(sr, mul_suite5());
    srunner_add_suite(sr, mul_suite6());
    srunner_add_suite(sr, mul_suite7());
    srunner_add_suite(sr, mul_suite8());
    srunner_add_suite(sr, mul_suite9());

    srunner_add_suite(sr, div_suite0());
    srunner_add_suite(sr, div_suite1());
    srunner_add_suite(sr, div_suite2());
    srunner_add_suite(sr, div_suite3());
    srunner_add_suite(sr, div_suite4());
    srunner_add_suite(sr, div_suite5());
    srunner_add_suite(sr, div_suite6());
    srunner_add_suite(sr, div_suite7());
    srunner_add_suite(sr, div_suite8());
    srunner_add_suite(sr, div_suite9());
    srunner_add_suite(sr, div_suite10());
    srunner_add_suite(sr, div_suite11());
    srunner_add_suite(sr, div_suite12());
    srunner_add_suite(sr, div_suite13());
    srunner_add_suite(sr, div_suite14());
    srunner_add_suite(sr, div_suite15());
    srunner_add_suite(sr, div_suite16());
    srunner_add_suite(sr, div_suite17());
    srunner_add_suite(sr, div_suite18());

    srunner_add_suite(sr, mod_suite0());
    srunner_add_suite(sr, mod_suite1());
    srunner_add_suite(sr, mod_suite2());
    srunner_add_suite(sr, mod_suite3());
    srunner_add_suite(sr, mod_suite4());
    srunner_add_suite(sr, mod_suite5());
    srunner_add_suite(sr, mod_suite6());
    srunner_add_suite(sr, mod_suite7());
    srunner_add_suite(sr, mod_suite8());
    srunner_add_suite(sr, mod_suite9());
    srunner_add_suite(sr, mod_suite10());
    srunner_add_suite(sr, mod_suite11());
    srunner_add_suite(sr, mod_suite12());
    srunner_add_suite(sr, mod_suite13());
    srunner_add_suite(sr, mod_suite14());
    srunner_add_suite(sr, mod_suite15());
    srunner_add_suite(sr, mod_suite16());
    srunner_add_suite(sr, mod_suite17());
    srunner_add_suite(sr, mod_suite18());

    srunner_add_suite(sr, is_less_suite1());
    srunner_add_suite(sr, is_less_suite2());
    srunner_add_suite(sr, is_less_suite3());
    srunner_add_suite(sr, is_less_suite4());
    srunner_add_suite(sr, is_less_suite5());
    srunner_add_suite(sr, is_less_suite6());
    srunner_add_suite(sr, is_less_suite7());
    srunner_add_suite(sr, is_less_suite8());
    srunner_add_suite(sr, is_less_suite9());
    srunner_add_suite(sr, is_less_suite10());
    srunner_add_suite(sr, is_less_suite11());
    srunner_add_suite(sr, is_less_suite12());
    srunner_add_suite(sr, is_less_suite13());
    srunner_add_suite(sr, is_less_suite14());
    srunner_add_suite(sr, is_less_suite15());
    srunner_add_suite(sr, is_less_suite16());

    srunner_add_suite(sr, is_equal_suite1());
    srunner_add_suite(sr, is_equal_suite2());
    srunner_add_suite(sr, is_equal_suite3());
    srunner_add_suite(sr, is_equal_suite4());
    srunner_add_suite(sr, is_equal_suite5());
    srunner_add_suite(sr, is_equal_suite6());
    srunner_add_suite(sr, is_equal_suite7());
    srunner_add_suite(sr, is_equal_suite8());
    srunner_add_suite(sr, is_equal_suite9());
    srunner_add_suite(sr, is_equal_suite10());
    srunner_add_suite(sr, is_equal_suite11());
    srunner_add_suite(sr, is_equal_suite12());
    srunner_add_suite(sr, is_equal_suite13());
    srunner_add_suite(sr, is_equal_suite14());
    srunner_add_suite(sr, is_equal_suite15());
    srunner_add_suite(sr, is_equal_suite16());

    srunner_add_suite(sr, is_less_or_equal_suite1());
    srunner_add_suite(sr, is_less_or_equal_suite2());
    srunner_add_suite(sr, is_less_or_equal_suite3());
    srunner_add_suite(sr, is_less_or_equal_suite4());
    srunner_add_suite(sr, is_less_or_equal_suite5());
    srunner_add_suite(sr, is_less_or_equal_suite6());
    srunner_add_suite(sr, is_less_or_equal_suite7());
    srunner_add_suite(sr, is_less_or_equal_suite8());
    srunner_add_suite(sr, is_less_or_equal_suite9());
    srunner_add_suite(sr, is_less_or_equal_suite10());
    srunner_add_suite(sr, is_less_or_equal_suite11());
    srunner_add_suite(sr, is_less_or_equal_suite12());
    srunner_add_suite(sr, is_less_or_equal_suite13());
    srunner_add_suite(sr, is_less_or_equal_suite14());
    srunner_add_suite(sr, is_less_or_equal_suite15());
    srunner_add_suite(sr, is_less_or_equal_suite16());

    srunner_add_suite(sr, is_greater_suite1());
    srunner_add_suite(sr, is_greater_suite2());
    srunner_add_suite(sr, is_greater_suite3());
    srunner_add_suite(sr, is_greater_suite4());
    srunner_add_suite(sr, is_greater_suite5());
    srunner_add_suite(sr, is_greater_suite6());
    srunner_add_suite(sr, is_greater_suite7());
    srunner_add_suite(sr, is_greater_suite8());
    srunner_add_suite(sr, is_greater_suite9());
    srunner_add_suite(sr, is_greater_suite10());
    srunner_add_suite(sr, is_greater_suite11());
    srunner_add_suite(sr, is_greater_suite12());
    srunner_add_suite(sr, is_greater_suite13());
    srunner_add_suite(sr, is_greater_suite14());
    srunner_add_suite(sr, is_greater_suite15());
    srunner_add_suite(sr, is_greater_suite16());

    srunner_add_suite(sr, is_greater_or_equal_suite1());
    srunner_add_suite(sr, is_greater_or_equal_suite2());
    srunner_add_suite(sr, is_greater_or_equal_suite3());
    srunner_add_suite(sr, is_greater_or_equal_suite4());
    srunner_add_suite(sr, is_greater_or_equal_suite5());
    srunner_add_suite(sr, is_greater_or_equal_suite6());
    srunner_add_suite(sr, is_greater_or_equal_suite7());
    srunner_add_suite(sr, is_greater_or_equal_suite8());
    srunner_add_suite(sr, is_greater_or_equal_suite9());
    srunner_add_suite(sr, is_greater_or_equal_suite10());
    srunner_add_suite(sr, is_greater_or_equal_suite11());
    srunner_add_suite(sr, is_greater_or_equal_suite12());
    srunner_add_suite(sr, is_greater_or_equal_suite13());
    srunner_add_suite(sr, is_greater_or_equal_suite14());
    srunner_add_suite(sr, is_greater_or_equal_suite15());
    srunner_add_suite(sr, is_greater_or_equal_suite16());

    srunner_add_suite(sr, is_not_equal_suite1());
    srunner_add_suite(sr, is_not_equal_suite2());
    srunner_add_suite(sr, is_not_equal_suite3());
    srunner_add_suite(sr, is_not_equal_suite4());
    srunner_add_suite(sr, is_not_equal_suite5());
    srunner_add_suite(sr, is_not_equal_suite6());
    srunner_add_suite(sr, is_not_equal_suite7());
    srunner_add_suite(sr, is_not_equal_suite8());
    srunner_add_suite(sr, is_not_equal_suite9());
    srunner_add_suite(sr, is_not_equal_suite10());
    srunner_add_suite(sr, is_not_equal_suite11());
    srunner_add_suite(sr, is_not_equal_suite12());
    srunner_add_suite(sr, is_not_equal_suite13());
    srunner_add_suite(sr, is_not_equal_suite14());
    srunner_add_suite(sr, is_not_equal_suite15());
    srunner_add_suite(sr, is_not_equal_suite16());

    srunner_add_suite(sr, from_int_to_decimal_suite());

    srunner_add_suite(sr, from_float_to_decimal_suite0());
    srunner_add_suite(sr, from_float_to_decimal_suite1());
    srunner_add_suite(sr, from_float_to_decimal_suite2());
    srunner_add_suite(sr, from_float_to_decimal_suite3());
    srunner_add_suite(sr, from_float_to_decimal_suite4());
    srunner_add_suite(sr, from_float_to_decimal_suite5());
    srunner_add_suite(sr, from_float_to_decimal_suite6());
    srunner_add_suite(sr, from_float_to_decimal_suite7());

    srunner_add_suite(sr, from_decimal_to_int_suite0());
    srunner_add_suite(sr, from_decimal_to_int_suite1());
    srunner_add_suite(sr, from_decimal_to_int_suite2());
    srunner_add_suite(sr, from_decimal_to_int_suite3());

    srunner_add_suite(sr, from_decimal_to_float_suite0());
    srunner_add_suite(sr, from_decimal_to_float_suite1());
    srunner_add_suite(sr, from_decimal_to_float_suite2());
    srunner_add_suite(sr, from_decimal_to_float_suite3());
    srunner_add_suite(sr, from_decimal_to_float_suite4());
    srunner_add_suite(sr, from_decimal_to_float_suite5());
    srunner_add_suite(sr, from_decimal_to_float_suite6());
    srunner_add_suite(sr, from_decimal_to_float_suite7());
    srunner_add_suite(sr, from_decimal_to_float_suite8());

    srunner_add_suite(sr, floor_suite0());
    srunner_add_suite(sr, floor_suite1());
    srunner_add_suite(sr, floor_suite2());
    srunner_add_suite(sr, floor_suite3());

    srunner_add_suite(sr, round_suite0());
    srunner_add_suite(sr, round_suite1());
    srunner_add_suite(sr, round_suite2());
    srunner_add_suite(sr, round_suite3());

    srunner_add_suite(sr, truncate_suite0());
    srunner_add_suite(sr, truncate_suite1());
    srunner_add_suite(sr, truncate_suite2());
    srunner_add_suite(sr, truncate_suite3());

    srunner_add_suite(sr, negate_suite0());
    srunner_add_suite(sr, negate_suite1());
    srunner_add_suite(sr, negate_suite2());
    srunner_add_suite(sr, negate_suite3());

    srunner_add_suite(sr, debug0());
    srunner_add_suite(sr, debug1());
    srunner_add_suite(sr, debug2());
    srunner_add_suite(sr, debug3());

    srunner_set_fork_status(sr, CK_NOFORK);
    // Используем данный блок для вывода подробно про каждый тест с разбиением по блокам
    // srunner_set_log(sr, "-");
    // srunner_run_all(sr, CK_SILENT);  // CK_SILENT || CK_MINIMAL || CK_NORMAL || CK_VERBOSE
    // Либо данный блок вместо предыдущего для вывода только ошибок и общего результата
    srunner_run_all(sr, CK_NORMAL);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
