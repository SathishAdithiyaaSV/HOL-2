/* Program Number: 62
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program ignores SIGINT signal and then resets it to default action using the sigaction system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    printf("Caught SIGINT signal!\n");
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // Ignore SIGINT signal
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT signal ignored. Try pressing Ctrl+C\n");
    sleep(5); // Wait for 5 seconds

    sa.sa_handler = handler; // Reset to catch SIGINT signal
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT signal will now be handled. Try pressing Ctrl+C\n");
    sleep(5); // Wait for 5 seconds

    return 0;
}
