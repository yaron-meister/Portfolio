/*****************************************************************************
 * File name:   cqueue_test.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-01-24 11:57:27
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* 		 printf   	   */
#include <stdlib.h>    /*     EXIT_SUCCESS 	   */
 
#include "cqueue.h"        /* Forward declarations */


/********************************* Macros *************************************/ 
 
 
/**************************** Forward Declarations ****************************/
static void IntEqualityTest(int actual_value, int expected_value,
													    int num_of_test);
static void PointerEqualityTest(void *actual_value, void *expected_value,
													    int num_of_test);
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
													    int num_of_test);
static int Compare(const void *left, const void *right);


/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

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
    
	



    
    
	printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
static void IntEqualityTest(int actual_value, int expected_value,
												 int num_of_test)
{
	if (expected_value != actual_value)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
static void PointerEqualityTest(void *actual_value, void *expected_value,
												 		  int num_of_test)
{
	if (expected_value != actual_value)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mFAILED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
							    				   		 int num_of_test)
{
	if (expected_value != actual_value)
    {
        printf("Test No. %d \t\033[1;31mFAILED\033[0m\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}






/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
