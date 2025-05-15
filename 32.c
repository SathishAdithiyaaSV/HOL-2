/* Program Number: 32
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program sends data from parent process to child process using pipe.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    char message[] = "Message from Parent to Child";
    char buffer[100];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid > 0)
    {
        // Parent process
        close(pipefd[0]); // Close read end
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]); // Close write end
    }
    else
    {
        // Child process
        close(pipefd[1]); // Close write end
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]); // Close read end
    }

    return 0;
}
