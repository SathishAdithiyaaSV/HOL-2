/* Program Number: 33
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program enables two-way communication between parent and child using two pipes.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    int pipe1[2]; // Parent to Child
    int pipe2[2]; // Child to Parent
    pid_t pid;
    char parent_msg[] = "Hello Child";
    char child_msg[] = "Hello Parent";
    char buffer[100];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
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
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    }
    else
    {
        // Child process
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        write(pipe2[1], child_msg, strlen(child_msg) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}
