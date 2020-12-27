/*
 * STDIN Client
 */

#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* system() */
#include <string.h>    /* read(), write(), close(), bzero(), strcmp() */
#include <unistd.h>    /* read(), write(), close() */
#include <arpa/inet.h> /* inet_addr() */

#include "tcp_udp.h"

#define PORT (5000)
#define BUFFER_SIZE (5)

void PingFunc(int socket_fd);

int main()
{
    int counter = 4;
    int socket_fd = 0;
    int port = 0;
    struct sockaddr_in server_addr;

    /* Creating a socket file descriptor and checking if it worked */
    socket_fd = NewSocketFD(SOCK_STREAM);
    

    bzero(&server_addr, sizeof(server_addr));

    /* Filling server information */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (0 != connect(socket_fd, (struct sockaddr *)&server_addr,
                          sizeof(server_addr)))
    {
        printf("Connection with the server failed\n");
        return (1);
    }

    system("clear");

    PingFunc(socket_fd);

    close(socket_fd);

    printf("Exiting the program after closing the socket\n\n");

    return (0);
}

void PingFunc(int socket_fd)
{
    char input[BUFFER_SIZE] = {0};
    char output[BUFFER_SIZE] = {0};
    int check = 0;

    while (1 != check)
    {
        printf("\nEnter a string to send\n");
        scanf("%s", output);

        bzero(input, sizeof(input));

        write(socket_fd, output, 5);

        bzero(input, sizeof(input));

        read(socket_fd, input, sizeof(input));

        printf("Received from the Server: %s\n\n", input);

        if (0 == strcmp(output, "quit"))
        {
            check = 1;
        }
    }
}
