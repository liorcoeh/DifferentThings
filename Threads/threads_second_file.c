/*
 * Threads - Second file
 */

#include <stdio.h>      /* printf() */
#include <time.h>       /* time() */
#include <unistd.h>     /* sleep() */
#include <stdlib.h>     /* system() */
#include <omp.h>        /* openMP */
#include <pthread.h>    /* pthread_t, pthread_create(), pthread_join()  */
                        /* pthread_detach(), pthread_self()             */


/*#define LARGE_NUMBER (1824997160)*/
#define LARGE_NUMBER (10)
#define MAX_THREAD (7)         /* You can change this number up to 15 */

/* Toggle this off to run EX6, else it runs EX5 */
/* #define RUN_SIX */


/****************************************************************************
	                        UTILITY FUNCTIONS
****************************************************************************/
/* Function to calculate the sum of divisors - using a loop */
size_t SumOfDivisors(int num);

/* Function to calculate the sum of divisors - using threads */
void *ThreadSumOfDivisors(void *arg);

/* Function to clear the terminal */
void ClearFun();

/****************************************************************************
	                        GLOBAL VARIABLES
****************************************************************************/
int part = 0;
size_t thread_sum = 0;

/****************************************************************************
	                              MAIN
****************************************************************************/

int main()
{
    time_t start = 0;
    time_t end = 0;
    size_t loop_sum = 0;
    pthread_t thread[MAX_THREAD] = {0};
    int i = 0;

/****************************************************************************
	            EX5 - Loop to calculate the sum of divisors
                                    VS
                 Threads to calculate the sum of divisors
****************************************************************************/
    ClearFun();

    printf("The loop calculation:\n");
    #ifndef RUN_SIX
    printf("This will take about 4 seconds\n\n");
    #endif /* RUN_SIX */
    #ifdef RUN_SIX
    printf("This will take about 8 seconds\n\n");
    #endif /* RUN_SIX */


    start = time(NULL);
    {
        loop_sum = SumOfDivisors(LARGE_NUMBER) + LARGE_NUMBER;
    }
    end = time(NULL);

    printf("The total sum of %d divisors is: %ld\n", LARGE_NUMBER, loop_sum);
    printf("The total time it took is: %ld seconds\n\n\n", end - start);

    
    printf("The threads calculation - using ");
    printf("%d threads:\n", MAX_THREAD);
    printf("This will take somewhere between 5 to 15 seconds\n\n");

    start = time(NULL);
    for (i = 0; i < MAX_THREAD; ++i)
    {
        pthread_create(&thread[i], NULL, ThreadSumOfDivisors, &i);
        pthread_join(thread[i], NULL);
    }

    end = time(NULL);

    thread_sum += LARGE_NUMBER;

    printf("The total sum of %d divisors is: %ld\n", LARGE_NUMBER, thread_sum);
    printf("The total time it took is: %ld seconds\n\n", end - start);

    return (0);
}


size_t SumOfDivisors(int num)
{
    int i = 1;
    size_t sum = 0;

    #ifndef RUN_SIX
    for (i = 1; i <= num / 2; ++i)
    {
        if (0 == num % i)
        {
            sum += i;
        }
    }
    #endif /* RUN_SIX */

    #ifdef RUN_SIX
    #pragma omp parallel
    {
        for (i = 1; i <= num / 2; ++i)
        {
            if (0 == num % i)
            {
                sum += i;
            }
        }
    }
    #endif /* RUN_SIX */
    return (sum);
}

void *ThreadSumOfDivisors(void *thread_number)
{
    int new_thread_num = *(int *)thread_number + 1;
    int begin = ((LARGE_NUMBER / MAX_THREAD) * (new_thread_num - 1)) + 1;
    int end = (LARGE_NUMBER / MAX_THREAD) * new_thread_num;
    int i = 0;

    if (end == LARGE_NUMBER)
    {
        end = LARGE_NUMBER - 1;
    }

    pthread_detach(pthread_self());

    for (i = begin; i <= end; ++i)
    {
        if (0 == LARGE_NUMBER % i)
        {
            thread_sum += i;
        }
    }

    return (&thread_sum);
}

void ClearFun()
{
    int system_check = 0;

    system_check = system("clear");
    if (-1 == system_check)
    {
        printf("\n\n\n");
    }
    else
    {
        printf("\n\n\n");
    }
    
    printf("All the times I mention might be faster or slower, depends on\n");
    printf("your system, so don't invest too much into it\n\n\n\n");
    sleep(3);
}



