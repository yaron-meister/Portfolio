/*****************************************************************************
 * File name:   fsq_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Max
 * Date:        2019-03-11 23:51:29
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <iostream>     /* 		cout, cerr		*/
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
#include <cstdio>		/*		  printf 		*/

#include "fsq.h"        /* Forward declarations */

 
/**************************** Forward Declarations ****************************/
void FSQTest(void);
void* Read(void* i);
void* Write(void* i);

/***************************** Global variables *******************************/
ilrd::FSQ<50> g_fsq;
size_t g_other_buffer[50]  = {0};
pthread_t push_threads[20] = {0};
pthread_t pop_threads [20] = {0};

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{   
  
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
	FSQTest();
	
	//g_fsq.Print();

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
void FSQTest(void)
{
	size_t i = 0;

	for (i = 0; i < 20; ++i)
	{
		pthread_create(&push_threads[i], NULL, Write, (void*)i);
		pthread_create(&pop_threads[i], NULL, Read, (void*)i);
	}
	
	for (i = 0; i < 20; ++i)
	{
		pthread_join(push_threads[i], NULL);
		pthread_join(pop_threads[i], NULL);
	} 

	printf("\n[ ");

	for (i = 0; i < 50; ++i)
	{
		printf("%lu ", g_other_buffer[i]);
	}

	printf("]\n");
}

/********************* 								      *********************/ 	
void* Read(void* i)
{
	g_fsq.Read(g_other_buffer + (size_t)i);
	
	return (NULL);
}

/********************* 								      *********************/ 	
void* Write(void* i)
{
	g_fsq.Write((size_t)i);
	
	return (NULL);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
