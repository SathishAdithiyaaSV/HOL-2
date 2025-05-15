/* Program Number: 36e
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program creates a FIFO file using the mkfifo library function.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
    const char *fifo_name = "my_fifo_lib";

    // Create FIFO using mkfifo library function with 0666 permission
    if (mkfifo(fifo_name, 0666) == -1)
    {
        perror("mkfifo library function");
        exit(1);
    }

    printf("FIFO file %s created successfully using mkfifo library function.\n", fifo_name);

    return 0;
}
