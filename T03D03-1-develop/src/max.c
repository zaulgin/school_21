#include <stdio.h>

int max(int a, int b);

int main() {
    int a, b;
    char c, f;

    printf("Введите 2 целых числа:\n");
    int res = scanf("%d%c%d%c", &a, &c, &b, &f);

    if (res == 4 && (c == ' ' || c == '\n') && f == '\n') {
        printf("%d\n", max(a, b));
    } else {
        printf("n/a\n");
    }
    return 0;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
