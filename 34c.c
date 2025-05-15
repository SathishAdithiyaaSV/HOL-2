/* Program Number: 34c
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program executes ls -l | wc using fcntl system call to duplicate file descriptors.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t pid;

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
        // Child process: executes wc
        close(pipefd[1]); // Close write end of pipe

        close(0); // Close stdin
        if (fcntl(pipefd[0], F_DUPFD, 0) != 0) // Duplicate pipefd[0] to 0 (stdin)
        {
            perror("fcntl (child)");
            exit(1);
        }

        close(pipefd[0]); // Close original pipefd[0] after duplication

        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    }
    else
    {
        // Parent process: executes ls -l
        close(pipefd[0]); // Close read end of pipe

        close(1); // Close stdout
        if (fcntl(pipefd[1], F_DUPFD, 1) != 1) // Duplicate pipefd[1] to 1 (stdout)
        {
            perror("fcntl (parent)");
            exit(1);
        }

        close(pipefd[1]); // Close original pipefd[1] after duplication

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }

    return 0;
}
