/*****************************************************************************
 * File name:   thread_mem_space.c
 * Developer:   Yaron Meister
 * Date:        2019-02-04 10:24:10
 * Description: Exercising MT memory space
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <pthread.h>	/*  pthread_t	*/

#include "utils.h"		/*		DBG		*/

/********************************* Macros *************************************/ 
#define NUM_OF_THREADS (4)
 
/************************** Forward Declarations ******************************/
void *PrintfAddressesRec(void *thread_struct); 
 
/***************************** Global variables *******************************/
typedef struct thread_st
{
	int thread_index;
	int iter_num;
} thread_st_t; 

int glob = 5;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*******************************************************************************
                                Main Function
*******************************************************************************/

int main(void)
{
	int i = 0;
	pthread_t threads_ids_array[NUM_OF_THREADS] = {0};
	thread_st_t thread_structs[NUM_OF_THREADS]	= {0};
	
	printf("\nMain local-var address: %p\n\n", (void*)&i);
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		thread_structs[i].thread_index = i;
		thread_structs[i].iter_num = 0;
		if (0 != pthread_create(&threads_ids_array[i], NULL,
								 PrintfAddressesRec, (void*)&thread_structs[i]))
		{
			DBG(fprintf(stderr, "FAILURE at thread No.%d\n", i));
		} 
	}
  
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads_ids_array[i], NULL);
	}
	
	printf("\n");
	
	pthread_mutex_destroy(&mutex);
	
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                           Functions Implementations
*******************************************************************************/  
/******************************************************************************/ 
void *PrintfAddressesRec(void *thread_struct)
{
	thread_st_t *thread_st = (thread_st_t*)thread_struct;
	int stack = 5;
	void *heap = malloc(sizeof(int));
	if (NULL == heap)
	{
		return (NULL);
	}
	
	++thread_st->iter_num;
	
	if (5 == thread_st->iter_num)
	{
		free(heap);
		heap = NULL;
		
		return (NULL);
	}
	
	pthread_mutex_lock(&mutex);
	
	printf("\nThread num: %d\nIter num: %d\nHeap address: %p\nStack address: %p\n"
		   "Global address: %p\n", thread_st->thread_index, thread_st->iter_num,
		   						  heap, (void*)&stack, (void*)&glob);
		   						   
    printf("*****************************************************************");

	pthread_mutex_unlock(&mutex);

	PrintfAddressesRec((void*)thread_st);
	
	free(heap);
	heap = NULL;
	
	return (NULL);
}



















/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
