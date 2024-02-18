#include <stdio.h>
#include <stdlib.h>

int input(int *arr, int n);
void output(int *arr, int n);
void sort(int *arr, int n);

int main() {
    int n;
    if (scanf("%d", &n) == 1 && n > 0) {
        int *pArr = malloc(n * sizeof(int));
        if (input(pArr, n) == 0) {
            sort(pArr, n);
            output(pArr, n);
            free(pArr);
        } else {
            free(pArr);
            printf("n/a");
            return 1;
        }
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}

int input(int *arr, int n) {
    for (int *p = arr; p - arr < n; p++) {
        if (scanf("%d", p) != 1) {
            return 1;
        }
    }
    return 0;
}

void output(int *arr, int n) {
    for (int *p = arr; p - arr < n; p++) {
        if (p - arr == n - 1) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}