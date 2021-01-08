/*****************************************************************************
 * File name:   pqueue.h
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-22 18:02:53
 * Description: Header File for Priority Queue
 *****************************************************************************/
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

typedef struct priority_queue pq_t;

/* Create an empty Priority queue */
/* Returns NULL on malloc() failure */
/* is_before is a boolean function, thus returns either truthy or zero */
/* If is_before is NULL, list creation fails */
/* param is volunatry, may be NULL */
/* Complexity: O(1) */
pq_t *PQCreate(int (*is_before)(const void *left, const void *right,
        const void *param), const void *param);

/* Frees all allocated memory */
/* Complexity: O(n) */
void PQDestroy(pq_t *q);

/* Inserts the element to the queue according to its priority */
/* is_before determines the sorting criteria */
/* Complexity: O(n) */
int PQEnqueue(pq_t *q, void *data);

/* Removes the top priority element */
/* returns NULL if queue is empty */
/* Complexity: O(1) */
void *PQDequeue(pq_t *q);

/* Returns a pointer to the top priority data */
/* returns NULL if queue is empty */
/* Complexity: O(1) */
void *PQPeek(const pq_t *q);

/* Returns truthy if queue is empty */
/* returns 0 if queue is not empty */
/* Complexity: O(1) */
int PQIsEmpty(const pq_t *q);

/* Returns the number of elements in the queue or 0 if empty */
/* Complexity: O(n) */
size_t PQSize(const pq_t *q);

/* Dequeues all the elements from the queue */
/* Complexity: O(n) */
void PQClear(pq_t *q);

/* Remove the first element returning truthy from function is_match */
/* and return a pointer to its data */
/* Complexity: O(n) */
void *PQErase(pq_t *q, int(*is_match)(const void *data,const void *args), const void *args);
 
#endif     /* __PQUEUE_H__ */

