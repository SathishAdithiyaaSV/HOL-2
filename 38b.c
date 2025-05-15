/* Program Number: 38 (Process 2)
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program communicates with another process using two-way FIFO communication.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";
    int fd_write, fd_read;
    char write_msg[] = "Hello from Process 2\n";
    char read_msg[100];

    // FIFOs already created by process1

    // Open fifo2 for writing and fifo1 for reading
    fd_read = open(fifo1, O_RDONLY);
    fd_write = open(fifo2, O_WRONLY);

    // Send message
    write(fd_write, write_msg, sizeof(write_msg));
    printf("Process 2: Sent message: %s", write_msg);

    // Receive message
    read(fd_read, read_msg, sizeof(read_msg));
    printf("Process 2: Received message: %s", read_msg);

    close(fd_write);
    close(fd_read);

    return 0;
}
