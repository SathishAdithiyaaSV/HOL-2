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
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(sock);
        exit(1);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(sock);
        exit(1);
    }

    // Send message to server
    strcpy(buffer, "Hello, Server!");
    send(sock, buffer, strlen(buffer), 0);
    printf("Message sent to server: %s\n", buffer);

    // Receive server response
    recv(sock, buffer, BUF_SIZE, 0);
    printf("Received from server: %s\n", buffer);

    // Close socket
    close(sock);

    return 0;
}
