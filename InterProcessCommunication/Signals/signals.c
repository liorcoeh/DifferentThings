/*
 * Signals
 */

#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* sizeof() */
#include <signal.h>     /* sig_atomic_t, sigaction(), kill() */
#include <string.h>     /* memset() */
#include <unistd.h>     /* pid_t, fork() */


/****************************************************************************
	    			Control of which exercise to activate
			One with out remarks brackets around it will be active
****************************************************************************/

/* #define TASK1 */
 #define TASK2 
 #define TASK3 

/****************************************************************************
	   Declaration of the Global variablers and Signal Handler function
****************************************************************************/


sig_atomic_t usr1_sig_flag = 0;
sig_atomic_t usr2_sig_flag = 1;
sig_atomic_t caller_signal = 0;

/* Signal Handlers */
void SignalHandler(int sig);
void SpeacialSigHandler(int sig, siginfo_t *info, void *ucontext);

/****************************************************************************
	    First exercise test - Line 15 - remove the remarks to activate
****************************************************************************/
#ifdef TASK1
int main()
{
	pid_t child_pid;

    struct sigaction act;

    memset(&act, 0, sizeof(act));

    act.sa_handler = &SignalHandler;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	child_pid = fork();
    
    while (1)
    {
	    if (0 > child_pid)
	    {
		    printf("ERROR\n");

            return (1);
	    }
	    else if (0 == child_pid) /* The child process is running */
	    {
			if (usr1_sig_flag)
			{
				printf("PING\t\t%d\n\n", (int)getppid());
				usr1_sig_flag = 0;
				kill(getppid(), SIGUSR2);
			}
	    }
	    else /* The parent process is running */
	    {
            if (usr2_sig_flag)
			{
				printf("PONG\t\t%d\n\n", child_pid);
				usr2_sig_flag = 0;
				kill(child_pid, SIGUSR1);
			}
	    }
    }

	return (0);
}
#endif /* TASK1 */



/****************************************************************************
		Second exercise test - Line 16 - remove the remarks to activate
****************************************************************************/
#ifdef TASK2
int main()
{
	char *args[]={"./child_process", NULL};
	pid_t child_pid;

    struct sigaction act;

    memset(&act, 0, sizeof(act));

    act.sa_handler = &SignalHandler;

	sigaction(SIGUSR1, &act, NULL);

	child_pid = fork();

	while (1)
    {
	    if (0 > child_pid)
	    {
		    printf("ERROR\n");

            return (1);
	    }
	    else if (0 == child_pid) /* The child process is running */
	    {
			if (usr2_sig_flag)
			{
        		execv(args[0], args);
			}
	    }
	    else /* The parent process is running */
	    {
            if (usr1_sig_flag)
			{
				printf("PONG\t\t%d\n\n", child_pid);
				usr1_sig_flag = 0;
				kill(child_pid, SIGUSR2);
			}
	    }
    }

	return (0);
}
#endif /* TASK2 */


#ifdef TASK3
int main()
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &SpeacialSigHandler;

	sigaction(SIGUSR1, &act, NULL);

	printf("My signal is %d\n\n", (int)getpid());

	while (1)
	{
		if (usr1_sig_flag)
		{
			printf("PONG\t\tSecond Process pid is %d\n", caller_signal);
			usr1_sig_flag = 0;
			kill(caller_signal, SIGUSR2);
		}
	}
	return (0);
}
#endif /* TASK3 */

/****************************************************************************
							SIGNAL HANDLER FUNCTIONS
****************************************************************************/

void SignalHandler(int sig)
{
    if (SIGUSR1 == sig)
    {
        usr1_sig_flag = 1;
    }
    else if (SIGUSR2 == sig)
    {
        usr2_sig_flag = 1;
    }
}

void SpeacialSigHandler(int sig, siginfo_t *info, void *vp)
{
	(void)sig;
	usr1_sig_flag = 1;
	caller_signal = info->si_pid;
}

