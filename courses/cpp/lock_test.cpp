/*****************************************************************************
 * File name:   lock_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Max
 * Date:        2019-03-11 18:47:50
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /*  cout, cerr   */
#include <cstdlib>      /* EXIT_SUCCESS  */
#include <mutex>        /*    mutex    */
#include <pthread.h>    /* pthread_mutex */
 
#include "lock.h"    /* Forward declarations */


/***************************** Global variables *******************************/
pthread_t threads_id[10] = {0};
 
/**************************** Forward Declarations ****************************/
void PThreadTest(void);
void *LockAndPrint1(void *index);

void STDMutexTest(void);
void *LockAndPrint2(void *index);

void RecMutexTest(void);
void *LockAndPrint3(void *index);


/***************************** Global variables *******************************/
  
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
    
    printf("\n****************** PThread - TEST ***************************\n");
    PThreadTest();

    printf("\n***************** STD::Mutex - TEST *************************\n");
    STDMutexTest();

    printf("\n****************** Rec-Mutex - TEST *************************\n");
    RecMutexTest();

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
void PThreadTest(void)
{
  size_t index = 0;
  
  for (index = 0; index < 10; ++index)
  {
    pthread_create(&threads_id[index], NULL, LockAndPrint1, (void*)index);
  }

  for (index = 0; index < 10; ++index)
  {
    pthread_join(threads_id[index], NULL);
  }

  printf("\n");
}

/**********                                **********/
void *LockAndPrint1(void *index)
{
  	{
	    size_t i = 1;
	    ilrd::Lock<pthread_mutex_t> lock(&g_pthread_mutex);

	    for (; i <= (size_t)index; ++i)
	    {
	      printf("%lu ", i);
	    }

	    printf("\n");
  	}

  return (NULL);
}

/******************************************************************************/
void STDMutexTest(void)
{
	size_t index = 0;
	  
    for (index = 0; index < 10; ++index)
	{
	    pthread_create(&threads_id[index], NULL, LockAndPrint2, (void*)index);
	}

	for (index = 0; index < 10; ++index)
	{
	    pthread_join(threads_id[index], NULL);
	}

	printf("\n");
}

/**********                                							 **********/
void *LockAndPrint2(void *index)
{
    {
	    size_t i = 1;
	    ilrd::Lock<std::mutex> lock(&g_std_mutex);
	    for (; i <= (size_t)index; ++i)
	    {
	      printf("%lu ", i);
	    }

	    printf("\n");
    }

  return (NULL);
}

/******************************************************************************/
void RecMutexTest(void)
{
  size_t index = 0;
  
  for (index = 0; index < 10; ++index)
  {
    pthread_create(&threads_id[index], NULL, LockAndPrint3, (void*)index);
  }

  for (index = 0; index < 10; ++index)
  {
    pthread_join(threads_id[index], NULL);
  }

  printf("\n");
}

/**********             						                     **********/
void *LockAndPrint3(void *index)
{
    {
	    if ((size_t)index > 10)
	    {
	      return (NULL);
	    }

	    size_t i = 1;
	    ilrd::Lock<std::recursive_mutex> lock(&g_rec_mutex);
	    for (; i <= (size_t)index; ++i)
	    {
	      printf("%lu ", i);
	    }

	    printf("\n");

	    LockAndPrint3((void*)((size_t)index + 1));
    }

  return (NULL);
}






/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
