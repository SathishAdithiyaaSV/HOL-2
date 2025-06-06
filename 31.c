/* Program Number: 31
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates creation of a pipe, writing to it, reading from it, and displaying the output.
*/
//Test commit

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    int result;
    char write_msg[] = "Hello from pipe!";
    char read_msg[100];

    result = pipe(pipefd);
    if (result == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Writing to pipe
    write(pipefd[1], write_msg, strlen(write_msg) + 1);

    // Reading from pipe
    read(pipefd[0], read_msg, sizeof(read_msg));

    // Display content
    printf("Data read from pipe: %s\n", read_msg);

    return 0;
}
