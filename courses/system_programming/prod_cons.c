/*****************************************************************************
 * File name:   prod_cons.c
 * Developer:   Yaron Meister
 * Date:        2019-01-23 13:06:13
 * Description: Threads synchronization cases
 *****************************************************************************/
 
#include <stdio.h>      /*    printf    */
#include <pthread.h>	/*  pthread_t	*/
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <signal.h>		/* sig_atomic_t	*/
#include <semaphore.h>	/*	semaphore	*/

#include "utils.h"		/* UNUSED_VAR	*/
#include "dlist.h"		/*	dlist.c		*/
#include "cqueue.h"		/*  cqueue.c	*/


/********************************* Macros *************************************/ 
#define STR1_LENGTH (20)
#define NUM_OF_THREADS (100)
#define EXE6_SRC_LENGTH (20)

enum read_write_flag
{
	WRITE,
	READ
}; 


/************************** Forward Declarations ******************************/
static void Exe1(void);
static void *WriteFunc(void *arg);
static void *ReadFunc(void *arg);

static void Exe2(void);
static void *Push2(void *arg);
static void *Pop2(void *arg);

static void Exe3(void);
static void *Push3(void *arg);
static void *Pop3(void *arg);

static void Exe4(void);
static void *Push4(void *arg);
static void *Pop4(void *arg);

static void Exe5(void);
static void *Push5(void *arg);
static void *Pop5(void *arg);

static void Exe6(void);
static void *Push6(void *arg);
static void *Pop6(void *arg);

/***************************** Global variables *******************************/
/* Arrays of thread_ids */
pthread_t push_threads[NUM_OF_THREADS] = {0};
pthread_t pop_threads [NUM_OF_THREADS] = {0};

/* Exe1 */
char exe1_src[]   			 = "Hello world of str1";
char exe1_dest[STR1_LENGTH]  = "";
char g_feed1				 = '\0';
volatile sig_atomic_t g_flag = WRITE;
char *exe1_writer	    	 = exe1_dest;					/* Write runner */
char *exe1_reader	   		 = exe1_dest;					/* Read runner  */

/* Exe2 */
dlist_t *g_dlist2 			  = NULL;
pthread_mutex_t dlist_mutex2  = PTHREAD_MUTEX_INITIALIZER;

/* Exe3 */
dlist_t *g_dlist3 			  = NULL;
pthread_mutex_t dlist_mutex3  = PTHREAD_MUTEX_INITIALIZER;	
sem_t dlist3_count;											/* Semaphore 3 */

/* Exe4 */
cq_t *g_que4 		       = NULL;
pthread_mutex_t que_mutex4 = PTHREAD_MUTEX_INITIALIZER;
sem_t que4_write_count;										/* W_semaphore 4 */
sem_t que4_read_count;										/* R_semaphore 4 */

/* Exe5 */
cq_t *g_que5 		             = NULL;
pthread_mutex_t que_mutex5_write = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t que_mutex5_read  = PTHREAD_MUTEX_INITIALIZER;
sem_t que5_write_count;										/* W_semaphore 5 */
sem_t que5_read_count;										/* R_semaphore 5 */

/* Exe6 */
char exe6_src[] 	   			= "Hello world of str6";
char exe6_dest[EXE6_SRC_LENGTH] = "";
pthread_mutex_t mutex6 			= PTHREAD_MUTEX_INITIALIZER;
char g_feed6	    	   		= '\0';
size_t g_index		   			= -1;
pthread_cond_t thread_flag_cv;								/*  Cond. var  */
sem_t exe6_count;											/* Semaphore 6 */


/*******************************************************************************
                                Main Function
*******************************************************************************/
int main(void)
{
	printf("\n\n**************** Exe1 - Test ******************************\n");
	Exe1();

	printf("\n\n**************** Exe2 - Test ******************************\n");
	Exe2();
	
	printf("\n\n**************** Exe3 - Test ******************************\n");
	Exe3();

	printf("\n\n**************** Exe4 - Test ******************************\n");
	Exe4();

	printf("\n\n**************** Exe5 - Test ******************************\n");
	Exe5();
	
	printf("\n\n**************** Exe6 - Test ******************************\n");
	Exe6();
	
    return (EXIT_SUCCESS);
} 

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/ 
static void Exe1(void)
{
	pthread_t w_thread = 0;
	pthread_t r_thread = 0;
	
	printf("\n");
	printf("\n");

	pthread_create(&w_thread, NULL, WriteFunc, NULL);
	pthread_create(&r_thread, NULL, ReadFunc, NULL);
	
	pthread_join(w_thread, NULL);
	pthread_join(r_thread, NULL);
	
	printf("\n");
	printf("\n");      	      
}
		
/********************* 								      *********************/ 	
static void *WriteFunc(void *arg)
{
	char *src_runner = exe1_src;
	
	UNUSED_VAR(arg);
	/* While 'writer' <= '\0' of 'dest' */
	while (exe1_writer < exe1_dest + STR1_LENGTH)
	{
		/* Busy wait */
		while (WRITE != g_flag)
		{
		}
		
		*exe1_writer = *src_runner;
		++exe1_writer;
		++src_runner;
		g_flag = READ;
	}
	
	return (NULL);
}	
	
/********************* 								      *********************/ 	
static void *ReadFunc(void *arg)
{
	UNUSED_VAR(arg);
	/* While 'reader' <= '\0' of 'dest' */
	while (exe1_reader < exe1_dest + STR1_LENGTH)
	{
		/* Busy wait */
		while (READ != g_flag)
		{
		}
		/* Reading test */
		printf("%c ", *exe1_reader);
		++exe1_reader;
		g_flag = WRITE;
	}

	return (NULL);
}		

/******************************************************************************/
static void Exe2(void)
{
	int i = 0;

	g_dlist2 = DListCreate(); 		
	if (NULL != g_dlist2)
	{
		/* Creating 10 prod and 10 cons threads */ 
		for (i = 0; i < 10; ++i)
		{
			pthread_create(&push_threads[i], NULL, Push2, NULL);
			pthread_create(&pop_threads[i], NULL, Pop2, NULL);
		}
		
		for (i = 0; i < 10; ++i)
		{
			pthread_join(push_threads[i], NULL);
			pthread_join(pop_threads[i], NULL);
		} 
	
		printf("\n");
		printf("\n");
		
		pthread_mutex_destroy(&dlist_mutex2);
		DListDestroy(g_dlist2);								
	}
}

/********************* 								      *********************/ 	
static void *Push2(void *arg)
{
	int a = 50;
	int i = 0;
	
	UNUSED_VAR(arg);
	/* while (1) demonstration */
	for (i = 0; i < 10; ++i)
	{
		pthread_mutex_lock(&dlist_mutex2);
	
		DListPushFront(g_dlist2, &a);
		/* printf for writing test */
		printf(RED_COLOUR"W2 "RESET_COLOUR); 
	
		pthread_mutex_unlock(&dlist_mutex2);
	}
	
	printf("\n");
	
	return (NULL);
}

/********************* 								      *********************/ 	
static void *Pop2(void *arg)
{
	int i = 0;
	
	UNUSED_VAR(arg);	
	/* while (1) demonstration */
	for (i = 0; i < 10; ++i)
	{
		pthread_mutex_lock(&dlist_mutex2);
		
		if (! DListIsEmpty(g_dlist2))
		{
			DListPopBack(g_dlist2);
			/* printf for reading test */
			printf(GREEN_COLOUR"R2 "RESET_COLOUR);
		}
	
		pthread_mutex_unlock(&dlist_mutex2); 
	}

	printf("\n");
	
	return (NULL);
}


/******************************************************************************/ 
static void Exe3(void)
{
	int i = 0;

	sem_init(&dlist3_count, 0, 0);
	
	g_dlist3 = DListCreate(); 		
	if (NULL != g_dlist3)
	{
		/* Creating 10 prod and 10 cons threads */ 
		for (i = 0; i < 10; ++i)
		{
			pthread_create(&push_threads[i], NULL, Push3, NULL);
			pthread_create(&pop_threads[i], NULL, Pop3, NULL);
		}
		
		for (i = 0; i < 10; ++i)
		{
			pthread_join(push_threads[i], NULL);
			pthread_join(pop_threads[i], NULL);
		} 
	
		printf("\n");
		printf("\n");
		
		pthread_mutex_destroy(&dlist_mutex3);
		sem_destroy(&dlist3_count);
		DListDestroy(g_dlist3);								
	}
}

/********************* 								      *********************/ 	
static void *Push3(void *arg)
{
	int a = 50;
	int i = 0;
	
	UNUSED_VAR(arg);
	/* while (1) demonstration */
	for (i = 0; i < 10; ++i)
	{	
		pthread_mutex_lock(&dlist_mutex3);
	
		DListPushFront(g_dlist3, &a);
		/* printf for writing test */
		printf(RED_COLOUR"W3 "RESET_COLOUR); 
	
		pthread_mutex_unlock(&dlist_mutex3);

		sem_post(&dlist3_count); 	 
	}
	
	printf("\n");

	return (NULL);
}

/********************* 								      *********************/ 	
static void *Pop3(void *arg)
{
	int i = 0;
	
	UNUSED_VAR(arg);	
	/* while (1) demonstration */
	for (i = 0; i < 10; ++i)
	{
		sem_wait(&dlist3_count);
	
		pthread_mutex_lock(&dlist_mutex3);
		
		DListPopFront(g_dlist3);
		/* printf for reading test */
		printf(GREEN_COLOUR"R3 "RESET_COLOUR);
	
		pthread_mutex_unlock(&dlist_mutex3);
	}
	
	printf("\n");
	
	return (NULL);
}

/******************************************************************************/ 
static void Exe4(void)
{
	int i = 0;

	sem_init(&que4_write_count, 0, NUM_OF_THREADS);
	sem_init(&que4_read_count, 0, 0);
	
	g_que4 = CQCreate(); 		
	if (NULL != g_que4)
	{
		/* Creating 10 prod and 10 cons threads */ 		
		for (i = 0; i < 10; ++i)
		{
			pthread_create(&push_threads[i], NULL, Push4, NULL);
			pthread_create(&pop_threads[i], NULL, Pop4, NULL);
		}
		
		for (i = 0; i < 10; ++i)
		{
			pthread_join(push_threads[i], NULL);
			pthread_join(pop_threads[i], NULL);
		} 
	
		printf("\n");
		printf("\n");
		
		pthread_mutex_destroy(&que_mutex4);
		sem_destroy(&que4_write_count);
		sem_destroy(&que4_read_count);
		CQDestroy(g_que4);							
	}
}

/********************* 								      *********************/ 	
static void *Push4(void *arg)
{
	int a = 50;
	int i = 0;
	
	UNUSED_VAR(arg);
	/* while (1) demonstration */
	for (i = 0; i < 10; ++i)
	{	
		sem_wait(&que4_write_count);
		
		pthread_mutex_lock(&que_mutex4);
	
		CQEnqueue(g_que4, a);
		/* printf for enqueuing test */
		printf(RED_COLOUR"E4 "RESET_COLOUR); 
	
		pthread_mutex_unlock(&que_mutex4);

		sem_post(&que4_read_count); 	 
	}

	printf("\n");
	
	return (NULL);
}

/********************* 								      *********************/ 	
static void *Pop4(void *arg)
{
	int i = 0;
	
	UNUSED_VAR(arg);	
	/* while (1) demonstration */	
	for (i = 0; i < 10; ++i)
	{
		sem_wait(&que4_read_count);
	
		pthread_mutex_lock(&que_mutex4);
		
		CQDequeue(g_que4);
		/* printf for dequeuing test */
		printf(GREEN_COLOUR"D4 "RESET_COLOUR);
	
		pthread_mutex_unlock(&que_mutex4);
		
		sem_post(&que4_write_count); 	 
	}

	printf("\n");
	
	return (NULL);
}

/******************************************************************************/ 
static void Exe5(void)
{
	int i = 0;

	sem_init(&que5_write_count, 0, NUM_OF_THREADS);
	sem_init(&que5_read_count, 0, 0);
	
	g_que5 = CQCreate(); 		
	if (NULL != g_que5)
	{
		/* Creating 10 prod and 10 cons threads */ 				
		for (i = 0; i < 10; ++i)
		{
			pthread_create(&push_threads[i], NULL, Push5, NULL);
			pthread_create(&pop_threads[i], NULL, Pop5, NULL);
		}
		
		for (i = 0; i < 10; ++i)
		{
			pthread_join(push_threads[i], NULL);
			pthread_join(pop_threads[i], NULL);
		} 
	
		printf("\n");
		printf("\n");
		
		pthread_mutex_destroy(&que_mutex5_write);
		pthread_mutex_destroy(&que_mutex5_read);
		sem_destroy(&que5_write_count);
		sem_destroy(&que5_read_count);
		CQDestroy(g_que5);							
	}
}

/********************* 								      *********************/ 	
static void *Push5(void *arg)
{
	int a = 50;
	int i = 0;
	
	UNUSED_VAR(arg);
	/* while (1) demonstration */	
	for (i = 0; i < 10; ++i)
	{	
		sem_wait(&que5_write_count);
		
		pthread_mutex_lock(&que_mutex5_write);
	
		CQEnqueue(g_que5, a);
		printf(RED_COLOUR"E5 "RESET_COLOUR); 
	
		pthread_mutex_unlock(&que_mutex5_write);

		sem_post(&que5_read_count); 	 
	}
	
	printf("\n");

	return (NULL);
}

/********************* 								      *********************/ 	
static void *Pop5(void *arg)
{
	int i = 0;
	
	UNUSED_VAR(arg);	
	/* while (1) demonstration */	
	for (i = 0; i < 10; ++i)
	{
		sem_wait(&que5_read_count);
	
		pthread_mutex_lock(&que_mutex5_read);
		
		CQDequeue(g_que5);
		printf(GREEN_COLOUR"D5 "RESET_COLOUR);
	
		pthread_mutex_unlock(&que_mutex5_read);
		
		sem_post(&que5_write_count); 	 
	}

	printf("\n");
	
	return (NULL);
}

/******************************************************************************/ 
static void Exe6(void)
{
	int i = 0;

	sem_init(&exe6_count, 0, 0);
	pthread_cond_init(&thread_flag_cv, NULL);

	/* One producer thread (using index 0 of the thread_ids array */
	pthread_create(&push_threads[0], NULL, Push6, NULL);

	/* 100 consumer threads (using indeces 1 - 100 of the thread_ids array */
	for (i = 1; i < 101; ++i)
	{
		pthread_create(&pop_threads[i], NULL, Pop6, NULL);
	}
	
	pthread_join(push_threads[0], NULL);
	
	for (i = 1; i < 101; ++i)
	{
		pthread_join(pop_threads[i], NULL);
	} 

	/* printf for EXE6 testing */
	printf("%s\n", exe6_dest); 

	printf("\n");
	printf("\n");
	
	pthread_mutex_destroy(&mutex6);
	sem_destroy(&exe6_count);
}

/********************* 								      *********************/ 	
static void *Push6(void *arg)
{
	int i = 0;
	int j = 0;
	
	UNUSED_VAR(arg);
	/* while (1) demonstration */		
	for (j = 0; j < EXE6_SRC_LENGTH; ++j)
	{
		/* A check that all threads are ready */
		for (i = 0; i < NUM_OF_THREADS; ++i)
		{	
			sem_wait(&exe6_count);
		}
	
		++g_index;
		
		pthread_mutex_lock(&mutex6);
		/* Writing to a buffer */
		g_feed6 = exe6_src[g_index];

		pthread_cond_broadcast(&thread_flag_cv);

		pthread_mutex_unlock(&mutex6);
	}
	
	return (NULL);
}

/********************* 								      *********************/ 	
static void *Pop6(void *arg)
{
	int i = 0;
	
	UNUSED_VAR(arg);	
	/* while (1) demonstration */		
	for (i = 0; i < EXE6_SRC_LENGTH; ++i)
	{
		pthread_mutex_lock(&mutex6);
	
		sem_post(&exe6_count);
		pthread_cond_wait(&thread_flag_cv,&mutex6);
	
		pthread_mutex_unlock(&mutex6);
		/* Reading from the buffer */
		exe6_dest[g_index] = g_feed6;
	}
	
	return (NULL);
}
	
		

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/ 
