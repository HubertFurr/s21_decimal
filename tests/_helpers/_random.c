#include <stdlib.h>
/**
 * @brief генерирует случайное положительное число int в диапазоне [min, max]
 * если min < 0, то min будет считаться 0
 * если max < 0, то max будет считаться -max
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param min минимальное генерируемое число
 * @param max максимальное генерируемое число
 * @return int случайное число
 */
int s21_random_int(int min, int max) {
    if (min < 0) {
        min = 0;
    }

    if (max < 0) {
        max = -max;
    }

    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
