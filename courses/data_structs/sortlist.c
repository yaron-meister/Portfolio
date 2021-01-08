/*****************************************************************************
 * File name:   sortlist.c
 * Developer:   Yaron Meister
 * Reviewer:    Eran
 * Date:        2018-11-22 08:43:32
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>          /* printf()             */
#include <stdlib.h>         /* malloc               */
#include <assert.h>         /* assert               */

#include "sortlist.h"       /* Forward declarations */
#include "dlist.h"          /* dlist.c declarations */
#include "utils.h"          /* Utils                */

/* Macros                */

 
/* Forward Declarations  */
struct sorted_list
{
    dlist_t *dlist;
    int (*is_before)(const void *left, const void *right, const void *param);
    const void *param;
}; 
 
/* Global variables      */
  
/******************************************************************************/
sortlist_t *SortListCreate(int (*is_before)(const void *left, const void *right,
        const void *param), const void *param)
{
    dlist_t *dlist = NULL;
    sortlist_t *sortlist = (sortlist_t*)malloc(sizeof(sortlist_t));
    if (NULL == sortlist || NULL == is_before)
    {
        DBG(fprintf(stderr,"Sortlist creation failed!!!\n"));
        free(sortlist);
        sortlist = NULL;
        return (NULL);
    }
    else
    {
        dlist = DListCreate();  
        if (NULL == dlist)                                                                      
        {  
            DBG(fprintf(stderr,"Sortlist creation failed!!!\n"));
            free(sortlist);
            sortlist = NULL;
            return (NULL);
        }
    }
    
    sortlist->dlist = dlist;
    sortlist->is_before = is_before;
    sortlist->param = param;
    
    return (sortlist);
}


/******************************************************************************/
void SortListDestroy(sortlist_t *sortlist)
{
    assert(sortlist);
    
    DListDestroy(sortlist->dlist);
    sortlist->dlist = NULL;
    sortlist->is_before = NULL;
    sortlist->param = NULL;
    free(sortlist);
    sortlist = NULL;
}

/******************************************************************************/
size_t SortListSize(const sortlist_t *sortlist)
{
    assert(sortlist);
    
    return (DListCount(sortlist->dlist));
}

/******************************************************************************/
int SortListIsEmpty(const sortlist_t *sortlist)
{
    assert(sortlist);
    
    return (DListIsEmpty(sortlist->dlist));
}

/******************************************************************************/
sortlist_iter_t SortListEnd(sortlist_t *sortlist)
{
    assert(sortlist);    

    return ((sortlist_iter_t)(DListEnd(sortlist->dlist)));
}

/******************************************************************************/
sortlist_iter_t SortListBegin(sortlist_t *sortlist)
{
    assert(sortlist);

    return ((sortlist_iter_t)(DListBegin(sortlist->dlist)));
}

/******************************************************************************/
sortlist_iter_t SortListNext(sortlist_iter_t iter)
{  
    return ((sortlist_iter_t)(DListNext((dlist_iter_t)iter)));
}
    
/******************************************************************************/
sortlist_iter_t SortListPrev(sortlist_iter_t iter)
{
   return ((sortlist_iter_t)(DListPrev((dlist_iter_t)iter)));
}

/******************************************************************************/
int SortListIsSameIter(sortlist_iter_t iter1, sortlist_iter_t iter2)
{
    return (iter1 == iter2);
}

/******************************************************************************/
int SortListIsBadIter(sortlist_iter_t iter)
{
    return (DListIsBadIter((dlist_iter_t)iter));
}

/******************************************************************************/
void *SortListGetData(sortlist_iter_t iter)
{
    return (DListGetData((dlist_iter_t)iter));
}

/******************************************************************************/
sortlist_iter_t SortListInsert(sortlist_t *sortlist, void *data)
{
    sortlist_iter_t iter = NULL;
    
    assert(sortlist);
    
    iter = SortListBegin(sortlist);

    /* If the inserted data is greater than the iter, then move on */
    while (iter != SortListEnd(sortlist) &&
           !(sortlist->is_before(data, SortListGetData(iter), NULL)))                                        
    {                        
        iter = SortListNext(iter);
    }
    
    /* Inserting the inserted data and returning the iter */
    return ((sortlist_iter_t)DListInsert((dlist_iter_t)iter, data));
}
    
/******************************************************************************/
sortlist_iter_t SortListErase(sortlist_iter_t iter, void **data)
{
    return ((sortlist_iter_t)DListErase((dlist_iter_t)iter, data));
}

/******************************************************************************/       
void *SortListPopFront(sortlist_t *sortlist)
{
    assert(sortlist); 

    return (DListPopFront(sortlist->dlist));
}

/******************************************************************************/
void *SortListPopBack(sortlist_t *sortlist)
{
    assert(sortlist); 

    return (DListPopBack(sortlist->dlist));
}

/******************************************************************************/
sortlist_iter_t SortListForEach(sortlist_iter_t from, sortlist_iter_t to,
    int (*action_func)(void *data, void *param), void *param)
{
    return ((sortlist_iter_t)DListForEach((dlist_iter_t)from, 
                                         (dlist_iter_t)to, action_func, param));
}    

/******************************************************************************/
sortlist_iter_t SortListFind(sortlist_iter_t from, sortlist_iter_t to,
    int (*compare_func)(const void *data, const void *param), const void *param)
{
    return ((sortlist_iter_t)DListFind((dlist_iter_t)from, 
                                      (dlist_iter_t)to, compare_func, param));
}

/******************************************************************************/
void SortListMerge(sortlist_t *dest, sortlist_t *source)
{
    sortlist_iter_t src_iter = NULL;
    sortlist_iter_t dest_iter = NULL;
    
    assert(dest);
    assert(source);
    
    dest_iter = SortListBegin(dest);
    src_iter = SortListBegin(source);  
    
    while (!SortListIsEmpty(source))
    {
        while (!(SortListIsBadIter(src_iter)) &&
               !(SortListIsBadIter(dest_iter)) && 
                (dest->is_before(SortListGetData(src_iter),
                                 SortListGetData(dest_iter), dest->param)))
        {
            src_iter = SortListNext(src_iter);
        }
        
        /* If dest count's less, put al that left from src to dest */
        if (SortListIsBadIter(dest_iter))
        {
            src_iter = SortListEnd(source);
        }

        /* Inserting 'begin(src) - prev(src_iter) into before dest_iter */
        /* Begin(src) is updating in every loop the the head of the next pile */
        DListSpliceBefore((dlist_iter_t)dest_iter, 
                    (dlist_iter_t)SortListBegin(source),(dlist_iter_t)src_iter);
                   
        if (!(SortListIsBadIter(dest_iter)))
        {
            dest_iter = SortListNext(dest_iter);
        }       
    }
}















