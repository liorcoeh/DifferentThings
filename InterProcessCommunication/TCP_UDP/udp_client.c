/*
 * UDP Client
 */

#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>     /* system() */
#include <unistd.h>     /* sleep() */
#include <netinet/in.h> /* struct sockaddr_in */

#include "tcp_udp.h"

#define PORT (10101)

static void SendRecieveFunc(int socket_fd, struct sockaddr_in server_addr);

int main()
{
    int socket_fd = 0;
    struct sockaddr_in server_addr;

    int port = 0;

    socket_fd = NewSocketFD(SOCK_DGRAM);

    server_addr = UDPUpdatingServerInfo(10101);

    SendRecieveFunc(socket_fd, server_addr);

    printf("Exiting the UDP client\n");

    return (0);
}


static void SendRecieveFunc(int socket_fd, struct sockaddr_in server_addr)
{
    int counter = 0;
    int sleep_interval = 0;
    char input[30];
    int length = 0;
    int input_length = 0;

    counter = RandNum();

    system("clear");

    printf("counter = %d\n", counter);

    while (0 != counter)
    {
        length = sizeof(server_addr);

        sleep_interval = RandNum();
        printf("Waiting %d seconds before sending a ping\n", sleep_interval);
        sleep(sleep_interval);
        
        sendto(socket_fd, "Ping", 4, MSG_CONFIRM,
                   (const struct sockaddr *)&server_addr, sizeof(server_addr));

        input_length = recvfrom(socket_fd, (char *)input, 30, MSG_WAITALL,
                                 (struct sockaddr *)&server_addr, &length);

        input[input_length] = '\0';

        printf("From the server: %s\n\n", input);

        --counter;
    }
}