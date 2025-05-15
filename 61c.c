/* Program Number: 61c
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGFPE (Floating point exception) signal using the sigaction system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Caught SIGFPE (Floating point exception) signal!\n");
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGFPE, &sa, NULL);

    int a = 0;
    int b = 1 / a;  // This will cause a floating-point exception (divide by zero)
    return 0;
}
