#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;
    int sum_of_squares = 0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); 
        int square = thread_id * thread_id;

        // Each thread prints its square
        printf("Thread ID: %d, Square: %d\n", thread_id, square);

        // Parallel reduction to compute sum of squares
        #pragma omp atomic
        sum_of_squares += square;
    }

    printf("Sum of squares of thread IDs: %d\n", sum_of_squares);

    return 0;
}
