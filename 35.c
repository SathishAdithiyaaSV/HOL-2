/* Program Number: 35
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program counts number of directories using ls -l | grep ^d | wc and redirects using dup2.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    int pipe1[2]; // For ls -l | grep ^d
    int pipe2[2]; // For grep ^d | wc
    pid_t pid1, pid2;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0)
    {
        // First child: executes ls -l
        dup2(pipe1[1], 1); // stdout → pipe1 write
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }

    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0)
    {
        // Second child: executes grep ^d
        dup2(pipe1[0], 0); // stdin ← pipe1 read
        dup2(pipe2[1], 1); // stdout → pipe2 write
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("grep", "grep", "^d", (char *)NULL);
        perror("execlp grep");
        exit(1);
    }

    // Parent: executes wc
    dup2(pipe2[0], 0); // stdin ← pipe2 read
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    execlp("wc", "wc", (char *)NULL);
    perror("execlp wc");
    exit(1);
}
