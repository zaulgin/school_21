#include <stdio.h>
#define LEN 100
#define ERROR printf("n/a")

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int input(int *arr, int *len);
void output(int *arr, int len);
void deleteZero(int *arr, int *len);
void shiftArray(int *arr, int len, int steps);
void swap(int *arr, int len);
int compareArrays(int *buff1, int len1, int *buff2, int len2);
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
    for (int i = 0; i < LEN; i++) {
        buff1[i] = 0;
        buff2[i] = 0;
    }
    
    if (input(buff1, &len1) == 1) {
        ERROR;
        return 1;
    }
    if (input(buff2, &len2) == 1) {
        ERROR;
        return 1;
    }

    deleteZero(buff1, &len1);
    deleteZero(buff2, &len2);

    sum(buff1, len1, buff2, len2, result, &result_length);
    if (result[99] >= 10) {
        ERROR;
        return 1;
    } else {
        output(result, result_length);
    }

    printf("\n");

    if (compareArrays(buff1, len1, buff2, len2)) {
        ERROR;
    } else {
        sub(buff1, len1, buff2, len2, result, &result_length);
        output(result, result_length);
    }
    
    return 0;
}

int compareArrays(int *buff1, int len1, int *buff2, int len2) {
    if (len1 > len2) {
        return 0;
    } else if (len1 < len2) {
        return 1;
    } else {
        if (buff1[0] < buff2[0]) {
            return 1;
        } else if (buff2[0] > buff1[0]) {
            return 0;
        }
    }
    for (int i = 1; i < len1; i++) {
        if (buff1[i] < buff2[i]) {
            return 1;
        }
    }
    return 0;
}

void deleteZero(int *arr, int *len) {
    int steps = 0;
    for (int i = 0; i < *len; i++) {
        if (arr[i] == 0) {
            steps++;
        } else {
            break;
        }
    }
    shiftArray(arr, *len, steps);
    *len -= steps;
}

int input(int *arr, int *len) {
    char endlineCheck = 'c';
    int len_count = 0;
    for (int *p = arr; p - arr < LEN; p++) {
        if (endlineCheck == '\n') {
            break;
        }
        len_count++;
        if (scanf("%d%c", p, &endlineCheck) != 2 || (endlineCheck != '\n' && endlineCheck != ' ') 
        || *p < 0 || *p > 9) {
            return 1;
        }
    }
    *len = len_count;
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

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    *result_length = len1;

    for (int i = 0; i < *result_length; i++) {
        result[i] = 0;
    }

    swap(buff1, len1);
    swap(buff2, len2);

    int j = 0;
    int k = 0;

    int tmpArr[LEN];
    for (int i = 0; i < len1; i++) {
        tmpArr[i] = buff1[i];
    }

    for (int i = 0; i < *result_length; i++) {
        tmpArr[j + 1]--;
        result[i] = (tmpArr[j] + 10) - buff2[k];
        if (result[i] >= 10) {
            tmpArr[j + 1]++;
            result[i] -= 10;
        }

        if (i == *result_length - 1 && result[i] >= 10) {
            result[i] = 0;
        }
        j++;
        k++;
    }

    swap(result, *result_length);
    
    while (result[0] == 0 && *result_length > 1) {
        shiftArray(result, *result_length, 1);
        *result_length -= 1;
    }

    swap(buff1, len1);
    swap(buff2, len2);
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    if (len1 > len2) {
        *result_length = len1 + 1;
    } else {
        *result_length = len2 + 1;
    }

    for (int i = 0; i < *result_length - 1; i++) {
        result[i] = 0;
    }

    swap(buff1, len1);
    swap(buff2, len2);

    int j = 0;
    int k = 0;
    for (int i = 0; i < *result_length; i++) {
        result[i] += buff1[j] + buff2[k];
        if (result[i] >= 10) {
            if (i + 1 != 100) {
                result[i] %= 10;
                result[i + 1] = 1;
            } else {
                return;
            }
        }
        j++;
        k++;
    }

    swap(result, *result_length);
    
    if (result[0] == 0) {
        shiftArray(result, *result_length, 1);
        *result_length -= 1;
    }

    swap(buff1, len1);
    swap(buff2, len2);
}

void shiftArray(int *arr, int len, int steps) {
    for (int *p = arr; p - arr < steps; p++) {
        int temp = arr[0];
        for (int *i = arr; i - arr < len - 1; i++) {
            *i = *(i + 1);
        }
        arr[len - 1] = temp;
    }
}

void swap(int *arr, int len) {
    int buf;
    int j = len - 1;
    for (int i = 0; i < len / 2; i++) {
        if (j < len / 2) {
            break;
        }
        buf = arr[i];
        arr[i] = arr[j];
        arr[j] = buf;
        j--;
    }
}
