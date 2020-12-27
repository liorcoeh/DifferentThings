/*
 * Signals - Child Process (will be the child of a process)
 */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* sizeof() */
#include <signal.h>     /* sig_atomic_t, sigaction(), kill() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* pid_t, fork() */

sig_atomic_t usr_sig_flag = 0;

void SignalHandler(int sig);

int main()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = &SignalHandler;

    sigaction(SIGUSR2, &act, NULL);

    usr_sig_flag = 1;

    while (1)
    {
        if (usr_sig_flag)
        {
            printf("PING\t\t%d\n\n", (int)getppid());
            usr_sig_flag = 0;
            kill(getppid(), SIGUSR1);
        }
    }

    return (0);
}

void SignalHandler(int sig)
{
    (void)sig;
    usr_sig_flag = 1;
}