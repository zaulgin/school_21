#include <stdio.h>
#include <stdlib.h>
#define ROWS 100
#define COLS 100
#define ERROR printf("n/a")

void menu(int* choice);
int inputDynamic(int** arr, int rows, int cols);
void outputDynamic(int** arr, int rows, int cols);
int inputStatic(int* arr, int cols);
void outputStatic(int* arr, int cols);
int inputRowsCols(int* rows, int* cols);
void maxmin(int** arr, int rows, int cols);
void maxminStatic(const int* arr, int* max, int* min, int cols);

int main() {
    int choice = 0;
    menu(&choice);
    if (choice > 0 && choice < 5) {
        int rows, cols;
        switch (choice) {
            //статическая матрица
            case 1:
                if (inputRowsCols(&rows, &cols) || rows < 1 || rows > 100 || cols < 1 || cols > 100) {
                    ERROR;
                    return 1;
                }
                int staticArr[ROWS][COLS];
                for (int i = 0; i < rows; i++) {
                    if (inputStatic(&staticArr[i][0], cols)) {
                        ERROR;
                        return 1;
                    }
                }
                for (int i = 0; i < rows; i++) {
                    outputStatic(&staticArr[i][0], cols);
                    printf("\n");
                }
                int maxArr[COLS];
                int minArr[COLS];
                int min, max;
                for (int i = 0; i < rows; i++) {
                    maxminStatic(&staticArr[i][0], &min, &max, cols);
                    maxArr[i] = min;
                    minArr[i] = max;
                }
                outputStatic(maxArr, cols);
                printf("\n");
                outputStatic(minArr, cols);
                break;
            //динамическая матрица (указатели к массивам)
            case 2:
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
                outputDynamic(pointerArray, rows, cols);
                maxmin(pointerArray, rows, cols);
                for (int i = 0; i < rows; i++) {
                    free(pointerArray[i]);
                }
                free(pointerArray);
                break;
            //динамическая матрица (указатели к сегментам массива)
            case 3:
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
                outputDynamic(pointerArrayToBuffer, rows, cols);
                maxmin(pointerArrayToBuffer, rows, cols);
                free(valuesArray);
                free(pointerArrayToBuffer);
                break;
            //динамическая матрица (один буффер)
            case 4:
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
                outputDynamic(singleArrayMatrix, rows, cols);
                maxmin(singleArrayMatrix, rows, cols);
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
            if (j == cols - 1) {
                printf("%d\n", arr[i][j]);
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

int inputStatic(int* arr, int cols) {
    for (int* p = arr; p - arr < cols; p++) {
        if (scanf("%d", p) != 1) {
            return 1;
        }
    }
    return 0;
}

void outputStatic(int* arr, int cols) {
    for (int* p = arr; p - arr < cols; p++) {
        if (p - arr == cols - 1) {
            printf("%d", *p);
        } else {
            printf("%d ", *p);
        }
    }
}

void maxmin(int** arr, int rows, int cols) {
    int* maxArr = malloc(rows * sizeof(int));
    int* minArr = malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        int max = arr[i][0];
        int min = arr[i][0];
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
            if (arr[i][j] < min) {
                min = arr[i][j];
            }
            maxArr[i] = max;
            minArr[i] = min;
        }
    }
    outputStatic(maxArr, rows);
    printf("\n");
    outputStatic(minArr, rows);
    free(maxArr);
    free(minArr);
}

void maxminStatic(const int* arr, int* max, int* min, int cols) {
    *max = arr[0];
    *min = arr[0];
    for (int i = 0; i < cols; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
        }
        if (arr[i] < *min) {
            *min = arr[i];
        }
    }
}