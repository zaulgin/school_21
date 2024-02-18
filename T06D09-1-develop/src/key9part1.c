/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define ARRLEN 10

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(const int *buffer, int length, int *isEvenElements);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int length, buffer[ARRLEN];
    if (input(buffer, &length) == 0) {
        int isEvenElements;
        int sum = sum_numbers(buffer, length, &isEvenElements);
        if (isEvenElements == 0) {
            printf("n/a");
            return 1;
        } else if (sum == 0) {
            printf("%d\n", sum);
            return 0;
        } else {
            int numbers[ARRLEN];
            printf("%d\n", sum);
            output(numbers, find_numbers(buffer, length, sum, numbers));
        }
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length, int *isEvenElements) {
    int sum = 0;
    *isEvenElements = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
            *isEvenElements = 1;
        }
    }
    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int *i = numbers;
    int count = 0;
    for (int *p = buffer; p - buffer < length; p++) {
        if ((*p) != 0) {
            if (number % (*p) == 0) {
                *i = *p;
                i++;
                count++;
            }
        }
    }
    return count;
}

int input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length > ARRLEN || *length <= 0) {
        return 1;
    } else {
        for (int *p = buffer; p - buffer < *length; p++) {
            if (scanf("%d", p) != 1) {
                return 1;
            }
        }
    }
    return 0;
}

void output(int *buffer, int length) {
    for (int *p = buffer; p - buffer < length; p++) {
        if (p - buffer == length - 1) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}
