#include <stdio.h>
#include <omp.h>

#define SIZE 100

int main() {
    int array[SIZE];
    int total_sum = 0;

    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        #pragma omp atomic
        total_sum += array[i];
    }

    printf("Total sum: %d\n", total_sum);

    return 0;
}
