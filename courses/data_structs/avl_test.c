/*****************************************************************************
 * File name:   avl_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	
 * Date:        2018-12-27 15:56:16
 * Test Flow:	Test cases 
 *****************************************************************************/
 
#include <stdio.h>      /*       printf()   	*/
#include <stdlib.h>     /*     EXIT_SUCCESS 	*/
#include <assert.h>		/* 	     assert			*/

#include "utils.h"	    /*	    UNUSED_VAR  	*/
#include "avl.h"       /*  Forward declarations */


/**************************** Forward Declarations ****************************/
static int Compare(const void *left, const void *right);
static int Action(void *data, void *param);
void AVLCreate_Test(void);
void AVLInsertAndFind_Test(void);
void AVLSizeAndIsEmpty_Test(void);

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
    
    AVLCreate_Test();
	AVLInsertAndFind_Test();
	AVLSizeAndIsEmpty_Test();
	
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
static int Compare(const void *left, const void *right)
{
	assert(left);
	assert(right);
	
	return (*(int*)left - *(int*)right);
}

/******************************************************************************/
static int Action(void *data, void *param)
{
	UNUSED_VAR(param);
	
	if (NULL == data)
	{
		return (-1);
	}
	
	*(int*)data += 1;
	
	return (0);
}
	                                                  
/******************************************************************************/
void AVLCreate_Test(void)
{
	int (*cmp_func)(const void *left, const void *right) = Compare;
	avl_t *avl = AVLCreate(cmp_func);
	
	AVLDestroy(avl);
}

/******************************************************************************/
void AVLInsertAndFind_Test(void)
{
	int (*cmp_func)(const void *left, const void *right) = Compare;
	avl_t *avl = AVLCreate(cmp_func);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int m = 6;
	
	printf("\n************** Insert and Find - TEST ***********************\n");

	AVLInsert(avl, &a);
	AVLInsert(avl, &b);	
	AVLInsert(avl, &c);	
	AVLInsert(avl, &d);	
	AVLInsert(avl, &e); 

	if (3 != AVLHeight(avl))
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (NULL == AVLFind(avl, &a))
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (NULL == AVLFind(avl, &d))
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (NULL != AVLFind(avl, &m))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	AVLDestroy(avl); 
}

/******************************************************************************/
void AVLSizeAndIsEmpty_Test(void)
{
	int (*cmp_func)(const void *left, const void *right) = Compare;
	avl_t *avl = AVLCreate(cmp_func);
	int a = 1;
	int b = 2;
	
	printf("\n************* Size and IsEmpty - TEST ***********************\n");

	if (0 != AVLSize(avl))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (!AVLIsEmpty(avl))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	AVLInsert(avl, &a);
	AVLInsert(avl, &b);	
AVLPrint(avl);
    if (2 != AVLSize(avl))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (AVLIsEmpty(avl))
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
 	AVLDestroy(avl); 
}

/******************************************************************************/
/*
void AVLSizeAndIsEmpty_Test(void)
{
	int (*cmp_func)(const void *left, const void *right) = Compare;
	avl_t *avl = AVLCreate(cmp_func);
	int(*action_func)(void *data, void *param) = Action;
	int a = 1;
	int b = 2;
	
	printf("\n************** Size and Find - TEST ***********************\n");

	if (0 != AVLSize(avl))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	AVLInsert(avl, &a);
	AVLInsert(avl, &b);	
    
    if (2 != AVLSize(avl))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
 	AVLDestroy(avl); 
}
*/











