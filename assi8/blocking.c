#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_msg = rank;
    int recv_msg;

    int next_rank = (rank + 1) % size;
    int prev_rank = (rank - 1 + size) % size;

    MPI_Send(&send_msg, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_msg, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received message %d from process %d\n", rank, recv_msg, prev_rank);

    MPI_Finalize();
    return 0;
}
