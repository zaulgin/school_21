#include <stdio.h>
#define ARRLEN 10

int input(int *a, int *n, int *c);
void output(int *a, int n);
void shiftArray(int *a, int n, int c);

int main() {
    int n, c, arr[ARRLEN];
    if (input(arr, &n, &c) == 0) {
        shiftArray(arr, n, c);
        output(arr, n);
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}

int input(int *a, int *n, int *c) {
    if (scanf("%d", n) != 1 || *n > ARRLEN || *n <= 0) {
        return 1;
    } else {
        for (int *p = a; p - a < *n; p++) {
            if (scanf("%d", p) != 1) {
                return 1;
            }
        }
    }
    if (scanf("%d", c) != 1) {
        return 1;
    }
    return 0;
}

void shiftArray(int *a, int n, int c) {
    if (c > 0) {
        for (int *p = a; p - a < c; p++) {
            int temp = a[0];
            for (int *i = a; i - a < n - 1; i++) {
                *i = *(i + 1);
            }
            a[n - 1] = temp;
        }
    } else if (c < 0) {
        for (int *p = a; p - a < c * -1; p++) {
            int temp = a[n - 1];
            for (int *i = a + (n - 1); i - a >= 0; i--) {
                *i = *(i - 1);
            }
            a[0] = temp;
        }
    }
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p - a == n - 1) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}
