#include <stdio.h>
#define ARRLEN 10

int input(int *a);
void output(int *a);
void sort(int *a);

int main() {
    int arr[ARRLEN];
    if (input(arr) == 0) {
        sort(arr);
        output(arr);
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}

int input(int *a) {
    for (int *p = a; p - a < ARRLEN; p++) {
        if (scanf("%d", p) != 1) {
            return 1;
        }
    }
    return 0;
}

void output(int *a) {
    for (int *p = a; p - a < ARRLEN; p++) {
        if (p - a == ARRLEN - 1) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}

void sort(int *a) {
    for (int *p = a; p - a < ARRLEN - 1; p++) {
        for (int *i = a; i - a < ARRLEN - (p - a); i++) {
            if (*i > *(i + 1)) {
                int tmp = *i;
                *i = *(i + 1);
                *(i + 1) = tmp;
            }
        }
    }
}