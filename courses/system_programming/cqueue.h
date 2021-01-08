/*****************************************************************************
 * File name:   cqueue.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2019-01-24 11:57:27
 * Description: 
 *****************************************************************************/

#ifndef __CQUEUE_H__
#define __CQUEUE_H__

#include <stddef.h>      /* size_t */

/*********************************************************************

     if the cq's that are supplied NULL - it is undfine behavior.
     
**********************************************************************/


typedef struct cqueue cq_t;


/*return NULL at faiure*/
cq_t *CQCreate(void);

void CQDestroy(cq_t *cq);

/*  O(n) */
size_t CQSize(const cq_t *cq);

/*return 1 if empty, 0 else
    O(1)*/
int CQIsEmpty(const cq_t *cq);

/*return 0 if enqueue successed,!0 for failure
         O(1)*/
int CQEnqueue(cq_t *q, int data);

/* return NULL if the q is empty 
return the element that went off the q
    O(1) */
void *CQDequeue(cq_t *cq);

/* Returns a pointer to the data that at the head of the queue and NULL
   if the queue is empty */
int CQPeek(const cq_t *cq);


#endif     /* __CQUEUE_H__ */


/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/
