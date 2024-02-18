#include <stdio.h>

int main() {
    double x, y, rSquared = 25;
    char c;
    printf("Введите 2 числа:\n");
    int res = scanf("%lf%lf%c", &x, &y, &c);
    if (res == 3 && c == '\n') {
        if ((x * x + y * y) < rSquared) {
            printf("GOTCHA\n");
        } else {
            printf("MISS\n");
        }
    } else {
        printf("n/a\n");
    }
    return 0;
}
