/*****************************************************************************
 * File name:   dlist_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Daniel
 * Date:        2018-11-20 11:04:53
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>    /* Memcpy       */
 
#include "dlist.h"       /*              */


/* Macros                  */
 
/* Forward Declarations    */
int DListCount_test(void);
int DListIsEmpty_test(void);
int DListBegin_test(void);
int DListEnd_test(void);
int DListNext_test(void);
int DListPrev_test(void);
int DListGetData_test(void);
int DListIsSameIter_test(void);
int DListIsBadIter_test(void);
int DListInsert_test(void);
int DListErase_test(void);
int DListPushFront_test(void);
int DListPushBack_test(void);
int DListPopFront_test(void);
int DListPopBack_test(void);
int DListSpliceBefore_test(void);
int DListForEach_test(void);
int DListFind_test(void);

int CompareData(const void *data, const void *param);
int Action(void *data, void *param);

 
/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/ 
int main(void)
{
                        /* count is the number of tests that succeeded */
    int count = 2;      /* Create and Destroy approaved by valgrind    */
    int tests = 45;
 
    count += DListCount_test();
    count += DListIsEmpty_test();
    count += DListBegin_test();
    count += DListEnd_test();
    count += DListNext_test();
    count += DListPrev_test();
    count += DListGetData_test();
    count += DListIsSameIter_test();
    count += DListIsBadIter_test();
    count += DListInsert_test();
    count += DListErase_test(); 
    count += DListPushFront_test(); 
    count += DListPushBack_test(); 
    count += DListPopFront_test(); 
    count += DListPopBack_test(); 
    count += DListSpliceBefore_test();
    count += DListForEach_test();
    count += DListFind_test();  
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count, tests - count); 
    printf("\n");
  
    return (EXIT_SUCCESS);
}

/******************************************************************************/
int DListCount_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    int a = 5;
    int b = 55;
    size_t count = 0;
    
    printf("\n******************* Count - TEST ****************************\n");
    count = DListCount(dlist);
    
    if (0 != count)
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++status;
    }
    
    DListInsert(DListEnd(dlist), &a);
    count = DListCount(dlist);
    
    if (1 != count)
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++status;
    }
    
    DListInsert(DListEnd(dlist), &b);
    count = DListCount(dlist);
    
    if (2 != count)
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListIsEmpty_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    int a = 5;
    dlist_iter_t iter = NULL;
    
    printf("\n******************* IsEmpty - TEST **************************\n");
   
    if (!DListIsEmpty(dlist))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++status;
    }
    
    iter = DListInsert(DListEnd(dlist), &a);

    if (DListIsEmpty(dlist))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++status;
    }
    
    DListErase(iter, NULL);
    
    if (!DListIsEmpty(dlist))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListBegin_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    int a = 5;
    int b = 55;
    
    printf("\n******************* Begin - TEST ****************************\n");
   
    if (DListBegin(dlist) != DListEnd(dlist))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++status;
    }
    
    DListInsert(DListEnd(dlist), &a);
    DListInsert(DListEnd(dlist), &b);

    if (5 != *(int*)DListGetData(DListBegin(dlist)))
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListEnd_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    int a = 5;
    int b = 55;
    
    printf("\n******************* End - TEST ******************************\n");
      
    DListInsert(DListEnd(dlist), &a);
    DListInsert(DListEnd(dlist), &b);

    if (55 != *(int*)DListGetData(DListPrev(DListEnd(dlist))))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListNext_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    int a = 5;
    int b = 55;
    
    printf("\n******************* Next - TEST *****************************\n");
    
    DListInsert(DListEnd(dlist), &a);
    DListInsert(DListEnd(dlist), &b);

    if (55 != *(int*)DListGetData(DListNext(DListBegin(dlist))))
    {
        printf("Test No. 10 failed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}


/******************************************************************************/
int DListPrev_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    int a = 5;
    int b = 55;
    
    printf("\n******************* Prev - TEST *****************************\n");
    
    DListInsert(DListEnd(dlist), &a);
    DListInsert(DListEnd(dlist), &b);

    if (55 != *(int*)DListGetData(DListPrev(DListEnd(dlist))))
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListGetData_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = DListEnd(dlist);
    int a = 5;
    
    printf("\n******************* GetData - TEST **************************\n");

    if (NULL != DListGetData(iter))
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++status;
    }
    
    iter = DListInsert(DListEnd(dlist), &a);
    
    if (5 != *(int*)DListGetData(iter))
    {
        printf("Test No. 13 failed\n");       
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListIsSameIter_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = DListEnd(dlist);
    int a = 5;
    
    printf("\n******************* IsSameIter - TEST ***********************\n");

    if (!DListIsSameIter(DListBegin(dlist), iter))
    {
        printf("Test No. 14 failed\n");       
    }
    else
    {
        printf("Test No. 14 succeded\n");
        ++status;
    }
    
    iter = DListInsert(DListEnd(dlist), &a);
    
    if (!DListIsSameIter(DListBegin(dlist), iter))
    {
        printf("Test No. 15 failed\n");       
    }
    else
    {
        printf("Test No. 15 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListIsBadIter_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    
    printf("\n******************* IsBadIter - TEST ************************\n");

    if (!DListIsBadIter(iter))
    {
        printf("Test No. 16 failed\n");       
    }
    else
    {
        printf("Test No. 16 succeded\n");
        ++status;
    }
    
    iter = DListInsert(DListEnd(dlist), &a);
    
    if (DListIsBadIter(iter))
    {
        printf("Test No. 17 failed\n");       
    }
    else
    {
        printf("Test No. 17 succeded\n");
        ++status;
    }
    
    iter = DListEnd(dlist);
    
    if (!DListIsBadIter(iter))
    {
        printf("Test No. 18 failed\n");       
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}


/******************************************************************************/
int DListInsert_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* Insert - TEST ***************************\n");

    DListInsert(DListEnd(dlist), &b);
    DListInsert(DListPrev(DListEnd(dlist)), &a);
    DListInsert(DListEnd(dlist), &c);
    iter = DListBegin(dlist);
    
    if (5 != *(int*)DListGetData(iter))
    {
        printf("Test No. 19 failed\n");       
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++status;
    }
    
    iter = DListNext(iter);
    
    if (55 != *(int*)DListGetData(iter))
    {
        printf("Test No. 20 failed\n");       
    }
    else
    {
        printf("Test No. 20 succeded\n");
        ++status;
    }
    
    iter = DListNext(iter);
    
    if (555 != *(int*)DListGetData(iter))
    {
        printf("Test No. 21 failed\n");       
    }
    else
    {
        printf("Test No. 21 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListErase_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* Erase - TEST ****************************\n");

    DListInsert(DListEnd(dlist), &b);
    DListInsert(DListPrev(DListEnd(dlist)), &a);
    DListInsert(DListEnd(dlist), &c);
    iter = DListBegin(dlist);
    iter = DListErase(iter, NULL);
    
    if (55 != *(int*)DListGetData(iter))
    {
        printf("Test No. 22 failed\n");       
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++status;
    }
    
    iter = DListErase(iter, NULL);
    
    if (555 != *(int*)DListGetData(iter))
    {
        printf("Test No. 23 failed\n");       
    }
    else
    {
        printf("Test No. 23 succeded\n");
        ++status;
    }
       
    iter = DListErase(iter, NULL);
    
    if (DListEnd(dlist) != iter)
    {
        printf("Test No. 24 failed\n");       
    }
    else
    {
        printf("Test No. 24 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListPushFront_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* PushFront - TEST ************************\n");

    DListPushFront(dlist, &c);
    DListPushFront(dlist, &b);
    DListPushFront(dlist, &a);
    iter = DListBegin(dlist);
    
    if (5 != *(int*)DListGetData(iter))
    {
        printf("Test No. 25 failed\n");       
    }
    else
    {
        printf("Test No. 25 succeded\n");
        ++status;
    }
    
    iter = DListNext(iter);
    
    if (55 != *(int*)DListGetData(iter))
    {
        printf("Test No. 26 failed\n");       
    }
    else
    {
        printf("Test No. 26 succeded\n");
        ++status;
    }
       
    iter = DListNext(iter);
    
    if (555 != *(int*)DListGetData(iter))
    {
        printf("Test No. 27 failed\n");       
    }
    else
    {
        printf("Test No. 27 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListPushBack_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* PushBack - TEST *************************\n");

    DListPushBack(dlist, &a);
    DListPushBack(dlist, &b);
    DListPushBack(dlist, &c);
    iter = DListBegin(dlist);
    
    if (5 != *(int*)DListGetData(iter))
    {
        printf("Test No. 28 failed\n");       
    }
    else
    {
        printf("Test No. 28 succeded\n");
        ++status;
    }
    
    iter = DListNext(iter);
    
    if (55 != *(int*)DListGetData(iter))
    {
        printf("Test No. 29 failed\n");       
    }
    else
    {
        printf("Test No. 29 succeded\n");
        ++status;
    }
       
    iter = DListNext(iter);
    
    if (555 != *(int*)DListGetData(iter))
    {
        printf("Test No. 30 failed\n");       
    }
    else
    {
        printf("Test No. 30 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListPopFront_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* PopFront - TEST *************************\n");

    DListPushBack(dlist, &a);
    DListPushBack(dlist, &b);
    DListPushBack(dlist, &c);
    DListPopFront(dlist);
    iter = DListBegin(dlist);
    
    if (55 != *(int*)DListGetData(iter))
    {
        printf("Test No. 31 failed\n");       
    }
    else
    {
        printf("Test No. 31 succeded\n");
        ++status;
    }
    
    DListPopFront(dlist);
    iter = DListBegin(dlist);
    
    if (555 != *(int*)DListGetData(iter))
    {
        printf("Test No. 32 failed\n");       
    }
    else
    {
        printf("Test No. 32 succeded\n");
        ++status;
    }
       
    DListPopFront(dlist);
    
    if (NULL != DListPopFront(dlist))
    {
        printf("Test No. 33 failed\n");       
    }
    else
    {
        printf("Test No. 33 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListPopBack_test(void)
{
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t iter = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    
    printf("\n******************* PopBack - TEST **************************\n");

    DListPushBack(dlist, &a);
    DListPushBack(dlist, &b);
    DListPushBack(dlist, &c);
    DListPopBack(dlist);
    iter = DListBegin(dlist);
    
    if (5 != *(int*)DListGetData(iter))
    {
        printf("Test No. 34 failed\n");       
    }
    else
    {
        printf("Test No. 34 succeded\n");
        ++status;
    }
    
    DListPopBack(dlist);
    iter = DListBegin(dlist);
    
    if (5 != *(int*)DListGetData(iter))
    {
        printf("Test No. 35 failed\n");       
    }
    else
    {
        printf("Test No. 35 succeded\n");
        ++status;
    }
       
    DListPopBack(dlist);
    
    if (NULL != DListPopBack(dlist))
    {
        printf("Test No. 36 failed\n");       
    }
    else
    {
        printf("Test No. 36 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}

/******************************************************************************/
int DListSpliceBefore_test(void)
{
    int status = 0;
    dlist_t *dlist1 = DListCreate();
    dlist_t *dlist2 = DListCreate();
    dlist_iter_t dest = NULL;
    dlist_iter_t to = NULL;
    dlist_iter_t from = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    int d = 5555;
    int e = 55555;
    
    printf("\n******************* Splice - TEST ***************************\n");

    DListPushBack(dlist1, &a);
    DListPushBack(dlist1, &b);
    DListPushBack(dlist1, &c);
    
    DListPushBack(dlist2, &d);
    DListPushBack(dlist2, &e);
       
    if (3 != DListCount(dlist1))
    {
        printf("Test No. 37 failed\n");       
    }
    else
    {
        printf("Test No. 37 succeded\n");
        ++status;
    }
    
    if (2 != DListCount(dlist2))
    {
        printf("Test No. 38 failed\n");       
    }
    else
    {
        printf("Test No. 38 succeded\n");
        ++status;
    }
    
    dest = DListNext(DListNext(DListBegin(dlist1)));
    from = DListNext(DListBegin(dlist2));
    to = DListNext(from);
    DListSpliceBefore(dest, from, to);

    if (4 != DListCount(dlist1))
    {
        printf("Test No. 39 failed\n");       
    }
    else
    {
        printf("Test No. 39 succeded\n");
        ++status;
    }
    
    if (1 != DListCount(dlist2))
    {
        printf("Test No. 40 failed\n");       
    }
    else
    {
        printf("Test No. 40 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist1);
    DListDestroy(dlist2);

    return (status);
}

/******************************************************************************/
int DListForEach_test(void)
{
    /* Action's implementation is at the bottom */
    int (*action_func)(void *data, void *param) = Action;
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t from = NULL;
    dlist_iter_t to = NULL;
    int a = 5;
    int b = 55;
    int c = 555;
    int d = 0;
    DListPushBack(dlist, &a);
    DListPushBack(dlist, &b);
    DListPushBack(dlist, &c);
    from = DListBegin(dlist);
    to = DListEnd(dlist);
    
    printf("\n******************* ForEach - TEST **************************\n"); 

    if (to != DListForEach(from, to, action_func, &d))
    {
        printf("Test No. 41 failed\n");
    }
    else
    {
        printf("Test No. 41 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
}  

/******************************************************************************/
int DListFind_test(void)
{
    /* CompareData's implementation is at the bottom */
    int (*compare_func)(const void *data, const void *param) = CompareData;
    int status = 0;
    dlist_t *dlist = DListCreate();
    dlist_iter_t from = NULL;
    dlist_iter_t to = NULL;
    int a = 5;
    int b = 55;
    int c = 55;
    int d = 50;
    DListPushBack(dlist, &a);
    DListPushBack(dlist, &b);
    from = DListBegin(dlist);
    to = DListEnd(dlist);

    printf("\n******************* Find - TEST *****************************\n"); 

    if (DListFind(from, to, compare_func, &c) != DListNext(DListBegin(dlist)))
    {
        printf("Test No. 42 failed\n");
    }
    else
    {
        printf("Test No. 42 succeded\n");
        ++status;
    }

    if (to != DListFind(from, to, compare_func, &d))
    {
        printf("Test No. 43 failed\n");
    }
    else
    {
        printf("Test No. 43 succeded\n");
        ++status;
    }
    
    DListDestroy(dlist);

    return (status);
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

 
