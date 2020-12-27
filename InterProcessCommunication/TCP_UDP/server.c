/*
 * The Server
 */

#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

#include "tcp_udp.h"

#define TCP_PORT (5000)
#define UPD_PORT (10101)

#define BUFFER_SIZE (5)
#define SEVEN (7)

int main()
{ 
    int tcp_fd = 0;
    int udp_fd = 0;
    int accept_fd = 0;
    int new_fd = 0;
    int fd_max = 0;
    int fd_ready = 0;
    int i = 0;
    int j = 0;
    int check = 0;
    int n_bytes = 0;

    struct sockaddr_in tcp_server_addr;
    struct sockaddr_in udp_server_addr;
    struct sockaddr_in client_addr;

    fd_set main_fd_set;
    fd_set new_fd_set;

    socklen_t length = 0;

    char buffer[BUFFER_SIZE]; 
    pid_t childpid; 
     
    ssize_t n; 
    
    const int on = 1;

    struct timeval main_tv;
    struct timeval backup_tv;
   
    char* message = "Hello Client";
    void sig_chld(int);
  
    /* Create listening TCP socket */
    tcp_fd = NewSocketFD(SOCK_STREAM);
    tcp_server_addr = TCPServerUpdatingServerInfo(TCP_PORT);
    BindSocketToAddr(tcp_fd, (const struct sockaddr *)&tcp_server_addr,
                               sizeof(tcp_server_addr));
    if (0 > listen(tcp_fd, 10))
    {
        perror("Listen failed\n");
        exit(1);
    }
  
    /* Create UDP socket */
    udp_fd = NewSocketFD(SOCK_DGRAM);
    udp_server_addr = UDPUpdatingServerInfo(UPD_PORT);
    BindSocketToAddr(udp_fd, (const struct sockaddr *)&udp_server_addr,
                               sizeof(udp_server_addr));

  
    /* Clear the descriptor set */
    FD_ZERO(&main_fd_set);
  
    /* Get fd_max */
    fd_max = MaxFD(tcp_fd, udp_fd);

    /* Set tcp_fd and udp_fd in readset list */
    FD_SET(tcp_fd, &main_fd_set);
    FD_SET(udp_fd, &main_fd_set);

    system("clear");

    main_tv.tv_sec = SEVEN;
    main_tv.tv_usec = 0;

    printf("\nStarting the server\n\n");

    for (;;)
    {
        new_fd_set = main_fd_set;
        backup_tv = main_tv;

        /* Select the ready descriptor */
        printf("Waiting for incoming message...\n");
        check = select(fd_max + 1, &new_fd_set, NULL, NULL, &backup_tv);

        if (-1 == check)
        {
            perror("Select Failed\n");
            exit(1);
        }
        if (0 == check)
        {
            printf("Seven seconds passed with no incoming message\n\n");
        }
      
        for (i = 0; i <= fd_max; ++i)
        {
            if (FD_ISSET(i, &new_fd_set))
            {
                if (udp_fd == i)
                {
                    printf("UDP connection established\n");
                    HandleUDPFUNC(udp_fd, udp_server_addr);
                }

                else if (tcp_fd == i)
                {
                    length = sizeof(client_addr);
                    bzero(buffer, sizeof(buffer));

                    accept_fd = AcceptConnection(tcp_fd);

                    FD_SET(accept_fd, &main_fd_set);

                    printf("Received initialized tcp connection: %s\n", buffer);
                    
                    HandleTCPFunc(accept_fd);

                    if (fd_max < accept_fd)
                    {
                        fd_max = accept_fd;
                    }
                }
                else
                {
                    if (-1 == HandleTCPFunc(i))
                    {
                        printf("Closing connection of socket fd %d\n\n", i);
                        FD_CLR(i, &main_fd_set);
                        close(i);
                    }
                    else
                    {
                        printf("Connection registered\n");
                    }
                }
            }
        }
    }

    return (0);
}
