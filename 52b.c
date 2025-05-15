/* Program Number: 52b
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates creating a concurrent server using pthread_create().
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUF_SIZE 1024

// Function to handle client communication in a thread
void *handle_client(void *client_socket_ptr)
{
    int client_socket = *((int *)client_socket_ptr);
    char buffer[BUF_SIZE];

    // Receive message from client
    recv(client_socket, buffer, BUF_SIZE, 0);
    printf("Received from client: %s\n", buffer);

    // Send response to client
    strcpy(buffer, "Message received by server.");
    send(client_socket, buffer, strlen(buffer), 0);

    // Close the client socket
    close(client_socket);

    return NULL;
}

int main()
{
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the server socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1)
    {
        perror("listen");
        close(server_fd);
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept and handle clients concurrently using pthread
    while (1)
    {
        // Accept client connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) == -1)
        {
            perror("accept");
            close(server_fd);
            exit(1);
        }

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, &client_socket) != 0)
        {
            perror("pthread_create");
            close(client_socket);
        }

        // Detach the thread so that it can clean up its resources automatically
        pthread_detach(thread_id);
    }

    // Close the server socket
    close(server_fd);

    return 0;
}
