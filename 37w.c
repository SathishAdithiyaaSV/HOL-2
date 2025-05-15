/* Program Number: 37 (Writer)
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program writes a message into a FIFO file using one-way communication.
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
    char message[] = "Hello from writer process\n";

    // Create FIFO if it does not exist
    if (mkfifo(fifo_name, 0666) == -1)
    {
        perror("mkfifo");
        // If it already exists, continue
    }

    // Open FIFO for writing
    fd = open(fifo_name, O_WRONLY);
    if (fd == -1)
    {
        perror("open for write");
        exit(1);
    }

    write(fd, message, sizeof(message));
    close(fd);

    printf("Writer: Message sent to FIFO.\n");

    return 0;
}
