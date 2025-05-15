/* Program Number: 37 (Reader)
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program reads a message from a FIFO file using one-way communication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    const char *fifo_name = "my_fifo_oneway";
    int fd;
    char buffer[100];

    // Open FIFO for reading
    fd = open(fifo_name, O_RDONLY);
    if (fd == -1)
    {
        perror("open for read");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Reader: Received message: %s", buffer);
    close(fd);

    return 0;
}
