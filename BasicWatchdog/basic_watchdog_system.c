/*
 * Basic Watchdog - System Call (Fucntion)
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */
#include<sys/wait.h>    /* wait()   */
#include <unistd.h> /* sleep()	*/
#include <stdlib.h> /* system() */

#define SIZE (50)

int ParentProcess();

int main()
{
    int status = 0;
    int counter = 0;
    
    while (3 > counter)
    {
        status = ParentProcess();
        ++counter;
    }
    
    return (0);
}

int ParentProcess()
{
    pid_t child_pid = 0;
    char input[SIZE] = {0};
    printf("I am the parent\n\n");

    printf("Enter the file to be processed (don't forget ./ at start)\n");
    scanf("%s", input);
    printf("\n");


    child_pid = system(input);

    printf("The child pid = %d\n", child_pid);
    
    return (0);
}
