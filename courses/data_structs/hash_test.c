/*****************************************************************************
 * File name:   hash_test.c
 * Developer:   Yaron Meister
 * Reviewer: 	Daria
 * Date:        2019-01-03 08:13:04
 * Test Flow: 	Test cases
 *****************************************************************************/
 
#include <stdio.h>     /*        printf       */
#include <stdlib.h>    /*     EXIT_SUCCESS    */
#include <assert.h>	   /*        assert	      */

#include "utils.h"	   /*		UNUSED_VAR	  */
#include "hash.h"      /* Forward declaratins */


/**************************** Forward Declarations ****************************/
static size_t HashFunc(const void *data, void *param);
static int CompareFunc(const void *left, const void *right);
static int ActionFunc(void *data, void *act_param);
void HashCreate_Test(void);
void HashInsertAndFind_Test(void);
void HashSizeAndIsEmpty_Test(void);
void HashRemove_Test(void);
void HashForEach_Test(void);

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
    
    HashCreate_Test();
	HashInsertAndFind_Test();
	HashSizeAndIsEmpty_Test();
	HashRemove_Test(); 
	HashForEach_Test();

    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/*******************************************************************************
                                Test Functions
*******************************************************************************/ 
/******************************************************************************/
static size_t HashFunc(const void *data, void *param)
{
	assert(data);
	assert(param);
	
	return (*(size_t*)data % *(size_t*)param);
}

/******************************************************************************/
static int CompareFunc(const void *left, const void *right)
{
	assert(left);
	assert(right);
	
	return (*(int*)left - *(int*)right);
}

/******************************************************************************/
static int ActionFunc(void *data, void *act_param)
{
	UNUSED_VAR(act_param);
	
	assert(data);
	
	printf("I am an Action func\n");
	
	return (0);
}
 
/******************************************************************************/
void HashCreate_Test(void)
{
	size_t a = 10;
	hash_t *hash = HashCreate(10, &a, &HashFunc, &CompareFunc);
	
	HashDestroy(hash); 
}

/******************************************************************************/
void HashInsertAndFind_Test(void)
{
	size_t a 		 = 10;
	size_t yaron = 123456789;
	size_t may	 = 123456788;
	size_t papa  = 123456787; 
	hash_t *hash = HashCreate(10, &a, &HashFunc, &CompareFunc);

	printf("\n************** Insert and Find - TEST ***********************\n");
	
	HashInsert(hash, &yaron);
	HashInsert(hash, &may);
	
	if (2 != HashSize(hash))
    {
        printf("Test No. 1 \tfailed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	
	if (123456789 != *(size_t*)HashFind(hash, &yaron))
    {
        printf("Test No. 2 \tfailed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	
	if (123456788 != *(size_t*)HashFind(hash, &may))
    {
        printf("Test No. 3 \tfailed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (NULL != HashFind(hash, &papa))
    {
        printf("Test No. 4 \tfailed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	HashDestroy(hash); 
}

/******************************************************************************/
void HashSizeAndIsEmpty_Test(void)
{
	size_t a 		 = 10;
	size_t yaron = 123456789;
	size_t may	 = 123456788;
	size_t papa  = 123456787; 
	hash_t *hash = HashCreate(10, &a, &HashFunc, &CompareFunc);

	printf("\n************** Size and IsEmpty - TEST **********************\n");
	
	if (0 != HashSize(hash))
    {
        printf("Test No. 5 \tfailed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	
	if (!HashIsEmpty(hash))
    {
        printf("Test No. 6 \tfailed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	HashInsert(hash, &yaron);
	HashInsert(hash, &may);
	HashInsert(hash, &papa);
	
	if (3 != HashSize(hash))
    {
        printf("Test No. 7 \tfailed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	
	if (HashIsEmpty(hash))
    {
        printf("Test No. 8 \tfailed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	HashDestroy(hash); 
}

/******************************************************************************/
void HashRemove_Test(void)
{
	size_t a 		 = 10;
	size_t yaron = 123456789;
	size_t may	 = 123456788;
	size_t papa  = 123456787; 
	hash_t *hash = HashCreate(10, &a, &HashFunc, &CompareFunc);

	printf("\n****************** Remove - TEST ****************************\n");
	
	HashInsert(hash, &yaron);
	HashInsert(hash, &may);
	HashInsert(hash, &papa);
	
	HashRemove(hash, &yaron);
	HashRemove(hash, &yaron);
	
	if (2 != HashSize(hash))
    {
        printf("Test No. 9 \tfailed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
	
	if (NULL != HashFind(hash, &yaron))
    {
        printf("Test No. 10 \tfailed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

	HashDestroy(hash); 
}

/******************************************************************************/
void HashForEach_Test(void)
{
	size_t a 		 = 10;
	size_t yaron = 123456789;
	size_t may	 = 123456788;
	size_t papa  = 123456787; 
	hash_t *hash = HashCreate(10, &a, &HashFunc, &CompareFunc);

	printf("\n****************** ForEach - TEST ***************************\n");
	
	HashInsert(hash, &yaron);
	HashInsert(hash, &may);
	HashInsert(hash, &papa);
	HashForEach(hash, &ActionFunc, NULL);

	HashDestroy(hash); 
}
/*******************************************************************************	
****************************** END OF FILE *************************************
*******************************************************************************/	
