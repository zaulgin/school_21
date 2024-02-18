#include <stdio.h>
#include <stdlib.h>
#define ROWS 100
#define COLS 100
#define ERROR printf("n/a")

void menu(int* choice);
int inputDynamic(int** arr, int rows, int cols);    
void outputDynamic(int** arr, int rows, int cols);
int inputStatic(int arr[ROWS][COLS], int rows, int cols);
void outputStatic(int arr[ROWS][COLS], int rows, int cols);
int inputRowsCols(int* rows, int* cols);
void maxRowElements(int** arr, int rows, int cols);
void minColElements(int** arr, int rows, int cols);
void maxRowElementsStatic(int arr[ROWS][COLS], int rows, int cols);
void minColElementsStatic(int arr[ROWS][COLS], int rows, int cols);

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
                if (inputStatic(staticArr, rows, cols)) {
                    ERROR;
                    return 1;
                }
                outputStatic(staticArr, rows, cols);
                maxRowElementsStatic(staticArr, rows, cols);
                printf("\n");
                minColElementsStatic(staticArr, rows, cols);
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
                maxRowElements(pointerArray, rows, cols);
                printf("\n");
                minColElements(pointerArray, rows, cols);
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
                maxRowElements(pointerArrayToBuffer, rows, cols);
                printf("\n");
                minColElements(pointerArrayToBuffer, rows, cols);
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
                maxRowElements(singleArrayMatrix, rows, cols);
                printf("\n");
                minColElements(singleArrayMatrix, rows, cols);
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

int inputStatic(int arr[ROWS][COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            if (scanf("%d", &arr[i][j]) != 1) {
                return 1;
            }
    }
    return 0;
}

void outputStatic(int arr[ROWS][COLS], int rows, int cols) {
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

void maxRowElements(int** arr, int rows, int cols) {
    int* maxArr = malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        int max = arr[i][0];
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
            maxArr[i] = max;
        }
    }

    for (int i = 0; i < rows; i++) {
        if (i == rows - 1) {
            printf("%d", maxArr[i]);
        } else {
            printf("%d ", maxArr[i]);
        }
    }

    free(maxArr);
}

void maxRowElementsStatic(int arr[ROWS][COLS], int rows, int cols) {
    int* maxArr = malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        int max = arr[i][0];
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > max) {
                max = arr[i][j];
            }
            maxArr[i] = max;
        }
    }

    for (int i = 0; i < rows; i++) {
        if (i == rows - 1) {
            printf("%d", maxArr[i]);
        } else {
            printf("%d ", maxArr[i]);
        }
    }

    free(maxArr);
}

void minColElements(int** arr, int rows, int cols) {
    int* minArr = malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        int min = arr[0][i];
        for (int j = 0; j < rows; j++) {
            if (arr[j][i] < min) {
                min = arr[j][i];
            }
            minArr[i] = min;
        }
    }

    for (int i = 0; i < cols; i++) {
        if (i == cols - 1) {
            printf("%d", minArr[i]);
        } else {
            printf("%d ", minArr[i]);
        }
    }
    free(minArr);
}

void minColElementsStatic(int arr[ROWS][COLS], int rows, int cols) {
    int* minArr = malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        int min = arr[0][i];
        for (int j = 0; j < rows; j++) {
            if (arr[j][i] < min) {
                min = arr[j][i];
            }
            minArr[i] = min;
        }
    }

    for (int i = 0; i < cols; i++) {
        if (i == cols - 1) {
            printf("%d", minArr[i]);
        } else {
            printf("%d ", minArr[i]);
        }
    }
    free(minArr);
}