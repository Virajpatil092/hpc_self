#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum = 0;
    int partial_sum = 0;

    #pragma omp parallel private(partial_sum) shared(total_sum) lastprivate(partial_sum)
    {
        partial_sum = 0;
        #pragma omp for
        for (int i = 1; i <= 20; i++) {
            partial_sum += i;
        }

        #pragma omp critical
        total_sum += partial_sum;
    }

    printf("Total sum of the first 20 natural numbers: %d\n", total_sum);

    return 0;
}
