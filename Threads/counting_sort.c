/*
 * Counting Sort - Using multi thread
 */

#include <stdio.h>      /* printf() */
#include <pthread.h>    /* pthread  */
#include <stdlib.h>     /* qsort()  */
#include <string.h>     /* strlen   */
#include <time.h>       /* time() */

 #define WITH_THREADS 
/* #define PRINT */

#define WORD_SIZE (30)  	/* Dictionary word size */
#define SIZE (10230500)        
#define THREAD_AMOUNT (4)   /* Amount of threads to open */

/****************************************************************************
	   				Declaration of utility functions
****************************************************************************/

/* Function for the thread to use to call the real sorting function */
/* It devides the array into sections and send all the arguments    */
void *PrapareToSort(void *thread_number);

/* The actual counting sort function to use */
void CountingSort(int arr[], size_t size, size_t range);

/****************************************************************************
	   				Declaration of the Global variablers
****************************************************************************/

int sorting_arr[SIZE] = {0};
int max_length = 0;

/****************************************************************************
	   				                MAIN
****************************************************************************/
/* gcc -D_POSIX_C_SOURCE=199309L -ansi -pedantic-errors -Wall -Wextra -g multi_threaded_counting_sort.c -lpthread */

int main()
{
    pthread_t sorting_thread[THREAD_AMOUNT];

    size_t i = 0;
    size_t j = 0;

	clock_t start_t = 0;
	clock_t end_t = 0;

	struct timespec start, finish;
	double elapsed = 0;
	
	

	/*************** GETTING THE WORDS OUT OF THE DICTIONARY **************/
    char words[WORD_SIZE]= {0};
    FILE *fp;
	
	fp = fopen("/usr/share/dict/american-english", "r");
	
	for (i = 0; i < SIZE; ++i)
	{
        if (i < (SIZE / 100))
        {
            fscanf(fp, "%s", words);
		    sorting_arr[i] = strlen(words);
        }
		else
        {
            sorting_arr[i] = sorting_arr[j];
            ++j;
        }
        
        if (0 == i % 102305)
        {
            j = 0;
        }
  
        if (max_length <= sorting_arr[i])
        {
            max_length = sorting_arr[i];
        }
	}

	printf("\nThe largest word has %d letters in it\n\n", max_length);
    fclose(fp);


	/************************ RUNNING THE SORTING **************************/

	#ifndef WITH_THREADS
	/*start_t = clock();*/
	clock_gettime(CLOCK_MONOTONIC, &start);
	CountingSort(sorting_arr, SIZE, max_length);
	end_t = clock();
	printf("Not using threads, ");
	/*printf("the time that passed is %ld\n\n", end_t - start_t);*/
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

  	printf("sorting took: %f seconds\n", elapsed);
	#endif /* WITH_THREADS */


	#ifdef WITH_THREADS
	/*start_t = clock();*/
	clock_gettime(CLOCK_MONOTONIC, &start); 
    for (i = 0; i < THREAD_AMOUNT; ++i)
    {
        pthread_create(&sorting_thread[i], NULL, PrapareToSort, &i);
    }

	for (i = 0; i < THREAD_AMOUNT; ++i)
    {
		pthread_join(sorting_thread[i], NULL);
    }

	/* Merging */
	CountingSort(sorting_arr, SIZE, max_length);
	
	/*end_t = clock();
	printf("Using threads, ");
	printf("the time that passed is %ld\n\n", end_t - start_t);*/
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

  	printf("sorting took: %f seconds\n", elapsed);

	#endif /* WITH_THREADS */

	/********************** PRINT THE SORTED ARRAY ************************/

	#ifdef PRINT
    for (i = 0; i < SIZE; ++i)
	{
		printf("%d->", sorting_arr[i]);
    }
	#endif /* PRINT */

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

	if (0 == new_thread_num)
	{
		one = 0;
	}

	CountingSort(sorting_arr + (part_arr_size * (new_thread_num - 1) + one), part_arr_size, max_length);

	return (0);
}

/***************************************************************************/

void CountingSort(int arr[], size_t size, size_t range)
{
	size_t i = 0;
	size_t j = 0;
	size_t total_sum = 0;
	int *small_sum = NULL;
	size_t min_count = 0;
	size_t counter = 0;
	
	small_sum = (int *)calloc(range + 1, sizeof(int));
	
	/* Getting the amount of each element and putting it in the right index */
	for (i = 0; i < size; ++i)
	{
		small_sum[arr[i]] += 1;
	}
	
	/* Putting in each element the total sum of all small sums before it */
	for (i = 0; i <= range; ++i)
	{
		total_sum += small_sum[i];
		small_sum[i] = total_sum;
	}
	
	for (i = 0; i <= range; ++i)
	{
		min_count = 0;
		if (0 != small_sum[i])
		{
			j = small_sum[i];
			
			for (j = small_sum[i]; j > counter; --j)
			{
				arr[j - 1] = i;				
				++min_count;
			}
			counter += min_count;
		}
	}
	
	free(small_sum);
	small_sum = NULL;
}

/***************************************************************************/
