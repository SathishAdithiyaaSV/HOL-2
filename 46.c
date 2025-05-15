/* Program Number: 46
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program removes the message queue.
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

    // Get message queue ID
    msgid = msgget(key, 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}
