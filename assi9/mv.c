#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  

int main(int argc, char* argv[]) {
    int rank, size;
    int matrix[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int vector[N] = {1, 1, 1, 1};  
    int result[N]; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = N / size;
    int extra_rows = N % size;
    int local_rows = (rank < extra_rows) ? rows_per_process + 1 : rows_per_process;
    int* local_matrix = (int*)malloc(local_rows * N * sizeof(int));
    int* local_result = (int*)malloc(local_rows * sizeof(int));

    int* sendcounts = (int*)malloc(size * sizeof(int));
    int* displs = (int*)malloc(size * sizeof(int));
    int offset = 0;

    for (int i = 0; i < size; i++) {
        sendcounts[i] = (i < extra_rows) ? (rows_per_process + 1) * N : rows_per_process * N;
        displs[i] = offset;
        offset += sendcounts[i];
    }

    MPI_Scatterv(matrix, sendcounts, displs, MPI_INT, local_matrix, local_rows * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_rows; i++) {
        local_result[i] = 0;
        for (int j = 0; j < N; j++) {
            local_result[i] += local_matrix[i * N + j] * vector[j];
        }
    }

    int* recvcounts = (int*)malloc(size * sizeof(int));
    int* displs_result = (int*)malloc(size * sizeof(int));
    offset = 0;

    for (int i = 0; i < size; i++) {
        recvcounts[i] = (i < extra_rows) ? rows_per_process + 1 : rows_per_process;
        displs_result[i] = offset;
        offset += recvcounts[i];
    }

    MPI_Gatherv(local_result, local_rows, MPI_INT, result, recvcounts, displs_result, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result of Matrix-Vector Multiplication:\n");
        for (int i = 0; i < N; i++) {
            printf("%d\n", result[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
