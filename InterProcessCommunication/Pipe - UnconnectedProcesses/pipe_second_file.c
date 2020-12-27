/*
 * Pipe - Between unconnected processes - SECOND file
 */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* sizeof() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* pid_t, fork() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int counter = 10;
    int second_pipe;
    char *my_fifo = "fifo_name";
    char output[10] = {0};

    mkfifo(my_fifo, 0666);

    system("clear");

    while (0 != counter)
    {
        second_pipe = open(my_fifo, O_RDONLY);

        read(second_pipe, output, 5);

        close(second_pipe);

        printf("%s ==> From second process\n\n", output);

        second_pipe = open(my_fifo, O_WRONLY);

        write(second_pipe, "Pong", 5);

        close(second_pipe);

        --counter;
    }

    return (0);
}