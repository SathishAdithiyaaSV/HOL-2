/* Program Number: 40
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program prints the maximum number of files a process can open and the default pipe size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/resource.h>
#include <errno.h>
#define _GNU_SOURCE

#ifndef F_GETPIPE_SZ
#define F_GETPIPE_SZ 1032
#endif


int main()
{
    struct rlimit lim;
    int pipefd[2];
    int pipe_size;

    // Get maximum number of open files per process
    if (getrlimit(RLIMIT_NOFILE, &lim) == -1)
    {
        perror("getrlimit");
        exit(1);
    }

    printf("Maximum number of files a process can open: %lu\n", (unsigned long)lim.rlim_cur);

    // Create a pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Get pipe size using fcntl
    pipe_size = fcntl(pipefd[1], F_GETPIPE_SZ);
    if (pipe_size == -1)
    {
        perror("fcntl");
        exit(1);
    }

    printf("Default pipe size (circular buffer): %d bytes\n", pipe_size);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
