#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 500 // Size of the matrix

void matrix_multiply_static(int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_dynamic(int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    srand(time(0));

    // Initialize matrices A and B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    double start = omp_get_wtime();
    matrix_multiply_static(A, B, C);
    double end = omp_get_wtime();
    printf("Static scheduling time: %f seconds\n", end - start);

    start = omp_get_wtime();
    matrix_multiply_dynamic(A, B, C);
    end = omp_get_wtime();
    printf("Dynamic scheduling time: %f seconds\n", end - start);

    return 0;
}
