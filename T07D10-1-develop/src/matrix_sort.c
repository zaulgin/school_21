#include <stdio.h>
#include <stdlib.h>
#define ROWS 100
#define COLS 100
#define ERROR printf("n/a")

void menu(int* choice);
int inputDynamic(int** arr, int rows, int cols);
void outputDynamic(int** arr, int rows, int cols);
int inputRowsCols(int* rows, int* cols);
void sortArrayBySum(int** arr, int rows, int cols);
int rowSum(const int* arr, int cols);

int main() {
    int choice = 0;
    menu(&choice);
    if (choice > 0 && choice < 4) {
        int rows, cols;
        switch (choice) {
            //динамическая матрица (указатели к массивам)
            case 1:
                if (inputRowsCols(&rows, &cols) || rows < 1 || cols < 1) {
                    ERROR;
                    return 1;
                }
                int** pointerArray = malloc(rows * sizeof(int*));
                for (int i = 0; i < rows; i++) {
                    pointerArray[i] = malloc(cols * sizeof(int));
                }
                if (inputDynamic(pointerArray, rows, cols)) {
                    for (int i = 0; i < rows; i++) {
                        free(pointerArray[i]);
                    }
                    free(pointerArray);
                    ERROR;
                    return 1;
                }
                sortArrayBySum(pointerArray, rows, cols);
                outputDynamic(pointerArray, rows, cols);
                for (int i = 0; i < rows; i++) {
                    free(pointerArray[i]);
                }
                free(pointerArray);
                break;
            //динамическая матрица (указатели к сегментам массива)
            case 2:
                if (inputRowsCols(&rows, &cols) || rows < 1 || cols < 1) {
                    ERROR;
                    return 1;
                }
                int** pointerArrayToBuffer = malloc(rows * sizeof(int*));
                int* valuesArray = malloc(rows * cols * sizeof(int));
                for (int i = 0; i < rows; i++) {
                    pointerArrayToBuffer[i] = valuesArray + cols * i;
                }
                if (inputDynamic(pointerArrayToBuffer, rows, cols)) {
                    free(valuesArray);
                    free(pointerArrayToBuffer);
                    ERROR;
                    return 1;
                }
                sortArrayBySum(pointerArrayToBuffer, rows, cols);
                outputDynamic(pointerArrayToBuffer, rows, cols);
                free(valuesArray);
                free(pointerArrayToBuffer);
                break;
            //динамическая матрица (один буффер)
            case 3:
                if (inputRowsCols(&rows, &cols) || rows < 1 || cols < 1) {
                    ERROR;
                    return 1;
                }
                int** singleArrayMatrix = malloc(rows * cols * sizeof(int) + rows * sizeof(int*));
                int* ptr = (int*)(singleArrayMatrix + rows);
                for (int i = 0; i < rows; i++) {
                    singleArrayMatrix[i] = ptr + cols * i;
                }
                if (inputDynamic(singleArrayMatrix, rows, cols)) {
                    free(singleArrayMatrix);
                    ERROR;
                    return 1;
                }
                sortArrayBySum(singleArrayMatrix, rows, cols);
                outputDynamic(singleArrayMatrix, rows, cols);
                free(singleArrayMatrix);
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

int inputDynamic(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            if (scanf("%d", &arr[i][j]) != 1) {
                return 1;
            }
    }
    return 0;
}

void outputDynamic(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == cols - 1 && i != rows - 1) {
                printf("%d\n", arr[i][j]);
            } else if (i == rows - 1 && j == cols - 1) {
                printf("%d", arr[i][j]);
            } else {
                printf("%d ", arr[i][j]);
            }
        }
    }
}

int inputRowsCols(int* rows, int* cols) {
    if (scanf("%d", rows) != 1) {
        return 1;
    }
    if (scanf("%d", cols) != 1) {
        return 1;
    }
    return 0;
}

void menu(int* choice) { scanf("%d", choice); }

void sortArrayBySum(int** arr, int rows, int cols) {
    int* buf;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows - 1; j++) {
            if (rowSum(*(arr + j), cols) > rowSum(*(arr + j + 1), cols)) {
                buf = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = buf;
            }
        }
    }
}

int rowSum(const int* arr, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; i++) {
        sum += arr[i];
    }
    return sum;
}