/* Program Number: 64b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program sends SIGSTOP signal to a process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    int target_pid;
    scanf("%d", &target_pid);
    printf("Sending SIGSTOP to the process with PID: %d\n", target_pid);
    kill(target_pid, SIGSTOP); // Send SIGSTOP to the parent process
    return 0;
}
