/*
 * TCP / UDP
 */

#ifndef PING_PONG_H
#define PING_PONG_H

#include <stdlib.h>

/* Creating a new TCP socket and checking if it was succesful */
int NewSocketFD(int type);

/* Initializing the server sockaddr_in struck */
struct sockaddr_in TCPServerUpdatingServerInfo();

/* Handaling the messages coming from the TCP clients */
int HandleTCPFunc(int socket_fd);

/* Initializing the sockaddr_in struck */
struct sockaddr_in UDPUpdatingServerInfo(int server_port);

/* Handlign the messages coming from the UDP clients */
void HandleUDPFUNC(int socket_fd, struct sockaddr_in server_addr);

/* Binding the socket to a server address */
int BindSocketToAddr(int socket_fd, const struct sockaddr *server_addr,
                           size_t length);

/* Accepting a new connection returning a new socket_fd */
int AcceptConnection(int socket_fd);

/* Returns a random number between 3 and 10 */
int RandNum();

/* Getting the max value out of two fds */
int MaxFD(int fd1, int fd2);



#endif /* PING_PONG_H */