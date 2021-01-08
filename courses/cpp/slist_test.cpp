/*****************************************************************************
 * File name:   slist_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 	Yael
 * Date:        2019-02-20 10:40:46
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <cstdlib>      /*     EXIT_SUCCESS 	*/
#include <stdio.h>		/*		  printf 		*/

#include "slist.h"      /* Forward declarations */


using namespace ilrd;

/**************************** Forward Declarations ****************************/
static void IntEqualityTest(int actual_value, int expected_value,
													    int num_of_test);
static void CharEqualityTest(char actual_value, char expected_value,
												 		int num_of_test);
static void floatEqualityTest(float actual_value, float expected_value,
												 		int num_of_test);
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
													    int num_of_test);
static void PointerEqualityTest(void *actual_value, void *expected_value,
												 		int num_of_test);

static void PushAndPopTest(void);
static void SizeAndIsEmptyTest(void);

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
    
  	PushAndPopTest();
  	SizeAndIsEmptyTest();

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
static void CharEqualityTest(char actual_value, char expected_value,
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
static void floatEqualityTest(float actual_value, float expected_value,
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
        printf("Test No. %d \t\033[1;32mSUCCEEDED\033[0m\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
static void PushAndPopTest(void)
{
	int num   = 5;
	float flo = 5.4;
	char chr  = 'a';

	SList list;

	printf("\n");
    printf("***************** Push and Pop - Test *************************\n");
    printf("\n");

	list.Push(&num);
	list.Push(&flo);
	list.Push(&chr);

	CharEqualityTest(*(char*)list.Pop(), 'a', 1);
	floatEqualityTest(*(float*)list.Pop(), 5.4, 2);
	IntEqualityTest(*(int*)list.Pop(), 5, 3);
	PointerEqualityTest(list.Pop(), NULL, 4);
}

/******************************************************************************/
static void SizeAndIsEmptyTest(void)
{
	int num   = 5;
	float flo = 5.4;

	SList list;

	printf("\n");
    printf("*************** Size and IsEmpty - Test ***********************\n");
	printf("\n");

    IntEqualityTest(list.IsEmpty(), true, 5);
    SizeTEqualityTest(list.Size(), 0, 6);

	list.Push(&num);

	IntEqualityTest(list.IsEmpty(), false, 7);
    SizeTEqualityTest(list.Size(), 1, 8);

	list.Push(&flo);

	IntEqualityTest(list.IsEmpty(), false, 9);
    SizeTEqualityTest(list.Size(), 2, 10);

	list.Pop();
	list.Pop();

	IntEqualityTest(list.IsEmpty(), true, 11);
    SizeTEqualityTest(list.Size(), 0, 12);
}

/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/    
