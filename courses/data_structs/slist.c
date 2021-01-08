/*****************************************************************************
 * File name:   slist.c
 * Developer:   Yaron Meister
 * Reviewer:    Majd
 * Date:        2018-11-15 12:45:35
 * Description: 
 *****************************************************************************/
 
#include <stdio.h>     /* printf()     */
#include <stdlib.h>    /*              */
#include <assert.h>    /* assert       */

#include "slist.h"       /*              */


/* Macros                  */
 
 
/* Forward Declarations    */
 
 
/* Global variables        */
 
 
 

/******************************************************************************/ 
sl_node_t *SLCreateNode(sl_node_t *next, void *data)
{
    sl_node_t *node = (sl_node_t*)malloc(sizeof(sl_node_t));
        
    if (NULL == node)
    {
        fprintf(stderr, "Malloc failed!!!");
        return (NULL);
    }
    
    assert(data);
    
    node->data = data;   
    node->next = next;
       
    return (node);
}

/******************************************************************************/
void SLFreeNode(sl_node_t *node)
{
    assert(node);
    
    node->data = NULL;                                                                                   /* node->data = NULL, node->next = NULL */
    node->next = NULL;
    free(node);
    node = NULL;
}
    
/******************************************************************************/
void SLFreeAll(sl_node_t *head)
{
    sl_node_t *next_to_free = head;
    sl_node_t *temp = NULL;
        
    assert (head);
       
    while (NULL != next_to_free)
    {
        temp = next_to_free->next;
        free(next_to_free);
        next_to_free = temp;   
    }
}
/******************************************************************************/
sl_node_t *SLInsertAfter(sl_node_t *where, sl_node_t *new_node)
{
    assert(where);
    assert(new_node);
    
    new_node->next = where->next;
    where->next = new_node;
    
    return (new_node);
}

/******************************************************************************/
sl_node_t *SLInsertBefore(sl_node_t *where, sl_node_t *new_node)
{
    void *temp = NULL;
    
    assert(where);
    assert(new_node);
    
    temp = new_node->data; /* Inserting the data before, not the node itself */
    new_node->data = where->data;       
    where->data = temp;
    SLInsertAfter(where, new_node);

    return (where);
}

/******************************************************************************/
sl_node_t *SLRemoveAfter(sl_node_t *node)
{
    sl_node_t *removed = NULL;
    
    assert(node);
    
    if (NULL != node->next)
    {
        removed = node->next; 
        node->next = removed->next;
        removed->next = NULL;
    }
    
    return (removed);
}

/******************************************************************************/
sl_node_t *SLRemove(sl_node_t *node)
{    
    assert(node);
   
    if (NULL != node->next)     /* Removing the data, not the node itself */
    {   
        node->data = (node->next)->data;
    }
    
    return (SLRemoveAfter(node));
}
    
/******************************************************************************/
size_t SLCount(const sl_node_t *head)
{
    size_t count = 0;
    const sl_node_t *temp = head;
    
    assert(head);
    
    while (NULL != temp)
    {
        ++count;
        temp = temp->next;
    }
    
    return (count);
}     
        
/******************************************************************************/   
int SLForEach(sl_node_t *head, 
              int (*action_func)(void *data, void *param), void *param, 
              sl_node_t **failed_node)
{
    int status = 0;
    sl_node_t *temp = head;

    assert(head);
    
    if (NULL != failed_node)
    {
        *failed_node = NULL;
    }

    while (NULL != temp && 0 == status)
    {
        status = action_func(temp->data, param);
        temp = temp->next;
    }

    if (0 != status && NULL != failed_node)
    {
        *failed_node = temp;
    }

    return (status);
}
    
/******************************************************************************/    
sl_node_t *SLFind(sl_node_t *head, 
                int (*compare_func)(const void *data, const void *param), 
                                                      const void *param)
{
    sl_node_t *temp = head;

    assert(head);
    
    while (NULL != temp)
    {
        if (0 == compare_func(temp->data, param))
        {
            break;
        }

        temp = temp->next;
    }

    return (temp);
}
            
/******************************************************************************/        
sl_node_t *SLFlip(sl_node_t *head)
{
    sl_node_t *temp1 = head;
    sl_node_t *temp2 = NULL;
    sl_node_t *temp3 = NULL;

    assert(head);
    
    temp2 = temp1->next;
    temp3 = temp2->next;

    while (NULL != temp3)
    {
        temp2->next = temp1;
        temp1 = temp2;
        temp2 = temp3;
        temp3 = temp3->next;
    }
    
    temp2->next = temp1;
    head->next = NULL;

    return (temp2);
}
    
/******************************************************************************/        
int SLHasLoop(const sl_node_t *head)
{
    sl_node_t *slow = (sl_node_t*)head;
    sl_node_t *fast = (sl_node_t*)head;

    assert(head);

    while (NULL != slow && NULL != fast && NULL != fast->next)
    {
        slow = slow->next;
        fast = (fast->next)->next;
        
        if (slow == fast)
        {
            return (1);
        }
    }

    return (0);
}   
    
/******************************************************************************/   
sl_node_t *SLFindIntersection(const sl_node_t *head1, const sl_node_t *head2)
{
    sl_node_t *temp_big = NULL;         /* Bigger list  */
    sl_node_t *temp_small = NULL;       /* Smaller list */
    size_t diff = 0;           /* The difference between the lengths of them */

    assert(head1);
    assert(head2);

    if (SLCount(head1) > SLCount(head2))
    {
        temp_big = (sl_node_t*)head1;
        temp_small = (sl_node_t*)head2;
        diff = SLCount(head1) - SLCount(head2);
    }
    else
    {
        temp_big = (sl_node_t*)head2;
        temp_small = (sl_node_t*)head1;
        diff = SLCount(head2) - SLCount(head1);
    }
    
    while (diff > 0)        /* Equaling the lengths of both of the lists */
    {
        temp_big = temp_big->next;
        --diff;
    }

    while (NULL != temp_big && NULL != temp_small)
    {
        if (temp_big == temp_small)
        {
            return (temp_big);
        }

        temp_big = temp_big->next;
        temp_small = temp_small->next;
    }

    return (NULL);
}
   
    
    

   
