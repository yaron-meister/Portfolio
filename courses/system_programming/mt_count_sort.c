/*****************************************************************************
 * File name:   mt_count_sort.c
 * Developer:   Yaron Meister
 * Reviewer: 	Yael
 * Date:        2019-01-29 11:48:18
 * Description: Multi-Threaded counting sort of ENGLISH dict
 *****************************************************************************/
 
#include <stdio.h>      /*     printf    */
#include <stdlib.h>     /*  EXIT_SUCCESS */
#include <assert.h>		/*	   assert	 */
#include <sys/mman.h>	/* 	    mmap	 */
#include <pthread.h>	/*   pthread_t	 */
#include <sys/types.h>	/*  fstat, open	 */
#include <sys/stat.h>	/*  fstat, open	 */
#include <unistd.h>		/*	   fstat	 */
#include <fcntl.h>		/*	    open	 */
#include <string.h>		/*	   memset	 */
#include <time.h> 		/* clock_gettime */

#include "utils.h"		/*	    DBG		 */
#include "sorts.h"		/*	 MergeSort	 */


/********************************* Macros *************************************/ 
#define NUM_OF_ASCII (256)
#define NUM_OF_CORES (4)
#define ULTIMATE_THREADS_NUM (2 * (NUM_OF_CORES)) 

/********************************* Structs ************************************/
typedef struct thread_arg
{
	char *buffer;
	off_t histo_offset;
	off_t overwrite_offset;

} thread_arg_t;

/************************** Forward Declarations ******************************/
static void DictCountSort(thread_arg_t *threads_arg);
static void *FillHistogram(thread_arg_t *thread_arg_struct);
static void FillOffset(void);
/* A function that writes the sorted buffer */
static void *OverwriteBuffer(thread_arg_t *thread_arg_struct);
static void TestFunc(char *real_buffer, int num_of_test);
int CompareFunc(const void *chr1, const void *chr2);

/***************************** Global variables *******************************/
pthread_t g_threads_ids_array[ULTIMATE_THREADS_NUM] = {0};
off_t g_histogram[NUM_OF_ASCII] 					= {0};
off_t g_offset[NUM_OF_ASCII]						= {0};
off_t g_file_part_size		        				=  0;
off_t g_ascii_part_size								=  0;

static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        

/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	thread_arg_t threads_arg[ULTIMATE_THREADS_NUM] = {0};

#ifdef PRINT_TEST
	int i = 0;
#endif
	
	DictCountSort(threads_arg);
	/* The field 'buffer' is the same at every struct, therefore - it
			doesn't matter which struct to work with */
	TestFunc(threads_arg[0].buffer, 1);

#ifdef PRINT_TEST	
	for (i = 0; i < (ULTIMATE_THREADS_NUM * g_file_part_size); ++i)
	{
		printf("%c ", (threads_arg[0].buffer)[i]);	
	}
	
	printf("\n\n");
#endif
	
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
static void DictCountSort(thread_arg_t *threads_arg)
{
	int dict_fd 	  	  =  0; 						/*  File descriptor  */
	struct stat file_stat = {0};						/*   For file_size   */
	char *buffer_runner	  = NULL;
	int fstat_ret		  =  0;							/* For FAILURE check */
	off_t i				  =  0;
	off_t file_size	  	  =  0; 						/*Counts chrs in file*/

	assert(threads_arg);

	dict_fd = open("eng_dict", O_RDONLY);
	if (-1 != dict_fd)
	{
		/* Getting stats of the file "eng_dict" */
		fstat_ret = fstat(dict_fd, &file_stat);
		if (0 == fstat_ret)
		{
			/* Getting count of chars in the file "eng_dict" */
			file_size    = file_stat.st_size;
			/* Dividing 'file_size' for parts for each thread */ 
			g_file_part_size   = file_size / (ULTIMATE_THREADS_NUM);
			/* Maping the file for the RAM to use as an array */
			buffer_runner = (char*)(mmap(NULL, (size_t)file_size,
							 PROT_READ | PROT_WRITE, MAP_PRIVATE, dict_fd, 0));

			if (MAP_FAILED != buffer_runner)
			{
				/* Filling the histogram */
				for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
				{
					/* Updating thread's arg struct */
					threads_arg[i].buffer       = buffer_runner;
					threads_arg[i].histo_offset = i * g_file_part_size;
				
					if (0 != pthread_create(&g_threads_ids_array[i], NULL,
											(void*(*)(void*))FillHistogram,
						 						   (void*)&threads_arg[i]))
					{
						DBG(fprintf(stderr, "FAILURE at thread No.%lu\n", i));
					} 
				}
			
				for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
				{
					pthread_join(g_threads_ids_array[i], NULL);
				}

				/* Filling the offset array */
				FillOffset();

				g_ascii_part_size = (NUM_OF_ASCII / ULTIMATE_THREADS_NUM);

				/* Writing the sorted buffer */
				for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
				{
					threads_arg[i].overwrite_offset = i * g_ascii_part_size;

					if (0 != pthread_create(&g_threads_ids_array[i], NULL,
					  					    (void*(*)(void*))OverwriteBuffer,
					   								 (void*)&threads_arg[i]))
					{
						DBG(fprintf(stderr, "FAILURE at thread No.%lu\n", i));
					} 
				}

				for (i = 0; i < ULTIMATE_THREADS_NUM; ++i)
				{
					pthread_join(g_threads_ids_array[i], NULL);
				}
			}
			else
			{
				DBG(fprintf(stderr, "FAILURE at maping\n"));
			}
		}
		else
		{
			DBG(fprintf(stderr, "FAILURE at statistics\n"));
		}
		
		close(dict_fd);
	}
	else
	{
		DBG(fprintf(stderr, "FAILURE at file open\n"));
	}
}

/********************                                      ********************/
static void *FillHistogram(thread_arg_t *thread_arg_struct)
{
	off_t i 			 = 0;
	unsigned int chr	 = 0;
	off_t part_first_idx = 0;
	off_t part_final_idx = 0;
	
	assert(thread_arg_struct);
	
	part_first_idx = thread_arg_struct->histo_offset;
	part_final_idx = part_first_idx + g_file_part_size;
	
	for (i = part_first_idx; i < part_final_idx; ++i)
	{
		chr = (unsigned char)thread_arg_struct->buffer[i];
		/* Incrementing histogram[chr] using atomic operation */
		__sync_fetch_and_add(&g_histogram[chr], 1);
	}
		
	return (NULL);
}		

/********************                                      ********************/
static void FillOffset(void)
{
	unsigned int chr =  0; 

	/* Filling the offset array */
	for (chr = 1; chr < NUM_OF_ASCII; ++chr)
	{
		g_offset[chr] = g_offset[chr - 1] + g_histogram[chr - 1];
	}
}
	
/********************                                      ********************/
/* A function that writes the sorted buffer */
static void *OverwriteBuffer(thread_arg_t *thread_arg_struct)
{
	unsigned int chr	 		= 0;
	off_t part_first_idx 		= 0;
	off_t part_final_idx 		= 0;
	
	assert(thread_arg_struct);
	
	part_first_idx = thread_arg_struct->overwrite_offset;
	part_final_idx = part_first_idx + g_ascii_part_size;

	for (chr = part_first_idx; chr < part_final_idx; ++chr)
	{
		/* Writing 'chr' at the right offset of 'buffer' */
		memset(thread_arg_struct->buffer + g_offset[chr], chr,
															  g_histogram[chr]);
	}

	return (NULL);
}

/******************************************************************************/ 
static void TestFunc(char *real_buffer, int num_of_test)
{
	struct stat file_stat = {0};				/*    For file_size    */
	int dict_fd 	  	  =  0; 				/*   File descriptor   */
	int fstat_ret		  =  0;					/*  For FAILURE check  */
	off_t file_size	  	  =  0; 				/* Counts chrs in file */
	int test_ret		  =  0;					/* Return from strcmp  */
	char *test_buffer	  = NULL;

	assert(real_buffer);

	dict_fd = open("eng_dict_test", O_RDONLY);
	if (-1 != dict_fd)
	{
		/* Getting stats of the file "eng_dict" */
		fstat_ret = fstat(dict_fd, &file_stat);
		if (0 == fstat_ret)
		{
			/* Getting count of chars in the file "eng_dict" */
			file_size = file_stat.st_size;
			
			/* Maping the file for the RAM to use as an array */
			test_buffer = (char*)(mmap(NULL, (size_t)file_size,
							 PROT_READ | PROT_WRITE, MAP_PRIVATE, dict_fd, 0));

			if (MAP_FAILED != test_buffer)
			{
				MergeSort(test_buffer, (size_t)file_size, sizeof(char),
																   CompareFunc);
				test_ret = strcmp(real_buffer, test_buffer);

				if (0 != test_ret)
				{
					printf("Test No. %d "RED_COLOUR"FAILED"RESET_COLOUR"\n",
																 num_of_test);
				}
				else
				{
					printf("Test No. %d "GREEN_COLOUR"SUCCEEDED"RESET_COLOUR"\n",
																 num_of_test);
					++g_count;
				}
		
				++g_tests;
			}
			else
			{
				DBG(fprintf(stderr, "FAILURE at maping\n"));
			}
		}
		else
		{
			DBG(fprintf(stderr, "FAILURE at statistics\n"));
		}
		
		close(dict_fd);
	}
	else
	{
		DBG(fprintf(stderr, "FAILURE at file open\n"));
	}
}

/********************                                      ********************/
int CompareFunc(const void *chr1, const void *chr2)
{
	assert(chr1);
	assert(chr2);

	return (*(unsigned char*)chr1 - *(unsigned char*)chr2);
}






	




/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
