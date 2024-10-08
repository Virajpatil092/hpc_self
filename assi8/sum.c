#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size, n = 10;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int local_sum = 0, total_sum = 0;

    if (rank == 0) {
        for (int i = 0; i < n / 2; i++) {
            local_sum += A[i];
        }
        MPI_Recv(&total_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum += local_sum;
        printf("Total Sum: %d\n", total_sum);
    } 
    else if (rank == 1) {
        for (int i = n / 2; i < n; i++) {
            local_sum += A[i];
        }
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
