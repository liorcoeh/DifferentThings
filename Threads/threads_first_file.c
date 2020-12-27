/*
 * Threads - First file
 **

#include <stdio.h>      /* printf() */
#include <unistd.h>     /* sleep() */
#include <stdlib.h>     /* system() */
#include <time.h>       /* time() */
#include <pthread.h>    /* pthread_t, pthread_create(), pthread_join()  */
                        /* pthread_detach(), pthread_self()             */


#define SIZE (100000)
#define MAX_THREAD (32753)
#define LARGE_NUMBER (1824997160)
/*#define LARGE_NUMBER (10)*/


/* Toggle these, one at a time to run the right EX */
 #define TASK1 
/* #define TASK2 */
/* #define TASK3 */
/* #define TASK4 */


/****************************************************************************
	                        UTILITY FUNCTIONS
****************************************************************************/
/* Function that writes into an array */
void *RegularKThread(void *index);

/* Function that writes into an array but detaches the thread */
void *DetachKThread(void *index);

/* Function to calculate the sum of divisors - using threads */
void *ThreadSumOfDivisors(void *thread_number);

/* Function to clear the terminal */
void ClearFun();


/****************************************************************************
	                        GLOBAL VARIABLES
****************************************************************************/
int arr_a[SIZE] = {0};
int arr_b[SIZE] = {0};
int sum[MAX_THREAD] = {0};
size_t thread_sum = 0;
int begin = 1;

/****************************************************************************
	                              MAIN
****************************************************************************/

int main()
{
    int i = 0;
    
    #ifdef TASK1
    int counter = 0;
    #endif /* TASK1 */

    #ifdef TASK2
    int check = 1;
    #endif /* TASK2 */ 

    #ifdef TASK3
    int check = 1;
    #endif /* TASK3 */

    time_t start = 0;
    time_t end = 0;
    pthread_t thread[SIZE];

    ClearFun();

#ifdef TASK1
/****************************************************************************
	            TASK1 - Writing into a global int array
****************************************************************************/
    printf("TASK1:\n\n");

    printf("This will take about 10 seconds - cause there is sleep(10)\n\n");

    start = time(NULL);
    for (i = 0; i < SIZE; ++i)
    {
        pthread_create(&thread[i], NULL, RegularKThread, &i);
    }
    end = time(NULL);
    sleep(10);
    printf("The time that passed is %ld\n\n", end - start);

    for (i = 0; i < SIZE; ++i)
    {
        if (arr_a[i] != i)
        {
            ++counter;
        }
        arr_a[i] = 0;
    }
    printf("There are %d elements in the array that didn't work\n", counter);
    printf("And there are %d elements that did work\n\n", SIZE - counter);
#endif /* TASK1 */
#ifdef TASK2
/****************************************************************************
            TASK2 - Trying to make every pthread_create successful
****************************************************************************/
    printf("TASK2:\n\n");

    printf("After couple of seconds you should press CTRL C - ");
    printf("it is stuck\n\n");

    start = time(NULL);
    for (i = 0; i < SIZE; ++i)
    {
        while (0 != check)
        {
            check = pthread_create(&thread[i], NULL, RegularKThread, &i);
        }
        check = 1;
    }
    end = time(NULL);

    printf("The time that passed is %ld\n", (end - start));

#endif /* TASK2 */
#ifdef TASK3
/****************************************************************************
            TASK3 - Trying to make every pthread_create successful
                            Using detached threads
****************************************************************************/
    printf("TASK3:\n\n");

    printf("This will take about 10 seconds - cause there is sleep()\n\n");

    start = time(NULL);
    for (i = 0; i < SIZE; ++i)
    {
         while (0 != check)
        {
            check = pthread_create(&thread[i], NULL, DetachKThread, &i);
        }
        check = 1;
    }
    end = time(NULL);
    sleep(10);
    
    printf("The time that passed is %ld\n\n", (end - start));

#endif /* TASK3 */
#ifdef TASK4
/****************************************************************************
            TASK4 - Calculating the sum of divisors of a large number
                    using the maximum thread possible number
****************************************************************************/
    printf("TASK4:\n\n");

    printf("This will take around 15 seconds - it's a long process...\n\n");

    start = time(NULL);
    for (i = 0; i < MAX_THREAD; ++i)
    {
        pthread_create(&thread[i], NULL, ThreadSumOfDivisors, &i);
        pthread_join(thread[i], NULL);
    }
    end = time(NULL);

    thread_sum += LARGE_NUMBER;

    printf("The time that passed is %ld\n", end - start);
    printf("The total sum is %ld\n\n", thread_sum);

    if (end - start > 15)
    {
        sleep(2);
        printf("I am sorry, I thought it would take only 15 seconds...\n\n");
    }

#endif /* TASK4 */


    return (0);
}


void *RegularKThread(void *index)
{
    int i = *(int *)index;
    
    arr_a[i] = i;

    return (index);
}

void *DetachKThread(void *index)
{
    int i = *(int *)index;

    pthread_detach(pthread_self());

    arr_b[i] = i;

    return (index);
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







/*

KEYWORDS:

Thread -
    A thread is a way for a program to divide itself into two or more
    simultaneously running tasks. In general a thread is contained inside a
    process and different threads in the same process share the same resources
    while different processes in the same multitasking do not. Threads are
    lightweight, in terms of the system resources the consume, as compared
    with processes.

OpenMP - Opne Multi Processing
    The application programming interface (API) OpenMP supports multi
    platform shared memory multiprocessing programming in c.
    OpenMP uses a portable, scalable model that gives programmers a simple
    and flexible interface for developing parallel applications for
    platforms ranging from the standard desktop computer to the supercomputer.


*/
