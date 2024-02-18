#include <stdio.h>
#define ARRLEN 10

int input(int *a);
void output(int *a);
void quickSortRecursive(int *a, int n);
void mergeSort(int *a, int left, int right);

int main() {
    int arr[ARRLEN];
    if (input(arr) == 0) {
        mergeSort(arr, 0, ARRLEN - 1);
        output(arr);
        printf("\n");
        quickSortRecursive(arr, ARRLEN);
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

void quickSortRecursive(int *a, int n) {
    int i = 0;
    int j = n - 1;

    int mid = a[n / 2];

    do {
        while (a[i] < mid) {
            i++;
        }
        while (a[j] > mid) {
            j--;
        }

        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        quickSortRecursive(a, j + 1);
    }
    if (i < n) {
        quickSortRecursive(&a[i], n - i);
    }
}

void mergeSort(int *a, int left, int right) {
    if (left == right) return;     // границы сомкнулись
    int mid = (left + right) / 2;  // определяем середину последовательности
    // и рекурсивно вызываем функцию сортировки для каждой половины
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    int i = left;                                        // начало первого пути
    int j = mid + 1;                                     // начало второго пути
    int tmp[ARRLEN];                                     // дополнительный массив
    for (int step = 0; step < right - left + 1; step++)  // для всех элементов дополнительного массива
    {
        // записываем в формируемую последовательность меньший из элементов двух путей
        // или остаток первого пути если j > r
        if ((j > right) || ((i <= mid) && (a[i] < a[j]))) {
            tmp[step] = a[i];
            i++;
        } else {
            tmp[step] = a[j];
            j++;
        }
    }
    // переписываем сформированную последовательность в исходный массив
    for (int step = 0; step < right - left + 1; step++) {
        a[left + step] = tmp[step];
    }
}