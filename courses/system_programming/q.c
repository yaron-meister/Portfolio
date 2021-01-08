/*****************************************************************************
 * File name:   q.c
 * Developer:   Yaron Meister
 * Reviewer:    Yael
 * Date:        2018-11-18 23:30:42
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /*              */
#include <assert.h>    /* assert       */

#include "q.h"         /*              */
#include "slist.h"     /* sl_node_t    */

/* Macros                  */
 
 
/* Forward Declarations    */
struct queue 
{
     sl_node_t *head;
     sl_node_t *tail;     
}; 
 
/* Global variables        */
 
 
/******************************************************************************/ 
queue_t *QCreate(void)
{
    queue_t *que = (queue_t*)malloc(sizeof(queue_t));
    if (NULL == que)
    {
        fprintf(stderr, "Malloc failed!!!");
        return (NULL);
    }

    que->head = SLCreateNode(NULL, "dump");   /* head is always a DUMMY node */
    que->tail  = que->head;

    return (que);
}

/******************************************************************************/
void QDestroy(queue_t *q)
{
    assert(q);

    SLFreeAll(q->head); 
    free(q);
    q = NULL;
}  

/******************************************************************************/
size_t QSize(const queue_t *q)
{    
    assert(q);
    
    return (SLCount(q->head) - 1);      /* DUMMY is not included */
}
    
/******************************************************************************/
int QIsEmpty(const queue_t *q)
{
    assert(q);
    
    return (NULL == q->head->next);
}    

/******************************************************************************/
int QEnqueue(queue_t *q, void *data)
{
    sl_node_t *new_node = NULL;
    
    assert(q);
    assert(data);
    
    new_node = SLCreateNode(NULL, data);
    if (NULL != new_node)
    {
        SLInsertAfter(q->tail, new_node);
        q->tail = new_node;                  /* Passing 'tail' to the end */
        return (q->tail->data != data); 
    }
    
    return (1);
}  
/******************************************************************************/    
void *QDequeue(queue_t *q)
{
    void *ret = NULL;
    
    assert(q);
    
    if (!QIsEmpty(q))
    {
        ret = q->head->next->data;
        SLFreeNode(SLRemoveAfter(q->head));
    }
    
    if (QIsEmpty(q))
    {
        q->tail = q->head;
    }
    
    return (ret);
}

/******************************************************************************/
const void *QPeek(const queue_t *q)
{
    const void *ret = NULL; 
    assert(q);
    
    if (!QIsEmpty(q))
    {
        ret = q->head->next->data;
    }
    
    return (ret);
}
   
/******************************************************************************/        
void QAppend(queue_t *to, queue_t *from)
{    
    assert(to);
    assert(from);
    
    to->tail->next = from->head->next;      /* Concatenating                 */
    to->tail = from->tail;                  /* Passing 'tail' to the end     */
    from->head->next = NULL;                /* Cutting 'from' from his nodes */
    from->tail  = from->head;
}   
    
    
    
    
    
    
    
    
    
    
    
    
    
    






 
