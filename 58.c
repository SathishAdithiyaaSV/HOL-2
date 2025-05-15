/* Program Number: 58
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program creates three threads and prints their IDs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_thread_id(void* arg)
{
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t threads[3];

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&threads[i], NULL, print_thread_id, NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
