/* Program Number: 36a
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates FIFO file creation using mknod command.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    const char *fifo_name = "my_fifo";

    // Creating FIFO file using mknod
    if (mknod(fifo_name, S_IFIFO | 0666, 0) == -1)
    {
        perror("mknod");
        exit(1);
    }

    printf("FIFO file %s created successfully using mknod.\n", fifo_name);

    return 0;
}
