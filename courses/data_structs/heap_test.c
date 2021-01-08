/*****************************************************************************
 * File name:   heap_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Nir
 * Date:        2019-01-07 09:17:04
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>      /* 		  printf        */
#include <stdlib.h>     /* 		EXIT_SUCCESS    */
#include <assert.h>		/*		  assert		*/

#include "utils.h"		/*		UNUSED_VAR		*/
#include "heap.h"       /* Forward declarations */


/**************************** Forward Declarations ****************************/
static void IntEqualityTest(int actual_value, int expected_value,
													    int num_of_test);
static void PointerEqualityTest(void *actual_value, void *expected_value,
													    int num_of_test);
static void SizeTEqualityTest(size_t actual_value, size_t expected_value,
													    int num_of_test);
static int IsBefore(const void *left, const void *right, void *param);
static int IsMatch(const void *data, const void *arg);
void HeapCreateAndDestroy_Test(void);
void HeapPushAndPeek_Test(void);
void HeapSizeAndIsEmpty_Test(void);
void HeapPop_Test(void);
void HeapRemove_Test(void);


/***************************** Global variables *******************************/
  
static int g_count = 0;        /* count is the number of tests that succeeded */
static int g_tests = 0;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{    
  printf("\n***************************************************************\n");
	printf("************ DON'T FORGET TO CHECK VALGRIND *******************\n");
  printf("***************************************************************\n\n");
    
    HeapCreateAndDestroy_Test();
    HeapPushAndPeek_Test();
    HeapSizeAndIsEmpty_Test();
	HeapPop_Test();
    HeapRemove_Test(); 
    
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
        printf("Test No. %d failed\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d succeded\n", num_of_test);
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
        printf("Test No. %d failed\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d succeded\n", num_of_test);
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
        printf("Test No. %d failed\n", num_of_test);       
    }
    else
    {
        printf("Test No. %d succeded\n", num_of_test);
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
static int IsBefore(const void *left, const void *right, void *param)
{
	assert(left);
	assert(right);
	
	UNUSED_VAR(param);
	
	return (*(int*)left > *(int*)right);
}

/******************************************************************************/
static int IsMatch(const void *data, const void *arg)
{
	assert(data);
	assert(arg);
	
	return (*(int*)data == *(int*)arg);
}

/******************************************************************************/
void HeapCreateAndDestroy_Test(void)
{
	heap_t *heap = HeapCreate(10, &IsBefore, NULL);
	
	HeapDestroy(heap);
}

/******************************************************************************/
void HeapPushAndPeek_Test(void)
{
	heap_t *heap = HeapCreate(10, &IsBefore, NULL);
	int arr[]    = {28, 26, 21, 13, 17, 5, 7, 30};
	int i 	     = 0;
	int status   = 0;
	
	printf("\n************** Push and Peek - TEST *************************\n");

	PointerEqualityTest((int*)HeapPeek(heap), NULL, 1);

	for (; i < 8 && 0 == status; ++i)
	{
		status = HeapPush(heap, arr + i);
	}
	
	IntEqualityTest(*(int*)HeapPeek(heap), 30, 2);
	
	IntEqualityTest(i, 8, 3);
	SizeTEqualityTest(HeapSize(heap), 8, 4);
	HeapPrint(heap);
	
	HeapDestroy(heap);
}

/******************************************************************************/
void HeapSizeAndIsEmpty_Test(void)
{
	heap_t *heap = HeapCreate(10, &IsBefore, NULL);
	int arr[]    = {28, 26, 21};
	int i 	     = 0;
	
	printf("\n************** Size and IsEmpty - TEST **********************\n");

	IntEqualityTest(HeapIsEmpty(heap), 1, 5);
	SizeTEqualityTest(HeapSize(heap), 0, 6);

	for (; i < 3; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	IntEqualityTest(HeapIsEmpty(heap), 0, 7);
	SizeTEqualityTest(HeapSize(heap), 3, 8);
	HeapPrint(heap);
	
	HeapDestroy(heap);
}

/******************************************************************************/
void HeapPop_Test(void)
{
	heap_t *heap = HeapCreate(10, &IsBefore, NULL);
	int arr[]    = {28, 26, 21, 13, 17, 5, 7, 30};
	int i 	     = 0;
	
	printf("\n****************** Pop - TEST *******************************\n");

	for (; i < 8; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	HeapPop(heap);
	HeapPop(heap); 
	printf("\nAfter 2 pops, ");
	HeapPrint(heap);
	
	SizeTEqualityTest(HeapSize(heap), 6, 9);
	
	for (i = 0; i < 7; ++i)
	{
		HeapPop(heap);
	}
	
	IntEqualityTest(HeapIsEmpty(heap), 1, 10);
	printf("\nAfter another 7 pops, ");
	HeapPrint(heap);
	
	HeapDestroy(heap);
}

/******************************************************************************/
void HeapRemove_Test(void)
{
	heap_t *heap = HeapCreate(10, &IsBefore, NULL);
	int arr[]    = {28, 26, 21, 13, 17, 5, 7, 30};
	int i 	     = 0;
	
	printf("\n***************** Remove - TEST *****************************\n");

	for (; i < 8; ++i)
	{
		HeapPush(heap, arr + i);
	}

	HeapPrint(heap);	
	HeapRemove(heap, &IsMatch, arr + 3);
	HeapPrint(heap);
	HeapRemove(heap, &IsMatch, arr + 5);
	HeapPrint(heap);
	HeapRemove(heap, &IsMatch, arr);
	HeapPrint(heap); 
	
	HeapDestroy(heap);
}


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
