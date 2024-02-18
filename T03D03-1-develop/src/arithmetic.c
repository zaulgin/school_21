#include <stdio.h>

int sum(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int main() {
    int a = 0, b = 0;
    char c, f;
    printf("Введите 2 целых числа через пробел(ы):\n");
    int res = scanf("%d%c%d%c", &a, &c, &b, &f);

    if (res == 4 && c == ' ' && f == '\n') {
        if (b == 0) {
            printf("%d %d %d n/a\n", sum(a, b), sub(a, b), mul(a, b));
        } else {
            printf("%d %d %d %d\n", sum(a, b), sub(a, b), mul(a, b), div(a, b));
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}

int sum(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int div(int a, int b) { return a / b; }
