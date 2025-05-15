/* Program Number: 48
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates the creation and initialization of a binary and counting semaphore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int main()
{
    key_t key;
    int semid;

    // Generate unique key
    key = ftok(".", 'A');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // Create a semaphore set with 2 semaphores
    semid = semget(key, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphores
    // Binary semaphore (value 1)
    if (semctl(semid, 0, SETVAL, 1) == -1)
    {
        perror("semctl (binary semaphore)");
        exit(1);
    }

    // Counting semaphore (value 5)
    if (semctl(semid, 1, SETVAL, 5) == -1)
    {
        perror("semctl (counting semaphore)");
        exit(1);
    }

    printf("Binary semaphore initialized to 1.\n");
    printf("Counting semaphore initialized to 5.\n");

    // Cleanup: Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl (remove)");
        exit(1);
    }

    printf("Semaphore set removed successfully.\n");

    return 0;
}
