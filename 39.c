/* Program Number: 39
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program waits for data in a FIFO within 10 seconds using the select system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    const char *fifo_name = "select_fifo";
    int fd;
    char buffer[100];
    fd_set read_fds;
    struct timeval timeout;

    // Create the FIFO
    if (mkfifo(fifo_name, 0666) == -1)
    {
        perror("mkfifo");
        // Continue even if it exists
    }

    // Open FIFO for reading (non-blocking)
    fd = open(fifo_name, O_RDONLY | O_NONBLOCK);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    timeout.tv_sec = 10;  // 10 seconds timeout
    timeout.tv_usec = 0;

    printf("Waiting for data in FIFO for up to 10 seconds...\n");

    int retval = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (retval == -1)
    {
        perror("select");
        exit(1);
    }
    else if (retval == 0)
    {
        printf("Timeout occurred. No data in FIFO.\n");
    }
    else
    {
        if (FD_ISSET(fd, &read_fds))
        {
            int bytes = read(fd, buffer, sizeof(buffer));
            if (bytes > 0)
            {
                printf("Received data: %.*s", bytes, buffer);
            }
            else
            {
                printf("No data read from FIFO.\n");
            }
        }
    }

    close(fd);
    return 0;
}
