/* Program Number: 45
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program changes the existing message queue permissions using the msqid_ds structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>

struct msgbuf
{
    long mtype;
    char mtext[100];
};

int main()
{
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate unique key
    key = ftok(".", 'A');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // Get message queue ID
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // Get current queue info
    if (msgctl(msgid, IPC_STAT, &info) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    // Change the permissions to read-write for user, group, and others
    info.msg_perm.mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    
    // Set the new permissions
    if (msgctl(msgid, IPC_SET, &info) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue permissions changed successfully.\n");

    return 0;
}
