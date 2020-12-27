/*
 * Message Queue - SECOND file
 */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* system() */
#include <sys/msg.h>
#include <sys/ipc.h>

typedef struct message_struct
{
    long message_type;
    char message_text[30];
} message_t;

int main()
{
    message_t main_message;
    key_t key = 0;
    int message_id = 0;
    char input[30] = {0}; /* 25 */

    system("clear");

    printf("Starting\n\n");

    /* Using ftok() to create a unique key */
    key = ftok("main_file", 28);

    /* Creating a new message queue */
    message_id = msgget(key, 0666 | IPC_CREAT);

    /* Receiving the message from the queue */
    msgrcv(message_id, &main_message, 30, 1, 0);

    printf("%s\n\n", main_message.message_text);

    /* Destroying the message queue */
    msgctl(message_id, IPC_RMID, NULL);

    return (0);
}