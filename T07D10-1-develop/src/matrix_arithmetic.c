#include <stdio.h>
#include <stdlib.h>
#define ERROR printf("n/a");

void menu(int *choice);
int input(int **arr, int *rows, int *cols);
void output(int **arr, int rows, int cols);
int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int transpose(int **matrix, int n, int m);
int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int main() {
    int choice = 0;
    menu(&choice);
    if (choice > 0 && choice < 3) {
        int rows1, cols1;
        int rows2, cols2;
        int **matrix1;
        int **matrix2;
        switch (choice) {
            //сумма
            case 1:
                // if (input(matrix1, &rows1, &cols1) || input(matrix2, &rows2, &cols2)) {
                //     ERROR;
                //     return 1;
                // }
                input(matrix1, &rows1, &cols1);

                // input(matrix2, &rows2, &cols2);
                // sum(pointerArray, rows, cols);
                output(matrix1, rows1, cols1);
                // output(matrix2, rows2, cols2);
                for (int i = 0; i < rows1; i++) {
                    free(matrix1[i]);
                }
                free(matrix1);
                for (int i = 0; i < rows1; i++) {
                    free(matrix2[i]);
                }
                free(matrix2);
                break;
            //умножение
            case 2:
                if (input(matrix1, &rows1, &cols1) || input(matrix2, &rows2, &cols2)) {
                    ERROR;
                    return 1;
                }
                // sum(pointerArray, rows, cols);
                output(matrix1, rows1, cols1);
                for (int i = 0; i < rows1; i++) {
                    free(matrix1[i]);
                }
                free(matrix1);
                for (int i = 0; i < rows1; i++) {
                    free(matrix2[i]);
                }
                free(matrix2);
                break;
            //транспонирование
            case 3:
                if (input(matrix1, &rows1, &cols1)) {
                    ERROR;
                    return 1;
                }
                // sum(pointerArray, rows, cols);
                output(matrix1, rows1, cols1);
                for (int i = 0; i < rows1; i++) {
                    free(matrix1[i]);
                }
                free(matrix1);
                break;
            default:
                break;
        }
    } else {
        ERROR;
        return 1;
    }
    return 0;
}

void menu(int *choice) { scanf("%d", choice); }

int input(int **matrix, int *rows, int *cols) {
    if (scanf("%d", rows) != 1 || *rows < 1) {
        return 1;
    }
    if (scanf("%d", cols) != 1 || *cols < 1) {
        return 1;
    }
    matrix = malloc((*rows) * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        *(matrix + i) = malloc((*cols) * sizeof(int));
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++)
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 1;
            }
    }
    return 0;
}

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