/*
 * Shared Memory - FORTH file
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
    char *input = NULL;

    /* Creating a unique key */
    key = ftok("main_file", 25);

    /* Getting identifier for the shared memory */
    shared_memory_id = shmget(key, 1024, 0666 | IPC_CREAT);

    /* Attaching to shared memory */
    input = (char *)shmat(shared_memory_id, (void*)0, 0);

    printf("From forth process it is the %s\n\n", input);

    /* Deatching from the shared memory */
    shmdt(input);

    /* Destroying the shared memory */
    shmctl(shared_memory_id, IPC_RMID, NULL);

    return (0);
}