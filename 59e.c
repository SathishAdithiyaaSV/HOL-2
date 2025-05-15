/* Program Number: 59e
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGALRM signal using the setitimer system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int signum)
{
    printf("Caught SIGALRM signal!\n");
}

int main()
{
    struct itimerval timer;
    
    signal(SIGALRM, handler);
    
    timer.it_value.tv_sec = 5;  // 5 seconds
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
    
    printf("Waiting for SIGALRM signal for 5 seconds...\n");
    pause(); // Wait for the signal
    
    return 0;
}
