/* Program Number: 36b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates FIFO file creation using mkfifo command.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
    const char *fifo_name = "my_fifo";

    // Creating FIFO file using mkfifo
    if (mkfifo(fifo_name, 0666) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    printf("FIFO file %s created successfully using mkfifo.\n", fifo_name);

    return 0;
}
