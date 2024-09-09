#include <stdio.h>
#include <omp.h>

int main() {
    // Define the number of family members
    const int num_members = 5;
    
    // Names of family members
    char* names[] = {"A", "B", "C", "D", "E"};
    
    // Job IDs for each family member
    int job_ids[] = {101, 102, 103, 104, 105};
    
    // Use OpenMP to create parallel threads
    #pragma omp parallel num_threads(num_members)
    {
        int thread_id = omp_get_thread_num(); // Get the thread ID
        
        // Each thread prints its assigned name and job ID
        printf("Name: %s, Job ID: %d, Printed by thread: %d\n", names[thread_id], job_ids[thread_id], thread_id);
    }
    
    return 0;
}
