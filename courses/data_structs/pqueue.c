/*****************************************************************************
 * File name:   pqueue.c
 * Developer:   Yaron Meister
 * Reviewer: 
 * Date:        2018-11-24 10:06:37
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>          /*       printf()          */
#include <stdlib.h>         /*       malloc            */
#include <assert.h>         /*       assert            */

#include "utils.h"          /*      Utils              */
#include "heap.h"       	/*  heap.c declarations    */
#include "pqueue.h"         /* pqueue.c declarations   */


typedef int(*is_before_heap_t)(const void *, const void *, void*);
 
/* Forward Declarations    */
struct priority_queue
{
    heap_t *heap;
};
  
/* Global variables        */
 
/******************************************************************************/
pq_t *PQCreate(int (*is_before)(const void *left, const void *right,
        const void *param), const void *param)
{
    pq_t *pq = (pq_t*)malloc(sizeof(pq_t));                                                           
    if (NULL == pq || NULL == is_before)
    {
        DBG(fprintf(stderr, "\nCreation failed!!!\n"));
        return (NULL);
    }
    else
    {
        pq->heap = HeapCreate(10, (is_before_heap_t)is_before, (void*)param);                                                             
        if (NULL == pq->heap)
        {
            DBG(fprintf(stderr, "\nCreation failed!!!\n"));
            free(pq);
            pq = NULL;
            return (NULL);
        }
    }

    return (pq);
}

/******************************************************************************/
void PQDestroy(pq_t *pq)
{
    assert(pq);                                                                 

    HeapDestroy(pq->heap);
    pq->heap = NULL;
    free(pq);
    pq = NULL;
}
    
/******************************************************************************/
int PQEnqueue(pq_t *pq, void *data)
{
    assert(pq);                                                                 

    return (HeapPush(pq->heap, data));
}
    
/******************************************************************************/
void *PQDequeue(pq_t *pq)
{
    void *data = NULL;

    assert(pq);

    /* Calling for Erase on [END] is undefined, 
     * therefore it's necessary to check if pq is empty
     */
    if (!PQIsEmpty(pq))
    {
    	data = HeapPeek(pq->heap);
        HeapPop(pq->heap);                         
    }

    return (data);
}

/******************************************************************************/    
void *PQPeek(const pq_t *pq)
{
    assert(pq);             /*assert(pq->sort)*/
 
    /* The return gets NULL if pq is empty. The NULL comes from dlist */  
    return (HeapPeek(pq->heap));
} 

/******************************************************************************/
int PQIsEmpty(const pq_t *pq)
{
    assert(pq);

    return (HeapIsEmpty(pq->heap));
}

/******************************************************************************/
size_t PQSize(const pq_t *pq)
{
    assert(pq);       
	assert(pq->heap);
	
    return (HeapSize(pq->heap));
}

/******************************************************************************/
void PQClear(pq_t *pq)
{
         /*assert(p->sort)*/                                                                  
        /* No need assert, assert's check is at PQIsEmpty and PQDequeue */
    while (!PQIsEmpty(pq))
    {
        PQDequeue(pq); 
    }
}

/******************************************************************************/
void *PQErase(pq_t *pq, int(*is_match)(const void *data,const void *args),
                                                               const void *args)

{
	void *temp   = NULL;
	void *erased = NULL;
	
	if (PQIsEmpty(pq) || is_match(PQPeek(pq), args))
	{
		return (PQDequeue(pq));
	}
	
	temp   = PQDequeue(pq);
	erased = PQErase(pq, is_match, args);
	
	PQEnqueue(pq, temp);
	
	return (erased);
}



 
