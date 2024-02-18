#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define ERROR printf("n/a")

double det(double **matrix, int n, int m);
void input(double **matrix, int *n, int *m);
void output(double det);
void allocArray(double ***matrix, int *n, int *m);
void freeArray(double **matrix, int n);

int main() {
    double **array = NULL;
    int n, m;
    allocArray(&array, &n, &m);
    if (n != -1) {
        double res = det(array, n, m);
        output(res);
        freeArray(array, n);
    } else {
        free(array);
        ERROR;
        return 1;
    }
    return 0;
}

void freeArray(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void allocArray(double ***matrix, int *n, int *m) {
    if (scanf("%d", n) != 1 || *n <= 0) {
        *n = -1;
        return;
    }
    if (scanf("%d", m) != 1 || *m <= 0) {
        *m = -1;
        return;
    }
    if (*n != *m) {
        *n = -1;
        return;
    }
    *matrix = NULL;
    *matrix = malloc((*n) * sizeof(int *));
    for (int i = 0; i < *n; i++) {
        (*matrix)[i] = malloc((*m) * sizeof(int));
    }
    input(*matrix, n, m);
}

void input(double **matrix, int *n, int *m) {
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
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

double det(double **matrix, int n, int m) {
    double det = 1;
    for (int i = 0; i < n; ++i) {
        double mx = fabs(matrix[i][i]);
        int idx = i;
        for (int j = i + 1; j < m; ++j) {
            if (mx < fabs(matrix[i][j])) {
                mx = fabs(matrix[i][idx = j]);
            }
            if (idx != i) {
                for (int j = i; j < n; ++j) {
                    double t = matrix[j][i];
                    matrix[j][i] = matrix[j][idx];
                    matrix[j][idx] = t;
                }
                det = -det;
            }
        }
        for (int k = i + 1; k < n; ++k) {
            double t = matrix[k][i] / matrix[i][i];
            for (int j = i; j < n; ++j) {
                matrix[k][j] -= matrix[i][j] * t;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        det *= matrix[i][i];
    }
    return det;
}

void output(double det) { printf("%.6f", det); }