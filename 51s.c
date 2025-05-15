/* Program Number: 51
Student Name: Sathish Adithiyaa SV; Register Number: IMT2023030
Date: 11-5-2025
Description: This program demonstrates inter-machine communication using sockets.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main()
{
    int server_fd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
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

    // Accept incoming connections
    if ((new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) == -1)
    {
        perror("accept");
        close(server_fd);
        exit(1);
    }

    printf("Connection established with client.\n");

    // Receive message from client
    recv(new_sock, buffer, BUF_SIZE, 0);
    printf("Received from client: %s\n", buffer);

    // Send response to client
    strcpy(buffer, "Message received by server.");
    send(new_sock, buffer, strlen(buffer), 0);

    // Close the sockets
    close(new_sock);
    close(server_fd);

    return 0;
}
