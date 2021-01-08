/*****************************************************************************
 * File name:   fsm_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Sandra
 * Date:        2018-12-04 14:44:05
 * Test Flow:   Test cases
 * 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "fsm.h"       /*   fsm.c      */

 
/****************************Forward Declarations******************************/
void FsmSuggestSize_test(void);
void FsmInit_test(void);
void FsmAlloc_test(void);
void FsmFree_test(void);
void FsmCountFree_test(void);
 
/*****************************Global variables*********************************/
static int g_count = 0;        
static int g_tests = 0;        

/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{ 
    FsmSuggestSize_test();
    FsmInit_test();
    FsmAlloc_test();
    FsmFree_test();
    FsmCountFree_test();
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");
      
    return (EXIT_SUCCESS);
}

/******************************************************************************/
void FsmSuggestSize_test(void)
{
    size_t block_size = 5;
    size_t num_of_blocks1 = 0;
    size_t num_of_blocks2 = 2;
    
    printf("\n*************** SuggestSize - TEST **************************\n");    
    
    if (24 != FsmSuggestSize(num_of_blocks1, block_size))
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
     
    if (56 != FsmSuggestSize(num_of_blocks2, block_size))
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
}

/******************************************************************************/
void FsmInit_test(void)
{
    void *segment = malloc(600);
    if (NULL == segment)
    {
        return;
    }

    printf("\n****************** Init - TEST ******************************\n");  
     
    FsmInit(segment, 2, 5);
    
    if (24 != *(size_t*)((char*)segment + 16))
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (40 != *(size_t*)((char*)segment + 24))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    if (0 != *(size_t*)((char*)segment + 40))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
     
    free(segment); 
}

/******************************************************************************/
void FsmAlloc_test(void)
{    
    void *block = NULL;
    void *segment = malloc(600);
    if (NULL == segment)
    {
        return;
    }

    printf("\n****************** Alloc - TEST *****************************\n");  
     
    FsmInit(segment, 2, 5);
    block = FsmAlloc(segment);
    
    if (block != ((char*)segment + 32))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    block = FsmAlloc(segment);
    
    if (block != ((char*)segment + 48))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }

    ++g_tests;
    block = FsmAlloc(segment);
    
    if (NULL != block)
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }

    ++g_tests;

    free(segment); 
}

/******************************************************************************/
void FsmFree_test(void)
{
    void *block = NULL; 
    void *segment = malloc(600); 
    if (NULL == segment)
    {
        return;
    }

    printf("\n******************* Free - TEST *****************************\n");  
     
    FsmInit(segment, 2, 5);
    block = FsmAlloc(segment);
    FsmFree(block);
    block = FsmAlloc(segment);
    
    if (block != ((char*)segment + 32))
    {
        printf("Test No. 9  failed\n");       
    }
    else
    {
        printf("Test No. 9  succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    block = FsmAlloc(segment);
    FsmFree(block);
    block = FsmAlloc(segment);

    if (block != ((char*)segment + 48))
    {
        printf("Test No. 10 failed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++g_count;
    }

    ++g_tests;

    free(segment); 
}

/******************************************************************************/
void FsmCountFree_test(void)
{
    void *segment = malloc(600);
    if (NULL == segment)
    {
        return;
    }

    printf("\n******************* Count - TEST ****************************\n");  
     
    FsmInit(segment, 2, 5);
    
    if (2 != FsmCountFree(segment))
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    FsmAlloc(segment);
    
    if (1 != FsmCountFree(segment))
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++g_count;
    }
    
    ++g_tests;    
    FsmAlloc(segment);
    
    if (0 != FsmCountFree(segment))
    {
        printf("Test No. 13 failed\n");       
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++g_count;
    }

    ++g_tests;

    free(segment); 
}

 
