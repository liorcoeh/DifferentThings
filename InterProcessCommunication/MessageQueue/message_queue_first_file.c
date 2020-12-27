/*
 * Message Queue - FIRST file
 */

#include <stdio.h>      /* printf() */
#include <string.h>     /* strlen() */
#include <stdlib.h>     /* system() */
#include <unistd.h>     /* sleep() */
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
    // = "I was sent from far away";

    system("clear");
    /* Using ftok() to create a unique key */
    key = ftok("main_file", 28);

    /* Creating a new message queue */
    message_id = msgget(key, 0666 | IPC_CREAT);
    main_message.message_type  = 1;

    //write(main_message.message_text, "I was sent from far away", 30);
    memcpy(main_message.message_text, "I was sent from far away", 30);


    /* Sending the message into the queue */
    msgsnd(message_id, &main_message, 30, 0);

    printf("Exiting the main process\n\n");

    return (0);
}

