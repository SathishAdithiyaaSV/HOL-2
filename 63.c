/* Program Number: 63
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program creates an orphan process by terminating the parent process
             using a SIGKILL signal from the child process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) // Child process
    {
        // Wait a moment before sending SIGKILL to the parent
        sleep(2);  // Make sure the parent is running first
        printf("Child Process: My Parent ID: %d\n", getppid());

        // Send SIGKILL to the parent process
        printf("Child Process: Sending SIGKILL to parent process (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);  // Kill the parent process

        // After the parent dies, the child becomes an orphan
        sleep(2); // Wait to see the change in parent PID
        printf("Child Process: Now My Parent ID is: %d\n", getppid());
    }
    else if (pid > 0) // Parent process
    {
        printf("Parent Process: My PID: %d\n", getpid());
        // Parent will wait here until killed
        while (1)
        {
            // Parent will wait for termination by the child process
        }
    }
    else
    {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
