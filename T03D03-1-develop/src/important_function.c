#include <math.h>
#include <stdio.h>

double function(double x);

int main() {
    double x;
    char c;
    printf("Введите число:\n");
    int res = scanf("%lf%c", &x, &c);
    if (res == 2 && c == '\n') {
        printf("%.1lf\n", function(x));
    } else {
        printf("n/a\n");
    }
    return 0;
}

double function(double x) {
    return 7e-3 * pow(x, 4) + ((22.8 * cbrt(x) - 1e3) * x + 3) / (x * x / 2) - x * pow((10 + x), 2 / x) -
           1.01;
}
