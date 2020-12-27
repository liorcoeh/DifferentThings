/*
 * Semaphore
 */

#include <stdio.h>      /* printf() */
#include <string.h>     /* memset() */
#include <semaphore.h>	/* sem functions */
#include <sys/stat.h>	/* S_IRWXU */
#include <fcntl.h>		/* sem functions, O_CREAT */
#include <stdlib.h>     /* system() */


/****************************************************************************
	   				Declaration of the Global variablers
****************************************************************************/

#define INIT_VALUE (100)
#define WORD_SIZE (10)


/****************************************************************************
	    						MAIN
****************************************************************************/

int main(int argc, char *argv[])
{
	sem_t *main_sem = NULL;
	char *sem_name = argv[1];
	
	int sem_value = 0;
	int difference = 0;
	char input[WORD_SIZE] = {0};
	int ammount = 0;

	main_sem = sem_open(sem_name, O_CREAT, S_IRWXU, INIT_VALUE);

	while (1)
	{
		system("clear");
		printf("\n\n");
		sem_getvalue(main_sem, &sem_value);
		printf("The semaphore value right now is %d\n", sem_value);

		printf("Enter 'D', 'U or 'X'\n");
		scanf("%s", input);

		/* Exit and reset the semaphore to it's init value */
		if (0 == strcmp(input, "X"))
		{
			sem_close(main_sem);
			sem_unlink(sem_name);

			return (0);
		}

		/* Decreasing the semaphore */
		else if (0 == strcmp(input, "D"))
		{
			printf("Enter the amount to decrease up to %d\n", sem_value);
			scanf("%d", &ammount);

			while (0 != ammount)
			{
				sem_wait(main_sem);
				--ammount;
			}
		}

		/* Increasing the semaphore */
		else if (0 == strcmp(input, "U"))
		{
			difference = INIT_VALUE - sem_value;
			printf("Enter the amount to increase up to %d\n", difference);
			scanf("%d", &ammount);

			while (0 != ammount)
			{
				sem_post(main_sem);
				--ammount;
			}
		}
	}
}

