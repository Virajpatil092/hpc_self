#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define VECTOR_SIZE 100000
#define PRINT_LIMIT 10  

int main() {
    int i, num_threads;
    float vector[VECTOR_SIZE];
    float scalar = 5.0;
    double start, end, cpu_time_used;
    int chunk_size;

    for (i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i * 1.0;
    }

    printf("Enter the maximum number of threads to use: ");
    scanf("%d", &num_threads);

    for (int t = 1; t <= num_threads; t++) 
    {
        omp_set_num_threads(t);

        chunk_size = VECTOR_SIZE / t;

        for (i = 0; i < VECTOR_SIZE; i++) {
            vector[i] = i * 1.0;
        }

        start = omp_get_wtime();

        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (i = 0; i < VECTOR_SIZE; i++) {
            vector[i] += scalar;
        }

        end = omp_get_wtime();
        cpu_time_used = end - start;

        printf("Threads: %d, Chunk size: %d, Parallel execution time: %f seconds\n", t, chunk_size, cpu_time_used);

        printf("First %d elements:\n", PRINT_LIMIT);
        for (i = 0; i < PRINT_LIMIT; i++) {
            printf("vector[%d] = %f\n", i, vector[i]);
        }

        printf("Last %d elements:\n", PRINT_LIMIT);
        for (i = VECTOR_SIZE - PRINT_LIMIT; i < VECTOR_SIZE; i++) {
            printf("vector[%d] = %f\n", i, vector[i]);
        }

        printf("\n");
    }

    return 0;
}
