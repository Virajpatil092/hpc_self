#include <stdio.h>
#include <omp.h>

#define SIZE 1000000

int main() {
    int array[SIZE];
    int sum = 0;

    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }

    printf("Sum of all elements in the array: %d\n", sum);

    return 0;
}
