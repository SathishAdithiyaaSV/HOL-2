/* Program Number: 60
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program ignores SIGINT signal and then resets it to default action. 
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
    signal(SIGINT, SIG_IGN); // Ignore SIGINT signal
    printf("SIGINT signal ignored. Try pressing Ctrl+C\n");
    sleep(5); // Wait for 5 seconds

    signal(SIGINT, handler); // Reset to default action to catch SIGINT
    printf("SIGINT signal will now be handled. Try pressing Ctrl+C\n");
    sleep(5); // Wait for 5 seconds

    return 0;
}
