/* Program Number: 43
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program sends a message to the message queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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

    // Create or access the message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // Set message details
    message.mtype = 1;
    printf("Enter message to send: ");
    fgets(message.mtext, sizeof(message.mtext), stdin);

    // Remove newline if present
    int len = strlen(message.mtext);
    if (message.mtext[len - 1] == '\n')
    {
        message.mtext[len - 1] = '\0';
    }

    // Send message
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1)
    {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent to message queue.\n");

    return 0;
}
