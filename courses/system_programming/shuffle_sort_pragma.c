/*****************************************************************************
 * File name:   shuffle_sort.c
 * Developer:   Yaron Meister
 * Reviewer: 	Majd
 * Date:        2019-01-30 14:08:45
 * Description: MT Shuffle and sort of the english dictionary
 *****************************************************************************/
 
#include <stdio.h>      /*    	printf    	*/
#include <stdlib.h>     /* 	 EXIT_SUCCESS 	*/
#include <assert.h>		/*      assert 		*/
#include <string.h>		/*  memcpy, strcmp 	*/
#include <pthread.h>	/*     pthread_t	*/
#include <time.h>	   	/*	     clock	    */

#include "utils.h"		/* 		 DBG 		*/

/********************************* Macros *************************************/ 
#define NUM_OF_CORES (4)
#define ULTIMATE_THREADS_NUM (2 * (NUM_OF_CORES)) 
#define NUM_OF_WORDS (495855)
#define MAX_LETTERS_NUM (30)  

#define NSEC_IN_SEC ((size_t) 1E+9)
#define REPEAT (10lu)

/************************** Forward Declarations ******************************/
static void ShuffleAndSort(void);
static void Shuffle(void);
static void DictSort(void);
static void SwapPointers(char **pointer1, char **pointer2);
static int  CompareFunc(char **pointer_for_word1, char **pointer_for_word2);
static void TestFunc(int num_of_test);


/***************************** Global variables *******************************/
char arr_of_words[NUM_OF_WORDS][MAX_LETTERS_NUM] 	= {0};
char *arr_of_pointers[NUM_OF_WORDS]					= {0};
pthread_t g_threads_ids_array[ULTIMATE_THREADS_NUM] = {0};
size_t g_part_size = NUM_OF_WORDS / ULTIMATE_THREADS_NUM;

static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        



/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
#ifdef PRINT_TEST
	int i = 0; 
#endif

	ShuffleAndSort();
	TestFunc(1);
	
#ifdef PRINT_TEST
 	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		printf("%s", arr_of_pointers[i]);	
	}
#endif
	

    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
static void ShuffleAndSort(void)
{
	FILE *dict_file = NULL;
	size_t i 	    = 0;
	
	/* Vars for time testing */
	struct timespec ts_start = {0};
    struct timespec ts_end   = {0};
    struct timespec ts_total = {0};
    
	assert(arr_of_words);

	dict_file = fopen("multiple_dict", "r");
	if (NULL != dict_file)
    {
		/* Filling 'arr_of_words' with the words from 'multiple_dict' */
    	for (i = 0; i < NUM_OF_WORDS; ++i)
    	{
    		fgets(arr_of_words[i], MAX_LETTERS_NUM, dict_file);
    	}   

    	fclose(dict_file);
	}
	else
	{
		DBG(fprintf(stderr, "FAILURE at file opening\n"));
	}

	/* Initiating arr of pointers to each word in 'arr_of_words' */
	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		arr_of_pointers[i] = arr_of_words[i];
	}

	/* Shuffling 'arr_of_pointers' */ 
	Shuffle();

	/* Starts time testing */
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_start);

	DictSort();

	/* Stops time testing */	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);

	/* All the following belongs to printing results of time testing */	
	if (ts_end.tv_nsec < ts_start.tv_nsec)
    {
        --ts_end.tv_sec;
        ts_end.tv_nsec += NSEC_IN_SEC;
    }

    ts_end.tv_sec  -= ts_start.tv_sec;
    ts_end.tv_nsec -= ts_start.tv_nsec;

    ts_total.tv_nsec += ts_end.tv_nsec;

    ts_total.tv_sec += ts_end.tv_sec +
        ts_total.tv_nsec / NSEC_IN_SEC;
    ts_total.tv_nsec %= NSEC_IN_SEC;

	printf("Sorting time: \t%8ld [ns]\n",
            (ts_total.tv_sec * NSEC_IN_SEC + ts_total.tv_nsec) / REPEAT);
}

/********************                                      ********************/
static void Shuffle(void)
{
		size_t i = 0;
		size_t random_index = 0;

		for (i = (NUM_OF_WORDS - 1); i > 0; --i)
		{
			random_index = rand() % (i + 1);
			SwapPointers(&arr_of_pointers[i], &arr_of_pointers[random_index]);
		}
}

/********************                                      ********************/
static void DictSort(void)
{
	size_t size = g_part_size;
	size_t i	= 0;
	
	/* Sorting is executed in two phases:
		1. 'qsort' in loop of parts inside pragma
		2. Merge sorting is executed above all of the 'dict' together
	*/
	
	#pragma omp for
	for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
	{
		if ((ULTIMATE_THREADS_NUM - 1) == i)
		{
			size = NUM_OF_WORDS - (size * (ULTIMATE_THREADS_NUM - 1));
		}
		
		qsort(arr_of_pointers + (i * g_part_size), size, sizeof(char*),
							  (int (*)(const void *, const void *))CompareFunc);
	}


	/* I tried to use MERGE instead of another qsort but according to a 
		DEADLINE I had to send this file as is.
		I'll get back to implement it using MERGE as soon as I will get time */


	/* The second phase of the SORTING */		     
	qsort(arr_of_pointers, NUM_OF_WORDS, sizeof(char*),
							  (int (*)(const void *, const void *))CompareFunc);
}     

/********************                                      ********************/
static void SwapPointers(char **pointer1, char **pointer2)
{
	char *temp = NULL;

	assert(pointer1);
	assert(pointer2);

	temp 	  = *pointer1;
	*pointer1 = *pointer2;
	*pointer2 = temp;
}

/********************                                      ********************/
static int CompareFunc(char **pointer_for_word1, char **pointer_for_word2)
{
	assert(pointer_for_word1);
	assert(pointer_for_word2);

	return (strcmp(*pointer_for_word1, *pointer_for_word2));
}

/******************************************************************************/ 
static void TestFunc(int num_of_test)
{
	char *arr_test[NUM_OF_WORDS] = {0};		
	size_t i  = 0;
	int count = 0;

	/* Initiating arr_test with pointers to each word in 'arr_of_words' */
	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		arr_test[i] = arr_of_words[i];
	}

	/* Comparing words */
	for (i = 0; i < NUM_OF_WORDS && 0 == count; ++i)
	{
		count = strcmp(arr_of_pointers[i], arr_test[i]);
	}

	if (0 != count)
    {
        printf("Test No. %d \t"RED_COLOUR"FAILED"RESET_COLOUR"\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t"GREEN_COLOUR"SUCCEEDED"RESET_COLOUR"\n",
        														   num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}







/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
