/*****************************************************************************
 * File name:   dlist.c
 * Developer:   Yaron
 * Reviewer: 
 * Date:        2018-11-20 11:04:53
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()                */
#include <stdlib.h>    /* malloc                  */
#include <assert.h>    /* assert                  */

#include "dlist.h"     /* Forward declaraations   */
#include "utils.h"     /* utils                   */

/* Macros                  */
#define DEADBEEF 0xDEADBEEFDEADBEEF       /* 0xBADC0FFEE0DDF00D */
 
 
/* Forward Declarations    */
typedef struct dlist_node 
{
    struct dlist_node *next;
    struct dlist_node *prev;
    void *data;
} dlist_node_t;

struct dlist 
{
	struct dlist_node start;
	struct dlist_node end;
};

static dlist_node_t *CreateNode(dlist_node_t *next,
                    dlist_node_t *prev, void *data); 
 
/* Global variables        */
 
 
/******************************************************************************/ 
dlist_t *DListCreate(void)
{
    dlist_t *dlist = (dlist_t*)malloc(sizeof(dlist_t));
    if (NULL == dlist)
    {
        DBG(fprintf(stderr, "Malloc failed!!!\n"));
        return (NULL);
    }
    
    dlist->end.next = NULL;
    dlist->end.prev = &dlist->start;
    dlist->end.data = (void*)DEADBEEF;  
      
    dlist->start.next = &dlist->end;
    dlist->start.prev = NULL;
    dlist->start.data = (void*)DEADBEEF;
    
    return (dlist);
}

/******************************************************************************/
void DListDestroy(dlist_t *dlist)
{
    dlist_iter_t next_to_free = NULL;
    dlist_iter_t temp = NULL;
    
    assert (dlist);
    
    next_to_free = DListBegin(dlist);
    
    while (next_to_free != DListEnd(dlist))
    {
        temp = next_to_free->next;
        
        next_to_free->next = NULL;
        next_to_free->prev = NULL;
        next_to_free->data = NULL;
        free(next_to_free);
        
        next_to_free = temp;
    }
    
    next_to_free =NULL;
    temp = NULL; 
    
    dlist->start.next = NULL;
    dlist->end.prev = NULL;
    free(dlist);
    
    dlist = NULL;
}
   
/******************************************************************************/ 
size_t DListCount(const dlist_t *dlist)
{
    size_t count = 0;
    dlist_iter_t iter = NULL;
    
    assert(dlist);
    
    iter = DListBegin(dlist);
    
    while (iter != DListEnd(dlist))
    {
        ++count;
        iter = iter->next;
    }  
    
    return (count);
} 
        
/******************************************************************************/        
int DListIsEmpty(const dlist_t *dlist)
{
    assert(dlist);
    
    return (dlist->start.next == &dlist->end);
}

/******************************************************************************/ 
dlist_iter_t DListBegin(const dlist_t *dlist)
{
    assert(dlist);
    
    return ((dlist_iter_t)(dlist->start.next));
}

/******************************************************************************/
dlist_iter_t DListEnd(const dlist_t *dlist)
{
    assert(dlist);
    
    return ((dlist_iter_t)&dlist->end);
}
            
/******************************************************************************/        
dlist_iter_t DListNext(dlist_iter_t iter)
{
    assert(iter);
    
    return (iter->next);
}

/******************************************************************************/            
dlist_iter_t DListPrev(dlist_iter_t iter)
{
    assert(iter);
    assert(iter->prev->prev);       /* Checking if iter is 'Begin()' */
    
    return (iter->prev);
}        
        
/******************************************************************************/        
void *DListGetData(const dlist_iter_t iter)
{
    void *data = NULL;
    
    assert(iter);        
       
    if (NULL != iter->next)
    {
        data = iter->data;
    }
    
    return (data);
}
        
/******************************************************************************/        
int DListIsSameIter(dlist_iter_t iter1, dlist_iter_t iter2)
{
    return (iter1 == iter2);
}
    
/******************************************************************************/            
int DListIsBadIter(dlist_iter_t iter)
{         
    if (NULL == iter)
    {
        return (-1);
    }
    else if (NULL == iter->next)
    {
        return (1);
    }
    
    return (0);
}            
        					    								
/******************************************************************************/
dlist_iter_t DListInsert(dlist_iter_t where, void *data)
{
    dlist_node_t *node = NULL;
     
    assert(where);
    
    node = CreateNode((dlist_iter_t)where, where->prev, data);
    
    if (NULL == node)
    {
        DBG(fprintf(stderr, "Insert failed!!!\n"));
        return (NULL);
    }
        
    where->prev->next = node;
    where->prev = node;
        
    return ((dlist_iter_t)node);
}
    
/******************************************************************************/
dlist_iter_t DListErase(dlist_iter_t where, void **data)
{
    dlist_iter_t where_next = NULL;
    
    assert(where);
    
    where_next = DListNext(where);
    
    if (NULL != data)
    {
        *data = where->data;
    }
    
    if (NULL != where->next)
    {
        where->prev->next = where->next;
        where->next->prev = where->prev;
        
        where->next = NULL;
        where->prev = NULL;
        where->data = NULL;
        free(where);
        where = NULL;
    }
    
    return (where_next);
}

/******************************************************************************/
int DListPushFront(dlist_t *dlist, void *data)
{
    dlist_iter_t iter = NULL;
    
    assert(dlist);
    
    iter = DListInsert(DListBegin(dlist), data);
    
    return (NULL == iter);
}
    
    
/******************************************************************************/   
int DListPushBack(dlist_t *dlist, void *data)    
{
    dlist_iter_t iter = NULL;
    
    assert(dlist);
    
    iter = DListInsert(DListEnd(dlist), data);
    
    return (NULL == iter);
}    

/******************************************************************************/
void *DListPopFront(dlist_t *dlist)
{
   void *data = NULL;
   
   assert(dlist);
   
   if (!DListIsEmpty(dlist))
   {
       DListErase(DListBegin(dlist), &data);
   }
   
   return (data);
}  

/******************************************************************************/
void *DListPopBack(dlist_t *dlist)
{
    void *data = NULL;

    assert(dlist);
   
    if (!DListIsEmpty(dlist))
    {
        DListErase(DListPrev(DListEnd(dlist)), &data);
    }
       
    return (data);
}     

/******************************************************************************/
void DListSpliceBefore(dlist_iter_t dest, 
                       dlist_iter_t src_begin, dlist_iter_t src_end)
{ 
    dlist_iter_t end_prev = NULL;       /* Temporary iterator */
      
    assert(dest);
    assert(src_begin);
    assert(src_end);

    if (!DListIsSameIter(src_begin, src_end) && !DListIsBadIter(src_begin))
    {   
        /* Cutting the pile from src */
        end_prev = src_end->prev;           
        src_begin->prev->next = src_end;
        src_end->prev = src_begin->prev;
        
        /* Pushing the pile into the dest list */ 
        src_begin->prev = dest->prev;
        end_prev->next = dest;
        dest->prev->next = src_begin;
        dest->prev = end_prev;
    } 
}

/******************************************************************************/
dlist_iter_t DListForEach(dlist_iter_t from, dlist_iter_t to,
				 int (*action_func)(void *data, void *param),
			  	 void *param)
{
    int status = 0;
    dlist_iter_t temp = from;

    assert(from);
    assert(to);

    while (temp != to)
    {
        status = action_func(temp->data, param);
        
        if (0 != status)
        {
            return (temp);
        }
        
        temp = DListNext(temp);
    }

    return (temp);
}

/******************************************************************************/
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
                int (*compare_func)(const void *data, const void *param), 
                                                      const void *param)
{
    dlist_iter_t temp = from;

    assert(from);
    assert(to);
    
    while (temp != to && 0 != compare_func(temp->data, param))
    {
        temp = DListNext(temp);
    }

    return (temp);
}
       
/******************************************************************************/
static dlist_node_t *CreateNode(dlist_node_t *next,
                                                 dlist_node_t *prev, void *data)
{
    dlist_node_t *node = (dlist_node_t*)malloc(sizeof(dlist_node_t));
    if (NULL == node)
    {
        DBG(fprintf(stderr, "Creating node failed!!!\n"));
        return (NULL);
    }
    
    node->next = next;
    node->prev = prev;
    node->data = data;
    
    return (node);
}

 


















    
    
