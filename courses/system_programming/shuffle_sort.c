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
static void *SortParts(void *thread_index);/* Thread sort for differnet parts */
static void SwapPointers(char **pointer1, char **pointer2);
static int  CompareFunc(char **pointer_for_word1, char **pointer_for_word2);
static void TestFunc(int num_of_test);

static void Merge(char **temp);
static void MergeArrays(char **arr_a, size_t size_a, char **arr_b, size_t size_b,
			             char **temp, int(*cmp_func)(char **left, char **right));
			             
			             
			             

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
 	for (i = 0; i < 20; ++i)
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

	/* Sorting 'arr_of_pointers' */
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
	size_t i    = 0;
	char **temp = (char**)malloc(sizeof(char*) * NUM_OF_WORDS);
	
	/* Sorting is executed in two phases:
		1. Each thread sorts his part of the 'dict'
		2. Merge sorting is executed above all of the 'dict' together
	*/

	/* The first phase of the SORTING (including threads create) */
	for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
	{
		if (0 != pthread_create(&g_threads_ids_array[i], NULL,
														   SortParts, (void*)i))
		{
			DBG(fprintf(stderr, "FAILURE at thread No.%lu\n", i));
		} 
	}

	for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
	{
		pthread_join(g_threads_ids_array[i], NULL);
	}

	/* I tried to use MERGE instead of another qsort but according to a 
		DEADLINE I had to send this file as is.
		I'll get back to implement it using MERGE as soon as I will get time */

	Merge(temp);
	
	free(temp);
	temp = NULL;





	/* The second phase of the SORTING */		     
	/*qsort(arr_of_pointers, NUM_OF_WORDS, sizeof(char*),
							  (int (*)(const void *, const void *))CompareFunc);*/
}     
	     
/********************                                      ********************/
/* Thread sort for differnet parts */
static void *SortParts(void *thread_index)
{	
	char *starting_address = NULL;
	size_t size  = g_part_size;

	starting_address = (char*)arr_of_pointers + 
						   ((size_t)thread_index * g_part_size * sizeof(char*));

    /* Special check for the case that NUM_OF_WORDS is not dividing in
    	ULTIMATE_THREADS_NUM. 
    	In this case, the last part is NOT equal to 'g_part_size'.
	*/					   
	if ((ULTIMATE_THREADS_NUM - 1) == (size_t)thread_index)
	{
		size = NUM_OF_WORDS - (size * (ULTIMATE_THREADS_NUM - 1));
	}

	qsort(starting_address, size, sizeof(char*),
							  (int (*)(const void *, const void *))CompareFunc);

	return (NULL);
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
	size_t i   = 0;
	int status = 0;

	/* Initiating arr_test with pointers to each word in 'arr_of_words' */
	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		arr_test[i] = arr_of_words[i];
	}

	/* Comparing words */
	for (i = 0; i < NUM_OF_WORDS && 0 == status; ++i)
	{
		status = strcmp(arr_of_pointers[i], arr_test[i]);
	}

	if (0 != status)
    {
    	printf("The wrong cmp is at index %lu\n", i);
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


/******************************************************************************/
static void Merge(char **temp)
{
	size_t size = g_part_size;
	size_t i	= 0;
	
	for (i = 0; i < 8; i += 2)
	{
		if (6 == i)
		{ 
			size = NUM_OF_WORDS - (7 * g_part_size);
		}
			
		MergeArrays(&arr_of_pointers[i * g_part_size], g_part_size,
			 &arr_of_pointers[(i + 1) * g_part_size], size, temp, CompareFunc);
	}
	
	size = 2 * g_part_size;

	for (i = 0; i < 8; i += 4)
	{
		if (4 == i)
		{ 
			size = NUM_OF_WORDS - (6 * g_part_size);
		}
		
		MergeArrays(&arr_of_pointers[i * g_part_size], 2 * g_part_size,
			  &arr_of_pointers[(i + 2) * g_part_size], size, temp, CompareFunc);
	}
	
	MergeArrays(&arr_of_pointers[0], 4 * g_part_size,
	 &arr_of_pointers[4 * g_part_size], NUM_OF_WORDS - (4 * g_part_size),
	 												  temp, CompareFunc);
}

/******************************************************************************/
static void MergeArrays(char **arr_a, size_t size_a, char **arr_b, size_t size_b,
			             char **temp, int(*cmp_func)(char **left, char **right))
{
	char **runner_a = arr_a;
	char **runner_b = arr_b;
	char **runner_t	= temp;

	assert(arr_a);
	assert(arr_b);
	assert(temp);
	assert(cmp_func);
	
	while (runner_a < (arr_a + size_a) && runner_b < (arr_b + size_b))
	{
		if (cmp_func(runner_a, runner_b) < 0)
		{
			memcpy(runner_t, runner_a, sizeof(char*));
			++runner_a;
		}
		else
		{
			memcpy(runner_t, runner_b, sizeof(char*));
			++runner_b;
		}
		
		++runner_t;
	}
	
	if (runner_a < (arr_a + size_a))
	{
		memcpy(runner_t, runner_a, ((arr_a + size_a) - runner_a) * sizeof(char*));
	}
	
	if (runner_b < (arr_b + size_b))
	{
		memcpy(runner_t, runner_b, ((arr_b + size_b) - runner_b) * sizeof(char*));
	}

	memcpy(arr_a, temp, (size_a + size_b) * sizeof(char*));
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
