#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else {
        int x, y;
        #pragma omp task shared(x)
        x = fibonacci(n - 1);
        #pragma omp task shared(y)
        y = fibonacci(n - 2);
        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n = 20;
    int result;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }

    double end_time = omp_get_wtime();

    printf("Time taken parallel: %f\n", end_time - start_time);

    double start_time_seq = omp_get_wtime();

    result = fibonacci(n);

    double end_time_seq = omp_get_wtime();

    printf("Time taken seq: %f\n", end_time_seq - start_time_seq);
    printf("Fibonacci(%d) = %d\n", n, result);

    printf("speed_up is %f\n", (end_time_seq - start_time_seq) / (end_time - start_time));

    return 0;
}