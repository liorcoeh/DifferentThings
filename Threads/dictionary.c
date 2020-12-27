/*
 * Dictionary - Shuffle and sort a dictionary using multi thread
 *

#include <stdio.h>      /* printf() */
#include <pthread.h>    /* pthread  */
#include <stdlib.h>     /* qsort()  */
#include <string.h>     /* strlen   */
#include <time.h>       /* time() */

 #define WITH_THREADS 
/* #define PRINT */

#define WORD_SIZE (30)  	/* Dictionary word size */
/*#define SIZE (1023050)       Size of the int array */
#define SIZE (204610)      /* Size of the int array */
#define THREAD_AMOUNT (4)   /* Amount of threads to open */

/****************************************************************************
	   				Declaration of utility functions
****************************************************************************/

/* Function for the thread to use to call the real sorting function */
/* It devides the array into sections and send all the arguments    */
void *PrapareToSort(void *thread_number);

/* The sorting function (uses the qsort() function)                 */
void Sort(char *arr[], size_t size);

/* Compare function being used by the qsort() function              */
int CmpFunc(const void *a, const void *b);

/* Utility function to shuffle the words of the dictionary          */
void Shuffle(char* arr[], size_t size);

/****************************************************************************
	   				Declaration of the Global variablers
****************************************************************************/

char **dictionary = NULL;
int max_length = 0;

/****************************************************************************
	   				                MAIN
****************************************************************************/
/* gcc -ansi -pedantic-errors -Wall -Wextra -g multi_threaded_counting_sort.c -lpthread */

int main()
{
    pthread_t sorting_thread[THREAD_AMOUNT];

    size_t i = 0;
    size_t j = 0;

	clock_t start_t = 0;
	clock_t end_t = 0;

    /******************** GETTING THE WORDS INTO A BUFFER ******************/

    char words[WORD_SIZE]= {0};
    FILE *fp;
	
	dictionary = (char **)malloc(sizeof(char *) * SIZE);
	
	fp = fopen("/usr/share/dict/american-english", "r");
	
	for (i = 0; i < SIZE;)
	{
        
        while (i < 102305)
        {
            fscanf(fp, "%s", words);
            dictionary[i] = (char *)malloc(sizeof(char) * WORD_SIZE);
            strcpy(dictionary[i], words);
            ++i;
        }

        while (j < 102305)
        {
            dictionary[i] = (char *)malloc(sizeof(char) * WORD_SIZE);
            strcpy(dictionary[i], dictionary[j]);
            ++j;
            ++i;
        }
        j = 0;
        
	}
	
	fclose(fp);

    /* Shuffling the words */
    Shuffle(dictionary, SIZE);

    /************************ RUNNING THE SORTING **************************/

    #ifndef WITH_THREADS
    start_t = clock();
    Sort(dictionary, SIZE);
    end_t = clock();
	printf("The time that passed is %ld\n\n", end_t - start_t);
    #endif /* WITH_THREAD */


    #ifdef WITH_THREADS
    start_t = clock();
    for (i = 0; i < THREAD_AMOUNT; ++i)
    {
        pthread_create(&sorting_thread[i], NULL, PrapareToSort, &i);
        pthread_join(sorting_thread[i], NULL);
    }

    /* Merging the sections */
    /*qsort(dictionary, SIZE, sizeof(char *), CmpFunc);*/

	end_t = clock();
	printf("The time that passed is %ld\n\n", end_t - start_t);
    #endif /* WITH_THREADS */


    /********************** PRINT THE SORTED ARRAY ************************/
    #ifdef PRINT
    for (i = 0; i < SIZE; ++i)
    {
        printf("%s, ", dictionary[i]);
    }
    printf("\n\nThe time that passed is %ld\n\n", end_t - start_t);
    #endif /* PRINT */


    /* Free the mallocs */
    for (i = 0; i < SIZE; ++i)
	{
        free(dictionary[i]);
        dictionary[i] = NULL;
    }

    free(dictionary);
    dictionary = NULL;

    return (0);
}


/****************************************************************************
	   				        UTILITY FUNCTIONS
****************************************************************************/


void *PrapareToSort(void *thread_number)
{ 
    int new_thread_num = *(int *)thread_number + 1;
	int part_arr_size = SIZE / THREAD_AMOUNT;
	int one = 1;

	if (1 == new_thread_num)
	{
		one = 0;
	}

    Sort(dictionary + (part_arr_size * (new_thread_num - 1) + one), part_arr_size);

    return (0);
}

/***************************************************************************/

void Sort(char *arr[], size_t size)
{
    qsort(arr, size, sizeof(char *), CmpFunc);
}

/***************************************************************************/

int CmpFunc(const void *a, const void *b)
{
	return strcmp(*(char**)a, *(char**)b);
}

/***************************************************************************/

void Shuffle(char* arr[], size_t size)
{
    size_t i = 0;
    size_t j = 0;
    char *temp = 0;

    for (i = 0; i < size;)
    {
        j = i + rand() % (size - i);

        if (i > 0 && strcmp(arr[j], arr[i - 1]) == 0)
        {
            i = 0;
        }
        else
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            ++i;
        }
    }
}




