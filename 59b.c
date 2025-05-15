/* Program Number: 59b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGINT (Interrupt) signal using signal system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Caught SIGINT (Interrupt) signal!\n");
}

int main()
{
    signal(SIGINT, handler);
    printf("Press Ctrl+C to send SIGINT signal\n");

    while (1)
    {
        // Infinite loop waiting for SIGINT
    }

    return 0;
}
