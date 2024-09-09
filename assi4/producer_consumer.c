#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;

void producer() {
    int item = 0;
    while (item < 20) {
        #pragma omp critical
        {
            if (count < BUFFER_SIZE) {
                buffer[in] = item;
                printf("Produced item: %d\n", item);
                in = (in + 1) % BUFFER_SIZE;
                count++;
                item++;
            }
        }
    }
}

void consumer() {
    int item = 0;
    while (item < 20) {
        #pragma omp critical
        {
            if (count > 0) {
                item = buffer[out];
                printf("Consumed item: %d\n", item);
                out = (out + 1) % BUFFER_SIZE;
                count--;
            }
        }
    }
}

int main() {
    // Parallel region with sections for producer and consumer
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            producer();
        }
        
        #pragma omp section
        {
            consumer();
        }
    }
    
    return 0;
}
