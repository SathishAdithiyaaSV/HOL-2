/* Program Number: 54
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program prints the system resource limits using the getrlimit system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rl;

    // Get resource limit for maximum number of open file descriptors
    if (getrlimit(RLIMIT_NOFILE, &rl) == 0)
    {
        printf("Maximum number of open file descriptors: %ld\n", rl.rlim_max);
    }
    else
    {
        perror("Error getting resource limit");
    }

    return 0;
}
