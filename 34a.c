/* Program Number: 34a
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program executes ls -l | wc using dup.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    int pid;

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

    if (pid == 0)
    {
        // Child process: wc
        close(pipefd[1]);
        close(0); // Close stdin
        dup(pipefd[0]); // Replace stdin with read end of pipe
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(1);
    }
    else
    {
        // Parent process: ls -l
        close(pipefd[0]);
        close(1); // Close stdout
        dup(pipefd[1]); // Replace stdout with write end of pipe
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }

    return 0;
}
