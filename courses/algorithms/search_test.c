/*****************************************************************************
 * File name:   search_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Majd
 * Date:        2019-01-10 16:34:38
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>      /* 		   printf  	    */
#include <stdlib.h>     /* 	    EXIT_SUCCESS    */

#include "search.h"     /* Forward declarations */


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
    void *ret  = NULL;
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10, 12};
	int arr3[] = {7};
    int arr4[] = {-3, -1, 5, 7, 9};	
    int a	   = 7;
    int b	   = 2;
    int c	   = 15;
	int d	   = -3;
	int e	   = 9;

	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
	printf("************ DON'T FORGET TO CHECK VALGRIND *********************");
	printf("\n"); 
  	printf("*****************************************************************");
  	printf("\n"); 
  	printf("\n"); 
    
	printf("************ Find  element in odd size array ******************\n");
    ret = BinarySearchRec(arr1, 5, sizeof(int), &Compare, &a);
    IntEqualityTest(*(int*)ret, 7, 1);

    ret = BinarySearchIter(arr1, 5, sizeof(int), &Compare, &a);
    IntEqualityTest(*(int*)ret, 7, 2);

	ret = JumpSearch(arr1, 5, sizeof(int), &Compare, &a);
    IntEqualityTest(*(int*)ret, 7, 3);

  	printf("\n");     

	printf("*********** Find  element in even size array ******************\n");
    ret = BinarySearchRec(arr2, 6, sizeof(int), &Compare, &b);
    IntEqualityTest(*(int*)ret, 2, 4);
    
    ret = BinarySearchIter(arr2, 6, sizeof(int), &Compare, &b);
    IntEqualityTest(*(int*)ret, 2, 5);

	ret = JumpSearch(arr2, 6, sizeof(int), &Compare, &b);
    IntEqualityTest(*(int*)ret, 2, 6);

  	printf("\n");     

	printf("********* Don't Find  element in odd size array ***************\n");
    ret = BinarySearchRec(arr1, 5, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 7);

    ret = BinarySearchIter(arr1, 5, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 8);

	ret = JumpSearch(arr1, 5, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 9);

  	printf("\n");     

	printf("********* Don't Find  element in even size array **************\n");    
    ret = BinarySearchRec(arr2, 6, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 10);
    
    ret = BinarySearchIter(arr2, 6, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 11);

	ret = JumpSearch(arr2, 6, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 12);

  	printf("\n");

	printf("********* Find  element in one element size array *************\n");    
    ret = BinarySearchRec(arr3, 1, sizeof(int), &Compare, &a);
    IntEqualityTest(*(int*)ret, 7, 13);
    
    ret = BinarySearchIter(arr3, 1, sizeof(int), &Compare, &a);
    IntEqualityTest(*(int*)ret, 7, 14);

	ret = JumpSearch(arr3, 1, sizeof(int), &Compare, &a);
    IntEqualityTest(*(int*)ret, 7, 15);

  	printf("\n");

	printf("******* Don't Find  element in one element size array *********\n");    
    ret = BinarySearchRec(arr3, 1, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 16);
    
    ret = BinarySearchIter(arr3, 1, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 17);

	ret = JumpSearch(arr3, 1, sizeof(int), &Compare, &c);
    PointerEqualityTest(ret, NULL, 18);

  	printf("\n");

	printf("************** Find  negative element in array ****************\n");    
    ret = BinarySearchRec(arr4, 5, sizeof(int), &Compare, &d);
    IntEqualityTest(*(int*)ret, -3, 19);
    
    ret = BinarySearchIter(arr4, 5, sizeof(int), &Compare, &d);
    IntEqualityTest(*(int*)ret, -3, 20);

	ret = JumpSearch(arr4, 5, sizeof(int), &Compare, &d);
    IntEqualityTest(*(int*)ret, -3, 21);

  	printf("\n");

	printf("**************** Find  last element in array ******************\n");    
    ret = BinarySearchRec(arr4, 5, sizeof(int), &Compare, &e);
    IntEqualityTest(*(int*)ret, 9, 22);
    
    ret = BinarySearchIter(arr4, 5, sizeof(int), &Compare, &e);
    IntEqualityTest(*(int*)ret, 9, 23); 

	ret = JumpSearch(arr4, 5, sizeof(int), &Compare, &e);
    IntEqualityTest(*(int*)ret, 9, 24);

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
static int Compare(const void *left, const void *right)
{
	return (*(int*)left - *(int*)right);
}



/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
