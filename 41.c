/* Program Number: 41
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program creates a message queue and prints the key and message queue ID.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok(".", 'A');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // Create message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID : %d\n", msgid);

    return 0;
}
