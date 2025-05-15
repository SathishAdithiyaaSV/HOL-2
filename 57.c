/* Program Number: 57
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program prints system limitations using sysconf and other related system calls.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // Maximum length of arguments in the exec family of functions
    printf("Maximum length of arguments: %ld\n", sysconf(_SC_ARG_MAX));

    // Maximum number of simultaneous processes per user ID
    printf("Maximum number of simultaneous processes: %ld\n", sysconf(_SC_CHILD_MAX));

    // Number of clock ticks (jiffies) per second
    printf("Number of clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));

    // Maximum number of open files
    printf("Maximum number of open files: %ld\n", sysconf(_SC_OPEN_MAX));

    // Size of a page
    printf("Size of a page: %ld bytes\n", sysconf(_SC_PAGE_SIZE));

    // Total number of pages in physical memory
    printf("Total number of pages in physical memory: %ld\n", sysconf(_SC_PHYS_PAGES));

    // Number of currently available pages in physical memory
    printf("Number of available pages in physical memory: %ld\n", sysconf(_SC_AVPHYS_PAGES));

    return 0;
}
