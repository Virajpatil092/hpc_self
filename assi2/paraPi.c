#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 100000000

int main() {
    long long int num_points = NUM_POINTS;
    long long int points_in_circle = 0;
    double x, y;
    double pi;
    double start, end;
    unsigned int seed;

    points_in_circle = 0;

    // Timing the parallel computation
    start = omp_get_wtime();

    #pragma omp parallel
    {
        seed = omp_get_thread_num(); // Initialize seed for each thread

        #pragma omp for reduction(+:points_in_circle) private(x, y, seed)
        for (long long int i = 0; i < num_points; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                points_in_circle++;
            }
        }
    }

    end = omp_get_wtime();
    double parallel_time = end - start;

    pi = 4.0 * points_in_circle / num_points;

    // Print the results
    printf("Parallel computation:\n");
    printf("Calculated value of pi: %f\n", pi);
    printf("Parallel execution time: %f seconds\n", parallel_time);

    return 0;
}
