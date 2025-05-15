/* Program Number: 56
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program measures the time taken to execute 100 getppid() system calls.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
    clock_t start_time, end_time;
    start_time = clock();

    for (int i = 0; i < 100; i++)
    {
        getppid(); // Call getppid system call
    }

    end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to execute 100 getppid() system calls: %f seconds\n", time_taken);

    return 0;
}
