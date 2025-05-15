/* Program Number: 36d
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program creates a FIFO file using the mknod system call directly in C.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    const char *fifo_name = "my_fifo_syscall";

    // Create FIFO using mknod system call with S_IFIFO and 0666 permission
    if (mknod(fifo_name, S_IFIFO | 0666, 0) == -1)
    {
        perror("mknod system call");
        exit(1);
    }

    printf("FIFO file %s created successfully using mknod system call.\n", fifo_name);

    return 0;
}
