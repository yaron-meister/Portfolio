/*****************************************************************************
 * File name:   semaphore_test.cpp
 * Developer:   Yaron Meister
 * Reviewer:    Max
 * Date:        2019-03-11 18:40:29
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <iostream>     /*       cout, cerr     */
#include <cstdlib>      /*      EXIT_SUCCESS    */
#include <semaphore.h>  /*        sem_t         */
#include <cerrno>       /*        errno         */
#include <unistd.h>     /*        sleep         */
#include "semaphore.h"  /* Forward declarations */

 
/**************************** Forward Declarations ****************************/
void ThreadTest1(void);
void *LockAndPrint1(void *index);

void ThreadTest2(void);
void *LockAndPrint2(void *index);

void ThreadTest3(void);
void *LockAndPrint3(void *index);

/***************************** Global variables *******************************/
ilrd::Sem sem(1);

ilrd::Sem time_sem(5);

pthread_t threads_id[10] = {0};

int time_count = 0;

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
	
    printf("\n******************** Wait - TEST ****************************\n");
    ThreadTest1();

    printf("\n****************** TryWait - TEST ***************************\n");
    ThreadTest2();

    printf("\n***************** TimedWait - TEST **************************\n");
    ThreadTest3();

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/ 
/******************************************************************************/
void ThreadTest1(void)
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

/**********                                                          **********/
void *LockAndPrint1(void *index)
{
  size_t i = 1;
  
  sem.Wait();

  for (; i <= (size_t)index; ++i)
  {
    printf("%lu ", i);
  }

  printf("\n");

  sem.Post();

  return (NULL);
}

/******************************************************************************/
void ThreadTest2(void)
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

/**********                                **********/
void *LockAndPrint2(void *index)
{
  size_t i = 1;
  
  sem.TryWait();

  if (EAGAIN == errno)
  {
    printf("TryWait is ON\n");
  }

  for (; i <= (size_t)index; ++i)
  {
    printf("%lu ", i);
  }

  printf("\n");

  return (NULL);
}

/******************************************************************************/
void ThreadTest3(void)
{
  size_t index = 0;

  for (index = 0; index < 10; ++index)
  {
    pthread_create(&threads_id[index], NULL, LockAndPrint3, NULL);
  }

  for (index = 0; index < 10; ++index)
  {
    pthread_join(threads_id[index], NULL);
  }

  if (5 == time_count)
  {
    printf("TimedWait SUCCEEDED\n\n");
  }
  else
  {
    printf("TimedWait FAILED\n\n");
  }
}

/**********                                **********/
void *LockAndPrint3(void *index)
{
  struct timespec ts = {0, 0};
  ts.tv_sec = time(NULL) + 1;

  if (0 == time_sem.TimedWait(&ts))
  {
    ++time_count;
    sleep(2);
    time_sem.Post();
  }

  return (NULL);
}





/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
