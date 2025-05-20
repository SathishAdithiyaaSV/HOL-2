/* Program Number: 53c
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program sets an interval timer for 10 seconds using ITIMER_PROF.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h> 

void timer_handler(int signum)
{
    printf("Timer expired after 10 seconds using ITIMER_PROF\n");
}

int main()
{
    struct itimerval timer;
    timer.it_value.tv_sec = 10; // 10 seconds
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0; // One-time timer
    timer.it_interval.tv_usec = 0;

    signal(SIGPROF, timer_handler);
    setitimer(ITIMER_PROF, &timer, NULL);

    printf("Timer set for 10 seconds using ITIMER_PROF\n");
    sleep(12); // Sleep to allow the timer to expire
    return 0;
}
