/* Program Number: 42
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program prints information about a message queue using msqid_ds and ipc_perm structures.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main()
{
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate key
    key = ftok(".", 'A');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // Get message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // Get info about the queue
    if (msgctl(msgid, IPC_STAT, &info) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    printf("Access Permissions (mode): %o\n", info.msg_perm.mode);
    printf("UID: %d\n", info.msg_perm.uid);
    printf("GID: %d\n", info.msg_perm.gid);
    printf("Time of last msgsnd: %s", ctime(&info.msg_stime));
    printf("Time of last msgrcv: %s", ctime(&info.msg_rtime));
    printf("Time of last change : %s", ctime(&info.msg_ctime));
    printf("Current number of bytes in queue: %lu\n", info.__msg_cbytes);
    printf("Number of messages in queue    : %lu\n", info.msg_qnum);
    printf("Maximum bytes allowed in queue : %lu\n", info.msg_qbytes);
    printf("PID of last msgsnd             : %d\n", info.msg_lspid);
    printf("PID of last msgrcv             : %d\n", info.msg_lrpid);

    return 0;
}
