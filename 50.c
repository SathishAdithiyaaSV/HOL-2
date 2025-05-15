/* Program Number: 50
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates a deadlock scenario using semaphores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#define SEM_KEY_1 1234
#define SEM_KEY_2 5678

// Union required by semctl
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Function to perform P (wait) operation
void sem_wait(int semid, int semnum) {
    struct sembuf sb = {semnum, -1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (wait)");
        exit(EXIT_FAILURE);
    }
}

// Function to perform V (signal) operation
void sem_signal(int semid, int semnum) {
    struct sembuf sb = {semnum, 1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop (signal)");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int semid1, semid2;

    // Create two semaphores with 1 semaphore each
    semid1 = semget(SEM_KEY_1, 1, IPC_CREAT | 0666);
    if (semid1 == -1) {
        perror("semget (semid1)");
        exit(EXIT_FAILURE);
    }

    semid2 = semget(SEM_KEY_2, 1, IPC_CREAT | 0666);
    if (semid2 == -1) {
        perror("semget (semid2)");
        exit(EXIT_FAILURE);
    }

    // Initialize both semaphores to 1 (binary semaphores)
    union semun sem_attr;
    sem_attr.val = 1;

    if (semctl(semid1, 0, SETVAL, sem_attr) == -1) {
        perror("semctl (set semid1)");
        exit(EXIT_FAILURE);
    }

    if (semctl(semid2, 0, SETVAL, sem_attr) == -1) {
        perror("semctl (set semid2)");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child: trying to lock semaphore 1...\n");
        sem_wait(semid1, 0);
        sleep(1);  // Simulate time delay to cause deadlock

        printf("Child: trying to lock semaphore 2...\n");
        sem_wait(semid2, 0);

        printf("Child: inside critical section.\n");
        sleep(2);

        printf("Child: releasing semaphores.\n");
        sem_signal(semid2, 0);
        sem_signal(semid1, 0);

        exit(0);
    } else {
        // Parent process
        printf("Parent: trying to lock semaphore 2...\n");
        sem_wait(semid2, 0);
        sleep(1);  // Simulate time delay to cause deadlock

        printf("Parent: trying to lock semaphore 1...\n");
        sem_wait(semid1, 0);

        printf("Parent: inside critical section.\n");
        sleep(2);

        printf("Parent: releasing semaphores.\n");
        sem_signal(semid1, 0);
        sem_signal(semid2, 0);

        // Wait for child process before cleanup
        wait(NULL);

        // Remove both semaphores
        if (semctl(semid1, 0, IPC_RMID) == -1) {
            perror("semctl (remove semid1)");
            exit(EXIT_FAILURE);
        }

        if (semctl(semid2, 0, IPC_RMID) == -1) {
            perror("semctl (remove semid2)");
            exit(EXIT_FAILURE);
        }

        printf("Semaphores removed successfully.\n");
    }

    return 0;
}
