#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
void output(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 0) {
        output(data, n);
        return 0;
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n > NMAX || *n <= 0) {
        return 1;
    } else {
        for (int *p = a; p - a < *n; p++) {
            if (scanf("%d", p) != 1) {
                return 1;
            }
        }
        return 0;
    }
}

double mean(int *a, int n) {
    double sum = 0;
    double mean;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    mean = sum / n;
    return mean;
}

double variance(int *a, int n) {
    double variance;
    double temp = 0;
    for (int *p = a; p - a < n; p++) {
        temp += pow(((*p) - mean(a, n)), 2);
    }
    variance = temp / n;
    return variance;
}

void output(int *a, int n) {
    int outputElement = 0;
    for (int *p = a; p - a < n; p++) {
        if (!((*p) % 2) && (*p) >= mean(a, n) && (*p) != 0 &&
            (*p) <= (mean(a, n) + 3 * sqrt(variance(a, n)))) {
            outputElement = *p;
            break;
        }
    }
    printf("%d", outputElement);
}
