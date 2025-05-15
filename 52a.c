/* Program Number: 52a
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates creating a concurrent server using fork().
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

// Function to handle client communication
void handle_client(int client_socket)
{
    char buffer[BUF_SIZE];

    // Receive message from client
    recv(client_socket, buffer, BUF_SIZE, 0);
    printf("Received from client: %s\n", buffer);

    // Send response to client
    strcpy(buffer, "Message received by server.");
    send(client_socket, buffer, strlen(buffer), 0);

    // Close the client socket
    close(client_socket);
}

int main()
{
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

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

    // Accept and handle clients concurrently
    while (1)
    {
        // Accept client connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) == -1)
        {
            perror("accept");
            close(server_fd);
            exit(1);
        }

        // Fork a new process to handle the client
        pid_t pid = fork();
        if (pid == 0)
        {
            // In the child process, handle the client
            close(server_fd); // Close the server socket in the child process
            handle_client(client_socket);
            exit(0); // Child process exits after handling the client
        }
        else if (pid < 0)
        {
            perror("fork");
            close(client_socket);
        }
        else
        {
            // In the parent process, continue accepting other clients
            close(client_socket);
        }
    }

    // Close the server socket
    close(server_fd);

    return 0;
}
