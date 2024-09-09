#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Series of 2: ");
            for (int i = 1; i <= 5; i++) {
                printf("%d ", 2 * i);
            }
            printf("\n");
        }

        #pragma omp section
        {
            printf("Series of 4: ");
            for (int i = 1; i <= 5; i++) {
                printf("%d ", 4 * i);
            }
            printf("\n");
        }
    }

    return 0;
}
