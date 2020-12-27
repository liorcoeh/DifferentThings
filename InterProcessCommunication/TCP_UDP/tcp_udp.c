/*
 * TCP / UDP - Functions definitions file
 */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* sizeof() */
#include <string.h>     /* memset(), strcmp() */
#include <unistd.h>     
#include <time.h>       /* time */
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> /* struct sockaddr_in */

#include "tcp_udp.h"

#define MAX_RAND_NUM (8)
#define BUFFER_SIZE (5)

int NewSocketFD(int type)
{
    int new_socket_fd = socket(AF_INET, type, 0);

    if (0 > new_socket_fd)
    {
        printf("Socket creation failed\n");
        exit(1);
    }

    return (new_socket_fd);
}

struct sockaddr_in TCPServerUpdatingServerInfo(int server_port)
{
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);

    return (server_addr);
}

int HandleTCPFunc(int socket_fd)
{
    char input[BUFFER_SIZE] = {0};

    if (0 == read(socket_fd, input, sizeof(input)))
    {
        return (-1);
    }

    printf("From client: socket number %d: %s\n\n", socket_fd,input);

    /* Checking the input */
    if (0 == strcmp(input, "ping") || 0 == strcmp(input, "Ping"))
    {
        if (0 > write(socket_fd, "Pong", 5))
        {
            perror("Accept tcp \"send\" failed\n");
            exit(1);
        }
    }
    else if (0 == strcmp(input, "quit"))
    {
        printf("Closing the server\n");
        write(socket_fd, "Bye\n", 5);
        exit(0);
    }
    else
    {
        write(socket_fd, " ", 5);
        printf("check\n");
        return (0);
    }  
}

struct sockaddr_in UDPUpdatingServerInfo(int server_port)
{
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    return (server_addr);
}

void HandleUDPFUNC(int socket_fd, struct sockaddr_in server_addr)
{
    char input[BUFFER_SIZE];
    int length = 0;
    int input_length = 0;

    length = sizeof(server_addr);
    
    input_length = recvfrom(socket_fd, (char *)input, BUFFER_SIZE, MSG_WAITALL,
                         (struct sockaddr *)&server_addr, &length);

    input[input_length] = '\0';

    printf("From client, socket number %d: %s\n\n", socket_fd, input);

    sendto(socket_fd, "Pong", 4, MSG_CONFIRM,
                   (const struct sockaddr *)&server_addr, length);

    printf("\n");
}


int BindSocketToAddr(int socket_fd, const struct sockaddr *server_addr,
                            size_t length)
{
    int result = bind(socket_fd, server_addr, length);

    if (0 > result)
    {
        printf("Binding has failed\n");
        exit(0);
    }

    return (result);
}

int AcceptConnection(int socket_fd)
{
    int new_fd = 0;
    int length = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;

    new_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &length);

    if (-1 == new_fd)
    {
        perror("Accept failed\n");
        exit(1);
    }
    
    return (new_fd);
}

int RandNum()
{
    srand(time(NULL));
    return (rand() % MAX_RAND_NUM + 3);
}

int MaxFD(int fd1, int fd2)
{ 
    if (fd1 > fd2)
    {
        return fd1;
    }
    else
    {
        return fd2;
    }
}