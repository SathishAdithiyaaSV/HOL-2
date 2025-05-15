/* Program Number: 59d
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGALRM signal using the alarm system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    printf("Caught SIGALRM signal!\n");
}

int main()
{
    signal(SIGALRM, handler);
    
    alarm(5); // Set an alarm for 5 seconds
    
    printf("Waiting for SIGALRM signal for 5 seconds...\n");
    pause(); // Wait for the signal
    
    return 0;
}
