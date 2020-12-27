/*
 * Pipe - Between connected processes
 */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* sizeof() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* pid_t, fork() */

int main()
{
    int counter = 4;

    int pipe_ping[2];
    int pipe_pong[2];

    char child_input[10];
    char parent_input[10];
    char *ping = "ping";
    char *pong = "pong";

    pid_t pid = 0;

    if (-1 == pipe(pipe_ping))
    {
        printf("Pipe Ping Failed\n");
        return (1);
    }

    if (-1 == pipe(pipe_pong))
    {
        printf("Pipe Pong Failed\n");
        return (1);
    }

    pid = fork();

    while (0 != counter)
    {
        if (0 > pid)
        {
            printf("The Fork failed\n");
            return (1);
        }
        /* Child Process */
        else if (0 == pid)
        {
            read(pipe_ping[0], child_input, 5); /* Read from the parent pipe */
            printf("%s ==> from the child process\n\n", child_input);

            write(pipe_pong[1], pong, 5); /* Write into the child's pipe */
        }
        /* Parent Process */
        else
        {
            /* Write into the parent pipe */
            write(pipe_ping[1], ping, 5);

            read(pipe_pong[0], parent_input, 5); /* Read from the childe's pipe */
            printf("%s ==> from the parent process\n\n", parent_input);
        }
        --counter;
    }

    return (0);
}