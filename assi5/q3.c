#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int Aryabhatta = 10; // Private variable for each thread
        int thread_id = omp_get_thread_num();
        int result = thread_id * Aryabhatta;

        printf("Thread ID: %d, Result: %d\n", thread_id, result);
    }

    return 0;
}
