#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size != 5) {
        if (world_rank == 0) {
            printf("This program needs exactly 5 processes, but you provided %d.\n", world_size);
        }
        MPI_Finalize();
        return -1;
    }

    // Display rank and communicator group size for each process
    printf("Process %d out of %d processes in the communicator group\n", world_rank, world_size);

    MPI_Finalize();
    return 0;
}
