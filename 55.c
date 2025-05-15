/* Program Number: 55
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program sets the system resource limit using the setrlimit system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rl;
    rl.rlim_cur = 1024; // Soft limit
    rl.rlim_max = 2048; // Hard limit

    // Set the resource limit for the maximum number of open file descriptors
    if (setrlimit(RLIMIT_NOFILE, &rl) == 0)
    {
        printf("System resource limit for open files set successfully\n");
    }
    else
    {
        perror("Error setting resource limit");
    }

    return 0;
}
