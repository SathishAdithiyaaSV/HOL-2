/* Program Number: 34b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program executes ls -l | wc using dup2 for redirection.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
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
        // Child process: execute wc
        close(pipefd[1]); // Close write end
        dup2(pipefd[0], 0); // Redirect stdin to read end of pipe
        close(pipefd[0]);

        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    }
    else
    {
        // Parent process: execute ls -l
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], 1); // Redirect stdout to write end of pipe
        close(pipefd[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }

    return 0;
}
