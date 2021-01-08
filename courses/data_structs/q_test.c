/*****************************************************************************
 * File name:   q_test.c
 * Developer:   Yaron Meister
 * Reviewer:    Yael
 * Date:        2018-11-18 23:30:42
 * Description:
 * Test Flow: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /* EXIT_SUCCESS */
 
#include "q.h"         /*              */
#include "slist.h"     /* sl_node_t    */

/* Macros                  */
 
/* Forward Declarations    */
int QSize_test(void);
int QIsEmpty_test(void);
int QEnqueue_test(void);     
int QDequeue_test(void);
int QPeek_test(void);
int QAppend_test(void);
 
/* Global variables        */
 
/*******************************************************************************
                                Main Function
*******************************************************************************/  
int main(void)
{
                        /* count is the number of tests that succeeded */
    int count = 2;      /* Create and destroy approaved by valgrind */
    int tests = 21;
     
    count += QSize_test();
    count += QIsEmpty_test(); 
    count += QEnqueue_test();
    count += QDequeue_test();
    count += QPeek_test();
    count += QAppend_test();
    
    printf("\n************** SUMARRY OF UNIT-TEST *************************\n");
    printf("%d tests succeeded and %d failed\n", count, tests - count); 
    printf("\n");
 
    return (EXIT_SUCCESS);
}
 
/******************************************************************************/
int QSize_test(void)
{
    int status = 0;
    queue_t *que = QCreate();
    char a = 'a';
    char b = 'b';
    
    printf("\n******************* Qsize - TEST ****************************\n");
    
    if (0 != QSize(que))
    {
        printf("Test No. 1 failed\n");       
    }
    else
    {
        printf("Test No. 1 succeded\n");
        ++status;
    }
    
    QEnqueue(que, &a);
    
    if (1 != QSize(que))
    {
        printf("Test No. 2 failed\n");       
    }
    else
    {
        printf("Test No. 2 succeded\n");
        ++status;
    }
    
    QEnqueue(que, &b);
    
    if (2 != QSize(que))
    {
        printf("Test No. 3 failed\n");       
    }
    else
    {
        printf("Test No. 3 succeded\n");
        ++status;
    }

    QDequeue(que);
    QDequeue(que);
    
    if (0 != QSize(que))
    {
        printf("Test No. 4 failed\n");       
    }
    else
    {
        printf("Test No. 4 succeded\n");
        ++status;
    }
    
    QDestroy(que);

    return (status);
}
 
/******************************************************************************/
int QIsEmpty_test()
{
    int status = 0;
    queue_t *que = QCreate();
    long a = 5;
    
    printf("\n******************* QIsEmpty - TEST *************************\n");
    
    if (!QIsEmpty(que))
    {
        printf("Test No. 5 failed\n");       
    }
    else
    {
        printf("Test No. 5 succeded\n");
        ++status;
    }
    
    QEnqueue(que, &a); 
    
    if (QIsEmpty(que))
    {
        printf("Test No. 6 failed\n");       
    }
    else
    {
        printf("Test No. 6 succeded\n");
        ++status;
    } 
    
    QDequeue(que);
    
    if (!QIsEmpty(que))
    {
        printf("Test No. 7 failed\n");       
    }
    else
    {
        printf("Test No. 7 succeded\n");
        ++status;
    }
    
    QDestroy(que);

    return (status);
}
    
/******************************************************************************/    
int QEnqueue_test(void)
{
    int status = 0;
    int enqueue_status = 0;
    queue_t *que = QCreate();
    long a = 10;
    long b = 20;
    
    printf("\n******************* QEnqueue - TEST *************************\n");
        
    enqueue_status = QEnqueue(que, &a);
    
    if (0 != enqueue_status)
    {
        printf("Test No. 8 failed\n");       
    }
    else
    {
        printf("Test No. 8 succeded\n");
        ++status;
    }
    
    if (10 != *(long*)QPeek(que))
    {
        printf("Test No. 9 failed\n");       
    }
    else
    {
        printf("Test No. 9 succeded\n");
        ++status;
    } 
    
    QEnqueue(que, &b);
    QDequeue(que);
    
    if (20 != *(long*)QPeek(que))
    {
        printf("Test No. 10 failed\n");       
    }
    else
    {
        printf("Test No. 10 succeded\n");
        ++status;
    } 
    
    QDestroy(que);

    return (status);
}   
    
/******************************************************************************/    
int QDequeue_test(void)
{
    int status = 0;
    void *dequeue = NULL;
    queue_t *que = QCreate();
    int a = 10;
    int b = 20;
    
    printf("\n******************* QDequeue - TEST *************************\n");
        
    dequeue = QDequeue(que);
    
    if (NULL != dequeue)
    {
        printf("Test No. 11 failed\n");       
    }
    else
    {
        printf("Test No. 11 succeded\n");
        ++status;
    }
    
    QEnqueue(que, &a);
    QEnqueue(que, &b);
    dequeue = QDequeue(que);
    
    if (10 != *(int*)dequeue)
    {
        printf("Test No. 12 failed\n");       
    }
    else
    {
        printf("Test No. 12 succeded\n");
        ++status;
    }
    
    dequeue = QDequeue(que);
    
    if (20 != *(int*)dequeue)
    {
        printf("Test No. 13 failed\n");       
    }
    else
    {
        printf("Test No. 13 succeded\n");
        ++status;
    }
    
    QDestroy(que);

    return (status);
}       
    
/******************************************************************************/    
int QPeek_test(void)
{
    int status = 0;
    const void *q_peek = NULL;
    queue_t *que = QCreate();
    int a = 10;
    int b = 20;
    
    printf("\n******************* QPeek - TEST ****************************\n"); 
    
    q_peek = QPeek(que);
    
    if (NULL != q_peek)
    {
        printf("Test No. 14 failed\n");       
    }
    else
    {
        printf("Test No. 14 succeded\n");
        ++status;
    }
    
    QEnqueue(que, &a);
    QEnqueue(que, &b);
    
    q_peek = QPeek(que);
    
    if (10 != *(int*)q_peek)
    {
        printf("Test No. 15 failed\n");       
    }
    else
    {
        printf("Test No. 15 succeded\n");
        ++status;
    }
    
    QDequeue(que);
    q_peek = QPeek(que);
    
    if (20 != *(int*)q_peek)
    {
        printf("Test No. 16 failed\n");       
    }
    else
    {
        printf("Test No. 16 succeded\n");
        ++status;
    }
    
    QDestroy(que);

    return (status);
}           
        
/******************************************************************************/    
int QAppend_test(void)
{
    int status = 0;
    queue_t *que1 = QCreate();
    queue_t *que2 = QCreate();
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    
    printf("\n******************* QAppend - TEST **************************\n"); 
    
    QEnqueue(que1, &a);
    QEnqueue(que1, &b);
    QEnqueue(que2, &c);
    QEnqueue(que2, &d);
    QAppend(que1, que2);
    
    if (NULL != QPeek(que2))
    {
        printf("Test No. 17 failed\n");       
    }
    else
    {
        printf("Test No. 17 succeded\n");
        ++status;
    }
    
    QDequeue(que1);
    QDequeue(que1);
    
    if (30 != *(int*)(QPeek(que1)))
    {
        printf("Test No. 18 failed\n");       
    }
    else
    {
        printf("Test No. 18 succeded\n");
        ++status;
    }
    
    QDequeue(que1);
    
    if (40 != *(int*)(QPeek(que1)))
    {
        printf("Test No. 19 failed\n");       
    }
    else
    {
        printf("Test No. 19 succeded\n");
        ++status;
    }
    
    QDestroy(que1);
    QDestroy(que2);

    return (status);
}          
    
  
