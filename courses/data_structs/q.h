/*****************************************************************************
 * File name:   queue.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-18 13:35:48
 * Description: 
 *****************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__


#include <stddef.h>      /* size_t */



/*********************************************************************

     if the q's that are supplied NULL - it is undfine behavior.
     
**********************************************************************/

typedef struct queue queue_t; 

/*return NULL at faiure*/
queue_t *QCreate(void);

void QDestroy(queue_t *q);

/*  O(n) */
size_t QSize(const queue_t *q);

/*return 1 if empty, 0 else
    O(1)*/
int QIsEmpty(const queue_t *q);

/*return 0 if enqueue successed,!0 for failure
         O(1)*/
int QEnqueue(queue_t *q, void *data);

/* return NULL if the q is empty 
return the element that went off the q
    O(1) */
void *QDequeue(queue_t *q);

/* Returns a pointer to the data that at the head of the queue and NULL
   if the queue is empty */
const void *QPeek(const queue_t *q);

/*From q remains empty after concatenation 
    O(1) */
void QAppend(queue_t *to, queue_t *from);

 
#endif     /* __QUEUE_H__ */

