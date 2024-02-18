#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int input(int *arr, int *len);
void output(int *arr, int len);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int len1, len2, result_length, buff1[LEN], buff2[LEN], result[LEN];
    input(buff1, &len1);
    input(buff2, &len2);
    sum(buff1, len1, buff2, len2, result, &result_length);
    output(result, result_length);
}

int input(int *arr, int *len) {
    if (scanf("%d", len) != 1 || *len > LEN || *len <= 0) {
        return 1;
    } else {
        for (int *p = arr; p - arr < *len; p++) {
            if (scanf("%d", p) != 1) {
                return 1;
            }
        }
    }
    return 0;
}

void output(int *arr, int len) {
    for (int *p = arr; p - arr < len; p++) {
        if (p - arr == len - 1) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    *result_length = len1;
    if (len1 > len2) {
        *result_length = len2;
    }
    int *i = result + (*result_length);
    int *j = buff2 + (len2 - 1);
    for (int *p = buff1 + (len1 - 1); p - buff1 >= 0; p--) {
        *i = (*p) + (*j);
        if (*i >= 10) {
            *i = *i % 10;
            *(p - 1) += 1;
        }
        j--;
        i--;
        if (j - buff2 < 0) {
            *j = 0;
        }
    }
}

// void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {

// }