/*****************************************************************************
 * File name:   sortlist_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Eran
 * Date:        2018-11-22 08:43:32
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>          /* printf()             */
#include <stdlib.h>         /* EXIT_SUCCESS         */
#include <assert.h>         /* assert               */
#include <string.h>         /* memcpy               */

#include "utils.h"          /* Utils                */ 
#include "sortlist.h"       /* Forward declarations */


/* Macros                  */
 
/* Forward Declarations    */
void SortListSize_test(void);
void SortListIsEmpty_test(void);
void SortListEnd_test(void);
void SortListBegin_test(void);
void SortListNext_test(void);
void SortListPrev_test(void);
void SortListIsSameIter_test(void);
void SortListIsBadIter_test(void);
void SortListGetData_test(void);
void SortListInsert_test(void);
void SortListErase_test(void);
void SortListPopFront_test(void);
void SortListPopBack_test(void);
void SortListForEach_test(void);
void SortListFind_test(void);
void SortListMerge_test1(void);

int CompareData(const void *data, const void *param);
int Action(void *data, void *param);
int IsBefore(const void *left, const void *right, const void *param);
 
/* Global variables */

static int count = 2;        /* count is the number of tests that succeeded */
static int tests = 2;        /* Create and Destroy approaved by valgrind    */

/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{ 
    printf("\n******************* Create and Destroy - TEST ***************\n");
    printf("Test No. 1 succeded --- (by valgrind)\n");
    printf("Test No. 2 succeded --- (by valgrind)\n");
    
    SortListSize_test();
    SortListIsEmpty_test();
    SortListEnd_test();
    SortListBegin_test();
    SortListNext_test();
    SortListPrev_test();
    SortListIsSameIter_test();
    SortListIsBadIter_test();
    SortListGetData_test();
    SortListInsert_test();
    SortListErase_test();
    SortListPopFront_test();
    SortListPopBack_test();
    SortListForEach_test();
    SortListFind_test();
    SortListMerge_test1();
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count, tests - count); 
    printf("\n");
  
    return (EXIT_SUCCESS);
}

/******************************************************************************/
void SortListSize_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    int a = 5;
    int b = 55;
    size_t count1 = 0;
    
    printf("\n******************* Size - TEST *****************************\n");
    count1 = SortListSize(sortlist);
    
    if (0 != count1)
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListInsert(sortlist, &a);
    count1 = SortListSize(sortlist);
    
    if (1 != count1)
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListInsert(sortlist, &b);
    count1 = SortListSize(sortlist);
    
    if (2 != count1)
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}
          
/******************************************************************************/
void SortListIsEmpty_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    int a = 5;
    sortlist_iter_t iter = NULL;
    
    printf("\n******************* IsEmpty - TEST **************************\n");
   
    if (!SortListIsEmpty(sortlist))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListInsert(sortlist, &a);

    if (SortListIsEmpty(sortlist))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListErase(iter, NULL);
    
    if (!SortListIsEmpty(sortlist))
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListEnd_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    int a = 5;
    int b = 55;
    
    printf("\n******************* End - TEST ******************************\n");

    SortListInsert(sortlist, &b);      
    SortListInsert(sortlist, &a);
    

    if (55 != *(int*)SortListGetData(SortListPrev(SortListEnd(sortlist))))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListBegin_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    int a = 5;
    int b = 55;
    
    printf("\n******************* Begin - TEST ****************************\n");
   
    if (SortListBegin(sortlist) != SortListEnd(sortlist))
    {
        printf("Test No. 10 failed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListInsert(sortlist, &b);   
    SortListInsert(sortlist, &a);    

    if (5 != *(int*)SortListGetData(SortListBegin(sortlist)))
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListNext_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    int a = 5;
    int b = 55;
    
    printf("\n******************* Next - TEST *****************************\n");

    SortListInsert(sortlist, &b);    
    SortListInsert(sortlist, &a);
    
    if (55 != *(int*)SortListGetData(SortListNext(SortListBegin(sortlist))))
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListPrev_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    int a = 5;
    int b = 55;
    
    printf("\n******************* Prev - TEST *****************************\n");

    SortListInsert(sortlist, &b);    
    SortListInsert(sortlist, &a);
    

    if (55 != *(int*)SortListGetData(SortListPrev(SortListEnd(sortlist))))
    {
        printf("Test No. 13 failed\n");       
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListIsSameIter_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = SortListEnd(sortlist);
    int a = 5;
    
    printf("\n******************* IsSameIter - TEST ***********************\n");

    if (!SortListIsSameIter(SortListBegin(sortlist), iter))
    {
        printf("Test No. 14 failed\n");       
    }
    else
    {
        printf("Test No. 14 succeded\n");
        ++count;
    }

    ++tests;    
    iter = SortListInsert(sortlist, &a);
    
    if (!SortListIsSameIter(SortListBegin(sortlist), iter))
    {
        printf("Test No. 15 failed\n");       
    }
    else
    {
        printf("Test No. 15 succeded\n");
        ++count;
    }

    ++tests;    
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListIsBadIter_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = NULL;
    int a = 5;
    
    printf("\n******************* IsBadIter - TEST ************************\n");

    if (!SortListIsBadIter(iter))
    {
        printf("Test No. 16 failed\n");       
    }
    else
    {
        printf("Test No. 16 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListInsert(sortlist, &a);
    
    if (SortListIsBadIter(iter))
    {
        printf("Test No. 17 failed\n");       
    }
    else
    {
        printf("Test No. 17 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListEnd(sortlist);
    
    if (!SortListIsBadIter(iter))
    {
        printf("Test No. 18 failed\n");       
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListGetData_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = SortListEnd(sortlist);
    int a = 5;
    
    printf("\n******************* GetData - TEST **************************\n");

    if (NULL != SortListGetData(iter))
    {
        printf("Test No. 19 failed\n");       
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListInsert(sortlist, &a);
    
    if (5 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 20 failed\n");       
    }
    else
    {
        printf("Test No. 20 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListInsert_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = SortListEnd(sortlist);
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* Insert - TEST ***************************\n");

    SortListInsert(sortlist, &c);
    SortListInsert(sortlist, &a);
    SortListInsert(sortlist, &b);
    iter = SortListBegin(sortlist);
    
    if (5 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 21 failed\n");       
    }
    else
    {
        printf("Test No. 21 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListNext(iter);
    
    if (55 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 22 failed\n");       
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListNext(iter);
    
    if (555 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 23 failed\n");       
    }
    else
    {
        printf("Test No. 23 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListErase_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = SortListEnd(sortlist);
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* Erase - TEST ****************************\n");

    SortListInsert(sortlist, &c);
    SortListInsert(sortlist, &a);
    SortListInsert(sortlist, &b);
    iter = SortListBegin(sortlist);
    iter = SortListErase(iter, NULL);
    
    if (55 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 24 failed\n");       
    }
    else
    {
        printf("Test No. 24 succeded\n");
        ++count;
    }
    
    ++tests;
    iter = SortListErase(iter, NULL);
    
    if (555 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 25 failed\n");       
    }
    else
    {
        printf("Test No. 25 succeded\n");
        ++count;
    }
    
    ++tests;  
    iter = SortListErase(iter, NULL);
    
    if (SortListEnd(sortlist) != iter)
    {
        printf("Test No. 26 failed\n");       
    }
    else
    {
        printf("Test No. 26 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListPopFront_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = SortListEnd(sortlist);
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* PopFront - TEST *************************\n");

    SortListInsert(sortlist, &c);
    SortListInsert(sortlist, &a);
    SortListInsert(sortlist, &b);
    SortListPopFront(sortlist);
    iter = SortListBegin(sortlist);
    
    if (55 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 27 failed\n");       
    }
    else
    {
        printf("Test No. 27 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListPopFront(sortlist);
    iter = SortListBegin(sortlist);
    
    if (555 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 28 failed\n");       
    }
    else
    {
        printf("Test No. 28 succeded\n");
        ++count;
    }
    
    ++tests;   
    SortListPopFront(sortlist);
    
    if (NULL != SortListPopFront(sortlist))
    {
        printf("Test No. 29 failed\n");       
    }
    else
    {
        printf("Test No. 29 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListPopBack_test(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = SortListEnd(sortlist);
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* PopBack - TEST **************************\n");

    SortListInsert(sortlist, &c);
    SortListInsert(sortlist, &a);
    SortListInsert(sortlist, &b);
    SortListPopBack(sortlist);
    iter = SortListBegin(sortlist);
    
    if (5 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 30 failed\n");       
    }
    else
    {
        printf("Test No. 30 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListPopBack(sortlist);
    iter = SortListBegin(sortlist);
    
    if (5 != *(int*)SortListGetData(iter))
    {
        printf("Test No. 31 failed\n");       
    }
    else
    {
        printf("Test No. 31 succeded\n");
        ++count;
    }
    
    ++tests;   
    SortListPopBack(sortlist);
    
    if (NULL != SortListPopBack(sortlist))
    {
        printf("Test No. 32 failed\n");       
    }
    else
    {
        printf("Test No. 32 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}

/******************************************************************************/
void SortListForEach_test(void)
{
    /* Action's implementation is at the bottom */
    int (*action_func)(void *data, void *param) = Action;
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t from = NULL;
    sortlist_iter_t to = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    int d = 0;
    SortListInsert(sortlist, &a);
    SortListInsert(sortlist, &c);
    SortListInsert(sortlist, &b);
    from = SortListBegin(sortlist);
    to = SortListEnd(sortlist);
    
    printf("\n******************* ForEach - TEST **************************\n"); 

    if (to != SortListForEach(from, to, action_func, &d))
    {
        printf("Test No. 33 failed\n");
    }
    else
    {
        printf("Test No. 33 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}  

/******************************************************************************/
void SortListFind_test(void)
{
    /* CompareData's implementation is at the bottom */
    int (*compare_func)(const void *data, const void *param) = CompareData;
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *sortlist = SortListCreate(is_before, NULL);
    sortlist_iter_t from = NULL;
    sortlist_iter_t to = NULL;
    int a = 5;
    int b = 55;
    int c = 55;
    int d = 50;
    SortListInsert(sortlist, &a);
    SortListInsert(sortlist, &b);
    from = SortListBegin(sortlist);
    to = SortListEnd(sortlist);

    printf("\n******************* Find - TEST *****************************\n"); 

    if (SortListFind(from, to, compare_func, &c) !=
                                          SortListNext(SortListBegin(sortlist)))
    {
        printf("Test No. 34 failed\n");
    }
    else
    {
        printf("Test No. 34 succeded\n");
        ++count;
    }
    
    ++tests;

    if (to != SortListFind(from, to, compare_func, &d))
    {
        printf("Test No. 35 failed\n");
    }
    else
    {
        printf("Test No. 35 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(sortlist);
}   

/******************************************************************************/
void SortListMerge_test1(void)
{
    int (*is_before)(const void *left, const void *right, const void *param) = 
    IsBefore;
    
    sortlist_t *dest = SortListCreate(is_before, NULL); 
    sortlist_t *src = SortListCreate(is_before, NULL);
    sortlist_iter_t iter = NULL;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    SortListInsert(dest, &a);
    SortListInsert(dest, &b);
    SortListInsert(dest, &e);
    SortListInsert(src, &c);
    SortListInsert(src, &d);

    printf("\n******************* Merge - TEST ****************************\n");

    SortListMerge(dest, src);
    iter = SortListNext(SortListNext(SortListBegin(dest)));  
    
    if ((3 != *(int*)SortListGetData(iter)) &&  
        (4 != *(int*)SortListGetData(SortListNext(iter))) &&
        (5 != *(int*)SortListGetData(SortListPrev(SortListEnd(dest)))))
    {
        printf("Test No. 36 failed\n");
    }
    else
    {
        printf("Test No. 36 succeded\n");
        ++count;
    }

    ++tests;

    if (!SortListIsEmpty(src))
    {
        printf("Test No. 37 failed\n");
    }
    else
    {
        printf("Test No. 37 succeded\n");
        ++count;
    }
    
    ++tests;
    SortListDestroy(dest);
    SortListDestroy(src);
}   
    
/******************************************************************************/
int Action(void *data, void *param)
{
    memcpy(param, data, sizeof(int));
 
    return  (*(int*) data != *(int*) param);
}
                                                      
/******************************************************************************/
int CompareData(const void *data, const void *param)
{
    return ((*(int*)data != *(int*)param));
}

/******************************************************************************/
/* A function that checks if 'right' is greater than 'left' */ 
int IsBefore(const void *left, const void *right, const void *param)
{
    assert(left);
    assert(right);
    
    UNUSED_VAR(param);
    
    return (*(int*)left < *(int*)right);
}





















  
