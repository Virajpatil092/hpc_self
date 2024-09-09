#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VECTOR_SIZE 100000
#define PRINT_LIMIT 10 
int main() {
    int i, num_threads;
    float vector[VECTOR_SIZE];
    float scalar = 5.0;
    clock_t start, end;
    double cpu_time_used;
    int chunk_size, start_index, end_index;

    for (i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i * 1.0;
    }

    printf("Enter the maximum number of simulated threads: ");
    scanf("%d", &num_threads);

    for (int t = 1; t <= num_threads; t++) {
        chunk_size = VECTOR_SIZE / t;
        if (chunk_size < 1) chunk_size = 1;  

        for (i = 0; i < VECTOR_SIZE; i++) {
            vector[i] = i * 1.0;
        }

        start = clock();

        for (int j = 0; j < t; j++) {
            start_index = j * chunk_size;
            end_index = (j == t - 1) ? VECTOR_SIZE : start_index + chunk_size;  // Handle the last chunk

            for (i = start_index; i < end_index; i++) {
                vector[i] += scalar;
            }
        }

        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Simulated threads: %d, Chunk size: %d, Sequential execution time: %f seconds\n", t, chunk_size, cpu_time_used);

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
