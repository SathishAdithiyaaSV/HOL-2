/* Program Number: 61a
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGSEGV (Segmentation fault) using the sigaction system call.
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
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL);

    int *ptr = NULL;
    *ptr = 42; // This will cause a segmentation fault
    return 0;
}
