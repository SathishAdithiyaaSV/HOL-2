/* Program Number: 47
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates the creation, writing, attaching, detaching, and removal of shared memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

#define SHM_SIZE 1024  // Define the shared memory size

int main()
{
    key_t key;
    int shm_id;
    char *shm_ptr;

    // Generate unique key
    key = ftok(".", 'A');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // Create shared memory
    shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Write data to shared memory
    printf("Writing to shared memory...\n");
    strcpy(shm_ptr, "This is some data in shared memory.");
    printf("Data written: %s\n", shm_ptr);

    // Attach with O_RDONLY and check if overwrite is possible
    char *shm_ptr_ro = (char *)shmat(shm_id, NULL, SHM_RDONLY);
    if (shm_ptr_ro == (char *)-1)
    {
        perror("shmat (readonly)");
        exit(1);
    }
    printf("Trying to overwrite data with read-only access (this will fail)...\n");
    // Attempt to overwrite, which will fail in read-only mode
    strcpy(shm_ptr_ro, "Attempt to overwrite in read-only memory"); // This should fail

    // Detach shared memory
    if (shmdt(shm_ptr) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    // Detach read-only shared memory
    if (shmdt(shm_ptr_ro) == -1)
    {
        perror("shmdt (readonly)");
        exit(1);
    }

    // Remove shared memory
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(1);
    }

    printf("Shared memory operations completed successfully.\n");

    return 0;
}
