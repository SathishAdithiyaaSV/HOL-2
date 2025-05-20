/* Program Number: 64a
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program waits for the SIGSTOP signal and handles it. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    printf("Caught SIGSTOP signal!\n");
}

int main()
{
    signal(SIGSTOP, handler);
    printf("Waiting for SIGSTOP signal...\n");
    while(1); // Infinite loop to wait for the signal
    return 0;
}
