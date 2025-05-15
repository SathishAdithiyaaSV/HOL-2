/* Program Number: 59a
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGSEGV (Segmentation Fault) signal using signal system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Caught SIGSEGV (Segmentation fault) signal!\n");
}

int main()
{
    signal(SIGSEGV, handler);

    int *ptr = NULL;
    *ptr = 42; // This will cause a segmentation fault
    return 0;
}
