/*
 * Child Process - To be used by the parent process
 */

#include <stdio.h>	/* printf */
#include <unistd.h> /* sleep()	*/

int main()
{
    printf("I am the child process\n");
    printf("I'm running cause my parent did a fork\n");
    printf("I'm not really sure why...\n\n");
    sleep(3);

    return (0);
}

