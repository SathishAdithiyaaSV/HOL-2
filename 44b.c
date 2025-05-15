/* Program Number: 44b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program receives messages from the message queue with IPC_NOWAIT flag.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msgbuf
{
    long mtype;
    char mtext[100];
};

int main()
{
    key_t key;
    int msgid;
    struct msgbuf message;

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

    // Receive message with IPC_NOWAIT flag (non-blocking)
    if (msgrcv(msgid, &message, sizeof(message.mtext), 0, IPC_NOWAIT) == -1)
    {
        if (errno == ENOMSG)
        {
            printf("No messages available in the queue.\n");
        }
        else
        {
            perror("msgrcv");
            exit(1);
        }
    }
    else
    {
        printf("Received Message: %s\n", message.mtext);
    }

    return 0;
}
