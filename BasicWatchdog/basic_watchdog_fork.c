/*
 * Basic Watchdog - Fork Fucntion
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */
#include<sys/wait.h> /* wait() */
#include <unistd.h> /* sleep(), pid_t	*/
#include <stdlib.h> /* system() */

#define SIZE (50)

int ParentProcess();


int main()
{
    int status = 0;
    
    while (0 == status)
    {
        status = ParentProcess();
    }
    
    return (0);
}

int ParentProcess()
{
    pid_t child_pid = 0;
    int status[10] = {0};
    char input[SIZE] = {0};
    char *args[]={"./child_process", NULL};

    printf("I am the parent\n\n");

    child_pid = fork();

    printf("\t\t\t\tChild pid = %d\n", child_pid);

    if (-1 == child_pid)
    {
        printf("ERROR\n");

        return (1);
    }
    else if (0 == child_pid) /* The child process is running */
    {
        printf("Enter the file to be processed (don't forget ./ at start)\n");
        scanf("%s", input);
        printf("\n");
        execv(input, args);
    }
    else /* The parent process is running */
    {
        printf("Waiting on child\n\n");
        wait(status);
        printf("Child has finished\n\n");
        printf("Parent pid = %d\n", getpid());
        printf("Child pid = %d\n", child_pid);
        printf("Child status is = %d\n\n", status[0]);
    }
    
    return (0);
}
