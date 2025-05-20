/* Program Number: 49
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates the use of System V semaphores for mutual exclusion
             between a parent and child process in accessing a critical section.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#define TICKET_FILE "ticket.txt"
#define SEM_KEY_BINARY 0x1234
#define SEM_KEY_COUNTING 0x5678

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Function prototypes
void sem_wait(int semid);
void sem_signal(int semid);
void initialize_ticket();
void reserve_ticket();
void access_resource();
void remove_semaphores();
void check_semaphore_status();

// Semaphore wait
void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop wait");
        exit(1);
    }
}

// Semaphore signal
void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop signal");
        exit(1);
    }
}

// Option 1: Initialize ticket file
void initialize_ticket() {
    int fd = open(TICKET_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    char init[] = "0\n";
    write(fd, init, strlen(init));
    close(fd);
    write(STDOUT_FILENO, "Ticket file initialized to 0.\n", 30);
}

// Option 2: Reserve ticket (uses binary semaphore and file lock)
void reserve_ticket() {
    int semid = semget(SEM_KEY_BINARY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Only initialize if necessary - check current value first
    int current_val = semctl(semid, 0, GETVAL);
    if (current_val <= 0) {
        union semun su;
        su.val = 1;
        if (semctl(semid, 0, SETVAL, su) == -1) {
            perror("semctl");
            exit(1);
        }
    }

    sem_wait(semid);

    int fd = open(TICKET_FILE, O_RDWR);
    if (fd < 0) {
        perror("open");
        sem_signal(semid);
        exit(1);
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(fd, F_SETLKW, &lock);

    char buf[16] = {0};
    read(fd, buf, sizeof(buf));
    int ticket_no = atoi(buf);
    ticket_no++;

    lseek(fd, 0, SEEK_SET);
    snprintf(buf, sizeof(buf), "%d\n", ticket_no);
    write(fd, buf, strlen(buf));

    char msg[64];
    snprintf(msg, sizeof(msg), "Ticket Reserved: Your Ticket Number is %d\n", ticket_no);
    write(STDOUT_FILENO, msg, strlen(msg));

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);
    sem_signal(semid);
}

// Option 3: Access resource with counting semaphore (allows 2 concurrent accesses)
void access_resource() {
    // First check if semaphore already exists
    int semid = semget(SEM_KEY_COUNTING, 1, 0666);
    
    // If semaphore doesn't exist, create and initialize it
    if (semid == -1) {
        if (errno == ENOENT) {  // Doesn't exist yet
            semid = semget(SEM_KEY_COUNTING, 1, IPC_CREAT | 0666);
            if (semid == -1) {
                perror("semget create");
                exit(1);
            }
            
            // Initialize to 2 as we're creating it for the first time
            union semun su;
            su.val = 2;  // allow 2 processes
            if (semctl(semid, 0, SETVAL, su) == -1) {
                perror("semctl set initial value");
                exit(1);
            }
            printf("Counting semaphore created and initialized to allow 2 concurrent processes\n");
        } else {
            perror("semget check");
            exit(1);
        }
    }

    printf("Process %d waiting to access resource...\n", getpid());
    sem_wait(semid);
    
    int current_val = semctl(semid, 0, GETVAL);
    printf("Process %d entered critical section. Current semaphore value: %d\n", 
           getpid(), current_val);

    char msg[64];
    snprintf(msg, sizeof(msg), "Process %d using resource...\n", getpid());
    write(STDOUT_FILENO, msg, strlen(msg));

    sleep(500); // reduced sleep time for testing

    snprintf(msg, sizeof(msg), "Process %d done. Releasing resource.\n", getpid());
    write(STDOUT_FILENO, msg, strlen(msg));

    sem_signal(semid);
    printf("Resource released by process %d\n", getpid());
}

// Option 4: Remove semaphores
void remove_semaphores() {
    int sem1 = semget(SEM_KEY_BINARY, 1, 0666);
    if (sem1 != -1) {
        if (semctl(sem1, 0, IPC_RMID) == -1) {
            perror("Error removing binary semaphore");
        } else {
            printf("Binary semaphore removed.\n");
        }
    } else {
        printf("Binary semaphore does not exist or cannot be accessed.\n");
    }

    int sem2 = semget(SEM_KEY_COUNTING, 1, 0666);
    if (sem2 != -1) {
        if (semctl(sem2, 0, IPC_RMID) == -1) {
            perror("Error removing counting semaphore");
        } else {
            printf("Counting semaphore removed.\n");
        }
    } else {
        printf("Counting semaphore does not exist or cannot be accessed.\n");
    }
}

// Option 5: Check semaphore status (for debugging)
void check_semaphore_status() {
    int sem1 = semget(SEM_KEY_BINARY, 1, 0666);
    if (sem1 != -1) {
        int val = semctl(sem1, 0, GETVAL);
        printf("Binary semaphore exists. Current value: %d\n", val);
    } else {
        printf("Binary semaphore does not exist or cannot be accessed.\n");
    }

    int sem2 = semget(SEM_KEY_COUNTING, 1, 0666);
    if (sem2 != -1) {
        int val = semctl(sem2, 0, GETVAL);
        printf("Counting semaphore exists. Current value: %d\n", val);
        printf("This means %d more processes can enter the critical section.\n", val);
    } else {
        printf("Counting semaphore does not exist or cannot be accessed.\n");
    }
}

int main() {
    int choice;
    printf("\nTicket Reservation System\n---------------------------\n");
    printf("1. Initialize ticket file\n");
    printf("2. Reserve a ticket (with semaphore)\n");
    printf("3. Access shared resource (counting semaphore)\n");
    printf("4. Remove semaphores\n");
    printf("5. Check semaphore status\n"); // Added option
    printf("Enter choice (1-5): ");

    scanf("%d", &choice);

    switch (choice) {
        case 1: initialize_ticket(); break;
        case 2: reserve_ticket(); break;
        case 3: access_resource(); break;
        case 4: remove_semaphores(); break;
        case 5: check_semaphore_status(); break; // Added option
        default: printf("Invalid choice\n");
    }

    return 0;
}