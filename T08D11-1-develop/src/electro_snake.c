#include <stdio.h>
#include <stdlib.h>
#define ERROR printf("n/a")
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **resultMatrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **resultMatrix);
void allocArray(int ***matrix, int *n, int *m);
void input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);
void sort(int **matrix, int n, int m);
void swap(int *matrix, int m);
void transpose(int **matrix, int n, int m, int **resultTransposed);
void freeArray(int **matrix, int n);

int main() {
    int **array = NULL;
    int n, m;
    allocArray(&array, &n, &m);
    if (n != -1 && m != -1) {
        int **result = NULL;
        result = malloc(n * sizeof(int *));
        if (result == NULL) {
            free(result);
            ERROR;
            return 1;
        }
        for (int i = 0; i < n; i++) {
            result[i] = malloc(m * sizeof(int));
            if (result[i] == NULL) {
                while (i >= 0) {
                    free(result[i]);
                    i--;
                    ERROR;
                    return 1;
                }
            }
        }

        sort_vertical(array, n, m, result);
        output(result, n, m);

        sort_horizontal(array, n, m, result);
        output(result, n, m);

        //очищение динамического массива
        freeArray(result, n);
        freeArray(array, n);
    } else {
        free(array);
        ERROR;
        return 1;
    }
    return 0;
}

void swap(int *matrix, int m) {
    int buf;
    int j = m - 1;
    for (int i = 0; i < m / 2; i++) {
        if (j < m / 2) {
            break;
        }
        buf = matrix[i];
        matrix[i] = matrix[j];
        matrix[j] = buf;
        j--;
    }
}

void sort_vertical(int **matrix, int n, int m, int **resultMatrix) {
    //присвоение резалту данных в исходной матрице
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            resultMatrix[i][j] = matrix[i][j];
        }
    }

    //создание буферного массива
    int **transposeArr = NULL;
    transposeArr = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        transposeArr[i] = malloc(n * sizeof(int));
    }

    transpose(resultMatrix, n, m, transposeArr);

    sort(transposeArr, m, n);

    for (int i = 0; i < m; i++) {
        if (i % 2 != 0) {
            swap(transposeArr[i], n);
        }
    }
    transpose(transposeArr, m, n, resultMatrix);

    freeArray(transposeArr, m);
}

void sort_horizontal(int **matrix, int n, int m, int **resultMatrix) {
    //присвоение резалту данных в исходной матрице
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            resultMatrix[i][j] = matrix[i][j];
        }
    }

    sort(resultMatrix, n, m);
    for (int i = 0; i < n; i++) {
        if (i % 2 != 0) {
            swap(resultMatrix[i], m);
        }
    }
}

void allocArray(int ***matrix, int *n, int *m) {
    if (scanf("%d", n) != 1 || *n <= 0) {
        *n = -1;
        return;
    }
    if (scanf("%d", m) != 1 || *m <= 0) {
        *m = -1;
        return;
    }
    *matrix = NULL;
    *matrix = malloc((*n) * sizeof(int *));
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = malloc((*m) * sizeof(int));
    }
    input(*matrix, n, m);
}

void freeArray(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void input(int **matrix, int *n, int *m) {
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                i = *n;
                while (i >= 0) {
                    free(matrix[i]);
                    i--;
                }
                *n = -1;
                return;
            }
        }
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1) {
                printf("%d\n", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
    }
}

void sort(int **arr, int n, int m) {
    int bufSize = n * m;
    int *buf = NULL;
    buf = malloc(bufSize * sizeof(int));
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            buf[count] = arr[i][j];
            count++;
        }
    }

    for (int i = 0; i < bufSize - 1; i++) {
        for (int j = 0; j < bufSize - i - 1; j++) {
            if (buf[j] > buf[j + 1]) {
                int tmp = buf[j];
                buf[j] = buf[j + 1];
                buf[j + 1] = tmp;
            }
        }
    }

    count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = buf[count];
            count++;
        }
    }
    free(buf);
}

void transpose(int **matrix, int n, int m, int **resultTransposed) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            resultTransposed[i][j] = matrix[j][i];
        }
    }
}