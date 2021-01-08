/*****************************************************************************
 * File name:   threads_100k.c
 * Developer:   Yaron Meister
 * Date:        2019-01-22 11:16:39
 * Description: 100K threads implementation
 *****************************************************************************/

#include <time.h>	   	/*	   clock    */ 
#include <pthread.h>    /*   pthread_t  */
#include <stdio.h>		/*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <unistd.h>		/*    sleep 	*/

/********************************* Macros *************************************/ 
#define HUNDRED_K (100000)
#define MAX_THREADS (30000)
 
/************************** Forward Declarations ******************************/
/* Thread's functions */
static void *FillArr1(void *index); 
static void *FillArr2(void *index);
static void *FillArr3(void *index);
static void *FillArr5(void *index);

/* Cases functions */
static void HunderedKThreads(void);
static void ThreadsNir(void);
static void ThreadsJoin(void);
static void NoThreads(void);
static void ThreadsDetached(void);

/***************************** Global variables *******************************/
int g_arr1[HUNDRED_K] 		   		 = {0};
int g_arr2[HUNDRED_K] 		   		 = {0};
int g_arr3[HUNDRED_K] 		   		 = {0};
int g_arr4[HUNDRED_K] 		   		 = {0};
int g_arr5[HUNDRED_K] 		   		 = {0};
pthread_t threads2[MAX_THREADS]  	 = {0};
pthread_t threads3[MAX_THREADS / 10] = {0};
pthread_t threads5[HUNDRED_K] 		 = {0};


/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	clock_t tiks = 0;
	
	printf("\n");
  	printf("*****************************************************************");
  	printf("\n");
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n");
  	printf("*****************************************************************");
  	printf("\n");
  	printf("\n");
	
	/*
	printf("\n******************* 100,000 Threads *************************\n");	
	tiks = clock();
	HunderedKThreads();
	tiks = clock() - tiks;
	printf("100,000 threads are at %d tiks\n", (int)tiks);
	
	
	printf("\n******************** Nir's Threads **************************\n");	
	tiks = clock();
	HunderedKThreads();
	tiks = clock() - tiks;
	printf("Nir's threads are at %d tiks\n", (int)tiks);
	*/
	
	printf("\n******************** Join Threads ***************************\n");	
	tiks = clock();
	ThreadsJoin();
	tiks = clock() - tiks;
	printf("Join threads are at %d tiks\n", (int)tiks);
	
	printf("\n********************* No Threads ****************************\n");	
	tiks = clock();
	NoThreads();
	tiks = clock() - tiks;
	printf("Without threads  there are %d tiks\n", (int)tiks);
	
	printf("\n****************** Detached Threads *************************\n");	
	tiks = clock();
	ThreadsDetached();
	tiks = clock() - tiks;
	printf("Detached threads are at %d tiks\n", (int)tiks);
	
	printf("\n");      
	printf("\n");
	
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                          Functions implementations
*******************************************************************************/  
/******************************************************************************/
static void HunderedKThreads(void)
{
	pthread_t thread_id = 0;
	unsigned long index		= 0;
	
	for (index = 0; index < HUNDRED_K; ++index)
	{
		pthread_create(&thread_id, NULL, FillArr1, (void*)index);
	}
}

/**********    														 **********/
static void *FillArr1(void *index)
{
	g_arr1[(unsigned long)index] = (unsigned long)index;
	
	return (NULL);
}


/******************************************************************************/
static void ThreadsNir(void)
{
	unsigned long index 	 = 0;
	unsigned long thread_num = 0;

	while (index < HUNDRED_K)
	{
		for (thread_num = 0; thread_num < MAX_THREADS &&
		     index < HUNDRED_K; ++thread_num, ++index)
		{
			pthread_create(&threads2[thread_num], NULL, FillArr2, (void *)index);
		}

		for (thread_num = 0; thread_num < MAX_THREADS &&
			 index < HUNDRED_K; ++thread_num)
		{
			pthread_join(threads2[thread_num], NULL);
		}
	}
}

/**********    														 **********/
static void *FillArr2(void *index)
{
	g_arr2[(unsigned long)index] = (unsigned long)index;

	return (NULL);
}

/******************************************************************************/
static void ThreadsJoin(void)
{
	unsigned long index = 0;
	unsigned long thread_num = 0;

	while (index < HUNDRED_K)
	{
		for (thread_num = 0; thread_num < (MAX_THREADS / 10) &&
		     index < HUNDRED_K; ++thread_num, index += 10)
		{
			pthread_create(&threads3[thread_num], NULL, FillArr3, (void *)index);
		}

		for (thread_num = 0; thread_num < (MAX_THREADS / 10) &&
			 index < HUNDRED_K; ++thread_num)
		{
			pthread_join(threads3[thread_num], NULL);
		}
	}
}

/**********    														 **********/ 
static void *FillArr3(void *index)
{
	unsigned long i = 0;

	for (i = (unsigned long)index; i < (unsigned long)index + 10; ++i)
	{
		g_arr3[i] = i;
	}

	return (NULL);
}

/******************************************************************************/
static void NoThreads(void)
{
	unsigned long index = 0;
	
	for (index = 0; index < HUNDRED_K; ++index)
	{
		g_arr4[index] = index;
	}
}

/******************************************************************************/
static void ThreadsDetached(void)
{
	pthread_attr_t attr;
	unsigned long index = 0;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	for (index = 0; index < HUNDRED_K; ++index)
	{
		if(0 != pthread_create(&threads5[index], &attr, FillArr5, (void*)index))
		{
			fprintf(stderr, "ERROR in index No. %lu\n",index);
			perror("Failed to create a thread");
			return;
		}
	}

	pthread_attr_destroy(&attr);
}

/**********    														 **********/ 
static void *FillArr5(void *index)
{
	g_arr5[(unsigned long)index] = (unsigned long)index;
	
	return (NULL);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
