/* Program Number: 59g
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGPROF signal using the setitimer system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int signum)
{
    printf("Caught SIGPROF signal!\n");
    exit(0); // Exit after catching the signal
}

int main()
{
    struct itimerval timer;
    
    signal(SIGPROF, handler);
    
    timer.it_value.tv_sec = 5;  // Timer set for 5s of CPU time
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);
    
    printf("Busy loop started to consume CPU (user + kernel) time...\n");

    // Loop to keep CPU busy
    while (1)
    {
        for (int i = 0; i < 1000000; i++)
        {
            double x = i * 3.14159; // simulate work
        }
    }

    return 0;
}
