/* Program Number: 49
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates the use of System V semaphores for mutual exclusion
             between a parent and child process in accessing a critical section.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Define union semun for semctl
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait(int semid)
{
    struct sembuf sb = {0, -1, 0}; // P operation
    if (semop(semid, &sb, 1) == -1)
    {
        perror("semop (wait)");
        exit(1);
    }
}

void sem_signal(int semid)
{
    struct sembuf sb = {0, 1, 0}; // V operation
    if (semop(semid, &sb, 1) == -1)
    {
        perror("semop (signal)");
        exit(1);
    }
}

int main()
{
    key_t key;
    int semid;

    // Generate unique key
    key = ftok(".", 'S');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // Create semaphore with 1 semaphore in the set
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget");
        exit(1);
    }

    // Initialize semaphore to 1
    union semun sem_attr;
    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1)
    {
        perror("semctl (SETVAL)");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child Process
        printf("Child process attempting to enter critical section...\n");
        sem_wait(semid);
        printf("Child process inside critical section.\n");
        sleep(2); // simulate work
        printf("Child process leaving critical section.\n");
        sem_signal(semid);
        exit(0);
    }
    else
    {
        // Parent Process
        sleep(1); // allow child to enter first
        printf("Parent process attempting to enter critical section...\n");
        sem_wait(semid);
        printf("Parent process inside critical section.\n");
        sleep(2); // simulate work
        printf("Parent process leaving critical section.\n");
        sem_signal(semid);

        // Wait for child to finish
        wait(NULL);

        // Remove semaphore
        if (semctl(semid, 0, IPC_RMID) == -1)
        {
            perror("semctl (IPC_RMID)");
            exit(1);
        }

        printf("Semaphore removed successfully.\n");
    }

    return 0;
}
