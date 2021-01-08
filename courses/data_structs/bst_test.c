/*****************************************************************************
 * File name:   bst_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Shiran
 * Date:        2018-12-18 14:56:01
 * Description:	BST data structure's testing
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>      /*       printf()   	*/
#include <stdlib.h>     /*     EXIT_SUCCESS 	*/
#include <assert.h>		/* 	     assert			*/

#include "utils.h"	    /*	    UNUSED_VAR  	*/
#include "bst.h"       /*  Forward declarations */


/**************************** Forward Declarations ****************************/
static int IsBefore(void *element1, void *element2, void *param);
void BSTCreate_Test(void);
void BSTGetDataAndInsert_Test(void);
void BSTFind_Test(void);
void BSTCountAndForEach_Test(void);
void BSTRemoveAndBeginAndNext_Test(void);
void BSTIsEmpty_Test(void);
void BSTIsSameIter_Test(void);
void BSTEnd_Test(void);
void BSTPrev_Test(void);


/***************************** Global variables *******************************/
 
 
static int g_count = 2;        /* count is the number of tests that succeeded */
static int g_tests = 2;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{    
    printf("\n******************* Create and Destroy - TEST ***************\n");
    printf("Test No. 1 succeded --- (by valgrind)\n");
    printf("Test No. 2 succeded --- (by valgrind)\n");
    
    BSTCreate_Test();
    BSTGetDataAndInsert_Test();
	BSTRemoveAndBeginAndNext_Test();
	BSTFind_Test();
	BSTCountAndForEach_Test();
	BSTIsEmpty_Test();
	BSTIsSameIter_Test();
	BSTEnd_Test();
	BSTPrev_Test();
	
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/  
/******************************************************************************/
static int IsBefore(void *element1, void *element2, void *param)
{
	assert(element1);
	assert(element2);
	
	UNUSED_VAR(param);
	
	return (*(int*)element1 < *(int*)element2);
}

/******************************************************************************/
void BSTCreate_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);
	
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTGetDataAndInsert_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	iter_t iter = NULL;
	int a = 10;
	int b = 7;
	int c = 15;
	
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);

	iter = BSTBegin(bst);

	printf("\n************** GetData and Insert - TEST ********************\n");

	if (7 != *(int*)(BSTGetData(iter)))
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	iter = BSTNext(iter);

	if (10 != *(int*)(BSTGetData(iter)))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	iter = BSTNext(iter);

	if (15 != *(int*)(BSTGetData(iter)))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++g_count;
    }

	++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTRemoveAndBeginAndNext_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	int a = 31;
	int b = 55;
	int c = 12;
	int d = 5;
	int e = 20;
	int f = 40;
	
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);
	BSTInsert(bst, &d);
	BSTInsert(bst, &e);
	BSTInsert(bst, &f);

	printf("\n************ Remove, Begin and Next - TEST ******************\n");

	BSTRemove(BSTFind(bst, &d));
	
	if (12 != *(int*)(BSTGetData(BSTBegin(bst))))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTRemove(BSTFind(bst, &b));
	
	if (40 != *(int*)(BSTGetData(BSTNext(BSTNext(BSTNext(BSTBegin(bst)))))))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    BSTRemove(BSTFind(bst, &a));
    
    if (40 != *(int*)(BSTGetData(BSTNext(BSTNext(BSTBegin(bst))))))
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    BSTRemove(BSTFind(bst, &c));
    
    if (20 != *(int*)(BSTGetData(BSTBegin(bst))))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    BSTInsert(bst, &c);
    BSTRemove(BSTFind(bst, &e));
    
    if (40 != *(int*)(BSTGetData(BSTNext(BSTBegin(bst)))))
    {
        printf("Test No. 10 failed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTFind_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	iter_t iter = NULL;
	int a = 10;
	int b = 7;
	int c = 15;
	int d = 7;
	int e = 20;
	
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);

	printf("\n********************* Find - TEST ***************************\n");

	iter = BSTFind(bst, &d);
	
	if (7 != *(int*)(BSTGetData(iter)))
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	iter = BSTFind(bst, &e);

	if (iter != BSTEnd(bst))
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTCountAndForEach_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	int a = 10;
	int b = 7;
	int c = 15;	

	printf("\n************** Count and ForEach - TEST *********************\n");

	if (0 != BSTCount(bst))
    {
        printf("Test No. 13 failed\n");       
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTInsert(bst, &a);
	BSTInsert(bst, &b);
	BSTInsert(bst, &c);

	if (3 != BSTCount(bst))
    {
        printf("Test No. 14 failed\n");       
    }
    else
    {
        printf("Test No. 14 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTIsEmpty_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	int a = 10;

	printf("\n******************* IsEmpty - TEST **************************\n");

	if (!BSTIsEmpty(bst))
    {
        printf("Test No. 15 failed\n");       
    }
    else
    {
        printf("Test No. 15 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTInsert(bst, &a);

	if (BSTIsEmpty(bst))
    {
        printf("Test No. 16 failed\n");       
    }
    else
    {
        printf("Test No. 16 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTIsSameIter_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	int a = 10;
	int b = 5;
	iter_t iter1 = NULL;
	iter_t iter2 = NULL;
	
	printf("\n****************** IsSameIter - TEST ************************\n");

	iter1 = BSTInsert(bst, &a);
	iter2 = BSTInsert(bst, &b);
	
	if (BSTIsSameIter(iter1, iter2))
    {
        printf("Test No. 17 failed\n");       
    }
    else
    {
        printf("Test No. 17 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	if (!BSTIsSameIter(iter2, BSTBegin(bst)))
    {
        printf("Test No. 18 failed\n");       
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTEnd_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);	
	
	printf("\n********************* End - TEST ****************************\n");

	if (BSTEnd(bst) != BSTBegin(bst))
    {
        printf("Test No. 19 failed\n");       
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	if (NULL == BSTEnd(bst))
    {
        printf("Test No. 20 failed\n");       
    }
    else
    {
        printf("Test No. 20 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/******************************************************************************/
void BSTPrev_Test(void)
{
	int (*is_before)(void *element1, void *element2, void *param) = IsBefore;
	bst_t *bst = BSTCreate(is_before, NULL);
	int a = 10;
	int b = 7;
	int c = 15;	
	iter_t iter1 = NULL;
	iter_t iter2 = NULL;
	iter_t iter3 = NULL;
	
	printf("\n********************* Prev - TEST ***************************\n");

	iter1 = BSTInsert(bst, &a);
	iter2 = BSTInsert(bst, &b);
	iter3 = BSTInsert(bst, &c);
	
	if (iter2 != BSTPrev(iter1))
    {
        printf("Test No. 21 failed\n");       
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	
	if (iter1 != BSTPrev(iter3))
    {
        printf("Test No. 21 failed\n");       
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	BSTDestroy(bst);
}

/**************************** END OF FILE *************************************/
