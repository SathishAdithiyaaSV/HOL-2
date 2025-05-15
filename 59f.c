/* Program Number: 59f
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program catches SIGVTALRM signal using the setitimer system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int signum)
{
    printf("Caught SIGVTALRM signal!\n");
    exit(0);  // Exit after catching signal
}

int main()
{
    struct itimerval timer;
    
    signal(SIGVTALRM, handler);
    
    // Set timer to expire after 5 seconds of user CPU time
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    printf("Busy loop started to consume user-mode CPU time...\n");

    // Busy loop to consume user time
    while (1)
    {
        for (int i = 0; i < 1000000; i++)
        {
            // Do some CPU-bound work
            double x = i * 1.1;
        }
    }

    return 0;
}
