/*
 * Shared Memory - FIRST file
 */

#include <stdio.h>      /* printf() */
#include <string.h>     /* strlen() */
#include <stdlib.h>     /* system() */
#include <sys/shm.h>
#include <sys/ipc.h>


int main()
{
    key_t key = 0;
    int shared_memory_id = 0;
    char *output = NULL;

    /* Creating a unique key */
    key = ftok("main_file", 25);

    /* Getting identifier for the shared memory */
    shared_memory_id = shmget(key, 1024, 0666 | IPC_CREAT);

    /* Attaching to shared memory */
    output = (char *)shmat(shared_memory_id, (void*)0, 0);

    /* Putting the data into the shared memory */
    memcpy(output, "Final Exercise finally", 23);

    /* Deatching from the shared memory */
    shmdt(output);

    return (0);
}

    



