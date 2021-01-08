/*****************************************************************************
 * File name:   pqueue_test.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-24 10:06:37
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>          /* printf()             */
#include <stdlib.h>         /* EXIT_SUCCESS         */
#include <assert.h>         /* assert               */

#include "pqueue.h"         /* Forward declarations */         
#include "utils.h"          /* Utils                */ 

/* Macros                  */
 
/* Forward Declarations    */
typedef struct data
{
    void *data;
    int *priority;
} data_t;

void PQEnqueue_test(void);
void PQDequeue_test(void);
void PQPeek_test(void);
void PQIsEmpty_test(void);
void PQSize_test(void);
void PQClear_test(void);
void PQErase_test(void);

int IsMatch(const void *data, const void *args);
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
    
    PQEnqueue_test();
    PQDequeue_test();
    PQPeek_test();
    PQIsEmpty_test();
    PQSize_test();
    PQClear_test();
    PQErase_test();

    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count, tests - count); 
    printf("\n");

    return (EXIT_SUCCESS);
}

/******************************************************************************/
void PQEnqueue_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
 
    pq_t *pq = PQCreate(is_before, NULL);
    data_t *peek = NULL;
    int dat1 = 500;
    int priority1 = 5;
    int dat2 = 300;
    int priority2 = 3;
    int dat3 = 800;
    int priority3 = 8;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
    data_t *data2 = (data_t*)malloc(sizeof(data_t));
    data_t *data3 = (data_t*)malloc(sizeof(data_t));

    printf("\n******************* Enqueue - TEST **************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;
    data2->data = &dat2;
    data2->priority = &priority2;
    data3->data = &dat3;
    data3->priority = &priority3;

    PQEnqueue(pq, data1);
    peek = (data_t*)PQPeek(pq);

    if (500 != *(int*)(peek->data))
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++count;
    }
    
    ++tests;
    PQEnqueue(pq, data2);
    peek = (data_t*)PQPeek(pq);

    if (500 != *(int*)(peek->data))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++count;
    }
    
    ++tests;
    PQEnqueue(pq, data3);
    peek = (data_t*)PQPeek(pq);

    if (800 != *(int*)(peek->data))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++count;
    }
    
    ++tests;
    free(data1);
    free(data2);
    free(data3);
    data1 = NULL;
    data2 = NULL;
    data3 = NULL;

    PQDestroy(pq);
}
    
/******************************************************************************/
void PQDequeue_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
 
    pq_t *pq = PQCreate(is_before, NULL);
    data_t *peek = NULL;
    void *dequeue = NULL;
    int dat1 = 500;
    int priority1 = 5;
    int dat2 = 300;
    int priority2 = 3;
    int dat3 = 800;
    int priority3 = 8;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
    data_t *data2 = (data_t*)malloc(sizeof(data_t));
    data_t *data3 = (data_t*)malloc(sizeof(data_t));

    printf("\n******************* Dequeue - TEST **************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;
    data2->data = &dat2;
    data2->priority = &priority2;
    data3->data = &dat3;
    data3->priority = &priority3;

    PQEnqueue(pq, data1);
    PQEnqueue(pq, data2);
    PQEnqueue(pq, data3);
    PQDequeue(pq);
    peek = (data_t*)PQPeek(pq);
    
    if (500 != *(int*)(peek->data))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++count;
    }
    
    ++tests;
    PQDequeue(pq);
    peek = (data_t*)PQPeek(pq);

    if (300 != *(int*)(peek->data))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++count;
    }
    
    ++tests;
    PQDequeue(pq);
    dequeue = PQDequeue(pq);

    if (NULL != dequeue)
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++count;
    }
    
    ++tests;
    free(data1);
    free(data2);
    free(data3);
    data1 = NULL;
    data2 = NULL;
    data3 = NULL;

    PQDestroy(pq);
}     

/******************************************************************************/
void PQPeek_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
 
    pq_t *pq = PQCreate(is_before, NULL);
    data_t *peek = NULL;
    int dat1 = 500;
    int priority1 = 5;
    int dat2 = 300;
    int priority2 = 3;
    int dat3 = 800;
    int priority3 = 8;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
    data_t *data2 = (data_t*)malloc(sizeof(data_t));
    data_t *data3 = (data_t*)malloc(sizeof(data_t));

    printf("\n******************* Peek - TEST *****************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;
    data2->data = &dat2;
    data2->priority = &priority2;
    data3->data = &dat3;
    data3->priority = &priority3;

    PQEnqueue(pq, data1);
    PQEnqueue(pq, data2);
    PQEnqueue(pq, data3);
    peek = (data_t*)PQPeek(pq);

    if (800 != *(int*)(peek->data))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++count;
    }
    
    ++tests;
    PQDequeue(pq);
    peek = (data_t*)PQPeek(pq);

    if (500 != *(int*)(peek->data))
    {
        printf("Test No. 10 failed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++count;
    }
    
    ++tests;
    PQDequeue(pq);
    peek = (data_t*)PQPeek(pq);

    if (300 != *(int*)(peek->data))
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++count;
    }
    
    ++tests;
    PQDequeue(pq);
    peek = (data_t*)PQPeek(pq);

    if (NULL != peek)
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++count;
    }

    ++tests;
    free(data1);
    free(data2);
    free(data3);
    data1 = NULL;
    data2 = NULL;
    data3 = NULL;

    PQDestroy(pq);
}

/******************************************************************************/
void PQIsEmpty_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
 
    pq_t *pq = PQCreate(is_before, NULL);
    int dat1 = 500;
    int priority1 = 5;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
   

    printf("\n******************* IsEmpty - TEST **************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;

    if (!PQIsEmpty(pq))
    {
        printf("Test No. 13 failed\n");       
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++count;
    }
    
    ++tests;
    PQEnqueue(pq, data1);

    if (PQIsEmpty(pq))
    {
        printf("Test No. 14 failed\n");       
    }
    else
    {
        printf("Test No. 14 succeded\n");
        ++count;
    }
    
    ++tests;
    PQDequeue(pq);

    if (!PQIsEmpty(pq))
    {
        printf("Test No. 15 failed\n");       
    }
    else
    {
        printf("Test No. 15 succeded\n");
        ++count;
    }
    
    ++tests;    
    free(data1);
    data1 = NULL;

    PQDestroy(pq);
}

/******************************************************************************/
void PQSize_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
 
    pq_t *pq = PQCreate(is_before, NULL);
    int dat1 = 500;
    int priority1 = 5;
    int dat2 = 300;
    int priority2 = 3;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
    data_t *data2 = (data_t*)malloc(sizeof(data_t));

    printf("\n******************* Size - TEST *****************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;
    data2->data = &dat2;
    data2->priority = &priority2;

    if (0 != PQSize(pq))
    {
        printf("Test No. 16 failed\n");       
    }
    else
    {
        printf("Test No. 16 succeded\n");
        ++count;
    }
    
    ++tests;
    PQEnqueue(pq, data1);

    if (1 != PQSize(pq))
    {
        printf("Test No. 17 failed\n");       
    }
    else
    {
        printf("Test No. 17 succeded\n");
        ++count;
    }
    
    ++tests;
    PQEnqueue(pq, data2);

    if (2 != PQSize(pq))
    {
        printf("Test No. 18 failed\n");       
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++count;
    }
    
    ++tests;
    free(data1);
    free(data2);
    data1 = NULL;
    data2 = NULL;

    PQDestroy(pq);
}

/******************************************************************************/
void PQClear_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
 
    pq_t *pq = PQCreate(is_before, NULL);
    int dat1 = 500;
    int priority1 = 5;
    int dat2 = 300;
    int priority2 = 3;
    int dat3 = 800;
    int priority3 = 8;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
    data_t *data2 = (data_t*)malloc(sizeof(data_t));
    data_t *data3 = (data_t*)malloc(sizeof(data_t));

    printf("\n******************* Clear - TEST ****************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;
    data2->data = &dat2;
    data2->priority = &priority2;
    data3->data = &dat3;
    data3->priority = &priority3;

    PQEnqueue(pq, data1);
    PQEnqueue(pq, data2);
    PQEnqueue(pq, data3);
    PQClear(pq);

    if (!PQIsEmpty(pq))
    {
        printf("Test No. 19 failed\n");       
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++count;
    }
    
    ++tests;
    free(data1);
    free(data2);
    free(data3);
    data1 = NULL;
    data2 = NULL;
    data3 = NULL;

    PQDestroy(pq);
}

/******************************************************************************/
void PQErase_test(void)
{
    int (*is_before)(const void *left,
                     const void *right, const void *param) = IsBefore;
    int(*is_match)(const void *data,const void *args) = IsMatch;

    pq_t *pq = PQCreate(is_before, NULL);
    data_t *peek = NULL;
    data_t *ret_data = NULL;
    int args1 = 400;
    int args2 = 500;
    int args3 = 800;
    int dat1 = 500;
    int priority1 = 5;
    int dat2 = 300;
    int priority2 = 3;
    int dat3 = 800;
    int priority3 = 8;
    data_t *data1 = (data_t*)malloc(sizeof(data_t));
    data_t *data2 = (data_t*)malloc(sizeof(data_t));
    data_t *data3 = (data_t*)malloc(sizeof(data_t));

    printf("\n******************* Erase - TEST ****************************\n");

    data1->data = &dat1;
    data1->priority = &priority1;
    data2->data = &dat2;
    data2->priority = &priority2;
    data3->data = &dat3;
    data3->priority = &priority3;

    PQEnqueue(pq, data1);
    peek = (data_t*)PQPeek(pq);
    PQEnqueue(pq, data2);
    peek = (data_t*)PQPeek(pq);
    PQEnqueue(pq, data3);
    peek = (data_t*)PQPeek(pq);
    PQErase(pq, is_match, &args1); 
                                                          
    if (800 != *(int*)(peek->data) || 3 != PQSize(pq))
    {
        printf("Test No. 20 failed\n");       
    }
    else
    {
        printf("Test No. 20 succeded\n");
        ++count;
    }
    
    ++tests;
    PQErase(pq, is_match, &args2);
    peek = (data_t*)PQPeek(pq);

    if (800 != *(int*)(peek->data) || 2 != PQSize(pq))
    {
        printf("Test No. 21 failed\n");       
    }
    else
    {
        printf("Test No. 21 succeded\n");
        ++count;
    }
    
    ++tests;
    ret_data = PQErase(pq, is_match, &args3);
    peek = (data_t*)PQPeek(pq);

    if (300 != *(int*)(peek->data) || 800 != *(int*)(ret_data->data))
    {
        printf("Test No. 22 failed\n");       
    }
    else
    {
        printf("Test No. 22 succeded\n");
        ++count;
    }
    
    ++tests;
    free(data1);
    free(data2);
    free(data3);
    data1 = NULL;
    data2 = NULL;
    data3 = NULL;

    PQDestroy(pq);
}
                                                     
/******************************************************************************/
/* A function that checks the equality of 'data' and 'args' */ 
int IsMatch(const void *data, const void *args)
{
    data_t *dat = (data_t*)data;

    assert(data);
        
    return (*(int*)dat->data == *(int*)args);
}

/******************************************************************************/
/*A function that checks if left's priority is greater than right's priority*/ 
int IsBefore(const void *left, const void *right, const void *param)
{
    data_t *lef = NULL;
    data_t *righ = NULL;

    assert(left);
    assert(right);

    lef = (data_t*)left;
    righ = (data_t*)right;
    
    UNUSED_VAR(param);
    
    return (*lef->priority > *righ->priority);
}

