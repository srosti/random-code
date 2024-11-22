#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 3, y = 4, z = 2;
    int ***arr;

    // Allocate memory for the 3D array
    arr = (int ***)calloc(x, sizeof(int**));
    for (int i = 0; i < x; i++) {
        arr[i] = (int **)calloc(y, sizeof(int*));
        for (int j = 0; j < y; j++) {
            arr[i][j] = (int *)calloc(z, sizeof(int));
        }
    }

    // Initialize the 3D array with some values
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                arr[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }

    // Print the 3D array
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                printf("arr[%d][%d][%d] = %d\n", i, j, k, arr[i][j][k]);
            }
        }
    }

    // Free the memory
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);

    return 0;
}