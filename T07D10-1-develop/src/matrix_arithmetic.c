#include <stdio.h>
#include <stdlib.h>
#define ERROR printf("n/a");

void menu(int *choice);
void input(int **arr, int *rows, int *cols);
void output(int **arr, int rows, int cols);
int** sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int** transpose(int **matrix, int n, int m);
int** mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
void allocArray(int ***matrix, int *n, int *m);
int checkInputErrors(int n, int m);
void freeArray(int **arr, int n);

int main() {
    int choice = 0;
    menu(&choice);
    int n_first, m_first, n_second, m_second, n_result, m_result;
    int **matrix_first = NULL;
    int **matrix_second = NULL;
    int **result = NULL;

    switch (choice) {
        //сумма
        case 1:
            allocArray(&matrix_first, &n_first, &m_first);
            if (checkInputErrors(n_first, m_first) == 1) {
                ERROR;
                return 1;
            }
            allocArray(&matrix_second, &n_second, &m_second);
            if (checkInputErrors(n_second, m_second) == 1) {
                ERROR;
                return 1;
            }
            if (n_first != n_second || m_first != m_second) {
                ERROR;
                return 1;
            }
            result = sum(matrix_first, n_first, m_first, matrix_second, n_second, m_second,
                result, &n_result, &m_result);
            output(result, n_result, m_result);

            freeArray(matrix_first, n_first);
            freeArray(matrix_second, n_second);
            freeArray(result, n_result);
            break;
        //умножение
        case 2:
            allocArray(&matrix_first, &n_first, &m_first);
            if (checkInputErrors(n_first, m_first) == 1) {
                ERROR;
                return 1;
            }
            allocArray(&matrix_second, &n_second, &m_second);
            if (checkInputErrors(n_second, m_second) == 1) {
                ERROR;
                return 1;
            }
            if (m_first != n_second) {
                ERROR;
                return 1;
            }
            result = mul(matrix_first, n_first, m_first, matrix_second, n_second, m_second,
                result, &n_result, &m_result);
            output(result, n_result, m_result);
            freeArray(matrix_first, n_first);
            freeArray(matrix_second, n_second);
            freeArray(result, n_result);
            break;
        //транспонирование
        case 3:
            allocArray(&matrix_first, &n_first, &m_first);
            if (checkInputErrors(n_first, m_first) == 1) {
                ERROR;
                return 1;
            }
            n_result = m_first;
            m_result = n_first;
            result = transpose(matrix_first, n_first, m_first);
            output(result, n_result, m_result);
            freeArray(matrix_first, n_first);
            freeArray(result, n_first);
            break;
        default:
            ERROR;
            return 1;
    }
    return 0;
}


int** transpose(int **matrix, int n, int m) {
    int **buffArr = NULL;
    buffArr = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        buffArr[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            buffArr[i][j] = matrix[j][i];
        }
    }
    return buffArr;
}


void freeArray(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

int checkInputErrors(int n, int m) {
    if (n != -1 && m != -1) {
        return 0;
    } else {
        return 1;
    }
}

int** mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    *n_result = n_first;
    *m_result = m_second;
    matrix_result = malloc(*n_result * sizeof(int *));
    for (int i = 0; i < *n_result; i++) {
        matrix_result[i] = malloc(*m_result * sizeof(int));
    }
    
    int k = 0;
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            int sum = 0;
            while (k < m_first) {
                 sum += matrix_first[i][k] * matrix_second[k][j];
                k++;
            }
            matrix_result[i][j] = sum;
            k = 0;
        }
    }
    
    return matrix_result;
}


int** sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    *n_result = n_first;
    *m_result = m_first;
    matrix_result = malloc(*n_result * sizeof(int *));
    for (int i = 0; i < *n_result; i++) {
        matrix_result[i] = malloc(*m_result * sizeof(int));
    }
    
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return matrix_result;
}

void menu(int *choice) { scanf("%d", choice); }

void output(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == cols - 1) {
                printf("%d\n", arr[i][j]);
            } else {
                printf("%d ", arr[i][j]);
            }
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