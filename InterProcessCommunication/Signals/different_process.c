/*
 * Signals - Different Process (will have no relation to an existing process)
 */

#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <unistd.h> /* pid_t, fork */
#include <stdlib.h> /* sizeof */
#include <signal.h> /* kill */
#include <string.h> /* memset */

sig_atomic_t usr_sig_flag = 0;
sig_atomic_t caller_signal = 0;

void SignalHandler(int sig);


int main()
{
    struct sigaction act;

    memset(&act, 0, sizeof(act));
	act.sa_handler = &SignalHandler;

    /* call SigUsr2Handler for sigusr2 */
    sigaction(SIGUSR2, &act, NULL);

    usr_sig_flag = 1;

    printf("program 2 started - PID %d\n", (int)getpid());

    printf("Enter the the requested PID: ");
    scanf("%d", &caller_signal);

    while (1)
    {
        if (usr_sig_flag)
        {
            printf("PING\t\tFirst Process pid is %d\n", caller_signal);
            usr_sig_flag = 0;
            kill(caller_signal, SIGUSR1);
        }
    }

    return (0);
}

void SignalHandler(int sig)
{
    (void)sig;
    usr_sig_flag = 1;
}
