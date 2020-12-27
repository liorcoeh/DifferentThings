/*
 * TCP Client
 */

#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* system() */
#include <strings.h>   /* read(), write(), close(), bzero */
#include <unistd.h>    /* read(), write(), close() */
#include <arpa/inet.h> /* inet_addr() */

#include "tcp_udp.h"

#define PORT (5000)
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
    char input[80];
    int counter = 0;
    int sleep_interval = 0;

    counter = RandNum();

    while (0 != counter)
    {
        bzero(input, sizeof(input));

        write(socket_fd, "Ping", 5);

        printf("Sending Ping to the server\n");

        bzero(input, sizeof(input));

        read(socket_fd, input, sizeof(input));

        printf("Received from the Server: %s\n\n", input);

        sleep_interval = RandNum();
        printf("Waiting %d seconds before sending a ping\n", sleep_interval);
        sleep(sleep_interval);

        --counter;
    }
}
