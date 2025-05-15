/* Program Number: 61b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGINT (Interrupt) signal using the sigaction system call.
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
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    while(1); // Infinite loop to keep the program running until interrupted
    return 0;
}
