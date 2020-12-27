/*
 * Pipe - Between unconnected processes - FIRST file
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
    int counter = 4;
    int main_pipe;
    char *my_fifo = "fifo_name";
    char output[10] = {0};

    mkfifo(my_fifo, 0666);

    system("clear");

    while (0 != counter)
    {
        main_pipe = open(my_fifo, 1);

        write(main_pipe, "Ping", 5);

        close(main_pipe);

        main_pipe = open(my_fifo, 0);

        read(main_pipe, output, 5);
        
        printf("%s ==> From main process\n\n", output);

        close(main_pipe);

        --counter;
    }

    return (0);
}