/*****************************************************************************
 * File name:   vsm_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Nir
 * Date:        2018-12-05 16:08:35
 * Test Flow:   Test cases
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <unistd.h>    /*    ssize_t   */
  
#include "vsm.h"       /*              */
 
/****************************Forward Declarations******************************/
void VSMInit_test(void);
void VSMAlloc_test(void);
void VSMFree_test(void);
void VSMCountFree_test(void);
void VSMLargestBlock_test(void);
 
/*****************************Global variables*********************************/
static int g_count = 0;        
static int g_tests = 0;        

/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{ 
    VSMInit_test();
    VSMAlloc_test();
    VSMFree_test();
    VSMCountFree_test();
    VSMLargestBlock_test();
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", g_count, g_tests - g_count); 
    printf("\n");
    
    return (EXIT_SUCCESS);
}

/******************************************************************************/
void VSMInit_test(void)
{
    void *segment = malloc(1500);
    if (NULL == segment)
    {
        return;
    }

    VSMInit(segment, 1000);

    printf("\n****************** Init - TEST ******************************\n");    

    if (1000 != *(size_t*)segment)
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

#ifndef NDEBUG
    if (976 != *(size_t*)((char*)segment + 8))
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    
    free(segment);
    segment = NULL;
    return;
#endif

    if (984 != *(ssize_t*)((char*)segment + 8))
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

    free(segment);
    segment = NULL;
}

/******************************************************************************/
void VSMAlloc_test(void)
{
    vsm_t *vsm = NULL;
    void *pointer1 = NULL;
    void *segment = malloc(1500);
    if (NULL == segment)
    {
        return;
    }

    printf("\n****************** Alloc - TEST *****************************\n");    

    vsm = VSMInit(segment, 1000);
    pointer1 = VSMAlloc(vsm, 50);


    if (-56 != *(ssize_t*)((char*)segment + 8))
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

#ifndef NDEBUG 
    if (pointer1 != (void*)((char*)segment + 24))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

    if (904 != *(ssize_t*)((char*)pointer1 + 56))
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
    segment = NULL;
    return;
#endif

    if (pointer1 != (void*)((char*)segment + 16))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

    if (920 != *(ssize_t*)((char*)pointer1 + 56))
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
    segment = NULL;
}

/******************************************************************************/
void VSMFree_test(void)
{
    vsm_t *vsm = NULL;
    void *pointer1 = NULL;
    void *pointer2 = NULL;
    void *segment = malloc(1500);
    if (NULL == segment)
    {
        return;
    }

    printf("\n******************* Free - TEST *****************************\n");    

    vsm = VSMInit(segment, 1000);
    pointer1 = VSMAlloc(vsm, 50);
    pointer2 = VSMAlloc(vsm, 104);
    VSMFree(pointer1);

    if (56 != *(ssize_t*)((char*)segment + 8))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

#ifndef NDEBUG
    VSMFree((char*)pointer2 + 1);
 
    if (-104 != *(ssize_t*)((char*)pointer2 - 16))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
   
    free(segment);
    segment = NULL;
    return;
#endif

    VSMFree(pointer2);
 
    if (104 != *(ssize_t*)((char*)pointer2 - 8))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
   
    free(segment);
    segment = NULL;
}

/******************************************************************************/
void VSMCountFree_test(void)
{
    vsm_t *vsm = NULL;
    void *pointer = NULL;
    void *segment = malloc(1500);
    if (NULL == segment)
    {
        return;
    }

    printf("\n******************* CountFree - TEST ************************\n");    

    vsm = VSMInit(segment, 1000);

#ifndef NDEBUG
    if (976 != VSMCountFree(vsm))
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    pointer = VSMAlloc(vsm, 960);

    if (0 != VSMCountFree(vsm))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    VSMFree(pointer);
    pointer = VSMAlloc(vsm, 976);

    if (NULL != pointer)
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
    segment = NULL;
    return;
#endif

    if (984 != VSMCountFree(vsm))
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    pointer = VSMAlloc(vsm, 976);

    if (0 != VSMCountFree(vsm))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    VSMFree(pointer);
    pointer = VSMAlloc(vsm, 984);

    if (NULL != pointer)
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
    segment = NULL;
}

/******************************************************************************/
void VSMLargestBlock_test(void)
{
    vsm_t *vsm = NULL;
    void *pointer1 = NULL;
    void *pointer2 = NULL;
    void *segment = malloc(1500);
    if (NULL == segment)
    {
        return;
    }

    printf("\n***************** LargetBlock - TEST ************************\n");    

    vsm = VSMInit(segment, 1000);
    pointer1 = VSMAlloc(vsm, 500);
    pointer2 = VSMAlloc(vsm, 102);
    VSMFree(pointer1);

    if (504 != VSMLargestBlock(vsm))
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++g_count;
    }
    
    ++g_tests;
    VSMFree(pointer2);
    VSMAlloc(vsm, VSMCountFree(vsm));

    if (0 != VSMLargestBlock(vsm))
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++g_count;
    }
    
    ++g_tests;

    free(segment);
    segment = NULL;
}

