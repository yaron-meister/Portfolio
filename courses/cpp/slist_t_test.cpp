/*****************************************************************************
 * File name:   slist_t_test.cpp
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-02-20 14:36:04
 * Test Flow: 
 *****************************************************************************/
 
#include <cstdlib>      /*     EXIT_SUCCESS     */
#include <stdio.h>      /*        printf        */

#include "slist_t.h"    /* Forward declarations */


using namespace ilrd;

/**************************** Forward Declarations ****************************/
static void IntEqualityTest(int actual_value, int expected_value,
                                                        int num_of_test);
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
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
static void PushAndPopTest(void)
{
    int num1 = 6;
    int num2 = 5;
    int num3 = 4;

    SListT<int> list;

    printf("\n");
    printf("***************** Push and Pop - Test *************************\n");
    printf("\n");

    list.Push(num1);
    list.Push(num2);
    list.Push(num3);

    IntEqualityTest(list.Pop(), 4, 1);
    IntEqualityTest(list.Pop(), 5, 2);
    IntEqualityTest(list.Pop(), 6, 3);
    IntEqualityTest(list.Pop(), 0, 4);
}

/******************************************************************************/
static void SizeAndIsEmptyTest(void)
{
    int num1 = 5;
    int num2 = 6;

    SListT<int> list;

    printf("\n");
    printf("*************** Size and IsEmpty - Test ***********************\n");
    printf("\n");

    IntEqualityTest(list.IsEmpty(), true, 5);
    SizeTEqualityTest(list.Size(), 0, 6);

    list.Push(num1);

    IntEqualityTest(list.IsEmpty(), false, 7);
    SizeTEqualityTest(list.Size(), 1, 8);

    list.Push(num2);

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
