#include <stdio.h>
#include <omp.h>

#define N 3

void matrixVectorMul(int matrix[N][N], int vector[N], int result[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main() {
    int matrix[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int vector[N] = {1, 2, 3};
    int result[N];

    matrixVectorMul(matrix, vector, result);

    printf("Result: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}